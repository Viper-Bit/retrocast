/* The Game Boy (DMG) and Game Boy Color (CGB mode): CPU + memory map +
 * timer + interrupts + serial + joypad + OAM DMA + cartridge, the Color's
 * banks, palettes, HDMA and double speed, and the CPU bus (Pan Docs
 * "Memory Map", "Timer and Divider Registers", "Interrupts", "OAM DMA
 * Transfer", "CGB Registers").
 * Everything is stepped once per M-cycle, before the CPU's access in that
 * cycle (gb.c tick); the PPU is in ppu.c. */
#ifndef GB_GB_H
#define GB_GB_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "apu.h"
#include "cart.h"
#include "sm83_cpu.h"

enum { GB_FRAME_CYCLES = 17556 };  /* M-cycles per frame: 154 lines x 114 */
enum { INT_VBLANK = 1, INT_STAT = 2, INT_TIMER = 4, INT_SERIAL = 8, INT_JOYPAD = 16 };
/* The model whose boot ROM state the game starts in. AUTO: CGB when the header asks for it ($0143 bit 7), else DMG.
 * CGB and AGB with a game that does not ask for the Color: compatibility mode (cgb_compat.c). The SGB models
 * differ in their boot state only. */
enum { GB_MODEL_AUTO = -1, GB_MODEL_DMG, GB_MODEL_CGB, GB_MODEL_DMG0, GB_MODEL_MGB, GB_MODEL_SGB, GB_MODEL_SGB2,
       GB_MODEL_AGB, GB_MODEL_CGB0, GB_MODEL_CGB_E };

typedef struct Gb {
    GbCpu cpu;
    GbCart cart;
    uint8_t vram[0x4000], wram[0x8000], oam[0xA0], hram[0x7F];  /* VRAM: 2 banks, WRAM: 8 (DMG: 1 and 2) */
    uint8_t io[0x80];          /* registers as written: sound ($10-$3F, apu.c), palettes */
    GbApu apu;
    uint8_t ie, ifl;
    /* timer: DIV is the top byte of a 16-bit counter of clocks; TIMA counts
     * falling edges of the bit TAC selects. tima_reload: 1 = TIMA overflowed
     * in the last cycle (reads 0; a write cancels), 2 = this cycle loads TMA */
    uint16_t div;
    uint8_t tima, tma, tac, tima_reload;
    /* serial: an internal-clock transfer ends after 8 bits at 8192 Hz with
     * no partner: SB reads $FF. Bytes sent are kept for the test runner. */
    uint8_t sb, sc;
    uint16_t speed_wait;       /* M-cycles left in a CGB speed switch */
    int serial_left;           /* M-cycles until the transfer ends; 0 = none */
    char serial_out[4096];
    int serial_n;
    /* joypad: P1 select bits, buttons held (core/input_log.h PAD_* bits) */
    uint8_t p1, pad;
    /* PPU (ppu.c) */
    uint8_t lcdc, stat, scy, scx, ly, lyc, wy, wx, stat_line;
    uint8_t mode, mode_seen;   /* STAT mode while the LCD is on; what it was a dot before the cycle's end (what the CPU reads) */
    uint8_t coin_hold;         /* the LY=LYC flag as the LCD was turned off */
    uint8_t ly_seen;           /* the same for LY: STAT's coincidence flag is clear for a cycle after LY changes */
    uint8_t wy_hit, win_line;  /* LY reached WY this frame; the window's own line counter */
    int dot;                   /* dot in the line (0-455) */
    struct {                   /* mode 3 of this line, drawn a dot at a time (ppu.c) */
        int x, stall, otile;          /* next pixel (160: mode 3 is over); dots left of a fetch stall */
        uint8_t fine, pos;     /* SCX mod 8 at the line's start; next bit of the tile row in hand (8: fetch) */
        uint8_t lo, hi, attr;  /* that row's two bit planes and (CGB) its map attributes */
        uint8_t glitch, stage, ntile, nattr, ny, nlo, nhi;  /* the next row: fetch step done, tile, attributes, row in tile, bytes */
        uint8_t col, wcol, win;  /* background and window tile columns fetched; the window has started */
        uint8_t nobj, next, objs[10];  /* objects on the line by X; the next one to fetch */
        uint8_t ob_ci[160], ob_fl[160], ob_ix[160];  /* object pixels so far: colour (0: none), OAM flags, OAM index */
    } m3;
    uint16_t fb[160 * 144];    /* the frame being drawn: DMG shades 0 (light) - 3 (dark); CGB: RGB555 */
    uint16_t frame[160 * 144]; /* the last whole frame (copied at vblank; blank while the LCD is off) */
    uint32_t frame_count;      /* frames completed into `frame` */
    /* OAM DMA: a byte per M-cycle for 160, starting a cycle after the write
     * to $FF46; meanwhile the CPU sees only HRAM */
    uint8_t dma_reg, dma_start, dma_on;
    int dma_pos;
    uint16_t dma_src, dma_next;
    uint64_t frame_end;        /* cpu.cycles where the current frame ends */
    /* Game Boy Color (cgb: 1 for early CGB, 2 for CGB-E; compat: it runs a DMG game, with the Color's palettes) */
    uint8_t cgb, compat, vbk, svbk, opri;       /* VRAM bank, WRAM bank at $D000 (0 = 1), object priority (0: OAM order) */
    uint8_t key1, double_speed, half;   /* speed switch armed; double speed; which half of the slow clock this is */
    uint8_t bcps, ocps, bg_pal[64], obj_pal[64];  /* palette RAM: 8 palettes x 4 colours, RGB555 little endian */
    /* HDMA: source, destination (VRAM offset), blocks left - 1 ($7F: none);
     * hdma_on: an HBlank transfer runs; hdma_due: hblank began, a block is due */
    uint16_t hdma_src, hdma_dst;
    uint8_t hdma_left, hdma_on, hdma_due;
    uint8_t recomp_on;         /* recompiled code (recomp_rt.h) made from this ROM is linked in */
    uint64_t cycles_native, cycles_interp;  /* where the CPU's cycles went (--coverage) */
    /* ROM code the interpreter ran, by gb_miss_slot (gb_headless --misses
     * for gbrecomp); NULL: not recorded. Not part of save states. */
    uint8_t *misses;
} Gb;

/* Load a ROM (copied) and set the state the boot ROM leaves; model:
 * GB_MODEL_* (gb_load: AUTO). */
int gb_load(Gb *g, const uint8_t *rom, size_t size, char *err, size_t errlen);
int gb_load_model(Gb *g, const uint8_t *rom, size_t size, int model, char *err, size_t errlen);
/* CPU M-cycles in a frame: twice as many in double speed */
static inline uint64_t gb_frame_cycles(const Gb *g) { return (uint64_t)GB_FRAME_CYCLES << g->double_speed; }
void gb_free(Gb *g);
void gb_step(Gb *g);           /* one instruction, interrupt entry or halted cycle */
void gb_run_frame(Gb *g);      /* GB_FRAME_CYCLES M-cycles */
void gb_set_pad(Gb *g, uint8_t pad);  /* PAD_* bits; a new press raises the joypad interrupt */
uint32_t gb_rom_hash(const Gb *g);     /* FNV-1a of the ROM (recompiled code is matched by it) */
/* misses: one slot per (ROM bank, address) for code at $0000-$7FFF */
static inline size_t gb_miss_slots(const Gb *g) { return (size_t)g->cart.rom_size / 0x4000 * 0x8000; }
void gb_misses_write(const Gb *g, FILE *f);  /* "MISS $PC bank B" lines */
/* Adds the lines of such a file to g->misses. Returns how many slots set
 * before the call the file did not list (0: nothing new to write). */
long gb_misses_merge(Gb *g, const char *path);

/* save states: the whole machine, for this ROM (by hash) and this build's layout */
int gb_state_save(const Gb *g, const char *path);
int gb_state_load(Gb *g, const char *path, char *err, size_t errlen);

/* ppu.c */
uint8_t gb_compat_palettes(Gb *g);  /* cgb_compat.c: the boot ROM's palette for this game; returns its title checksum */
void ppu_tick(Gb *g, int step);
int ppu_mode(const Gb *g);
int ppu_vmode(const Gb *g);
void ppu_stat_update(Gb *g);
void ppu_stat_write(Gb *g, uint8_t v);
void ppu_lcdc_write(Gb *g, uint8_t v);

#endif
