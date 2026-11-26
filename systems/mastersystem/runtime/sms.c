/* The Master System machine: the Z80's memory and I/O, the pads, and a
 * frame's timeline. No BIOS: the cartridge starts at $0000, as games do on a
 * console whose BIOS found them (the mapper's power-on banks 0, 1, 2). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input_log.h"
#include "recomp_rt.h"
#include "sms.h"

/* ---- memory ---- */
static int cart_ram_on(const Sms *s, uint16_t a) { return a >= 0x8000 && a < 0xC000 && s->cart.mapper <= SMS_MAPPER_CODEMASTERS && (s->cart.page[0] & 0x08); }
static uint8_t *cart_ram(Sms *s, uint16_t a) {
    return &s->cart.ram[(s->cart.page[0] & 0x04 ? 0x4000 : 0) + (a & 0x3FFF)];
}

static uint8_t read_mem(Sms *s, uint16_t a) {
    if (a >= 0xC000) return s->ram[a & 0x1FFF];
    if (cart_ram_on(s, a)) return *cart_ram(s, a);
    uint32_t off = sms_cart_addr(&s->cart, a);
    return off < s->cart.size ? s->cart.data[off] : 0xFF;
}

static void write_mem(Sms *s, uint16_t a, uint8_t v) {
    if (a >= 0xC000) {
        s->ram[a & 0x1FFF] = v;  /* the mapper registers are written through to RAM too */
        if (a >= 0xFFFC && s->cart.mapper == SMS_MAPPER_SEGA) s->cart.page[a & 3] = v;
    } else if (cart_ram_on(s, a)) {
        *cart_ram(s, a) = v;
        s->cart.ram_used = 1;
    } else if (sms_mapped_8k(&s->cart) && a < 4) {
        s->cart.page[a] = v;
    } else if (s->cart.mapper == SMS_MAPPER_KOREAN && a == 0xA000) {
        s->cart.page[3] = v;
    } else if (s->cart.mapper == SMS_MAPPER_CODEMASTERS && (a & 0x3FFF) == 0) {
        s->cart.page[1 + (a >> 14)] = v;
    }
}

uint8_t z80_fetch(Z80 *z, uint16_t pc) { return read_mem(z->bus, pc); }
uint8_t z80_read(Z80 *z, uint16_t a) { return read_mem(z->bus, a); }
void z80_write(Z80 *z, uint16_t a, uint8_t v) { write_mem(z->bus, a, v); }
void z80_idle(Z80 *z, uint16_t a, unsigned n) { (void)z, (void)a, (void)n; }
uint8_t z80_irq_ack(Z80 *z) { (void)z; return 0xFF; }  /* games use IM 1: RST $38 */

/* ---- I/O: decoded by A7, A6 and A0 (SMS Power, Port map) ---- */
/* $DC: pad 1 up, down, left, right, button 1, button 2, pad 2 up, down;
 * $DD: pad 2 left, right, 1, 2, Reset, -, then the TH lines (0 = pressed). */
static unsigned pad_bits(uint16_t p) {
    return (p & PAD_UP ? 1 : 0) | (p & PAD_DOWN ? 2 : 0) | (p & PAD_LEFT ? 4 : 0) |
           (p & PAD_RIGHT ? 8 : 0) | (p & PAD_B ? 16 : 0) | (p & PAD_A ? 32 : 0);
}

static uint8_t port_dd(const Sms *s) {
    unsigned p2 = pad_bits(s->pad[1]);
    uint8_t v = (uint8_t)~(p2 >> 2) & 0x0F;
    v |= 0x30;  /* Reset not pressed; bit 5 reads 1 */
    /* TH: an output set by $3F reads back its level (export consoles), an input reads 1 */
    v |= s->io_ctrl & 0x02 ? 0x40 : s->io_ctrl & 0x20 ? 0x40 : 0;
    v |= s->io_ctrl & 0x08 ? 0x80 : s->io_ctrl & 0x80 ? 0x80 : 0;
    return v;
}

/* Game Gear ports $00-$06 (SMS Power, I/O Port Map - Game Gear): $00 is
 * Start (bit 7, 0 = pressed), export (bit 6) and NTSC (bit 5 = 0); $01-$05
 * the link port, read as nothing connected. */
static uint8_t gg_port(const Sms *s, unsigned port) {
    static const uint8_t link[6] = {0, 0x7F, 0xFF, 0x00, 0xFF, 0x00};
    if (port) return link[port];
    long h = sms_header(s->cart.data, s->cart.size);
    int japan = h >= 0 && s->cart.data[h + 15] >> 4 == 5;
    return (uint8_t)(((s->pad[0] | s->pad[1]) & PAD_START ? 0 : 0x80) | (japan ? 0 : 0x40));
}

uint8_t z80_in(Z80 *z, uint16_t port) {
    Sms *s = z->bus;
    if (s->vdp.gg && (port & 0xFF) < 6) return gg_port(s, port & 0xFF);
    switch (port & 0xC1) {
    case 0x40: return sms_vdp_vcount(s);
    case 0x41: return sms_vdp_hcount(s);
    case 0x80: return sms_vdp_read_data(&s->vdp);
    case 0x81: return sms_vdp_read_status(&s->vdp);
    case 0xC0: return (uint8_t)~(pad_bits(s->pad[0]) | (pad_bits(s->pad[1]) & 3) << 6);
    case 0xC1: return port_dd(s);
    default: return 0xFF;
    }
}

void z80_out(Z80 *z, uint16_t port, uint8_t v) {
    Sms *s = z->bus;
    /* shortcut: the Game Gear's stereo register ($06) and link port are ignored, the
     * sound is mono; keep $06 and mix two channels if stereo is wanted */
    if (s->vdp.gg && (port & 0xFF) < 7) return;
    switch (port & 0xC1) {
    case 0x00: s->mem_ctrl = v; break;
    case 0x01: s->io_ctrl = v; break;
    case 0x40: case 0x41: sms_psg_run(&s->psg, z->tstates); sms_psg_write(&s->psg, v); break;
    case 0x80: sms_vdp_write_data(&s->vdp, v); s->writes++; break;
    case 0x81: sms_vdp_write_ctrl(&s->vdp, v); s->writes++; break;
    default: break;
    }
}

/* ---- recompiled code ---- */
uint32_t sms_rom_hash(const uint8_t *rom, size_t size) {
    uint32_t h = 2166136261u;
    for (size_t i = 0; i < size; i++) h = (h ^ rom[i]) * 16777619u;
    return h;
}

unsigned sms_page_at(const SmsCart *c, uint16_t a) {
    return a < 0x0400 && c->mapper == SMS_MAPPER_SEGA ? 0 : c->page[1 + (a >> 14)];
}

void sms_step(Sms *s) {
    uint64_t before = s->cpu.tstates;
    SmsRecompFn f = NULL;
    if (s->recomp_on && !s->cpu.halted && s->cpu.pc < SMS_CODE_SPAN)
        f = sms_recomp_program->lookup(s->cpu.pc, sms_page_at(&s->cart, s->cpu.pc));
    if (f) {
        f(&s->cpu);
        s->cycles_native += s->cpu.tstates - before;
    } else {
        if (s->misses && !sms_mapped_8k(&s->cart) && s->cpu.pc < SMS_CODE_SPAN) {
            unsigned page = sms_page_at(&s->cart, s->cpu.pc);
            if (page < (s->cart.size + SMS_ROM_BANK - 1) / SMS_ROM_BANK) s->misses[sms_code_index(page, s->cpu.pc)] = 1;
        }
        z80_step(&s->cpu);
        s->cycles_interp += s->cpu.tstates - before;
    }
}

size_t sms_miss_slots(const Sms *s) {
    return sms_code_index((unsigned)((s->cart.size + SMS_ROM_BANK - 1) / SMS_ROM_BANK), 0);
}

void sms_misses_write(const Sms *s, FILE *f) {
    for (size_t i = 0, n = sms_miss_slots(s); i < n; i++)
        if (s->misses[i]) fprintf(f, "MISS $%04X page %u\n", (unsigned)(i % SMS_CODE_SPAN), (unsigned)(i / SMS_CODE_SPAN));
}

size_t sms_misses_merge(Sms *s, const char *path) {
    size_t n = sms_miss_slots(s), fresh = 0;
    uint8_t *known = calloc(n, 1);
    if (!known) return 1;
    FILE *f = fopen(path, "r");
    char line[64];
    unsigned pc, page;
    while (f && fgets(line, sizeof line, f))
        if (sscanf(line, "MISS $%x page %u", &pc, &page) == 2 && pc < SMS_CODE_SPAN && sms_code_index(page, (uint16_t)pc) < n)
            known[sms_code_index(page, (uint16_t)pc)] = 1;
    if (f) fclose(f);
    for (size_t i = 0; i < n; i++) fresh += s->misses[i] && !known[i], s->misses[i] |= known[i];
    free(known);
    return fresh;
}

/* ---- the machine ---- */
unsigned sms_lines(const Sms *s) { return s->pal ? SMS_LINES_PAL : SMS_LINES_NTSC; }

void sms_reset(Sms *s) {
    memset(&s->cpu, 0, sizeof s->cpu);
    s->cpu.bus = s;
    z80_reset(&s->cpu);
    s->cpu.sp = 0xDFF0;  /* where the BIOS leaves it */
    memset(s->ram, 0, sizeof s->ram);
    uint8_t gg = s->vdp.gg;
    memset(&s->vdp, 0, sizeof s->vdp);
    s->vdp.gg = gg;
    s->cart.page[0] = 0, s->cart.page[1] = 0;
    s->cart.page[2] = sms_mapped_8k(&s->cart) ? 0 : 1;
    s->cart.page[3] = s->cart.mapper == SMS_MAPPER_SEGA || s->cart.mapper == SMS_MAPPER_KOREAN ? 2 : 0;
    s->mem_ctrl = 0xAB, s->io_ctrl = 0xFF;
    s->pause = 0;
    s->line = 0;
    s->line_start = 0;
    s->frames = 0;
    s->cycles_native = s->cycles_interp = 0;
    s->samples_made = 0;
    s->n_samples = 0;
    sms_psg_reset(&s->psg);
}

int sms_init(Sms *s, const uint8_t *rom, size_t size, int pal, int gg) {
    if (!rom || !size) return 1;
    memset(s, 0, sizeof *s);
    s->cart.data = rom;
    s->cart.size = size;
    s->cart.mapper = (uint8_t)sms_mapper(rom, size);
    s->pal = pal && !gg;  /* every Game Gear is 60 Hz */
    s->vdp.gg = (uint8_t)(gg != 0);
    /* shortcut: MSX slots are 8 KB, use the interpreter until code generation supports that layout. */
    s->recomp_on = !sms_mapped_8k(&s->cart) && sms_recomp_program && sms_recomp_program->rom_hash == sms_rom_hash(rom, size);
    sms_reset(s);
    return 0;
}

static uint64_t sample_time(const Sms *s, uint64_t n) {
    return n * (uint64_t)(s->pal ? SMS_CLOCK_PAL : SMS_CLOCK_NTSC) / SMS_SAMPLE_RATE;
}

void sms_frame(Sms *s, uint16_t pad0, uint16_t pad1) {
    s->pad[0] = pad0, s->pad[1] = pad1;
    int pause = ((pad0 | pad1) & PAD_START) != 0;
    if (pause && !s->pause && !s->vdp.gg) z80_nmi(&s->cpu);  /* Pause is the Z80's NMI, on the press */
    s->pause = (uint8_t)pause;
    s->n_samples = 0;
    unsigned lines = sms_lines(s);
    for (unsigned line = 0; line < lines; line++) {
        s->line = line;
        sms_vdp_line(s, line);
        uint64_t end = s->line_start + SMS_LINE_TSTATES;
        s->line_end = end;
        while (s->cpu.tstates < end)
            if (!sms_vdp_irq(&s->vdp) || !z80_interrupt(&s->cpu)) sms_step(s);
        for (uint64_t t; (t = sample_time(s, s->samples_made + 1)) <= end; s->samples_made++) {
            sms_psg_run(&s->psg, t);
            if (s->n_samples < sizeof s->samples / sizeof s->samples[0])
                s->samples[s->n_samples++] = sms_psg_take(&s->psg);
        }
        s->line_start = end;
    }
    s->frames++;
}

/* ---- save states: the machine without the ROM pointer ---- */
static const char MAGIC[8] = {'S', 'M', 'S', 'S', 'T', 'A', 'T', '2'};

int sms_save(const Sms *s, const char *path) {
    FILE *f = fopen(path, "wb");
    if (!f) return 1;
    Sms copy = *s;
    copy.cart.data = NULL;
    copy.cpu.bus = NULL;
    copy.misses = NULL;
    uint32_t size = sizeof copy;
    int bad = fwrite(MAGIC, 1, 8, f) != 8 || fwrite(&size, 4, 1, f) != 1 || fwrite(&copy, 1, sizeof copy, f) != sizeof copy;
    return fclose(f) || bad;
}

int sms_load(Sms *s, const char *path, char *err, size_t errlen) {
    static Sms loaded;
    FILE *f = fopen(path, "rb");
    if (!f) { snprintf(err, errlen, "cannot open state %s", path); return 1; }
    char magic[8];
    uint32_t size = 0;
    int bad = fread(magic, 1, 8, f) != 8 || memcmp(magic, MAGIC, 8) || fread(&size, 4, 1, f) != 1 ||
              size != sizeof loaded || fread(&loaded, 1, sizeof loaded, f) != sizeof loaded;
    fclose(f);
    if (bad || loaded.cart.mapper != s->cart.mapper) { snprintf(err, errlen, "%s: incompatible save state", path); return 1; }
    const uint8_t *rom = s->cart.data;
    size_t rom_size = s->cart.size;
    uint8_t *misses = s->misses;
    int recomp_on = s->recomp_on;
    *s = loaded;
    s->cart.data = rom;
    s->cart.size = rom_size;
    s->misses = misses;
    s->recomp_on = recomp_on;
    s->cpu.bus = s;
    return 0;
}
