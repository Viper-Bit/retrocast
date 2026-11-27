#include "machine.h"

#include <stdio.h>
#include <stdlib.h>

static int check_sound_bus(Cps2Machine *s)
{
    static const uint8_t program[0x18000] = {
        0x3e, 0x77,             /* ld a,$77 */
        0x32, 0xff, 0xcf,       /* ld ($cfff),a */
        0x76,                   /* halt */
        [0x14000] = 0x42
    };
    s->audio_program = program;
    s->audio_size = sizeof(program);
    s->audio_irq_clock = 32000;
    s->sample_clock = QSOUND_CLOCKS_PER_SAMPLE * 2;
    s->audio_cpu.bus = s;
    z80_reset(&s->audio_cpu);
    cps2_sound_run(s);
    if (s->shared[0xfff])
        return 0;
    m68k_write(&s->cpu, 0x804040, 8, 5, 1);
    s->cpu.cycles += 100;
    cps2_sound_run(s);
    z80_write(&s->audio_cpu, 0xd003, 1);
    int ok = m68k_read(&s->cpu, 0x619ffe, 5, 1) == 0xff77 &&
             z80_read(&s->audio_cpu, 0x8000) == 0x42;
    m68k_write(&s->cpu, 0x804040, 0, 5, 1);
    ok = ok && s->audio_cpu.pc == 0;
    s->audio_program = NULL;
    return ok;
}

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
    int sound_ok = check_sound_bus(machine);
    m68k_write(&machine->cpu, 0x804152, 17, 5, 3);
    m68k_write(&machine->cpu, 0x8040e0, 1, 5, 1);
    m68k_write(&machine->cpu, 0x70e000, 0xabcd, 5, 3);
    cps2_machine_run(machine, 241 * 1024);
    int ok = sound_ok && machine->cpu.d[0] == 42 && !machine->cpu.halted &&
             machine->objects[0][0] == 0xab && machine->objects[0][1] == 0xcd &&
             machine->cpu.ipl == 6 && machine->rendered == 224;
    cps2_machine_destroy(machine);
    free(machine);
    if (!ok)
        fputs("CPS-2 machine smoke test failed\n", stderr);
    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
