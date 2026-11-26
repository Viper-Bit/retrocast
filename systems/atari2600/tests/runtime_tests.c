#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "atari.h"
#include "palette.h"

static void test_scanline(void) {
    A26Tia tia;
    a26_tia_init(&tia);
    a26_tia_write(&tia, 6, 0x28);
    a26_tia_write(&tia, 7, 0x34);
    a26_tia_write(&tia, 8, 0x28);
    a26_tia_write(&tia, 0x0A, 2); /* Score mode puts the left playfield over player 1. */
    a26_tia_write(&tia, 0x1C, 0x80);
    a26_tia_write(&tia, 0x0D, 0x30);
    while (tia.x < 69) a26_tia_tick(&tia);
    assert(tia.collision[3] & 0x80);
    a26_tia_write(&tia, 0x0D, 0);
    while (tia.x < 73) a26_tia_tick(&tia);
    for (unsigned i = 0; i < 4; i++) assert(tia.frame[i] == 0x28);
    assert(tia.frame[4] == 0);

    a26_tia_write(&tia, 0x10, 0);
    a26_tia_write(&tia, 0x12, 0);
    assert(tia.position[0] == 10 && tia.position[2] == 9);
    a26_tia_write(&tia, 0x28, 0);
    assert(tia.position[2] == 9);
    a26_tia_write(&tia, 0x28, 2);
    a26_tia_write(&tia, 0x28, 0);
    assert(tia.position[2] == 14);

    a26_tia_write(&tia, 3, 0);
    assert(tia.x == 225 && tia.y == 0);
    for (unsigned i = 0; i < 3; i++) a26_tia_tick(&tia);
    assert(tia.x == 0 && tia.y == 1 && tia.frame[8] == 1 && tia.audio_clock == 76);

    a26_tia_init(&tia);
    while (tia.x < 220) a26_tia_tick(&tia);
    a26_tia_write(&tia, 0x2A, 0);
    while (tia.y == 0) a26_tia_tick(&tia);
    assert(tia.position[0] == 0 && !tia.hmove_blank);
    while (tia.x < 33) a26_tia_tick(&tia);
    assert(tia.position[0] == 152 && !tia.moving && !tia.hmove_blank);
}

static void test_variable_frames(void) {
    static const uint8_t program[] = {
        0xA2, 0x02,       /* LDX #2 */
        0x8A,             /* TXA */
        0xA8,             /* TAY */
        0x85, 0x02,       /* STA WSYNC */
        0x88,             /* DEY */
        0xD0, 0xFB,       /* BNE wait */
        0xA9, 0x02,       /* LDA #2 */
        0x85, 0x00,       /* STA VSYNC */
        0x85, 0x02,       /* STA WSYNC */
        0xA9, 0x00,       /* LDA #0 */
        0x85, 0x00,       /* STA VSYNC */
        0xE8,             /* INX */
        0x4C, 0x02, 0xF0, /* JMP frame */
    };
    uint8_t rom[2048] = {0};
    memcpy(rom, program, sizeof program);
    rom[0x7FD] = 0xF0;
    Atari2600 machine;
    InputFrame input = {0};
    assert(a26_init(&machine, rom, sizeof rom, A26_CART_AUTO, 0) == 0);
    a26_frame(&machine, &input);
    uint64_t first = machine.bus.cpu.cycles;
    a26_frame(&machine, &input);
    uint64_t second = machine.bus.cpu.cycles;
    a26_frame(&machine, &input);
    assert(machine.tia.frames == 3);
    assert(machine.bus.cpu.cycles - second == second - first + 76);
}

int main(int argc, char **argv) {
    assert(argc == 2);
    test_scanline();
    test_variable_frames();
    A26Tia tia;
    a26_tia_init(&tia);
    a26_tia_write(&tia, 0x1B, 0x80);
    a26_tia_write(&tia, 0x1C, 0x80);
    a26_tia_write(&tia, 0x0D, 0x10);
    assert(tia.reg[0x1B] == 0 && tia.reg[0x0D] == 0);
    a26_tia_tick(&tia);
    assert(tia.reg[0x1B] == 0x80 && tia.reg[0x0D] == 0);
    a26_tia_tick(&tia);
    assert(tia.reg[0x0D] == 0x10);
    tia.position[0] = tia.position[1] = 0;
    tia.x = 68;
    a26_tia_tick(&tia);
    assert((a26_tia_read(&tia, 7, 0) & 0x80) != 0);
    assert((a26_tia_read(&tia, 2, 0) & 0x80) != 0);
    a26_tia_write(&tia, 0x2C, 0);
    assert(a26_tia_read(&tia, 7, 0) == 0);
    a26_tia_write(&tia, 0x02, 0);
    assert(!a26_tia_ready(&tia));
    while (tia.x) a26_tia_tick(&tia);
    assert(a26_tia_ready(&tia));
    a26_tia_write(&tia, 0, 2);
    a26_tia_write(&tia, 0, 0);
    assert(tia.frames == 1 && tia.y == 0);
    tia.x = 0;
    a26_tia_write(&tia, 2, 0);
    assert(a26_tia_ready(&tia));
    tia.x = 30;
    a26_tia_write(&tia, 0x10, 0);
    assert(tia.position[0] == 1);
    a26_tia_write(&tia, 0x20, 0xF0);
    a26_tia_write(&tia, 0x2A, 0);
    for (int i = 0; i < 3; i++) a26_tia_tick(&tia);
    a26_tia_write(&tia, 0x2A, 0);
    for (int i = 0; i < 2; i++) a26_tia_tick(&tia);
    assert(!tia.hmove_blank && tia.position[0] == 1);
    a26_tia_tick(&tia);
    assert(tia.hmove_blank && tia.position[0] == 1);
    for (int i = 0; i < 3; i++) a26_tia_tick(&tia);
    assert(tia.position[0] == 0 && tia.motion_counter == 0);
    while (tia.x < 73) a26_tia_tick(&tia);
    assert(tia.position[0] == 1 && !tia.moving);
    assert(a26_palette_color(0x20, 0) != a26_palette_color(0x20, 1));
    assert(a26_palette_color(0x21, 0) == a26_palette_color(0x20, 0));
    tia.fire[0] = 0;
    a26_tia_write(&tia, 1, 0);
    assert(a26_tia_read(&tia, 0x0C, 0) == 0);
    a26_tia_write(&tia, 0x19, 15);
    for (int i = 0; i < 228 * 10; i++) a26_tia_tick(&tia);
    float samples[2048];
    int count = a26_tia_samples(&tia, samples, 2048);
    assert(count > 0);
    int audible = 0;
    for (int i = 0; i < count; i++) if (samples[i] > 0) audible = 1;
    assert(audible);

    uint8_t rom[4096] = {0};
    rom[0] = 0x4C; rom[1] = 0x00; rom[2] = 0xF0;
    rom[0xFFC] = 0; rom[0xFFD] = 0xF0;
    Atari2600 machine;
    assert(a26_init(&machine, rom, sizeof rom, A26_CART_AUTO, 0) == 0);
    InputFrame input = {0};
    input.pad[0] = PAD_UP | PAD_A | PAD_START;
    a26_frame(&machine, &input);
    assert(!(machine.bus.riot.input_a & 0x10));
    assert(!(machine.bus.riot.input_b & 1));
    assert(!machine.tia.input[4]);
    assert(a26_save(&machine, argv[1]) == 0);
    a26_frame(&machine, &input);
    uint64_t cycles = machine.bus.cpu.cycles;
    unsigned x = machine.tia.x, y = machine.tia.y;
    assert(a26_load(&machine, argv[1]) == 0);
    a26_frame(&machine, &input);
    assert(machine.bus.cpu.cycles == cycles && machine.tia.x == x && machine.tia.y == y);
    machine.rom_hash++;
    assert(a26_load(&machine, argv[1]) != 0);
    {   /* a state keeps the cartridge's slices and RAM (E7 here) */
        static uint8_t e7[16384];
        static Atari2600 m;
        assert(a26_init(&m, e7, sizeof e7, A26_CART_E7, 0) == 0);
        m.bus.cart.slice[0] = 3;
        m.bus.cart.slice[1] = 2;
        m.bus.cart.ram[0x500] = 0x9C;
        assert(a26_save(&m, argv[1]) == 0);
        m.bus.cart.slice[0] = m.bus.cart.slice[1] = 0;
        m.bus.cart.ram[0x500] = 0;
        assert(a26_load(&m, argv[1]) == 0);
        assert(m.bus.cart.slice[0] == 3 && m.bus.cart.slice[1] == 2 && m.bus.cart.ram[0x500] == 0x9C);
        m.bus.cart.slice[1] = 9;  /* out of range: refused */
        assert(a26_save(&m, argv[1]) == 0 && a26_load(&m, argv[1]) != 0);
    }
    Atari2600 reference;
    assert(a26_init(&machine, rom, sizeof rom, A26_CART_AUTO, 0) == 0);
    assert(a26_init(&reference, rom, sizeof rom, A26_CART_AUTO, 0) == 0);
    reference.bus.riot.ram[0] = 1;
    machine.reference = &reference;
    a26_frame(&machine, &input);
    assert(machine.diff_failed);
    puts("Atari 2600 runtime tests passed");
    return 0;
}
