/* Game Boy without a window, for tests (tests/gb/test_roms.py, test_gb_recomp.py).
 *   gb_headless ROM [--frames N] [--pgm FILE] [--wav FILE] [--play] [--state-at F FILE] [--load-state FILE]
 *               [--misses FILE] [--diff] [--coverage] [--ppm FILE] [--model dmg|cgb|...]
 *   --pgm         write the last whole frame as a grey image (shade 0 = white)
 *   --wav         write the sound (48 kHz stereo, 16-bit)
 *   --ppm         write the last whole frame in colour (CGB: 5-bit components as (c << 3) | (c >> 2))
 *   --model       run as this model: dmg, cgb (a DMG game: compatibility mode), cgb-e, cgb0, agb, dmg0, mgb, sgb, sgb2 (default: what the header asks for)
 *   --play        scripted input: Start and A taps, later walking right
 *   --state-at    save a state before frame F; --load-state: start from one
 *   --misses      write the ROM code the interpreter ran ("MISS $PC bank B",
 *                 input for gbrecomp; without recompiled code: everything run)
 *   --diff        run an interpreter-only Game Boy in lockstep: the CPU must
 *                 match after every step (chained blocks: one step), the whole
 *                 machine after every frame
 *   --coverage    print the share of CPU cycles run by recompiled code
 * Runs up to N frames (default 3600), stopping early when a test ROM
 * reports on the serial port: blargg's "Passed" / "Failed" text, or
 * mooneye's bytes 3 5 8 13 21 34 (pass) / six $42 (fail), or blargg's
 * result in cartridge RAM ($A000-). Prints what the serial port received (other bytes as \xHH) and a last line
 * "result: passed|failed|timeout". Exit code 0 only for passed. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stddef.h>

#include "capture.h"
#include "file.h"
#include "gb.h"
#include "input_log.h"  /* PAD_* */
#include "recomp_rt.h"

static int result(const Gb *g) {  /* 1 pass, -1 fail, 0 not yet */
    static const char FIB[6] = {3, 5, 8, 13, 21, 34}, FAIL[6] = {0x42, 0x42, 0x42, 0x42, 0x42, 0x42};
    const char *s = g->serial_out;
    int n = g->serial_n;
    if (n >= 6 && !memcmp(s + n - 6, FIB, 6)) return 1;
    if (n >= 6 && !memcmp(s + n - 6, FAIL, 6)) return -1;
    char text[sizeof g->serial_out + 1];
    memcpy(text, s, (size_t)n);
    text[n] = 0;
    if (strstr(text, "Passed")) return 1;
    if (strstr(text, "Failed")) return -1;
    /* blargg's memory protocol: $A001 = DE B0 61, $A000 = $80 while running, then the result code */
    const uint8_t *m = g->cart.ram;
    if (g->cart.ram_size >= 0x2000 && m[1] == 0xDE && m[2] == 0xB0 && m[3] == 0x61 && m[0] != 0x80)
        return m[0] == 0 ? 1 : -1;
    return 0;
}

/* blargg's text at $A004, when it reports through memory */
static const char *memory_text(const Gb *g) {
    const uint8_t *m = g->cart.ram;
    if (g->cart.ram_size < 0x2000 || m[1] != 0xDE || m[2] != 0xB0 || m[3] != 0x61) return "";
    return (const char *)m + 4;
}

/* ---- lockstep comparison (--diff) ---- */
static int same_cpu(const GbCpu *a, const GbCpu *b) {
    GbCpu x = *a, y = *b;
    x.bus = y.bus = NULL;
    return !memcmp(&x, &y, sizeof x);
}

/* The machine's fields; what differs between the two runs by design
 * (recomp_*, cycles_*, misses, the pointers) is left out. */
#define F(x) {#x, offsetof(Gb, x), sizeof(((Gb *)0)->x)}
static const struct { const char *name; size_t off, len; } FIELDS[] = {
    F(vram), F(wram), F(oam), F(hram), F(io), F(apu), F(ie), F(ifl), F(div), F(tima), F(tma), F(tac),
    F(tima_reload), F(sb), F(sc), F(speed_wait), F(serial_left), F(serial_out), F(serial_n), F(p1), F(pad), F(lcdc), F(stat),
    F(scy), F(scx), F(ly), F(lyc), F(wy), F(wx), F(stat_line), F(mode), F(wy_hit), F(win_line), F(dot),
    F(m3), F(fb), F(frame), F(frame_count), F(dma_reg), F(dma_start), F(dma_on), F(dma_pos), F(dma_src),
    F(dma_next), F(frame_end), F(cgb), F(compat), F(vbk), F(svbk), F(opri), F(key1), F(double_speed), F(half), F(bcps),
    F(ocps), F(bg_pal), F(obj_pal), F(hdma_src), F(hdma_dst), F(hdma_left), F(hdma_on), F(hdma_due),
};
static const char *differs(const Gb *a, const Gb *b) {
    if (!same_cpu(&a->cpu, &b->cpu)) return "cpu";
    static GbCart x, y;
    x = a->cart, y = b->cart;
    x.rom = y.rom = NULL;
    if (memcmp(&x, &y, sizeof x)) return "cart";
    for (size_t i = 0; i < sizeof FIELDS / sizeof *FIELDS; i++)
        if (memcmp((const char *)a + FIELDS[i].off, (const char *)b + FIELDS[i].off, FIELDS[i].len)) return FIELDS[i].name;
    return NULL;
}

static void print_cpu(const char *who, const GbCpu *c) {
    printf("  %-11s PC=%04X SP=%04X A=%02X F=%02X B=%02X C=%02X D=%02X E=%02X H=%02X L=%02X ime=%d ei=%d halt=%d cycles=%llu\n",
           who, c->pc, c->sp, c->a, c->f, c->b, c->c, c->d, c->e, c->h, c->l, c->ime, c->ei, c->halted,
           (unsigned long long)c->cycles);
}

/* One frame of both; 0, or -1 after printing the first difference. */
static int frame_diff(Gb *g, Gb *ref, long frame) {
    g->frame_end += gb_frame_cycles(g);
    ref->frame_end = g->frame_end;
    while (g->cpu.cycles < g->frame_end) {
        GbCpu before = g->cpu;
        int native = g->recomp_on && !g->speed_wait && before.pc < 0x8000 && gb_recomp_program->lookup(before.pc, gb_cart_bank(&g->cart, before.pc));
        gb_step(g);
        while (ref->cpu.cycles < g->cpu.cycles) gb_step(ref);
        const char *what = same_cpu(&g->cpu, &ref->cpu) ? NULL : "cpu";
        if (!what && g->cpu.cycles >= g->frame_end) what = differs(g, ref);
        if (!what) continue;
        printf("DIVERGENCE (%s) in frame %ld, step from PC=%04X (%s)\n", what, frame, before.pc,
               native ? "recompiled block" : "interpreted");
        print_cpu("before", &before);
        print_cpu("recompiled", &g->cpu);
        print_cpu("interpreter", &ref->cpu);
        return -1;
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: gb_headless ROM [--frames N]\n");
        return 2;
    }
    long frames = 3600, state_at = -1;
    const char *pgm = NULL, *wav = NULL, *state_out = NULL, *state_in = NULL;
    const char *misses = NULL, *ppm = NULL;
    int play = 0, diff = 0, coverage = 0, model = GB_MODEL_AUTO;
    for (int i = 2; i < argc; i++) {
        if (!strcmp(argv[i], "--frames") && i + 1 < argc) frames = atol(argv[++i]);
        else if (!strcmp(argv[i], "--pgm") && i + 1 < argc) pgm = argv[++i];
        else if (!strcmp(argv[i], "--wav") && i + 1 < argc) wav = argv[++i];
        else if (!strcmp(argv[i], "--play")) play = 1;
        else if (!strcmp(argv[i], "--state-at") && i + 2 < argc) state_at = atol(argv[++i]), state_out = argv[++i];
        else if (!strcmp(argv[i], "--load-state") && i + 1 < argc) state_in = argv[++i];
        else if (!strcmp(argv[i], "--misses") && i + 1 < argc) misses = argv[++i];
        else if (!strcmp(argv[i], "--diff")) diff = 1;
        else if (!strcmp(argv[i], "--coverage")) coverage = 1;
        else if (!strcmp(argv[i], "--ppm") && i + 1 < argc) ppm = argv[++i];
        else if (!strcmp(argv[i], "--model") && i + 1 < argc) {
            const char *m = argv[++i];
            static const char *const NAMES[] = {"dmg", "cgb", "dmg0", "mgb", "sgb", "sgb2", "agb", "cgb0", "cgb-e"};  /* GB_MODEL_* order */
            model = -2;
            for (int k = 0; k < (int)(sizeof NAMES / sizeof *NAMES); k++)
                if (!strcmp(m, NAMES[k])) model = k;
            if (model == -2) { fprintf(stderr, "gb_headless: --model dmg, cgb, cgb0, cgb-e, agb, dmg0, mgb, sgb or sgb2\n"); return 2; }
        }
        else { fprintf(stderr, "gb_headless: unknown option %s\n", argv[i]); return 2; }
    }
    size_t size;
    uint8_t *rom = file_read(argv[1], &size);
    if (!rom) { perror(argv[1]); return 2; }
    static Gb g, ref;
    char err[128];
    if (gb_load_model(&g, rom, (size_t)size, model, err, sizeof err) != 0 ||
        (diff && gb_load_model(&ref, rom, (size_t)size, model, err, sizeof err) != 0)) {
        fprintf(stderr, "%s: %s\n", argv[1], err);
        return 2;
    }
    free(rom);
    if (gb_recomp_program && !g.recomp_on)
        printf("WARNING: the recompiled code is for %s; this ROM differs, all of it is interpreted\n", gb_recomp_program->rom_name);
    if (diff && !g.recomp_on) { fprintf(stderr, "--diff needs matching recompiled code\n"); return 2; }
    ref.recomp_on = 0;
    if (state_in && (gb_state_load(&g, state_in, err, sizeof err) != 0 || (diff && gb_state_load(&ref, state_in, err, sizeof err) != 0))) {
        fprintf(stderr, "%s: %s\n", state_in, err);
        return 2;
    }
    ref.recomp_on = 0;
    if (misses && !(g.misses = calloc(gb_miss_slots(&g), 1))) { perror("misses"); return 2; }
    FILE *w = wav ? capture_wav_open(wav) : NULL;
    if (wav && !w) { perror(wav); return 2; }
    int r = 0;
    for (long i = 0; i < frames && !(r = result(&g)) && !g.cpu.jammed; i++) {
        if (i == state_at && gb_state_save(&g, state_out) != 0) { perror(state_out); return 2; }
        if (play) {  /* Start and A taps to get past menus, then some walking right */
            long k = i % 90;
            uint8_t pad = k < 5 ? PAD_START : k >= 45 && k < 48 ? PAD_A : i > 900 && k >= 60 ? PAD_RIGHT : 0;
            gb_set_pad(&g, pad);
            if (diff) gb_set_pad(&ref, pad);
        }
        if (!diff) gb_run_frame(&g);
        else if (frame_diff(&g, &ref, i) != 0) return 1;
        ref.apu.buf_len = 0;  /* drained as g is below */
        float buf[GB_APU_BUF * 2];
        int n = 2 * gb_apu_take_samples(&g, buf, GB_APU_BUF);  /* floats: left, right, ... */
        for (int k = 0; w && k < n; k++) {
            float x = buf[k] < -1 ? -1 : buf[k] > 1 ? 1 : buf[k];
            int16_t v = (int16_t)(x * 32767);
            capture_wav_samples(w, &v, 1);
        }
    }
    if (w && capture_wav_close(w, 48000, 2)) { perror(wav); return 2; }  /* stereo, 48000 Hz */
    if (pgm) {  /* the last whole frame; shade 0 (light) = 255, as dmg-acid2's reference */
        FILE *o = fopen(pgm, "wb");
        if (!o) { perror(pgm); return 2; }
        fprintf(o, "P5\n160 144\n255\n");
        for (int i = 0; i < 160 * 144; i++) fputc((3 - g.frame[i]) * 85, o);
        fclose(o);
    }
    if (ppm) {
        static uint32_t rgb[160 * 144];
        for (int i = 0; i < 160 * 144; i++) {
            uint16_t c = g.frame[i];
            rgb[i] = 0;
            for (int k = 0; k < 3; k++) {  /* red, green, blue */
                unsigned v = g.cgb ? (c >> (5 * k) & 31u) << 3 | (c >> (5 * k) & 31u) >> 2 : (3u - (c & 3u)) * 85u;
                rgb[i] |= v << (16 - 8 * k);
            }
        }
        if (capture_ppm(ppm, rgb, 160, 144, 160)) { perror(ppm); return 2; }
    }
    for (int i = 0; i < g.serial_n; i++) {
        unsigned char ch = (unsigned char)g.serial_out[i];
        if (ch == '\n' || (ch >= 0x20 && ch < 0x7F)) putchar(ch);
        else printf("\\x%02X", ch);
    }
    if (!g.serial_n) printf("%.1024s", memory_text(&g));
    printf("\nresult: %s%s\n", r > 0 ? "passed" : r < 0 ? "failed" : "timeout", g.cpu.jammed ? " (CPU jammed)" : "");
    if (diff) printf("DIFF OK: no divergence\n");
    if (coverage) {
        double total = (double)(g.cycles_native + g.cycles_interp);
        printf("COVERAGE %.3f%% of CPU cycles recompiled\n", total ? 100 * g.cycles_native / total : 0.0);
    }
    if (misses) {
        FILE *m = fopen(misses, "w");
        if (!m) { perror(misses); return 2; }
        gb_misses_write(&g, m);
        fclose(m);
        return 0;  /* a trace: how the ROM's own test ended does not matter */
    }
    gb_free(&g);
    if (diff) gb_free(&ref);
    return r > 0 ? 0 : 1;
}
