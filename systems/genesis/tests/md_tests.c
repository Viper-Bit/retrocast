/* Self-checks of the machine (tests/genesis/test_machine.py): a small ROM
 * made here, the 68000 looping on STOP, the checks poking the 68000's
 * bus directly. Covers the version register, work RAM mirrors, Z80 reset,
 * bus request and bank (a Z80 program reads ROM and work RAM through its
 * window and counts its vertical blank interrupts), 3- and 6-button pads,
 * battery RAM, TMSS; the VDP's ports, a DMA, both interrupts and a
 * plane tile and a sprite on screen; save states and the reset button;
 * the PSG's and the YM2612's pitch and level, the release, timer A, the DAC.
 * They check this code against the hardware facts in
 * systems/genesis/docs/roadmap.md, not against a console. Prints each failure;
 * exit code 0 when all pass. */
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "input_log.h"
#include "md.h"

static Md m;
static int failed;

#define CHECK(cond, ...) do { if (!(cond)) { printf("FAIL line %d: ", __LINE__); printf(__VA_ARGS__); printf("\n"); failed++; } } while (0)

static unsigned r8(uint32_t a) {
    uint16_t v = m68k_read(&m.cpu, a, 5, a & 1 ? 1 : 2);
    return a & 1 ? v & 0xFF : v >> 8;
}
static unsigned r16(uint32_t a) { return m68k_read(&m.cpu, a, 5, 3); }
static void w8(uint32_t a, unsigned v) { m68k_write(&m.cpu, a, (uint16_t)(v << 8 | v), 5, a & 1 ? 1 : 2); }
static void w16(uint32_t a, unsigned v) { m68k_write(&m.cpu, a, (uint16_t)v, 5, 3); }

static uint8_t rom[0x10000];
static void make_rom(const char *regions, int sram) {
    memset(rom, 0, sizeof rom);
    const uint8_t vec[8] = {0x00, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x02, 0x00};  /* SSP $FFFE00, PC $200 */
    memcpy(rom, vec, 8);
    memcpy(rom + 0x100, "SEGA GENESIS    ", 16);
    if (sram) memcpy(rom + 0x1B0, "RA\xF8\x20\x00\x20\x00\x01\x00\x20\x3F\xFF", 12);  /* odd bytes $200001-$203FFF */
    memcpy(rom + 0x1F0, regions, strlen(regions));
    static const uint8_t code[] = {
        0x46, 0xFC, 0x20, 0x00,                          /* $200: MOVE.W #$2000,SR (interrupts on) */
        0x4E, 0x72, 0x20, 0x00,                          /* $204: STOP #$2000 */
        0x52, 0x79, 0x00, 0xFF, 0x00, 0x14,              /* ADDQ.W #1,$FF0014: once per interrupt */
        0x60, 0xF4,                                      /* BRA.S $204 */
    }, vint[] = {0x52, 0x79, 0x00, 0xFF, 0x00, 0x10, 0x4E, 0x73},  /* ADDQ.W #1,$FF0010; RTE */
       hint[] = {0x52, 0x79, 0x00, 0xFF, 0x00, 0x12, 0x4E, 0x73};  /* ADDQ.W #1,$FF0012; RTE */
    memcpy(rom + 0x200, code, sizeof code);
    memcpy(rom + 0x300, vint, sizeof vint);
    memcpy(rom + 0x310, hint, sizeof hint);
    rom[0x72] = 0x03, rom[0x73] = 0x10;  /* level 4 autovector: $310 */
    rom[0x7A] = 0x03, rom[0x7B] = 0x00;  /* level 6: $300 */
}
static void load(const char *regions, int sram) {
    char err[64];
    md_free(&m);
    make_rom(regions, sram);
    if (md_load(&m, rom, sizeof rom, err, sizeof err)) { printf("load: %s\n", err); failed++; }
}

static void version(void) {
    load("U  ", 0);
    CHECK(r8(0xA10001) == 0xA0, "version (U) $%02X", r8(0xA10001));
    load("J  ", 0);
    CHECK(r8(0xA10001) == 0x20, "version (J) $%02X", r8(0xA10001));
    load("E  ", 0);
    CHECK(r8(0xA10001) == 0xE0 && m.pal, "version (E) $%02X", r8(0xA10001));
    load("4", 0);  /* the hex form: the Americas */
    CHECK(r8(0xA10001) == 0xA0, "version (4) $%02X", r8(0xA10001));
}

static void ram(void) {
    load("U", 0);
    w16(0xFF1234, 0xBEEF);
    CHECK(r16(0xE01234) == 0xBEEF && r16(0xFF1234) == 0xBEEF, "work RAM mirror $%04X", r16(0xE01234));
    w8(0xFF1235, 0x12);
    CHECK(r16(0xFF1234) == 0xBE12, "work RAM byte write $%04X", r16(0xFF1234));
    CHECK(r16(0x000100) == 0x5345, "ROM \"SE\" $%04X", r16(0x100));
}

static void z80(void) {
    static const uint8_t prog[] = {
        0x31, 0x00, 0x20,              /* LD SP,$2000 */
        0xED, 0x56,                    /* IM 1 */
        0x3A, 0x00, 0x81,              /* LD A,($8100): ROM $000100 through bank 0 */
        0x32, 0x00, 0x10,              /* LD ($1000),A */
        0x21, 0x00, 0x60,              /* LD HL,$6000 */
        0x36, 0x00,                    /* bank bits, low first: $1FE = $FF0000 >> 15 */
        0x36, 0x01, 0x36, 0x01, 0x36, 0x01, 0x36, 0x01, 0x36, 0x01, 0x36, 0x01, 0x36, 0x01, 0x36, 0x01,
        0x3A, 0x00, 0x80,              /* LD A,($8000): work RAM $FF0000 */
        0x32, 0x02, 0x10,              /* LD ($1002),A */
        0xFB,                          /* EI */
        0x18, 0xFE,                    /* JR $ */
    };
    /* $38: INC ($1001), wait out the INT pulse (DJNZ 256 times), EI, RETI */
    static const uint8_t isr[] = {0x21, 0x01, 0x10, 0x34, 0x06, 0x00, 0x10, 0xFE, 0xFB, 0xED, 0x4D};
    load("U", 0);
    w8(0xFF0000, 0x5A);
    CHECK(r16(0xA11100) & 0x100, "bus request reads granted at power-on");
    w16(0xA11100, 0x100);                 /* request the bus; the Z80 is still in reset */
    for (unsigned i = 0; i < sizeof prog; i++) w8(0xA00000 + i, prog[i]);
    for (unsigned i = 0; i < sizeof isr; i++) w8(0xA00038 + i, isr[i]);
    CHECK(r8(0xA00005) == 0x3A && r8(0xA02005) == 0x3A, "Z80 RAM and its mirror");
    w16(0xA11200, 0x100);                 /* out of reset */
    CHECK(!(r16(0xA11100) & 0x100), "bus request not granted");
    w16(0xA11100, 0);                     /* the Z80 runs */
    CHECK(r16(0xA11100) & 0x100, "the Z80 runs but its bus reads granted");
    w8(0xA01000, 0xEE);                   /* without the bus: dropped */
    for (int f = 0; f < 3; f++) md_run_frame(&m);
    w16(0xA11100, 0x100);
    CHECK(r8(0xA01000) == 'S', "Z80 read of ROM through its window: $%02X", r8(0xA01000));
    CHECK(r8(0xA01002) == 0x5A, "Z80 read of work RAM through bank $1FE: $%02X", r8(0xA01002));
    CHECK(m.z80_bank == 0x1FE, "bank $%03X", m.z80_bank);
    CHECK(r8(0xA01001) == 3, "vertical blank interrupts in 3 frames: %u", r8(0xA01001));
    w16(0xA11200, 0);                     /* reset: the Z80 starts over */
    CHECK(m.z80.pc == 0 && m.z80.sp == 0xFFFF, "Z80 reset");
}

static void pads(void) {
    load("U", 0);
    m.pad[0] = PAD_B | PAD_UP | PAD_START;
    w8(0xA10009, 0x40);                    /* TH an output */
    w8(0xA10003, 0x40);
    CHECK((r8(0xA10003) & 0x7F) == 0x6E, "TH 1: ?1CBRLDU $%02X", r8(0xA10003));
    w8(0xA10003, 0x00);
    CHECK((r8(0xA10003) & 0x7F) == 0x12, "TH 0: ?0SA00DU $%02X", r8(0xA10003));
    CHECK((r8(0xA10005) & 0x3F) == 0x3F, "pad 2 idle $%02X", r8(0xA10005));
    w8(0xA10003, 0x40);
    m.pad6[0] = 1;
    m.pad[0] = PAD_X | PAD_A;              /* Y and C */
    md_run_frame(&m);                      /* longer than the 6-button timeout */
    static const uint8_t want[] = {0x33, 0x5F, 0x33, 0x5F, 0x30, 0x5D, 0x3F, 0x5F, 0x33, 0x5F};
    for (int i = 0; i < 10; i++) {         /* from TH 1: the mark on the third 0, X Y Z on the 1 after it, then over */
        w8(0xA10003, i & 1 ? 0x40 : 0x00);
        CHECK((r8(0xA10003) & 0x7F) == want[i], "6-button step %d: $%02X, want $%02X", i, r8(0xA10003) & 0x7F, want[i]);
    }
}

static void sram(void) {
    load("U", 1);
    CHECK(m.sram && m.sram_start == 0x200000, "battery RAM from the header");
    w8(0x200001, 0x42);
    CHECK(r8(0x200001) == 0x42, "battery RAM write $%02X", r8(0x200001));
    w8(0xA130F1, 2);                       /* write protect */
    w8(0x200001, 0x43);
    CHECK(r8(0x200001) == 0x42, "battery RAM protected");
}

/* ---- serial EEPROM (I2C), driven bit by bit as the games do ---- */
typedef struct { uint32_t sda_out, scl, sda_in; unsigned sda_out_bit, scl_bit, sda_in_bit; } Wiring;
static Wiring wire;
static uint8_t latch[2];  /* what the game last wrote to $200000 / $200001 */
static void lines(int scl, int sda) {
    latch[wire.scl & 1] = (uint8_t)((latch[wire.scl & 1] & ~(1u << wire.scl_bit)) | (unsigned)scl << wire.scl_bit);
    latch[wire.sda_out & 1] = (uint8_t)((latch[wire.sda_out & 1] & ~(1u << wire.sda_out_bit)) | (unsigned)sda << wire.sda_out_bit);
    w8(0x200000, latch[0]);
    w8(0x200001, latch[1]);
}
static int sda_in(void) { return r8(wire.sda_in) >> wire.sda_in_bit & 1; }
static void i2c_start(void) { lines(1, 1); lines(1, 0); lines(0, 0); }
static void i2c_stop(void) { lines(0, 0); lines(1, 0); lines(1, 1); }
static int i2c_send(unsigned byte) {  /* returns the chip's ack (1: acked) */
    for (int i = 7; i >= 0; i--) { int b = byte >> i & 1; lines(0, b); lines(1, b); lines(0, b); }
    lines(0, 1); lines(1, 1);
    int ack = !sda_in();
    lines(0, 1);
    return ack;
}
static unsigned i2c_recv(int ack) {
    unsigned v = 0;
    lines(0, 1);
    for (int i = 0; i < 8; i++) { lines(1, 1); v = v << 1 | (unsigned)sda_in(); lines(0, 1); }
    lines(0, !ack); lines(1, !ack); lines(0, !ack);
    return v;
}
static void load_eeprom(const char *code, int flag) {
    char err[64];
    md_free(&m);
    make_rom("U", 0);
    memcpy(rom + 0x180, code, 14);
    if (flag) memcpy(rom + 0x1B0, "RA\xE8\x40\x00\x20\x00\x01\x00\x20\x00\x01", 12);
    if (md_load(&m, rom, sizeof rom, err, sizeof err)) { printf("load: %s\n", err); failed++; }
    latch[0] = latch[1] = 0xFF;
}

static void eeprom(void) {
    /* Sega's wiring (Evander Holyfield's Boxing): $200001 bit 0 SDA, bit 1 SCL; a 24C01 in mode 1
       (the first byte is the 7-bit address and the read bit, no device select) */
    wire = (Wiring){0x200001, 0x200001, 0x200001, 0, 1, 0};
    load_eeprom("GM MK-1215 -00", 1);
    CHECK(!m.sram && m.eeprom.size == 128, "Evander: a 24C01, not battery RAM (size %u)", m.eeprom.size);
    i2c_start();
    CHECK(i2c_send(0x10 << 1), "mode 1: address acked");
    CHECK(i2c_send(0x5A) && i2c_send(0xA5), "mode 1: data acked");
    i2c_stop();
    i2c_start(); i2c_send(0x10 << 1 | 1);
    unsigned a = i2c_recv(1), b = i2c_recv(0);
    i2c_stop();
    CHECK(a == 0x5A && b == 0xA5, "mode 1 read back %02X %02X", a, b);
    /* a page of 4 bytes: the fifth write wraps to the page's start */
    i2c_start(); i2c_send(0x20 << 1);
    for (unsigned i = 0; i < 5; i++) i2c_send(i + 1);
    i2c_stop();
    CHECK(m.eeprom.mem[0x20] == 5 && m.eeprom.mem[0x21] == 2 && m.eeprom.mem[0x24] != 5, "page wrap: %u %u",
          m.eeprom.mem[0x20], m.eeprom.mem[0x21]);
    /* an unknown game with the header's EEPROM flag: Sega's wiring */
    load_eeprom("GM T-99999 -00", 1);
    CHECK(m.eeprom.size == 128, "flagged, unknown: a 24C01 on Sega's wiring");

    /* Acclaim's (NBA Jam TE): SCL $200000 bit 0, SDA $200001 bit 0; a 24C04, device select, then a random read */
    wire = (Wiring){0x200001, 0x200000, 0x200001, 0, 0, 0};
    load_eeprom("GM T-81406 -00", 0);
    CHECK(m.eeprom.size == 512, "NBA Jam TE: a 24C04 (size %u)", m.eeprom.size);
    i2c_start();
    CHECK(i2c_send(0xA2) && i2c_send(0x33) && i2c_send(0x77), "24C04: block 1, address $33, data");
    i2c_stop();
    CHECK(m.eeprom.mem[0x133] == 0x77, "24C04 write at $133");
    i2c_start(); i2c_send(0xA2); i2c_send(0x33);   /* the address, then a restart to read */
    i2c_start(); i2c_send(0xA3);
    a = i2c_recv(0);
    i2c_stop();
    CHECK(a == 0x77, "24C04 random read %02X", a);
    i2c_start();
    CHECK(!i2c_send(0x50), "not $Ax: no ack");
    i2c_stop();

    /* College Slam: the same wiring, a 24C65: two address bytes */
    load_eeprom("GM T-81576 -00", 1);
    CHECK(m.eeprom.size == 8192, "College Slam: a 24C65 (size %u)", m.eeprom.size);
    i2c_start(); i2c_send(0xA0); i2c_send(0x12); i2c_send(0x34); i2c_send(0x99); i2c_stop();
    CHECK(m.eeprom.mem[0x1234] == 0x99, "24C65 write at $1234");

    /* EA's (NHLPA Hockey 93, no header flag): $200001 bit 7 SDA, bit 6 SCL */
    wire = (Wiring){0x200001, 0x200001, 0x200001, 7, 6, 7};
    load_eeprom("GM T-50396 -00", 0);
    CHECK(m.eeprom.size == 128, "NHLPA 93: a 24C01");
    i2c_start(); i2c_send(0xA0); i2c_send(0x05); i2c_send(0x66); i2c_stop();
    i2c_start(); i2c_send(0xA0); i2c_send(0x05); i2c_start(); i2c_send(0xA1);
    a = i2c_recv(0);
    i2c_stop();
    CHECK(a == 0x66, "EA wiring read back %02X", a);

    load("U", 0);
    CHECK(!m.eeprom.size, "no EEPROM without the flag or a listed game");
}

static void tmss(void) {
    load("U", 0);
    w16(0xC00004, 0x8104);
    CHECK(!m.tmss_locked && m.vdp_writes == 1, "VDP locked on a console without TMSS");
    load("U", 0);
    m.io[0] |= 1;                          /* a console with TMSS */
    w16(0xC00004, 0x8104);
    CHECK(m.tmss_locked && m.cpu.halted && !m.vdp_writes, "VDP not locked before \"SEGA\"");
    load("U", 0);
    m.io[0] |= 1;
    w16(0xA14000, 0x5345), w16(0xA14002, 0x4741);
    w16(0xC00004, 0x8104);
    CHECK(!m.tmss_locked && m.vdp_writes == 1, "VDP locked after \"SEGA\"");
}

/* A command word pair: target (1 VRAM, 3 CRAM, 5 VSRAM write; 0 VRAM read) and address; dma: CD5. */
static void cmd(unsigned code, unsigned a, int dma) {
    w16(0xC00004, (code & 3) << 14 | (a & 0x3FFF));
    w16(0xC00004, (code & 0x3C) << 2 | (dma ? 0x80 : 0) | a >> 14);
}

static void vdp(void) {
    load("U", 0);
    static const unsigned regs[] = {0x8004, 0x8114, 0x8230, 0x8407, 0x8578, 0x8C81, 0x8D3F, 0x8F02, 0x9000};
    for (unsigned i = 0; i < sizeof regs / sizeof *regs; i++) w16(0xC00004, regs[i]);
    cmd(1, 0x0000, 0);
    w16(0xC00000, 0x1234), w16(0xC00000, 0x5678);
    cmd(0, 0x0000, 0);
    CHECK(r16(0xC00000) == 0x1234 && r16(0xC00000) == 0x5678, "VRAM through the data port, increment 2");
    cmd(1, 0x0000, 0), w16(0xC00000, 0), w16(0xC00000, 0);  /* tile 0 blank again: the empty cells show it */
    cmd(3, 0x0022, 0);
    w16(0xC00000, 0xFFFF);
    CHECK(m.vdp.cram[0x11] == 0x0EEE, "CRAM keeps 9 bits: $%04X", m.vdp.cram[0x11]);
    /* DMA: 16 words of $11 from work RAM to tile 1 */
    for (int i = 0; i < 32; i++) w8(0xFF0100 + (unsigned)i, 0x11);
    static const unsigned dma[] = {0x9310, 0x9400, 0x9580, 0x9680, 0x977F};  /* 16 words from $FF0100 */
    for (unsigned i = 0; i < 5; i++) w16(0xC00004, dma[i]);
    uint64_t before = m.cpu.cycles;
    cmd(1, 0x0020, 1);
    CHECK(m.vdp.vram[0x20] == 0x11 && m.vdp.vram[0x3F] == 0x11 && m.vdp.vram[0x40] == 0, "DMA to VRAM");
    CHECK(m.cpu.cycles > before, "the 68000 waits for the DMA");
    /* the picture: plane A cell (0,0) = tile 1 in red; sprite 0 = tile 1, palette 1 (green), at (16, 16) */
    cmd(3, 0x0002, 0), w16(0xC00000, 0x000E);
    cmd(3, 0x0022, 0), w16(0xC00000, 0x00E0);
    cmd(1, 0xC000, 0), w16(0xC00000, 0x0001);
    cmd(1, 0xF000, 0);
    w16(0xC00000, 0x0090), w16(0xC00000, 0x0000), w16(0xC00000, 0x2001), w16(0xC00000, 0x0090);
    w16(0xC00004, 0x8174);                 /* display, VINT, DMA on */
    w16(0xC00004, 0x8014), w16(0xC00004, 0x8A00);  /* HINT every line */
    md_run_frame(&m);
    md_run_frame(&m);
    const uint32_t *f = m.vdp.frame;
    CHECK(m.vdp.frame_w == 320 && m.vdp.frame_h == 224, "H40 V28 frame %dx%d", m.vdp.frame_w, m.vdp.frame_h);
    CHECK(f[0] == 0xFF0000 && f[7 * 320 + 7] == 0xFF0000, "plane A tile: $%06X", f[0]);
    CHECK(f[8] == 0 && f[8 * 320] == 0, "plane A beside the tile: $%06X", f[8]);
    CHECK(f[16 * 320 + 16] == 0x00FF00 && f[23 * 320 + 23] == 0x00FF00 && f[24 * 320 + 24] == 0, "sprite: $%06X",
          f[16 * 320 + 16]);
    CHECK(r16(0xFF0010) == 2, "vertical interrupts in 2 frames: %u", r16(0xFF0010));
    CHECK(r16(0xFF0012) == 2 * 225, "horizontal interrupts in 2 frames: %u", r16(0xFF0012));
    /* one wake per interrupt but at line 224, where H and V come together in this line-step model */
    CHECK(r16(0xFF0014) == 2 * 225, "STOP resumed after the interrupt: %u", r16(0xFF0014));
    CHECK((r16(0xC00004) & 0x0201) == 0x0200, "status: FIFO empty, NTSC $%04X", r16(0xC00004));
}

/* n sample frames from now; their left channel in buf */
static float snd[SND_BUF];
static int sound_run(int n) {
    static float buf[2 * SND_BUF];
    snd_take(&m.snd, buf, SND_BUF);
    snd_run(&m, m.snd.next + (uint64_t)(n - 1) * SND_SAMPLE_CLOCKS);
    n = snd_take(&m.snd, buf, SND_BUF);
    for (int i = 0; i < n; i++) snd[i] = buf[2 * i];
    return n;
}
/* Hz from the first to the last rising zero crossing */
static double pitch(int n) {
    int first = -1, last = -1, count = 0;
    for (int i = 1; i < n; i++)
        if (snd[i - 1] < 0 && snd[i] >= 0) {
            if (first < 0) first = i;
            last = i, count++;
        }
    return count > 1 ? (count - 1) * (double)md_sample_rate(&m) / (last - first) : 0;
}
static float peak(int n) {
    float p = 0;
    for (int i = 0; i < n; i++) p = snd[i] > p ? snd[i] : -snd[i] > p ? -snd[i] : p;
    return p;
}
#define YM_GOLDEN 0xA0209A86u
static void ym(unsigned reg, unsigned v) { w8(0xA04000, reg), w8(0xA04001, v); }

static void sound(void) {
    load("U", 0);
    w8(0xC00011, 0x80), w8(0xC00011, 0x10), w8(0xC00011, 0x90);  /* PSG tone 0: period $100, loudest */
    int n = sound_run(4000);
    double f = pitch(n), want = 53693175.0 / 15 / 32 / 256;
    CHECK(n == 4000 && f > want - 0.5 && f < want + 0.5, "PSG tone: %.2f Hz, want %.2f", f, want);
    w8(0xC00011, 0x9F);                    /* off */
    w16(0xA11100, 0x100), w16(0xA11200, 0x100);  /* the Z80's bus, for the YM2612 */
    ym(0xB0, 0x07), ym(0xB4, 0xC0);        /* channel 1: algorithm 7, both sides */
    ym(0x30, 0x01), ym(0x40, 0x00), ym(0x50, 0x1F), ym(0x60, 0), ym(0x70, 0), ym(0x80, 0x0F);  /* S1 alone */
    ym(0x44, 0x7F), ym(0x48, 0x7F), ym(0x4C, 0x7F);
    ym(0xA4, 4 << 3 | 1000 >> 8), ym(0xA0, 1000 & 0xFF);  /* block 4, F-number 1000 */
    ym(0x28, 0x10);                        /* key on S1 */
    n = sound_run(4000);
    want = 1000 * 8 * md_sample_rate(&m) / 1048576.0;
    f = pitch(n);
    CHECK(f > want - 0.5 && f < want + 0.5, "YM2612 sine: %.2f Hz, want %.2f", f, want);
    CHECK(peak(n) > 0.3f && peak(n) < 0.34f, "YM2612 sine at full: peak %.3f", peak(n));
    ym(0x28, 0x00);                        /* key off: release rate 15 */
    sound_run(1000);                       /* 1023 / 8 every third sample: about 400 samples */
    sound_run(1000);
    CHECK(peak(1000) < 0.001f && m.snd.ym.ch[0].op[0].att == 0x3FF, "YM2612 release: peak %.4f", peak(1000));
    ym(0x24, 924 >> 2), ym(0x25, 924 & 3), ym(0x27, 0x05);  /* timer A: 100 samples, flag on */
    uint64_t t = m.snd.next;
    CHECK(ym_read(&m, t + 98 * SND_SAMPLE_CLOCKS) == 0, "timer A early");
    CHECK(ym_read(&m, t + 99 * SND_SAMPLE_CLOCKS) == 1, "timer A after 100 samples");
    CHECK(r8(0xA04000) == 1, "YM2612 status through the 68000's window");
    ym(0x27, 0x15);
    CHECK(r8(0xA04000) == 0, "timer A flag reset");
    ym(0x2B, 0x80), ym(0x2A, 0xFF);       /* DAC on channel 6 */
    sound_run(10);
    CHECK(snd[0] > 0.3f, "DAC $FF: %.3f", snd[0]);
}

/* A state saved, two frames run, the state loaded: the same two frames again. */
static void states(const char *path) {
    static Md after;
    CHECK(md_state_save(&m, path) == 0, "state save");
    md_run_frame(&m), md_run_frame(&m);
    after = m;
    char err[64] = "";
    CHECK(md_state_load(&m, path, err, sizeof err) == 0, "state load: %s", err);
    CHECK(m.frame_count + 2 == after.frame_count, "state load: frame %u", m.frame_count);
    md_run_frame(&m), md_run_frame(&m);
    CHECK(!memcmp(m.wram, after.wram, sizeof m.wram) && !memcmp(m.vdp.frame, after.vdp.frame, sizeof m.vdp.frame) &&
          m.cpu.cycles == after.cpu.cycles, "the frames after a loaded state differ");
    rom[0x300] ^= 1;  /* another game */
    static Md other;
    md_load(&other, rom, sizeof rom, err, sizeof err);
    CHECK(md_state_load(&other, path, err, sizeof err) != 0, "a state loaded into another game");
    md_free(&other);
    remove(path);
    uint16_t count = (uint16_t)r16(0xFF0010);
    md_reset(&m);
    CHECK(m.cpu.pc == 0x204 && r16(0xFF0010) == count && !m.z80_run, "reset: pc $%06X", m.cpu.pc);
}

/* The YM2612's samples for a fixed program, pinned: moving the operator
 * (core/audio/fm.c) must not change one bit. */
static void ym_golden(void) {
    load("U", 0);
    for (int c = 0; c < 4; c++) w8(0xC00011, (uint8_t)(0x9F | c << 5));  /* the PSG silent: only the integer FM path */
    static const uint8_t ops[4][7] = {  /* DT/MUL, TL, KS/AR, AM/DR, SR, SL/RR per operator */
        {0x71, 0x23, 0x5F, 0x8C, 0x05, 0x27}, {0x02, 0x10, 0x1F, 0x05, 0x02, 0x1A},
        {0x34, 0x2C, 0x9A, 0x0A, 0x03, 0x45}, {0x01, 0x00, 0x1F, 0x86, 0x04, 0x1F}};
    ym(0x22, 0x0B);                              /* the LFO on */
    for (int ch = 0; ch < 2; ch++) {
        for (int o = 0; o < 4; o++)
            for (int r = 0; r < 6; r++) ym(0x30 + r * 0x10 + o * 4 + ch, ops[o][r]);
        ym(0xB0 + ch, ch ? 0x07 : 0x2C);         /* algorithm 4 with feedback 5; algorithm 7 */
        ym(0xB4 + ch, 0xF5);                     /* both sides, AMS 3, FMS 5 */
        ym(0xA4 + ch, 0x22 + ch), ym(0xA0 + ch, 0x69);
        ym(0x28, 0xF0 | ch);                     /* key on */
    }
    uint32_t h = 2166136261u;
    for (int part = 0; part < 2; part++) {
        int n = sound_run(4096);
        for (int i = 0; i < n; i++) {  /* 16-bit integers: the same on every compiler and C library */
            uint16_t v = (uint16_t)(int16_t)lrintf(snd[i] * 32767);
            h = (h ^ (v & 0xFF)) * 16777619u, h = (h ^ (v >> 8)) * 16777619u;
        }
        if (part == 0) CHECK(peak(n) > 0.05f, "YM2612 program silent: %f", peak(n));
        if (part == 0) ym(0x28, 0x00), ym(0x28, 0x01);  /* key off */
    }
    CHECK(h == YM_GOLDEN, "YM2612 samples changed: hash %08X", (unsigned)h);
}

int main(int argc, char **argv) {
    (void)argc;
    version();
    ram();
    z80();
    pads();
    sram();
    eeprom();
    tmss();
    vdp();
    sound();
    ym_golden();
    char path[1024];
    snprintf(path, sizeof path, "%s.state", argv[0]);  /* next to the program */
    states(path);
    md_free(&m);
    printf(failed ? "%d failed\n" : "all passed\n", failed);
    return failed != 0;
}
