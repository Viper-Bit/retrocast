// SPDX-License-Identifier: BSD-3-Clause
#pragma once

#include <stdint.h>

// Words are in host order. The separate opcode buffer must hold bytes / 2 words.
void cps2_decrypt(const uint16_t *rom, uint16_t *opcodes, int bytes, const uint8_t key_rom[20]);
