/* The CPS-1's 68000 side (cps1.h): the memory map, inputs and DIP
 * switches, the CPS-A / CPS-B registers, and the frame's timeline.
 *   $000000-$3FFFFF  program ROM
 *   $800000          players (P1 low byte, P2 high; active low)
 *   $800018-$80001F  system inputs, DIP switches A-C (in the high byte)
 *   $800100-$80013F  CPS-A registers;  $800140-$80017F  CPS-B registers
 *   $800180 / $800188  sound command / fade (for the Z80)
 *   $900000-$92FFFF  graphics RAM;  $FF0000-$FFFFFF  work RAM
 * Anything else reads $FFFF. VBlank is interrupt level 2 (autovector) from
 * line 240, held until acknowledged.
 * The sound Z80: $0000-$7FFF ROM, $8000-$BFFF a 16 KB bank (ROM $8000 +
 * bank x $4000; $F004 bit 0), $D000-$D7FF RAM, $F000/$F001 the YM2151,
 * $F002 the OKI ($F006 its pin 7), $F008 / $F00A the 68000's command and fade; the YM2151's
 * IRQ is its INT. It runs line by line after the 68000.
 * Sources: docs/sources.md (CPS-1, CPS-1 sound). */
#include <string.h>

#include "cps1.h"
#include "input_log.h"

static uint16_t be16(const uint8_t *p) { return (uint16_t)(p[0] << 8 | p[1]); }

static void put(uint8_t *p, uint16_t v, unsigned strobe) {
    if (strobe & 2) p[0] = (uint8_t)(v >> 8);
    if (strobe & 1) p[1] = (uint8_t)v;
}

/* a register after a write of the bytes strobe selects (2 upper, 1 lower) */
static uint16_t merge(uint16_t old, uint16_t v, unsigned strobe) {
    uint16_t mask = (uint16_t)((strobe & 2 ? 0xFF00 : 0) | (strobe & 1 ? 0x00FF : 0));
    return (uint16_t)((old & ~mask) | (v & mask));
}

static uint16_t players(const Cps1 *s) {
    uint16_t v = 0;
    for (int p = 0; p < 2; p++) {
        uint16_t pad = s->pad[p], b = 0;
        if (pad & PAD_RIGHT) b |= 0x01;
        if (pad & PAD_LEFT) b |= 0x02;
        if (pad & PAD_DOWN) b |= 0x04;
        if (pad & PAD_UP) b |= 0x08;
        if (pad & PAD_B) b |= 0x10;  /* button 1 */
        if (pad & PAD_A) b |= 0x20;  /* button 2 */
        if (pad & PAD_X) b |= 0x40;  /* button 3 */
        v |= (uint16_t)(b << (p * 8));
    }
    return (uint16_t)~v;
}

static uint8_t system_in(const Cps1 *s) {
    uint8_t v = 0;
    for (int p = 0; p < 2; p++) {
        if (s->pad[p] & PAD_SELECT) v |= (uint8_t)(0x01 << p);  /* coins */
        if (s->pad[p] & PAD_START) v |= (uint8_t)(0x10 << p);
    }
    return (uint8_t)~v;
}

/* MAME's IN2: Street Fighter II's kicks (P1 bits 0-2, P2 bits 4-6), or
 * player 3 (directions, buttons 1-2, coin 3, start 3); active low. */
static uint16_t extra_in(const Cps1 *s) {
    uint8_t v = 0;
    if (s->rom->game->extra == CPS1_EXTRA_KICKS) {
        for (int p = 0; p < 2; p++) {
            uint16_t pad = s->pad[p];
            uint8_t b = (uint8_t)((pad & PAD_Y ? 1 : 0) | (pad & PAD_L ? 2 : 0) | (pad & PAD_R ? 4 : 0));
            v |= (uint8_t)(b << (p * 4));
        }
    } else if (s->rom->game->extra == CPS1_EXTRA_P3) {
        uint16_t pad = s->pad[2];
        if (pad & PAD_RIGHT) v |= 0x01;
        if (pad & PAD_LEFT) v |= 0x02;
        if (pad & PAD_DOWN) v |= 0x04;
        if (pad & PAD_UP) v |= 0x08;
        if (pad & PAD_B) v |= 0x10;
        if (pad & PAD_A) v |= 0x20;
        if (pad & PAD_SELECT) v |= 0x40;
        if (pad & PAD_START) v |= 0x80;
    }
    return (uint8_t)~v;
}

static uint16_t cpsb_read(const Cps1 *s, unsigned off) {
    const Cps1B *b = &s->rom->game->b;
    if (s->rom->game->in2 != CPS1_NONE && off == s->rom->game->in2) return extra_in(s);
    uint32_t product = (uint32_t)s->mult_a * s->mult_b;
    if (off == b->id_reg) return b->id_val;
    if (off == b->mult_lo) return (uint16_t)product;
    if (off == b->mult_hi) return (uint16_t)(product >> 16);
    return s->cpsb[off >> 1];
}

static void cpsb_write(Cps1 *s, unsigned off, uint16_t v) {
    const Cps1B *b = &s->rom->game->b;
    if (off == b->mult_a) s->mult_a = v;
    else if (off == b->mult_b) s->mult_b = v;
    s->cpsb[off >> 1] = v;
}

static uint16_t rd(Cps1 *s, uint32_t a, unsigned strobe) {
    (void)strobe;
    a &= 0xFFFFFE;
    const Cps1Rom *r = s->rom;
    if (a < 0x400000) return a + 1 < r->size[CPS1_R_MAIN] ? be16(r->region[CPS1_R_MAIN] + a) : 0xFFFF;
    if (a >= 0xFF0000) return be16(s->ram + (a & 0xFFFF));
    if (a >= 0x900000 && a < 0x930000) return be16(s->gfxram + (a - 0x900000));
    if (a == 0x800000) return players(s);
    if (a == 0x800018) return (uint16_t)(system_in(s) << 8 | 0xFF);
    if (a >= 0x80001A && a < 0x800020) return (uint16_t)(s->dip[(a - 0x80001A) >> 1] << 8 | 0xFF);
    if (a >= 0x800140 && a < 0x800180) return cpsb_read(s, a - 0x800140);
    if (s->rom->game->dial && ((a >= 0x800052 && a < 0x800056) || (a >= 0x80005A && a < 0x80005E))) {
        int p = a >= 0x80005A;  /* the uPD4701: 12 bits since the last reset, low byte then high */
        uint32_t c = (uint32_t)(s->dial[p] - s->dial_start[p]) & 0xFFF;
        return (uint16_t)(((a - (p ? 0x80005A : 0x800052)) & 2) ? c >> 8 : c & 0xFF);
    }
    return 0xFFFF;
}

static void wr(Cps1 *s, uint32_t a, uint16_t v, unsigned strobe) {
    a &= 0xFFFFFE;
    if (a >= 0xFF0000) put(s->ram + (a & 0xFFFF), v, strobe);
    else if (a >= 0x900000 && a < 0x930000) put(s->gfxram + (a - 0x900000), v, strobe);
    else if (a >= 0x800100 && a < 0x800140) {
        s->cpsa[(a - 0x800100) >> 1] = merge(s->cpsa[(a - 0x800100) >> 1], v, strobe);
        if (a == 0x80010A) cps1_palette_upload(s);
    }
    else if (a >= 0x800140 && a < 0x800180) cpsb_write(s, a - 0x800140, merge(s->cpsb[(a - 0x800140) >> 1], v, strobe));
    else if (a >= 0x800180 && a < 0x800188) s->sound_cmd = (uint8_t)v;   /* P3: the Z80 reads it */
    else if (a >= 0x800188 && a < 0x800190) s->sound_fade = (uint8_t)v;
    else if (s->rom->game->dial && (a == 0x800040 || a == 0x800048) && (strobe & 1))
        s->dial_start[a == 0x800048] = s->dial[a == 0x800048];  /* reset X / Y */
}

uint16_t m68k_read(M68k *c, uint32_t a, unsigned fc, unsigned strobe) { (void)fc; return rd(c->bus, a, strobe); }
void m68k_write(M68k *c, uint32_t a, uint16_t v, unsigned fc, unsigned strobe) { (void)fc; wr(c->bus, a, v, strobe); }
void m68k_idle(M68k *c, unsigned clocks) { (void)c, (void)clocks; }
void m68k_aborted(M68k *c, uint32_t a, unsigned fc, unsigned strobe, int write) { (void)c, (void)a, (void)fc, (void)strobe, (void)write; }
int m68k_iack(M68k *c, int level) { (void)level; c->ipl = 0; return -1; }  /* autovector; acknowledging clears it */
void m68k_reset_out(M68k *c) { (void)c; }

/* ---- the sound Z80 ---- */

static uint8_t zrd(Cps1 *s, uint16_t a) {
    const uint8_t *rom = s->rom->region[CPS1_R_SOUND];
    uint32_t size = s->rom->size[CPS1_R_SOUND], at = a < 0x8000 ? a : 0x8000u + s->bank * 0x4000u + (a - 0x8000u);
    if (a < 0xC000) return at < size ? rom[at] : 0xFF;
    if (a >= 0xD000 && a < 0xD800) return s->z80_ram[a - 0xD000];
    switch (a) {
    case 0xF001: return opm_status(&s->opm);
    case 0xF002: return oki_status(&s->oki);
    case 0xF008: return s->sound_cmd;
    case 0xF00A: return s->sound_fade;
    default: return 0xFF;
    }
}

uint8_t z80_fetch(Z80 *z, uint16_t pc) { return zrd(z->bus, pc); }
uint8_t z80_read(Z80 *z, uint16_t a) { return zrd(z->bus, a); }
void z80_write(Z80 *z, uint16_t a, uint8_t v) {
    Cps1 *s = z->bus;
    if (a >= 0xD000 && a < 0xD800) s->z80_ram[a - 0xD000] = v;
    else if (a == 0xF000 || a == 0xF001) opm_write(&s->opm, a & 1, v);
    else if (a == 0xF002) oki_write(&s->oki, v);
    else if (a == 0xF004) s->bank = v & 1;
    else if (a == 0xF006) s->oki.pin7 = v & 1;  /* the OKI's rate: 132 clocks a sample, or 165 */
}
uint8_t z80_in(Z80 *z, uint16_t port) { (void)z, (void)port; return 0xFF; }
void z80_out(Z80 *z, uint16_t port, uint8_t v) { (void)z, (void)port, (void)v; }
void z80_idle(Z80 *z, uint16_t a, unsigned n) { (void)z, (void)a, (void)n; }
uint8_t z80_irq_ack(Z80 *z) { (void)z; return 0xFF; }  /* IM 1: RST $38 */

static void sample(Cps1 *s) {
    s->oki_acc += 64ull * 1000000;  /* 64 Z80 T-states in OKI clocks (1 MHz) x 3,579,545 */
    uint64_t period = (s->oki.pin7 ? 132ull : 165ull) * CPS1_Z80_CLOCK;
    while (s->oki_acc >= period) s->oki_acc -= period, s->oki_out = oki_sample(&s->oki);
    /* MAME's CPS-1 mix: the YM2151's two sides x 0.35, the OKI x 0.30, full
     * scale 32,768 for the YM2151's 16 bits and 65,536 for the OKI's sum */
    int v = opm_sample(&s->opm) * 7 / 10 + s->oki_out * 15 / 100;
    if (s->snd_n < CPS1_SND_BUF) s->snd[s->snd_n++] = (int16_t)(v > 32767 ? 32767 : v < -32768 ? -32768 : v);
}

static void run_z80(Cps1 *s) {
    uint64_t end = s->lines * CPS1_Z80_CLOCK * 512 / 8000000;  /* 229.09 a line */
    while (s->z80.tstates < end) {
        if (!s->opm.irq || !z80_interrupt(&s->z80)) z80_step(&s->z80);
        while (s->z80.tstates >= s->snd_next) sample(s), s->snd_next += 64;
    }
}

int cps1_take_sound(Cps1 *s, int16_t *out, int max) {
    int n = s->snd_n < max ? s->snd_n : max;
    memcpy(out, s->snd, (size_t)n * sizeof *out);
    memmove(s->snd, s->snd + n, (size_t)(s->snd_n - n) * sizeof *out);
    s->snd_n -= n;
    return n;
}

void cps1_init(Cps1 *s, const Cps1Rom *r) {
    memset(s, 0, sizeof *s);
    s->rom = r;
    memcpy(s->dip, r->game->dip, sizeof s->dip);  /* the game's defaults */
    s->line_clocks = r->game->clock_mhz == 12 ? 768 : CPS1_LINE_CLOCKS;
    s->cpu.bus = s;
    m68k_reset(&s->cpu);
    s->z80.bus = s;
    z80_reset(&s->z80);
    opm_reset(&s->opm);
    oki_reset(&s->oki, r->region[CPS1_R_OKI], r->size[CPS1_R_OKI]);
    s->snd_next = 64;
}

void cps1_set_input(Cps1 *s, int player, uint16_t pad) {
    if (player >= 0 && player < 4) s->pad[player] = pad;
}

void cps1_frame(Cps1 *s) {
    s->frames++;
    if (s->rom->game->dial)  /* L / R turn the dial 20 steps a frame, as MAME's keys do */
        for (int p = 0; p < 2; p++) s->dial[p] += (s->pad[p] & PAD_R ? 20 : 0) - (s->pad[p] & PAD_L ? 20 : 0);
    for (s->line = 0; s->line < CPS1_LINES; s->line++) {
        if (s->line == CPS1_VBLANK_LINE) {
            cps1_render(s);
            s->cpu.ipl = 2;
        }
        s->line_end += s->line_clocks;
        while (s->cpu.cycles < s->line_end && !s->cpu.halted) m68k_step(&s->cpu);
        if (s->cpu.halted) s->cpu.cycles = s->line_end;
        s->lines++;
        run_z80(s);
    }
}
