#include "atari.h"

#include <stdio.h>
#include <string.h>

static void connect_tia(Atari2600 *a) {
    a->bus.cpu.bus = &a->bus;
    a->bus.tia = &a->tia;
    a->bus.tia_read = a26_tia_read;
    a->bus.tia_write = a26_tia_write;
    a->bus.tia_tick = a26_tia_tick;
    a->bus.tia_ready = a26_tia_ready;
}

int a26_init(Atari2600 *a, const uint8_t *rom, size_t size, A26CartType type, int pal) {
    memset(a, 0, sizeof *a);
    a26_bus_init(&a->bus);
    a26_tia_init(&a->tia);
    if (pal) a->tia.color_rate = 3546895;
    if (a26_cart_init(&a->bus.cart, rom, size, type)) return -1;
    connect_tia(a);
    a->pal = pal;
    a->rom_hash = 2166136261u;
    for (size_t i = 0; i < size; i++) a->rom_hash = (a->rom_hash ^ rom[i]) * 16777619u;
    if (a26_recomp_program && a26_recomp_program->rom_hash == a->rom_hash &&
        a26_recomp_program->mapper == (int)a->bus.cart.type && a26_recomp_program->pal == pal)
        a->program = a26_recomp_program;
    a->audio_lfsr[0] = a->audio_lfsr[1] = 1;
    cpu_reset(&a->bus.cpu);
    return 0;
}

static uint8_t direction(uint16_t pad) {
    uint8_t pins = 15;
    if (pad & PAD_UP) pins &= (uint8_t)~1;
    if (pad & PAD_DOWN) pins &= (uint8_t)~2;
    if (pad & PAD_LEFT) pins &= (uint8_t)~4;
    if (pad & PAD_RIGHT) pins &= (uint8_t)~8;
    return pins;
}

static void set_input(Atari2600 *a, const InputFrame *input) {
    a->bus.riot.input_a = (uint8_t)((direction(input->pad[0]) << 4) | direction(input->pad[1]));
    a->bus.riot.input_b = 0xFF;
    if (input->pad[0] & PAD_START) a->bus.riot.input_b &= (uint8_t)~1;
    if (input->pad[0] & PAD_SELECT) a->bus.riot.input_b &= (uint8_t)~2;
    for (unsigned i = 0; i < 2; i++) {
        a->tia.fire[i] = (input->pad[i] & PAD_A) ? 0 : 0x80;
        if (!(a->tia.reg[1] & 0x40)) a->tia.input[4 + i] = a->tia.fire[i];
        else if (!a->tia.fire[i]) a->tia.input[4 + i] = 0;
    }
}

static const char *compare_state(const Atari2600 *a, const Atari2600 *b, int frame_complete) {
    Cpu ca = a->bus.cpu, cb = b->bus.cpu;
    ca.bus = cb.bus = NULL;
    if (memcmp(&ca, &cb, sizeof ca)) return "CPU";
    if (a->bus.cart.bank != b->bus.cart.bank || memcmp(a->bus.cart.slice, b->bus.cart.slice, sizeof a->bus.cart.slice))
        return "cartridge bank";
    if (memcmp(a->bus.cart.ram, b->bus.cart.ram, sizeof a->bus.cart.ram)) return "cartridge RAM";
    if (memcmp(&a->bus.riot, &b->bus.riot, sizeof a->bus.riot)) return "RIOT";
    size_t start = offsetof(A26Tia, frame), after = start + sizeof a->tia.frame;
    size_t samples = offsetof(A26Tia, samples), end_samples = samples + sizeof a->tia.samples;
    if (memcmp(&a->tia, &b->tia, start) ||
        memcmp((const uint8_t *)&a->tia + after, (const uint8_t *)&b->tia + after, samples - after) ||
        memcmp((const uint8_t *)&a->tia + end_samples, (const uint8_t *)&b->tia + end_samples,
               sizeof a->tia - end_samples)) return "TIA";
    if (frame_complete && (memcmp(a->tia.frame, b->tia.frame, sizeof a->tia.frame) ||
        memcmp(a->tia.samples, b->tia.samples, a->tia.sample_count * sizeof a->tia.samples[0])))
        return "frame or audio";
    return NULL;
}

static void step(Atari2600 *a) {
    Cpu *cpu = &a->bus.cpu;
    unsigned address = cpu->pc & 0x1FFF;
    unsigned bank = a->bus.cart.bank;
    unsigned offset = address & 0xFFF;
    if (a->trace && (address & 0x1000)) a->trace[bank * 4096 + offset] = 1;
    A26RecompFn fn = (a->program && (address & 0x1000) && !cpu->poll_prev)
        ? a->program->lookup(bank, offset) : NULL;
    uint64_t before = cpu->cycles;
    uint16_t pc = cpu->pc;
    unsigned previous_frame = a->tia.frames;
    if (fn) fn(cpu); else cpu_step(cpu);
    a->total_cycles += cpu->cycles - before;
    if (fn) a->compiled_cycles += cpu->cycles - before;
    if (a->reference) {
        cpu_step(&a->reference->bus.cpu);
        const char *difference = compare_state(a, a->reference, a->tia.frames != previous_frame);
        if (difference) {
            fprintf(stderr, "Atari diff: %s diverged at PC $%04X bank %u cycle %llu\n",
                    difference, pc, bank, (unsigned long long)before);
            fprintf(stderr, "compiled: PC=%04X A=%02X X=%02X Y=%02X S=%02X P=%02X bank=%u TIA=%u,%u RIOT=%02X\n",
                    cpu->pc, cpu->a, cpu->x, cpu->y, cpu->s, cpu->p, a->bus.cart.bank,
                    a->tia.x, a->tia.y, a->bus.riot.timer);
            Cpu *ref = &a->reference->bus.cpu;
            fprintf(stderr, "reference: PC=%04X A=%02X X=%02X Y=%02X S=%02X P=%02X bank=%u TIA=%u,%u RIOT=%02X\n",
                    ref->pc, ref->a, ref->x, ref->y, ref->s, ref->p, a->reference->bus.cart.bank,
                    a->reference->tia.x, a->reference->tia.y, a->reference->bus.riot.timer);
            a->diff_failed = 1;
        }
    }
}

void a26_frame(Atari2600 *a, const InputFrame *input) {
    set_input(a, input);
    if (a->reference) set_input(a->reference, input);
    unsigned frame = a->tia.frames;
    uint64_t end = a->bus.cpu.cycles + 76 * 400;
    while (a->tia.frames == frame && a->bus.cpu.cycles < end && !a->bus.cpu.jammed && !a->diff_failed)
        step(a);
    if (a->reference && !a->diff_failed) {
        const char *difference = compare_state(a, a->reference, 1);
        if (difference) {
            fprintf(stderr, "Atari diff: %s diverged at frame boundary\n", difference);
            a->diff_failed = 1;
        }
    }
}

/* A26STAT2's layout; A26STAT3 adds the cartridge's slices and RAM after it. */
typedef struct {
    char magic[8];
    uint32_t hash;
    int pal;
    Cpu cpu;
    A26Riot riot;
    A26Tia tia;
    unsigned bank;
    uint32_t audio_phase[2];
    uint16_t audio_lfsr[2];
    unsigned sample_phase;
} A26StateV2;

typedef struct {
    A26StateV2 v2;
    uint8_t slice[4];
    uint8_t ram[2048];
} A26State;

int a26_save(Atari2600 *a, const char *path) {
    A26State state = {0};
    memcpy(state.v2.magic, "A26STAT3", 8);
    state.v2.hash = a->rom_hash;
    state.v2.pal = a->pal;
    state.v2.cpu = a->bus.cpu;
    state.v2.cpu.bus = NULL;
    for (unsigned i = 0; i < 32; i++) {
        state.v2.cpu.read_map[i] = NULL;
        state.v2.cpu.write_map[i] = NULL;
    }
    state.v2.riot = a->bus.riot;
    state.v2.tia = a->tia;
    state.v2.bank = a->bus.cart.bank;
    memcpy(state.v2.audio_phase, a->audio_phase, sizeof state.v2.audio_phase);
    memcpy(state.v2.audio_lfsr, a->audio_lfsr, sizeof state.v2.audio_lfsr);
    state.v2.sample_phase = a->sample_phase;
    memcpy(state.slice, a->bus.cart.slice, sizeof state.slice);
    memcpy(state.ram, a->bus.cart.ram, sizeof state.ram);
    FILE *file = fopen(path, "wb");
    if (!file) return -1;
    int failed = fwrite(&state, sizeof state, 1, file) != 1;
    if (fclose(file)) failed = 1;
    return failed ? -1 : 0;
}

int a26_load(Atari2600 *a, const char *path) {
    A26State state;
    FILE *file = fopen(path, "rb");
    if (!file) return -1;
    size_t got = fread(&state, 1, sizeof state, file);
    fclose(file);
    int legacy = !memcmp(state.v2.magic, "A26STATE", 8);
    int v3 = !memcmp(state.v2.magic, "A26STAT3", 8);
    if (got != (v3 ? sizeof state : sizeof state.v2)) return -1;
    if (!v3) {  /* older states: no slices, no cartridge RAM */
        memset(state.slice, 0, sizeof state.slice);
        memset(state.ram, 0, sizeof state.ram);
    }
    A26CartType type = a->bus.cart.type;
    unsigned limit = type == A26_CART_E0 ? 8 : type == A26_CART_E7 ? (unsigned)(a->bus.cart.size / 2048) : 256;
    if (state.slice[0] >= limit || state.slice[1] >= (type == A26_CART_E7 ? 4u : limit) ||
        state.slice[2] >= limit || state.slice[3]) return -1;
    if ((!legacy && !v3 && memcmp(state.v2.magic, "A26STAT2", 8)) || state.v2.hash != a->rom_hash ||
        state.v2.pal != a->pal || state.v2.bank >= a->bus.cart.banks || state.v2.tia.x >= 228 ||
        state.v2.tia.y >= A26_HEIGHT || state.v2.tia.sample_count > 2048 ||
        state.v2.tia.color_rate != (unsigned)(a->pal ? 3546895 : 3579545) ||
        (state.v2.riot.divider != 1 && state.v2.riot.divider != 8 &&
         state.v2.riot.divider != 64 && state.v2.riot.divider != 1024)) return -1;
    if (legacy) {
        state.v2.tia.pf_pixel = state.v2.tia.pf_reflect = state.v2.tia.rsync_skip = state.v2.tia.next_hmove = 0;
        state.v2.tia.motion_counter = state.v2.tia.moving = 0;
        state.v2.tia.audio_clock = (uint8_t)state.v2.tia.x;
        memset(state.v2.tia.reserved, 0, sizeof state.v2.tia.reserved);
    }
    if (state.v2.tia.pf_pixel > 1 || state.v2.tia.pf_reflect > 1 ||
        state.v2.tia.rsync_skip > state.v2.tia.x || state.v2.tia.next_hmove > 6 ||
        state.v2.tia.motion_counter > 15 || state.v2.tia.moving > 0x1F || state.v2.tia.audio_clock >= 228 ||
        (state.v2.tia.next_hmove && state.v2.tia.next_hmove <= state.v2.tia.pending_delay[0x2A])) return -1;
    for (unsigned i = 0; i < 5; i++)
        if ((unsigned)state.v2.tia.position[i] >= A26_WIDTH) return -1;
    unsigned pending = 0;
    for (unsigned i = 0; i < 64; i++) {
        if (state.v2.tia.pending_delay[i] > (i >= sizeof state.v2.tia.reg ? 0 : i == 0x2A ? 6 : 2)) return -1;
        if (state.v2.tia.pending_delay[i]) pending++;
    }
    if (pending != state.v2.tia.pending_count) return -1;
    a->bus.cpu = state.v2.cpu;
    for (unsigned i = 0; i < 32; i++) {
        a->bus.cpu.read_map[i] = NULL;
        a->bus.cpu.write_map[i] = NULL;
    }
    a->bus.riot = state.v2.riot;
    a->tia = state.v2.tia;
    a->bus.cart.bank = state.v2.bank;
    if (v3) {
        memcpy(a->bus.cart.slice, state.slice, sizeof state.slice);
        memcpy(a->bus.cart.ram, state.ram, sizeof state.ram);
    }
    memcpy(a->audio_phase, state.v2.audio_phase, sizeof a->audio_phase);
    memcpy(a->audio_lfsr, state.v2.audio_lfsr, sizeof a->audio_lfsr);
    a->sample_phase = state.v2.sample_phase;
    connect_tia(a);
    return 0;
}
