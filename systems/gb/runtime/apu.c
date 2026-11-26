/* The Game Boy's sound (apu.h). Channel i's registers are NRi0-NRi4 at
 * $FF10 + 5i: 0, 1 pulses, 2 wave, 3 noise. CGB mode differs in a few
 * details (blargg cgb_sound): wave RAM while playing is the byte being
 * played at any time, no retrigger corruption, and powering off clears
 * the length counters too. */
#include <string.h>

#include "gb.h"

#define IO(k) g->io[k]
static int nr(int ch, int k) { return 0x10 + 5 * ch + k; }
static int freq(const Gb *g, int ch) { return IO(nr(ch, 3)) | (IO(nr(ch, 4)) & 7) << 8; }
static int dac_on(const Gb *g, int ch) { return ch == 2 ? IO(0x1A) & 0x80 : IO(nr(ch, 2)) & 0xF8; }
static int noise_period(const Gb *g) {  /* M-cycles: divisor 8, 16, 32 .. 112 clocks, shifted */
    int r = IO(0x22) & 7;
    return (r ? 4 * r : 2) << (IO(0x22) >> 4);
}

/* bits that read as 1 ($FF10-$FF2F) */
static const uint8_t MASK[0x20] = {
    0x80, 0x3F, 0x00, 0xFF, 0xBF, 0xFF, 0x3F, 0x00, 0xFF, 0xBF, 0x7F, 0xFF, 0x9F, 0xFF, 0xBF, 0xFF,
    0xFF, 0x00, 0x00, 0xBF, 0x00, 0x00, 0x70, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

/* ---- sweep (channel 0) ---- */
static int sweep_calc(Gb *g) {  /* the next frequency; above 2047 the channel stops */
    GbApu *p = &g->apu;
    int d = p->shadow >> (IO(0x10) & 7), f;
    if (IO(0x10) & 8) f = p->shadow - d, p->sweep_neg_used = 1;
    else f = p->shadow + d;
    if (f > 2047) p->on[0] = 0;
    return f;
}
static void sweep_clock(Gb *g) {
    GbApu *p = &g->apu;
    if (--p->sweep_timer) return;
    int period = IO(0x10) >> 4 & 7;
    p->sweep_timer = period ? period : 8;
    if (!p->sweep_on || !period) return;
    int f = sweep_calc(g);
    if (f <= 2047 && (IO(0x10) & 7)) {
        p->shadow = (uint16_t)f;
        IO(0x13) = (uint8_t)f, IO(0x14) = (uint8_t)((IO(0x14) & ~7) | f >> 8);
        sweep_calc(g);  /* checked again for overflow, not stored */
    }
}

/* ---- frame sequencer: length at steps 0 2 4 6, sweep at 2 6, envelopes at 7 ---- */
void apu_frame_step(Gb *g) {
    GbApu *p = &g->apu;
    if (!p->power) return;
    int s = p->fs_step;
    p->fs_step = (uint8_t)((s + 1) & 7);
    if (!(s & 1))
        for (int i = 0; i < 4; i++)
            if ((IO(nr(i, 4)) & 0x40) && p->len[i] && !--p->len[i]) p->on[i] = 0;
    if (s == 2 || s == 6) sweep_clock(g);
    if (s == 7)
        for (int i = 0; i < 4; i++) {
            int period = IO(nr(i, 2)) & 7;
            if (i == 2 || !p->on[i] || !period || --p->env_timer[i]) continue;
            p->env_timer[i] = (uint8_t)period;
            if (IO(nr(i, 2)) & 8) { if (p->vol[i] < 15) p->vol[i]++; }
            else if (p->vol[i]) p->vol[i]--;
        }
}

static void trigger(Gb *g, int ch) {
    GbApu *p = &g->apu;
    int was_on = p->on[ch];
    p->on[ch] = dac_on(g, ch) != 0;
    if (ch == 2) {
        /* DMG: retriggering in the cycle before a sample is read corrupts
         * wave RAM's first bytes with the ones about to be read */
        if (!g->cgb && was_on && p->timer[2] == 1) {
            int k = ((p->wave_pos + 1) >> 1) & 15;
            if (k < 4) IO(0x30) = IO(0x30 + k);
            else memcpy(g->io + 0x30, g->io + 0x30 + (k & ~3), 4);
        }
        p->timer[2] = 2048 - freq(g, 2) + 3;  /* the first sample comes a little late */
        p->wave_pos = 0;
        return;
    }
    p->vol[ch] = IO(nr(ch, 2)) >> 4;
    p->env_timer[ch] = IO(nr(ch, 2)) & 7;
    if (ch == 3) {
        p->timer[3] = noise_period(g);
        p->lfsr = 0x7FFF;
        return;
    }
    p->timer[ch] = 2048 - freq(g, ch);
    if (ch == 0) {
        int period = IO(0x10) >> 4 & 7, shift = IO(0x10) & 7;
        p->shadow = (uint16_t)freq(g, 0);
        p->sweep_timer = period ? period : 8;
        p->sweep_on = period || shift;
        p->sweep_neg_used = 0;
        if (shift) sweep_calc(g);
    }
}

/* ---- registers ---- */
uint8_t apu_read(Gb *g, uint16_t a) {
    GbApu *p = &g->apu;
    if (a >= 0xFF30) {  /* wave RAM; while playing (DMG) only in the cycle a sample is read, and then that byte */
        if (!p->on[2]) return IO(a & 0x7F);
        return p->wave_just_read || g->cgb ? IO(0x30 + p->wave_pos / 2) : 0xFF;
    }
    if (a == 0xFF26) return (uint8_t)(0x70 | p->power << 7 | p->on[0] | p->on[1] << 1 | p->on[2] << 2 | p->on[3] << 3);
    return IO(a & 0x7F) | MASK[a - 0xFF10];
}

void gb_apu_write(Gb *g, uint16_t a, uint8_t v) {
    GbApu *p = &g->apu;
    int r = a & 0x7F;
    if (a >= 0xFF30) {
        if (!p->on[2]) IO(r) = v;
        else if (p->wave_just_read || g->cgb) IO(0x30 + p->wave_pos / 2) = v;
        return;
    }
    if (a == 0xFF26) {
        if (!(v & 0x80) && p->power) {  /* off: every register cleared; the length counters stay (DMG) */
            memset(g->io + 0x10, 0, 0x16);
            memset(p->on, 0, sizeof p->on);
            if (g->cgb) memset(p->len, 0, sizeof p->len);
            p->power = 0;
            p->ds_delay = p->fs_pending = 0;
        } else if ((v & 0x80) && !p->power) {
            p->power = 1;
            p->fs_step = 0;
            p->duty_pos[0] = p->duty_pos[1] = 0;
            p->wave_sample = 0;
        }
        return;
    }
    if (a > 0xFF26) return;  /* unused */
    if (!p->power && g->cgb) return;
    if (!p->power) {  /* off: only the length counters can be written (DMG) */
        if (r == 0x11 || r == 0x16) v &= 0x3F;
        else if (r != 0x1B && r != 0x20) return;
    }
    uint8_t old = IO(r);
    IO(r) = v;
    int ch = (r - 0x10) / 5, k = (r - 0x10) % 5;
    if (ch > 3) return;  /* NR50, NR51 */
    switch (k) {
    case 0:
        if (ch == 0 && p->sweep_neg_used && !(v & 8)) p->on[0] = 0;  /* leaving negate mode after using it */
        if (ch == 2 && !(v & 0x80)) p->on[2] = 0;
        break;
    case 1: p->len[ch] = (uint16_t)(ch == 2 ? 256 - v : 64 - (v & 63)); break;
    case 2: if (ch != 2 && !(v & 0xF8)) p->on[ch] = 0; break;  /* the DAC turned off */
    case 4: {
        /* enabling the length counter when the next step won't clock it
         * clocks it once now; so does a trigger reloading it */
        int max = ch == 2 ? 256 : 64, early = p->fs_step & 1;
        if (early && (v & 0x40) && !(old & 0x40) && p->len[ch] && !--p->len[ch] && !(v & 0x80)) p->on[ch] = 0;
        if (v & 0x80) {
            if (!p->len[ch]) p->len[ch] = (uint16_t)(max - (early && (v & 0x40)));
            trigger(g, ch);
        }
        break;
    }
    }
}

/* ---- one M-cycle: the channels' timers, then the mix ---- */
void apu_tick(Gb *g) {
    GbApu *p = &g->apu;
    p->wave_just_read = 0;
    if (p->power) {
        static const uint8_t DUTY[4] = {0x01, 0x81, 0x87, 0x7E};  /* 12.5 25 50 75 %, step 0 first */
        int out[4] = {0, 0, 0, 0};
        for (int i = 0; i < 2; i++) {
            if (!p->on[i]) continue;
            if (--p->timer[i] <= 0) p->timer[i] = 2048 - freq(g, i), p->duty_pos[i] = (p->duty_pos[i] + 1) & 7;
            out[i] = (DUTY[IO(nr(i, 1)) >> 6] >> p->duty_pos[i] & 1) * p->vol[i];
        }
        if (p->on[2]) {
            for (int h = 0; h < 2; h++)  /* 2 MHz; "just read" only when the second half read one */
                if (p->wave_just_read = 0, --p->timer[2] <= 0) {
                    p->timer[2] = 2048 - freq(g, 2);
                    p->wave_pos = (p->wave_pos + 1) & 31;
                    p->wave_sample = IO(0x30 + p->wave_pos / 2) >> (p->wave_pos & 1 ? 0 : 4) & 15;
                    p->wave_just_read = 1;
                }
            static const uint8_t SHIFT[4] = {4, 0, 1, 2};  /* mute, 100 50 25 % */
            out[2] = p->wave_sample >> SHIFT[IO(0x1C) >> 5 & 3];
        }
        if (p->on[3]) {
            if (--p->timer[3] <= 0) {
                p->timer[3] = noise_period(g);
                if ((IO(0x22) >> 4) < 14) {
                    int x = (p->lfsr ^ p->lfsr >> 1) & 1;
                    p->lfsr = (uint16_t)(p->lfsr >> 1 | x << 14);
                    if (IO(0x22) & 8) p->lfsr = (uint16_t)((p->lfsr & ~0x40) | x << 6);
                }
            }
            out[3] = (~p->lfsr & 1) * p->vol[3];
        }
        /* each DAC turns 0-15 into +1 .. -1 (off: nothing); NR51 routes, NR50 scales each side */
        float l = 0, r = 0;
        for (int i = 0; i < 4; i++) {
            if (!dac_on(g, i)) continue;
            float s = 1.0f - out[i] / 7.5f;
            if (IO(0x25) & 0x10 << i) l += s;
            if (IO(0x25) & 1 << i) r += s;
        }
        p->acc[0] += l * ((IO(0x24) >> 4 & 7) + 1) / 32.0f;
        p->acc[1] += r * ((IO(0x24) & 7) + 1) / 32.0f;
    }
    p->acc_n++;
    p->frac += GB_SAMPLE_RATE;
    if (p->frac < 1048576) return;
    p->frac -= 1048576;
    for (int c = 0; c < 2; c++) {
        float x = p->acc[c] / (float)p->acc_n;
        float y = x - p->cap[c];  /* the output capacitor (SameBoy's charge factor 0.999958 per clock, at 48 kHz) */
        p->cap[c] = x - y * 0.996336f;
        p->acc[c] = 0;
        if (p->buf_len < GB_APU_BUF) p->buf[p->buf_len * 2 + c] = 0.5f * y;
    }
    p->acc_n = 0;
    if (p->buf_len < GB_APU_BUF) p->buf_len++;
}

void apu_boot(Gb *g) {
    static const uint8_t SOUND[0x17] = {0x80, 0xBF, 0xF3, 0xFF, 0xBF, 0x00, 0x3F, 0x00, 0xFF, 0xBF, 0x7F, 0xFF,
                                        0x9F, 0xFF, 0xBF, 0x00, 0xFF, 0x00, 0x00, 0xBF, 0x77, 0xF3, 0xF1};
    memcpy(g->io + 0x10, SOUND, sizeof SOUND);
    GbApu *p = &g->apu;
    p->power = 1;
    p->on[0] = 1;  /* the boot sound's channel, its envelope faded to 0 */
    p->timer[0] = p->timer[1] = p->timer[2] = p->timer[3] = 1;
}

int gb_apu_take_samples(Gb *g, float *out, int max) {
    GbApu *p = &g->apu;
    int n = p->buf_len < max ? p->buf_len : max;
    memcpy(out, p->buf, (size_t)n * 2 * sizeof *out);
    memmove(p->buf, p->buf + 2 * n, (size_t)(p->buf_len - n) * 2 * sizeof *out);
    p->buf_len -= n;
    return n;
}
