/* Game Boy cartridges: the header, ROM only, MBC1, MBC2, MBC3 (with its
 * clock), MBC5 and MBC7 (Pan Docs). */
#ifndef GB_CART_H
#define GB_CART_H

#include <stddef.h>
#include <stdint.h>
#include "eeprom93c46.h"

enum { MBC_NONE, MBC_1, MBC_2, MBC_3, MBC_5, MBC_7, MBC_HUC1, MBC_HUC3 };

typedef struct {
    uint8_t *rom;
    uint32_t rom_size;          /* bytes, a power of two (32 KB and up) */
    uint8_t ram[0x20000];       /* battery storage (MBC2: 512 half-bytes; MBC7: EEPROM) */
    uint32_t ram_size;
    uint8_t type, mbc, battery, has_rtc;
    uint8_t multicart;          /* MBC1M: bank bits 4-5 sit one place lower (shift 4, not 5) */
    char title[17];
    /* banking */
    uint8_t ram_on, mode;       /* RAM (and clock) enabled; MBC1 banking mode */
    uint16_t rom_bank;          /* MBC1: the 5-bit register; others: the bank at $4000 */
    uint8_t bank2;              /* MBC1: the 2-bit register; MBC3/5: RAM bank (MBC3 $08-$0C: clock) */
    /* MBC3 clock: seconds, minutes, hours, day low, day high (bit 0 day
     * bit 8, bit 6 halt, bit 7 carry); counted in emulated time */
    uint8_t rtc[5], rtc_latched[5], latch_prev;
    uint32_t rtc_cycles;        /* M-cycles into the current second */
    union {
        Eeprom93c46 eeprom;
        struct {
            uint8_t nvram[128];  /* 256 RTC MCU nibbles, low nibble first */
            uint8_t addr, command;
        } huc3;
    };
    uint64_t mbc7_cycles;      /* normal-speed M-cycles */
    uint16_t tilt_x, tilt_y;  /* latched accelerometer values */
    int8_t tilt_dx, tilt_dy;  /* simulated gravity in whole g */
    uint8_t tilt_ready;
} GbCart;

/* Copies the ROM. 0 on success, else a message in err. */
int gb_cart_load(GbCart *c, const uint8_t *data, size_t size, char *err, size_t errlen);
void gb_cart_free(GbCart *c);
uint8_t gb_cart_read(const GbCart *c, uint16_t addr);    /* $0000-$7FFF, $A000-$BFFF */
uint32_t gb_cart_bank(const GbCart *c, uint16_t addr);   /* the ROM bank mapped at addr ($0000-$7FFF) */
void gb_cart_write(GbCart *c, uint16_t addr, uint8_t v);
void gb_cart_tick(GbCart *c);                            /* one normal-speed M-cycle */
void gb_cart_rtc_advance(GbCart *c, uint64_t seconds);  /* time that passed with the program closed */

#endif
