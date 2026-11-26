/* A cartridge's serial EEPROM (I2C, 24C01 to 24C65), on the lines some games
 * wire to $200000/$200001 in place of battery RAM. The chip, its size and
 * wiring per game: MAME's src/devices/bus/megadrive/eeprom.cpp (docs/sources.md).
 * Codemasters' J-Cart EEPROMs ($300000/$380001) are not here. */
#ifndef MD_EEPROM_H
#define MD_EEPROM_H

#include <stdint.h>

typedef struct {
    uint8_t mem[8192];
    uint16_t size;          /* bytes; 0: no EEPROM */
    uint8_t mode;           /* 1: X24C01 (the first byte is the address); 2: a device select, then an
                             * address byte (24C02-24C16, block bits in the select); 3: two address bytes */
    uint8_t page;           /* a write's page, minus one (writes wrap inside it) */
    uint32_t sda_in, sda_out, scl;           /* byte addresses of the lines */
    uint8_t sda_in_bit, sda_out_bit, scl_bit;
    /* the bus: lines the 68000 drives, the chip's own SDA (1: released) */
    uint8_t line_scl, line_sda, out;
    uint8_t state, bit, shift, block, data, acked, master_ack;
    uint16_t addr;
} MdEeprom;

/* Sets up the EEPROM for a ROM (its product code, or the header's EEPROM flag); size 0 if none. */
void md_eeprom_setup(MdEeprom *e, const uint8_t *rom);
/* The 68000 writes the byte at a ($200000 or $200001); returns whether it is the EEPROM's. */
int md_eeprom_write(MdEeprom *e, uint32_t a, uint8_t v);
/* The byte at a, as the EEPROM drives it (its SDA bit; the rest 0). */
uint8_t md_eeprom_read(const MdEeprom *e, uint32_t a);
/* The lines themselves (for the tests and the write above). */
void md_eeprom_lines(MdEeprom *e, int scl, int sda);

#endif
