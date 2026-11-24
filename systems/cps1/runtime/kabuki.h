/* The Kabuki: the Q-Sound board's Z80, which runs encrypted code. Each byte
 * is decoded by its address and whether it is an opcode or data (bit-pair
 * swaps, rotations and an XOR, keyed per game). MAME 0.289 kabuki.cpp,
 * ported (docs/sources.md). */
#ifndef CPS1_KABUKI_H
#define CPS1_KABUKI_H

#include <stdint.h>

void kabuki_decode(const uint8_t *src, uint8_t *opcodes, uint8_t *data, int base, int length, uint32_t swap_key1,
                   uint32_t swap_key2, uint16_t addr_key, uint8_t xor_key);
/* The first 32 KB of a Q-Sound game's Z80 ROM, decoded with the key of init
 * (CPS1_INIT_WOF, _DINO, _PUNISHER or _SLAMMAST, cps1.h). */
void cps1_kabuki(int init, const uint8_t *rom, uint8_t *opcodes, uint8_t *data);

#endif
