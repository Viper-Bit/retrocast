/* The Genesis / Mega Drive machine (systems/genesis/docs/roadmap.md D1): the 68000's
 * and the Z80's memory maps, the I/O ports and pads, the version register,
 * Z80 bus request, reset and bank, the cartridge (ROM, battery RAM, the
 * SSF2 bank registers), TMSS, and both CPUs on one master-clock timeline.
 * The VDP is in vdp.c, sound in sound.c. */
#ifndef GENESIS_MD_H
#define GENESIS_MD_H

#include <stddef.h>
#include <stdint.h>

#include "eeprom.h"
#include "m68k_cpu.h"
#include "sound.h"
#include "vdp.h"
#include "z80_cpu.h"

enum { MD_LINE_CLOCKS = 3420 };  /* master clocks per line (68000: 488.57 clocks, Z80: 228) */

typedef struct Md {
    M68k cpu;
    Z80 z80;
    uint8_t *rom;           /* big endian, as on the cartridge bus */
    uint32_t rom_size;
    uint8_t wram[0x10000];  /* 68000 work RAM, $FF0000 (mirrored from $E00000) */
    uint8_t zram[0x2000];   /* Z80 RAM, $A00000 for the 68000 (mirrored at $2000) */
    uint8_t *sram;          /* battery RAM from the header ("RA"), NULL if none */
    uint32_t sram_start, sram_size;  /* 68000 addresses sram_start.. (even, every byte kept) */
    MdEeprom eeprom;        /* a serial EEPROM in place of battery RAM (eeprom.h); size 0 if none */
    uint8_t sram_ctl;       /* $A130F1: bit 0 maps it over ROM, bit 1 write protects */
    uint8_t ssf2[8];        /* $A130F3-$A130FF: 512 KB bank per 512 KB slot (ROMs over 4 MB) */
    uint8_t pal;            /* 313 lines a frame, not 262 */
    /* I/O, the odd bytes $A10001-$A1001F: version (overseas, PAL, no
     * expansion unit; version 0, or 1 for a console with TMSS), data of
     * pads 1, 2 and the expansion port, their control (bit set: an
     * output), the serial registers (kept, no serial) */
    uint8_t io[16];
    uint16_t pad[2];        /* buttons held (core/input_log.h PAD_*) */
    uint8_t pad6[2];        /* a 6-button pad on this port, else 3 buttons */
    uint8_t th_count[2];    /* 6-button pad: TH rises since the timeout, x2 (0-6) */
    uint64_t th_time[2];    /* master clock of the last TH rise */
    /* Z80 control: bus requested ($A11100), reset released ($A11200), bank ($6000) */
    uint8_t z80_busreq, z80_run;
    uint16_t z80_bank;      /* 9 bits: 68000 address bits 23-15 of the $8000 window */
    /* TMSS ($A14000), version 1 only: the VDP stays locked until "SEGA" is written there */
    uint8_t tmss[4];
    uint8_t tmss_locked;    /* the game touched the locked VDP: the 68000 hangs, as on the console */
    Vdp vdp;
    /* port writes the VDP saw, the frame of the first (the boot check) */
    uint32_t vdp_writes;
    int32_t vdp_first_frame;  /* -1: none yet */
    /* timeline, in master clocks: 68000 = cycles x 7, Z80 = tstates x 15 */
    uint64_t frame_start;
    uint64_t z80_t0;        /* the Z80's T-states when its current instruction began */
    Sound snd;
    uint64_t z80_clock;     /* the Z80's position (it waits while held or the 68000 has the bus) */
    uint32_t frame_count;
    int line;               /* the next line md_run_line runs */
    uint64_t line_end;      /* master clock where the running line ends */
    /* recompiled code (recomp_rt.h): linked in and made from this ROM; where
     * the 68000's clocks went (--coverage); the ROM code the interpreter ran,
     * a byte per word below md_code_end (--misses), NULL: not recorded.
     * Not part of save states. */
    uint8_t recomp_on;
    uint64_t cycles_native, cycles_interp;
    uint8_t *misses;
} Md;

/* Load a ROM (copied): the header picks region and battery RAM; power-on. */
int md_load(Md *m, const uint8_t *rom, size_t size, char *err, size_t errlen);
void md_free(Md *m);
/* What the game keeps on the cartridge (battery RAM or EEPROM), for a .sav file; NULL if nothing. */
uint8_t *md_battery(Md *m, uint32_t *size);
/* The console's reset button: the 68000 restarts, the Z80 is held in
 * reset; RAM, VRAM and the cartridge keep their contents. */
void md_reset(Md *m);
uint32_t md_rom_hash(const Md *m);  /* FNV-1a of the ROM: a state belongs to one game */
/* save states: the whole machine and the battery RAM, for this ROM and this build's layout */
int md_state_save(const Md *m, const char *path);
int md_state_load(Md *m, const char *path, char *err, size_t errlen);
void md_run_frame(Md *m);  /* one frame: 262 lines (PAL 313) of master clocks */
void md_run_line(Md *m);   /* one line (the frame's lines in turn) */
/* The end of the ROM code that is always mapped: what the recompiler may
 * compile (not the SSF2 banks, not where battery RAM can be switched in). */
uint32_t md_code_end(const Md *m);
uint16_t md_read16(Md *m, uint32_t a);  /* a word of the 68000's space (DMA) */
static inline int md_sample_rate(const Md *m) { return m->pal ? 52781 : 53267; }  /* master / 1008 */
static inline uint64_t md_now(const Md *m) { return m->cpu.cycles * 7; }

#endif
