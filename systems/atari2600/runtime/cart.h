#ifndef ATARI2600_CART_H
#define ATARI2600_CART_H

#include <stddef.h>
#include <stdint.h>

/* New types go at the end: recompiled programs store the number. */
typedef enum {
    A26_CART_AUTO, A26_CART_2K, A26_CART_4K,
    A26_CART_F8, A26_CART_F6, A26_CART_F4,
    A26_CART_F8SC, A26_CART_F6SC, A26_CART_F4SC,  /* Superchip: 128 bytes of RAM */
    A26_CART_FA,                                  /* CBS RAM Plus: 3 x 4K, 256 bytes of RAM */
    A26_CART_E0,                                  /* Parker Brothers: 1K slices */
    A26_CART_E7,                                  /* M Network: 2K banks, 2K of RAM */
    A26_CART_3F                                   /* Tigervision: 2K banks, switched by writes to $00-$3F */
} A26CartType;

/* The caller owns the ROM bytes for the lifetime of the cartridge. */
typedef struct {
    const uint8_t *rom;
    size_t size;
    A26CartType type;
    unsigned bank;      /* the 4K bank (2K..F4SC, FA) */
    unsigned banks;
    uint8_t slice[4];   /* E0: the 1K at $1000/$1400/$1800; E7: [0] the 2K at $1000, [1] the RAM bank; 3F: [0] */
    uint8_t ram[2048];
} A26Cart;

/* Returns -1 for an unsupported size, type, or size/type combination. */
int a26_cart_init(A26Cart *cart, const uint8_t *rom, size_t size, A26CartType type);
void a26_cart_reset(A26Cart *cart);
uint8_t a26_cart_read(A26Cart *cart, uint16_t address);
void a26_cart_write(A26Cart *cart, uint16_t address, uint8_t value);
/* A write outside the cartridge ($0000-$0FFF): 3F switches on $00-$3F. */
void a26_cart_tia_write(A26Cart *cart, uint16_t address, uint8_t value);
/* Whether the recompiler handles this type (one 4K bank at a time, no RAM). */
int a26_cart_recompilable(A26CartType type);

#endif
