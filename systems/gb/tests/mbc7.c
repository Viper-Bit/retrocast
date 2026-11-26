#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <string.h>

#include "gb.h"
#include "input_log.h"

static void send(GbCart *c, unsigned bits, unsigned count) {
    while (count--) {
        uint8_t port = (uint8_t)(0x80 | (bits >> count & 1) << 1);
        gb_cart_write(c, 0xA080, port);
        gb_cart_write(c, 0xA080, port | 0x40);
    }
}

static void command(GbCart *c, unsigned cmd) {
    gb_cart_write(c, 0xA080, 0);
    gb_cart_write(c, 0xA080, 0x80);
    send(c, 0x400 | cmd, 11);
}

static unsigned read_word(GbCart *c, unsigned addr) {
    command(c, 0x200 | addr);
    assert(!(gb_cart_read(c, 0xA080) & 1));  /* dummy bit */
    unsigned word = 0;
    for (int i = 0; i < 16; i++) {
        send(c, 0, 1);
        word = word << 1 | (gb_cart_read(c, 0xA080) & 1);
    }
    return word;
}

int main(void) {
    static uint8_t rom[0x10000];
    static Gb g;
    rom[0x147] = 0x22;
    rom[0x148] = 1;
    rom[0] = 0x10;
    rom[0xC000] = 0x13;
    char err[80];
    assert(gb_load(&g, rom, sizeof rom, err, sizeof err) == 0);
    GbCart *c = &g.cart;
    assert(c->battery && c->ram_size == 256);
    gb_cart_write(c, 0x2000, 3);
    assert(gb_cart_read(c, 0x4000) == 0x13);
    gb_cart_write(c, 0x2000, 0);
    assert(gb_cart_read(c, 0x4000) == 0x10);

    gb_cart_write(c, 0x0000, 0x0A);
    assert(gb_cart_read(c, 0xA030) == 0xFF);
    gb_cart_write(c, 0x4000, 0x40);
    assert(gb_cart_read(c, 0xA030) == 0x80);
    assert(gb_cart_read(c, 0xB030) == 0xFF);
    gb_set_pad(&g, PAD_LEFT | PAD_DOWN);
    gb_cart_write(c, 0xA000, 0x55);
    gb_cart_write(c, 0xA010, 0xAA);
    assert(gb_cart_read(c, 0xA12F) == 0x40 && gb_cart_read(c, 0xA030) == 0x82);
    assert(gb_cart_read(c, 0xA040) == 0x60 && gb_cart_read(c, 0xA050) == 0x81);
    gb_set_pad(&g, 0);
    gb_cart_write(c, 0xA010, 0xAA);
    assert(gb_cart_read(c, 0xA020) == 0x40);

    command(c, 0x17F);  /* a write while locked */
    send(c, 0x1234, 16);
    assert(read_word(c, 127) == 0xFFFF);
    command(c, 0x0C0);  /* EWEN */
    command(c, 0x17F);
    send(c, 0x1234, 16);
    gb_cart_write(c, 0xA080, 0);
    gb_cart_write(c, 0xA080, 0x80);
    assert(!(gb_cart_read(c, 0xA080) & 1));
    for (int i = 0; i < 2000; i++) gb_cart_tick(c);
    assert(gb_cart_read(c, 0xA080) & 1);
    assert(read_word(c, 0xFF) == 0x1234);  /* the high address bit is ignored */
    assert(c->ram[254] == 0x34 && c->ram[255] == 0x12);
    gb_free(&g);
    return 0;
}
