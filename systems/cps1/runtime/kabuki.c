/* The Kabuki's decoding (kabuki.h), adapted from MAME 0.289's kabuki.cpp.
 * license:BSD-3-Clause; copyright-holders: Nicola Salmoria (MAME). */
#include "kabuki.h"

#include "cps1.h"

/* Swap the bit pairs (0,1), (2,3), (4,5), (6,7) whose select bit the key's nibbles name. */
static int bitswap1(int src, int key, int select) {
    if (select & (1 << ((key >> 0) & 7))) src = (src & 0xFC) | ((src & 0x01) << 1) | ((src & 0x02) >> 1);
    if (select & (1 << ((key >> 4) & 7))) src = (src & 0xF3) | ((src & 0x04) << 1) | ((src & 0x08) >> 1);
    if (select & (1 << ((key >> 8) & 7))) src = (src & 0xCF) | ((src & 0x10) << 1) | ((src & 0x20) >> 1);
    if (select & (1 << ((key >> 12) & 7))) src = (src & 0x3F) | ((src & 0x40) << 1) | ((src & 0x80) >> 1);
    return src;
}

/* The same pairs, the key's nibbles in the other order. */
static int bitswap2(int src, int key, int select) {
    if (select & (1 << ((key >> 12) & 7))) src = (src & 0xFC) | ((src & 0x01) << 1) | ((src & 0x02) >> 1);
    if (select & (1 << ((key >> 8) & 7))) src = (src & 0xF3) | ((src & 0x04) << 1) | ((src & 0x08) >> 1);
    if (select & (1 << ((key >> 4) & 7))) src = (src & 0xCF) | ((src & 0x10) << 1) | ((src & 0x20) >> 1);
    if (select & (1 << ((key >> 0) & 7))) src = (src & 0x3F) | ((src & 0x40) << 1) | ((src & 0x80) >> 1);
    return src;
}

static int rol(int v) { return ((v & 0x7F) << 1) | ((v & 0x80) >> 7); }

static uint8_t bytedecode(int src, uint32_t swap_key1, uint32_t swap_key2, uint8_t xor_key, int select) {
    src = bitswap1(src, swap_key1 & 0xFFFF, select & 0xFF);
    src = rol(src);
    src = bitswap2(src, swap_key1 >> 16, select & 0xFF);
    src ^= xor_key;
    src = rol(src);
    src = bitswap2(src, swap_key2 & 0xFFFF, select >> 8);
    src = rol(src);
    return (uint8_t)bitswap1(src, swap_key2 >> 16, select >> 8);
}

void kabuki_decode(const uint8_t *src, uint8_t *opcodes, uint8_t *data, int base, int length, uint32_t swap_key1,
                   uint32_t swap_key2, uint16_t addr_key, uint8_t xor_key) {
    for (int a = 0; a < length; a++) {
        uint8_t b = src[a];  /* src may be data: read before writing */
        opcodes[a] = bytedecode(b, swap_key1, swap_key2, xor_key, a + base + addr_key);
        data[a] = bytedecode(b, swap_key1, swap_key2, xor_key, ((a + base) ^ 0x1FC0) + addr_key + 1);
    }
}

void cps1_kabuki(int init, const uint8_t *rom, uint8_t *opcodes, uint8_t *data) {
    static const struct { uint32_t k1, k2; uint16_t addr; uint8_t x; } keys[4] = {
        {0x01234567, 0x54163072, 0x5151, 0x51},   /* Warriors of Fate */
        {0x76543210, 0x24601357, 0x4343, 0x43},   /* Cadillacs and Dinosaurs */
        {0x67452103, 0x75316024, 0x2222, 0x22},   /* The Punisher */
        {0x54321076, 0x65432107, 0x3131, 0x19}};  /* Slam Masters, Muscle Bomber Duo */
    int k = init - CPS1_INIT_WOF;
    kabuki_decode(rom, opcodes, data, 0, 0x8000, keys[k].k1, keys[k].k2, keys[k].addr, keys[k].x);
}
