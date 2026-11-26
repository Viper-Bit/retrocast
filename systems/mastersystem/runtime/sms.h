/* The Sega Master System (and Mark III), and the Game Gear in its own mode:
 * a Z80 at 3.58 MHz, 8 KB of work RAM, the Sega mapper, the mode-4 VDP and
 * the SN76489 PSG. The Game Gear differs in the palette (12-bit colours,
 * written two bytes at a time), ports $00-$06 (Start, region, stereo), no
 * Pause/NMI, 60 Hz only, and an LCD showing the central 160x144 of the
 * picture; it runs Master System cartridges in Master System mode. A frame is run a
 * line at a time, 228 Z80 T-states each (the VDP's 342 pixel clocks); the
 * VDP's frame and line interrupts are checked before every instruction.
 * Sources: SMS Power (Development: VDP documentation by Charles MacDonald,
 * "Sega Master System VDP documentation"; Mappers; Port map; Peripherals;
 * Game Gear: Palette, I/O Port Map). */
#ifndef SMS_H
#define SMS_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "z80_cpu.h"

#define SMS_WIDTH 256
#define SMS_HEIGHT 192
#define GG_WIDTH 160                /* the Game Gear's LCD: the picture's centre */
#define GG_HEIGHT 144
#define GG_X 48
#define GG_Y 24
#define SMS_LINE_TSTATES 228        /* 342 pixel clocks at 1.5 per T-state */
#define SMS_LINES_NTSC 262
#define SMS_LINES_PAL 313
#define SMS_CLOCK_NTSC 3579545
#define SMS_CLOCK_PAL 3546893
#define SMS_SAMPLE_RATE 44100
#define SMS_ROM_BANK 0x4000         /* the Sega mapper switches 16 KB banks */
#define SMS_CODE_SPAN 0xC000        /* ROM is mapped at $0000-$BFFF */

/* Code is known by the page mapped in its slot and its address: a page can
 * be mapped into any of the three slots, at different addresses. */
static inline size_t sms_code_index(unsigned page, uint16_t pc) { return (size_t)page * SMS_CODE_SPAN + pc; }

typedef struct {
    const uint8_t *data;
    size_t size;
    uint8_t page[4];                /* $FFFC (control) and $FFFD-$FFFF (slots 0-2) */
    uint8_t ram[0x8000];            /* cartridge RAM: two 16 KB banks at $8000 ($FFFC bits 3, 2) */
    uint8_t ram_used;               /* a game mapped it: it is saved next to the game */
    uint8_t codemasters;            /* Codemasters' mapper: banks written at $0000, $4000, $8000 */
} SmsCart;

typedef struct {
    uint8_t vram[0x4000];
    uint16_t cram[32];              /* --BBGGRR (GG: ----BBBBGGGGRRRR): 16 background, then 16 sprite colours */
    uint8_t cram_latch;             /* GG: the low byte, written to an even address */
    uint8_t gg;                     /* Game Gear mode */
    uint8_t reg[16];
    uint8_t status;                 /* bit 7 frame interrupt, 6 sprite overflow, 5 collision */
    uint8_t line_flag;              /* the line interrupt is pending */
    uint8_t line_counter;
    uint8_t latch, code, buffer;    /* control port's second byte expected; access code; read buffer */
    uint16_t addr;
    uint8_t vscroll;                /* register 9, latched at the top of the frame */
    uint8_t frame[SMS_WIDTH * SMS_HEIGHT];  /* CRAM indices 0-31; 32-47 the TMS9918 palette */
} SmsVdp;

typedef struct {
    uint16_t period[3];             /* 10-bit tone periods */
    uint8_t noise;                  /* bit 2: white, bits 1-0: rate (3 = tone 2's) */
    uint8_t vol[4];                 /* 4-bit attenuation */
    uint16_t count[4];
    uint8_t out[4];
    uint16_t lfsr;
    uint8_t latch;
    uint64_t next;                  /* T-state of the next counter step */
    float acc, level;
    unsigned steps;
} SmsPsg;

typedef struct Sms {
    Z80 cpu;
    SmsCart cart;
    SmsVdp vdp;
    SmsPsg psg;
    uint8_t ram[0x2000];
    uint8_t mem_ctrl, io_ctrl;      /* ports $3E and $3F */
    uint16_t pad[2];                /* PAD_* bits (core/input_log.h) */
    uint8_t pause;                  /* the console's Pause button, held last frame */
    int pal;
    unsigned line;                  /* the line being run */
    uint64_t line_start;            /* its first T-state */
    uint64_t line_end;              /* T-state the line's instructions must finish by */
    int recomp_on;                  /* a matching recompiled program is linked */
    uint64_t cycles_native, cycles_interp;
    uint8_t *misses;                /* by sms_code_index: 1 = run in the interpreter (pages * 48 KB) */
    uint32_t frames;
    uint64_t samples_made;          /* samples since power-on: their T-states follow from the clock */
    float samples[1024];            /* this frame's, mono */
    unsigned n_samples;
    uint32_t writes;                /* VDP writes, for the headless program's report */
} Sms;

/* The ROM is borrowed: keep it alive while the machine runs. gg: Game Gear
 * mode (sms_gg_mode), which is 60 Hz whatever pal says. Returns 0 on success. */
int sms_init(Sms *s, const uint8_t *rom, size_t size, int pal, int gg);
void sms_reset(Sms *s);
/* One frame (262 NTSC / 313 PAL lines) with the pads' PAD_* bits; Start on
 * either pad is the console's Pause button (the Game Gear's Start). */
void sms_frame(Sms *s, uint16_t pad0, uint16_t pad1);
int sms_save(const Sms *s, const char *path);
int sms_load(Sms *s, const char *path, char *err, size_t errlen);
/* XRGB8888 of CRAM entry 0-31. */
uint32_t sms_color(const Sms *s, unsigned index);
unsigned sms_lines(const Sms *s);
/* FNV-1a of the ROM, as the recompiler computes it. */
uint32_t sms_rom_hash(const uint8_t *rom, size_t size);
/* The ROM page mapped into the slot holding `a` (slot 0's vectors stay on 0). */
unsigned sms_page_at(const SmsCart *c, uint16_t a);
/* One instruction, or a recompiled block when there is one for the PC. */
void sms_step(Sms *s);
/* The code run in the interpreter (s->misses, sms_miss_slots bytes): written
 * as "MISS $PC page P" lines, which smsrecomp reads; merge adds a file's
 * lines and returns how many of this run's it did not have. */
size_t sms_miss_slots(const Sms *s);
void sms_misses_write(const Sms *s, FILE *f);
size_t sms_misses_merge(Sms *s, const char *path);

/* cart.c */
long sms_header(const uint8_t *data, size_t size);  /* "TMR SEGA" offset, or -1 */
int sms_is_codemasters(const uint8_t *data, size_t size);
/* Game Gear mode: a header's region 5-7 says yes, 3-4 no (a Master System
 * cartridge, which the Game Gear runs as one); without, a .gg file name. */
int sms_gg_mode(const uint8_t *data, size_t size, const char *path);
uint32_t sms_cart_addr(const SmsCart *c, uint16_t a);

/* vdp.c */
uint8_t sms_vdp_read_data(SmsVdp *v);
uint8_t sms_vdp_read_status(SmsVdp *v);
void sms_vdp_write_data(SmsVdp *v, uint8_t val);
void sms_vdp_write_ctrl(SmsVdp *v, uint8_t val);
void sms_vdp_line(Sms *s, unsigned line);           /* a line's start: draw it, counters, flags */
uint8_t sms_vdp_vcount(const Sms *s);
uint8_t sms_vdp_hcount(const Sms *s);
/* The VDP's interrupt line: inline, as recompiled code checks it after every instruction. */
static inline int sms_vdp_irq(const SmsVdp *v) {
    return ((v->status & 0x80) && (v->reg[1] & 0x20)) || (v->line_flag && (v->reg[0] & 0x10));
}

/* psg.c */
void sms_psg_reset(SmsPsg *p);
void sms_psg_run(SmsPsg *p, uint64_t tstates);
void sms_psg_write(SmsPsg *p, uint8_t v);
float sms_psg_take(SmsPsg *p);

#endif
