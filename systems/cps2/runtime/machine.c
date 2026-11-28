#include "machine.h"
#include "cps2crypt.h"
#include "recomp_rt.h"

#include <stdlib.h>
#include <string.h>

static uint16_t be16(const uint8_t *p)
{
    return (uint16_t)(p[0] << 8 | p[1]);
}

uint16_t cps2_opcode(const Cps2Machine *s, uint32_t address)
{
    return s->opcodes ? s->opcodes[address / 2] : be16(s->program + address);
}

int cps2_machine_set_recomp(Cps2Machine *s, const Cps2Recomp *program)
{
    uint32_t hash = 2166136261u;
    for (uint32_t a = 0; a < s->program_size; a += 2) {
        uint16_t word = cps2_opcode(s, a);
        hash = (hash ^ (word >> 8)) * 16777619u;
        hash = (hash ^ (word & 255)) * 16777619u;
    }
    s->recomp = program && hash == program->opcode_hash ? program : NULL;
    return s->recomp != NULL;
}

static uint8_t *mapped_ram(Cps2Machine *s, uint32_t a, int write)
{
    if (a >= 0xff0000)
        return s->work + (a - 0xff0000);
    if (a >= 0x900000 && a <= 0x92ffff)
        return s->graphics + (a - 0x900000);
    if (a >= 0x708000 && a <= 0x70ffff)
        return s->objects[s->object_bank ^ 1] + (a & 0x1fff);
    if (write && a >= 0x700000 && a <= 0x701fff)
        return s->objects[s->object_bank] + (a & 0x1fff);
    if (a >= 0x400000 && a <= 0x40000b)
        return s->output + (a - 0x400000);
    if ((a & 0xffbfc0) == 0x800140)
        return s->cps_b + (a & 0x3f);
    if (write && (a & 0xffbfc0) == 0x800100)
        return s->cps_a + (a & 0x3f);
    return NULL;
}

uint16_t m68k_read(M68k *c, uint32_t a, unsigned fc, unsigned strobe)
{
    (void)strobe;
    Cps2Machine *s = c->bus;
    a &= 0xfffffe;
    if (a < s->program_size) {
        /* Reset vectors are data even though the core issues program cycles. */
        if ((fc & 3) == 2)
            return cps2_opcode(s, a);
        return be16(s->program + a);
    }
    switch (a & 0xffbffe) {
    case 0x800144:
    case 0x800146: {
        uint32_t product = (uint32_t)be16(s->cps_b) * be16(s->cps_b + 2);
        return (uint16_t)(product >> ((a & 2) ? 16 : 0));
    }
    case 0x800150:
    case 0x800152:
        return s->raster_counter[(a >> 1) & 1];
    }
    const uint8_t *ram = mapped_ram(s, a, 0);
    if (ram)
        return be16(ram);
    if (a >= 0x618000 && a <= 0x619fff) {
        if (s->audio_program)
            cps2_sound_run(s);
        return 0xff00 | s->shared[(a - 0x618000) / 2];
    }
    switch (a) {
    case 0x804000: return s->inputs[0];
    case 0x804010: return s->inputs[1];
    case 0x804020: return (s->inputs[2] & 0xfffe) | eeprom_do(&s->eeprom, c->cycles / 16);
    case 0x804030: return 0xe021;
    default: return 0xffff;
    }
}

void m68k_write(M68k *c, uint32_t a, uint16_t v, unsigned fc, unsigned strobe)
{
    (void)fc;
    Cps2Machine *s = c->bus;
    a &= 0xfffffe;
    uint8_t *ram = mapped_ram(s, a, 1);
    if (ram) {
        if (strobe & 2) ram[0] = (uint8_t)(v >> 8);
        if (strobe & 1) ram[1] = (uint8_t)v;
        if ((a & 0xffbffe) == 0x80010a)
            cps2_palette_upload(s);
        if ((a & 0xffbffe) == 0x800150 || (a & 0xffbffe) == 0x800152) {
            unsigned counter = (a >> 1) & 1;
            uint16_t value = be16(ram);
            s->raster_reload[counter] = value & 0x1ff;
            if (value & 0x8000)
                s->raster_counter[counter] = s->raster_reload[counter];
        }
    } else if (a == 0x804040 && (strobe & 2)) {
        eeprom_write_lines(&s->eeprom, (v >> 14) & 1, (v >> 13) & 1,
                          (v >> 12) & 1, c->cycles / 16);
    } else if (a == 0x8040e0 && (strobe & 1)) {
        s->object_bank = v & 1;
    } else if (a >= 0x618000 && a <= 0x619fff && (strobe & 1)) {
        if (s->audio_program)
            cps2_sound_run(s);
        s->shared[(a - 0x618000) / 2] = (uint8_t)v;
    }
    if (a == 0x804040 && (strobe & 1))
        cps2_sound_control(s, (uint8_t)v);
}

void m68k_idle(M68k *c, unsigned clocks) { (void)c; (void)clocks; }
void m68k_aborted(M68k *c, uint32_t a, unsigned fc, unsigned strobe, int write)
{ (void)c; (void)a; (void)fc; (void)strobe; (void)write; }
int m68k_iack(M68k *c, int level) { (void)level; c->ipl = 0; return -1; }
void m68k_reset_out(M68k *c) { (void)c; }

int cps2_machine_init(Cps2Machine *s, const Cps2Rom *rom)
{
    memset(s, 0, sizeof(*s));
    s->program = cps2_region(rom, "maincpu", &s->program_size);
    if (!s->program || s->program_size < 8 || s->program_size > 0x400000 || s->program_size % 2)
        return -1;
    size_t key_size;
    const uint8_t *key = cps2_region(rom, "key", &key_size);
    if (key) {
        if (key_size < 20)
            return -1;
        uint16_t *words = malloc(s->program_size);
        s->opcodes = malloc(s->program_size);
        if (!words || !s->opcodes) {
            free(words);
            cps2_machine_destroy(s);
            return -1;
        }
        for (size_t i = 0; i < s->program_size / 2; ++i)
            words[i] = be16(s->program + 2 * i);
        cps2_decrypt(words, s->opcodes, (int)s->program_size, key);
        free(words);
    }
    if (cps2_video_init(s, rom)) {
        cps2_machine_destroy(s);
        return -1;
    }
    eeprom_init(&s->eeprom, 0);
    s->raster_reload[0] = s->raster_reload[1] = 0x1ff;
    s->raster_clock = UINT64_MAX;
    for (size_t i = 0; i < 3; ++i)
        s->inputs[i] = 0xffff;
    s->cpu.bus = s;
    m68k_reset(&s->cpu);
    return 0;
}

void cps2_machine_destroy(Cps2Machine *s)
{
    free(s->opcodes);
    free(s->tiles);
    s->opcodes = NULL;
    s->tiles = NULL;
}

static void run_native(M68k *cpu, Cps2RecompFn block)
{
    if (!setjmp(cpu->abort))
        block(cpu);
}

void cps2_machine_run(Cps2Machine *s, uint64_t until)
{
    s->deadline = until;
    while (s->cpu.cycles < until && !s->cpu.halted) {
        if (s->cpu.cycles >= s->line_clock) {
            for (unsigned i = 0; i < 2; ++i) {
                s->raster_counter[i] = s->scanline
                    ? (s->raster_counter[i] - 1) & 0x1ff : s->raster_reload[i];
                if (!s->raster_counter[i])
                    s->raster_clock = s->line_clock + ((be16(s->cps_b + 0x0e) >> 1) & 0xff) * 4;
            }
            if (s->scanline == 16)
                s->rendered = 0;
            if (s->scanline == 240) {
                cps2_video_render(s, 224);
                memcpy(s->latched_objects, s->objects[s->object_bank],
                       sizeof(s->latched_objects));
                s->priority = be16(s->output + 4);
                s->cpu.ipl |= 2;
            }
            s->scanline = (s->scanline + 1) % 262;
            s->line_clock += 1024;
        }
        if (s->cpu.cycles >= s->raster_clock) {
            if (s->scanline > 16 && s->scanline <= 240)
                cps2_video_render(s, s->scanline - 16);
            s->cpu.ipl |= 4;
            s->raster_clock = UINT64_MAX;
        }
        M68k *cpu = &s->cpu;
        uint32_t pc = (cpu->pc - 4) & 0xffffff;
        Cps2RecompFn block = NULL;
        if (s->executed && !(pc & 1) && pc < s->program_size &&
            !cpu->stopped && !cpu->trace && !cpu->ipl && !cpu->ipl_seen)
            s->executed[pc] = 1;
        if (s->recomp && !CPS2_STOP(s, cpu) && !(pc & 1) && pc < s->program_size &&
            cpu->ir == cps2_opcode(s, pc))
            block = s->recomp->lookup(pc);
        uint64_t before = cpu->cycles;
        if (block) {
            run_native(cpu, block);
            s->native_clocks += cpu->cycles - before;
        } else {
            m68k_step(cpu);
        }
        if (s->audio_program)
            cps2_sound_run(s);
    }
}
