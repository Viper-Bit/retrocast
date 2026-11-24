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
#include "recomp_rt.h"

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
    if (s->rom->game->extra == CPS1_EXTRA_P4)  /* Slam Masters: players 3 and 4's button 3 */
        v |= (uint16_t)((s->pad[2] & PAD_X ? 0x0080 : 0) | (s->pad[3] & PAD_X ? 0x8000 : 0));
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

/* Player 3 or 4's port (MAME's IN2, IN3): directions, buttons 1-2, coin,
 * start; active low. */
static uint8_t extra_player(uint16_t pad) {
    uint8_t v = 0;
    if (pad & PAD_RIGHT) v |= 0x01;
    if (pad & PAD_LEFT) v |= 0x02;
    if (pad & PAD_DOWN) v |= 0x04;
    if (pad & PAD_UP) v |= 0x08;
    if (pad & PAD_B) v |= 0x10;
    if (pad & PAD_A) v |= 0x20;
    if (pad & PAD_SELECT) v |= 0x40;
    if (pad & PAD_START) v |= 0x80;
    return (uint8_t)~v;
}

/* MAME's IN2: Street Fighter II's kicks (P1 bits 0-2, P2 bits 4-6), or
 * player 3; active low. */
static uint16_t extra_in(const Cps1 *s) {
    uint8_t v = 0;
    if (s->rom->game->extra == CPS1_EXTRA_KICKS) {
        for (int p = 0; p < 2; p++) {
            uint16_t pad = s->pad[p];
            uint8_t b = (uint8_t)((pad & PAD_Y ? 1 : 0) | (pad & PAD_L ? 2 : 0) | (pad & PAD_R ? 4 : 0));
            v |= (uint8_t)(b << (p * 4));
        }
        return (uint8_t)~v;
    }
    return s->rom->game->extra >= CPS1_EXTRA_P3 ? extra_player(s->pad[2]) : 0xFF;
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

/* The EEPROM's clock: microseconds of 68000 time. */
static uint64_t eeprom_now(const Cps1 *s) { return s->cpu.cycles / s->rom->game->clock_mhz; }

/* The Q-Sound board's own 68000 addresses (MAME's qsound_main_map). */
static uint16_t qsound_rd(const Cps1 *s, uint32_t a) {
    if (a < 0xF10000)  /* Slam Masters' protection: the Z80 ROM's bytes */
        return s->rom->z80_raw ? (uint16_t)(0xFF00 | s->rom->z80_raw[(a - 0xF00000) >> 1]) : 0;
    if (a >= 0xF18000 && a < 0xF1A000) return (uint16_t)(0xFF00 | s->qram[0][(a - 0xF18000) >> 1]);
    if (a >= 0xF1E000 && a < 0xF20000) return (uint16_t)(0xFF00 | s->qram[1][(a - 0xF1E000) >> 1]);
    if (a == 0xF1C000) return s->rom->game->extra >= CPS1_EXTRA_P3 ? extra_player(s->pad[2]) : 0xFF;
    if (a == 0xF1C002) return s->rom->game->extra == CPS1_EXTRA_P4 ? extra_player(s->pad[3]) : 0xFF;
    if (a == 0xF1C006) return (uint16_t)eeprom_do(&s->eeprom, eeprom_now(s));
    return 0xFFFF;
}

static void qsound_wr(Cps1 *s, uint32_t a, uint16_t v, unsigned strobe) {
    if (!(strobe & 1)) return;  /* all on the low byte */
    if (a < 0xF1A000) s->qram[0][(a - 0xF18000) >> 1] = (uint8_t)v;
    else if (a >= 0xF1E000) s->qram[1][(a - 0xF1E000) >> 1] = (uint8_t)v;
    else if (a == 0xF1C006) eeprom_write_lines(&s->eeprom, v >> 7 & 1, v >> 6 & 1, v & 1, eeprom_now(s));  /* CS, CLK, DI */
}

/* A bootleg's own reads (MAME's init functions), or -1. */
static int32_t init_rd(const Cps1 *s, uint32_t a) {
    uint8_t init = s->rom->game->init;
    switch (init) {
    case CPS1_INIT_SF2RB:
    case CPS1_INIT_SF2RB2:
        if (a >= 0x200000 && a < 0x300000) return a == 0x201200 ? (init == CPS1_INIT_SF2RB ? 0x0002 : 0) : a == 0x281200 ? 0x0040 : 0;
        break;
    case CPS1_INIT_SF2DONGB:  /* a programmed chip in the fourth ROM's socket */
        if (a >= 0x180000 && a < 0x200000) return a == 0x180000 || a == 0x1F7040 ? 0x0210 : 0;
        break;
    case CPS1_INIT_SF2CEBLP:
        if (a == 0x57A2B0) return s->prot == 0 ? 0x1992 : s->prot == 4 ? 0x0408 : 0xFFFF;
        break;
    case CPS1_INIT_PANG3B4:
        if (a == 0x57A2B0) return (s->prot & 0xFF) <= 7 ? (s->prot & 0xFF) + 0x20 : s->prot == 0x17 ? 0x7321 : 0xFFFF;
        if (a == 0x80017A) return 0xFFFF;  /* Pang! 3's EEPROM port, filtered out on this board */
        break;
    case CPS1_INIT_DINOHUNT:
        if (a >= 0xF18000 && a < 0xF1A000) return 0x00FF;
        if (a == 0xFC0000) return extra_player(s->pad[2]);
        break;
    case CPS1_INIT_SF2HACK:
    case CPS1_INIT_SF2RK:  /* the system inputs and DIP switches on both bytes */
        if (a >= 0x800018 && a < 0x800020) {
            uint8_t in = a == 0x800018 ? system_in(s) : s->dip[(a - 0x80001A) >> 1];
            return in << 8 | in;
        }
        break;
    case CPS1_INIT_SF2THNDR:
        if (a >= 0x8001C0 && a < 0x800200) return cpsb_read(s, a - 0x8001C0);
        break;
    default: break;
    }
    return -1;
}

static uint16_t rd(Cps1 *s, uint32_t a, unsigned strobe) {
    (void)strobe;
    a &= 0xFFFFFE;
    const Cps1Rom *r = s->rom;
    int32_t own = r->game->init >= CPS1_INIT_SF2HACK ? init_rd(s, a) : -1;
    if (own >= 0) return (uint16_t)own;
    if (a < 0x400000) return a + 1 < r->size[CPS1_R_MAIN] ? be16(r->region[CPS1_R_MAIN] + a) : 0xFFFF;
    if (a >= 0xFF0000) return be16(s->ram + (a & 0xFFFF));
    if (a >= 0x900000 && a < 0x930000) return be16(s->gfxram + (a - 0x900000));
    if (a >= 0xF00000 && s->rom->game->group == CPS1_QSOUND) return qsound_rd(s, a);
    if (a == 0x800000) return players(s);
    if (a == 0x800018) return (uint16_t)(system_in(s) << 8 | 0xFF);
    if (a >= 0x80001A && a < 0x800020) return (uint16_t)(s->dip[(a - 0x80001A) >> 1] << 8 | 0xFF);
    if (a == 0x80017A && (s->rom->game->init == CPS1_INIT_PANG3 || s->rom->game->init == CPS1_INIT_PANG3B))
        return (uint16_t)eeprom_do(&s->eeprom, eeprom_now(s));  /* Pang! 3: the EEPROM in the CPS-B's range */
    uint32_t cpsb = s->rom->game->cpsb_high ? 0x8001C0 : 0x800140;  /* revision E of Street Fighter II: higher */
    if (a >= cpsb && a < cpsb + 0x40) return cpsb_read(s, a - cpsb);
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
    else if (a == 0x80017A && (s->rom->game->init == CPS1_INIT_PANG3 || s->rom->game->init == CPS1_INIT_PANG3B)) {
        if (strobe & 1) eeprom_write_lines(&s->eeprom, v >> 7 & 1, v >> 6 & 1, v & 1, eeprom_now(s));  /* CS, CLK, DI */
    }
    else if ((s->rom->game->init == CPS1_INIT_SF2CEBLP || s->rom->game->init == CPS1_INIT_PANG3B4) && (a == 0x5762B0 || a == 0x80017A)) {
        if (a == 0x5762B0) s->prot = v;  /* the whole word, as MAME */
    }
    else if (s->rom->game->init == CPS1_INIT_SF2THNDR && a >= 0x8001C0 && a < 0x800200)
        cpsb_write(s, a - 0x8001C0, merge(s->cpsb[(a - 0x8001C0) >> 1], v, strobe));
    else if (a >= (s->rom->game->cpsb_high ? 0x8001C0u : 0x800140u) && a < (s->rom->game->cpsb_high ? 0x800200u : 0x800180u)) {
        uint32_t off = a - (s->rom->game->cpsb_high ? 0x8001C0u : 0x800140u);
        cpsb_write(s, off, merge(s->cpsb[off >> 1], v, strobe));
    }
    else if (a >= 0x800180 && a < 0x800188) s->sound_cmd = (uint8_t)v;   /* P3: the Z80 reads it */
    else if (a >= 0x800188 && a < 0x800190) s->sound_fade = (uint8_t)v;
    else if (a >= 0xF18000 && a < 0xF20000 && s->rom->game->group == CPS1_QSOUND) qsound_wr(s, a, v, strobe);
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

/* The Q-Sound Z80 (MAME's qsound_sub_map): $0000-$7FFF ROM (its opcodes
 * Kabuki-decoded apart from its data), $8000-$BFFF a 16 KB bank ($D003),
 * $C000-$CFFF and $F000-$FFFF RAM shared with the 68000, $D000-$D002 the
 * chip's data and register, $D007 its ready flag. */
static uint8_t qzrd(const Cps1 *s, uint16_t a) {
    const uint8_t *rom = s->rom->region[CPS1_R_SOUND];
    uint32_t size = s->rom->size[CPS1_R_SOUND], at = a < 0x8000 ? a : 0x8000u + s->qbank * 0x4000u + (a - 0x8000u);
    if (a < 0xC000) return at < size ? rom[at] : 0xFF;
    if (a < 0xD000) return s->qram[0][a - 0xC000];
    if (a >= 0xF000) return s->qram[1][a - 0xF000];
    return a == 0xD007 ? qsound_ready(&s->qs) : 0xFF;
}

static void qzwr(Cps1 *s, uint16_t a, uint8_t v) {
    if (a >= 0xC000 && a < 0xD000) s->qram[0][a - 0xC000] = v;
    else if (a >= 0xF000) s->qram[1][a - 0xF000] = v;
    else if (a >= 0xD000 && a <= 0xD002) qsound_write(&s->qs, a - 0xD000, v);
    else if (a == 0xD003)  /* a bank past the ROM is bank 0, as MAME */
        s->qbank = (uint8_t)(0x8000u + (v & 15u) * 0x4000u >= s->rom->size[CPS1_R_SOUND] ? 0 : v & 15);
}

uint8_t z80_fetch(Z80 *z, uint16_t pc) {
    const Cps1 *s = z->bus;
    if (s->rom->game->group == CPS1_QSOUND) return pc < 0x8000 && s->rom->z80_op ? s->rom->z80_op[pc] : qzrd(s, pc);
    return zrd(z->bus, pc);
}
uint8_t z80_read(Z80 *z, uint16_t a) {
    const Cps1 *s = z->bus;
    return s->rom->game->group == CPS1_QSOUND ? qzrd(s, a) : zrd(z->bus, a);
}
void z80_write(Z80 *z, uint16_t a, uint8_t v) {
    Cps1 *s = z->bus;
    if (s->rom->game->group == CPS1_QSOUND) {
        qzwr(s, a, v);
        return;
    }
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

/* A Q-Sound sample in 1/15 Z80 T-states: 2,496 clocks at 60 MHz are 332.8 T-states at 8 MHz. */
#define QSOUND_STEP15 (QSOUND_CLOCKS_PER_SAMPLE * 2)

static void qsample(Cps1 *s) {
    int16_t o[2];
    qsound_sample(&s->qs, o);
    if (s->snd_n + 2 <= CPS1_SND_BUF) s->snd[s->snd_n++] = o[0], s->snd[s->snd_n++] = o[1];
}

/* shortcut: the chip's samples are made after each Z80 instruction, so a
 * register write or ready read lands up to one instruction later in the
 * sample stream than in MAME (which brings the stream up to the access). */
static void run_qsound_z80(Cps1 *s) {
    uint64_t end = s->lines * 512;  /* 8 MHz: 512 T-states a line */
    while (s->z80.tstates < end) {
        if (s->z80.tstates >= s->qirq_next) s->qirq = 1, s->qirq_next += CPS1_QSOUND_IRQ;
        if (s->qirq && z80_interrupt(&s->z80)) s->qirq = 0;  /* held until taken, as MAME's HOLD_LINE */
        else z80_step(&s->z80);
        while (s->z80.tstates * 15 >= s->snd_next) qsample(s), s->snd_next += QSOUND_STEP15;
    }
}

static void run_z80(Cps1 *s) {
    if (s->rom->game->group == CPS1_QSOUND) {
        run_qsound_z80(s);
        return;
    }
    uint64_t end = s->lines * CPS1_Z80_CLOCK * 512 / 8000000;  /* 229.09 a line */
    while (s->z80.tstates < end) {
        if (!s->opm.irq || !z80_interrupt(&s->z80)) z80_step(&s->z80);
        while (s->z80.tstates >= s->snd_next) sample(s), s->snd_next += 64;
    }
}

int cps1_take_sound(Cps1 *s, int16_t *out, int max) {
    int n = s->snd_n < max ? s->snd_n : max;
    n -= n % cps1_channels(s->rom->game);  /* whole left / right pairs */
    memcpy(out, s->snd, (size_t)n * sizeof *out);
    memmove(s->snd, s->snd + n, (size_t)(s->snd_n - n) * sizeof *out);
    s->snd_n -= n;
    return n;
}

uint32_t cps1_code_hash(const Cps1Rom *r) {
    uint32_t h = 2166136261u;  /* FNV-1a, as the recompiler's m68k_recomp_hash */
    for (uint32_t i = 0; i < r->size[CPS1_R_MAIN]; i++) h = (h ^ r->region[CPS1_R_MAIN][i]) * 16777619u;
    return h;
}

void cps1_init(Cps1 *s, const Cps1Rom *r) { cps1_init_with(s, r, cps1_recomp_program); }

void cps1_init_with(Cps1 *s, const Cps1Rom *r, const Cps1RecompProgram *p) {
    memset(s, 0, sizeof *s);
    s->rom = r;
    s->recomp = p;
    s->recomp_on = p && p->rom_hash == cps1_code_hash(r);
    memcpy(s->dip, r->game->dip, sizeof s->dip);  /* the game's defaults */
    s->line_clocks = r->game->clock_mhz == 12 ? 768 : CPS1_LINE_CLOCKS;
    s->cpu.bus = s;
    m68k_reset(&s->cpu);
    s->z80.bus = s;
    z80_reset(&s->z80);
    opm_reset(&s->opm);
    oki_reset(&s->oki, r->region[CPS1_R_OKI], r->size[CPS1_R_OKI]);
    s->snd_next = 64;
    if (cps1_has_eeprom(r->game)) eeprom_init(&s->eeprom, r->game->group == CPS1_QSOUND);  /* 128 bytes, or Pang! 3's 64 words */
    if (r->game->group == CPS1_QSOUND) {
        qsound_init(&s->qs, r->dsp, r->region[CPS1_R_QSOUND], r->size[CPS1_R_QSOUND]);
        s->snd_next = QSOUND_STEP15, s->qirq_next = CPS1_QSOUND_IRQ;
    }
}

void cps1_set_input(Cps1 *s, int player, uint16_t pad) {
    if (player >= 0 && player < 4) s->pad[player] = pad;
}

/* One step of the 68000: a recompiled block when one holds the queued
 * instruction and the interpreter would run it as a plain instruction,
 * else one interpreted step. */
static void cpu_step(Cps1 *s) {
    M68k *c = &s->cpu;
    uint32_t at = (c->pc - 4) & 0xFFFFFF;
    uint64_t t0 = c->cycles;
    Cps1RecompFn f = NULL;
    if (s->recomp_on && !c->halted && !c->stopped && !c->trace && !c->ipl && !c->ipl_seen) f = s->recomp->lookup(at);
    if (f) {
        if (!setjmp(c->abort)) f(c);  /* an address error ends the block's instruction as the interpreter's */
        s->cycles_native += c->cycles - t0;
        return;
    }
    if (s->misses && at < s->rom->size[CPS1_R_MAIN]) s->misses[at >> 1] = 1;
    m68k_step(c);
    s->cycles_interp += c->cycles - t0;
}

void cps1_line(Cps1 *s) {
    if (s->line >= CPS1_LINES) s->line = 0;
    if (s->line == 0) {
        s->frames++;
        if (s->rom->game->dial)  /* L / R turn the dial 20 steps a frame, as MAME's keys do */
            for (int p = 0; p < 2; p++) s->dial[p] += (s->pad[p] & PAD_R ? 20 : 0) - (s->pad[p] & PAD_L ? 20 : 0);
    }
    if (s->line == CPS1_VBLANK_LINE) {
        cps1_render(s);
        s->cpu.ipl = 2;
    }
    s->line_end += s->line_clocks;
    while (s->cpu.cycles < s->line_end && !s->cpu.halted) cpu_step(s);
    if (s->cpu.halted) s->cpu.cycles = s->line_end;
    s->lines++;
    run_z80(s);
    s->line++;
}

void cps1_frame(Cps1 *s) {
    do cps1_line(s);
    while (s->line < CPS1_LINES);
}
