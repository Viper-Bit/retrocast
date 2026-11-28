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
    m68k_write(&machine->cpu, 0xfffff8, 0x1234, 5, 3);
    int output_ok = m68k_read(&machine->cpu, 0x400008, 5, 3) == 0;
    cps2_machine_destroy(machine);
    Cps2Game phoenix = game;
    phoenix.machine = "dead_cps2comm";
    rom.game = &phoenix;
    if (cps2_machine_init(machine, &rom)) {
        free(machine);
        return EXIT_FAILURE;
    }
    m68k_write(&machine->cpu, 0xfffff8, 0x1234, 5, 3);
    m68k_write(&machine->cpu, 0x400008, 0x00cd, 5, 1);
    output_ok = output_ok && m68k_read(&machine->cpu, 0xfffff8, 5, 3) == 0x12cd &&
                m68k_read(&machine->cpu, 0x400008, 5, 3) == 0x12cd;
    m68k_write(&machine->cpu, 0x804140, 0xffff, 5, 3);
    m68k_write(&machine->cpu, 0x800142, 0x8081, 5, 3);
    int multiplier_ok = m68k_read(&machine->cpu, 0x804144, 5, 3) == 0x7f7f &&
                        m68k_read(&machine->cpu, 0x800146, 5, 3) == 0x8080;
    m68k_write(&machine->cpu, 0x804152, 17, 5, 3);
    m68k_write(&machine->cpu, 0x8040e0, 1, 5, 1);
    m68k_write(&machine->cpu, 0x70e000, 0xabcd, 5, 3);
    cps2_machine_run(machine, 241 * 1024);
    int ok = sound_ok && output_ok && multiplier_ok && machine->cpu.d[0] == 42 && !machine->cpu.halted &&
             machine->objects[0][0] == 0xab && machine->objects[0][1] == 0xcd &&
             machine->cpu.ipl == 6 && machine->rendered == 224;
    m68k_write(&machine->cpu, 0x804166, 0x0084, 5, 3);
    m68k_write(&machine->cpu, 0x804104, 0x9040, 5, 3);
    m68k_write(&machine->cpu, 0x804108, 0x9200, 5, 3);
    m68k_write(&machine->cpu, 0x804112, 32, 5, 3);
    m68k_write(&machine->cpu, 0x804120, 0x3f8, 5, 3);
    m68k_write(&machine->cpu, 0x804122, 5, 5, 3);
    m68k_write(&machine->cpu, 0x920010, 16, 5, 3);
    m68k_write(&machine->cpu, 0x90414c, 1, 5, 3);  /* column 5, row 3 */
    machine->tiles[128] = 0x80;
    machine->palette[0x401] = 0xff00;
    machine->rendered = 0;
    cps2_video_render(machine, 1);
    ok = ok && machine->frame[0] == 0xff0000;
    cps2_machine_destroy(machine);
    free(machine);
    if (!ok)
        fputs("CPS-2 machine smoke test failed\n", stderr);
    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
