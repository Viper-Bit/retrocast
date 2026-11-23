/* The game table: where each chip of a game goes, which CPS-B and graphics
 * ROM mapper (PAL) its board has, its 68000's clock, its DIP switch
 * defaults and extra inputs (cps1.h). The layouts, configs, mappers and DIP
 * defaults are MAME 0.289's for the set each zip is (cps1.cpp, cps1_v.cpp;
 * docs/sources.md), the CRCs the zips' own. Keep the layout: the build's
 * detection reads this file (cmake/detect_system.cmake). */
#include "cps1.h"

#define K 1024

/* Graphics ROM mappers: bank sizes, then ranges (layers, first, last, bank)
 * in 64-byte units (cps1.h). */
#define MAPPER_AR24B {{0x8000, 0x0, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x2FFF, 0}, {CPS1_GFX_SCROLL1, 0x3000, 0x3FFF, 0}, {CPS1_GFX_SCROLL2, 0x4000, 0x5FFF, 0}, {CPS1_GFX_SCROLL3, 0x6000, 0x7FFF, 0}}}
#define MAPPER_CA24B {{0x8000, 0x0, 0x0, 0x0}, 6, {{CPS1_GFX_SPRITES, 0x0000, 0x2FFF, 0}, {CPS1_GFX_SCROLL2, 0x0000, 0x2FFF, 0}, {CPS1_GFX_SCROLL3, 0x3000, 0x4FFF, 0}, {CPS1_GFX_SCROLL1, 0x5000, 0x57FF, 0}, {CPS1_GFX_SPRITES, 0x5800, 0x7FFF, 0}, {CPS1_GFX_SCROLL2, 0x5800, 0x7FFF, 0}}}
#define MAPPER_CK24B {{0x8000, 0x0, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x2FFF, 0}, {CPS1_GFX_SCROLL1, 0x3000, 0x3FFF, 0}, {CPS1_GFX_SCROLL2, 0x4000, 0x6FFF, 0}, {CPS1_GFX_SCROLL3, 0x7000, 0x7FFF, 0}}}
#define MAPPER_DM620 {{0x8000, 0x2000, 0x2000, 0x0}, 3, {{CPS1_GFX_SCROLL3, 0x8000, 0xBFFF, 1}, {CPS1_GFX_SPRITES, 0x2000, 0x3FFF, 2}, {CPS1_GFX_STARS | CPS1_GFX_SPRITES | CPS1_GFX_SCROLL1 | CPS1_GFX_SCROLL2 | CPS1_GFX_SCROLL3, 0x0000, 0x1FFFF, 0}}}
#define MAPPER_KD29B {{0x8000, 0x8000, 0x0, 0x0}, 5, {{CPS1_GFX_SPRITES, 0x0000, 0x7FFF, 0}, {CPS1_GFX_SPRITES, 0x8000, 0x8FFF, 1}, {CPS1_GFX_SCROLL2, 0x9000, 0xBFFF, 1}, {CPS1_GFX_SCROLL1, 0xC000, 0xD7FF, 1}, {CPS1_GFX_SCROLL3, 0xD800, 0xFFFF, 1}}}
#define MAPPER_KR63B {{0x8000, 0x8000, 0x0, 0x0}, 6, {{CPS1_GFX_SPRITES, 0x0000, 0x7FFF, 0}, {CPS1_GFX_SCROLL2, 0x0000, 0x7FFF, 0}, {CPS1_GFX_SCROLL1, 0x8000, 0x9FFF, 1}, {CPS1_GFX_SPRITES, 0x8000, 0xCFFF, 1}, {CPS1_GFX_SCROLL2, 0x8000, 0xCFFF, 1}, {CPS1_GFX_SCROLL3, 0xD000, 0xFFFF, 1}}}
#define MAPPER_LWCHR {{0x8000, 0x8000, 0x0, 0x0}, 5, {{CPS1_GFX_SPRITES, 0x0000, 0x7FFF, 0}, {CPS1_GFX_SCROLL1, 0x0000, 0x1FFFF, 0}, {CPS1_GFX_STARS, 0x0000, 0x1FFFF, 1}, {CPS1_GFX_SCROLL2, 0x0000, 0x1FFFF, 1}, {CPS1_GFX_SCROLL3, 0x0000, 0x1FFFF, 1}}}
#define MAPPER_MS24B {{0x8000, 0x0, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x3FFF, 0}, {CPS1_GFX_SCROLL1, 0x4000, 0x4FFF, 0}, {CPS1_GFX_SCROLL2, 0x5000, 0x6FFF, 0}, {CPS1_GFX_SCROLL3, 0x7000, 0x7FFF, 0}}}
#define MAPPER_NM24B {{0x8000, 0x0, 0x0, 0x0}, 6, {{CPS1_GFX_SPRITES, 0x0000, 0x3FFF, 0}, {CPS1_GFX_SCROLL2, 0x0000, 0x3FFF, 0}, {CPS1_GFX_SCROLL1, 0x4000, 0x47FF, 0}, {CPS1_GFX_SPRITES, 0x4800, 0x67FF, 0}, {CPS1_GFX_SCROLL2, 0x4800, 0x67FF, 0}, {CPS1_GFX_SCROLL3, 0x6800, 0x7FFF, 0}}}
#define MAPPER_O224B {{0x8000, 0x4000, 0x0, 0x0}, 7, {{CPS1_GFX_SCROLL1, 0x0000, 0x0BFF, 0}, {CPS1_GFX_SCROLL2, 0x0C00, 0x3BFF, 0}, {CPS1_GFX_SCROLL3, 0x3C00, 0x4BFF, 0}, {CPS1_GFX_SPRITES, 0x4C00, 0x7FFF, 0}, {CPS1_GFX_SPRITES, 0x8000, 0xA7FF, 1}, {CPS1_GFX_SCROLL2, 0xA800, 0xB7FF, 1}, {CPS1_GFX_SCROLL3, 0xB800, 0xBFFF, 1}}}
#define MAPPER_Q522B {{0x4000, 0x4000, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES | CPS1_GFX_SCROLL2, 0x0000, 0x3FFF, 0}, {CPS1_GFX_SPRITES | CPS1_GFX_SCROLL2, 0x4000, 0x6FFF, 1}, {CPS1_GFX_SCROLL3, 0x7000, 0x77FF, 1}, {CPS1_GFX_SCROLL1, 0x7800, 0x7FFF, 1}}}
#define MAPPER_RT24B {{0x8000, 0x8000, 0x0, 0x0}, 6, {{CPS1_GFX_SPRITES, 0x0000, 0x53FF, 0}, {CPS1_GFX_SCROLL1, 0x5400, 0x6FFF, 0}, {CPS1_GFX_SCROLL3, 0x7000, 0x7FFF, 0}, {CPS1_GFX_SCROLL3, 0x0000, 0x3FFF, 1}, {CPS1_GFX_SCROLL2, 0x2800, 0x7FFF, 1}, {CPS1_GFX_SPRITES, 0x5400, 0x7FFF, 1}}}
#define MAPPER_S224B {{0x8000, 0x0, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x43FF, 0}, {CPS1_GFX_SCROLL1, 0x4400, 0x4BFF, 0}, {CPS1_GFX_SCROLL3, 0x4C00, 0x5FFF, 0}, {CPS1_GFX_SCROLL2, 0x6000, 0x7FFF, 0}}}
#define MAPPER_S9263B {{0x8000, 0x8000, 0x8000, 0x0}, 6, {{CPS1_GFX_SPRITES, 0x0000, 0x7FFF, 0}, {CPS1_GFX_SPRITES, 0x8000, 0xFFFF, 1}, {CPS1_GFX_SPRITES, 0x10000, 0x11FFF, 2}, {CPS1_GFX_SCROLL3, 0x2000, 0x3FFF, 2}, {CPS1_GFX_SCROLL1, 0x4000, 0x4FFF, 2}, {CPS1_GFX_SCROLL2, 0x5000, 0x7FFF, 2}}}
#define MAPPER_ST24M1 {{0x8000, 0x8000, 0x0, 0x0}, 5, {{CPS1_GFX_STARS, 0x0000, 0x03FF, 0}, {CPS1_GFX_SPRITES, 0x0000, 0x4FFF, 0}, {CPS1_GFX_SCROLL2, 0x4000, 0x7FFF, 0}, {CPS1_GFX_SCROLL3, 0x0000, 0x7FFF, 1}, {CPS1_GFX_SCROLL1, 0x7000, 0x7FFF, 1}}}
#define MAPPER_STF29 {{0x8000, 0x8000, 0x8000, 0x0}, 6, {{CPS1_GFX_SPRITES, 0x0000, 0x7FFF, 0}, {CPS1_GFX_SPRITES, 0x8000, 0xFFFF, 1}, {CPS1_GFX_SPRITES, 0x10000, 0x11FFF, 2}, {CPS1_GFX_SCROLL3, 0x2000, 0x3FFF, 2}, {CPS1_GFX_SCROLL1, 0x4000, 0x4FFF, 2}, {CPS1_GFX_SCROLL2, 0x5000, 0x7FFF, 2}}}
#define MAPPER_TK24B1 {{0x8000, 0x8000, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x5FFF, 0}, {CPS1_GFX_SCROLL1, 0x6000, 0x7FFF, 0}, {CPS1_GFX_SCROLL2, 0x4000, 0x7FFF, 1}, {CPS1_GFX_SCROLL3, 0x0000, 0x3FFF, 1}}}
#define MAPPER_VA24B {{0x8000, 0x0, 0x0, 0x0}, 1, {{CPS1_GFX_SPRITES | CPS1_GFX_SCROLL1 | CPS1_GFX_SCROLL2 | CPS1_GFX_SCROLL3, 0x0000, 0x7FFF, 0}}}
#define MAPPER_WL24B {{0x8000, 0x4000, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x4FFF, 0}, {CPS1_GFX_SCROLL3, 0x5000, 0x6FFF, 0}, {CPS1_GFX_SCROLL1, 0x7000, 0x7FFF, 0}, {CPS1_GFX_SCROLL2, 0x0000, 0x3FFF, 1}}}
#define MAPPER_YI24B {{0x8000, 0x0, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x1FFF, 0}, {CPS1_GFX_SCROLL3, 0x2000, 0x3FFF, 0}, {CPS1_GFX_SCROLL1, 0x4000, 0x47FF, 0}, {CPS1_GFX_SCROLL2, 0x4800, 0x7FFF, 0}}}

/* CPS-B configs: ID port and value, multiplier ports, layer control,
 * priority masks, palette control, layer enable bits (cps1.h). */
#define CPSB_01 {CPS1_NONE, 0x0000, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x26, {0x28, 0x2A, 0x2C, 0x2E}, 0x30, {0x02, 0x04, 0x08, 0x30, 0x30}}
#define CPSB_02 {0x20, 0x0002, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x2C, {0x2A, 0x28, 0x26, 0x24}, 0x22, {0x02, 0x04, 0x08, 0x00, 0x00}}
#define CPSB_03 {0x24, 0x0003, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x30, {0x2E, 0x2C, 0x2A, 0x28}, 0x26, {0x20, 0x10, 0x08, 0x00, 0x00}}
#define CPSB_04 {0x20, 0x0004, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x2E, {0x26, 0x30, 0x28, 0x32}, 0x2A, {0x02, 0x04, 0x08, 0x00, 0x00}}
#define CPSB_05 {0x20, 0x0005, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x28, {0x2A, 0x2C, 0x2E, 0x30}, 0x32, {0x02, 0x08, 0x20, 0x14, 0x14}}
#define CPSB_11 {0x32, 0x0401, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x26, {0x28, 0x2A, 0x2C, 0x2E}, 0x30, {0x08, 0x10, 0x20, 0x00, 0x00}}
#define CPSB_12 {0x20, 0x0402, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x2C, {0x2A, 0x28, 0x26, 0x24}, 0x22, {0x02, 0x04, 0x08, 0x00, 0x00}}
#define CPSB_13 {0x2E, 0x0403, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x22, {0x24, 0x26, 0x28, 0x2A}, 0x2C, {0x20, 0x02, 0x04, 0x00, 0x00}}
#define CPSB_14 {0x1E, 0x0404, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x12, {0x14, 0x16, 0x18, 0x1A}, 0x1C, {0x08, 0x20, 0x10, 0x00, 0x00}}
#define CPSB_15 {0x0E, 0x0405, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x02, {0x04, 0x06, 0x08, 0x0A}, 0x0C, {0x04, 0x02, 0x20, 0x00, 0x00}}
#define CPSB_16 {0x00, 0x0406, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x0C, {0x0A, 0x08, 0x06, 0x04}, 0x02, {0x10, 0x0A, 0x0A, 0x00, 0x00}}
#define CPSB_21_BT1 {0x32, 0x0800, 0x0E, 0x0C, 0x0A, 0x08, 0x28, {0x26, 0x24, 0x22, 0x20}, 0x30, {0x20, 0x04, 0x08, 0x12, 0x12}}
#define CPSB_21_BT2 {CPS1_NONE, 0xFFFF, 0x1E, 0x1C, 0x1A, 0x18, 0x20, {0x2E, 0x2C, 0x2A, 0x28}, 0x30, {0x30, 0x08, 0x30, 0x00, 0x00}}
#define CPSB_21_BT4 {CPS1_NONE, 0xFFFF, 0x06, 0x04, 0x02, 0x00, 0x28, {0x26, 0x24, 0x22, 0x20}, 0x30, {0x20, 0x10, 0x02, 0x00, 0x00}}
#define CPSB_21_BT6 {CPS1_NONE, 0xFFFF, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x20, {0x2E, 0x2C, 0x2A, 0x28}, 0x30, {0x20, 0x14, 0x14, 0x00, 0x00}}
#define CPSB_21_DEF {0x32, 0xFFFF, 0x00, 0x02, 0x04, 0x06, 0x26, {0x28, 0x2A, 0x2C, 0x2E}, 0x30, {0x02, 0x04, 0x08, 0x30, 0x30}}

const Cps1Game cps1_games[] = {
    /* MAME 1941r1 (cps1_10MHz), CPS_B_05 mapper_YI24B */
    {"1941", "1941: Counter Attack (World)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_05, 12, {
        {0x9deb1e75, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* 41e_30.11f */
        {0xd63942b3, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* 41e_35.11h */
        {0xdf201112, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* 41e_31.12f */
        {0x816a818f, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* 41e_36.12h */
        {0x4e9648ca, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* 41-32m.8h */
        {0x01d1cb11, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* 41-5m.7a */
        {0xaeaa3509, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* 41-7m.9a */
        {0xff77985a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* 41-1m.3a */
        {0x983be58f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* 41-3m.5a */
        {0x0f9d8527, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* 41_9.12b */
        {0xd1f15aeb, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* 41_18.11c */
        {0x15aec3a6, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* 41_19.12c */
    }, MAPPER_YI24B, 10, {0xFF, 0xFF, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE},
    /* MAME 3wonders (cps1_10MHz), CPS_B_21_BT1 mapper_RT24B */
    {"3wonders", "Three Wonders (World 910520)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 256 * K}, CPSB_21_BT1, 19, {
        {0xef5b8b33, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* rte_30a.11f */
        {0x7d705529, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* rte_35a.11h */
        {0x32835e5e, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* rte_31a.12f */
        {0x7637975f, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* rte_36a.12h */
        {0x054137c8, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* rt_28a.9f */
        {0x7264cb1b, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* rt_33a.9h */
        {0xcddaa919, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* rte_29a.10f */
        {0xed52e7e5, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* rte_34a.10h */
        {0x86aef804, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* rt-5m.7a */
        {0x4f057110, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* rt-7m.9a */
        {0x902489d0, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* rt-1m.3a */
        {0xe35ce720, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* rt-3m.5a */
        {0x13cb0e7c, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 0},  /* rt-6m.8a */
        {0x1f055014, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 0},  /* rt-8m.10a */
        {0xe9a034f4, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 0},  /* rt-2m.4a */
        {0xdf0eea8b, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 0},  /* rt-4m.6a */
        {0xabfca165, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* rt_9.12b */
        {0x26b211ab, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* rt_18.11c */
        {0xdbe64ad0, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* rt_19.12c */
    }, MAPPER_RT24B, 10, {0xFF, 0x9A, 0x99}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE},
    /* MAME cawing (cps1_10MHz), CPS_B_16 mapper_CA24B */
    {"cawing", "Carrier Air Wing (World 901012)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_16, 12, {
        {0x91fceacd, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* cae_30a.11f */
        {0x3ef03083, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* cae_35a.11h */
        {0xe5b75caf, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* cae_31a.12f */
        {0xc73fd713, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* cae_36a.12h */
        {0x0c4837d4, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* ca-32m.8h */
        {0x66d4cc37, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* ca-5m.7a */
        {0xb6f896f2, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* ca-7m.9a */
        {0x4d0620fd, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* ca-1m.3a */
        {0x0b0341c3, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* ca-3m.5a */
        {0x96fe7485, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ca_9.12b */
        {0x4a613a2c, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ca_18.11c */
        {0x74584493, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* ca_19.12c */
    }, MAPPER_CA24B, 10, {0xFF, 0xFC, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE},
    /* MAME cworld2j (cps1_12MHz), CPS_B_21_BT6 mapper_Q522B */
    {"cworld2j", "Adventure Quiz Capcom World 2 (Japan 920611)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_21_BT6, 27, {
        {0x38a08099, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* q5_36.12f */
        {0x4d29b3a4, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* q5_42.12h */
        {0xeb547ebc, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* q5_37.13f */
        {0x3ef65ea8, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* q5_43.13h */
        {0x7fcc1317, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* q5_34.10f */
        {0x7f14b7b4, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* q5_40.10h */
        {0xabacee26, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* q5_35.11f */
        {0xd3654067, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* q5_41.11h */
        {0x48496d80, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* q5_09.4b */
        {0xc5453f56, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* q5_01.4a */
        {0xc741ac52, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* q5_13.9b */
        {0x143e068f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* q5_05.9a */
        {0xb419d139, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* q5_24.5e */
        {0xbd3b4d11, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* q5_17.5c */
        {0x9c24670c, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* q5_38.8h */
        {0x3ef9c7c2, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* q5_32.8f */
        {0x119e5e93, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100000, 0},  /* q5_10.5b */
        {0xa2cadcbe, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100001, 0},  /* q5_02.5a */
        {0xa8755f82, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100002, 0},  /* q5_14.10b */
        {0xc92a91fc, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100003, 0},  /* q5_06.10a */
        {0x979237cb, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100004, 0},  /* q5_25.7e */
        {0xc57da03c, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100005, 0},  /* q5_18.7c */
        {0xa5839b25, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100006, 0},  /* q5_39.9h */
        {0x04d03930, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100007, 0},  /* q5_33.9f */
        {0xe14dc524, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* q5_23.13b */
        {0xd10c1b68, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* q5_30.12c */
        {0x7d17e496, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* q5_31.13c */
    }, MAPPER_Q522B, 12, {0xFF, 0xFE, 0xDF}, 0x36, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE},
    /* MAME dynwar (cps1_10MHz), CPS_B_02 mapper_TK24B1 */
    {"dynwar", "Dynasty Wars (USA, B-Board 89624B-?)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 256 * K}, CPSB_02, 16, {
        {0xf9ec6d68, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* 30.11f */
        {0xe41fff2f, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* 35.11h */
        {0xe3de76ff, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* 31.12f */
        {0x7a13cfbf, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* 36.12h */
        {0x93654bcf, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* tkm-9.8h */
        {0xf64bb6a0, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* tkm-5.7a */
        {0x21fe6274, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* tkm-8.9a */
        {0x0bf228cb, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* tkm-6.3a */
        {0x1255dfb1, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* tkm-7.5a */
        {0x44f7661e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 0},  /* tkm-1.8a */
        {0xa54c515d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 0},  /* tkm-4.10a */
        {0xca5c687c, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 0},  /* tkm-2.4a */
        {0xf9fe6591, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 0},  /* tkm-3.6a */
        {0xb3b79d4f, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* tke_17.12b */
        {0xac6e307d, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* tke_18.11c */
        {0x068741db, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* tke_19.12c */
    }, MAPPER_TK24B1, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE},
    /* MAME ffight (cps1_10MHz), CPS_B_04 mapper_S224B */
    {"ffight", "Final Fight (World, set 1)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_04, 12, {
        {0xf9a5ce83, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* ff_36.11f */
        {0x65f11215, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* ff_42.11h */
        {0xe1033784, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* ff_37.12f */
        {0x995e968a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* ffe_43.12h */
        {0xc747696e, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* ff-32m.8h */
        {0x9c284108, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* ff-5m.7a */
        {0xa7584dfb, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* ff-7m.9a */
        {0x0b605e44, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* ff-1m.3a */
        {0x52291cd2, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* ff-3m.5a */
        {0xb8367eb5, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ff_09.12b */
        {0x375c66e7, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ff_18.11c */
        {0x1ef137f9, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* ff_19.12c */
    }, MAPPER_S224B, 10, {0xFF, 0xF4, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE},
    /* MAME forgottnua (forgottn), CPS_B_01 mapper_LWCHR */
    {"forgottn", "Forgotten Worlds (USA, B-Board 88618B-2, Rev. A)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 256 * K}, CPSB_01, 16, {
        {0xddf78831, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* lwu_11a.14f */
        {0xf7ce2097, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* lwu_15a.14g */
        {0x8cb38c81, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* lwu_10a.13f */
        {0xd70ef9fd, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* lwu_14a.13g */
        {0xfd252a26, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* lw-07.13e */
        {0x0318f298, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* lw-01.9d */
        {0x25a8e43c, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* lw-08.9f */
        {0xe4552fd7, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* lw-05.9e */
        {0x8e6a832b, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* lw-12.9g */
        {0x43e6c5c8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 0},  /* lw-02.12d */
        {0x899cb4ad, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 0},  /* lw-09.12f */
        {0x5b9edffc, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 0},  /* lw-06.12e */
        {0x8e058ef5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 0},  /* lw-13.12g */
        {0x59df2a63, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* lwu_00.14a */
        {0x807d051f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* lw-03u.14c */
        {0xe6cd098e, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* lw-04u.13c */
    }, MAPPER_LWCHR, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, NULL, 1, 0x200000, CPS1_EXTRA_NONE},
    /* MAME ghouls (cps1_10MHz), CPS_B_01 mapper_DM620 */
    {"ghouls", "Ghouls'n Ghosts (World)", CPS1_PLAIN, {1024 * K, 3072 * K, 64 * K, 0 * K}, CPSB_01, 26, {
        {0x166a58a2, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* dme_29.10h */
        {0x7ac8407a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* dme_30.10j */
        {0xf734b2be, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* dme_27.9h */
        {0x03d3e714, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* dme_28.9j */
        {0x3ea1b0f2, 512 * K, CPS1_R_MAIN, CPS1_LOAD_PLAIN, 0x080000, 0},  /* dm-17.7j */
        {0x0ba9c0b0, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* dm-05.3a */
        {0x5d760ab9, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* dm-07.3f */
        {0x4ba90b59, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* dm-06.3c */
        {0x4bdee9de, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* dm-08.3g */
        {0xae24bb19, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200000, 0},  /* 09.4a */
        {0xd34e271a, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200001, 0},  /* 18.7a */
        {0x3f70dd37, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200002, 0},  /* 13.4e */
        {0x7e69e2e6, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200003, 0},  /* 22.7e */
        {0x37c9b6c6, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200004, 0},  /* 11.4c */
        {0x2f1345b4, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200005, 0},  /* 20.7c */
        {0x3c2a212a, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200006, 0},  /* 15.4g */
        {0x889aac05, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200007, 0},  /* 24.7g */
        {0xbcc0f28c, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280000, 0},  /* 10.4b */
        {0x2a40166a, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280001, 0},  /* 19.7b */
        {0x20f85c03, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280002, 0},  /* 14.4f */
        {0x8426144b, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280003, 0},  /* 23.7f */
        {0xda088d61, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280004, 0},  /* 12.4d */
        {0x17e11df0, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280005, 0},  /* 21.7d */
        {0xf187ba1c, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280006, 0},  /* 16.4h */
        {0x29f79c78, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280007, 0},  /* 25.7h */
        {0x3692f6e5, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* 26.10a */
    }, MAPPER_DM620, 10, {0xFF, 0xFD, 0xFF}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE},
    /* MAME knights (cps1_10MHz), CPS_B_21_BT4 mapper_KR63B */
    {"knights", "Knights of the Round (World 911127)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 256 * K}, CPSB_21_BT4, 13, {
        {0x1b3997eb, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x000000, 0},  /* kr_23e.8f */
        {0xd0b671a9, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* kr_22.7f */
        {0x9e36c1a4, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* kr-5m.3a */
        {0xc5832cae, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* kr-7m.5a */
        {0xf095be2d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* kr-1m.4a */
        {0x179dfd96, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* kr-3m.6a */
        {0x1f4298d2, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 0},  /* kr-6m.7a */
        {0x37fa8751, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 0},  /* kr-8m.9a */
        {0x0200bc3d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 0},  /* kr-2m.8a */
        {0x0bb2b4e7, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 0},  /* kr-4m.10a */
        {0x5e44d9ee, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* kr_09.11a */
        {0xda69d15f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* kr_18.11c */
        {0xbfc654e9, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* kr_19.12c */
    }, MAPPER_KR63B, 10, {0xFF, 0xFC, 0x9F}, 0x36, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_P3},
    /* MAME kodr1 (cps1_10MHz), CPS_B_21_BT2 mapper_KD29B */
    {"kod", "The King of Dragons (World 910711)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 0 * K}, CPSB_21_BT2, 16, {
        {0xc7414fd4, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* kde_30.11e */
        {0xa5bf40d2, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* kde_37.11f */
        {0x1fffc7bd, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* kde_31.12e */
        {0x89e57a82, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* kde_38.12f */
        {0x9367bcd9, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* kde_28.9e */
        {0x4ca6a48a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* kde_35.9f */
        {0x6a0ba878, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* kde_29.10e */
        {0xb509b39d, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* kde_36.10f */
        {0xe45b8701, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* kd-5m.4a */
        {0xa7750322, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* kd-7m.6a */
        {0x5f74bf78, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* kd-1m.3a */
        {0x5e5303bf, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* kd-3m.5a */
        {0x113358f3, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 0},  /* kd-6m.4c */
        {0x38853c44, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 0},  /* kd-8m.6c */
        {0x9ef36604, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 0},  /* kd-2m.3c */
        {0x402b9b4f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 0},  /* kd-4m.5c */
    }, MAPPER_KD29B, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_P3},
    /* MAME mercs (cps1_10MHz), CPS_B_12 mapper_O224B */
    {"mercs", "Mercs (World 900302)", CPS1_PLAIN, {1024 * K, 3072 * K, 64 * K, 256 * K}, CPSB_12, 20, {
        {0xe17f9bf7, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* so2_30e.11f */
        {0x78e63575, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* so2_35e.11h */
        {0x51204d36, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* so2_31e.12f */
        {0x9cfba8b4, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* so2_36e.12h */
        {0x2eb5cf0c, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* so2-32m.8h */
        {0xaa6102af, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* so2-6m.8a */
        {0x839e6869, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* so2-8m.10a */
        {0x597c2875, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* so2-2m.4a */
        {0x912a9ca0, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* so2-4m.6a */
        {0x3f254efe, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200000, 0},  /* so2_24.7d */
        {0xf5a8905e, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200001, 0},  /* so2_14.7c */
        {0xf3aa5a4a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200002, 0},  /* so2_26.9d */
        {0xb43cd1a8, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200003, 0},  /* so2_16.9c */
        {0x8ca751a3, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200004, 0},  /* so2_20.3d */
        {0xe9f569fd, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200005, 0},  /* so2_10.3c */
        {0xfce9a377, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200006, 0},  /* so2_22.5d */
        {0xb7df8a06, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200007, 0},  /* so2_12.5c */
        {0xd09d7c7a, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* so2_09.12b */
        {0xbbea1643, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* so2_18.11c */
        {0xac58aa71, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* so2_19.12c */
    }, MAPPER_O224B, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_P3},
    /* MAME msword (cps1_10MHz), CPS_B_13 mapper_MS24B */
    {"msword", "Magic Sword: Heroic Fantasy (World 900725)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_13, 12, {
        {0x03fc8dbc, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* mse_30.11f */
        {0xd5bf66cd, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* mse_35.11h */
        {0x30332bcf, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* mse_31.12f */
        {0x8f7d6ce9, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* mse_36.12h */
        {0x2475ddfc, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* ms-32m.8h */
        {0xc00fe7e2, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* ms-5m.7a */
        {0x4ccacac5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* ms-7m.9a */
        {0x0d2bbe00, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* ms-1m.3a */
        {0x3a1a5bf4, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* ms-3m.5a */
        {0x57b29519, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ms_09.12b */
        {0xfb64e90d, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ms_18.11c */
        {0x74f892b9, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* ms_19.12c */
    }, MAPPER_MS24B, 10, {0xFF, 0xBC, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE},
    /* MAME mtwins (cps1_10MHz), CPS_B_14 mapper_CK24B */
    {"mtwins", "Mega Twins (World 900619)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_14, 12, {
        {0x9a2a2db1, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* che_30.11f */
        {0xa7f96b02, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* che_35.11h */
        {0xbbff8a99, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* che_31.12f */
        {0x0fa00c39, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* che_36.12h */
        {0x9b70bd41, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* ck-32m.8h */
        {0x4ec75f15, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* ck-5m.7a */
        {0xd85d00d6, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* ck-7m.9a */
        {0xf33ca9d4, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* ck-1m.3a */
        {0x0ba2047f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* ck-3m.5a */
        {0x4d4255b7, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ch_09.12b */
        {0xf909e8de, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ch_18.11c */
        {0xfc158cf7, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* ch_19.12c */
    }, MAPPER_CK24B, 10, {0xFF, 0xDF, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE},
    /* MAME nemo (cps1_10MHz), CPS_B_15 mapper_NM24B */
    {"nemo", "Nemo (World 901130)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_15, 12, {
        {0xd2c03e56, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* nme_30a.11f */
        {0x5fd31661, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* nme_35a.11h */
        {0xb2bd4f6f, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* nme_31a.12f */
        {0xee9450e3, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* nme_36a.12h */
        {0xd6d1add3, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* nm-32m.8h */
        {0x487b8747, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* nm-5m.7a */
        {0x203dc8c6, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* nm-7m.9a */
        {0x9e878024, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* nm-1m.3a */
        {0xbb01e6b6, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* nm-3m.5a */
        {0x0f4b0581, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* nme_09.12b */
        {0xbab333d4, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* nme_18.11c */
        {0x2650a0a8, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* nme_19.12c */
    }, MAPPER_NM24B, 10, {0xFF, 0xFF, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE},
    /* MAME sf2 (cps1_10MHz), CPS_B_11 mapper_STF29 */
    {"sf2", "Street Fighter II: The World Warrior (World 910522)", CPS1_PLAIN, {1024 * K, 6144 * K, 64 * K, 256 * K}, CPSB_11, 23, {
        {0xfe39ee33, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* sf2e_30g.11e */
        {0xfb92cd74, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* sf2e_37g.11f */
        {0x69a0a301, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* sf2e_31g.12e */
        {0x5e22db70, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* sf2e_38g.12f */
        {0x8bf9f1e5, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* sf2e_28g.9e */
        {0x626ef934, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* sf2e_35g.9f */
        {0xbb4af315, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* sf2_29b.10e */
        {0xc02a13eb, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* sf2_36b.10f */
        {0x22c9cc8e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* sf2-5m.4a */
        {0x57213be8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* sf2-7m.6a */
        {0xba529b4f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* sf2-1m.3a */
        {0x4b1b33a8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* sf2-3m.5a */
        {0x2c7e2229, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 0},  /* sf2-6m.4c */
        {0xb5548f17, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 0},  /* sf2-8m.6c */
        {0x14b84312, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 0},  /* sf2-2m.3c */
        {0x5e9cd89a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 0},  /* sf2-4m.5c */
        {0x994bfa58, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 0},  /* sf2-13m.4d */
        {0x3e66ad9d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 0},  /* sf2-15m.6d */
        {0xc1befaa8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 0},  /* sf2-9m.3d */
        {0x0627c831, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 0},  /* sf2-11m.5d */
        {0xa4823a1b, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* sf2_9.12a */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* sf2_18.11c */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* sf2_19.12c */
    }, MAPPER_STF29, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_KICKS},
    /* MAME sf2ceea (cps1_12MHz), CPS_B_21_DEF mapper_S9263B */
    {"sf2ce", "Street Fighter II': Champion Edition (World 920313)", CPS1_PLAIN, {1536 * K, 6144 * K, 64 * K, 256 * K}, CPSB_21_DEF, 18, {
        {0x3f846b74, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x000000, 0},  /* s92e_23a.8f */
        {0x99f1cca4, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* s92_22a.7f */
        {0x925a7877, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x100000, 0},  /* s92_21a.6f */
        {0x03b0d852, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* s92-1m.3a */
        {0x840289ec, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* s92-3m.5a */
        {0xcdb5f027, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* s92-2m.4a */
        {0xe2799472, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* s92-4m.6a */
        {0xba8a2761, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 0},  /* s92-5m.7a */
        {0xe584bfb5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 0},  /* s92-7m.9a */
        {0x21e3f87d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 0},  /* s92-6m.8a */
        {0xbefc47df, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 0},  /* s92-8m.10a */
        {0x960687d5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 0},  /* s92-10m.3c */
        {0x978ecd18, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 0},  /* s92-12m.5c */
        {0xd6ec9a0a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 0},  /* s92-11m.4c */
        {0xed2c67f6, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 0},  /* s92-13m.6c */
        {0x08f6b60e, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* s92_09.11a */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* s92_18.11c */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* s92_19.12c */
    }, MAPPER_S9263B, 12, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_KICKS},
    /* MAME sf2hf (cps1_12MHz), CPS_B_21_DEF mapper_S9263B */
    {"sf2hf", "Street Fighter II': Hyper Fighting (World 921209)", CPS1_PLAIN, {1536 * K, 6144 * K, 64 * K, 256 * K}, CPSB_21_DEF, 18, {
        {0x2dd72514, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x000000, 0},  /* s2te_23.8f */
        {0xaea6e035, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* s2te_22.7f */
        {0xfd200288, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x100000, 0},  /* s2te_21.6f */
        {0x03b0d852, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* s92-1m.3a */
        {0x840289ec, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* s92-3m.5a */
        {0xcdb5f027, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* s92-2m.4a */
        {0xe2799472, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* s92-4m.6a */
        {0xba8a2761, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* s92-5m.7a */
        {0xe584bfb5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* s92-7m.9a */
        {0x21e3f87d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* s92-6m.8a */
        {0xbefc47df, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* s92-8m.10a */
        {0x960687d5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 1},  /* s92-10m.3c */
        {0x978ecd18, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 1},  /* s92-12m.5c */
        {0xd6ec9a0a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 1},  /* s92-11m.4c */
        {0xed2c67f6, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 1},  /* s92-13m.6c */
        {0x08f6b60e, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* s92_09.11a */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* s92_18.11c */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* s92_19.12c */
    }, MAPPER_S9263B, 12, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "sf2ce", 0, -1, CPS1_EXTRA_KICKS},
    /* MAME strider (cps1_10MHz), CPS_B_01 mapper_ST24M1 */
    {"strider", "Strider (USA, B-Board 89624B-2)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 256 * K}, CPSB_01, 16, {
        {0xda997474, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* 30.11f */
        {0x5463aaa3, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* 35.11h */
        {0xd20786db, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* 31.12f */
        {0x21aa2863, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* 36.12h */
        {0x9b3cfc08, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* st-14.8h */
        {0x4eee9aea, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* st-2.8a */
        {0x2d7f21e4, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* st-11.10a */
        {0x7705aa46, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* st-5.4a */
        {0x5b18b722, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* st-9.6a */
        {0x005f000b, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 0},  /* st-1.7a */
        {0xb9441519, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 0},  /* st-10.9a */
        {0xb7d04e8b, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 0},  /* st-4.3a */
        {0x6b4713b4, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 0},  /* st-8.5a */
        {0x2ed403bc, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* 09.12b */
        {0x4386bc80, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* 18.11c */
        {0x444536d7, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* 19.12c */
    }, MAPPER_ST24M1, 10, {0xFF, 0x8D, 0xFF}, CPS1_NONE, CPS1_NONE, NULL, 0, 0x000000, CPS1_EXTRA_NONE},
    /* MAME unsquad (cps1_10MHz), CPS_B_11 mapper_AR24B */
    {"unsquad", "U.N. Squadron (USA)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 128 * K}, CPSB_11, 11, {
        {0x24d8f88d, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* aru_30.11f */
        {0x8b954b59, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* aru_35.11h */
        {0x33e9694b, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* aru_31.12f */
        {0x7cc8fb9e, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* aru_36.12h */
        {0xae1d7fb0, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* ar-32m.8h */
        {0xbf4575d8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* ar-5m.7a */
        {0xa02945f4, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* ar-7m.9a */
        {0x5965ca8d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* ar-1m.3a */
        {0xac6db17d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* ar-3m.5a */
        {0xf3dd1367, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ar_09.12b */
        {0x584b43a9, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* aru_18.11c */
    }, MAPPER_AR24B, 10, {0xFF, 0xFF, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE},
    /* MAME varth (cps1_12MHz), CPS_B_04 mapper_VA24B */
    {"varth", "Varth: Operation Thunderstorm (World 920714)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_04, 15, {
        {0xadb8d391, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* vae_30b.11f */
        {0x44e5548f, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* vae_35b.11h */
        {0x1749a71c, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* vae_31b.12f */
        {0x5f2e2450, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* vae_36b.12h */
        {0xe524ca50, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* vae_28b.9f */
        {0xc0bbf8c9, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* vae_33b.9h */
        {0x6640996a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* vae_29b.10f */
        {0xfa59be8a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* vae_34b.10h */
        {0xb1fb726e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* va-5m.7a */
        {0x4c6588cd, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* va-7m.9a */
        {0x0b1ace37, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* va-1m.3a */
        {0x44dfe706, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* va-3m.5a */
        {0x7a99446e, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* va_09.12b */
        {0xde30510e, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* va_18.11c */
        {0x0610a4ac, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* va_19.12c */
    }, MAPPER_VA24B, 12, {0xFF, 0xF7, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE},
    /* MAME willowu (cps1_10MHz), CPS_B_03 mapper_WL24B */
    {"willow", "Willow (USA)", CPS1_PLAIN, {1024 * K, 3072 * K, 64 * K, 256 * K}, CPSB_03, 19, {
        {0xd604dbb1, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* wlu_30.11f */
        {0x7a791e77, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* 35.11h */
        {0x0eb48a83, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* wlu_31.12f */
        {0xdfd9f643, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* wlm-32.8h */
        {0xafa74b73, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* wlm-7.7a */
        {0x12a0dc0b, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* wlm-5.9a */
        {0xc6f2abce, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* wlm-3.3a */
        {0x4aa4c6d3, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* wlm-1.5a */
        {0x6f0adee5, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200000, 0},  /* wl_24.7d */
        {0x9cf3027d, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200001, 0},  /* wl_14.7c */
        {0xf09c8ecf, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200002, 0},  /* wl_26.9d */
        {0xe35407aa, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200003, 0},  /* wl_16.9c */
        {0x84992350, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200004, 0},  /* wl_20.3d */
        {0xb87b5a36, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200005, 0},  /* wl_10.3c */
        {0xfd3f89f0, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200006, 0},  /* wl_22.5d */
        {0x7da49d69, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200007, 0},  /* wl_12.5c */
        {0xf6b3d060, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* wl_09.12b */
        {0xbde23d4d, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* wl_18.11c */
        {0x683898f5, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* wl_19.12c */
    }, MAPPER_WL24B, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE},
};
const int cps1_game_count = (int)(sizeof cps1_games / sizeof cps1_games[0]);
