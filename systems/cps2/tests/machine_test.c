#include "machine.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    static uint8_t program[] = {
        0x00, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x08,
        0x70, 0x2a,             /* moveq #42,d0 */
        0x60, 0xfe              /* bra.s to itself */
    };
    static uint8_t graphics[0x200000];
    static const Cps2Region regions[] = {
        {.tag = "maincpu", .size = sizeof(program)},
        {.tag = "gfx", .size = sizeof(graphics)}
    };
    static const Cps2Game game = {.regions = regions, .count = 2};
    uint8_t *bytes[] = {program, graphics};
    Cps2Rom rom = {.game = &game, .regions = bytes};
    Cps2Machine *machine = malloc(sizeof(*machine));
    if (!machine || cps2_machine_init(machine, &rom)) {
        free(machine);
        return EXIT_FAILURE;
    }
    m68k_write(&machine->cpu, 0x804152, 17, 5, 3);
    m68k_write(&machine->cpu, 0x8040e0, 1, 5, 1);
    m68k_write(&machine->cpu, 0x70e000, 0xabcd, 5, 3);
    cps2_machine_run(machine, 241 * 1024);
    int ok = machine->cpu.d[0] == 42 && !machine->cpu.halted &&
             machine->objects[0][0] == 0xab && machine->objects[0][1] == 0xcd &&
             machine->cpu.ipl == 6 && machine->rendered == 224;
    cps2_machine_destroy(machine);
    free(machine);
    if (!ok)
        fputs("CPS-2 machine smoke test failed\n", stderr);
    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
