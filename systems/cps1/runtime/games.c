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
#define MAPPER_AR22B {{0x4000, 0x4000, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x2FFF, 0}, {CPS1_GFX_SCROLL1, 0x3000, 0x3FFF, 0}, {CPS1_GFX_SCROLL2, 0x4000, 0x5FFF, 1}, {CPS1_GFX_SCROLL3, 0x6000, 0x7FFF, 1}}}
#define MAPPER_AR24B {{0x8000, 0x0, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x2FFF, 0}, {CPS1_GFX_SCROLL1, 0x3000, 0x3FFF, 0}, {CPS1_GFX_SCROLL2, 0x4000, 0x5FFF, 0}, {CPS1_GFX_SCROLL3, 0x6000, 0x7FFF, 0}}}
#define MAPPER_CA22B {{0x4000, 0x4000, 0x0, 0x0}, 7, {{CPS1_GFX_SPRITES, 0x0000, 0x2FFF, 0}, {CPS1_GFX_SCROLL2, 0x0000, 0x2FFF, 0}, {CPS1_GFX_SCROLL3, 0x3000, 0x3FFF, 0}, {CPS1_GFX_SCROLL3, 0x4000, 0x4FFF, 1}, {CPS1_GFX_SCROLL1, 0x5000, 0x57FF, 1}, {CPS1_GFX_SPRITES, 0x5800, 0x7FFF, 1}, {CPS1_GFX_SCROLL2, 0x5800, 0x7FFF, 1}}}
#define MAPPER_CA24B {{0x8000, 0x0, 0x0, 0x0}, 6, {{CPS1_GFX_SPRITES, 0x0000, 0x2FFF, 0}, {CPS1_GFX_SCROLL2, 0x0000, 0x2FFF, 0}, {CPS1_GFX_SCROLL3, 0x3000, 0x4FFF, 0}, {CPS1_GFX_SCROLL1, 0x5000, 0x57FF, 0}, {CPS1_GFX_SPRITES, 0x5800, 0x7FFF, 0}, {CPS1_GFX_SCROLL2, 0x5800, 0x7FFF, 0}}}
#define MAPPER_CC63B {{0x8000, 0x8000, 0x0, 0x0}, 6, {{CPS1_GFX_SPRITES, 0x0000, 0x7FFF, 0}, {CPS1_GFX_SCROLL2, 0x0000, 0x7FFF, 0}, {CPS1_GFX_SPRITES, 0x8000, 0xFFFF, 1}, {CPS1_GFX_SCROLL1, 0x8000, 0xFFFF, 1}, {CPS1_GFX_SCROLL2, 0x8000, 0xFFFF, 1}, {CPS1_GFX_SCROLL3, 0x8000, 0xFFFF, 1}}}
#define MAPPER_CK22B {{0x4000, 0x4000, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x2FFF, 0}, {CPS1_GFX_SCROLL1, 0x3000, 0x3FFF, 0}, {CPS1_GFX_SCROLL2, 0x4000, 0x6FFF, 1}, {CPS1_GFX_SCROLL3, 0x7000, 0x7FFF, 1}}}
#define MAPPER_CK24B {{0x8000, 0x0, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x2FFF, 0}, {CPS1_GFX_SCROLL1, 0x3000, 0x3FFF, 0}, {CPS1_GFX_SCROLL2, 0x4000, 0x6FFF, 0}, {CPS1_GFX_SCROLL3, 0x7000, 0x7FFF, 0}}}
#define MAPPER_DM22A {{0x4000, 0x4000, 0x2000, 0x2000}, 5, {{CPS1_GFX_SPRITES, 0x0000, 0x1FFF, 0}, {CPS1_GFX_SCROLL1, 0x2000, 0x3FFF, 0}, {CPS1_GFX_SCROLL2, 0x4000, 0x7FFF, 1}, {CPS1_GFX_SCROLL3, 0x0000, 0x1FFFF, 2}, {CPS1_GFX_SPRITES, 0x2000, 0x3FFF, 3}}}
#define MAPPER_DM620 {{0x8000, 0x2000, 0x2000, 0x0}, 3, {{CPS1_GFX_SCROLL3, 0x8000, 0xBFFF, 1}, {CPS1_GFX_SPRITES, 0x2000, 0x3FFF, 2}, {CPS1_GFX_STARS | CPS1_GFX_SPRITES | CPS1_GFX_SCROLL1 | CPS1_GFX_SCROLL2 | CPS1_GFX_SCROLL3, 0x0000, 0x1FFFF, 0}}}
#define MAPPER_KD29B {{0x8000, 0x8000, 0x0, 0x0}, 5, {{CPS1_GFX_SPRITES, 0x0000, 0x7FFF, 0}, {CPS1_GFX_SPRITES, 0x8000, 0x8FFF, 1}, {CPS1_GFX_SCROLL2, 0x9000, 0xBFFF, 1}, {CPS1_GFX_SCROLL1, 0xC000, 0xD7FF, 1}, {CPS1_GFX_SCROLL3, 0xD800, 0xFFFF, 1}}}
#define MAPPER_KR63B {{0x8000, 0x8000, 0x0, 0x0}, 6, {{CPS1_GFX_SPRITES, 0x0000, 0x7FFF, 0}, {CPS1_GFX_SCROLL2, 0x0000, 0x7FFF, 0}, {CPS1_GFX_SCROLL1, 0x8000, 0x9FFF, 1}, {CPS1_GFX_SPRITES, 0x8000, 0xCFFF, 1}, {CPS1_GFX_SCROLL2, 0x8000, 0xCFFF, 1}, {CPS1_GFX_SCROLL3, 0xD000, 0xFFFF, 1}}}
#define MAPPER_LWCHR {{0x8000, 0x8000, 0x0, 0x0}, 5, {{CPS1_GFX_SPRITES, 0x0000, 0x7FFF, 0}, {CPS1_GFX_SCROLL1, 0x0000, 0x1FFFF, 0}, {CPS1_GFX_STARS, 0x0000, 0x1FFFF, 1}, {CPS1_GFX_SCROLL2, 0x0000, 0x1FFFF, 1}, {CPS1_GFX_SCROLL3, 0x0000, 0x1FFFF, 1}}}
#define MAPPER_MS22B {{0x4000, 0x4000, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x3FFF, 0}, {CPS1_GFX_SCROLL1, 0x4000, 0x4FFF, 1}, {CPS1_GFX_SCROLL2, 0x5000, 0x6FFF, 1}, {CPS1_GFX_SCROLL3, 0x7000, 0x7FFF, 1}}}
#define MAPPER_MS24B {{0x8000, 0x0, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x3FFF, 0}, {CPS1_GFX_SCROLL1, 0x4000, 0x4FFF, 0}, {CPS1_GFX_SCROLL2, 0x5000, 0x6FFF, 0}, {CPS1_GFX_SCROLL3, 0x7000, 0x7FFF, 0}}}
#define MAPPER_NM24B {{0x8000, 0x0, 0x0, 0x0}, 6, {{CPS1_GFX_SPRITES, 0x0000, 0x3FFF, 0}, {CPS1_GFX_SCROLL2, 0x0000, 0x3FFF, 0}, {CPS1_GFX_SCROLL1, 0x4000, 0x47FF, 0}, {CPS1_GFX_SPRITES, 0x4800, 0x67FF, 0}, {CPS1_GFX_SCROLL2, 0x4800, 0x67FF, 0}, {CPS1_GFX_SCROLL3, 0x6800, 0x7FFF, 0}}}
#define MAPPER_O224B {{0x8000, 0x4000, 0x0, 0x0}, 7, {{CPS1_GFX_SCROLL1, 0x0000, 0x0BFF, 0}, {CPS1_GFX_SCROLL2, 0x0C00, 0x3BFF, 0}, {CPS1_GFX_SCROLL3, 0x3C00, 0x4BFF, 0}, {CPS1_GFX_SPRITES, 0x4C00, 0x7FFF, 0}, {CPS1_GFX_SPRITES, 0x8000, 0xA7FF, 1}, {CPS1_GFX_SCROLL2, 0xA800, 0xB7FF, 1}, {CPS1_GFX_SCROLL3, 0xB800, 0xBFFF, 1}}}
#define MAPPER_Q522B {{0x4000, 0x4000, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES | CPS1_GFX_SCROLL2, 0x0000, 0x3FFF, 0}, {CPS1_GFX_SPRITES | CPS1_GFX_SCROLL2, 0x4000, 0x6FFF, 1}, {CPS1_GFX_SCROLL3, 0x7000, 0x77FF, 1}, {CPS1_GFX_SCROLL1, 0x7800, 0x7FFF, 1}}}
#define MAPPER_RT24B {{0x8000, 0x8000, 0x0, 0x0}, 6, {{CPS1_GFX_SPRITES, 0x0000, 0x53FF, 0}, {CPS1_GFX_SCROLL1, 0x5400, 0x6FFF, 0}, {CPS1_GFX_SCROLL3, 0x7000, 0x7FFF, 0}, {CPS1_GFX_SCROLL3, 0x0000, 0x3FFF, 1}, {CPS1_GFX_SCROLL2, 0x2800, 0x7FFF, 1}, {CPS1_GFX_SPRITES, 0x5400, 0x7FFF, 1}}}
#define MAPPER_S222B {{0x4000, 0x4000, 0x0, 0x0}, 5, {{CPS1_GFX_SPRITES, 0x0000, 0x3FFF, 0}, {CPS1_GFX_SPRITES, 0x4000, 0x43FF, 1}, {CPS1_GFX_SCROLL1, 0x4400, 0x4BFF, 1}, {CPS1_GFX_SCROLL3, 0x4C00, 0x5FFF, 1}, {CPS1_GFX_SCROLL2, 0x6000, 0x7FFF, 1}}}
#define MAPPER_S224B {{0x8000, 0x0, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x43FF, 0}, {CPS1_GFX_SCROLL1, 0x4400, 0x4BFF, 0}, {CPS1_GFX_SCROLL3, 0x4C00, 0x5FFF, 0}, {CPS1_GFX_SCROLL2, 0x6000, 0x7FFF, 0}}}
#define MAPPER_S9263B {{0x8000, 0x8000, 0x8000, 0x0}, 6, {{CPS1_GFX_SPRITES, 0x0000, 0x7FFF, 0}, {CPS1_GFX_SPRITES, 0x8000, 0xFFFF, 1}, {CPS1_GFX_SPRITES, 0x10000, 0x11FFF, 2}, {CPS1_GFX_SCROLL3, 0x2000, 0x3FFF, 2}, {CPS1_GFX_SCROLL1, 0x4000, 0x4FFF, 2}, {CPS1_GFX_SCROLL2, 0x5000, 0x7FFF, 2}}}
#define MAPPER_ST22B {{0x4000, 0x4000, 0x4000, 0x4000}, 7, {{CPS1_GFX_STARS, 0x0000, 0x1FFFF, 0}, {CPS1_GFX_SPRITES, 0x0000, 0x3FFF, 0}, {CPS1_GFX_SPRITES, 0x4000, 0x4FFF, 1}, {CPS1_GFX_SCROLL2, 0x4000, 0x7FFF, 1}, {CPS1_GFX_SCROLL3, 0x0000, 0x3FFF, 2}, {CPS1_GFX_SCROLL3, 0x4000, 0x7FFF, 3}, {CPS1_GFX_SCROLL1, 0x7000, 0x7FFF, 3}}}
#define MAPPER_ST24M1 {{0x8000, 0x8000, 0x0, 0x0}, 5, {{CPS1_GFX_STARS, 0x0000, 0x03FF, 0}, {CPS1_GFX_SPRITES, 0x0000, 0x4FFF, 0}, {CPS1_GFX_SCROLL2, 0x4000, 0x7FFF, 0}, {CPS1_GFX_SCROLL3, 0x0000, 0x7FFF, 1}, {CPS1_GFX_SCROLL1, 0x7000, 0x7FFF, 1}}}
#define MAPPER_STF29 {{0x8000, 0x8000, 0x8000, 0x0}, 6, {{CPS1_GFX_SPRITES, 0x0000, 0x7FFF, 0}, {CPS1_GFX_SPRITES, 0x8000, 0xFFFF, 1}, {CPS1_GFX_SPRITES, 0x10000, 0x11FFF, 2}, {CPS1_GFX_SCROLL3, 0x2000, 0x3FFF, 2}, {CPS1_GFX_SCROLL1, 0x4000, 0x4FFF, 2}, {CPS1_GFX_SCROLL2, 0x5000, 0x7FFF, 2}}}
#define MAPPER_TK22B {{0x4000, 0x4000, 0x4000, 0x4000}, 5, {{CPS1_GFX_SPRITES, 0x0000, 0x3FFF, 0}, {CPS1_GFX_SPRITES, 0x4000, 0x5FFF, 1}, {CPS1_GFX_SCROLL1, 0x6000, 0x7FFF, 1}, {CPS1_GFX_SCROLL3, 0x0000, 0x3FFF, 2}, {CPS1_GFX_SCROLL2, 0x4000, 0x7FFF, 3}}}
#define MAPPER_TK24B1 {{0x8000, 0x8000, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x5FFF, 0}, {CPS1_GFX_SCROLL1, 0x6000, 0x7FFF, 0}, {CPS1_GFX_SCROLL2, 0x4000, 0x7FFF, 1}, {CPS1_GFX_SCROLL3, 0x0000, 0x3FFF, 1}}}
#define MAPPER_VA22B {{0x4000, 0x4000, 0x0, 0x0}, 2, {{CPS1_GFX_SPRITES | CPS1_GFX_SCROLL1 | CPS1_GFX_SCROLL2 | CPS1_GFX_SCROLL3, 0x0000, 0x3FFF, 0}, {CPS1_GFX_SPRITES | CPS1_GFX_SCROLL1 | CPS1_GFX_SCROLL2 | CPS1_GFX_SCROLL3, 0x4000, 0x7FFF, 1}}}
#define MAPPER_VA24B {{0x8000, 0x0, 0x0, 0x0}, 1, {{CPS1_GFX_SPRITES | CPS1_GFX_SCROLL1 | CPS1_GFX_SCROLL2 | CPS1_GFX_SCROLL3, 0x0000, 0x7FFF, 0}}}
#define MAPPER_VA63B {{0x8000, 0x0, 0x0, 0x0}, 1, {{CPS1_GFX_SPRITES | CPS1_GFX_SCROLL1 | CPS1_GFX_SCROLL2 | CPS1_GFX_SCROLL3, 0x0000, 0x7FFF, 0}}}
#define MAPPER_WL24B {{0x8000, 0x4000, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x4FFF, 0}, {CPS1_GFX_SCROLL3, 0x5000, 0x6FFF, 0}, {CPS1_GFX_SCROLL1, 0x7000, 0x7FFF, 0}, {CPS1_GFX_SCROLL2, 0x0000, 0x3FFF, 1}}}
#define MAPPER_YI24B {{0x8000, 0x0, 0x0, 0x0}, 4, {{CPS1_GFX_SPRITES, 0x0000, 0x1FFF, 0}, {CPS1_GFX_SCROLL3, 0x2000, 0x3FFF, 0}, {CPS1_GFX_SCROLL1, 0x4000, 0x47FF, 0}, {CPS1_GFX_SCROLL2, 0x4800, 0x7FFF, 0}}}

/* CPS-B configs (MAME's CPS_B_* and, for hacks and bootlegs, HACK_B_*): ID port and value,
 * multiplier ports, layer control, priority masks, palette control, layer enable bits (cps1.h). */
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
#define CPSB_17 {0x08, 0x0407, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x14, {0x12, 0x10, 0x0E, 0x0C}, 0x0A, {0x08, 0x14, 0x02, 0x00, 0x00}}
#define CPSB_18 {0x10, 0x0408, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x1C, {0x1A, 0x18, 0x16, 0x14}, 0x12, {0x10, 0x08, 0x02, 0x00, 0x00}}
#define CPSB_21_BT1 {0x32, 0x0800, 0x0E, 0x0C, 0x0A, 0x08, 0x28, {0x26, 0x24, 0x22, 0x20}, 0x30, {0x20, 0x04, 0x08, 0x12, 0x12}}
#define CPSB_21_BT2 {CPS1_NONE, 0xFFFF, 0x1E, 0x1C, 0x1A, 0x18, 0x20, {0x2E, 0x2C, 0x2A, 0x28}, 0x30, {0x30, 0x08, 0x30, 0x00, 0x00}}
#define CPSB_21_BT3 {CPS1_NONE, 0xFFFF, 0x06, 0x04, 0x02, 0x00, 0x20, {0x2E, 0x2C, 0x2A, 0x28}, 0x30, {0x20, 0x12, 0x12, 0x00, 0x00}}
#define CPSB_21_BT4 {CPS1_NONE, 0xFFFF, 0x06, 0x04, 0x02, 0x00, 0x28, {0x26, 0x24, 0x22, 0x20}, 0x30, {0x20, 0x10, 0x02, 0x00, 0x00}}
#define CPSB_21_BT5 {0x32, 0xFFFF, 0x0E, 0x0C, 0x0A, 0x08, 0x20, {0x2E, 0x2C, 0x2A, 0x28}, 0x30, {0x20, 0x04, 0x02, 0x00, 0x00}}
#define CPSB_21_BT6 {CPS1_NONE, 0xFFFF, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x20, {0x2E, 0x2C, 0x2A, 0x28}, 0x30, {0x20, 0x14, 0x14, 0x00, 0x00}}
#define CPSB_21_DEF {0x32, 0xFFFF, 0x00, 0x02, 0x04, 0x06, 0x26, {0x28, 0x2A, 0x2C, 0x2E}, 0x30, {0x02, 0x04, 0x08, 0x30, 0x30}}
#define HACK_B_1 {CPS1_NONE, 0xFFFF, CPS1_NONE, CPS1_NONE, CPS1_NONE, CPS1_NONE, 0x14, {0x12, 0x10, 0x0E, 0x0C}, 0x0A, {0x0E, 0x0E, 0x0E, 0x30, 0x30}}
#define HACK_B_2 {CPS1_NONE, 0xFFFF, 0x0E, 0x0C, 0x0A, 0x08, 0x28, {0x26, 0x24, 0x22, 0x20}, 0x22, {0x20, 0x04, 0x08, 0x12, 0x12}}

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
    }, MAPPER_YI24B, 10, {0xFF, 0xFF, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 270, 0},
    /* MAME 3wondersh (cps1_10MHz), HACK_B_2 mapper_RT24B */
    {"3wonderh", "Three Wonders (hack)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 256 * K}, HACK_B_2, 27, {
        {0xe6071884, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* 22.bin */
        {0xa28447b7, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* 26.bin */
        {0xfd3d6509, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* 23.bin */
        {0x999cba3d, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* 27.bin */
        {0x054137c8, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 1},  /* rt_28a.9f */
        {0x7264cb1b, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 1},  /* rt_33a.9h */
        {0xcddaa919, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 1},  /* rte_29a.10f */
        {0xed52e7e5, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 1},  /* rte_34a.10h */
        {0xc997bca2, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* 16.bin */
        {0x3eea321a, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* 6.bin */
        {0x98acdfd4, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* 18.bin */
        {0xdc9ca6f9, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* 8.bin */
        {0x0d8a6007, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* 12.bin */
        {0xd75563b9, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* 2.bin */
        {0x84369a28, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* 14.bin */
        {0xd4831578, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* 4.bin */
        {0x040edff5, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200000, 0},  /* 17.bin */
        {0xc7c0468c, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200001, 0},  /* 7.bin */
        {0x9fef114f, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200002, 0},  /* 19.bin */
        {0x48cbfba5, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200003, 0},  /* 9.bin */
        {0x8fc3d7d1, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200004, 0},  /* 13.bin */
        {0xc65e9a86, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200005, 0},  /* 3.bin */
        {0xf239341a, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200006, 0},  /* 15.bin */
        {0x947ac944, 256 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200007, 0},  /* 5.bin */
        {0xabfca165, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* rt_9.12b */
        {0x26b211ab, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* rt_18.11c */
        {0xdbe64ad0, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* rt_19.12c */
    }, MAPPER_RT24B, 10, {0xFF, 0x9A, 0x99}, CPS1_NONE, CPS1_NONE, "3wonders", 0, -1, CPS1_EXTRA_NONE, 0, 0},
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
    }, MAPPER_RT24B, 10, {0xFF, 0x9A, 0x99}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME area88 (cps1_10MHz), CPS_B_11 mapper_AR22B */
    {"area88", "Area 88 (Japan)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 128 * K}, CPSB_11, 26, {
        {0x65030392, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* ar_36.12f */
        {0xc48170de, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* ar_42.12h */
        {0x33e9694b, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* ar_37.13f */
        {0x7cc8fb9e, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* ar_43.13h */
        {0xf6e80386, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* ar_34.10f */
        {0xbe36c145, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* ar_40.10h */
        {0x86d98ff3, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* ar_35.11f */
        {0x758893d3, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* ar_41.11h */
        {0xdb9376f8, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* ar_09.4b */
        {0x392151b4, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* ar_01.4a */
        {0x81436481, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* ar_13.9b */
        {0xe246ed9f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* ar_05.9a */
        {0x9cd6e2a3, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* ar_24.5e */
        {0x0b8e0df4, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* ar_17.5c */
        {0x8b9e75b9, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* ar_38.8h */
        {0xdb6acdcf, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* ar_32.8f */
        {0x4219b622, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100000, 0},  /* ar_10.5b */
        {0xbac5dec5, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100001, 0},  /* ar_02.5a */
        {0xe6bae179, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100002, 0},  /* ar_14.10b */
        {0xc8f04223, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100003, 0},  /* ar_06.10a */
        {0x15ccf981, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100004, 0},  /* ar_25.7e */
        {0x9336db6a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100005, 0},  /* ar_18.7c */
        {0x9b8e1363, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100006, 0},  /* ar_39.9h */
        {0x3968f4b5, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100007, 0},  /* ar_33.9f */
        {0xf3dd1367, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ar_23.13c */
        {0x584b43a9, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ar_30.12e */
    }, MAPPER_AR22B, 10, {0xFF, 0xFF, 0x9F}, CPS1_NONE, CPS1_NONE, "unsquad", 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME captcommr1 (cps1_10MHz), CPS_B_21_BT3 mapper_CC63B */
    {"captcomm", "Captain Commando (World 911014)", CPS1_PLAIN, {1280 * K, 4096 * K, 64 * K, 256 * K}, CPSB_21_BT3, 15, {
        {0x19c58ece, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x000000, 0},  /* cce_23d.8f */
        {0xa91949b7, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* cc_22d.7f */
        {0x680e543f, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x100000, 0},  /* cc_24d.9e */
        {0x8820039f, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x100001, 0},  /* cc_28d.9f */
        {0x7261d8ba, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* cc-5m.3a */
        {0x6a60f949, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* cc-7m.5a */
        {0x00637302, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* cc-1m.4a */
        {0xcc87cf61, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* cc-3m.6a */
        {0x28718bed, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 0},  /* cc-6m.7a */
        {0xd4acc53a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 0},  /* cc-8m.9a */
        {0x0c69f151, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 0},  /* cc-2m.8a */
        {0x1f9ebb97, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 0},  /* cc-4m.10a */
        {0x698e8b58, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* cc_09.11a */
        {0x6de2c2db, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* cc_18.11c */
        {0xb99091ae, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* cc_19.12c */
    }, MAPPER_CC63B, 10, {0xFF, 0xF4, 0x9F}, 0x36, 0x38, NULL, 0, -1, CPS1_EXTRA_P3, 0, 0},
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
    }, MAPPER_CA24B, 10, {0xFF, 0xFC, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME cawingj (cps1_10MHz), CPS_B_16 mapper_CA22B */
    {"cawingj", "U.S. Navy (Japan 901012)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_16, 27, {
        {0x91fceacd, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* caj_36a.12f */
        {0x039f8362, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* caj_42a.12h */
        {0xe5b75caf, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* caj_37a.13f */
        {0xc73fd713, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* caj_43a.13h */
        {0x51ea57f4, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* caj_34.10f */
        {0x2ab71ae1, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* caj_40.10h */
        {0x01d71973, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* caj_35.11f */
        {0x3a43b538, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* caj_41.11h */
        {0x41b0f9a6, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* caj_09.4b */
        {0x1002d0b8, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* caj_01.4a */
        {0x6f3948b2, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* caj_13.9b */
        {0x207373d7, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* caj_05.9a */
        {0xe356aad7, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* caj_24.5e */
        {0x540f2fd8, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* caj_17.5c */
        {0x2464d4ab, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* caj_38.8h */
        {0x9b5836b3, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* caj_32.8f */
        {0xbf8a5f52, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100000, 0},  /* caj_10.5b */
        {0x125b018d, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100001, 0},  /* caj_02.5a */
        {0x8458e7d7, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100002, 0},  /* caj_14.10b */
        {0xcf80e164, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100003, 0},  /* caj_06.10a */
        {0xcdd0204d, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100004, 0},  /* caj_25.7e */
        {0x29c1d4b1, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100005, 0},  /* caj_18.7c */
        {0xeea23b67, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100006, 0},  /* caj_39.9h */
        {0xdde3891f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100007, 0},  /* caj_33.9f */
        {0x96fe7485, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* caj_23.13b */
        {0x4a613a2c, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* caj_30.12c */
        {0x74584493, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* caj_31.13c */
    }, MAPPER_CA22B, 10, {0xFF, 0xFC, 0x9F}, CPS1_NONE, CPS1_NONE, "cawing", 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME cawingr1 (cps1_10MHz), CPS_B_16 mapper_CA24B */
    {"cawingr1", "Carrier Air Wing (World 901009)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_16, 12, {
        {0x23305cd5, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* cae_30.11f */
        {0x69419113, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* cae_35.11h */
        {0x9008dfb3, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* cae_31.12f */
        {0x4dbf6f8e, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* cae_36.12h */
        {0x0c4837d4, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 1},  /* ca-32m.8h */
        {0x66d4cc37, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* ca-5m.7a */
        {0xb6f896f2, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* ca-7m.9a */
        {0x4d0620fd, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* ca-1m.3a */
        {0x0b0341c3, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* ca-3m.5a */
        {0x96fe7485, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* cae_09.12b */
        {0x4a613a2c, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* cae_18.11c */
        {0x74584493, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* cae_19.12c */
    }, MAPPER_CA24B, 10, {0xFF, 0xFC, 0x9F}, CPS1_NONE, CPS1_NONE, "cawing", 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME chikij (cps1_10MHz), CPS_B_14 mapper_CK22B */
    {"chikij", "Chiki Chiki Boys (Japan 900619)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_14, 27, {
        {0xec1328d8, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* chj_36a.12f */
        {0x4ae13503, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* chj_42a.12h */
        {0x46d2cf7b, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* chj_37a.13f */
        {0x8d387fe8, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* chj_43a.13h */
        {0x609ed2f9, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* ch_34.10f */
        {0xbe0d8301, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* ch_40.10h */
        {0xb810867f, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* ch_35.11f */
        {0x8ad96155, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* ch_41.11h */
        {0x567ab3ca, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* ch_09.4b */
        {0x7f3b7b56, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* ch_01.4a */
        {0x12a7a8ba, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* ch_13.9b */
        {0x6c1afb9a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* ch_05.9a */
        {0x9cb6e6bc, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* ch_24.5e */
        {0xfe490846, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* ch_17.5c */
        {0x6e5c8cb6, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* ch_38.8h */
        {0x317d27b0, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* ch_32.8f */
        {0xe8251a9b, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100000, 0},  /* ch_10.5b */
        {0x7c8c88fb, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100001, 0},  /* ch_02.5a */
        {0x4012ec4b, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100002, 0},  /* ch_14.10b */
        {0x81884b2b, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100003, 0},  /* ch_06.10a */
        {0x1dfcbac5, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100004, 0},  /* ch_25.7e */
        {0x516a34d1, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100005, 0},  /* ch_18.7c */
        {0x872fb2a4, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100006, 0},  /* ch_39.9h */
        {0x30dc5ded, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100007, 0},  /* ch_33.9f */
        {0x4d4255b7, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ch_23.13b */
        {0xf909e8de, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ch_30.12c */
        {0xfc158cf7, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* ch_31.13c */
    }, MAPPER_CK22B, 10, {0xFF, 0xDF, 0x9F}, CPS1_NONE, CPS1_NONE, "mtwins", 0, -1, CPS1_EXTRA_NONE, 0, 0},
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
    }, MAPPER_Q522B, 12, {0xFF, 0xFE, 0xDF}, 0x36, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME daimakai (cps1_10MHz), CPS_B_01 mapper_DM22A */
    {"daimakai", "Daimakaimura (Japan)", CPS1_PLAIN, {1024 * K, 3072 * K, 64 * K, 0 * K}, CPSB_01, 41, {
        {0x82fd1798, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* dmj_38.12f */
        {0x35366ccc, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* dmj_39.12h */
        {0xa17c170a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* dmj_40.13f */
        {0x6af0b391, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* dmj_41.13h */
        {0x384d60c4, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* dm_33.10f */
        {0x19abe30f, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* dm_34.10h */
        {0xc04b85c8, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* dm_35.11f */
        {0x89be83de, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* dm_36.11h */
        {0x8b98dc48, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* dm_02.4b */
        {0x80896c33, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* dm_01.4a */
        {0xc2e7d9ef, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* dm_10.9b */
        {0xc9c4afa5, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* dm_09.9a */
        {0x1aa0db99, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* dm_18.5e */
        {0xdc6ed8ad, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* dm_17.5c */
        {0xd9d3f8bd, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* dm_30.8h */
        {0x49a48796, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* dm_29.8f */
        {0xa4f4f8f0, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100000, 0},  /* dm_04.5b */
        {0xb1033e62, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100001, 0},  /* dm_03.5a */
        {0x10fdd76a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100002, 0},  /* dm_12.10b */
        {0x9040cb04, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100003, 0},  /* dm_11.10a */
        {0x281d0b3e, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100004, 0},  /* dm_20.7e */
        {0x2623b52f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100005, 0},  /* dm_19.7c */
        {0x99692344, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100006, 0},  /* dm_32.9h */
        {0x54acb729, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100007, 0},  /* dm_31.9f */
        {0xae24bb19, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200000, 0},  /* dm_06.7b */
        {0xd34e271a, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200001, 0},  /* dm_05.7a */
        {0x3f70dd37, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200002, 0},  /* dm_14.11b */
        {0x7e69e2e6, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200003, 0},  /* dm_13.11a */
        {0x37c9b6c6, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200004, 0},  /* dm_22.8e */
        {0x2f1345b4, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200005, 0},  /* dm_21.8c */
        {0x3c2a212a, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200006, 0},  /* dm_26.10e */
        {0x889aac05, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200007, 0},  /* dm_25.10c */
        {0xbcc0f28c, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280000, 0},  /* dm_08.8b */
        {0x2a40166a, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280001, 0},  /* dm_07.8a */
        {0x20f85c03, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280002, 0},  /* dm_16.12b */
        {0x8426144b, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280003, 0},  /* dm_15.12a */
        {0xda088d61, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280004, 0},  /* dm_24.9e */
        {0x17e11df0, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280005, 0},  /* dm_23.9c */
        {0xf187ba1c, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280006, 0},  /* dm_28.11e */
        {0x29f79c78, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280007, 0},  /* dm_27.11c */
        {0x3692f6e5, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* 37.13c */
    }, MAPPER_DM22A, 10, {0xFF, 0xFD, 0xFF}, CPS1_NONE, CPS1_NONE, "ghouls", 0, -1, CPS1_EXTRA_NONE, 0, 0},
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
    }, MAPPER_TK24B1, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME dynwarj (cps1_10MHz), CPS_B_02 mapper_TK22B */
    {"dynwarj", "Tenchi wo Kurau (Japan)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 256 * K}, CPSB_02, 43, {
        {0x1a516657, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* 36.12f */
        {0x12a290a0, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* 42.12h */
        {0x932fc943, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* 37.13f */
        {0x872ad76d, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* 43.13h */
        {0x8f663d00, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* 34.10f */
        {0x1586dbf3, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* 40.10h */
        {0x9db93d7a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* 35.11f */
        {0x1aae69a4, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* 41.11h */
        {0xc3e83c69, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* 09.4b */
        {0x187b2886, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* 01.4a */
        {0x0273d87d, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* 13.9b */
        {0x339378b8, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* 05.9a */
        {0xc6909b6f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* 24.5e */
        {0x2e2f8320, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* 17.5c */
        {0xcd7923ed, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* 38.8h */
        {0x21a0a453, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* 32.8f */
        {0xff28f8d0, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100000, 0},  /* 10.5b */
        {0xcc83c02f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100001, 0},  /* 02.5a */
        {0x18fb232c, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100002, 0},  /* 14.10b */
        {0x6f9edd75, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100003, 0},  /* 06.10a */
        {0x152ea74a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100004, 0},  /* 25.7e */
        {0x1833f932, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100005, 0},  /* 18.7c */
        {0xbc09b360, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100006, 0},  /* 39.9h */
        {0x89de1533, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100007, 0},  /* 33.9f */
        {0x29eaf490, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200000, 0},  /* 11.7b */
        {0x7bf51337, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200001, 0},  /* 03.7a */
        {0xd36cdb91, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200002, 0},  /* 15.11b */
        {0xe04af054, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200003, 0},  /* 07.11a */
        {0x07fc714b, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200004, 0},  /* 26.8e */
        {0x7114e5c6, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200005, 0},  /* 19.8c */
        {0xaf62bf07, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200006, 0},  /* 28.10e */
        {0x523f462a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200007, 0},  /* 21.10c */
        {0x38652339, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300000, 0},  /* 12.8b */
        {0x4951bc0f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300001, 0},  /* 04.8a */
        {0x381608ae, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300002, 0},  /* 16.12b */
        {0xb475d4e9, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300003, 0},  /* 08.12a */
        {0xa27e81fa, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300004, 0},  /* 27.9e */
        {0x002796dc, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300005, 0},  /* 20.9c */
        {0x6b41f82d, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300006, 0},  /* 29.11e */
        {0x52145369, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300007, 0},  /* 22.11c */
        {0xb3b79d4f, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* 23.13c */
        {0x7e5f6cb4, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* 30.12e */
        {0x4a30c737, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* 31.13e */
    }, MAPPER_TK22B, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, "dynwar", 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME dynwara (cps1_10MHz), CPS_B_02 mapper_TK22B */
    {"dynwaru", "Dynasty Wars (USA, B-Board 88622B-3)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 256 * K}, CPSB_02, 43, {
        {0x895991d1, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* tke_36.12f */
        {0xc898d2e8, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* tke_42.12h */
        {0xb228d58c, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* tke_37.13f */
        {0x1a14375a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* tke_43.13h */
        {0x8f663d00, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* 34.10f */
        {0x1586dbf3, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* 40.10h */
        {0x9db93d7a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* 35.11f */
        {0x1aae69a4, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* 41.11h */
        {0xc3e83c69, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* 09.4b */
        {0x187b2886, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* 01.4a */
        {0x0273d87d, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* 13.9b */
        {0x339378b8, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* 05.9a */
        {0xc6909b6f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* 24.5e */
        {0x2e2f8320, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* 17.5c */
        {0xcd7923ed, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* 38.8h */
        {0x21a0a453, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* 32.8f */
        {0xff28f8d0, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100000, 0},  /* 10.5b */
        {0xcc83c02f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100001, 0},  /* 02.5a */
        {0x58d9b32f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100002, 0},  /* 14.10b */
        {0x6f9edd75, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100003, 0},  /* 06.10a */
        {0x152ea74a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100004, 0},  /* 25.7e */
        {0x1833f932, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100005, 0},  /* 18.7c */
        {0xbc09b360, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100006, 0},  /* 39.9h */
        {0x89de1533, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100007, 0},  /* 33.9f */
        {0x29eaf490, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200000, 0},  /* 11.7b */
        {0x7bf51337, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200001, 0},  /* 03.7a */
        {0xd36cdb91, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200002, 0},  /* 15.11b */
        {0xe04af054, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200003, 0},  /* 07.11a */
        {0x07fc714b, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200004, 0},  /* 26.8e */
        {0x7114e5c6, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200005, 0},  /* 19.8c */
        {0xaf62bf07, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200006, 0},  /* 28.10e */
        {0x523f462a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200007, 0},  /* 21.10c */
        {0x38652339, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300000, 0},  /* 12.8b */
        {0x4951bc0f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300001, 0},  /* 04.8a */
        {0x381608ae, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300002, 0},  /* 16.12b */
        {0xb475d4e9, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300003, 0},  /* 08.12a */
        {0xa27e81fa, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300004, 0},  /* 27.9e */
        {0x002796dc, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300005, 0},  /* 20.9c */
        {0x6b41f82d, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300006, 0},  /* 29.11e */
        {0x52145369, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300007, 0},  /* 22.11c */
        {0xb3b79d4f, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* 23.13c */
        {0xac6e307d, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* tke_30.12e */
        {0x068741db, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* tke_31.13e */
    }, MAPPER_TK22B, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, "dynwar", 0, -1, CPS1_EXTRA_NONE, 0, 0},
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
    }, MAPPER_S224B, 10, {0xFF, 0xF4, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME ffightj (cps1_10MHz), CPS_B_04 mapper_S222B */
    {"ffightj", "Final Fight (Japan)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_04, 27, {
        {0xf9a5ce83, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* ff36.bin */
        {0x65f11215, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* ff42.bin */
        {0xe1033784, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* ff37.bin */
        {0xb6dee1c3, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* ff43.bin */
        {0x0c8dc3fc, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* ffj_34.10f */
        {0x8075bab9, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* ffj_40.10h */
        {0x4a934121, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* ffj_35.11f */
        {0x2af68154, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* ffj_41.11h */
        {0x5b116d0d, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* ffj_09.4b */
        {0x815b1797, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* ffj_01.4a */
        {0x8721a7da, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* ffj_13.9b */
        {0xd0fcd4b5, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* ffj_05.9a */
        {0xa1ab607a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* ffj_24.5e */
        {0x2dc18cf4, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* ffj_17.5c */
        {0x6535a57f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* ffj_38.8h */
        {0xc8bc4a57, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* ffj_32.8f */
        {0x624a924a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100000, 0},  /* ffj_10.5b */
        {0x5d91f694, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100001, 0},  /* ffj_02.5a */
        {0x0a2e9101, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100002, 0},  /* ffj_14.10b */
        {0x1c18f042, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100003, 0},  /* ffj_06.10a */
        {0x6e8181ea, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100004, 0},  /* ffj_25.7e */
        {0xb19ede59, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100005, 0},  /* ffj_18.7c */
        {0x9416b477, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100006, 0},  /* ffj_39.9h */
        {0x7369fa07, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100007, 0},  /* ffj_33.9f */
        {0xb8367eb5, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ff_23.bin */
        {0x375c66e7, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ffj_30.bin */
        {0x1ef137f9, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* ffj_31.bin */
    }, MAPPER_S222B, 10, {0xFF, 0xF4, 0x9F}, CPS1_NONE, CPS1_NONE, "ffight", 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME ffightj2 (cps1_10MHz), CPS_B_02 mapper_S222B */
    {"ffightj1", "Final Fight (Japan 900305)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_02, 27, {
        {0x088ed1c9, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* ffj_36a.12f */
        {0xc4c491e6, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* ffj_42a.12h */
        {0x708557ff, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* ffj_37a.13f */
        {0xc004004a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* ffj_43a.13h */
        {0x0c8dc3fc, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* ff_34.10f */
        {0x8075bab9, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* ff_40.10h */
        {0x4a934121, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* ff_35.11f */
        {0x2af68154, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* ff_41.11h */
        {0x5b116d0d, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* ff_09.4b */
        {0x815b1797, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* ff_01.4a */
        {0x8721a7da, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* ff_13.9b */
        {0xd0fcd4b5, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* ff_05.9a */
        {0xa1ab607a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* ff_24.5e */
        {0x2dc18cf4, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* ff_17.5c */
        {0x6535a57f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* ff_38.8h */
        {0xc8bc4a57, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* ff_32.8f */
        {0x624a924a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100000, 0},  /* ff_10.5b */
        {0x5d91f694, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100001, 0},  /* ff_02.5a */
        {0x0a2e9101, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100002, 0},  /* ff_14.10b */
        {0x1c18f042, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100003, 0},  /* ff_06.10a */
        {0x6e8181ea, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100004, 0},  /* ff_25.7e */
        {0xb19ede59, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100005, 0},  /* ff_18.7c */
        {0x9416b477, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100006, 0},  /* ff_39.9h */
        {0x7369fa07, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100007, 0},  /* ff_33.9f */
        {0xb8367eb5, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ff_23.13c */
        {0x375c66e7, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ff_30.12e */
        {0x1ef137f9, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* ff_31.13e */
    }, MAPPER_S222B, 10, {0xFF, 0xF4, 0x9F}, CPS1_NONE, CPS1_NONE, "ffight", 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME ffightj1 (cps1_10MHz), CPS_B_01 mapper_S222B */
    {"ffightj2", "Final Fight (Japan 900112)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_01, 27, {
        {0xe2a48af9, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* ffj_36.12f */
        {0xf4bb480e, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* ffj_42.12h */
        {0xc371c667, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* ffj_37.13f */
        {0x6f81f194, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* ffj_43.13h */
        {0x0c8dc3fc, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* ffj_34.10f */
        {0x8075bab9, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* ffj_40.10h */
        {0x4a934121, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* ffj_35.11f */
        {0x2af68154, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* ffj_41.11h */
        {0x5b116d0d, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* ffj_09.4b */
        {0x815b1797, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* ffj_01.4a */
        {0x8721a7da, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* ffj_13.9b */
        {0xd0fcd4b5, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* ffj_05.9a */
        {0xa1ab607a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* ffj_24.5e */
        {0x2dc18cf4, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* ffj_17.5c */
        {0x6535a57f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* ffj_38.8h */
        {0xc8bc4a57, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* ffj_32.8f */
        {0x624a924a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100000, 0},  /* ffj_10.5b */
        {0x5d91f694, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100001, 0},  /* ffj_02.5a */
        {0x0a2e9101, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100002, 0},  /* ffj_14.10b */
        {0x1c18f042, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100003, 0},  /* ffj_06.10a */
        {0x6e8181ea, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100004, 0},  /* ffj_25.7e */
        {0xb19ede59, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100005, 0},  /* ffj_18.7c */
        {0x9416b477, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100006, 0},  /* ffj_39.9h */
        {0x7369fa07, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100007, 0},  /* ffj_33.9f */
        {0xb8367eb5, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ff_23.13b */
        {0x375c66e7, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ffj_30.12c */
        {0x1ef137f9, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* ffj_31.13c */
    }, MAPPER_S222B, 10, {0xFF, 0xF4, 0x9F}, CPS1_NONE, CPS1_NONE, "ffight", 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME ffightu (cps1_10MHz), CPS_B_04 mapper_S224B */
    {"ffightu", "Final Fight (USA, set 1)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_04, 12, {
        {0xf9a5ce83, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 1},  /* ff_36.11f */
        {0x65f11215, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 1},  /* ff_42.11h */
        {0xe1033784, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 1},  /* ff_37.12f */
        {0x4ca65947, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* ffu_43.12h */
        {0xc747696e, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 1},  /* ff-32m.8h */
        {0x9c284108, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* ff-5m.7a */
        {0xa7584dfb, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* ff-7m.9a */
        {0x0b605e44, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* ff-1m.3a */
        {0x52291cd2, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* ff-3m.5a */
        {0xb8367eb5, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* ff_09.12b */
        {0x375c66e7, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* ff_18.11c */
        {0x1ef137f9, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* ff_19.12c */
    }, MAPPER_S224B, 10, {0xFF, 0xF4, 0x9F}, CPS1_NONE, CPS1_NONE, "ffight", 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME ffightua (cps1_10MHz), CPS_B_01 mapper_S224B */
    {"ffightua", "Final Fight (USA 900112)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_01, 12, {
        {0xe2a48af9, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* ffu_36.11f */
        {0xf4bb480e, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* ffu_42.11h */
        {0xc371c667, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* ffu_37.12f */
        {0x2f5771f9, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* ffu_43.12h */
        {0xc747696e, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 1},  /* ff-32m.8h */
        {0x9c284108, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* ff-5m.7a */
        {0xa7584dfb, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* ff-7m.9a */
        {0x0b605e44, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* ff-1m.3a */
        {0x52291cd2, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* ff-3m.5a */
        {0xb8367eb5, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* ff_09.12b */
        {0x375c66e7, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* ff_18.11c */
        {0x1ef137f9, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* ff_19.12c */
    }, MAPPER_S224B, 10, {0xFF, 0xF4, 0x9F}, CPS1_NONE, CPS1_NONE, "ffight", 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME forgottnua (forgottn), CPS_B_01 mapper_LWCHR */
    {"forgott1", "Forgotten Worlds (USA, B-Board 88618B-2, Rev. A)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 256 * K}, CPSB_01, 16, {
        {0xddf78831, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 1},  /* lwu_11a.14f */
        {0xf7ce2097, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 1},  /* lwu_15a.14g */
        {0x8cb38c81, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 1},  /* lwu_10a.13f */
        {0xd70ef9fd, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 1},  /* lwu_14a.13g */
        {0xfd252a26, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* lw-07.13e */
        {0x0318f298, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* lw-01.9d */
        {0x25a8e43c, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* lw-08.9f */
        {0xe4552fd7, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* lw-05.9e */
        {0x8e6a832b, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* lw-12.9g */
        {0x43e6c5c8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 0},  /* lw-02.12d */
        {0x899cb4ad, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* lw-09.12f */
        {0x5b9edffc, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 0},  /* lw-06.12e */
        {0x8e058ef5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* lw-13.12g */
        {0x59df2a63, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* lwu_00.14a */
        {0x807d051f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* lw-03u.14c */
        {0xe6cd098e, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* lw-04u.13c */
    }, MAPPER_LWCHR, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, "forgottn", 1, 0x200000, CPS1_EXTRA_NONE, 0, 0},
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
    }, MAPPER_LWCHR, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, NULL, 1, 0x200000, CPS1_EXTRA_NONE, 0, 0},
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
    }, MAPPER_DM620, 10, {0xFF, 0xFD, 0xFF}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME ghoulsu (cps1_10MHz), CPS_B_01 mapper_DM620 */
    {"ghoulsu", "Ghouls'n Ghosts (USA)", CPS1_PLAIN, {1024 * K, 3072 * K, 64 * K, 0 * K}, CPSB_01, 26, {
        {0x334d85b2, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* dmu_29.10h */
        {0xcee8ceb5, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* dmu_30.10j */
        {0x4a524140, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* dmu_27.9h */
        {0x94aae205, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* dmu_28.9j */
        {0x3ea1b0f2, 512 * K, CPS1_R_MAIN, CPS1_LOAD_PLAIN, 0x080000, 1},  /* dm-17.7j */
        {0x0ba9c0b0, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* dm-05.3a */
        {0x5d760ab9, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* dm-07.3f */
        {0x4ba90b59, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* dm-06.3c */
        {0x4bdee9de, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* dm-08.3g */
        {0xae24bb19, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200000, 1},  /* 09.4a */
        {0xd34e271a, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200001, 1},  /* 18.7a */
        {0x3f70dd37, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200002, 1},  /* 13.4e */
        {0x7e69e2e6, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200003, 1},  /* 22.7e */
        {0x37c9b6c6, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200004, 1},  /* 11.4c */
        {0x2f1345b4, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200005, 1},  /* 20.7c */
        {0x3c2a212a, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200006, 1},  /* 15.4g */
        {0x889aac05, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200007, 1},  /* 24.7g */
        {0xbcc0f28c, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280000, 1},  /* 10.4b */
        {0x2a40166a, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280001, 1},  /* 19.7b */
        {0x20f85c03, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280002, 1},  /* 14.4f */
        {0x8426144b, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280003, 1},  /* 23.7f */
        {0xda088d61, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280004, 1},  /* 12.4d */
        {0x17e11df0, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280005, 1},  /* 21.7d */
        {0xf187ba1c, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280006, 1},  /* 16.4h */
        {0x29f79c78, 64 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x280007, 1},  /* 25.7h */
        {0x3692f6e5, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* 26.10a */
    }, MAPPER_DM620, 10, {0xFF, 0xF7, 0xFF}, CPS1_NONE, CPS1_NONE, "ghouls", 0, -1, CPS1_EXTRA_NONE, 0, 0},
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
    }, MAPPER_KR63B, 10, {0xFF, 0xFC, 0x9F}, 0x36, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_P3, 0, 0},
    /* MAME knightsu (cps1_10MHz), CPS_B_21_BT4 mapper_KR63B */
    {"knightsu", "Knights of the Round (USA 911127)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 256 * K}, CPSB_21_BT4, 13, {
        {0x252bc2ba, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x000000, 0},  /* kr_23u.8f */
        {0xd0b671a9, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 1},  /* kr_22.7f */
        {0x9e36c1a4, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* kr-5m.3a */
        {0xc5832cae, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* kr-7m.5a */
        {0xf095be2d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* kr-1m.4a */
        {0x179dfd96, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* kr-3m.6a */
        {0x1f4298d2, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* kr-6m.7a */
        {0x37fa8751, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* kr-8m.9a */
        {0x0200bc3d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* kr-2m.8a */
        {0x0bb2b4e7, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* kr-4m.10a */
        {0x5e44d9ee, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* kr_09.11a */
        {0xda69d15f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* kr_18.11c */
        {0xbfc654e9, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* kr_19.12c */
    }, MAPPER_KR63B, 10, {0xFF, 0xFC, 0x9F}, 0x36, CPS1_NONE, "knights", 0, -1, CPS1_EXTRA_P3, 0, 0},
    /* MAME kodr1 (cps1_10MHz), CPS_B_21_BT2 mapper_KD29B */
    {"kod", "The King of Dragons (World 910711)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 256 * K}, CPSB_21_BT2, 19, {
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
        {0xf5514510, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* kd_9.12a */
        {0x69ecb2c8, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* kd_18.11c */
        {0x02d851c1, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* kd_19.12c */
    }, MAPPER_KD29B, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_P3, 0, 0},
    /* MAME kodj (cps1_10MHz), CPS_B_21_BT2 mapper_KD29B */
    {"kodj", "The King of Dragons (Japan 910805, B-Board 90629B-3)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 256 * K}, CPSB_21_BT2, 16, {
        {0xebc788ad, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* kdj_30a.11e */
        {0xe55c3529, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* kdj_37a.11f */
        {0xc710d722, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* kdj_31a.12e */
        {0x57d6ed3a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* kdj_38a.12f */
        {0x9bd7ad4b, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* kd_33.6f */
        {0xe45b8701, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* kd_06.8a */
        {0xa7750322, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* kd_08.10a */
        {0x5f74bf78, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* kd_05.7a */
        {0x5e5303bf, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* kd_07.9a */
        {0x113358f3, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* kd_15.8c */
        {0x38853c44, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* kd_17.10c */
        {0x9ef36604, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* kd_14.7c */
        {0x402b9b4f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* kd_16.9c */
        {0xbac6ec26, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* kd_09.12a */
        {0x4c63181d, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* kd_18.11c */
        {0x92941b80, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* kd_19.12c */
    }, MAPPER_KD29B, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "kod", 0, -1, CPS1_EXTRA_P3, 0, 0},
    /* MAME kodu (cps1_10MHz), CPS_B_21_BT2 mapper_KD29B */
    {"kodu", "The King of Dragons (USA 910910)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 256 * K}, CPSB_21_BT2, 19, {
        {0x825817f9, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* kdu_30b.11e */
        {0xd2422dfb, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* kdu_37b.11f */
        {0x9af36039, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* kdu_31b.12e */
        {0xbe8405a1, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* kdu_38b.12f */
        {0x9367bcd9, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 1},  /* kdu_28.9e */
        {0x4ca6a48a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 1},  /* kdu_35.9f */
        {0x0360fa72, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* kdu_29.10e */
        {0x95a3cef8, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* kdu_36a.10f */
        {0xe45b8701, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* kd-5m.4a */
        {0xa7750322, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* kd-7m.6a */
        {0x5f74bf78, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* kd-1m.3a */
        {0x5e5303bf, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* kd-3m.5a */
        {0x113358f3, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* kd-6m.4c */
        {0x38853c44, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* kd-8m.6c */
        {0x9ef36604, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* kd-2m.3c */
        {0x402b9b4f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* kd-4m.5c */
        {0xbac6ec26, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* kd_09.12a */
        {0x4c63181d, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* kd_18.11c */
        {0x92941b80, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* kd_19.12c */
    }, MAPPER_KD29B, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "kod", 0, -1, CPS1_EXTRA_P3, 0, 0},
    /* MAME lostwrld (forgottn), CPS_B_01 mapper_LWCHR */
    {"lostwrld", "Lost Worlds (Japan)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 256 * K}, CPSB_01, 16, {
        {0x67e42546, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* lw_11c.14f */
        {0x402e2a46, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* lw_15c.14g */
        {0xc46479d7, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* lw_10c.13f */
        {0x97670f4a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* lw_14c.13g */
        {0xfd252a26, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 1},  /* lw-07.13e */
        {0x0318f298, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* lw-01.9d */
        {0x25a8e43c, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* lw-08.9f */
        {0xe4552fd7, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* lw-05.9e */
        {0x8e6a832b, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* lw-12.9g */
        {0x43e6c5c8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* lw-02.12d */
        {0x899cb4ad, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* lw-09.12f */
        {0x5b9edffc, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* lw-06.12e */
        {0x8e058ef5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* lw-13.12g */
        {0x59df2a63, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* lw_00b.14a */
        {0xce2159e7, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* lw-03.14c */
        {0x39305536, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* lw-04.13c */
    }, MAPPER_LWCHR, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, "forgottn", 1, 0x200000, CPS1_EXTRA_NONE, 0, 0},
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
    }, MAPPER_O224B, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_P3, 270, 0},
    /* MAME mercsj (cps1_10MHz), CPS_B_12 mapper_O224B */
    {"mercsj", "Senjou no Ookami II (Japan 900302)", CPS1_PLAIN, {1024 * K, 3072 * K, 64 * K, 256 * K}, CPSB_12, 35, {
        {0xe17f9bf7, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* so2_36.12f */
        {0x2c3884c6, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* so2_42.12h */
        {0x51204d36, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* so2_37.13f */
        {0x9cfba8b4, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* so2_43.13h */
        {0xb8dae95f, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* so2_34.10f */
        {0xde37771c, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* so2_40.10h */
        {0x7d24394d, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* so2_35.11f */
        {0x914f85e0, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* so2_41.11h */
        {0x690c261d, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* so2_09.4b */
        {0x31fd2715, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* so2_01.4a */
        {0xb5e48282, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* so2_13.9b */
        {0x54bed82c, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* so2_05.9a */
        {0x78b6f0cb, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* so2_24.5e */
        {0xe78bb308, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* so2_17.5c */
        {0x0010a9a2, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* so2_38.8h */
        {0x75dffc9a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* so2_32.8f */
        {0x2f871714, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100000, 0},  /* so2_10.5b */
        {0xb4b2a0b7, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100001, 0},  /* so2_02.5a */
        {0x737a744b, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100002, 0},  /* so2_14.10b */
        {0x9d756f51, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100003, 0},  /* so2_06.10a */
        {0x6d0e05d6, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100004, 0},  /* so2_25.7e */
        {0x96f61f4e, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100005, 0},  /* so2_18.7c */
        {0xd52ba336, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100006, 0},  /* so2_39.9h */
        {0x39b90d25, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100007, 0},  /* so2_33.9f */
        {0x3f254efe, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200000, 0},  /* so2_11.7b */
        {0xf5a8905e, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200001, 0},  /* so2_03.7a */
        {0xf3aa5a4a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200002, 0},  /* so2_15.11b */
        {0xb43cd1a8, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200003, 0},  /* so2_07.11a */
        {0x8ca751a3, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200004, 0},  /* so2_26.8e */
        {0xe9f569fd, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200005, 0},  /* so2_19.8c */
        {0xfce9a377, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200006, 0},  /* so2_28.10e */
        {0xb7df8a06, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200007, 0},  /* so2_21.10c */
        {0xd09d7c7a, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* so2_23.13b */
        {0xbbea1643, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* so2_30.12c */
        {0xac58aa71, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* so2_31.13c */
    }, MAPPER_O224B, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "mercs", 0, -1, CPS1_EXTRA_P3, 270, 0},
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
    }, MAPPER_MS24B, 10, {0xFF, 0xBC, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME mswordj (cps1_10MHz), CPS_B_13 mapper_MS22B */
    {"mswordj", "Magic Sword: Heroic Fantasy (Japan 900623)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_13, 27, {
        {0x04f0ef50, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* msj_36.12f */
        {0x9fcbb9cd, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* msj_42.12h */
        {0x6c060d70, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* msj_37.13f */
        {0xaec77787, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* msj_43.13h */
        {0x0e59a62d, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* ms_34.10f */
        {0xbabade3a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* ms_40.10h */
        {0x03da99d1, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* ms_35.11f */
        {0xfadf99ea, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* ms_41.11h */
        {0x4adee6f6, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* ms_09.4b */
        {0xf7ab1b88, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* ms_01.4a */
        {0xe01adc4b, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* ms_13.9b */
        {0xf62c2369, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* ms_05.9a */
        {0xbe64a3a1, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* ms_24.5e */
        {0x0bc1665f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* ms_17.5c */
        {0x904a2ed5, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* ms_38.8h */
        {0x3d89c530, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* ms_32.8f */
        {0xf02c0718, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100000, 0},  /* ms_10.5b */
        {0xd071a405, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100001, 0},  /* ms_02.5a */
        {0xdfb2e4df, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100002, 0},  /* ms_14.10b */
        {0xd3ce2a91, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100003, 0},  /* ms_06.10a */
        {0x0f199d56, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100004, 0},  /* ms_25.7e */
        {0x1ba76df2, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100005, 0},  /* ms_18.7c */
        {0x01efce86, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100006, 0},  /* ms_39.9h */
        {0xce25defc, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100007, 0},  /* ms_33.9f */
        {0x57b29519, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ms_23.13b */
        {0xfb64e90d, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* ms_30.12c */
        {0x74f892b9, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* ms_31.13c */
    }, MAPPER_MS22B, 10, {0xFF, 0xBC, 0x9F}, CPS1_NONE, CPS1_NONE, "msword", 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME mswordr1 (cps1_10MHz), CPS_B_13 mapper_MS24B */
    {"mswordr1", "Magic Sword: Heroic Fantasy (World 900623)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_13, 12, {
        {0x21c1f078, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* ms_30.11f */
        {0xa540a73a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* ms_35.11h */
        {0xd7e762b5, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* ms_31.12f */
        {0x66f2dcdb, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* ms_36.12h */
        {0x2475ddfc, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 1},  /* ms-32m.8h */
        {0xc00fe7e2, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* ms-5m.7a */
        {0x4ccacac5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* ms-7m.9a */
        {0x0d2bbe00, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* ms-1m.3a */
        {0x3a1a5bf4, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* ms-3m.5a */
        {0x57b29519, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* ms_09.12b */
        {0xfb64e90d, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* ms_18.11c */
        {0x74f892b9, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* ms_19.12c */
    }, MAPPER_MS24B, 10, {0xFF, 0xBC, 0x9F}, CPS1_NONE, CPS1_NONE, "msword", 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME mswordu (cps1_10MHz), CPS_B_13 mapper_MS24B */
    {"mswordu", "Magic Sword: Heroic Fantasy (USA 900725)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_13, 12, {
        {0xd963c816, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* msu_30.11f */
        {0x72f179b3, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* msu_35.11h */
        {0x20cd7904, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* msu_31.12f */
        {0xbf88c080, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* msu_36.12h */
        {0x2475ddfc, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 1},  /* ms-32m.8h */
        {0xc00fe7e2, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* ms-5m.7a */
        {0x4ccacac5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* ms-7m.9a */
        {0x0d2bbe00, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* ms-1m.3a */
        {0x3a1a5bf4, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* ms-3m.5a */
        {0x57b29519, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* ms_09.12b */
        {0xfb64e90d, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* ms_18.11c */
        {0x74f892b9, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* ms_19.12c */
    }, MAPPER_MS24B, 10, {0xFF, 0xBC, 0x9F}, CPS1_NONE, CPS1_NONE, "msword", 0, -1, CPS1_EXTRA_NONE, 0, 0},
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
    }, MAPPER_CK24B, 10, {0xFF, 0xDF, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0},
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
    }, MAPPER_NM24B, 10, {0xFF, 0xFF, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0},
    /* MAME nemoj (cps1_10MHz), CPS_B_15 mapper_NM24B */
    {"nemoj", "Nemo (Japan 901120, 88622B-3 ROM board)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_15, 27, {
        {0xdaeceabb, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* nmj_36a.12f */
        {0x55024740, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* nmj_42a.12h */
        {0x619068b6, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* nmj_37a.13f */
        {0xa948a53b, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* nmj_43a.13h */
        {0x5737feed, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* nmj_34.10f */
        {0x8a4099f3, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* nmj_40.10h */
        {0xbd11a7f8, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* nmj_35.11f */
        {0x6309603d, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* nmj_41.11h */
        {0x9d60d286, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* nmj_09.4b */
        {0x8a83f7c4, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* nmj_01.4a */
        {0xa4909fe0, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* nmj_13.9b */
        {0x16db1e61, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* nmj_05.9a */
        {0x3312c648, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* nmj_24.5e */
        {0xccfc50e2, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* nmj_17.5c */
        {0xae98a997, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* nmj_38.8h */
        {0xb3704dde, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* nmj_32.8f */
        {0x33c1388c, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100000, 0},  /* nmj_10.5b */
        {0x84c69469, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100001, 0},  /* nmj_02.5a */
        {0x66612270, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100002, 0},  /* nmj_14.10b */
        {0x8b9bcf95, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100003, 0},  /* nmj_06.10a */
        {0xacfc84d2, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100004, 0},  /* nmj_25.7e */
        {0x4347deed, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100005, 0},  /* nmj_18.7c */
        {0x6a274ecd, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100006, 0},  /* nmj_39.9h */
        {0xc469dc74, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100007, 0},  /* nmj_33.9f */
        {0x8d3c5a42, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* nmj_23.13b */
        {0xbab333d4, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* nmj_30.12c */
        {0x2650a0a8, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* nmj_31.13c */
    }, MAPPER_NM24B, 10, {0xFF, 0xFF, 0x9F}, CPS1_NONE, CPS1_NONE, "nemo", 0, -1, CPS1_EXTRA_NONE, 0, 0},
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
    }, MAPPER_STF29, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_KICKS, 0, 0},
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
    }, MAPPER_S9263B, 12, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2ceua (cps1_12MHz), CPS_B_21_DEF mapper_S9263B */
    {"sf2ceua", "Street Fighter II': Champion Edition (USA 920313)", CPS1_PLAIN, {1536 * K, 6144 * K, 64 * K, 256 * K}, CPSB_21_DEF, 18, {
        {0xac44415b, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x000000, 0},  /* s92u_23a.8f */
        {0x99f1cca4, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 1},  /* s92_22a.7f */
        {0x925a7877, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x100000, 1},  /* s92_21a.6f */
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
    }, MAPPER_S9263B, 12, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "sf2ce", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2ceub (cps1_12MHz), CPS_B_21_DEF mapper_S9263B */
    {"sf2ceub", "Street Fighter II': Champion Edition (USA 920513)", CPS1_PLAIN, {1536 * K, 6144 * K, 64 * K, 256 * K}, CPSB_21_DEF, 18, {
        {0x996a3015, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x000000, 0},  /* s92u_23b.8f */
        {0x2bbe15ed, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* s92_22b.7f */
        {0x925a7877, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x100000, 1},  /* s92_21a.6f */
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
    }, MAPPER_S9263B, 12, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "sf2ce", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2ceuc (cps1_12MHz), CPS_B_21_DEF mapper_S9263B */
    {"sf2ceuc", "Street Fighter II': Champion Edition (USA 920803)", CPS1_PLAIN, {1536 * K, 6144 * K, 64 * K, 256 * K}, CPSB_21_DEF, 18, {
        {0x0a8b6aa2, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x000000, 0},  /* s92u_23c.8f */
        {0x5fd8630b, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* s92_22c.7f */
        {0x925a7877, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x100000, 1},  /* s92_21a.6f */
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
    }, MAPPER_S9263B, 12, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "sf2ce", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2eb (cps1_10MHz), CPS_B_17 mapper_STF29 */
    {"sf2eb", "Street Fighter II: The World Warrior (World 910214)", CPS1_PLAIN, {1024 * K, 6144 * K, 64 * K, 256 * K}, CPSB_17, 23, {
        {0x57bd7051, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* sf2e_30b.11e */
        {0x62691cdd, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* sf2e_37b.11f */
        {0xa673143d, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* sf2e_31b.12e */
        {0x4c2ccef7, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* sf2e_38b.12f */
        {0x4009955e, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* sf2_28b.9e */
        {0x8c1f3994, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* sf2_35b.9f */
        {0xbb4af315, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 1},  /* sf2_29b.10e */
        {0xc02a13eb, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 1},  /* sf2_36b.10f */
        {0x22c9cc8e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* sf2-5m.4a */
        {0x57213be8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* sf2-7m.6a */
        {0xba529b4f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* sf2-1m.3a */
        {0x4b1b33a8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* sf2-3m.5a */
        {0x2c7e2229, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* sf2-6m.4c */
        {0xb5548f17, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* sf2-8m.6c */
        {0x14b84312, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* sf2-2m.3c */
        {0x5e9cd89a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* sf2-4m.5c */
        {0x994bfa58, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 1},  /* sf2-13m.4d */
        {0x3e66ad9d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 1},  /* sf2-15m.6d */
        {0xc1befaa8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 1},  /* sf2-9m.3d */
        {0x0627c831, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 1},  /* sf2-11m.5d */
        {0xa4823a1b, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_9.12a */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_18.11c */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* sf2_19.12c */
    }, MAPPER_STF29, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "sf2", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
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
    }, MAPPER_S9263B, 12, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "sf2ce", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2j (cps1_10MHz), CPS_B_13 mapper_STF29 */
    {"sf2j", "Street Fighter II: The World Warrior (Japan 911210, CPS-B-13)", CPS1_PLAIN, {1024 * K, 6144 * K, 64 * K, 256 * K}, CPSB_13, 23, {
        {0x79022b31, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* sf2j30.bin */
        {0x516776ec, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* sf2j37.bin */
        {0xfe15cb39, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* sf2j31.bin */
        {0x38614d70, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* sf2j38.bin */
        {0xd283187a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* sf2j28.bin */
        {0xd28158e4, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* sf2j35.bin */
        {0xbb4af315, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 1},  /* sf2_29a.bin */
        {0xc02a13eb, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 1},  /* sf2_36a.bin */
        {0x22c9cc8e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* sf2_06.8a */
        {0x57213be8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* sf2_08.10a */
        {0xba529b4f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* sf2_05.7a */
        {0x4b1b33a8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* sf2_07.9a */
        {0x2c7e2229, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* sf2_15.8c */
        {0xb5548f17, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* sf2_17.10c */
        {0x14b84312, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* sf2_14.7c */
        {0x5e9cd89a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* sf2_16.9c */
        {0x994bfa58, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 1},  /* sf2_25.8d */
        {0x3e66ad9d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 1},  /* sf2_27.10d */
        {0xc1befaa8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 1},  /* sf2_24.7d */
        {0x0627c831, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 1},  /* sf2_26.9d */
        {0xa4823a1b, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_09.bin */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_18.bin */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* sf2_19.bin */
    }, MAPPER_STF29, 10, {0xFF, 0xF7, 0x9F}, 0x36, CPS1_NONE, "sf2", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2ja (cps1_10MHz), CPS_B_17 mapper_STF29 */
    {"sf2ja", "Street Fighter II: The World Warrior (Japan 910214)", CPS1_PLAIN, {1024 * K, 6144 * K, 64 * K, 256 * K}, CPSB_17, 23, {
        {0x57bd7051, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* sf2j_30a.11e */
        {0x1e1f6844, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* sf2j_37a.11f */
        {0xa673143d, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* sf2j_31a.12e */
        {0x4c2ccef7, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* sf2j_38a.12f */
        {0x4009955e, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* sf2j_28a.9e */
        {0x8c1f3994, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* sf2j_35a.9f */
        {0xbb4af315, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 1},  /* sf2j_29a.10e */
        {0xc02a13eb, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 1},  /* sf2j_36a.10f */
        {0x22c9cc8e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* sf2_06.8a */
        {0x57213be8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* sf2_08.10a */
        {0xba529b4f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* sf2_05.7a */
        {0x4b1b33a8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* sf2_07.9a */
        {0x2c7e2229, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* sf2_15.8c */
        {0xb5548f17, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* sf2_17.10c */
        {0x14b84312, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* sf2_14.7c */
        {0x5e9cd89a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* sf2_16.9c */
        {0x994bfa58, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 1},  /* sf2_25.8d */
        {0x3e66ad9d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 1},  /* sf2_27.10d */
        {0xc1befaa8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 1},  /* sf2_24.7d */
        {0x0627c831, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 1},  /* sf2_26.9d */
        {0xa4823a1b, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2j_09.12a */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2j_18.11c */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* sf2j_19.12c */
    }, MAPPER_STF29, 10, {0xFF, 0xF7, 0x9F}, 0x36, CPS1_NONE, "sf2", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2jc (cps1_10MHz), CPS_B_12 mapper_STF29 */
    {"sf2jc", "Street Fighter II: The World Warrior (Japan 910306)", CPS1_PLAIN, {1024 * K, 6144 * K, 64 * K, 256 * K}, CPSB_12, 23, {
        {0x8add35ec, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* sf2j_30c.11e */
        {0x0d74a256, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* sf2j_37c.11f */
        {0xc4fff4a9, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* sf2j_31c.12e */
        {0x8210fc0e, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* sf2j_38c.12f */
        {0x6eddd5e8, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* sf2j_28c.9e */
        {0x6bcb404c, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* sf2j_35c.9f */
        {0xbb4af315, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 1},  /* sf2j_29a.10e */
        {0xc02a13eb, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 1},  /* sf2j_36a.10f */
        {0x22c9cc8e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* sf2_06.8a */
        {0x57213be8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* sf2_08.10a */
        {0xba529b4f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* sf2_05.7a */
        {0x4b1b33a8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* sf2_07.9a */
        {0x2c7e2229, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* sf2_15.8c */
        {0xb5548f17, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* sf2_17.10c */
        {0x14b84312, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* sf2_14.7c */
        {0x5e9cd89a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* sf2_16.9c */
        {0x994bfa58, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 1},  /* sf2_25.8d */
        {0x3e66ad9d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 1},  /* sf2_27.10d */
        {0xc1befaa8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 1},  /* sf2_24.7d */
        {0x0627c831, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 1},  /* sf2_26.9d */
        {0xa4823a1b, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_09.12a */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2j_18.11c */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* sf2j_19.12c */
    }, MAPPER_STF29, 10, {0xFF, 0xF7, 0x9F}, 0x36, CPS1_NONE, "sf2", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2m3 (sf2m3), HACK_B_1 mapper_S9263B */
    {"sf2m3", "Street Fighter II': Champion Edition (M3, bootleg)", CPS1_PLAIN, {1536 * K, 6144 * K, 64 * K, 256 * K}, HACK_B_1, 18, {
        {0xdb567b66, 512 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* u222chp */
        {0x95ea597e, 512 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* u196chp */
        {0x925a7877, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x100000, 1},  /* s92_21a.bin */
        {0x03b0d852, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* s92_01.bin */
        {0x840289ec, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* s92_02.bin */
        {0xcdb5f027, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* s92_03.bin */
        {0xe2799472, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* s92_04.bin */
        {0xba8a2761, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* s92_05.bin */
        {0xe584bfb5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* s92_06.bin */
        {0x21e3f87d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* s92_07.bin */
        {0xbefc47df, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* s92_08.bin */
        {0x960687d5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 1},  /* s92_10.bin */
        {0x978ecd18, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 1},  /* s92_11.bin */
        {0xd6ec9a0a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 1},  /* s92_12.bin */
        {0xed2c67f6, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 1},  /* s92_13.bin */
        {0x08f6b60e, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* s92_09.bin */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* s92_18.bin */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* s92_19.bin */
    }, MAPPER_S9263B, 10, {0xFF, 0xFF, 0x9F}, CPS1_NONE, CPS1_NONE, "sf2ce", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2red (cps1_12MHz), CPS_B_21_DEF mapper_S9263B */
    {"sf2red", "Street Fighter II': Champion Edition (Red Wave, bootleg, set 1)", CPS1_PLAIN, {1536 * K, 6144 * K, 64 * K, 256 * K}, CPSB_21_DEF, 18, {
        {0x40276abb, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x000000, 0},  /* sf2red.23 */
        {0x18daf387, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* sf2red.22 */
        {0x52c486bb, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x100000, 0},  /* sf2red.21 */
        {0x03b0d852, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* s92_01.bin */
        {0x840289ec, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* s92_02.bin */
        {0xcdb5f027, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* s92_03.bin */
        {0xe2799472, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* s92_04.bin */
        {0xba8a2761, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* s92_05.bin */
        {0xe584bfb5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* s92_06.bin */
        {0x21e3f87d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* s92_07.bin */
        {0xbefc47df, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* s92_08.bin */
        {0x960687d5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 1},  /* s92_10.bin */
        {0x978ecd18, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 1},  /* s92_11.bin */
        {0xd6ec9a0a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 1},  /* s92_12.bin */
        {0xed2c67f6, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 1},  /* s92_13.bin */
        {0x08f6b60e, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* s92_09.bin */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* s92_18.bin */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* s92_19.bin */
    }, MAPPER_S9263B, 12, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "sf2ce", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2ua (cps1_10MHz), CPS_B_17 mapper_STF29 */
    {"sf2ua", "Street Fighter II: The World Warrior (USA 910206)", CPS1_PLAIN, {1024 * K, 6144 * K, 64 * K, 256 * K}, CPSB_17, 23, {
        {0x08beb861, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* sf2u_30a.11e */
        {0xb7638d69, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* sf2u_37a.11f */
        {0x0d5394e0, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* sf2u_31a.12e */
        {0x42d6a79e, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* sf2u_38a.12f */
        {0x387a175c, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* sf2u_28a.9e */
        {0xa1a5adcc, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* sf2u_35a.9f */
        {0xbb4af315, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 1},  /* sf2_29b.10e */
        {0xc02a13eb, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 1},  /* sf2_36b.10f */
        {0x22c9cc8e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* sf2-5m.4a */
        {0x57213be8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* sf2-7m.6a */
        {0xba529b4f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* sf2-1m.3a */
        {0x4b1b33a8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* sf2-3m.5a */
        {0x2c7e2229, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* sf2-6m.4c */
        {0xb5548f17, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* sf2-8m.6c */
        {0x14b84312, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* sf2-2m.3c */
        {0x5e9cd89a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* sf2-4m.5c */
        {0x994bfa58, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 1},  /* sf2-13m.4d */
        {0x3e66ad9d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 1},  /* sf2-15m.6d */
        {0xc1befaa8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 1},  /* sf2-9m.3d */
        {0x0627c831, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 1},  /* sf2-11m.5d */
        {0xa4823a1b, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_9.12a */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_18.11c */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* sf2_19.12c */
    }, MAPPER_STF29, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "sf2", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2ub (cps1_10MHz), CPS_B_17 mapper_STF29 */
    {"sf2ub", "Street Fighter II: The World Warrior (USA 910214)", CPS1_PLAIN, {1024 * K, 6144 * K, 64 * K, 256 * K}, CPSB_17, 23, {
        {0x57bd7051, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* sf2u_30b.11e */
        {0x4a54d479, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* sf2u_37b.11f */
        {0xa673143d, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* sf2u_31b.12e */
        {0x4c2ccef7, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* sf2u_38b.12f */
        {0x4009955e, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* sf2u_28b.9e */
        {0x8c1f3994, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* sf2u_35b.9f */
        {0xbb4af315, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 1},  /* sf2_29b.10e */
        {0xc02a13eb, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 1},  /* sf2_36b.10f */
        {0x22c9cc8e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* sf2-5m.4a */
        {0x57213be8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* sf2-7m.6a */
        {0xba529b4f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* sf2-1m.3a */
        {0x4b1b33a8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* sf2-3m.5a */
        {0x2c7e2229, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* sf2-6m.4c */
        {0xb5548f17, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* sf2-8m.6c */
        {0x14b84312, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* sf2-2m.3c */
        {0x5e9cd89a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* sf2-4m.5c */
        {0x994bfa58, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 1},  /* sf2-13m.4d */
        {0x3e66ad9d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 1},  /* sf2-15m.6d */
        {0xc1befaa8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 1},  /* sf2-9m.3d */
        {0x0627c831, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 1},  /* sf2-11m.5d */
        {0xa4823a1b, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_9.12a */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_18.11c */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* sf2_19.12c */
    }, MAPPER_STF29, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "sf2", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2ud (cps1_10MHz), CPS_B_05 mapper_STF29 */
    {"sf2ud", "Street Fighter II: The World Warrior (USA 910318)", CPS1_PLAIN, {1024 * K, 6144 * K, 64 * K, 256 * K}, CPSB_05, 23, {
        {0x4bb2657c, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* sf2u_30d.11e */
        {0xb33b42f2, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* sf2u_37d.11f */
        {0xd57b67d7, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* sf2u_31d.12e */
        {0x9c8916ef, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* sf2u_38d.12f */
        {0x175819d1, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* sf2u_28d.9e */
        {0x82060da4, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* sf2u_35d.9f */
        {0xbb4af315, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 1},  /* sf2_29b.10e */
        {0xc02a13eb, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 1},  /* sf2_36b.10f */
        {0x22c9cc8e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* sf2-5m.4a */
        {0x57213be8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* sf2-7m.6a */
        {0xba529b4f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* sf2-1m.3a */
        {0x4b1b33a8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* sf2-3m.5a */
        {0x2c7e2229, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* sf2-6m.4c */
        {0xb5548f17, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* sf2-8m.6c */
        {0x14b84312, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* sf2-2m.3c */
        {0x5e9cd89a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* sf2-4m.5c */
        {0x994bfa58, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 1},  /* sf2-13m.4d */
        {0x3e66ad9d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 1},  /* sf2-15m.6d */
        {0xc1befaa8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 1},  /* sf2-9m.3d */
        {0x0627c831, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 1},  /* sf2-11m.5d */
        {0xa4823a1b, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_9.12a */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_18.11c */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* sf2_19.12c */
    }, MAPPER_STF29, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "sf2", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2ue (cps1_10MHz), CPS_B_18 mapper_STF29 */
    {"sf2ue", "Street Fighter II: The World Warrior (USA 910228)", CPS1_PLAIN, {1024 * K, 6144 * K, 64 * K, 256 * K}, CPSB_18, 23, {
        {0xf37cd088, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* sf2u_30e.11e */
        {0x6c61a513, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* sf2u_37e.11f */
        {0x7c4771b4, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* sf2u_31e.12e */
        {0xa4bd0cd9, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* sf2u_38e.12f */
        {0xe3b95625, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* sf2u_28e.9e */
        {0x3648769a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* sf2u_35e.9f */
        {0xbb4af315, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 1},  /* sf2_29b.10e */
        {0xc02a13eb, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 1},  /* sf2_36b.10f */
        {0x22c9cc8e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* sf2-5m.4a */
        {0x57213be8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* sf2-7m.6a */
        {0xba529b4f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* sf2-1m.3a */
        {0x4b1b33a8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* sf2-3m.5a */
        {0x2c7e2229, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* sf2-6m.4c */
        {0xb5548f17, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* sf2-8m.6c */
        {0x14b84312, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* sf2-2m.3c */
        {0x5e9cd89a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* sf2-4m.5c */
        {0x994bfa58, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 1},  /* sf2-13m.4d */
        {0x3e66ad9d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 1},  /* sf2-15m.6d */
        {0xc1befaa8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 1},  /* sf2-9m.3d */
        {0x0627c831, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 1},  /* sf2-11m.5d */
        {0xa4823a1b, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_9.12a */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_18.11c */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* sf2_19.12c */
    }, MAPPER_STF29, 10, {0xFF, 0xFF, 0x9F}, 0x3C, CPS1_NONE, "sf2", 0, -1, CPS1_EXTRA_KICKS, 0, 1},
    /* MAME sf2uf (cps1_10MHz), CPS_B_15 mapper_STF29 */
    {"sf2uf", "Street Fighter II: The World Warrior (USA 910411)", CPS1_PLAIN, {1024 * K, 6144 * K, 64 * K, 256 * K}, CPSB_15, 23, {
        {0xfe39ee33, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 1},  /* sf2u_30f.11e */
        {0x169e7388, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* sf2u_37f.11f */
        {0x69a0a301, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 1},  /* sf2u_31f.12e */
        {0x1510e4e2, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* sf2u_38f.12f */
        {0xacd8175b, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* sf2u_28f.9e */
        {0xc0a80bd1, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* sf2u_35f.9f */
        {0xbb4af315, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 1},  /* sf2_29b.10e */
        {0xc02a13eb, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 1},  /* sf2_36b.10f */
        {0x22c9cc8e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* sf2-5m.4a */
        {0x57213be8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* sf2-7m.6a */
        {0xba529b4f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* sf2-1m.3a */
        {0x4b1b33a8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* sf2-3m.5a */
        {0x2c7e2229, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* sf2-6m.4c */
        {0xb5548f17, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* sf2-8m.6c */
        {0x14b84312, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* sf2-2m.3c */
        {0x5e9cd89a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* sf2-4m.5c */
        {0x994bfa58, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 1},  /* sf2-13m.4d */
        {0x3e66ad9d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 1},  /* sf2-15m.6d */
        {0xc1befaa8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 1},  /* sf2-9m.3d */
        {0x0627c831, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 1},  /* sf2-11m.5d */
        {0xa4823a1b, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_9.12a */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_18.11c */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* sf2_19.12c */
    }, MAPPER_STF29, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "sf2", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2ui (cps1_10MHz), CPS_B_14 mapper_STF29 */
    {"sf2ui", "Street Fighter II: The World Warrior (USA 910522, Rev. I)", CPS1_PLAIN, {1024 * K, 6144 * K, 64 * K, 256 * K}, CPSB_14, 23, {
        {0xfe39ee33, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 1},  /* sf2u_30i.11e */
        {0x9df707dd, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* sf2u_37i.11f */
        {0x69a0a301, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 1},  /* sf2u_31i.12e */
        {0x4cb46daf, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* sf2u_38i.12f */
        {0x1580be4c, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* sf2u_28i.9e */
        {0x1468d185, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* sf2u_35i.9f */
        {0xbb4af315, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 1},  /* sf2_29b.10e */
        {0xc02a13eb, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 1},  /* sf2_36b.10f */
        {0x22c9cc8e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* sf2-5m.4a */
        {0x57213be8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* sf2-7m.6a */
        {0xba529b4f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* sf2-1m.3a */
        {0x4b1b33a8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* sf2-3m.5a */
        {0x2c7e2229, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* sf2-6m.4c */
        {0xb5548f17, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* sf2-8m.6c */
        {0x14b84312, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* sf2-2m.3c */
        {0x5e9cd89a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* sf2-4m.5c */
        {0x994bfa58, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 1},  /* sf2-13m.4d */
        {0x3e66ad9d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 1},  /* sf2-15m.6d */
        {0xc1befaa8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 1},  /* sf2-9m.3d */
        {0x0627c831, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 1},  /* sf2-11m.5d */
        {0xa4823a1b, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_9.12a */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_18.11c */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* sf2_19.12c */
    }, MAPPER_STF29, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "sf2", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2uk (cps1_10MHz), CPS_B_17 mapper_STF29 */
    {"sf2uk", "Street Fighter II: The World Warrior (USA 911101)", CPS1_PLAIN, {1024 * K, 6144 * K, 64 * K, 256 * K}, CPSB_17, 23, {
        {0x8f66076c, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* sf2u_30k.11e */
        {0x4e1f6a83, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* sf2u_37k.11f */
        {0xf9f89f60, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* sf2u_31k.12e */
        {0x6ce0a85a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* sf2u_38k.12f */
        {0x8e958f31, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* sf2u_28k.9e */
        {0xfce76fad, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* sf2u_35k.9f */
        {0xbb4af315, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 1},  /* sf2u_29a.10e */
        {0xc02a13eb, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 1},  /* sf2u_36a.10f */
        {0x22c9cc8e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* sf2-5m.4a */
        {0x57213be8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* sf2-7m.6a */
        {0xba529b4f, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* sf2-1m.3a */
        {0x4b1b33a8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* sf2-3m.5a */
        {0x2c7e2229, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* sf2-6m.4c */
        {0xb5548f17, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* sf2-8m.6c */
        {0x14b84312, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* sf2-2m.3c */
        {0x5e9cd89a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* sf2-4m.5c */
        {0x994bfa58, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 1},  /* sf2-13m.4d */
        {0x3e66ad9d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 1},  /* sf2-15m.6d */
        {0xc1befaa8, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 1},  /* sf2-9m.3d */
        {0x0627c831, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 1},  /* sf2-11m.5d */
        {0xa4823a1b, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_09.12a */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* sf2_18.11c */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* sf2_19.12c */
    }, MAPPER_STF29, 10, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "sf2", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
    /* MAME sf2v004 (cps1_12MHz), CPS_B_21_DEF mapper_S9263B */
    {"sf2v004", "Street Fighter II': Champion Edition (V004, bootleg)", CPS1_PLAIN, {1536 * K, 6144 * K, 64 * K, 256 * K}, CPSB_21_DEF, 18, {
        {0x52d19f2c, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x000000, 0},  /* sf2v004.23 */
        {0x4b26fde7, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* sf2v004.22 */
        {0x52c486bb, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x100000, 0},  /* sf2red.21 */
        {0x03b0d852, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* s92_01.bin */
        {0x840289ec, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* s92_02.bin */
        {0xcdb5f027, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* s92_03.bin */
        {0xe2799472, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* s92_04.bin */
        {0xba8a2761, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200000, 1},  /* s92_05.bin */
        {0xe584bfb5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200002, 1},  /* s92_06.bin */
        {0x21e3f87d, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200004, 1},  /* s92_07.bin */
        {0xbefc47df, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x200006, 1},  /* s92_08.bin */
        {0x960687d5, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400000, 1},  /* s92_10.bin */
        {0x978ecd18, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400002, 1},  /* s92_11.bin */
        {0xd6ec9a0a, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400004, 1},  /* s92_12.bin */
        {0xed2c67f6, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x400006, 1},  /* s92_13.bin */
        {0x08f6b60e, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* s92_09.bin */
        {0x7f162009, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* s92_18.bin */
        {0xbeade53f, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* s92_19.bin */
    }, MAPPER_S9263B, 12, {0xFF, 0xFF, 0x9F}, 0x36, CPS1_NONE, "sf2ce", 0, -1, CPS1_EXTRA_KICKS, 0, 0},
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
    }, MAPPER_ST24M1, 10, {0xFF, 0x8D, 0xFF}, CPS1_NONE, CPS1_NONE, NULL, 0, 0x000000, CPS1_EXTRA_NONE, 0, 0},
    /* MAME striderj (cps1_10MHz), CPS_B_01 mapper_ST22B */
    {"stridrja", "Strider Hiryu (Japan)", CPS1_PLAIN, {1024 * K, 4096 * K, 64 * K, 256 * K}, CPSB_01, 43, {
        {0x53c7b006, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* sth_36.12f */
        {0x4037f65f, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* sth_42.12h */
        {0x80e8877d, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* sth_37.13f */
        {0x6b3fa466, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* sth_43.13h */
        {0xbea770b5, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* sth_34.10f */
        {0x43b922dc, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* sth_40.10h */
        {0x5cc429da, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* sth_35.11f */
        {0x50af457f, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* sth_41.11h */
        {0x1ef6bfbd, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* sth_09.4b */
        {0x1e21b0c1, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* sth_01.4a */
        {0x063263ae, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* sth_13.9b */
        {0xec9f8714, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* sth_05.9a */
        {0x6356f4d2, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* sth_24.5e */
        {0xb4f73d86, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* sth_17.5c */
        {0xee5abfc2, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* sth_38.8h */
        {0x44a206a3, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* sth_32.8f */
        {0xdf3dd3bc, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100000, 0},  /* sth_10.5b */
        {0xc75f9ea0, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100001, 0},  /* sth_02.5a */
        {0x6c03e19d, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100002, 0},  /* sth_14.10b */
        {0xd84f5478, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100003, 0},  /* sth_06.10a */
        {0x921e506a, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100004, 0},  /* sth_25.7e */
        {0x5b318956, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100005, 0},  /* sth_18.7c */
        {0x9321d6aa, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100006, 0},  /* sth_39.9h */
        {0xb47ddfc7, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100007, 0},  /* sth_33.9f */
        {0x2484f241, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200000, 0},  /* sth_11.7b */
        {0xaaa07245, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200001, 0},  /* sth_03.7a */
        {0xe415d943, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200002, 0},  /* sth_15.11b */
        {0x97d072d2, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200003, 0},  /* sth_07.11a */
        {0x0ebfcb02, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200004, 0},  /* sth_26.8e */
        {0x257ce683, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200005, 0},  /* sth_19.8c */
        {0x98ac8cd1, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200006, 0},  /* sth_28.10e */
        {0x538d9423, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x200007, 0},  /* sth_21.10c */
        {0xf670a477, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300000, 0},  /* sth_12.8b */
        {0x853d3e01, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300001, 0},  /* sth_04.8a */
        {0x4092019f, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300002, 0},  /* sth_16.12b */
        {0x2ce9b4c7, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300003, 0},  /* sth_08.12a */
        {0xf82c88d9, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300004, 0},  /* sth_27.9e */
        {0xeb584dd4, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300005, 0},  /* sth_20.9c */
        {0x34ae2997, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300006, 0},  /* sth_29.11e */
        {0x78dd9c48, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x300007, 0},  /* sth_22.11c */
        {0x2ed403bc, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* sth_23.13c */
        {0x4386bc80, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* sth_30.12e */
        {0x444536d7, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* sth_31.13e */
    }, MAPPER_ST22B, 10, {0xFF, 0x8D, 0xFF}, CPS1_NONE, CPS1_NONE, "strider", 0, 0x000000, CPS1_EXTRA_NONE, 0, 0},
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
    }, MAPPER_AR24B, 10, {0xFF, 0xFF, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0},
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
    }, MAPPER_VA24B, 12, {0xFF, 0xF7, 0x9F}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 270, 0},
    /* MAME varthj (cps1_12MHz), CPS_B_21_BT5 mapper_VA22B */
    {"varthj", "Varth: Operation Thunderstorm (Japan 920714)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_21_BT5, 27, {
        {0x1d798d6a, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* vaj_36b.12f */
        {0x0f720233, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* vaj_42b.12h */
        {0x24414b17, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* vaj_37b.13f */
        {0x34b4b06c, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* vaj_43b.13h */
        {0x87c79aed, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* vaj_34b.10f */
        {0x210b4bd0, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* vaj_40b.10h */
        {0x6b0da69f, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* vaj_35b.11f */
        {0x6542c8a4, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* vaj_41b.11h */
        {0x183dfaa8, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000000, 0},  /* va_09.4b */
        {0xc41312b5, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000001, 0},  /* va_01.4a */
        {0x45537e69, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000002, 0},  /* va_13.9b */
        {0x7065d4e9, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000003, 0},  /* va_05.9a */
        {0x57191ccf, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000004, 0},  /* va_24.5e */
        {0x054f5a5b, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000005, 0},  /* va_17.5c */
        {0xe117a17e, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000006, 0},  /* va_38.8h */
        {0x3b4f40b2, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x000007, 0},  /* va_32.8f */
        {0xd62750cd, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100000, 0},  /* va_10.5b */
        {0x11590325, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100001, 0},  /* va_02.5a */
        {0xdc2f4783, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100002, 0},  /* va_14.10b */
        {0x06e833ac, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100003, 0},  /* va_06.10a */
        {0x51d90690, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100004, 0},  /* va_25.7e */
        {0xa17817c0, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100005, 0},  /* va_18.7c */
        {0xb0b12f51, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100006, 0},  /* va_39.9h */
        {0x4b003af7, 128 * K, CPS1_R_GFX, CPS1_LOAD_GFX8, 0x100007, 0},  /* va_33.9f */
        {0x7a99446e, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* va_23.13c */
        {0xde30510e, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* va_30.12e */
        {0x0610a4ac, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* va_31.13e */
    }, MAPPER_VA22B, 12, {0xFF, 0xF7, 0x9F}, CPS1_NONE, CPS1_NONE, "varth", 0, -1, CPS1_EXTRA_NONE, 270, 0},
    /* MAME varthr1 (cps1_12MHz), CPS_B_04 mapper_VA24B */
    {"varthr1", "Varth: Operation Thunderstorm (World 920612)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_04, 15, {
        {0x7fcd0091, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* vae_30a.11f */
        {0x35cf9509, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* vae_35a.11h */
        {0x15e5ee81, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* vae_31a.12f */
        {0x153a201e, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* vae_36a.12h */
        {0x7a0e0d25, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x080000, 0},  /* vae_28a.9f */
        {0xf2365922, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x080001, 0},  /* vae_33a.9h */
        {0x5e2cd2c3, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x0C0000, 0},  /* vae_29a.10f */
        {0x3d9bdf83, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x0C0001, 0},  /* vae_34a.10h */
        {0xb1fb726e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 1},  /* va-5m.7a */
        {0x4c6588cd, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 1},  /* va-7m.9a */
        {0x0b1ace37, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 1},  /* va-1m.3a */
        {0x44dfe706, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 1},  /* va-3m.5a */
        {0x7a99446e, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 1},  /* va_09.12b */
        {0xde30510e, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 1},  /* va_18.11c */
        {0x0610a4ac, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 1},  /* va_19.12c */
    }, MAPPER_VA24B, 12, {0xFF, 0xF7, 0x9F}, CPS1_NONE, CPS1_NONE, "varth", 0, -1, CPS1_EXTRA_NONE, 270, 0},
    /* MAME varthu (cps1_12MHz), CPS_B_04 mapper_VA63B */
    {"varthu", "Varth: Operation Thunderstorm (USA 920612)", CPS1_PLAIN, {1024 * K, 2048 * K, 64 * K, 256 * K}, CPSB_04, 9, {
        {0xfbe68726, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x000000, 0},  /* vau_23a.8f */
        {0x0ed71bbd, 512 * K, CPS1_R_MAIN, CPS1_LOAD_SWAP16, 0x080000, 0},  /* vau_22a.7f */
        {0xb1fb726e, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000000, 0},  /* va-5m.3a */
        {0x4c6588cd, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000002, 0},  /* va-7m.5a */
        {0x0b1ace37, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000004, 0},  /* va-1m.4a */
        {0x44dfe706, 512 * K, CPS1_R_GFX, CPS1_LOAD_GFX4, 0x000006, 0},  /* va-3m.6a */
        {0x7a99446e, 64 * K, CPS1_R_SOUND, CPS1_LOAD_PLAIN, 0x000000, 0},  /* va_09.11a */
        {0xde30510e, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x000000, 0},  /* va_18.11c */
        {0x0610a4ac, 128 * K, CPS1_R_OKI, CPS1_LOAD_PLAIN, 0x020000, 0},  /* va_19.12c */
    }, MAPPER_VA63B, 12, {0xFF, 0xF7, 0x9F}, CPS1_NONE, CPS1_NONE, "varth", 0, -1, CPS1_EXTRA_NONE, 270, 0},
    /* MAME willowu (cps1_10MHz), CPS_B_03 mapper_WL24B */
    {"willow", "Willow (USA)", CPS1_PLAIN, {1024 * K, 3072 * K, 64 * K, 256 * K}, CPSB_03, 20, {
        {0xd604dbb1, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x000000, 0},  /* wlu_30.11f */
        {0x7a791e77, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x000001, 0},  /* 35.11h */
        {0x0eb48a83, 128 * K, CPS1_R_MAIN, CPS1_LOAD_EVEN, 0x040000, 0},  /* wlu_31.12f */
        {0x36100209, 128 * K, CPS1_R_MAIN, CPS1_LOAD_ODD, 0x040001, 0},  /* wlu_36.12h */
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
    }, MAPPER_WL24B, 10, {0xFF, 0xFF, 0xFF}, CPS1_NONE, CPS1_NONE, NULL, 0, -1, CPS1_EXTRA_NONE, 0, 0},
};
const int cps1_game_count = (int)(sizeof cps1_games / sizeof cps1_games[0]);
