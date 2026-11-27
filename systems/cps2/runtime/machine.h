#ifndef CPS2_MACHINE_H
#define CPS2_MACHINE_H
#include "roms.h"
#include "m68k_cpu.h"
#include "eeprom93c46.h"
#include "z80_cpu.h"
#include "qsound.h"

typedef struct {
    M68k cpu;
    Z80 audio_cpu;
    QSound sound;
    uint16_t dsp[4096];
    const uint8_t *audio_program;
    size_t audio_size;
    uint8_t audio_ram[0x1000], audio_bank, audio_irq;
    uint64_t audio_irq_clock, sample_clock;
    void (*audio_sample)(void *context, const int16_t sample[2]);
    void *audio_context;
    Eeprom93c46 eeprom;
    const uint8_t *program;
    uint16_t *opcodes;
    size_t program_size;
    uint8_t *tiles;
    size_t tile_size;
    uint8_t work[0x10000], graphics[0x30000], objects[2][0x2000];
    uint8_t output[12], cps_a[64], cps_b[64], shared[0x1000];
    uint16_t inputs[3]; /* raw port levels, active low except EEPROM DO */
    uint8_t object_bank, sound_control;
    uint16_t raster_reload[2], raster_counter[2], scanline;
    uint64_t line_clock, raster_clock;
    uint8_t latched_objects[0x2000];
    uint16_t palette[0xc00], priority;
    uint32_t frame[384 * 224];
    unsigned rendered;
} Cps2Machine;

/* The ROM must outlive the machine. */
int cps2_machine_init(Cps2Machine *machine, const Cps2Rom *rom);
void cps2_machine_destroy(Cps2Machine *machine);
void cps2_machine_run(Cps2Machine *machine, uint64_t until);
int cps2_sound_init(Cps2Machine *machine, const Cps2Rom *rom, const Zip *archive);
void cps2_sound_run(Cps2Machine *machine);
void cps2_sound_control(Cps2Machine *machine, uint8_t value);
int cps2_video_init(Cps2Machine *machine, const Cps2Rom *rom);
void cps2_palette_upload(Cps2Machine *machine);
void cps2_video_render(Cps2Machine *machine, unsigned end);

#endif
