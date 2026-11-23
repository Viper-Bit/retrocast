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
#include "oki6295.h"
#include "ym2151.h"
#include "z80_cpu.h"
#include "zip.h"

/* ---- the game table (games.c) and loading (load.c) ---- */

enum { CPS1_R_MAIN, CPS1_R_GFX, CPS1_R_SOUND, CPS1_R_OKI, CPS1_REGIONS };
enum {
    CPS1_LOAD_PLAIN,    /* the bytes as they are */
    CPS1_LOAD_EVEN,     /* an 8-bit chip on the 68000's upper byte: every other byte from offset */
    CPS1_LOAD_ODD,      /* the same on the lower byte (offset is odd) */
    CPS1_LOAD_SWAP16,   /* a 16-bit chip, its words byte-swapped into big-endian order */
    CPS1_LOAD_GFX4,     /* a 16-bit graphics chip: 2 bytes into every 8, at offset's slot (0, 2, 4, 6) */
    CPS1_LOAD_GFX8      /* an 8-bit graphics chip: 1 byte into every 8, at offset's slot (0-7) */
};
enum { CPS1_PLAIN, CPS1_QSOUND, CPS1_ODD };  /* board groups (docs/roadmap.md) */
enum { CPS1_EXTRA_NONE, CPS1_EXTRA_KICKS, CPS1_EXTRA_P3 };  /* buttons 4-6 of players 1-2, or player 3 (MAME's IN2) */

typedef struct {
    uint32_t crc, size;
    uint8_t region, load;
    uint32_t offset;
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
    Cps1File files[32];
    Cps1Mapper mapper;           /* the board's graphics ROM PAL */
    uint8_t clock_mhz;           /* the 68000's: 10 or 12 */
    uint8_t dip[3];              /* DIP switches A-C at their defaults, as read (active low) */
    uint8_t in2, in3;            /* CPS-B ports of the extra inputs (players 3-4, kicks), or CPS1_NONE */
    const char *parent;          /* a clone's parent zip (beside it) holding the rest of its files, or NULL */
    uint8_t dial;                /* Forgotten Worlds' rotary dials */
    int32_t stars;               /* the star layers' 32 KB in the graphics ROM, or -1: none */
    uint8_t extra;               /* what the in2 port holds: CPS1_EXTRA_* */
} Cps1Game;

extern const Cps1Game cps1_games[];
extern const int cps1_game_count;

typedef struct {
    const Cps1Game *game;
    uint8_t *region[CPS1_REGIONS];
    uint32_t size[CPS1_REGIONS];
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
/* A game's zip (data, read from path) matched and loaded; a clone's other
 * files from "<parent>.zip" in the same folder. 0, or -1 with a message. */
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
#define CPS1_SND_BUF 8192

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
} Cps1;

void cps1_init(Cps1 *s, const Cps1Rom *r);
void cps1_frame(Cps1 *s);       /* 262 lines; the picture is left in s->frame */
/* Players 0-3: buttons 1-3 = B, A, X; Start; Select = coin; Street Fighter
 * II's kicks (4-6) = Y, L, R; Forgotten Worlds' dial: L / R turn it. */
void cps1_set_input(Cps1 *s, int player, uint16_t pad);
/* Up to max samples (mono, CPS1_SAMPLE_RATE) made so far; the number taken. When
 * nobody takes them, a full buffer drops the new ones. */
int cps1_take_sound(Cps1 *s, int16_t *out, int max);

/* ---- save states (state.c) ---- */
int cps1_state_save(const Cps1 *s, const char *path);  /* 0, or 1 */
/* 0, or 1 with a message: not a state, another version or another game;
 * the machine is untouched then. */
int cps1_state_load(Cps1 *s, const char *path, char *err, size_t errlen);

/* ---- the picture (video.c) ---- */
void cps1_render(Cps1 *s);                     /* fills s->frame */
uint32_t cps1_color(const Cps1 *s, uint16_t index);  /* 0xRRGGBB */
void cps1_palette_upload(Cps1 *s);             /* on a write to the palette base */

#endif
