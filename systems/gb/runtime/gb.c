#include "gb.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sm83_ops.h"    /* rd */
#include "input_log.h"  /* PAD_* */
#include "recomp_rt.h"

/* ---- timer (Pan Docs "Timer obscure behaviour") ---- */
static int timer_bit(uint16_t div, uint8_t tac) {
    static const uint16_t BIT[4] = {1 << 9, 1 << 3, 1 << 5, 1 << 7};  /* 4096, 262144, 65536, 16384 Hz */
    return (tac & 4) && (div & BIT[tac & 3]);
}
static void timer_inc(Gb *g) {
    if (++g->tima == 0) g->tima_reload = 1;  /* TIMA reads 0 for a cycle, then TMA */
}

/* WRAM: $C000-$CFFF bank 0, $D000-$DFFF the bank SVBK picks (0 = 1); $E000- echoes */
static unsigned wram_at(const Gb *g, uint16_t a) {
    unsigned o = a & 0x1FFF;
    return o < 0x1000 ? o : (g->svbk ? g->svbk : 1u) * 0x1000u + (o & 0xFFF);
}
static unsigned vram_at(const Gb *g, uint16_t a) { return g->vbk * 0x2000u + (a & 0x1FFF); }

/* A byte as the DMA units read it: no side effects; $E000-$FFFF reach WRAM. */
static uint8_t dma_peek(Gb *g, uint16_t a) {
    if (a < 0x8000 || (a >= 0xA000 && a < 0xC000)) return gb_cart_read(&g->cart, a);
    if (a < 0xA000) return g->vram[vram_at(g, a)];
    return g->wram[wram_at(g, a)];
}

static void tick(Gb *g);
/* A TAC write after its cycle's tick (d0: DIV before it, old: TAC before). Switching
 * the selected bit or disabling can make a falling edge; so does enabling a bit that
 * fell in this very cycle (mooneye rapid_toggle). */
static void timer_tac_write(Gb *g, uint8_t v, uint16_t d0, uint8_t old) {
    int before = timer_bit(g->div, old);
    int fell_now = !timer_bit(d0, old) && timer_bit(d0, v & 7);
    g->tac = v & 7;
    if ((before || fell_now) && !timer_bit(g->div, g->tac)) timer_inc(g);
}
/* HDMA: 16 bytes to VRAM; the CPU waits 8 M-cycles of normal speed (Pan Docs "VRAM DMA Transfers") */
static void hdma_block(Gb *g) {
    for (int i = 0; i < 16; i++) {
        uint8_t v = dma_peek(g, g->hdma_src++);
        g->vram[g->vbk * 0x2000u + (g->hdma_dst++ & 0x1FFF)] = v;
    }
    g->hdma_dst &= 0x1FFF;
    if (g->hdma_left-- == 0) g->hdma_left = 0x7F, g->hdma_on = 0;
    for (int i = 0; i < 8 << g->double_speed; i++) g->cpu.cycles++, tick(g);
}
static void hdma_poll(Gb *g) {  /* hblank began: a block, if the transfer still runs */
    if (!g->hdma_due) return;
    g->hdma_due = 0;
    if (g->hdma_on) hdma_block(g);
}

/* One M-cycle of everything but the CPU. In double speed the CPU, timer,
 * serial and OAM DMA run twice as fast; the PPU (2 dots), sound and the
 * cartridge clock (every other cycle) keep their pace. */
static void tick(Gb *g) {
    if (g->tima_reload == 2) g->tima_reload = 0;
    else if (g->tima_reload == 1) g->tima = g->tma, g->ifl |= INT_TIMER, g->tima_reload = 2;
    int before = timer_bit(g->div, g->tac);
    uint16_t old = g->div;
    g->div += 4;
    if (before && !timer_bit(g->div, g->tac)) timer_inc(g);
    if (old & ~g->div & (g->double_speed ? 0x2000 : 0x1000)) apu_frame_step(g);  /* DIV bit 4 (5) fell: 512 Hz */

    if (g->serial_left && !--g->serial_left) g->sb = 0xFF, g->sc &= 0x7F, g->ifl |= INT_SERIAL;

    if (g->dma_start && !--g->dma_start) g->dma_on = 1, g->dma_pos = 0, g->dma_src = g->dma_next;
    if (g->dma_on) {  /* 160 cycles that each move a byte; the bus is free after the last */
        if (g->dma_pos == 0xA0) g->dma_on = 0;
        else g->oam[g->dma_pos] = dma_peek(g, (uint16_t)(g->dma_src + g->dma_pos)), g->dma_pos++;
    }

    ppu_tick(g);
    if (g->double_speed && (g->half ^= 1)) return;
    apu_tick(g);
    gb_cart_tick(&g->cart);
}

/* ---- registers ---- */
static uint8_t io_read(Gb *g, uint16_t a) {
    switch (a) {
    case 0xFF00: {  /* buttons pressed read 0 in the selected group(s) */
        uint8_t low = 0x0F, p = g->pad;
        if (!(g->p1 & 0x10)) low &= (uint8_t)~((p >> 7 & 1) | (p >> 6 & 1) << 1 | (p >> 4 & 1) << 2 | (p >> 5 & 1) << 3);
        if (!(g->p1 & 0x20)) low &= (uint8_t)~(p & 0x0F);
        return (uint8_t)(0xC0 | g->p1 | low);
    }
    case 0xFF01: return g->sb;
    case 0xFF02: return g->sc | 0x7E;
    case 0xFF04: return (uint8_t)(g->div >> 8);
    case 0xFF05: return g->tima;
    case 0xFF06: return g->tma;
    case 0xFF07: return g->tac | 0xF8;
    case 0xFF0F: return g->ifl | 0xE0;
    case 0xFF40: return g->lcdc;
    case 0xFF41: return (uint8_t)(0x80 | g->stat | ((g->lcdc & 0x80 ? g->ly_seen == g->ly && g->ly == g->lyc : g->coin_hold) ? 4 : 0) | ppu_vmode(g));
    case 0xFF42: return g->scy;
    case 0xFF43: return g->scx;
    case 0xFF44: return g->ly;
    case 0xFF45: return g->lyc;
    case 0xFF46: return g->dma_reg;
    case 0xFF47: case 0xFF48: case 0xFF49: return g->io[a & 0x7F];
    case 0xFF4A: return g->wy;
    case 0xFF4B: return g->wx;
    }
    if (a >= 0xFF10 && a < 0xFF40) return apu_read(g, a);
    if (!g->cgb) return 0xFF;
    switch (a) {  /* CGB */
    case 0xFF4D: return g->compat ? 0xFF : (uint8_t)(0x7E | g->double_speed << 7 | g->key1);
    case 0xFF4F: return 0xFE | g->vbk;
    case 0xFF55: return (uint8_t)((g->hdma_on ? 0 : 0x80) | g->hdma_left);
    case 0xFF68: return g->bcps | 0x40;
    case 0xFF69: return ppu_vmode(g) == 3 ? 0xFF : g->bg_pal[g->bcps & 0x3F];  /* palette RAM: the PPU owns it in mode 3 */
    case 0xFF6A: return g->ocps | 0x40;
    case 0xFF6B: return ppu_vmode(g) == 3 ? 0xFF : g->obj_pal[g->ocps & 0x3F];
    case 0xFF6C: return 0xFE | g->opri;
    case 0xFF70: return g->compat ? 0xFF : 0xF8 | g->svbk;
    case 0xFF72: case 0xFF73: case 0xFF76: case 0xFF77: return 0x00;  /* undocumented; FF76/7 read the sound's output */
    case 0xFF75: return 0x8F;
    }
    return 0xFF;
}

static void io_write(Gb *g, uint16_t a, uint8_t v) {
    switch (a) {
    case 0xFF00: g->p1 = v & 0x30; return;
    case 0xFF01: g->sb = v; return;
    case 0xFF02:
        g->sc = v & 0x81;
        if ((v & 0x81) == 0x81) {  /* internal clock: send SB */
            if (g->serial_n < (int)sizeof g->serial_out - 1) g->serial_out[g->serial_n++] = (char)g->sb;
            g->serial_left = (512 - (g->div & 511)) / 4 + 7 * 128 - 1;  /* the first bit goes at DIV's next bit-8 fall; -1 as measured by boot_sclk_align */
        }
        return;
    case 0xFF04: {  /* reset the counter; a falling edge on the way counts */
        int before = timer_bit(g->div, g->tac);
        if (g->div & 0x1000) apu_frame_step(g);
        g->div = 0;
        if (before) timer_inc(g);
        return;
    }
    case 0xFF05:
        if (g->tima_reload == 1) g->tima_reload = 0;  /* cancels the reload and the interrupt */
        if (g->tima_reload != 2) g->tima = v;           /* in the reload cycle TMA wins */
        return;
    case 0xFF06:
        g->tma = v;
        if (g->tima_reload == 2) g->tima = v;
        return;
    case 0xFF07: return;  /* gb_write: the tick comes first */
    case 0xFF0F: g->ifl = v & 0x1F; return;
    case 0xFF40: ppu_lcdc_write(g, v); return;
    case 0xFF41: ppu_stat_write(g, v); return;
    case 0xFF42: g->scy = v; return;
    case 0xFF43: g->scx = v; return;
    case 0xFF44: return;  /* LY is read-only */
    case 0xFF45: g->lyc = v; ppu_stat_update(g); return;
    case 0xFF46: g->dma_reg = v, g->dma_next = (uint16_t)(v << 8), g->dma_start = 2; return;  /* mooneye oam_dma_start: the next cycle still free */
    case 0xFF4A: g->wy = v; return;
    case 0xFF4B: g->wx = v; return;
    }
    if (a >= 0xFF10 && a < 0xFF40) gb_apu_write(g, a, v);
    else if (a >= 0xFF47 && a <= 0xFF49) g->io[a & 0x7F] = v;
    if (!g->cgb) return;
    switch (a) {  /* CGB */
    case 0xFF4D: g->key1 = v & 1; return;
    case 0xFF4F: g->vbk = v & 1; return;
    case 0xFF51: g->hdma_src = (uint16_t)((g->hdma_src & 0xFF) | v << 8); return;
    case 0xFF52: g->hdma_src = (uint16_t)((g->hdma_src & 0xFF00) | (v & 0xF0)); return;
    case 0xFF53: g->hdma_dst = (uint16_t)((g->hdma_dst & 0xFF) | (v & 0x1F) << 8); return;
    case 0xFF54: g->hdma_dst = (uint16_t)((g->hdma_dst & 0x1F00) | (v & 0xF0)); return;
    case 0xFF55:
        if (g->hdma_on && !(v & 0x80)) { g->hdma_on = 0; return; }  /* stops an HBlank transfer */
        g->hdma_left = v & 0x7F;
        if (v & 0x80) { g->hdma_on = 1; return; }  /* a block at the start of each hblank */
        g->hdma_on = 1;  /* general purpose: every block now (the last one ends it) */
        while (g->hdma_on) hdma_block(g);
        return;
    case 0xFF68: g->bcps = v & 0xBF; return;
    case 0xFF6A: g->ocps = v & 0xBF; return;
    case 0xFF69: case 0xFF6B: {  /* a palette byte; the index steps on if asked */
        uint8_t *ps = a == 0xFF69 ? &g->bcps : &g->ocps;
        if (ppu_vmode(g) != 3) (a == 0xFF69 ? g->bg_pal : g->obj_pal)[*ps & 0x3F] = v;  /* lost in mode 3, the index still steps */
        if (*ps & 0x80) *ps = (uint8_t)(0x80 | ((*ps + 1) & 0x3F));
        return;
    }
    case 0xFF6C: g->opri = v & 1; return;
    case 0xFF70: g->svbk = v & 7; return;
    }
}

static uint8_t bus_read(Gb *g, uint16_t a) {
    if (a < 0x8000) return gb_cart_read(&g->cart, a);
    if (a < 0xA000) return g->vram[vram_at(g, a)];
    if (a < 0xC000) return gb_cart_read(&g->cart, a);
    if (a < 0xFE00) return g->wram[wram_at(g, a)];   /* $E000-$FDFF: echo of WRAM */
    if (a < 0xFEA0) return g->oam[a - 0xFE00];
    if (a < 0xFF00) return 0x00;                  /* unusable area (DMG reads 0) */
    if (a == 0xFFFF) return g->ie;
    if (a >= 0xFF80) return g->hram[a - 0xFF80];
    return io_read(g, a);
}

static void bus_write(Gb *g, uint16_t a, uint8_t v) {
    if (a < 0x8000) gb_cart_write(&g->cart, a, v);
    else if (a < 0xA000) g->vram[vram_at(g, a)] = v;
    else if (a < 0xC000) gb_cart_write(&g->cart, a, v);
    else if (a < 0xFE00) g->wram[wram_at(g, a)] = v;
    else if (a < 0xFEA0) g->oam[a - 0xFE00] = v;
    else if (a < 0xFF00) return;
    else if (a == 0xFFFF) g->ie = v;
    else if (a >= 0xFF80) g->hram[a - 0xFF80] = v;
    else io_write(g, a, v);
}

/* ---- the CPU's bus: each call is one M-cycle; the rest of the machine runs first ---- */
/* During OAM DMA the unit owns one bus: the video bus ($8000-$9FFF) or
 * the external one (cartridge, WRAM). A CPU access on that bus gets the
 * byte the DMA is moving (writes are lost); OAM reads $FF; the other bus,
 * I/O and HRAM work as usual. The CGB has WRAM on a bus of its own: a DMA
 * from WRAM leaves the cartridge free (a game's STAT handler in ROM runs
 * while it waits for one in HRAM) and the other way round. */
static int video_bus(uint16_t a) { return a >= 0x8000 && a < 0xA000; }
static int bus_of(const Gb *g, uint16_t a) { return video_bus(a) ? 1 : g->cgb && a >= 0xC000 ? 2 : 0; }
static int dma_conflict(const Gb *g, uint16_t a) {
    return g->dma_on && a < 0xFF00 && (a >= 0xFE00 || bus_of(g, a) == bus_of(g, g->dma_src));
}
/* The PPU owns VRAM in mode 3 and OAM in modes 2 and 3: the CPU reads $FF
 * and its writes are lost (Pan Docs "Accessing VRAM and OAM"). Reads are
 * blocked as the mode begins and free a dot late; writes see the mode a dot
 * late at both ends, and OAM is free for one cycle as mode 3 begins (mooneye
 * lcdon_timing, lcdon_write_timing). */
static int ppu_owns(const Gb *g, uint16_t a, int write) {
    int mode = ppu_mode(g), seen = ppu_vmode(g);
    int oam = a >= 0xFE00 && a < 0xFEA0;
    if (!video_bus(a) && !oam) return 0;
    if (write) return seen == 3 || (oam && seen == 2 && mode == 2);
    return mode == 3 || seen == 3 || (oam && mode == 2);
}
/* An HBlank HDMA block is moved in the first CPU cycle after hblank began
 * (the CPU waits), in recompiled code as in the interpreter. */
uint8_t gb_read(GbCpu *c, uint16_t a) {
    Gb *g = c->bus;
    tick(g);
    hdma_poll(g);
    if (dma_conflict(g, a)) return a >= 0xFE00 ? 0xFF : dma_peek(g, (uint16_t)(g->dma_src + g->dma_pos));
    if (ppu_owns(g, a, 0)) return 0xFF;
    return bus_read(g, a);
}
void gb_write(GbCpu *c, uint16_t a, uint8_t v) {
    Gb *g = c->bus;
    if (a == 0xFF07) {  /* TAC takes effect at the end of the cycle; see timer_tac_write */
        uint16_t d0 = g->div;
        uint8_t old = g->tac;
        tick(g);
        hdma_poll(g);
        timer_tac_write(g, v, d0, old);
        return;
    }
    tick(g);
    hdma_poll(g);
    if (!dma_conflict(g, a) && !ppu_owns(g, a, 1)) bus_write(g, a, v);
}
void gb_idle(GbCpu *c) {
    Gb *g = c->bus;
    tick(g);
    hdma_poll(g);
}

/* Interrupt entry asks after pushing PC's high byte: that push can change
 * IE (SP = $0000), and then no interrupt is taken (PC = 0). */
uint16_t gb_irq_ack(GbCpu *c) {
    Gb *g = c->bus;
    uint8_t p = g->ie & g->ifl & 0x1F;
    if (!p) return 0x0000;
    int bit = 0;
    while (!(p & 1 << bit)) bit++;
    g->ifl &= (uint8_t)~(1 << bit);
    return (uint16_t)(0x40 + 8 * bit);
}

/* A step: interrupt entry, a halted cycle, or code: a recompiled block when
 * there is one for this PC and bank, else one instruction interpreted. */
void gb_step(Gb *g) {
    GbCpu *c = &g->cpu;
    uint8_t pending = g->ie & g->ifl & 0x1F;
    if (c->halted && !pending) {
        /* halted, the CPU keeps reading the opcode at PC; an interrupt that
         * turns up in that cycle wakes it: with IME on the entry follows at
         * once, with IME off the next instruction is fetched in the next
         * cycle (mooneye halt_ime0_nointr_timing, halt_ime1_timing) */
        rd(c, c->pc);
        if (!(g->ie & g->ifl & 0x1F)) return;
        c->halted = 0;
        if (c->ime) gb_cpu_interrupt(c);
        return;
    }
    if (c->halted) c->halted = 0;  /* any enabled interrupt wakes HALT, IME or not */
    if (c->ime && pending) {
        gb_cpu_interrupt(c);
        return;
    }
    uint64_t before = c->cycles;
    GbRecompFn f = NULL;
    if (g->recomp_on && c->pc < 0x8000 && !c->halt_bug && !c->stopped && !c->jammed)
        f = gb_recomp_program->lookup(c->pc, gb_cart_bank(&g->cart, c->pc));
    if (f) {
        if (c->ei) c->ei = 0, c->ime = 1;  /* as gb_cpu_step: EI ends blocks, so only here */
        f(c);
        g->cycles_native += c->cycles - before;
    } else {
        if (g->misses && c->pc < 0x8000 && !c->stopped && !c->jammed)
            g->misses[gb_cart_bank(&g->cart, c->pc) * 0x8000 + c->pc] = 1;
        gb_cpu_step(c);
        g->cycles_interp += c->cycles - before;
    }
    /* HALT with IME off and an interrupt already pending does not halt; the
     * next opcode byte is read twice (the "HALT bug") */
    if (c->halted && !c->ime && (g->ie & g->ifl & 0x1F)) c->halted = 0, c->halt_bug = 1;
    /* CGB: STOP with KEY1 armed switches the speed and goes on past the byte
     * after it (2 bytes then; a game puts $E3 there). The CPU waits about 2050
     * M-cycles while the rest of the machine runs; DIV restarts. */
    if (c->stopped && g->cgb && g->key1) {
        for (int i = 0; i < 2050; i++) c->cycles++, tick(g);  /* in the old speed; DIV restarts at the end (age spsw-div) */
        g->double_speed ^= 1, g->half = 0, g->div = 0;
        g->key1 = 0, c->stopped = 0, c->pc++;
    }
}

void gb_run_frame(Gb *g) {
    g->frame_end += gb_frame_cycles(g);
    while (g->cpu.cycles < g->frame_end) gb_step(g);
}

void gb_set_pad(Gb *g, uint8_t pad) {
    if (pad & ~g->pad) g->ifl |= INT_JOYPAD, g->cpu.stopped = 0;  /* a new press */
    g->pad = pad;
    if (g->cart.mbc == MBC_7) {
        /* shortcut: one g from digital directions, use continuous input if a motion device is added. */
        g->cart.tilt_dx = (int8_t)(!!(pad & PAD_LEFT) - !!(pad & PAD_RIGHT));
        g->cart.tilt_dy = (int8_t)(!!(pad & PAD_UP) - !!(pad & PAD_DOWN));
    }
}

int gb_load(Gb *g, const uint8_t *rom, size_t size, char *err, size_t errlen) {
    return gb_load_model(g, rom, size, GB_MODEL_AUTO, err, errlen);
}

int gb_load_model(Gb *g, const uint8_t *rom, size_t size, int model, char *err, size_t errlen) {
    memset(g, 0, sizeof *g);
    if (gb_cart_load(&g->cart, rom, size, err, errlen) != 0) return -1;
    GbCpu *c = &g->cpu;
    c->bus = g;
    int color = model == GB_MODEL_CGB || model == GB_MODEL_CGB0 || model == GB_MODEL_AGB;
    g->cgb = (uint8_t)(color || (model == GB_MODEL_AUTO && (g->cart.rom[0x143] & 0x80)));
    g->compat = (uint8_t)(color && !(g->cart.rom[0x143] & 0x80));
    /* what the boot ROM of the model leaves (Pan Docs "Power Up Sequence"): the registers A F B C D E H L, and the
     * DIV counter (mooneye boot_div and boot_regs tests). DMG: F = $B0 with a correct header checksum, else H and C too.
     * div_compat: the counter when the Color boots a DMG game (mooneye's boot_div-A, -cgb0, -cgbABCDE are DMG games). A
     * Color game's DIV is unchecked (no test ROM is a Color game), so it stays what it was. */
    static const struct { uint8_t r[8]; uint16_t div, div_compat; } BOOT[] = {
        [GB_MODEL_DMG]  = {{0x01, 0xB0, 0x00, 0x13, 0x00, 0xD8, 0x01, 0x4D}, 0xABC8, 0},
        [GB_MODEL_MGB]  = {{0xFF, 0xB0, 0x00, 0x13, 0x00, 0xD8, 0x01, 0x4D}, 0xABC8, 0},
        [GB_MODEL_DMG0] = {{0x01, 0x00, 0xFF, 0x13, 0x00, 0xC1, 0x84, 0x03}, 0x182C, 0},
        [GB_MODEL_SGB]  = {{0x01, 0x00, 0x00, 0x14, 0x00, 0x00, 0xC0, 0x60}, 0xD85C, 0},
        [GB_MODEL_SGB2] = {{0xFF, 0x00, 0x00, 0x14, 0x00, 0x00, 0xC0, 0x60}, 0xD84C, 0},
        [GB_MODEL_CGB]  = {{0x11, 0x80, 0x00, 0x00, 0xFF, 0x56, 0x00, 0x0D}, 0x1EA0, 0x2674},
        [GB_MODEL_CGB0] = {{0x11, 0x80, 0x00, 0x00, 0xFF, 0x56, 0x00, 0x0D}, 0x1EA0, 0x2880},
        [GB_MODEL_AGB]  = {{0x11, 0x00, 0x01, 0x00, 0xFF, 0x56, 0x00, 0x0D}, 0x1EA0, 0x2678},
    };
    int m = model == GB_MODEL_AUTO ? (g->cgb ? GB_MODEL_CGB : GB_MODEL_DMG) : model;
    c->a = BOOT[m].r[0], c->f = BOOT[m].r[1], c->b = BOOT[m].r[2], c->c = BOOT[m].r[3];
    c->d = BOOT[m].r[4], c->e = BOOT[m].r[5], c->h = BOOT[m].r[6], c->l = BOOT[m].r[7];
    c->sp = 0xFFFE, c->pc = 0x0100;
    g->div = g->compat ? BOOT[m].div_compat : BOOT[m].div;
    if (g->cgb) memset(g->bg_pal, 0xFF, sizeof g->bg_pal);  /* the boot ROM leaves the background white */
    if (g->compat) {  /* the boot ROM picked the palettes; B = title checksum (AGB: + 1), DE = $0008, HL = $007C */
        memset(g->obj_pal, 0xFF, sizeof g->obj_pal);
        uint8_t sum = gb_compat_palettes(g);
        c->b = (uint8_t)(sum + (m == GB_MODEL_AGB)), c->d = 0x00, c->e = 0x08, c->h = 0x00, c->l = 0x7C;
        g->opri = 1, g->p1 = 0x30, g->bcps = 0x88, g->ocps = 0x90;  /* the boot ROM wrote 8 and 16 palette bytes */
    }
    g->hdma_left = 0x7F;
    g->tac = 0x00;
    g->ifl = INT_VBLANK;
    g->lcdc = 0x91;
    g->mode = 2;
    g->dma_reg = 0xFF;
    apu_boot(g);
    g->recomp_on = gb_recomp_program && gb_recomp_program->rom_hash == gb_rom_hash(g);
    g->io[0x47] = 0xFC, g->io[0x48] = 0xFF, g->io[0x49] = 0xFF;
    /* DMG0 starts in vblank (LY $91); mooneye boot_hwio-dmg0 passes for dots 84-252 of that line, 168 is a pick */
    if (m == GB_MODEL_DMG0) g->ly = 145, g->dot = 168, g->mode = 1;
    if (m == GB_MODEL_SGB || m == GB_MODEL_SGB2) g->p1 = 0x30, g->apu.on[0] = 0;  /* the SGB's boot ends on a joypad write, with no boot sound */
    return 0;
}

void gb_free(Gb *g) { gb_cart_free(&g->cart); }

/* ---- save states: a header, then the Gb struct as it is in memory (the
 * same build reads it back; a field-wise format when states must outlive
 * program updates) ---- */
enum { GB_STATE_VERSION = 2 };
typedef struct { char magic[4]; uint32_t version, size, rom_hash; } GbStateHeader;

uint32_t gb_rom_hash(const Gb *g) {  /* FNV-1a */
    uint32_t h = 2166136261u;
    for (uint32_t i = 0; i < g->cart.rom_size; i++) h = (h ^ g->cart.rom[i]) * 16777619u;
    return h;
}

int gb_state_save(const Gb *g, const char *path) {
    GbStateHeader h = {{'G', 'B', 'S', 'S'}, GB_STATE_VERSION, (uint32_t)sizeof *g, gb_rom_hash(g)};
    FILE *f = fopen(path, "wb");
    if (!f) return -1;
    int ok = fwrite(&h, sizeof h, 1, f) == 1 && fwrite(g, sizeof *g, 1, f) == 1;
    return fclose(f) == 0 && ok ? 0 : -1;
}

int gb_state_load(Gb *g, const char *path, char *err, size_t errlen) {
    FILE *f = fopen(path, "rb");
    if (!f) return snprintf(err, errlen, "cannot open"), -1;
    GbStateHeader h;
    Gb *s = malloc(sizeof *s);
    int ok = s && fread(&h, sizeof h, 1, f) == 1 && !memcmp(h.magic, "GBSS", 4);
    if (!ok) snprintf(err, errlen, "not a save state");
    else if (h.version != GB_STATE_VERSION || h.size != sizeof *g)
        ok = 0, snprintf(err, errlen, "saved by a different version of the program");
    else if (h.rom_hash != gb_rom_hash(g))
        ok = 0, snprintf(err, errlen, "saved with a different game");
    else if (fread(s, sizeof *s, 1, f) != 1)
        ok = 0, snprintf(err, errlen, "file is truncated");
    fclose(f);
    if (ok) {  /* everything but what belongs to this process: the ROM copy, the CPU's link to its bus,
                * this program's recompiled code and the misses being recorded */
        s->cart.rom = g->cart.rom;
        s->recomp_on = g->recomp_on, s->misses = g->misses;
        *g = *s;
        g->cpu.bus = g;
    }
    free(s);
    return ok ? 0 : -1;
}

void gb_misses_write(const Gb *g, FILE *f) {
    for (size_t i = 0; g->misses && i < gb_miss_slots(g); i++)
        if (g->misses[i]) fprintf(f, "MISS $%04X bank %u\n", (unsigned)(i & 0x7FFF), (unsigned)(i / 0x8000));
}

long gb_misses_merge(Gb *g, const char *path) {
    size_t slots = gb_miss_slots(g);
    uint8_t *listed = calloc(slots, 1);
    FILE *f = fopen(path, "r");
    char line[128];
    unsigned pc, bank;
    while (listed && f && fgets(line, sizeof line, f))
        if (sscanf(line, "MISS $%x bank %u", &pc, &bank) == 2 && pc < 0x8000 && (size_t)bank * 0x8000 + pc < slots)
            listed[bank * 0x8000 + pc] = 1;
    if (f) fclose(f);
    long fresh = 0;
    for (size_t i = 0; listed && i < slots; i++) {
        fresh += g->misses[i] && !listed[i];
        g->misses[i] |= listed[i];
    }
    free(listed);
    return fresh;
}
