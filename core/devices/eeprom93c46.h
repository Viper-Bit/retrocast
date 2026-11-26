/* The 93C46 serial EEPROM: 1 Kbit, as 64 16-bit cells or 128 bytes (its ORG
 * pin), driven by three lines (CS, CLK, DI) and read on one (DO). A command
 * starts when CS rises: a start bit 1, a 2-bit opcode and the address, then
 * data for a write. READ shifts out a dummy 0, then the cell; WRITE, ERASE,
 * WRAL and ERAL need EWEN first and leave DO low (busy) for their time
 * while the next command waits for its start bit. MAME 0.289's
 * eeprom_serial_93cxx_device (eepromser.cpp, eeprom.cpp), ported without
 * the streaming reads no 93C46 user needs (docs/sources.md). */
#ifndef EEPROM93C46_H
#define EEPROM93C46_H

#include <stdint.h>

typedef struct {
    uint8_t data[128];     /* as MAME's nvram file: 16-bit cells little-endian */
    uint8_t org8;          /* 1: 128 bytes, 7 address bits; 0: 64 words, 6 */
    uint8_t state, cs, clk, di, locked, command;
    uint8_t bits;          /* clocked so far in this phase */
    uint16_t accum;        /* the opcode and address as clocked */
    uint16_t address;
    uint32_t shift;
    uint64_t busy_until;   /* microseconds: the end of the last write or erase */
} Eeprom93c46;

void eeprom_init(Eeprom93c46 *e, int org8);  /* every cell $FF..., locked: MAME's default */
/* The lines after a write of the port, at time now (microseconds); edges
 * are taken in DI, CLK, CS order, as MAME's port bits. */
void eeprom_write_lines(Eeprom93c46 *e, int cs, int clk, int di, uint64_t now);
/* 93LC56 in 16-bit mode, with separate battery storage. Initialize e with org8=0. */
void eeprom93lc56_write(Eeprom93c46 *e, uint8_t data[256], uint8_t port, uint64_t now);
int eeprom_do(const Eeprom93c46 *e, uint64_t now);

#endif
