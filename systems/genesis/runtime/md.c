/* The Genesis / Mega Drive machine: memory maps, I/O, Z80 control,
 * cartridge, TMSS and the timeline (md.h; systems/genesis/docs/roadmap.md D1). */
#include "md.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input_log.h"  /* PAD_* */
#include "recomp_rt.h"

enum { Z80_INT_CLOCKS = 2573 };  /* the Z80's INT pulse: BlastEm's measured 171.5 Z80 clocks (from memory) */
enum { TH_TIMEOUT = 80540 }; /* 6-button pad: ~1.5 ms of master clocks without a TH rise resets its count */

/* shortcut: open bus reads give the queued opcode word, not the last word on the bus; exact once a game needs it */
static uint16_t open_bus(const Md *m) { return m->cpu.irc; }  /* the bus last held the prefetched word (Time Killers' $A11100 test) */

static int z80_has_bus(const Md *m) { return m->z80_run && !m->z80_busreq; }

/* ---- the VDP's ports (vdp.c), behind TMSS ---- */
static int vdp_ok(Md *m) {  /* TMSS: a locked VDP hangs the 68000 */
    if ((m->io[0] & 0x0F) && memcmp(m->tmss, "SEGA", 4)) {
        m->tmss_locked = m->cpu.halted = 1;
        return 0;
    }
    return 1;
}
static uint16_t vdp_read(Md *m, uint32_t a) {
    if ((a & 0x1F) >= 0x10 || !vdp_ok(m)) return open_bus(m);
    return vdp_port_read(m, a);
}
static void vdp_write(Md *m, uint32_t a, uint16_t v, uint64_t now) {
    if ((a & 0x18) == 0x10) { psg_write(m, now, (uint8_t)v); return; }  /* the PSG, $11-$17 */
    if ((a & 0x1F) >= 0x10) return;
    if (!vdp_ok(m)) return;
    if (m->vdp_first_frame < 0) m->vdp_first_frame = (int32_t)m->frame_count;
    m->vdp_writes++;
    vdp_port_write(m, a, v);
}
/* the VDP answers at $C00000-$C0001F and its mirrors up to $DFFFFF */
static int vdp_at(uint32_t a) { return (a & 0xE700E0) == 0xC00000; }

/* ---- pads ($A10003/5; GPGX's 3- and 6-button protocol) ---- */
static int th_of(const Md *m, int p) { return m->io[4 + p] & 0x40 ? m->io[1 + p] & 0x40 : 0x40; }

static uint8_t pad_pins(Md *m, int p) {
    unsigned b = m->pad[p];
#define K(bit, button) ((b & (button)) ? (bit) : 0u)
    unsigned ud = K(1, PAD_UP) | K(2, PAD_DOWN), lr = K(4, PAD_LEFT) | K(8, PAD_RIGHT);
    /* the pad's B and C are south and east, A west; X, Y, Z: L, north, R; Mode: Select */
    unsigned bc = K(0x10, PAD_B) | K(0x20, PAD_A), sa = K(0x10, PAD_Y) | K(0x20, PAD_START);
    unsigned xyz = K(1, PAD_R) | K(2, PAD_X) | K(4, PAD_L) | K(8, PAD_SELECT);
#undef K
    int th = th_of(m, p) != 0;
    if (m->pad6[p] && md_now(m) - m->th_time[p] > TH_TIMEOUT) m->th_count[p] = 0;
    unsigned step = (m->pad6[p] ? m->th_count[p] : 0u) | (unsigned)th, down;
    switch (step) {
    case 7: down = bc | xyz; break;      /* TH 1 after three rises: C B Mode X Y Z */
    case 6: down = sa; break;            /* TH 0: Start A, the low bits read 1 */
    case 4: down = sa | 0x0F; break;     /* TH 0: Start A 0 0 0 0, a 6-button pad's mark */
    default: down = th ? bc | lr | ud : sa | 0x0C | ud;  /* C B R L D U / Start A 0 0 D U */
    }
    return (uint8_t)((th ? 0x40 : 0) | (~down & 0x3F));
}

static uint8_t io_read(Md *m, int r) {
    if (r < 1 || r > 3) return m->io[r];
    uint8_t ctl = m->io[3 + r], pins = r == 3 ? 0x7F : pad_pins(m, r - 1);
    return (uint8_t)((m->io[r] & (0x80 | ctl)) | (pins & ~ctl & 0x7F));
}
static void io_write(Md *m, int r, uint8_t v) {
    if (r == 0) return;  /* the version register */
    int p = r <= 3 ? r - 1 : r - 4;
    int was = p < 2 ? th_of(m, p) : 0;
    m->io[r] = v;
    if (p < 2 && !was && th_of(m, p) && m->pad6[p]) {
        if (md_now(m) - m->th_time[p] > TH_TIMEOUT) m->th_count[p] = 0;
        m->th_count[p] = (uint8_t)((m->th_count[p] + 2) & 7);
        m->th_time[p] = md_now(m);
    }
}

/* ---- the cartridge ---- */
static int sram_on(const Md *m, uint32_t a) {
    return m->sram && a - m->sram_start < m->sram_size && (m->rom_size <= m->sram_start || (m->sram_ctl & 1));
}
static uint32_t rom_offset(const Md *m, uint32_t a) {
    if (m->rom_size <= 0x400000) return a;
    return (uint32_t)m->ssf2[a >> 19] << 19 | (a & 0x7FFFF);  /* SSF2's mapper: 512 KB banks */
}

/* ---- the Z80's space ($0000-$7FFF: RAM, YM2612, bank, VDP; the 68000 sees it at $A00000) ---- */
static uint16_t rd(Md *m, uint32_t a, unsigned strobe);
static void wr(Md *m, uint32_t a, uint16_t v, unsigned strobe);

/* now: the master clock of the access (the Z80's or the 68000's) */
static uint8_t zbus_read(Md *m, uint16_t a, uint64_t now) {
    if (a < 0x4000) return m->zram[a & 0x1FFF];
    if (a < 0x6000) return ym_read(m, now);
    if (a >= 0x7F00 && a < 0x7F20) return (uint8_t)(vdp_read(m, 0xC00000 | (a & 0x1F)) >> (a & 1 ? 0 : 8));
    return 0xFF;
}
static void zbus_write(Md *m, uint16_t a, uint8_t v, uint64_t now) {
    if (a < 0x4000) m->zram[a & 0x1FFF] = v;
    else if (a < 0x6000) ym_write(m, now, a & 3, v);
    else if (a < 0x6100) m->z80_bank = (uint16_t)((m->z80_bank >> 1 | (v & 1) << 8) & 0x1FF);
    else if (a >= 0x7F00 && a < 0x7F20) vdp_write(m, 0xC00000 | (a & 0x1F), (uint16_t)(v << 8 | v), now);
}
/* The $8000 window: a byte of the 68000's space at the bank. */
static uint32_t window(const Md *m, uint16_t a) { return (uint32_t)m->z80_bank << 15 | (a & 0x7FFF); }
/* The Z80's clock during its instruction. */
static uint64_t z80_now(const Md *m) { return m->z80_clock + (m->z80.tstates - m->z80_t0) * 15; }
/* An access through the window waits for the 68000's bus: 3 T-states (Genesis Plus GX's figure,
 * from memory; it sets the pitch of DAC samples read from ROM). shortcut: the 68000 loses no time */
static uint8_t zread(Md *m, uint16_t a) {
    if (a < 0x8000) return zbus_read(m, a, z80_now(m));
    m->z80.tstates += 3;
    uint32_t t = window(m, a);
    if (t >= 0xA00000 && t < 0xA10000) return 0xFF;  /* its own space through the 68000: hangs on the console */
    uint16_t v = rd(m, t, t & 1 ? 1 : 2);
    return (uint8_t)(t & 1 ? v : v >> 8);
}
static void zwrite(Md *m, uint16_t a, uint8_t v) {
    if (a < 0x8000) { zbus_write(m, a, v, z80_now(m)); return; }
    m->z80.tstates += 3;
    uint32_t t = window(m, a);
    if (t < 0xA00000 || t >= 0xA10000) wr(m, t, (uint16_t)(v << 8 | v), t & 1 ? 1 : 2);
}

uint8_t z80_fetch(Z80 *z, uint16_t pc) { return zread(z->bus, pc); }
uint8_t z80_read(Z80 *z, uint16_t a) { return zread(z->bus, a); }
void z80_write(Z80 *z, uint16_t a, uint8_t v) { zwrite(z->bus, a, v); }
uint8_t z80_in(Z80 *z, uint16_t port) { (void)z, (void)port; return 0xFF; }  /* no ports on the Genesis */
void z80_out(Z80 *z, uint16_t port, uint8_t v) { (void)z, (void)port, (void)v; }
void z80_idle(Z80 *z, uint16_t a, unsigned n) { (void)z, (void)a, (void)n; }
uint8_t z80_irq_ack(Z80 *z) { (void)z; return 0xFF; }

/* ---- the 68000's space ---- */
/* The 16-bit data bus for a read at a (strobe as for wr); byte-wide devices give their byte on both halves. */
static uint16_t rd(Md *m, uint32_t a, unsigned strobe) {
    a &= 0xFFFFFE;
    if (a < 0x400000) {
        if (m->eeprom.size && a == 0x200000)
            return (uint16_t)(md_eeprom_read(&m->eeprom, a) << 8 | md_eeprom_read(&m->eeprom, a + 1));
        if (sram_on(m, a)) {
            uint32_t o = a - m->sram_start;
            return (uint16_t)(m->sram[o] << 8 | m->sram[o + 1]);
        }
        uint32_t o = rom_offset(m, a);
        return o < m->rom_size ? (uint16_t)(m->rom[o] << 8 | m->rom[o + 1]) : open_bus(m);
    }
    if (a >= 0xE00000) return (uint16_t)(m->wram[a & 0xFFFF] << 8 | m->wram[(a & 0xFFFF) + 1]);
    if (a >= 0xC00000) return vdp_at(a) ? vdp_read(m, a) : open_bus(m);
    if (a >= 0xA00000 && a < 0xA10000) {
        if (z80_has_bus(m)) return open_bus(m);  /* not granted */
        uint8_t v = zbus_read(m, (uint16_t)(a | (strobe == 1)), md_now(m));  /* $8000-$FFFF: not the window from this side */
        return (uint16_t)(v << 8 | v);
    }
    if (a >= 0xA10000 && a < 0xA10020) {
        uint8_t v = io_read(m, (int)(a >> 1 & 0xF));
        return (uint16_t)(v << 8 | v);
    }
    if (a == 0xA11100)  /* bit 8: 0 once the Z80 has given its bus (requested and out of reset) */
        return (uint16_t)((open_bus(m) & 0xFEFF) | !(m->z80_busreq && m->z80_run) << 8);
    return open_bus(m);  /* expansion (Mega-CD, $400000-$7FFFFF) and the rest */
}

/* The Z80's reset line also resets the YM2612. */
static void z80_reset_line(Md *m, int run) {
    if (!run) {
        z80_reset(&m->z80);
        snd_run(m, md_now(m));
        ym_reset(&m->snd.ym);
    }
    m->z80_run = (uint8_t)run;
}

/* strobe 3: a word; 2: the byte at the even address (upper half); 1: the odd one */
static void wr(Md *m, uint32_t a, uint16_t v, unsigned strobe) {
    a &= 0xFFFFFE;
    uint8_t byte = (uint8_t)(strobe == 1 ? v : v >> 8);  /* a word to a byte device: its upper byte */
    if (a < 0x400000) {
        if (m->eeprom.size && a == 0x200000) {
            if (strobe & 2) md_eeprom_write(&m->eeprom, a, (uint8_t)(v >> 8));
            if (strobe & 1) md_eeprom_write(&m->eeprom, a + 1, (uint8_t)v);
        } else if (sram_on(m, a) && !(m->sram_ctl & 2)) {
            uint32_t o = a - m->sram_start;
            if (strobe & 2) m->sram[o] = (uint8_t)(v >> 8);
            if (strobe & 1) m->sram[o + 1] = (uint8_t)v;
        }
    } else if (a >= 0xE00000) {
        if (strobe & 2) m->wram[a & 0xFFFF] = (uint8_t)(v >> 8);
        if (strobe & 1) m->wram[(a & 0xFFFF) + 1] = (uint8_t)v;
    } else if (a >= 0xC00000) {
        if (vdp_at(a)) vdp_write(m, a, v, md_now(m));
    } else if (a >= 0xA00000 && a < 0xA10000) {
        if (!z80_has_bus(m)) zbus_write(m, (uint16_t)(a | (strobe == 1)), byte, md_now(m));
    } else if (a >= 0xA10000 && a < 0xA10020) {
        io_write(m, (int)(a >> 1 & 0xF), (uint8_t)v);  /* the odd byte (a word: its lower half) */
    } else if (a == 0xA11100) {
        if (strobe & 2) m->z80_busreq = (uint8_t)(v >> 8 & 1);
    } else if (a == 0xA11200) {
        if (strobe & 2) z80_reset_line(m, v >> 8 & 1);
    } else if (a >= 0xA130F0 && a < 0xA13100) {
        if (a == 0xA130F0) m->sram_ctl = (uint8_t)(v & 3);
        else m->ssf2[(a & 0xF) >> 1] = (uint8_t)(v & 0x3F);
    } else if (a >= 0xA14000 && a < 0xA14004) {
        if (strobe & 2) m->tmss[a & 3] = (uint8_t)(v >> 8);
        if (strobe & 1) m->tmss[(a & 3) + 1] = (uint8_t)v;
    }
}

uint16_t md_read16(Md *m, uint32_t a) { return rd(m, a, 3); }
uint16_t m68k_read(M68k *c, uint32_t a, unsigned fc, unsigned strobe) { (void)fc; return rd(c->bus, a, strobe); }
void m68k_write(M68k *c, uint32_t a, uint16_t v, unsigned fc, unsigned strobe) { (void)fc; wr(c->bus, a, v, strobe); }
void m68k_idle(M68k *c, unsigned clocks) { (void)c, (void)clocks; }
void m68k_aborted(M68k *c, uint32_t a, unsigned fc, unsigned strobe, int write) { (void)c, (void)a, (void)fc, (void)strobe, (void)write; }
int m68k_iack(M68k *c, int level) { vdp_iack(c->bus, level); return -1; }  /* autovectors */
void m68k_reset_out(M68k *c) { (void)c; }

/* ---- the timeline ---- */
/* The Z80 runs up to the 68000's clock, one instruction at a time; it waits
 * while held in reset or while the 68000 has its bus. */
void md_z80_catch_up(Md *m) {
    uint64_t now = md_now(m);
    if (!z80_has_bus(m)) { m->z80_clock = now; return; }
    while (m->z80_clock < now) {
        uint64_t t0 = m->z80.tstates, pos = m->z80_clock - m->frame_start;
        uint64_t vbl = (uint64_t)vdp_height(m) * MD_LINE_CLOCKS;  /* INT from the start of vertical blank */
        int irq = pos >= vbl && pos < vbl + Z80_INT_CLOCKS;
        m->z80_t0 = t0;
        if (!irq || !z80_interrupt(&m->z80)) z80_step(&m->z80);
        m->z80_clock += (m->z80.tstates - t0) * 15;
    }
}

uint32_t md_code_end(const Md *m) {
    uint32_t end = m->rom_size > 0x400000 ? 0x80000 : m->rom_size;
    if (m->sram && m->rom_size > m->sram_start && m->sram_start < end) end = m->sram_start;
    return end;
}

/* One step of the 68000: a recompiled block when one holds the queued
 * instruction and the interpreter would run it as a plain instruction,
 * else one interpreted step; then the Z80 catches up (the block does that
 * after each of its instructions itself). */
static void cpu_step(Md *m) {
    M68k *c = &m->cpu;
    uint32_t at = (c->pc - 4) & 0xFFFFFF;
    uint64_t t0 = c->cycles;
    MdRecompFn f = NULL;
    if (m->recomp_on && !c->halted && !c->stopped && !c->trace && !c->ipl && !c->ipl_seen) f = md_recomp_program->lookup(at);
    if (f) {
        if (setjmp(c->abort)) md_z80_catch_up(m);  /* an address error ended the block's instruction */
        else f(c);
        m->cycles_native += c->cycles - t0;
        return;
    }
    if (m->misses && at < md_code_end(m)) m->misses[at >> 1] = 1;
    m68k_step(c);
    md_z80_catch_up(m);
    m->cycles_interp += c->cycles - t0;
}

/* The CPUs run through a line, then the VDP draws it. */
void md_run_line(Md *m) {
    int lines = m->pal ? 313 : 262;
    if (m->line == vdp_height(m)) vdp_vblank(m);
    m->line_end = m->frame_start + (uint64_t)(m->line + 1) * MD_LINE_CLOCKS;
    while (md_now(m) < m->line_end) cpu_step(m);
    vdp_line_end(m, m->line);
    if (++m->line < lines) return;
    m->line = 0;
    m->frame_start += (uint64_t)lines * MD_LINE_CLOCKS;
    snd_run(m, m->frame_start);
    m->frame_count++;
}

void md_run_frame(Md *m) {
    uint32_t f = m->frame_count;
    while (m->frame_count == f) md_run_line(m);
}

/* ---- loading ---- */
static uint32_t be32(const uint8_t *p) { return (uint32_t)p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3]; }

/* Version register bits 7 (overseas) and 6 (PAL) from the header's regions:
 * "JUE" letters, or one hex digit (bit 0 Japan, 2 Americas, 3 Europe). The
 * Americas when allowed, else Japan, else Europe. */
static uint8_t region(const uint8_t *rom) {
    int j = 0, u = 0, e = 0;
    for (int i = 0; i < 3; i++) {
        char ch = (char)rom[0x1F0 + i];
        j |= ch == 'J', u |= ch == 'U', e |= ch == 'E';
    }
    if (!j && !u && !e) {
        char ch = (char)rom[0x1F0];
        int d = ch >= '0' && ch <= '9' ? ch - '0' : ch >= 'A' && ch <= 'F' ? ch - 'A' + 10 : 0;
        j = d & 1, u = d >> 2 & 1, e = d >> 3 & 1;
    }
    return u || (!j && !e) ? 0x80 : j ? 0x00 : 0xC0;
}

int md_load(Md *m, const uint8_t *rom, size_t size, char *err, size_t errlen) {
    memset(m, 0, sizeof *m);
    if (size < 0x200 || size > 0x2000000) {
        snprintf(err, errlen, "not a Genesis ROM: %zu bytes", size);
        return -1;
    }
    m->rom_size = (uint32_t)((size + 1) & ~(size_t)1);
    m->rom = calloc(1, m->rom_size);
    if (!m->rom) { snprintf(err, errlen, "out of memory"); return -1; }
    memcpy(m->rom, rom, size);
    for (int i = 0; i < 8; i++) m->ssf2[i] = (uint8_t)i;
    /* battery RAM: "RA", type, $20, start, end (odd bytes, even bytes or both; every byte kept) */
    md_eeprom_setup(&m->eeprom, m->rom);  /* a serial EEPROM takes battery RAM's place */
    uint32_t start = be32(rom + 0x1B4) & ~1u, end = be32(rom + 0x1B8) | 1u;
    if (!m->eeprom.size && rom[0x1B0] == 'R' && rom[0x1B1] == 'A' && start >= 0x200000 && start < 0x400000 && end > start &&
        end - start < 0x20000) {
        m->sram_start = start;
        m->sram_size = end - start + 1;
        m->sram = malloc(m->sram_size);
        if (!m->sram) { md_free(m); snprintf(err, errlen, "out of memory"); return -1; }
        memset(m->sram, 0xFF, m->sram_size);
    }
    static const uint8_t IO[16] = {0x20, 0x7F, 0x7F, 0x7F, 0, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0};
    memcpy(m->io, IO, sizeof IO);
    m->io[0] |= region(m->rom);  /* version 0: a console before TMSS (early games never write "SEGA") */
    m->pal = m->io[0] >> 6 & 1;
    m->vdp_first_frame = -1;
    m->cpu.bus = m->z80.bus = m;
    z80_reset(&m->z80);  /* held in reset until the 68000 releases it */
    snd_reset(&m->snd);
    m68k_reset(&m->cpu);
    m->recomp_on = md_recomp_program && md_recomp_program->rom_hash == md_rom_hash(m);
    return 0;
}

void md_reset(Md *m) {
    m->z80_busreq = m->tmss_locked = 0;
    z80_reset_line(m, 0);
    m68k_reset(&m->cpu);
}

uint32_t md_rom_hash(const Md *m) {
    uint32_t h = 2166136261u;
    for (uint32_t i = 0; i < m->rom_size; i++) h = (h ^ m->rom[i]) * 16777619u;
    return h;
}

enum { STATE_VERSION = 2 };  /* 2: the EEPROM */
typedef struct { char magic[4]; uint32_t version, size, rom_hash; } StateHeader;

int md_state_save(const Md *m, const char *path) {
    StateHeader h = {{'M', 'D', 'S', 'S'}, STATE_VERSION, (uint32_t)sizeof *m, md_rom_hash(m)};
    FILE *f = fopen(path, "wb");
    if (!f) return -1;
    int ok = fwrite(&h, sizeof h, 1, f) == 1 && fwrite(m, sizeof *m, 1, f) == 1 &&
             (!m->sram || fwrite(m->sram, m->sram_size, 1, f) == 1);
    return fclose(f) == 0 && ok ? 0 : -1;
}

int md_state_load(Md *m, const char *path, char *err, size_t errlen) {
    FILE *f = fopen(path, "rb");
    if (!f) return snprintf(err, errlen, "cannot open"), -1;
    StateHeader h;
    Md *s = malloc(sizeof *s);
    uint8_t *sram = m->sram ? malloc(m->sram_size) : NULL;
    int ok = s && (sram || !m->sram) && fread(&h, sizeof h, 1, f) == 1 && !memcmp(h.magic, "MDSS", 4);
    if (!ok) snprintf(err, errlen, "not a save state");
    else if (h.version != STATE_VERSION || h.size != sizeof *m)
        ok = 0, snprintf(err, errlen, "saved by a different version of the program");
    else if (h.rom_hash != md_rom_hash(m))
        ok = 0, snprintf(err, errlen, "saved with a different game");
    else if (fread(s, sizeof *s, 1, f) != 1 || (sram && fread(sram, m->sram_size, 1, f) != 1))
        ok = 0, snprintf(err, errlen, "file is truncated");
    fclose(f);
    if (ok) {  /* all but what belongs to this process: the ROM and battery RAM buffers, the CPUs' links,
                * the recompiled code and the misses being recorded */
        if (sram) memcpy(m->sram, sram, m->sram_size);
        s->rom = m->rom, s->sram = m->sram;
        s->recomp_on = m->recomp_on, s->misses = m->misses;
        *m = *s;
        m->cpu.bus = m->z80.bus = m;
    }
    free(s);
    free(sram);
    return ok ? 0 : -1;
}

void md_free(Md *m) {
    free(m->rom);
    free(m->sram);
    m->rom = m->sram = NULL;
}

uint8_t *md_battery(Md *m, uint32_t *size) {
    if (m->eeprom.size) return *size = m->eeprom.size, m->eeprom.mem;
    *size = m->sram ? m->sram_size : 0;
    return m->sram;
}
