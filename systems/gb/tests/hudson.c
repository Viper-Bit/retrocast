#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>

#include "cart.h"

static GbCart cart;
static uint8_t rom[0x10000];

static void load(uint8_t type) {
    char err[80];
    rom[0x147] = type;
    rom[0x148] = 1;
    rom[0x149] = 3;
    rom[0xC000] = 0x53;
    assert(gb_cart_load(&cart, rom, sizeof rom, err, sizeof err) == 0);
    gb_cart_write(&cart, 0x2000, 3);
    assert(gb_cart_read(&cart, 0x4000) == 0x53);
}

static unsigned clock_cmd(uint8_t cmd) {
    gb_cart_write(&cart, 0x0000, 0x0B);
    gb_cart_write(&cart, 0xA000, cmd);
    gb_cart_write(&cart, 0x0000, 0x0D);
    assert(gb_cart_read(&cart, 0xA123) & 1);
    gb_cart_write(&cart, 0xA000, 0xFE);
    gb_cart_write(&cart, 0x0000, 0x0C);
    return gb_cart_read(&cart, 0xA000) & 15;
}

int main(void) {
    load(0xFF);
    gb_cart_write(&cart, 0x4000, 2);
    gb_cart_write(&cart, 0xA123, 0x42);
    gb_cart_write(&cart, 0x0000, 0x0E);
    gb_cart_write(&cart, 0xA123, 0);
    assert(gb_cart_read(&cart, 0xA123) == 0xC0);
    gb_cart_write(&cart, 0x0000, 0);
    assert(gb_cart_read(&cart, 0xA123) == 0x42);
    gb_cart_write(&cart, 0x4000, 0);
    assert(gb_cart_read(&cart, 0xA123) == 0);
    gb_cart_free(&cart);

    load(0xFE);
    gb_cart_write(&cart, 0x0000, 0x0A);
    gb_cart_write(&cart, 0xA000, 0x34);
    gb_cart_write(&cart, 0x0000, 0);
    gb_cart_write(&cart, 0xA000, 0x12);
    assert(gb_cart_read(&cart, 0xA000) == 0x34);
    assert(clock_cmd(0x62) == 1);
    gb_cart_rtc_advance(&cart, 86400 + 60);
    clock_cmd(0x60);
    clock_cmd(0x40);
    clock_cmd(0x50);
    assert(clock_cmd(0x10) == 1 && clock_cmd(0x10) == 0);
    clock_cmd(0x43);
    assert(clock_cmd(0x10) == 1);
    gb_cart_free(&cart);
    return 0;
}
