/* The Game Boy's sound (DMG): two pulse channels (the first with a
 * frequency sweep), a wave channel, a noise channel, the frame sequencer
 * (Pan Docs "Audio Details", gbdev "Gameboy sound hardware"). The
 * registers' values are in Gb.io[$10-$3F]; this is the rest of the state. */
#ifndef GB_APU_H
#define GB_APU_H

#include <stdint.h>

enum { GB_SAMPLE_RATE = 48000, GB_APU_BUF = 4096 };

typedef struct GbApu {
    uint8_t power;             /* NR52 bit 7 */
    uint8_t fs_step;           /* the frame sequencer's next step (0-7) */
    uint8_t on[4];             /* channels playing (NR52 bits 0-3) */
    uint16_t len[4];           /* length counters (kept while powered off, DMG) */
    uint8_t ds_delay, fs_pending;  /* CGB speed-switch delay and a frame sequencer edge due next cycle */
    int timer[4];              /* frequency timers: M-cycles left (wave: 2 MHz cycles) */
    uint8_t vol[4], env_timer[4];  /* envelopes (pulses, noise) */
    uint8_t duty_pos[2];
    uint16_t shadow;           /* sweep: the frequency it works from */
    uint8_t sweep_timer, sweep_on, sweep_neg_used;
    uint8_t wave_pos, wave_sample, wave_just_read;  /* just_read: a sample was read this M-cycle */
    uint16_t lfsr;
    /* output, left and right: a box filter to 48 kHz, the console's high-pass capacitors */
    float acc[2], cap[2];
    int acc_n;
    uint32_t frac;
    float buf[GB_APU_BUF * 2];  /* stereo sample frames, left first */
    int buf_len;               /* in sample frames */
} GbApu;

struct Gb;
void apu_tick(struct Gb *g);           /* one M-cycle */
void apu_frame_step(struct Gb *g);     /* DIV bit 12 fell (512 Hz) */
uint8_t apu_read(struct Gb *g, uint16_t a);
void gb_apu_write(struct Gb *g, uint16_t a, uint8_t v);
void apu_boot(struct Gb *g);           /* the state the boot ROM leaves */
int gb_apu_take_samples(struct Gb *g, float *out, int max);  /* drain up to max 48 kHz stereo sample frames */

#endif
