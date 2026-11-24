/* The Q-Sound chip (qsound.h), adapted from MAME 0.289's qsoundhle.cpp.
 * license:BSD-3-Clause; copyright-holders: superctr, Valley Bell (MAME). MAME relies on
 * C++20's wrapping shifts of negative numbers and on sums that wrap; here
 * that arithmetic is done unsigned (wrap) and converted back. */
#include "qsound.h"

#include <stdlib.h>
#include <string.h>

enum {
    DATA_PAN_TAB = 0x110, DATA_ADPCM_TAB = 0x9DC, DATA_FILTER_TAB = 0xD53,
    STATE_BOOT = 0x000, STATE_INIT1 = 0x288, STATE_INIT2 = 0x61A, STATE_REFRESH1 = 0x039, STATE_REFRESH2 = 0x04F,
    STATE_NORMAL1 = 0x314, STATE_NORMAL2 = 0x6B2,
    PAN_TABLE_DRY = 0, PAN_TABLE_WET = 98, PAN_TABLE_CH_OFFSET = 196, FILTER_ENTRY_SIZE = 95,
    DELAY_BASE_OFFSET = 0x554, DELAY_BASE_OFFSET2 = 0x53C
};

static int32_t shl(int32_t v, int n) { return (int32_t)((uint32_t)v << n); }
static int32_t add(int32_t a, int32_t b) { return (int32_t)((uint32_t)a + (uint32_t)b); }
static int32_t clamp(int32_t v, int32_t lo, int32_t hi) { return v < lo ? lo : v > hi ? hi : v; }

static uint16_t dsp_rom(const QSound *q, uint16_t a) { return q->dsp[a & 0xFFF]; }

/* A byte of the sample ROM on the chip's 24-bit bus: mirrored over the
 * power of two holding it, zero past its end (MAME's device_rom_interface). */
static int16_t read_sample(const QSound *q, uint16_t bank, uint16_t address) {
    uint32_t a = ((uint32_t)(bank & 0x7FFF) << 16 | address) & 0xFFFFFF, rmask = q->size - 1;
    rmask |= rmask >> 1, rmask |= rmask >> 2, rmask |= rmask >> 4, rmask |= rmask >> 8, rmask |= rmask >> 16;
    a &= rmask;
    return (int16_t)((a < q->size ? q->rom[a] : 0) << 8);  /* bits 0-7 are tied to ground */
}

void qsound_init(QSound *q, const uint16_t *dsp_rom, const uint8_t *samples, uint32_t size) {
    memset(q, 0, sizeof *q);
    q->dsp = dsp_rom, q->rom = samples, q->size = size;
    q->state = STATE_BOOT;  /* not ready, silent, counter 0 */
}

/* The register at an address, or NULL (MAME's register map). */
static uint16_t *reg(QSound *q, uint8_t a) {
    if (a < 0x80) {
        QsVoice *v = &q->voice[a >> 3];
        switch (a & 7) {
        case 0: return &q->voice[((a >> 3) + 1) % 16].bank;  /* the bank applies to the next voice */
        case 1: return (uint16_t *)&v->addr;
        case 2: return &v->rate;
        case 3: return &v->phase;
        case 4: return (uint16_t *)&v->loop_len;
        case 5: return (uint16_t *)&v->end_addr;
        case 6: return (uint16_t *)&v->volume;
        default: return NULL;
        }
    }
    if (a < 0x90) return &q->voice_pan[a - 0x80];
    if (a < 0x93) return &q->voice_pan[16 + a - 0x90];
    if (a == 0x93) return (uint16_t *)&q->echo.feedback;
    if (a >= 0xBA && a < 0xCA) return (uint16_t *)&q->voice[a - 0xBA].echo;
    if (a >= 0xCA && a < 0xD6) {
        QsAdpcm *p = &q->adpcm[(a - 0xCA) >> 2];
        switch ((a - 0xCA) & 3) {
        case 0: return &p->start_addr;
        case 1: return &p->end_addr;
        case 2: return &p->bank;
        default: return (uint16_t *)&p->volume;
        }
    }
    if (a >= 0xD6 && a < 0xD9) return &q->adpcm[a - 0xD6].flag;
    switch (a) {
    case 0xD9: return &q->echo.end_pos;
    case 0xDA: return &q->filter[0].table_pos;
    case 0xDC: return &q->filter[1].table_pos;
    case 0xDB: return &q->alt_filter[0].table_pos;
    case 0xDD: return &q->alt_filter[1].table_pos;
    case 0xDE: return (uint16_t *)&q->wet[0].delay;
    case 0xE0: return (uint16_t *)&q->wet[1].delay;
    case 0xDF: return (uint16_t *)&q->dry[0].delay;
    case 0xE1: return (uint16_t *)&q->dry[1].delay;
    case 0xE2: return &q->delay_update;
    case 0xE3: return &q->next_state;
    case 0xE4: return (uint16_t *)&q->wet[0].volume;
    case 0xE6: return (uint16_t *)&q->wet[1].volume;
    case 0xE5: return (uint16_t *)&q->dry[0].volume;
    case 0xE7: return (uint16_t *)&q->dry[1].volume;
    default: return NULL;
    }
}

void qsound_write(QSound *q, int offset, uint8_t v) {
    if (offset == 0) q->data_latch = (uint16_t)((q->data_latch & 0x00FF) | v << 8);
    else if (offset == 1) q->data_latch = (uint16_t)((q->data_latch & 0xFF00) | v);
    else if (offset == 2) {
        uint16_t *r = reg(q, v);
        if (r) *r = q->data_latch;
        q->ready_flag = 0;
    }
}

uint8_t qsound_ready(const QSound *q) { return (uint8_t)q->ready_flag; }

static void state_init(QSound *q) {
    int mode = q->state == STATE_INIT2;
    if (q->state_counter >= 2) {  /* busy for 4 samples, the filter refresh included */
        q->state_counter = 0;
        q->state = q->next_state;
        return;
    }
    if (q->state_counter == 1) {
        q->state_counter++;
        return;
    }
    memset(q->voice, 0, sizeof q->voice), memset(q->adpcm, 0, sizeof q->adpcm);
    memset(q->filter, 0, sizeof q->filter), memset(q->alt_filter, 0, sizeof q->alt_filter);
    memset(q->wet, 0, sizeof q->wet), memset(q->dry, 0, sizeof q->dry), memset(&q->echo, 0, sizeof q->echo);
    for (int i = 0; i < 19; i++) q->voice_pan[i] = DATA_PAN_TAB + 0x10, q->voice_output[i] = 0;
    for (int i = 0; i < 16; i++) q->voice[i].bank = 0x8000;
    for (int i = 0; i < 3; i++) q->adpcm[i].bank = 0x8000;
    if (mode == 0) {
        q->wet[0].delay = 0, q->dry[0].delay = 46, q->wet[1].delay = 0, q->dry[1].delay = 48;
        q->filter[0].table_pos = DATA_FILTER_TAB + FILTER_ENTRY_SIZE * 1;
        q->filter[1].table_pos = DATA_FILTER_TAB + FILTER_ENTRY_SIZE * 2;
        q->echo.end_pos = DELAY_BASE_OFFSET + 6;
        q->next_state = STATE_REFRESH1;
    } else {
        q->wet[0].delay = 1, q->dry[0].delay = 0, q->wet[1].delay = 0, q->dry[1].delay = 0;
        q->filter[0].table_pos = 0xF73, q->filter[1].table_pos = 0xFA4;
        q->alt_filter[0].table_pos = 0xF73, q->alt_filter[1].table_pos = 0xFA4;
        q->echo.end_pos = DELAY_BASE_OFFSET2 + 6;
        q->next_state = STATE_REFRESH2;
    }
    q->wet[0].volume = q->dry[0].volume = q->wet[1].volume = q->dry[1].volume = 0x3FFF;
    q->delay_update = 1;
    q->ready_flag = 0;
    q->state_counter = 1;
}

static void refresh_filter(QSound *q, int mode2) {
    for (int ch = 0; ch < 2; ch++) {
        QsFir *f = &q->filter[ch], *g = &q->alt_filter[ch];
        f->delay_pos = 0, f->tap_count = mode2 ? 45 : 95;
        for (int i = 0; i < f->tap_count; i++) f->taps[i] = (int16_t)dsp_rom(q, (uint16_t)(f->table_pos + i));
        if (mode2) {
            g->delay_pos = 0, g->tap_count = 44;
            for (int i = 0; i < 44; i++) g->taps[i] = (int16_t)dsp_rom(q, (uint16_t)(g->table_pos + i));
        }
    }
    q->state = q->next_state = mode2 ? STATE_NORMAL2 : STATE_NORMAL1;
}

static int16_t voice_update(QSound *q, QsVoice *v, int32_t *echo_out) {
    int16_t output = (int16_t)((v->volume * read_sample(q, v->bank, (uint16_t)v->addr)) >> 14);
    *echo_out = add(*echo_out, shl(output * v->echo, 2));
    int32_t new_phase = add(v->rate, (int32_t)((uint32_t)(int32_t)v->addr << 12 | (uint32_t)(v->phase >> 4)));
    if ((new_phase >> 12) >= v->end_addr) new_phase = add(new_phase, -shl(v->loop_len, 12));
    new_phase = clamp(new_phase, -0x8000000, 0x7FFFFFF);
    v->addr = (int16_t)(new_phase >> 12);
    v->phase = (uint16_t)((uint32_t)new_phase << 4);
    return output;
}

static int16_t adpcm_update(QSound *q, QsAdpcm *p, int16_t curr_sample, int nibble) {
    int8_t step;
    if (!nibble) {
        if (p->cur_addr == p->end_addr) p->cur_vol = 0;  /* muted at its end */
        if (p->flag) {                                   /* started */
            curr_sample = 0, p->flag = 0, p->step_size = 10, p->cur_vol = p->volume, p->cur_addr = p->start_addr;
        }
        step = (int8_t)(read_sample(q, p->bank, p->cur_addr) >> 8);  /* the top nibble */
    } else {
        step = (int8_t)(read_sample(q, p->bank, p->cur_addr++) >> 4);  /* the bottom one */
    }
    step = (int8_t)(step >> 4);  /* sign-extended */
    int32_t delta = ((1 + abs(step * 2)) * p->step_size) >> 1;  /* (0.5 + |step|) x step size */
    if (step <= 0) delta = -delta;
    delta = clamp(delta + curr_sample, -32768, 32767);
    int16_t s = (int16_t)((dsp_rom(q, (uint16_t)(DATA_ADPCM_TAB + 8 + step)) * p->step_size) >> 6);
    p->step_size = s < 1 ? 1 : s > 2000 ? 2000 : s;
    return (int16_t)((delta * p->cur_vol) >> 16);
}

static int16_t echo_apply(QsEcho *e, int32_t input) {  /* the delay line's last two samples averaged */
    int32_t old_sample = e->delay_line[e->delay_pos], last_sample = e->last_sample;
    e->last_sample = (int16_t)old_sample;
    old_sample = (old_sample + last_sample) >> 1;
    int32_t new_sample = add(input, shl(old_sample * e->feedback, 2));
    e->delay_line[e->delay_pos++] = (int16_t)(new_sample >> 16);
    if (e->delay_pos >= e->length) e->delay_pos = 0;
    return (int16_t)old_sample;
}

static int32_t fir_apply(QsFir *f, int16_t input) {  /* the Q1 transfer function */
    int32_t output = 0, tap = 0;
    for (; tap < f->tap_count - 1; tap++) {
        output = add(output, -shl(f->taps[tap] * f->delay_line[f->delay_pos++], 2));
        if (f->delay_pos >= f->tap_count - 1) f->delay_pos = 0;
    }
    output = add(output, -shl(f->taps[tap] * input, 2));
    f->delay_line[f->delay_pos++] = input;
    if (f->delay_pos >= f->tap_count - 1) f->delay_pos = 0;
    return output;
}

static int32_t delay_apply(QsDelay *d, int32_t input) {
    d->delay_line[d->write_pos++] = (int16_t)(input >> 16);
    if (d->write_pos >= 51) d->write_pos = 0;
    int32_t output = d->delay_line[d->read_pos++] * d->volume;
    if (d->read_pos >= 51) d->read_pos = 0;
    return output;
}

static void delay_update(QsDelay *d) {
    int16_t pos = (int16_t)((d->write_pos - d->delay) % 51);
    d->read_pos = (int16_t)(pos < 0 ? pos + 51 : pos);
}

static void normal_update(QSound *q) {
    q->ready_flag = 0x80;
    int16_t len = (int16_t)(q->echo.end_pos - (q->state == STATE_NORMAL2 ? DELAY_BASE_OFFSET2 : DELAY_BASE_OFFSET));
    q->echo.length = len < 0 ? 0 : len > 1024 ? 1024 : len;
    int32_t echo_input = 0;
    for (int i = 0; i < 16; i++) q->voice_output[i] = voice_update(q, &q->voice[i], &echo_input);
    int a = q->state_counter % 3;  /* one ADPCM voice a sample */
    q->voice_output[16 + a] = adpcm_update(q, &q->adpcm[a], q->voice_output[16 + a], q->state_counter / 3);
    int16_t echo_output = echo_apply(&q->echo, echo_input);
    for (int ch = 0; ch < 2; ch++) {
        /* the echo: on the unfiltered part of the left, the filtered part of the right */
        int32_t wet = ch == 1 ? echo_output * 16384 : 0, dry = ch == 0 ? echo_output * 16384 : 0;
        for (int i = 0; i < 19; i++) {
            uint16_t pan = (uint16_t)(q->voice_pan[i] + ch * PAN_TABLE_CH_OFFSET);
            dry = add(dry, -(q->voice_output[i] * (int16_t)dsp_rom(q, (uint16_t)(pan + PAN_TABLE_DRY))));
            wet = add(wet, -(q->voice_output[i] * (int16_t)dsp_rom(q, (uint16_t)(pan + PAN_TABLE_WET))));
        }
        dry = clamp(dry, -0x1FFFFFFF, 0x1FFFFFFF) * 4;
        wet = clamp(wet, -0x1FFFFFFF, 0x1FFFFFFF) * 4;
        wet = fir_apply(&q->filter[ch], (int16_t)(wet >> 16));
        if (q->state == STATE_NORMAL2) dry = fir_apply(&q->alt_filter[ch], (int16_t)(dry >> 16));
        int32_t output = add(delay_apply(&q->wet[ch], wet), delay_apply(&q->dry[ch], dry));
        output = (int32_t)((uint32_t)add(output, 0x2000) & ~0x3FFFu);  /* the DSP's rounding */
        q->out[ch] = (int16_t)clamp(output >> 14, -0x7FFF, 0x7FFF);
        if (q->delay_update) delay_update(&q->wet[ch]), delay_update(&q->dry[ch]);
    }
    q->delay_update = 0;
    if (++q->state_counter > 5) q->state_counter = 0, q->state = q->next_state;  /* the next state after 6 samples */
}

void qsound_sample(QSound *q, int16_t out[2]) {
    switch (q->state) {
    case STATE_REFRESH1: refresh_filter(q, 0); break;
    case STATE_REFRESH2: refresh_filter(q, 1); break;
    case STATE_NORMAL1:
    case STATE_NORMAL2: normal_update(q); break;
    default: state_init(q); break;  /* boot, init 1 and 2 */
    }
    out[0] = q->out[0], out[1] = q->out[1];
}
