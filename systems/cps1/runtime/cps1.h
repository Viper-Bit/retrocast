/* The Capcom Play System I (CPS-1): a 68000 at 10 MHz running the game, a
 * Z80 at 3.58 MHz for sound (YM2151, OKI MSM6295), and the CPS-A / CPS-B
 * graphics chips (three scroll layers, sprites, stars). A game comes as a
 * zip of chip dumps; games.c says which chip goes where, and which CPS-B
 * the board has (its ID, ports and layer bits differ by game).
 * Sources: docs/sources.md (CPS-1). */
#ifndef CPS1_H
#define CPS1_H

#include <stddef.h>
#include <stdint.h>

#include "m68k_cpu.h"
#include "eeprom93c46.h"
#include "oki6295.h"
#include "qsound.h"
#include "ym2151.h"
#include "z80_cpu.h"
#include "zip.h"

/* ---- the game table (games.c) and loading (load.c) ---- */

enum { CPS1_R_MAIN, CPS1_R_GFX, CPS1_R_SOUND, CPS1_R_OKI, CPS1_REGIONS };
#define CPS1_R_QSOUND CPS1_R_OKI  /* the Q-Sound board's samples: where the others' OKI samples are */
enum {
    CPS1_LOAD_PLAIN,    /* the bytes as they are */
    CPS1_LOAD_EVEN,     /* an 8-bit chip on the 68000's upper byte: every other byte from offset */
    CPS1_LOAD_ODD,      /* the same on the lower byte (offset is odd) */
    CPS1_LOAD_SWAP16,   /* a 16-bit chip, its words byte-swapped into big-endian order */
    CPS1_LOAD_GFX4,     /* a 16-bit graphics chip: 2 bytes into every 8, at offset's slot (0, 2, 4, 6) */
    CPS1_LOAD_GFX8,     /* an 8-bit graphics chip: 1 byte into every 8, at offset's slot (0-7) */
    CPS1_LOAD_BYTE4     /* an 8-bit chip: 1 byte into every 4, at offset's slot (0-3; MAME's ROM_LOAD32_BYTE) */
};
enum { CPS1_PLAIN, CPS1_QSOUND, CPS1_ODD };  /* board groups (docs/roadmap.md) */
/* What MAME's IN2 holds: buttons 4-6 of players 1-2, player 3, or players 3
 * and 4 (IN3, and their buttons 3 in IN1's bits 7 and 15: Slam Masters). */
enum { CPS1_EXTRA_NONE, CPS1_EXTRA_KICKS, CPS1_EXTRA_P3, CPS1_EXTRA_P4 };
/* What MAME's init function for a set does beyond the board: the Q-Sound
 * games' Kabuki keys (kabuki.h); Pang! 3's code decryption (not its
 * bootleg's) and its EEPROM on the CPS-B's port $80017A. */
enum { CPS1_INIT_NONE, CPS1_INIT_WOF, CPS1_INIT_DINO, CPS1_INIT_PUNISHER, CPS1_INIT_SLAMMAST, CPS1_INIT_PANG3, CPS1_INIT_PANG3B };

typedef struct {
    uint32_t crc, size;
    uint8_t region, load;
    uint32_t offset;
    uint32_t skip, len;          /* the part of the chip placed here: len bytes from skip; len 0: all of it (MAME's
                                  * ROM_CONTINUE, ROM_RELOAD and ROM_IGNORE are rows of one chip) */
    uint8_t from_parent;         /* in the clone's parent zip, not its own */
} Cps1File;

#define CPS1_NONE 0xFF  /* a CPS-B port the board does not have */
typedef struct {
    uint8_t id_reg;              /* the ID port (a byte offset into the CPS-B registers) */
    uint16_t id_val;
    uint8_t mult_a, mult_b, mult_lo, mult_hi;  /* the multiplier's ports */
    uint8_t layer_ctrl, prio[4], pal_ctrl;
    uint16_t layer_enable[5];    /* the layer-control bits enabling scroll1-3, stars 1-2 */
} Cps1B;

/* The graphics ROM mapper (a PAL per board): which tile codes each layer
 * may use, in 64-byte units (a code shifted: sprites and scroll2 << 1,
 * scroll1 << 0, scroll3 << 3), and the bank they come from. A code in no
 * range of its layer is not drawn; no ranges at all lets every code through. */
enum { CPS1_GFX_SPRITES = 1, CPS1_GFX_SCROLL1 = 2, CPS1_GFX_SCROLL2 = 4, CPS1_GFX_SCROLL3 = 8, CPS1_GFX_STARS = 16 };
typedef struct { uint8_t type; uint32_t start, end; uint8_t bank; } Cps1Range;
typedef struct { uint32_t bank_size[4]; uint8_t n; Cps1Range range[8]; } Cps1Mapper;
/* The code to draw for a layer's tile code, or -1: not drawn. */
int cps1_gfx_map(const Cps1Mapper *m, int type, int code);

typedef struct {
    const char *id, *title;
    uint8_t group;
    uint32_t region_size[CPS1_REGIONS];
    Cps1B b;
    uint8_t nfiles;
    Cps1File files[48];          /* the most a board uses: 43 (Japanese boards of many small chips) */
    Cps1Mapper mapper;           /* the board's graphics ROM PAL */
    uint8_t clock_mhz;           /* the 68000's: 10 or 12 */
    uint8_t dip[3];              /* DIP switches A-C at their defaults, as read (active low) */
    uint8_t in2, in3;            /* CPS-B ports of the extra inputs (players 3-4, kicks), or CPS1_NONE */
    const char *parent;          /* a clone's parent zip (beside it) holding the rest of its files, or NULL */
    uint8_t dial;                /* Forgotten Worlds' rotary dials */
    int32_t stars;               /* the star layers' 32 KB in the graphics ROM, or -1: none */
    uint8_t extra;               /* what the in2 port holds: CPS1_EXTRA_* */
    uint16_t rotate;             /* the monitor, as MAME's ROT: 0, or 270 (turned 90 degrees anticlockwise) */
    uint8_t cpsb_high;           /* the CPS-B at $8001C0, not $800140 (Street Fighter II revision E, MAME's init_sf2ee) */
    uint8_t init;                /* CPS1_INIT_* */
    uint8_t z80_raw;             /* $F00000 reads the Z80 ROM as dumped (MAME's audiorom_raw: Slam Masters' protection) */
    uint8_t kludge;              /* a bootleg's own video wiring, MAME's bootleg_kludge (video.c) */
} Cps1Game;

extern const Cps1Game cps1_games[];
extern const int cps1_game_count;

typedef struct {
    const Cps1Game *game;
    uint8_t *region[CPS1_REGIONS];
    uint32_t size[CPS1_REGIONS];
    uint8_t *z80_op;             /* Q-Sound: the Z80's first 32 KB as opcodes (the region holds it as data) */
    uint8_t *z80_raw;            /* Q-Sound: those 32 KB as dumped, when the game reads them (z80_raw) */
    uint16_t dsp[4096];          /* Q-Sound: the chip ROM's tables (dl-1425.bin from qsound.zip) */
} Cps1Rom;

/* The game whose own files are all in the zip (by CRC and size), or NULL;
 * other entries (PAL dumps, clones of a merged set) do not matter, and a
 * clone's files from its parent need not be there. Two matches: the one
 * with more of its own files, then the first. */
const Cps1Game *cps1_match(const Zip *z);
const Cps1Game *cps1_match_in(const Zip *z, const Cps1Game *games, int n);
/* 0, or -1 with the first missing or damaged file (its CRC) in err. */
int cps1_load(const Cps1Game *g, const Zip *z, Cps1Rom *r, char *err, size_t errlen);
void cps1_unload(Cps1Rom *r);
/* Pang! 3's 68000 code from $80000: the low byte of each word decrypted (MAME's init_pang3). */
void cps1_pang3_decrypt(uint8_t *main, uint32_t size);
/* A game's zip (data, read from path) matched and loaded; a clone's other
 * files from "<parent>.zip" in the same folder, a Q-Sound game's chip ROM
 * from qsound.zip there (MAME's names). 0, or -1 with a message. */
int cps1_open(const char *path, const uint8_t *data, size_t size, Cps1Rom *r, char *err, size_t errlen);
int cps1_open_in(const char *path, const uint8_t *data, size_t size, const Cps1Game *games, int n, Cps1Rom *r,
                 char *err, size_t errlen);

/* ---- the machine (cps1.c) ---- */

#define CPS1_WIDTH 384
#define CPS1_HEIGHT 224
#define CPS1_LINES 262          /* 8 MHz pixel clock, 512 per line: 59.64 Hz */
#define CPS1_FIRST_LINE 16      /* the visible lines are 16-239 */
#define CPS1_VBLANK_LINE 240
#define CPS1_CLOCK 10000000     /* 68000 */
#define CPS1_LINE_CLOCKS 640    /* 10 MHz / (8 MHz / 512) */
#define CPS1_Z80_CLOCK 3579545
#define CPS1_SAMPLE_RATE OPM_RATE  /* mono, one sample every 64 Z80 T-states */
#define CPS1_QSOUND_Z80_CLOCK 8000000
#define CPS1_QSOUND_RATE (QSOUND_CLOCK / QSOUND_CLOCKS_PER_SAMPLE)  /* stereo, 24,038 Hz (24,038.46) */
#define CPS1_QSOUND_IRQ 32000   /* the Q-Sound Z80's interrupt: every 32,000 T-states (250 Hz) */
#define CPS1_SND_BUF 8192

/* Recompiled 68000 code (recomp_rt.h, systems/cps1/recomp): made from one
 * game's main-CPU code; runs only where cps1_code_hash matches rom_hash. */
typedef void (*Cps1RecompFn)(M68k *c);
typedef struct {
    uint32_t rom_hash;
    const char *game_id;
    Cps1RecompFn (*lookup)(uint32_t at);  /* the block holding the instruction at `at`; NULL: none */
} Cps1RecompProgram;
/* Defined by the generated code; NULL in programs without it (recomp_none.c). */
extern const Cps1RecompProgram *const cps1_recomp_program;
uint32_t cps1_code_hash(const Cps1Rom *r);  /* FNV-1a of the main-CPU region */

typedef struct Cps1 {
    M68k cpu;
    const Cps1Rom *rom;
    uint8_t ram[0x10000];       /* $FF0000-$FFFFFF */
    uint8_t gfxram[0x30000];    /* $900000-$92FFFF */
    uint16_t cpsa[0x20], cpsb[0x20];  /* $800100 and $800140, by word */
    uint16_t mult_a, mult_b;
    uint8_t sound_cmd, sound_fade;
    uint16_t pad[4];            /* core/input_log.h PAD_* bits, players 1-4 */
    uint32_t line_clocks;       /* 68000 clocks a line: 640 at 10 MHz, 768 at 12 */
    int32_t dial[2], dial_start[2];  /* Forgotten Worlds' uPD4701: counters, and their value at the last reset */
    uint8_t dip[3];             /* DIP switches A-C, as read (active low) */
    int line;
    uint64_t frames;            /* run since power-on */
    uint64_t line_end;          /* cpu.cycles when the current line ends */
    Z80 z80;                    /* sound: $0000-$BFFF ROM (bank at $8000), $D000 RAM, $F000- I/O */
    uint8_t z80_ram[0x800];
    uint8_t bank;
    Opm opm;
    Oki oki;
    uint64_t lines;             /* since power-on: the Z80 runs to lines x 229.09 T-states */
    uint64_t snd_next;          /* the Z80 T-state of the next sample */
    uint64_t oki_acc;           /* towards the OKI's next sample */
    int oki_out;
    int16_t snd[CPS1_SND_BUF];
    int snd_n;
    uint16_t pal[0xC00];        /* the colours, as uploaded (video.c) */
    uint16_t frame[CPS1_WIDTH * CPS1_HEIGHT];  /* palette indices */
    const Cps1RecompProgram *recomp;  /* this program's recompiled code, if any */
    uint8_t recomp_on;          /* it is this game's: blocks run where they hold the PC */
    uint8_t *misses;            /* NULL, or a byte per main-CPU word: set where the interpreter ran */
    uint64_t cycles_native, cycles_interp;  /* 68000 clocks run each way (--coverage) */
    /* The Q-Sound board: the Z80 shares $C000-$CFFF and $F000-$FFFF with the
     * 68000 ($F18000 and $F1E000, a byte a word); a 16 KB bank; the chip; the EEPROM. */
    uint8_t qram[2][0x1000];
    uint8_t qbank, qirq;        /* qirq: the Z80's interrupt, held until taken */
    uint64_t qirq_next;         /* the T-state of the next one */
    QSound qs;
    Eeprom93c46 eeprom;
} Cps1;

void cps1_init(Cps1 *s, const Cps1Rom *r);  /* with cps1_recomp_program */
void cps1_init_with(Cps1 *s, const Cps1Rom *r, const Cps1RecompProgram *p);
void cps1_frame(Cps1 *s);       /* 262 lines; the picture is left in s->frame */
void cps1_line(Cps1 *s);        /* one of them (s->line: the next, 262 after the last) */
/* Players 0-3: buttons 1-3 = B, A, X; Start; Select = coin; Street Fighter
 * II's kicks (4-6) = Y, L, R; Forgotten Worlds' dial: L / R turn it. */
void cps1_set_input(Cps1 *s, int player, uint16_t pad);
/* Up to max sample values made so far: mono at CPS1_SAMPLE_RATE, or, on the
 * Q-Sound board, left / right pairs at CPS1_QSOUND_RATE (cps1_channels); the
 * number taken. When nobody takes them, a full buffer drops the new ones. */
int cps1_take_sound(Cps1 *s, int16_t *out, int max);
/* The board keeps settings in a 93C46 EEPROM (GAME.eeprom next to the zip). */
static inline int cps1_has_eeprom(const Cps1Game *g) {
    return g->group == CPS1_QSOUND || g->init == CPS1_INIT_PANG3 || g->init == CPS1_INIT_PANG3B;
}
static inline int cps1_channels(const Cps1Game *g) { return g->group == CPS1_QSOUND ? 2 : 1; }
static inline int cps1_sample_rate(const Cps1Game *g) { return g->group == CPS1_QSOUND ? CPS1_QSOUND_RATE : CPS1_SAMPLE_RATE; }

/* ---- save states (state.c) ---- */
int cps1_state_save(const Cps1 *s, const char *path);  /* 0, or 1 */
/* 0, or 1 with a message: not a state, another version or another game;
 * the machine is untouched then. */
int cps1_state_load(Cps1 *s, const char *path, char *err, size_t errlen);

/* ---- the picture (video.c) ---- */
void cps1_render(Cps1 *s);                     /* fills s->frame */
uint32_t cps1_color(const Cps1 *s, uint16_t index);  /* 0xRRGGBB */
/* The picture as shown, turned for the game's monitor: CPS1_WIDTH x CPS1_HEIGHT,
 * or CPS1_HEIGHT x CPS1_WIDTH for a turned one; *w and *h say which. */
void cps1_picture(const Cps1 *s, uint32_t *rgb, int *w, int *h);
void cps1_palette_upload(Cps1 *s);             /* on a write to the palette base */

#endif
