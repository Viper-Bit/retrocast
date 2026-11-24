/* CPS-1 self-checks: matching a zip to the game table and the load layouts
 * (with a test-only game), the detector, and the machine: VBlank, inputs,
 * the CPS-B ID and multiplier, unmapped reads; the palette, the three
 * scroll layers, sprites and priority. */
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "cps1.h"
#include "detect.h"
#include "input_log.h"
#include "oki6295.h"
#include "ym2151.h"

extern const SystemDetector cps1_detector;

/* ---- a stored-only zip built in memory ---- */

static uint8_t zbuf[1 << 21];
static size_t zlen;
static struct { const char *name; const uint8_t *data; uint32_t size, header; } zent[16];
static int zcount;

static void put16(uint8_t *p, uint32_t v) { p[0] = (uint8_t)v, p[1] = (uint8_t)(v >> 8); }
static void put32(uint8_t *p, uint32_t v) { put16(p, v), put16(p + 2, v >> 16); }

static void zip_add(const char *name, const uint8_t *data, uint32_t size) {
    zent[zcount].name = name, zent[zcount].data = data, zent[zcount].size = size, zent[zcount].header = (uint32_t)zlen;
    zcount++;
}

static size_t zip_build(void) {  /* local headers and data, the directory, the end record */
    zlen = 0;
    for (int i = 0; i < zcount; i++) {
        uint8_t *h = zbuf + zlen;
        size_t n = strlen(zent[i].name);
        memset(h, 0, 30);
        put32(h, 0x04034B50u), put32(h + 14, zip_crc32(zent[i].data, zent[i].size));
        put32(h + 18, zent[i].size), put32(h + 22, zent[i].size), put16(h + 26, (uint32_t)n);
        zent[i].header = (uint32_t)zlen;
        memcpy(h + 30, zent[i].name, n), memcpy(h + 30 + n, zent[i].data, zent[i].size);
        zlen += 30 + n + zent[i].size;
    }
    size_t dir = zlen;
    for (int i = 0; i < zcount; i++) {
        uint8_t *h = zbuf + zlen;
        size_t n = strlen(zent[i].name);
        memset(h, 0, 46);
        put32(h, 0x02014B50u), put32(h + 16, zip_crc32(zent[i].data, zent[i].size));
        put32(h + 20, zent[i].size), put32(h + 24, zent[i].size), put16(h + 28, (uint32_t)n);
        put32(h + 42, zent[i].header);
        memcpy(h + 46, zent[i].name, n);
        zlen += 46 + n;
    }
    uint8_t *e = zbuf + zlen;
    memset(e, 0, 22);
    put32(e, 0x06054B50u), put16(e + 8, (uint32_t)zcount), put16(e + 10, (uint32_t)zcount);
    put32(e + 12, (uint32_t)(zlen - dir)), put32(e + 16, (uint32_t)dir);
    zlen += 22;
    return zlen;
}

/* ---- a test game: one file of each layout ---- */

static uint8_t even[4] = {1, 2, 5, 6}, odd[4] = {3, 4, 7, 8}, swapped[4] = {0x22, 0x11, 0x44, 0x33};
static uint8_t gfx[2][4] = {{0xA0, 0xA1, 0xA2, 0xA3}, {0xB0, 0xB1, 0xB2, 0xB3}}, plain[3] = {9, 8, 7};
static Cps1Game test_game = {"test", "Test", CPS1_PLAIN, {16, 16, 3, 0}, {0}, 6, {{0}}, {{0}, 0, {{0}}}, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0};

static void make_test_game(void) {
    Cps1File f[6] = {
        {zip_crc32(even, 4), 4, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0, 0},
        {zip_crc32(odd, 4), 4, CPS1_R_MAIN, CPS1_LOAD_ODD, 1, 0},
        {zip_crc32(swapped, 4), 4, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 8, 0},
        {zip_crc32(gfx[0], 4), 4, CPS1_R_GFX, CPS1_LOAD_GFX4, 0, 0},
        {zip_crc32(gfx[1], 4), 4, CPS1_R_GFX, CPS1_LOAD_GFX4, 6, 0},
        {zip_crc32(plain, 3), 3, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0, 0},
    };
    memcpy(test_game.files, f, sizeof f);
}

static void zip_test_game(int skip) {
    static const char *names[6] = {"even", "odd", "swapped", "gfx0", "gfx1", "plain"};
    const uint8_t *data[6] = {even, odd, swapped, gfx[0], gfx[1], plain};
    static const uint8_t pal[279] = {0};
    zcount = 0;
    zip_add("buf1", pal, sizeof pal);  /* a PAL dump the table does not list */
    for (int i = 0; i < 6; i++)
        if (i != skip) zip_add(names[i], data[i], test_game.files[i].size);
    zip_build();
}

static void test_layouts(void) {
    Zip z;
    Cps1Rom r;
    char err[128];
    zip_test_game(-1);
    assert(zip_open(&z, zbuf, zlen) == 0);
    assert(cps1_match_in(&z, &test_game, 1) == &test_game);
    assert(cps1_load(&test_game, &z, &r, err, sizeof err) == 0);
    static const uint8_t main_[16] = {1, 3, 2, 4, 5, 7, 6, 8, 0x11, 0x22, 0x33, 0x44, 0, 0, 0, 0};
    assert(r.size[CPS1_R_MAIN] == 16 && memcmp(r.region[CPS1_R_MAIN], main_, 16) == 0);
    static const uint8_t gfx_[16] = {0xA0, 0xA1, 0, 0, 0, 0, 0xB0, 0xB1, 0xA2, 0xA3, 0, 0, 0, 0, 0xB2, 0xB3};
    assert(memcmp(r.region[CPS1_R_GFX], gfx_, 16) == 0);
    assert(memcmp(r.region[CPS1_R_SOUND], plain, 3) == 0);
    assert(r.size[CPS1_R_OKI] == 0);
    cps1_unload(&r);
    zip_close(&z);
}

static void test_missing(void) {
    Zip z;
    Cps1Rom r;
    char err[128] = "";
    zip_test_game(2);
    assert(zip_open(&z, zbuf, zlen) == 0);
    assert(cps1_match_in(&z, &test_game, 1) == NULL);
    assert(cps1_load(&test_game, &z, &r, err, sizeof err) == -1);
    char crc[16];
    snprintf(crc, sizeof crc, "%08x", (unsigned)test_game.files[2].crc);
    assert(strstr(err, crc));
    zip_close(&z);
}

static void test_detector(void) {
    static uint8_t junk[1 << 20];
    for (size_t i = 0; i < sizeof junk; i++) junk[i] = (uint8_t)(i * 2654435761u >> 13);
    zcount = 0;
    zip_add("game.bin", junk, sizeof junk);
    zip_build();
    assert(cps1_detector.score(zbuf, zlen) == 0);
    assert(cps1_detector.score(junk, sizeof junk) == 0);  /* not a zip at all */
}

/* ---- the machine, on a hand-assembled program ---- */

static Cps1 m;
static uint8_t prog[1 << 20];
static Cps1Game prog_game = {"prog", "Program", CPS1_PLAIN, {1 << 20, 0, 0, 0},
                             {0x20, 0x0004, 0x00, 0x02, 0x04, 0x06, 0x2E, {0x26, 0x28, 0x2A, 0x2C}, 0x30, {0}}, 0, {{0}}, {{0}, 0, {{0}}}, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0};
static Cps1Rom prog_rom;

static void w16(uint32_t a, uint16_t v) { prog[a] = (uint8_t)(v >> 8), prog[a + 1] = (uint8_t)v; }

static void boot_program(void) {
    memset(prog, 0, sizeof prog);
    w16(0, 0x00FF), w16(2, 0x8000);              /* SSP $FF8000 */
    w16(4, 0x0000), w16(6, 0x0400);              /* PC $400 */
    w16(26 * 4, 0x0000), w16(26 * 4 + 2, 0x0500);  /* level 2 autovector: $500 */
    static const uint16_t main_[] = {0x46FC, 0x2000,                       /* move #$2000,sr */
                                     0x33F9, 0x0080, 0x0000, 0x00FF, 0x0002,  /* move.w $800000,$FF0002 */
                                     0x60F4};                              /* bra.s the move */
    for (unsigned i = 0; i < sizeof main_ / 2; i++) w16(0x400 + i * 2, main_[i]);
    static const uint16_t irq[] = {0x5279, 0x00FF, 0x0000, 0x4E73};      /* addq.w #1,$FF0000; rte */
    for (unsigned i = 0; i < sizeof irq / 2; i++) w16(0x500 + i * 2, irq[i]);
    prog_rom.game = &prog_game;
    prog_rom.region[CPS1_R_MAIN] = prog;
    prog_rom.size[CPS1_R_MAIN] = sizeof prog;
    cps1_init(&m, &prog_rom);
}

static uint16_t ram16(uint32_t a) { return (uint16_t)(m.ram[a & 0xFFFF] << 8 | m.ram[(a + 1) & 0xFFFF]); }

static void test_vblank(void) {
    boot_program();
    for (int i = 0; i < 3; i++) cps1_frame(&m);
    assert(ram16(0xFF0000) == 3);
}

/* ---- recompiled code (recomp_rt.h): a stand-in program whose one block
 * runs one interpreted step and counts its calls ---- */
static int block_calls;
static void test_block(M68k *c) { block_calls++, m68k_step(c); }
static Cps1RecompFn test_lookup(uint32_t at) { (void)at; return test_block; }
static Cps1RecompProgram test_program = {0, "prog", test_lookup};

static void test_recomp_gate(void) {  /* the program runs only on the code it was made from */
    boot_program();
    test_program.rom_hash = cps1_code_hash(&prog_rom);
    cps1_init_with(&m, &prog_rom, &test_program);
    assert(m.recomp_on);
    block_calls = 0;
    for (int i = 0; i < 3; i++) cps1_frame(&m);
    assert(block_calls > 0 && ram16(0xFF0000) == 3);
    test_program.rom_hash ^= 1;  /* another game's */
    cps1_init_with(&m, &prog_rom, &test_program);
    assert(!m.recomp_on);
    block_calls = 0;
    for (int i = 0; i < 3; i++) cps1_frame(&m);
    assert(block_calls == 0 && ram16(0xFF0000) == 3);
}

static void test_recomp_state(void) {  /* a state from the interpreter, loaded with recompiled code: still on */
    boot_program();  /* recomp_none.c: off */
    cps1_frame(&m);
    const char *path = "cps1_recomp_state.tmp";
    assert(!cps1_state_save(&m, path));
    test_program.rom_hash = cps1_code_hash(&prog_rom);
    cps1_init_with(&m, &prog_rom, &test_program);
    static uint8_t misses[16];
    m.misses = misses;
    char err[256];
    assert(!cps1_state_load(&m, path, err, sizeof err));
    assert(m.recomp_on && m.misses == misses && m.recomp == &test_program);
    remove(path);
}

static void test_inputs(void) {
    boot_program();
    cps1_frame(&m);
    assert(ram16(0xFF0002) == 0xFFFF);           /* nothing pressed: all high */
    cps1_set_input(&m, 0, PAD_RIGHT | PAD_B);
    cps1_set_input(&m, 1, PAD_UP);
    cps1_frame(&m);
    assert(ram16(0xFF0002) == (uint16_t)~(0x01 | 0x10 | 0x0800));  /* P1 right, button 1; P2 up */
    cps1_set_input(&m, 0, PAD_START | PAD_SELECT);
    assert((m68k_read(&m.cpu, 0x800018, 5, 3) >> 8) == (uint8_t)~(0x10 | 0x01));  /* start 1, coin 1 */
}

static void test_cpsb(void) {
    boot_program();
    assert(m68k_read(&m.cpu, 0x800140 + 0x20, 5, 3) == 0x0004);  /* the ID port */
    m68k_write(&m.cpu, 0x800140 + 0x00, 300, 5, 3);
    m68k_write(&m.cpu, 0x800140 + 0x02, 400, 5, 3);
    uint32_t p = (uint32_t)m68k_read(&m.cpu, 0x800140 + 0x06, 5, 3) << 16 | m68k_read(&m.cpu, 0x800140 + 0x04, 5, 3);
    assert(p == 120000);
}

static void test_cpsb_high(void) {  /* Street Fighter II revision E: the CPS-B at $8001C0, nothing at $800140 */
    boot_program();
    prog_game.cpsb_high = 1;
    cps1_init(&m, &prog_rom);
    assert(m68k_read(&m.cpu, 0x8001C0 + 0x20, 5, 3) == 0x0004);  /* the ID port */
    assert(m68k_read(&m.cpu, 0x800140 + 0x20, 5, 3) == 0xFFFF);
    m68k_write(&m.cpu, 0x8001C0 + 0x2E, 0x1234, 5, 3);
    assert(m.cpsb[0x2E >> 1] == 0x1234);
    prog_game.cpsb_high = 0;
}

static void test_unmapped(void) {
    boot_program();
    assert(m68k_read(&m.cpu, 0x600000, 5, 3) == 0xFFFF);
    m68k_write(&m.cpu, 0x900010, 0xABCD, 5, 3);  /* graphics RAM is RAM */
    assert(m68k_read(&m.cpu, 0x900010, 5, 3) == 0xABCD);
}

static void test_byte_writes(void) {  /* a byte write keeps the register's other byte */
    boot_program();
    m68k_write(&m.cpu, 0x800110, 0x1234, 5, 3);
    m68k_write(&m.cpu, 0x800111, 0x5656, 5, 1);   /* lower byte only */
    assert(m.cpsa[0x10 >> 1] == 0x1256);
    m68k_write(&m.cpu, 0x80016E, 0xABCD, 5, 3);
    m68k_write(&m.cpu, 0x80016E, 0x7777, 5, 2);   /* upper byte only */
    assert(m.cpsb[0x2E >> 1] == 0x77CD);
}

/* ---- video ---- */

static uint8_t gfxrom[1 << 20];

static void boot_video(void) {
    boot_program();
    memset(gfxrom, 0xFF, sizeof gfxrom);  /* every pen 15: transparent */
    prog_rom.region[CPS1_R_GFX] = gfxrom;
    prog_rom.size[CPS1_R_GFX] = sizeof gfxrom;
    prog_game.b.layer_enable[0] = 0x02, prog_game.b.layer_enable[1] = 0x04, prog_game.b.layer_enable[2] = 0x08;
}

static void cpsa(unsigned off, uint16_t v) { m68k_write(&m.cpu, 0x800100 + off, v, 5, 3); }
static void cpsb(unsigned off, uint16_t v) { m68k_write(&m.cpu, 0x800140 + off, v, 5, 3); }
static void gram(uint32_t off, uint16_t v) { m68k_write(&m.cpu, 0x900000 + off, v, 5, 3); }

/* pen at (x, y) of a tile at addr with rows of rowbytes; 8 pixels per 4 bytes */
static void pixel(uint32_t addr, unsigned rowbytes, unsigned x, unsigned y, unsigned pen) {
    uint8_t *b = gfxrom + addr + y * rowbytes + (x / 8) * 4;
    for (unsigned p = 0; p < 4; p++) {
        b[p] = (uint8_t)(b[p] & ~(0x80 >> x % 8));
        b[p] |= (uint8_t)(((pen >> p) & 1) << (7 - x % 8));
    }
}

/* bottom to top: scroll3, scroll2, sprites, scroll1; all three enabled */
#define ORDER (3 << 6 | 2 << 8 | 0 << 10 | 1 << 12 | 0x0E)

static void test_palette(void) {
    boot_video();
    cpsb(0x30, 0x3F);                    /* upload all six pages */
    gram(0x20000 + 0x13 * 2, 0xFF08);    /* brightest: red 15, blue 8 */
    gram(0x20000 + 0x14 * 2, 0x0F00);    /* darkest: red 15 */
    cpsa(0x0A, 0x9200);                  /* palette base $920000: the upload */
    assert(cps1_color(&m, 0x13) == 0xFF0088);
    assert(cps1_color(&m, 0x14) == 0x550000);
}

static void test_scroll1_tile(void) {
    boot_video();
    cpsb(0x2E, ORDER);
    cpsa(0x02, 0x9080);                  /* scroll1 map at $908000 */
    unsigned col = 9, row = 2, i = (row & 0x1F) + ((col & 0x3F) << 5) + ((row & 0x20) << 6);
    gram(0x8000 + i * 4, 3), gram(0x8000 + i * 4 + 2, 4);  /* code 3, palette 4 */
    pixel(3 * 64, 8, 8 + 0, 0, 5);       /* an odd column: the right half (bytes 4-7) */
    cps1_render(&m);
    assert(m.frame[0 * CPS1_WIDTH + 8] == 0x200 + 4 * 16 + 5);
    assert(m.frame[0 * CPS1_WIDTH + 9] == 0xBFF);  /* the background */
}

static void test_scroll2_tile(void) {
    boot_video();
    cpsb(0x2E, ORDER);
    cpsa(0x04, 0x9040);                  /* scroll2 map at $904000 */
    cpsa(0x10, 16), cpsa(0x12, 0);       /* scrolled 16 right */
    unsigned col = 6, row = 2, i = (row & 0x0F) + ((col & 0x3F) << 4) + ((row & 0x30) << 6);
    gram(0x4000 + i * 4, 5), gram(0x4000 + i * 4 + 2, 2);
    pixel(5 * 128, 8, 3, 4, 7);          /* tile pixel (3, 4): map (99, 36) */
    cps1_render(&m);
    assert(m.frame[(36 - 16) * CPS1_WIDTH + (99 - 64 - 16)] == 0x400 + 2 * 16 + 7);
}

static void test_scroll3_tile(void) {
    boot_video();
    cpsb(0x2E, ORDER);
    cpsa(0x06, 0x90C0);                  /* scroll3 map at $90C000 */
    unsigned col = 3, row = 0, i = (row & 0x07) + ((col & 0x3F) << 3) + ((row & 0x38) << 6);
    gram(0xC000 + i * 4, 2), gram(0xC000 + i * 4 + 2, 0);
    pixel(2 * 512, 16, 8, 26, 9);        /* map (104, 26): screen (40, 10) */
    cps1_render(&m);
    assert(m.frame[10 * CPS1_WIDTH + 40] == 0x600 + 9);
}

static void sprite_scene(uint16_t prio) {
    boot_video();
    cpsb(0x2E, ORDER);
    cpsb(0x28, prio);                    /* the mask of group 1 */
    cpsa(0x00, 0x9100);                  /* sprites at $910000 */
    gram(0x10000, 64 + 100), gram(0x10002, 16 + 50), gram(0x10004, 0x20);
    gram(0x10006, 1 | 0x20 | 1 << 8);    /* palette 1, flipped in X, 2 blocks wide */
    gram(0x1000E, 0xFF00);               /* the end */
    pixel(0x20 * 128, 8, 0, 0, 3);
    cpsa(0x04, 0x9040);                  /* a scroll2 tile under the sprite's pixel, group 1, pen 7 */
    unsigned col = 12, row = 4, i = (row & 0x0F) + ((col & 0x3F) << 4) + ((row & 0x30) << 6);
    gram(0x4000 + i * 4, 6), gram(0x4000 + i * 4 + 2, 1 << 7);
    pixel(6 * 128, 8, 3, 2, 7);          /* map (195, 66): screen (131, 50) */
    cps1_render(&m);
}

static void test_sprite_flip(void) {
    sprite_scene(0);
    assert(m.frame[50 * CPS1_WIDTH + 131] == 0x13);   /* block $20, flipped, on the right */
    assert(m.frame[50 * CPS1_WIDTH + 100] == 0xBFF);  /* block $21 (empty) on the left */
}

static void test_priority(void) {
    sprite_scene(1 << 7);                /* pen 7 of group 1 goes over sprites */
    assert(m.frame[50 * CPS1_WIDTH + 131] == 0x400 + 0 * 16 + 7);
}

static void test_gfx_mapper(void) {  /* S224B: a tile outside its layer's range is not drawn */
    static const Cps1Mapper s224b = {{0x8000}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x43FF, 0}, {CPS1_GFX_SCROLL1, 0x4400, 0x4BFF, 0},
                                                   {CPS1_GFX_SCROLL3, 0x4C00, 0x5FFF, 0}, {CPS1_GFX_SCROLL2, 0x6000, 0x7FFF, 0}}};
    assert(cps1_gfx_map(&s224b, CPS1_GFX_SCROLL2, 0x3000) == 0x3000);  /* << 1: unit $6000, scroll2's */
    assert(cps1_gfx_map(&s224b, CPS1_GFX_SCROLL2, 0x0005) == -1);      /* a sprite's */
    assert(cps1_gfx_map(&s224b, CPS1_GFX_SCROLL1, 0x4400) == 0x4400);
    assert(cps1_gfx_map(&s224b, CPS1_GFX_SCROLL3, 0x0980) == 0x0980);  /* << 3: unit $4C00 */
    assert(cps1_gfx_map(&s224b, CPS1_GFX_SPRITES, 0x3000) == -1);
    static const Cps1Mapper none = {{0}, 0, {{0}}};
    assert(cps1_gfx_map(&none, CPS1_GFX_SCROLL2, 0x0005) == 0x0005);   /* no ranges: every code */

    boot_video();                                  /* the same scroll2 tile, drawn without a mapper, hidden with it */
    cpsb(0x2E, ORDER);
    cpsa(0x04, 0x9040);
    unsigned col = 6, row = 2, i = (row & 0x0F) + ((col & 0x3F) << 4) + ((row & 0x30) << 6);
    gram(0x4000 + i * 4, 5), gram(0x4000 + i * 4 + 2, 2);
    pixel(5 * 128, 8, 3, 4, 7);
    cps1_render(&m);
    assert(m.frame[(36 - 16) * CPS1_WIDTH + (99 - 64)] == 0x400 + 2 * 16 + 7);
    prog_game.mapper = s224b;
    cps1_render(&m);
    assert(m.frame[(36 - 16) * CPS1_WIDTH + (99 - 64)] == 0xBFF);
    prog_game.mapper = none;
}

static void test_layout_gfx8(void) {  /* 8-bit graphics chips: one byte into every 8, at the offset's slot */
    static uint8_t a[2] = {0xA0, 0xA1}, b[2] = {0xB0, 0xB1};
    static Cps1Game g8 = {"g8", "G8", CPS1_PLAIN, {0, 16, 0, 0}, {0}, 2, {{0}}, {{0}, 0, {{0}}}, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0};
    g8.files[0] = (Cps1File){zip_crc32(a, 2), 2, CPS1_R_GFX, CPS1_LOAD_GFX8, 1, 0};
    g8.files[1] = (Cps1File){zip_crc32(b, 2), 2, CPS1_R_GFX, CPS1_LOAD_GFX8, 6, 0};
    zcount = 0;
    zip_add("a", a, 2), zip_add("b", b, 2);
    zip_build();
    Zip z;
    Cps1Rom r;
    char err[128];
    assert(zip_open(&z, zbuf, zlen) == 0 && cps1_load(&g8, &z, &r, err, sizeof err) == 0);
    static const uint8_t want[16] = {0, 0xA0, 0, 0, 0, 0, 0xB0, 0, 0, 0xA1, 0, 0, 0, 0, 0xB1, 0};
    assert(memcmp(r.region[CPS1_R_GFX], want, 16) == 0);
    cps1_unload(&r);
    zip_close(&z);
}

static void test_mapper_bounds(void) {  /* a mapper bank larger than the graphics ROM: no read past it */
    static const Cps1Mapper big = {{0x10000}, 1, {{CPS1_GFX_SCROLL2, 0x0000, 0xFFFF, 0}}};
    boot_video();
    prog_rom.size[CPS1_R_GFX] = 0x10000;           /* 64 KB: tile codes up to $1FF */
    prog_game.mapper = big;
    cpsb(0x2E, ORDER);
    cpsa(0x04, 0x9040);
    for (unsigned i = 0; i < 64 * 64; i++) gram(0x4000 + i * 4, 0x7FFF), gram(0x4000 + i * 4 + 2, 0);  /* past the ROM */
    cps1_render(&m);
    for (int i = 0; i < CPS1_WIDTH * CPS1_HEIGHT; i++) assert(m.frame[i] == 0xBFF);
    prog_game.mapper = (Cps1Mapper){{0}, 0, {{0}}};
}

static void test_flip(void) {  /* video control bit 15: the picture turned 180 degrees */
    boot_video();
    cpsb(0x2E, ORDER);
    cpsa(0x02, 0x9080);
    unsigned col = 9, row = 2, i = (row & 0x1F) + ((col & 0x3F) << 5) + ((row & 0x20) << 6);
    gram(0x8000 + i * 4, 3), gram(0x8000 + i * 4 + 2, 4);
    pixel(3 * 64, 8, 8 + 0, 0, 5);                /* the tile pixel at screen (8, 0) */
    cpsa(0x22, 0x8000);
    cps1_render(&m);
    assert(m.frame[(CPS1_HEIGHT - 1) * CPS1_WIDTH + (CPS1_WIDTH - 1 - 8)] == 0x200 + 4 * 16 + 5);
    assert(m.frame[8] == 0xBFF);
    cpsa(0x22, 0);
}

static void test_stars(void) {  /* a star of layer 2 (ROM byte +0, scroll 1, colours $800) */
    boot_video();
    prog_game.stars = 0;
    prog_game.b.layer_enable[3] = 0x10, prog_game.b.layer_enable[4] = 0x20;
    unsigned offs = 3 * 256 + 40;
    gfxrom[8 * offs] = 0x05;                       /* column 3 x 32 + 5, row 40: raw (101, 40) */
    cpsb(0x2E, ORDER | 0x20);
    cps1_render(&m);
    assert(m.frame[(40 - 16) * CPS1_WIDTH + (101 - 64)] == 0x800);
    cpsb(0x2E, ORDER);                             /* its enable off */
    cps1_render(&m);
    assert(m.frame[(40 - 16) * CPS1_WIDTH + (101 - 64)] == 0xBFF);
    prog_game.stars = -1;
    prog_game.b.layer_enable[3] = prog_game.b.layer_enable[4] = 0;
}

static void test_rotate(void) {  /* ROT270: raw (x, y) shows at (y, 383 - x) of a 224 x 384 picture */
    static uint32_t rgb[CPS1_WIDTH * CPS1_HEIGHT];
    boot_video();
    cps1_render(&m);
    m.frame[20 * CPS1_WIDTH + 10] = 0x13;
    m.pal[0x13] = 0x0F00;                          /* full red */
    int w, h;
    prog_game.rotate = 270;
    cps1_picture(&m, rgb, &w, &h);
    assert(w == CPS1_HEIGHT && h == CPS1_WIDTH);
    assert(rgb[(CPS1_WIDTH - 1 - 10) * w + 20] == cps1_color(&m, 0x13));
    prog_game.rotate = 0;
    cps1_picture(&m, rgb, &w, &h);
    assert(w == CPS1_WIDTH && rgb[20 * CPS1_WIDTH + 10] == cps1_color(&m, 0x13));
}

/* ---- the YM2151 ---- */

static Opm opm;
static void opm_reg(uint8_t r, uint8_t v) { opm_write(&opm, 0, r), opm_write(&opm, 1, v); }

static void opm_tone(uint8_t kc) {  /* channel 0, algorithm 7, only C2 sounding */
    opm_reset(&opm);
    opm_reg(0x20, 0xC7);
    for (int slot = 0; slot < 4; slot++) opm_reg((uint8_t)(0x60 + slot * 8), 127);
    opm_reg(0x40 + 24, 0x01), opm_reg(0x60 + 24, 0), opm_reg(0x80 + 24, 0x1F), opm_reg(0xE0 + 24, 0x0F);
    opm_reg(0x28, kc), opm_reg(0x30, 0);
    opm_reg(0x08, 0x40);                 /* key on C2 of channel 0 */
}

static double opm_pitch(void) {
    int prev = opm_sample(&opm), crossings = 0;
    for (int i = 1; i < OPM_RATE; i++) {
        int v = opm_sample(&opm);
        if (prev < 0 && v >= 0) crossings++;
        prev = v;
    }
    return crossings;
}

static void test_opm_pitch(void) {
    opm_tone(0x4A);                      /* A4 */
    double f = opm_pitch();
    assert(f >= 437 && f <= 443);
}

static void test_opm_octave(void) {
    opm_tone(0x5A);                      /* A5 */
    double f = opm_pitch();
    assert(f >= 874 && f <= 886);
}

static void test_opm_timer_a(void) {
    opm_reset(&opm);
    opm_reg(0x10, 1000 >> 2), opm_reg(0x11, 1000 & 3);  /* 24 samples */
    opm_reg(0x14, 0x05);                 /* load A, its IRQ on */
    for (int i = 0; i < 23; i++) opm_sample(&opm);
    assert(!opm.irq && !(opm_status(&opm) & 1));
    opm_sample(&opm);
    assert(opm.irq && (opm_status(&opm) & 1));
    opm_reg(0x14, 0x15);                 /* reset A's flag (keep it running) */
    assert(!opm.irq && !(opm_status(&opm) & 1));
}

static void test_opm_timer_b(void) {
    opm_reset(&opm);
    opm_reg(0x12, 255);                  /* 16 samples */
    opm_reg(0x14, 0x0A);
    for (int i = 0; i < 15; i++) opm_sample(&opm);
    assert(!opm.irq);
    opm_sample(&opm);
    assert(opm.irq && (opm_status(&opm) & 2));
}

static void test_opm_release(void) {
    opm_tone(0x4A);
    for (int i = 0; i < 1000; i++) opm_sample(&opm);
    opm_reg(0x08, 0x00);                 /* key off */
    int last = 1;
    for (int i = 0; i < 2000; i++) last = opm_sample(&opm);
    for (int i = 0; i < 100; i++) last |= opm_sample(&opm);
    assert(last == 0);
}

static void test_opm_sustain_hold(void) {  /* D1L 0: the decay holds at full level, no extra step */
    opm_tone(0x4A);
    opm_reg(0xA0 + 24, 31);              /* D1R 31 */
    for (int i = 0; i < 2000; i++) opm_sample(&opm);
    assert(opm.ch[0].op[3].att == 0);
}

static void test_opm_lfo_rate(void) {  /* LFRQ $C0: (16 << 12) a sample, a cycle in 2^30 / 65,536 samples */
    opm_reset(&opm);
    opm_reg(0x18, 0xC0);
    for (int i = 0; i < 16384; i++) opm_sample(&opm);
    assert(opm.lfo_phase == 1u << 30);
}

static void test_opm_carriers_sum(void) {  /* algorithm 7: four loud carriers pass the YM2612's 14-bit clip */
    opm_tone(0x4A);
    for (int slot = 0; slot < 4; slot++)
        opm_reg((uint8_t)(0x40 + slot * 8), 0x01), opm_reg((uint8_t)(0x60 + slot * 8), 0), opm_reg((uint8_t)(0x80 + slot * 8), 0x1F);
    opm_reg(0x08, 0x78);
    int peak = 0;
    for (int i = 0; i < 2000; i++) {
        int v = opm_sample(&opm);
        peak = v > peak ? v : -v > peak ? -v : peak;
    }
    assert(peak > 8191 * 2);             /* both sides, (L + R) / 2: four carriers near 8,168 each */
}

/* ---- the OKI MSM6295 ---- */

static uint8_t okirom[0x1000];
static Oki oki;

static void oki_phrase(int n, uint32_t start, uint32_t end) {
    uint8_t *e = okirom + n * 8;
    e[0] = (uint8_t)(start >> 16), e[1] = (uint8_t)(start >> 8), e[2] = (uint8_t)start;
    e[3] = (uint8_t)(end >> 16), e[4] = (uint8_t)(end >> 8), e[5] = (uint8_t)end;
}

static void oki_setup(void) {
    memset(okirom, 0, sizeof okirom);
    oki_phrase(1, 0x400, 0x401);
    okirom[0x400] = 0x08, okirom[0x401] = 0x80;  /* nibbles 0, 8, 8, 0 */
    oki_phrase(2, 0x500, 0x4FF);                 /* ends before it starts */
    oki_phrase(3, 0x3FFFF, 0x3FFFF);             /* past the ROM */
    oki_phrase(4, 0xFF0, 0xFFF0);                /* runs off the ROM's end */
    oki_reset(&oki, okirom, sizeof okirom);
}

static void test_oki_decode(void) {
    oki_setup();
    oki_write(&oki, 0x81), oki_write(&oki, 0x10);  /* phrase 1 on voice 1, full volume */
    assert(oki_sample(&oki) == 2 * 32);  /* signal x volume (32: full) */
    assert(oki_sample(&oki) == 0);
    assert(oki_sample(&oki) == -2 * 32);
    assert(oki_sample(&oki) == 0);
}

static void test_oki_status(void) {
    oki_setup();
    assert(oki_status(&oki) == 0xF0);
    oki_write(&oki, 0x81), oki_write(&oki, 0x20);  /* voice 2 */
    assert(oki_status(&oki) == 0xF2);
    for (int i = 0; i < 3; i++) oki_sample(&oki);
    assert(oki_status(&oki) == 0xF2);
    oki_sample(&oki);                              /* the last nibble ends it */
    assert(oki_status(&oki) == 0xF0);
}

static void test_oki_as_mame(void) {  /* MAME's okim6295: busy voices ignore a start; start = end is no phrase */
    oki_setup();
    oki_phrase(5, 0x600, 0x600);
    okirom[0x400] = 0x77;                          /* a large first nibble: a restart would show */
    oki_write(&oki, 0x81), oki_write(&oki, 0x10);
    oki_sample(&oki);
    oki_write(&oki, 0x81), oki_write(&oki, 0x17); /* again, at volume 7 */
    assert(oki.v[0].nibble == 1 && oki.v[0].vol == 32);
    oki_write(&oki, 0x85), oki_write(&oki, 0x20);
    assert(!(oki_status(&oki) & 2));
    oki_write(&oki, 0x81), oki_write(&oki, 0x47); /* voice 3 at volume 7: 3/32 */
    assert(oki.v[2].vol == 3);
}

static void test_oki_stop(void) {
    oki_setup();
    oki_write(&oki, 0x81), oki_write(&oki, 0x10);
    oki_write(&oki, 0x08);                         /* stop voice 1 */
    assert(oki_status(&oki) == 0xF0 && oki_sample(&oki) == 0);
}

static void test_oki_bad_phrase(void) {
    oki_setup();
    oki_write(&oki, 0x82), oki_write(&oki, 0x10);
    oki_write(&oki, 0x83), oki_write(&oki, 0x20);
    assert(oki_status(&oki) == 0xF0);
    oki_write(&oki, 0x84), oki_write(&oki, 0x40);  /* runs off the ROM: no read past it */
    for (int i = 0; i < 0x1000; i++) oki_sample(&oki);
    assert(oki.v[2].playing && oki.v[2].start + oki.v[2].nibble / 2 > sizeof okirom);  /* zeros, as MAME reads them */
}

/* ---- the Z80 side ---- */

static uint8_t zrom[0x10000];

static void boot_sound(const uint8_t *code, size_t n) {
    memset(zrom, 0, sizeof zrom);
    memcpy(zrom, code, n);
    boot_program();
    prog_rom.region[CPS1_R_SOUND] = zrom;
    prog_rom.size[CPS1_R_SOUND] = sizeof zrom;
    cps1_init(&m, &prog_rom);
}

static void test_latch(void) {
    static const uint8_t code[] = {0x3A, 0x08, 0xF0, 0x32, 0x00, 0xD0, 0x18, 0xF8};  /* ld a,($F008); ld ($D000),a; jr */
    boot_sound(code, sizeof code);
    m68k_write(&m.cpu, 0x800180, 0x0023, 5, 1);  /* the low byte: $800181 */
    cps1_frame(&m);
    assert(m.z80_ram[0] == 0x23);
    m68k_write(&m.cpu, 0x800180, 0x0011, 5, 1);
    m68k_write(&m.cpu, 0x800180, 0x0042, 5, 1);  /* only the last one stays */
    cps1_frame(&m);
    assert(m.z80_ram[0] == 0x42);
}

static void test_bank(void) {
    static const uint8_t code[] = {0x3E, 0x01, 0x32, 0x04, 0xF0,   /* ld a,1; ld ($F004),a */
                                   0x3A, 0x00, 0x80, 0x32, 0x00, 0xD0, 0x18, 0xFE};  /* ld a,($8000); ld ($D000),a */
    boot_sound(code, sizeof code);
    zrom[0xC000] = 0x5A;                         /* bank 1: ROM $8000 + $4000 */
    cps1_frame(&m);
    assert(m.z80_ram[0] == 0x5A);
}

static void test_ym_irq(void) {
    static const uint8_t code[] = {
        0x31, 0x00, 0xD8, 0xED, 0x56,            /* ld sp,$D800; im 1 */
        0x3E, 0x10, 0x32, 0x00, 0xF0, 0x3E, 0x80, 0x32, 0x01, 0xF0,  /* timer A = 512: 512 samples */
        0x3E, 0x14, 0x32, 0x00, 0xF0, 0x3E, 0x15, 0x32, 0x01, 0xF0,  /* load A, its IRQ on */
        0xFB, 0x18, 0xFE};                       /* ei; jr $ */
    static const uint8_t irq[] = {0x21, 0x01, 0xD0, 0x34,  /* ld hl,$D001; inc (hl) */
        0x3E, 0x14, 0x32, 0x00, 0xF0, 0x3E, 0x15, 0x32, 0x01, 0xF0,  /* reset A's flag */
        0xFB, 0xC9};                             /* ei; ret */
    boot_sound(code, sizeof code);
    memcpy(zrom + 0x38, irq, sizeof irq);
    cps1_frame(&m), cps1_frame(&m);
    assert(m.z80_ram[1] >= 2);                   /* ~1,876 samples: 3 interrupts */
}

static void test_sound_buffer(void) {
    static const uint8_t code[] = {0x18, 0xFE};
    static int16_t out[CPS1_SND_BUF];
    boot_sound(code, sizeof code);
    for (int i = 0; i < 20; i++) cps1_frame(&m);  /* nobody takes the samples */
    assert(m.snd_n <= CPS1_SND_BUF);
    cps1_take_sound(&m, out, CPS1_SND_BUF);
    cps1_frame(&m);
    int n = cps1_take_sound(&m, out, CPS1_SND_BUF);
    assert(n >= 936 && n <= 940);
}

/* ---- per-game machine: clock, extra inputs, DIPs, the dial ---- */

static void test_clock_12mhz(void) {
    boot_program();
    prog_game.clock_mhz = 12;
    cps1_init(&m, &prog_rom);
    uint64_t c0 = m.cpu.cycles;
    int16_t out[CPS1_SND_BUF];
    cps1_take_sound(&m, out, CPS1_SND_BUF);
    cps1_frame(&m);
    uint64_t ran = m.cpu.cycles - c0;
    assert(ran >= 262 * 768 - 40 && ran <= 262 * 768 + 40);
    assert(ram16(0xFF0000) == 1);                  /* VBlank still once a frame */
    int n = cps1_take_sound(&m, out, CPS1_SND_BUF);
    assert(n >= 936 && n <= 940);                  /* the Z80 and the sound as at 10 MHz */
    prog_game.clock_mhz = 10;
}

static void test_in2_port(void) {
    boot_program();
    prog_game.in2 = 0x36, prog_game.extra = CPS1_EXTRA_P3;
    cps1_init(&m, &prog_rom);
    cps1_set_input(&m, 2, PAD_RIGHT | PAD_B | PAD_START | PAD_SELECT);
    assert(m68k_read(&m.cpu, 0x800140 + 0x36, 5, 3) == (uint8_t)~(0x01 | 0x10 | 0x80 | 0x40));
    prog_game.extra = CPS1_EXTRA_KICKS;
    cps1_init(&m, &prog_rom);
    cps1_set_input(&m, 0, PAD_Y | PAD_R), cps1_set_input(&m, 1, PAD_L);
    assert(m68k_read(&m.cpu, 0x800140 + 0x36, 5, 3) == (uint8_t)~(0x01 | 0x04 | 0x20));  /* P1 kicks 4, 6; P2 kick 5 */
    prog_game.in2 = CPS1_NONE, prog_game.extra = CPS1_EXTRA_NONE;
}

static void test_dip_defaults(void) {
    boot_program();
    prog_game.dip[0] = 0xFF, prog_game.dip[1] = 0xF4, prog_game.dip[2] = 0x9F;
    cps1_init(&m, &prog_rom);
    assert(m68k_read(&m.cpu, 0x80001A, 5, 3) >> 8 == 0xFF && m68k_read(&m.cpu, 0x80001C, 5, 3) >> 8 == 0xF4 &&
           m68k_read(&m.cpu, 0x80001E, 5, 3) >> 8 == 0x9F);
    prog_game.dip[0] = prog_game.dip[1] = prog_game.dip[2] = 0xFF;
}

static void test_dial(void) {  /* Forgotten Worlds: R turns player 1's dial 20 steps a frame */
    boot_program();
    prog_game.dial = 1;
    cps1_init(&m, &prog_rom);
    cps1_set_input(&m, 0, PAD_R);
    for (int i = 0; i < 3; i++) cps1_frame(&m);
    unsigned lo = m68k_read(&m.cpu, 0x800052, 5, 3) & 0xFF, hi = m68k_read(&m.cpu, 0x800054, 5, 3) & 0x0F;
    assert((hi << 8 | lo) == 60);
    cps1_set_input(&m, 0, PAD_L);
    for (int i = 0; i < 4; i++) cps1_frame(&m);   /* back past zero: 12 bits */
    lo = m68k_read(&m.cpu, 0x800052, 5, 3) & 0xFF, hi = m68k_read(&m.cpu, 0x800054, 5, 3) & 0x0F;
    assert((hi << 8 | lo) == (unsigned)(-20 & 0xFFF));
    m68k_write(&m.cpu, 0x800040, 0, 5, 1);         /* reset player 1's counter */
    assert((m68k_read(&m.cpu, 0x800052, 5, 3) & 0xFF) == 0);
    prog_game.dial = 0;
}

/* ---- clones and their parent's zip ---- */

static void write_zip(const char *path) {
    FILE *f = fopen(path, "wb");
    fwrite(zbuf, 1, zlen, f), fclose(f);
}

static void test_clone_parent(void) {
    static uint8_t own[4] = {1, 2, 3, 4}, shared[4] = {5, 6, 7, 8};
    static Cps1Game clone = {"clone", "Clone", CPS1_PLAIN, {8, 0, 0, 0}, {0}, 2, {{0}}, {{0}, 0, {{0}}}, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, "cps1_par", 0, -1, CPS1_EXTRA_NONE, 0, 0};
    clone.files[0] = (Cps1File){zip_crc32(own, 4), 4, CPS1_R_MAIN, CPS1_LOAD_PLAIN, 0, 0};
    clone.files[1] = (Cps1File){zip_crc32(shared, 4), 4, CPS1_R_MAIN, CPS1_LOAD_PLAIN, 4, 1};
    zcount = 0, zip_add("own", own, 4), zip_build(), write_zip("cps1_clone.zip");
    static uint8_t clone_zip[256];
    size_t clone_len = zlen;
    memcpy(clone_zip, zbuf, zlen);
    Zip z;
    assert(zip_open(&z, clone_zip, clone_len) == 0);
    assert(cps1_match_in(&z, &clone, 1) == &clone);  /* its own files are enough to know it */
    zip_close(&z);
    Cps1Rom r;
    char err[256] = "";
    remove("cps1_par.zip");
    assert(cps1_open_in("cps1_clone.zip", clone_zip, clone_len, &clone, 1, &r, err, sizeof err) == -1);
    assert(strstr(err, "cps1_par.zip"));
    zcount = 0, zip_add("shared", shared, 4), zip_build(), write_zip("cps1_par.zip");
    assert(cps1_open_in("cps1_clone.zip", clone_zip, clone_len, &clone, 1, &r, err, sizeof err) == 0);
    static const uint8_t want[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    assert(memcmp(r.region[CPS1_R_MAIN], want, 8) == 0);
    cps1_unload(&r);
    remove("cps1_clone.zip"), remove("cps1_par.zip");
}

static void test_match_order(void) {  /* a zip two games match: the one with more of its own files */
    static uint8_t a[4] = {9, 9, 9, 1}, b[4] = {9, 9, 9, 2};
    static Cps1Game two[2] = {
        {"small", "Small", CPS1_PLAIN, {8, 0, 0, 0}, {0}, 1, {{0}}, {{0}, 0, {{0}}}, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0},
        {"big", "Big", CPS1_PLAIN, {8, 0, 0, 0}, {0}, 2, {{0}}, {{0}, 0, {{0}}}, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0}};
    two[0].files[0] = (Cps1File){zip_crc32(a, 4), 4, CPS1_R_MAIN, CPS1_LOAD_PLAIN, 0, 0};
    two[1].files[0] = two[0].files[0];
    two[1].files[1] = (Cps1File){zip_crc32(b, 4), 4, CPS1_R_MAIN, CPS1_LOAD_PLAIN, 4, 0};
    zcount = 0, zip_add("a", a, 4), zip_add("b", b, 4), zip_build();
    Zip z;
    assert(zip_open(&z, zbuf, zlen) == 0);
    assert(cps1_match_in(&z, two, 2) == &two[1]);
    zip_close(&z);
}

/* ---- save states ---- */

static Cps1 m2;

static void state_scene(void) {  /* the 68000's VBlank program and the Z80 with the YM2151's timer IRQ */
    static const uint8_t code[] = {
        0x31, 0x00, 0xD8, 0xED, 0x56, 0x3E, 0x10, 0x32, 0x00, 0xF0, 0x3E, 0x80, 0x32, 0x01, 0xF0,
        0x3E, 0x14, 0x32, 0x00, 0xF0, 0x3E, 0x15, 0x32, 0x01, 0xF0, 0xFB, 0x18, 0xFE};
    static const uint8_t irq[] = {0x21, 0x01, 0xD0, 0x34, 0x3E, 0x14, 0x32, 0x00, 0xF0, 0x3E, 0x15, 0x32, 0x01, 0xF0, 0xFB, 0xC9};
    boot_sound(code, sizeof code);
    memcpy(zrom + 0x38, irq, sizeof irq);
    cps1_init(&m, &prog_rom);
}

static void test_state_roundtrip(void) {
    static int16_t a[CPS1_SND_BUF], b[CPS1_SND_BUF];
    static uint16_t frame[CPS1_WIDTH * CPS1_HEIGHT];
    state_scene();
    for (int i = 0; i < 30; i++) cps1_frame(&m), cps1_take_sound(&m, a, CPS1_SND_BUF);
    m68k_write(&m.cpu, 0x800180, 0x0033, 5, 1);   /* a command still waiting for the Z80 */
    assert(cps1_state_save(&m, "cps1_test.state") == 0);
    int na = 0;
    for (int i = 0; i < 20; i++) cps1_frame(&m), na += cps1_take_sound(&m, a + na, CPS1_SND_BUF - na);
    memcpy(frame, m.frame, sizeof frame);
    cps1_init(&m2, &prog_rom);
    char err[128];
    assert(cps1_state_load(&m2, "cps1_test.state", err, sizeof err) == 0);
    int nb = 0;
    for (int i = 0; i < 20; i++) cps1_frame(&m2), nb += cps1_take_sound(&m2, b + nb, CPS1_SND_BUF - nb);
    assert(na == nb && memcmp(a, b, (size_t)na * sizeof *a) == 0);
    assert(memcmp(frame, m2.frame, sizeof frame) == 0);
    assert(m2.frames == m.frames && m2.z80_ram[1] == m.z80_ram[1]);
}

static void test_state_refused(void) {
    static Cps1 before;
    char err[128] = "";
    state_scene();
    for (int i = 0; i < 3; i++) cps1_frame(&m);
    assert(cps1_state_save(&m, "cps1_test.state") == 0);
    FILE *f = fopen("cps1_test.state", "rb");
    static uint8_t buf[sizeof(Cps1) + 64];
    size_t n = fread(buf, 1, sizeof buf, f);
    fclose(f);
    prog_game.id = "other";                        /* another game's state */
    memcpy(&before, &m, sizeof m);
    assert(cps1_state_load(&m, "cps1_test.state", err, sizeof err) == 1 && strstr(err, "prog"));
    assert(memcmp(&before, &m, sizeof m) == 0);
    prog_game.id = "prog";
    f = fopen("cps1_test.state", "wb"), fwrite(buf, 1, n / 2, f), fclose(f);  /* cut short */
    assert(cps1_state_load(&m, "cps1_test.state", err, sizeof err) == 1 && memcmp(&before, &m, sizeof m) == 0);
    buf[0] ^= 1;                                   /* a wrong magic */
    f = fopen("cps1_test.state", "wb"), fwrite(buf, 1, n, f), fclose(f);
    assert(cps1_state_load(&m, "cps1_test.state", err, sizeof err) == 1 && memcmp(&before, &m, sizeof m) == 0);
    buf[0] ^= 1;
    buf[8 + 16 + 4 + 4 + offsetof(Cps1, snd_n) + 1] ^= 0x40;  /* damaged inside, the right length */
    f = fopen("cps1_test.state", "wb"), fwrite(buf, 1, n, f), fclose(f);
    assert(cps1_state_load(&m, "cps1_test.state", err, sizeof err) == 1 && memcmp(&before, &m, sizeof m) == 0);
    remove("cps1_test.state");
}

int main(void) {
    make_test_game();
    test_layouts();
    test_missing();
    test_detector();
    test_vblank();
    test_inputs();
    test_cpsb();
    test_unmapped();
    test_cpsb_high();
    test_byte_writes();
    test_palette();
    test_scroll1_tile();
    test_scroll2_tile();
    test_scroll3_tile();
    test_sprite_flip();
    test_priority();
    test_gfx_mapper();
    test_layout_gfx8();
    test_mapper_bounds();
    test_flip();
    test_stars();
    test_rotate();
    test_opm_pitch();
    test_opm_octave();
    test_opm_timer_a();
    test_opm_timer_b();
    test_opm_release();
    test_opm_sustain_hold();
    test_opm_lfo_rate();
    test_opm_carriers_sum();
    test_oki_decode();
    test_oki_status();
    test_oki_stop();
    test_oki_as_mame();
    test_oki_bad_phrase();
    test_latch();
    test_bank();
    test_ym_irq();
    test_sound_buffer();
    test_clock_12mhz();
    test_recomp_gate();
    test_recomp_state();
    test_in2_port();
    test_dip_defaults();
    test_dial();
    test_clone_parent();
    test_match_order();
    test_state_roundtrip();
    test_state_refused();
    puts("cps1_tests: ok");
    return 0;
}
