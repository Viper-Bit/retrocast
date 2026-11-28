/* CPS-2 QSound bus (MAME 0.289 cps2.cpp and cps1.cpp). */
#include "machine.h"
#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cps2_sound_init(Cps2Machine *s, const Cps2Rom *rom, const Zip *archive)
{
    size_t program_size, sample_size;
    const uint8_t *program = cps2_region(rom, "audiocpu", &program_size);
    const uint8_t *samples = cps2_region(rom, "qsound", &sample_size);
    uint8_t raw[0x6000];
    const ZipEntry *entry = zip_find_crc(archive, 0xd6cf5ef5, sizeof(raw));
    if (!program || program_size < 0x14000 || !samples || !entry || zip_read(archive, entry, raw))
        return -1;
    for (size_t i = 0; i < sizeof(s->dsp) / sizeof(s->dsp[0]); ++i)
        s->dsp[i] = (uint16_t)(raw[i * 2] | raw[i * 2 + 1] << 8);
    qsound_init(&s->sound, s->dsp, samples, (uint32_t)sample_size);
    s->audio_program = program;
    s->audio_size = program_size;
    s->audio_cpu.bus = s;
    z80_reset(&s->audio_cpu);
    s->audio_irq_clock = 32000;
    s->sample_clock = QSOUND_CLOCKS_PER_SAMPLE * 2;
    return 0;
}

/* Each DSP sample takes 4992/15 Z80 T-states. */
static void samples_until(Cps2Machine *s, uint64_t tstates)
{
    while (tstates * 15 >= s->sample_clock) {
        int16_t sample[2];
        qsound_sample(&s->sound, sample);
        if (s->audio_sample)
            s->audio_sample(s->audio_context, sample);
        s->sample_clock += QSOUND_CLOCKS_PER_SAMPLE * 2;
    }
}

void cps2_sound_control(Cps2Machine *s, uint8_t value)
{
    if (s->audio_program && ((s->sound_control ^ value) & 8)) {
        cps2_sound_run(s);
        if (!(value & 8)) {
            uint64_t tstates = s->audio_cpu.tstates;
            z80_reset(&s->audio_cpu);
            s->audio_cpu.tstates = tstates;
            s->audio_irq = 0;
        }
    }
    s->sound_control = value;
}

void cps2_sound_run(Cps2Machine *s)
{
    Z80 *z = &s->audio_cpu;
    uint64_t until = s->cpu.cycles / 2;
    if (!(s->sound_control & 8))
        z->tstates = until > z->tstates ? until : z->tstates;
    while (z->tstates < until) {
        if (z->tstates >= s->audio_irq_clock) {
            s->audio_irq = 1;
            s->audio_irq_clock = (z->tstates / 32000 + 1) * 32000;
        }
        if (s->audio_irq && z80_interrupt(z))
            s->audio_irq = 0;
        else
            z80_step(z);
    }
    if (!(s->sound_control & 8))
        s->audio_irq_clock = (z->tstates / 32000 + 1) * 32000;
    samples_until(s, until);
}

uint8_t z80_read(Z80 *z, uint16_t a)
{
    Cps2Machine *s = z->bus;
    if (a < 0x8000) return s->audio_program[a];
    if (a < 0xc000) return s->audio_program[0x10000 + s->audio_bank * 0x4000 + (a & 0x3fff)];
    if (a < 0xd000) return s->shared[a & 0xfff];
    if (a >= 0xf000) return s->audio_ram[a & 0xfff];
    if (a == 0xd007) {
        samples_until(s, z->tstates);
        return qsound_ready(&s->sound);
    }
    return 0xff;
}

uint8_t z80_fetch(Z80 *z, uint16_t pc) { return z80_read(z, pc); }

void z80_write(Z80 *z, uint16_t a, uint8_t v)
{
    Cps2Machine *s = z->bus;
    if (a >= 0xf000) s->audio_ram[a & 0xfff] = v;
    else if (a >= 0xc000 && a < 0xd000) s->shared[a & 0xfff] = v;
    else if (a >= 0xd000 && a <= 0xd002) {
        samples_until(s, z->tstates);
        qsound_write(&s->sound, a - 0xd000, v);
    } else if (a == 0xd003) {
        unsigned bank = v & 15;
        s->audio_bank = (uint8_t)(0x10000 + (bank + 1) * 0x4000 <= s->audio_size ? bank : 0);
    }
}

uint8_t z80_in(Z80 *z, uint16_t port) { (void)z; (void)port; return 0xff; }
void z80_out(Z80 *z, uint16_t port, uint8_t v) { (void)z; (void)port; (void)v; }
void z80_idle(Z80 *z, uint16_t a, unsigned n) { (void)z; (void)a; (void)n; }
uint8_t z80_irq_ack(Z80 *z) { (void)z; return 0xff; }

int cps2_sound_open(Cps2Machine *machine, const Cps2Rom *rom, const char *folder)
{
    size_t capacity = strlen(folder) + sizeof("/qsound.zip");
    char *path = malloc(capacity);
    if (!path)
        return -1;
    snprintf(path, capacity, "%s/qsound.zip", folder);
    size_t size;
    uint8_t *bytes = file_read(path, &size);
    free(path);
    Zip archive;
    int status = -1;
    if (bytes && !zip_open(&archive, bytes, size)) {
        status = cps2_sound_init(machine, rom, &archive);
        zip_close(&archive);
    }
    free(bytes);
    return status;
}
