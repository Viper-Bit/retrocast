/* The Capcom Q-Sound chip (DL-1425: a DSP16 running Capcom's program): 16
 * PCM voices and 3 ADPCM voices on 8-bit sample ROM, panned through the
 * chip ROM's tables, an echo, and the "Q1" FIR filters, out in stereo at
 * 60 MHz / 2 / 1,248 = 24,038 Hz. MAME 0.289's high-level version
 * (qsoundhle.cpp, by superctr and Valley Bell), ported sample for sample;
 * its tables come from the chip's ROM, dl-1425.bin (docs/sources.md). */
#ifndef QSOUND_H
#define QSOUND_H

#include <stdint.h>

#define QSOUND_CLOCK 60000000
#define QSOUND_CLOCKS_PER_SAMPLE 2496  /* 60 MHz clocks: the DSP's 1,248 cycles at 30 MHz */

typedef struct {
    uint16_t bank;
    int16_t addr;             /* the sample address (its top word) */
    uint16_t phase, rate;     /* rate: 4.12 fixed point */
    int16_t loop_len, end_addr, volume, echo;
} QsVoice;

typedef struct {
    uint16_t start_addr, end_addr, bank;
    int16_t volume;
    uint16_t flag;
    int16_t cur_vol, step_size;
    uint16_t cur_addr;
} QsAdpcm;

typedef struct {
    int32_t tap_count, delay_pos;
    uint16_t table_pos;
    int16_t taps[95], delay_line[95];
} QsFir;

typedef struct {
    int16_t delay, volume, write_pos, read_pos, delay_line[51];
} QsDelay;

typedef struct {
    uint16_t end_pos;
    int16_t feedback, length, last_sample, delay_line[1024], delay_pos;
} QsEcho;

typedef struct {
    const uint16_t *dsp;        /* the chip ROM's first 4,096 words */
    const uint8_t *rom;         /* the samples */
    uint32_t size;
    uint16_t data_latch;
    int16_t out[2];
    QsVoice voice[16];
    QsAdpcm adpcm[3];
    uint16_t voice_pan[19];
    int16_t voice_output[19];
    QsEcho echo;
    QsFir filter[2], alt_filter[2];
    QsDelay wet[2], dry[2];
    uint16_t state, next_state, delay_update;
    int32_t state_counter, ready_flag;
} QSound;

void qsound_init(QSound *q, const uint16_t *dsp_rom, const uint8_t *samples, uint32_t size);  /* and reset */
void qsound_write(QSound *q, int offset, uint8_t v);  /* 0: data high, 1: data low, 2: the register to write */
uint8_t qsound_ready(const QSound *q);                /* $80 ready, 0 busy */
void qsound_sample(QSound *q, int16_t out[2]);        /* the next sample, left and right */

#endif
