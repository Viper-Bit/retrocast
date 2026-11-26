#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "cart.h"

int main(void) {
    uint8_t rom[32768];
    A26Cart cart;
    for (unsigned bank = 0; bank < 8; bank++)
        memset(rom + bank * 4096, (int)bank, 4096);

    assert(a26_cart_init(&cart, rom, 2048, A26_CART_AUTO) == 0);
    rom[0x123] = 0xA5;
    assert(a26_cart_read(&cart, 0x1123) == 0xA5);
    assert(a26_cart_read(&cart, 0x1923) == 0xA5);
    assert(a26_cart_init(&cart, rom, 4096, A26_CART_AUTO) == 0);
    assert(a26_cart_read(&cart, 0x1123) == 0xA5);

    const size_t sizes[] = {8192, 16384, 32768};
    const unsigned counts[] = {2, 4, 8};
    const unsigned first[] = {0xFF8, 0xFF6, 0xFF4};
    for (unsigned type = 0; type < 3; type++) {
        assert(a26_cart_init(&cart, rom, sizes[type], A26_CART_AUTO) == 0);
        assert(cart.bank == counts[type] - 1);
        for (unsigned bank = 0; bank < counts[type]; bank++) {
            assert(a26_cart_read(&cart, (uint16_t)(0x1000 + first[type] + bank)) == bank);
            a26_cart_write(&cart, (uint16_t)(0xF000 + first[type] + bank), 0);
            assert(cart.bank == bank);
        }
        a26_cart_reset(&cart);
        assert(cart.bank == counts[type] - 1);
    }
    assert(a26_cart_init(&cart, rom, 4096, A26_CART_F8) == -1);
    assert(a26_cart_init(&cart, rom, 1234, A26_CART_AUTO) == -1);

    /* every 1K of the image holds its own index, so a read shows which 1K is mapped */
    for (unsigned k = 0; k < 32; k++) memset(rom + k * 1024, (int)k, 1024);

    /* E0 (Parker Brothers): $1000/$1400/$1800 each pick one of 8 1K slices
       ($1FE0-7, $1FE8-F, $1FF0-7); $1C00 is always the last; starts at 4, 5, 6 */
    assert(a26_cart_init(&cart, rom, 8192, A26_CART_E0) == 0);
    assert(a26_cart_read(&cart, 0x1000) == 4 && a26_cart_read(&cart, 0x1400) == 5);
    assert(a26_cart_read(&cart, 0x1800) == 6 && a26_cart_read(&cart, 0x1C00) == 7);
    a26_cart_read(&cart, 0x1FE2);
    a26_cart_write(&cart, 0x1FEB, 0);
    a26_cart_read(&cart, 0x1FF1);
    assert(a26_cart_read(&cart, 0x1000) == 2 && a26_cart_read(&cart, 0x1400) == 3);
    assert(a26_cart_read(&cart, 0x1800) == 1 && a26_cart_read(&cart, 0x1FFF) == 7);

    /* 3F (Tigervision): a write to $00-$3F picks the 2K at $1000; $1800 is the last 2K */
    assert(a26_cart_init(&cart, rom, 8192, A26_CART_3F) == 0);
    assert(a26_cart_read(&cart, 0x1000) == 0 && a26_cart_read(&cart, 0x1800) == 6);
    a26_cart_tia_write(&cart, 0x003F, 2);
    assert(a26_cart_read(&cart, 0x1000) == 4 && a26_cart_read(&cart, 0x1400) == 5);
    a26_cart_tia_write(&cart, 0x0040, 1);  /* past $3F: not a hotspot */
    assert(a26_cart_read(&cart, 0x1000) == 4);

    /* FA (CBS RAM Plus): 3 4K banks at $1FF8-A; 256 bytes of RAM, written at $1000, read at $1100 */
    assert(a26_cart_init(&cart, rom, 12288, A26_CART_FA) == 0);
    assert(a26_cart_read(&cart, 0x1200) == 8);
    a26_cart_read(&cart, 0x1FF8);
    assert(a26_cart_read(&cart, 0x1200) == 0);
    a26_cart_write(&cart, 0x1012, 0x5A);
    assert(a26_cart_read(&cart, 0x1112) == 0x5A);

    /* Superchip (F8SC, F6SC, F4SC): 128 bytes of RAM, written at $1000, read at $1080 */
    assert(a26_cart_init(&cart, rom, 8192, A26_CART_F8SC) == 0);
    a26_cart_write(&cart, 0x1005, 0x77);
    assert(a26_cart_read(&cart, 0x1085) == 0x77);
    a26_cart_read(&cart, 0x1FF8);
    assert(a26_cart_read(&cart, 0x1085) == 0x77 && a26_cart_read(&cart, 0x1200) == 0);

    /* E7 (M Network), 16K: $1000 is one of 2K banks 0-6 ($1FE0-6) or, at $1FE7, 1K of RAM
       (written at $1000, read at $1400); $1800 is a 256-byte RAM bank ($1FE8-B, written at
       $1800, read at $1900); $1A00-$1FFF is the last 2K bank's last 1.5K */
    assert(a26_cart_init(&cart, rom, 16384, A26_CART_E7) == 0);
    assert(a26_cart_read(&cart, 0x1000) == 0 && a26_cart_read(&cart, 0x1C00) == 15);
    a26_cart_read(&cart, 0x1FE3);
    assert(a26_cart_read(&cart, 0x1000) == 6 && a26_cart_read(&cart, 0x1400) == 7);
    a26_cart_read(&cart, 0x1FE7);
    a26_cart_write(&cart, 0x1010, 0x33);
    assert(a26_cart_read(&cart, 0x1410) == 0x33);
    a26_cart_read(&cart, 0x1FE9);
    a26_cart_write(&cart, 0x1820, 0x44);
    assert(a26_cart_read(&cart, 0x1920) == 0x44);
    a26_cart_read(&cart, 0x1FE8);
    assert(a26_cart_read(&cart, 0x1920) != 0x44);
    a26_cart_read(&cart, 0x1FE9);
    assert(a26_cart_read(&cart, 0x1920) == 0x44 && a26_cart_read(&cart, 0x1410) == 0x33);
    /* 12K: six banks, $1FE0-7 -> 0, 1, 0, 1, 2, 3, 4, RAM */
    assert(a26_cart_init(&cart, rom, 12288, A26_CART_E7) == 0);
    a26_cart_read(&cart, 0x1FE4);
    assert(a26_cart_read(&cart, 0x1000) == 4);
    a26_cart_read(&cart, 0x1FE3);
    assert(a26_cart_read(&cart, 0x1000) == 2);

    /* detection, by Stella's signatures (docs/sources.md) */
    static uint8_t img[32768];
    memset(img, 0xEA, sizeof img);
    memcpy(img + 100, (const uint8_t[]){0x8D, 0xE0, 0x1F}, 3);
    img[0] = 1;  /* not a Superchip image */  /* STA $1FE0 */
    assert(a26_cart_init(&cart, img, 8192, A26_CART_AUTO) == 0 && cart.type == A26_CART_E0);
    memset(img, 0xEA, sizeof img);
    memcpy(img + 100, (const uint8_t[]){0x85, 0x3F, 0, 0x85, 0x3F}, 5);
    img[0] = 1;  /* not a Superchip image */  /* STA $3F twice */
    assert(a26_cart_init(&cart, img, 8192, A26_CART_AUTO) == 0 && cart.type == A26_CART_3F);
    memset(img, 0xEA, sizeof img);
    memcpy(img + 100, (const uint8_t[]){0xAD, 0xE5, 0x1F}, 3);
    img[0] = 1;  /* not a Superchip image */  /* LDA $1FE5 */
    assert(a26_cart_init(&cart, img, 16384, A26_CART_AUTO) == 0 && cart.type == A26_CART_E7);
    assert(a26_cart_init(&cart, img, 12288, A26_CART_AUTO) == 0 && cart.type == A26_CART_E7);
    memset(img, 0xEA, sizeof img);
    img[300] = 1;
    assert(a26_cart_init(&cart, img, 12288, A26_CART_AUTO) == 0 && cart.type == A26_CART_FA);
    assert(a26_cart_init(&cart, img, 8192, A26_CART_AUTO) == 0 && cart.type == A26_CART_F8SC);
    assert(a26_cart_init(&cart, img, 32768, A26_CART_AUTO) == 0 && cart.type == A26_CART_F4SC);
    img[5] = 1;  /* the first 128 bytes no longer repeat: no Superchip */
    assert(a26_cart_init(&cart, img, 16384, A26_CART_AUTO) == 0 && cart.type == A26_CART_F6);
    puts("Atari 2600 cartridge tests passed");
    return 0;
}
