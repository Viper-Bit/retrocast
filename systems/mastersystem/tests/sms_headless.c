/* Runs a .sms without a window, for tests and scripts: --frames N, --play
 * (button 1 taps, and Start on a Game Gear, to get past title screens, then
 * walking right), --ppm FILE
 * (the last frame), --wav FILE, --state-at N FILE, --load-state FILE,
 * --pal/--ntsc, --misses FILE (a trace for smsrecomp), --diff (run the
 * interpreter alongside the recompiled code) and --coverage. A Game Gear
 * game (sms_gg_mode) runs in that mode; --ppm and the colour count are then
 * its LCD's 160x144. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "capture.h"
#include "input_log.h"
#include "loader.h"
#include "sms.h"

static uint16_t scripted(long frame, int gg) {
    long k = frame % 60;
    uint16_t pad = frame >= 60 && k < 4 ? PAD_B : 0;
    /* a Game Gear title screen waits for Start (on a Master System it is Pause) */
    if (gg && frame >= 60 && frame <= 600 && k >= 30 && k < 34) pad |= PAD_START;
    if (frame > 600 && k >= 20) pad |= PAD_RIGHT;
    if (frame > 600 && k >= 40 && k < 44) pad |= PAD_A;
    return pad;
}

static int write_wav(FILE *w, long n) {  /* mono, 16-bit: the sizes once known */
    uint32_t data = (uint32_t)n * 2, riff = data + 36, rate = SMS_SAMPLE_RATE, bps = rate * 2;
    uint8_t h[44] = {'R', 'I', 'F', 'F', 0, 0, 0, 0, 'W', 'A', 'V', 'E', 'f', 'm', 't', ' ', 16, 0, 0, 0, 1, 0, 1, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 16, 0, 'd', 'a', 't', 'a'};
    memcpy(h + 4, &riff, 4), memcpy(h + 24, &rate, 4), memcpy(h + 28, &bps, 4), memcpy(h + 40, &data, 4);
    return fseek(w, 0, SEEK_SET) || fwrite(h, 1, 44, w) != 44;
}

/* The first thing the two runs disagree on that could affect a later frame,
 * or NULL. Fields, not the structs: Z80.bus points at each machine, and
 * padding differs. */
#define DIFF(cond, what) if (cond) return what
static const char *differs(const Sms *a, const Sms *b) {
    const Z80 *x = &a->cpu, *y = &b->cpu;
    DIFF(x->tstates != y->tstates, "T-states");
    DIFF(x->pc != y->pc || x->sp != y->sp || x->wz != y->wz || x->addr != y->addr, "PC, SP, WZ or the address bus");
    DIFF(x->a != y->a || x->f != y->f || x->b != y->b || x->c != y->c || x->d != y->d || x->e != y->e ||
         x->h != y->h || x->l != y->l, "main registers");
    DIFF(x->ixh != y->ixh || x->ixl != y->ixl || x->iyh != y->iyh || x->iyl != y->iyl, "IX or IY");
    DIFF(x->af_ != y->af_ || x->bc_ != y->bc_ || x->de_ != y->de_ || x->hl_ != y->hl_, "shadow registers");
    DIFF(x->i != y->i || x->r != y->r, "I or R");
    DIFF(x->iff1 != y->iff1 || x->iff2 != y->iff2 || x->im != y->im || x->ei != y->ei || x->halted != y->halted,
         "interrupt state");
    DIFF(x->q != y->q || x->qprev != y->qprev || x->p != y->p, "Q or P");
    DIFF(memcmp(a->ram, b->ram, sizeof a->ram), "work RAM");
    DIFF(memcmp(a->cart.page, b->cart.page, sizeof a->cart.page) || a->cart.ram_used != b->cart.ram_used ||
         memcmp(a->cart.ram, b->cart.ram, sizeof a->cart.ram), "cartridge pages or RAM");
    DIFF(memcmp(a->vdp.vram, b->vdp.vram, sizeof a->vdp.vram), "VRAM");
    DIFF(memcmp(a->vdp.cram, b->vdp.cram, sizeof a->vdp.cram) || memcmp(a->vdp.reg, b->vdp.reg, sizeof a->vdp.reg),
         "CRAM or VDP registers");
    DIFF(a->vdp.status != b->vdp.status || a->vdp.addr != b->vdp.addr || a->vdp.code != b->vdp.code ||
         a->vdp.latch != b->vdp.latch || a->vdp.buffer != b->vdp.buffer || a->vdp.line_counter != b->vdp.line_counter ||
         a->vdp.line_flag != b->vdp.line_flag || a->vdp.vscroll != b->vdp.vscroll, "VDP state");
    DIFF(memcmp(a->vdp.frame, b->vdp.frame, sizeof a->vdp.frame), "picture");
    DIFF(memcmp(&a->psg, &b->psg, sizeof a->psg), "PSG");
    DIFF(a->mem_ctrl != b->mem_ctrl || a->io_ctrl != b->io_ctrl, "ports $3E/$3F");
    DIFF(a->samples_made != b->samples_made || a->writes != b->writes || a->frames != b->frames ||
         a->line != b->line || a->line_start != b->line_start, "frame position");
    return NULL;
}

int main(int argc, char **argv) {
    if (argc < 2 || argv[1][0] == '-') {
        fprintf(stderr, "usage: sms_headless ROM [--frames N] [--play] [--ppm FILE] [--wav FILE]\n"
                        "       [--state-at N FILE] [--load-state FILE] [--pal|--ntsc]\n"
                        "       [--misses FILE] [--diff] [--coverage]\n");
        return 2;
    }
    const char *path = argv[1], *ppm = NULL, *wav = NULL, *state_out = NULL, *state_in = NULL, *misses = NULL;
    long frames = 600, state_at = -1;
    int play = 0, pal = strstr(path, "(Europe)") != NULL, diff = 0, coverage = 0, gg;
    for (int i = 2; i < argc; i++) {
        if (!strcmp(argv[i], "--frames") && i + 1 < argc) frames = atol(argv[++i]);
        else if (!strcmp(argv[i], "--play")) play = 1;
        else if (!strcmp(argv[i], "--pal")) pal = 1;
        else if (!strcmp(argv[i], "--ntsc")) pal = 0;
        else if (!strcmp(argv[i], "--ppm") && i + 1 < argc) ppm = argv[++i];
        else if (!strcmp(argv[i], "--wav") && i + 1 < argc) wav = argv[++i];
        else if (!strcmp(argv[i], "--load-state") && i + 1 < argc) state_in = argv[++i];
        else if (!strcmp(argv[i], "--state-at") && i + 2 < argc) state_at = atol(argv[++i]), state_out = argv[++i];
        else if (!strcmp(argv[i], "--misses") && i + 1 < argc) misses = argv[++i];
        else if (!strcmp(argv[i], "--diff")) diff = 1;
        else if (!strcmp(argv[i], "--coverage")) coverage = 1;
        else { fprintf(stderr, "sms_headless: unknown option %s\n", argv[i]); return 2; }
    }
    uint8_t *rom;
    size_t size;
    char err[256];
    if (sms_load_rom(path, &rom, &size, err, sizeof err)) { fprintf(stderr, "%s\n", err); return 2; }
    static Sms s, reference;
    gg = sms_gg_mode(rom, size, path);
    sms_init(&s, rom, size, pal, gg);
    if (state_in && sms_load(&s, state_in, err, sizeof err)) { fprintf(stderr, "%s\n", err); return 2; }
    uint8_t *trace = NULL;
    if (misses) {
        trace = calloc(sms_miss_slots(&s), 1);
        if (!trace) { perror("misses"); return 2; }
        s.misses = trace;
    }
    if (diff) {
        sms_init(&reference, rom, size, pal, gg);
        reference.recomp_on = 0;
        if (state_in && sms_load(&reference, state_in, err, sizeof err)) { fprintf(stderr, "%s\n", err); return 2; }
        reference.misses = NULL;
        if (!s.recomp_on) { fprintf(stderr, "--diff needs recompiled code for this ROM\n"); return 2; }
    }
    FILE *w = wav ? fopen(wav, "wb") : NULL;
    if (wav && (!w || fseek(w, 44, SEEK_SET))) { perror(wav); return 2; }
    long samples = 0;
    int failed = 0;
    for (long i = 0; i < frames && !failed; i++) {
        if (i == state_at && sms_save(&s, state_out)) { perror(state_out); return 2; }
        uint16_t pad = play ? scripted(i, gg) : 0;
        sms_frame(&s, pad, 0);
        if (diff) {
            sms_frame(&reference, pad, 0);
            const char *what = differs(&s, &reference);
            if (what) {
                printf("diff: frame %ld: %s (pc=%04X/%04X)\n", i, what, s.cpu.pc, reference.cpu.pc);
                failed = 1;
            }
        }
        for (unsigned k = 0; w && k < s.n_samples; k++, samples++) {
            float x = s.samples[k] < -1 ? -1 : s.samples[k] > 1 ? 1 : s.samples[k];
            int16_t v = (int16_t)(x * 32767);
            fwrite(&v, 2, 1, w);
        }
    }
    if (w && (write_wav(w, samples) || fclose(w))) { perror(wav); return 2; }
    unsigned w0 = gg ? GG_WIDTH : SMS_WIDTH, h0 = gg ? GG_HEIGHT : SMS_HEIGHT, x0 = gg ? GG_X : 0, y0 = gg ? GG_Y : 0;
    static uint8_t seen[4096];
    unsigned colours = 0;
    for (unsigned y = 0; y < h0; y++)
        for (unsigned x = 0; x < w0; x++) {
            uint32_t rgb = sms_color(&s, s.vdp.frame[(y + y0) * SMS_WIDTH + x + x0]);
            unsigned c = (rgb >> 20 & 15) << 8 | (rgb >> 12 & 15) << 4 | (rgb >> 4 & 15);
            colours += !seen[c], seen[c] = 1;
        }
    printf("frames=%u pc=%04X vdp_writes=%u colours=%u\n", s.frames, s.cpu.pc, s.writes, colours);
    if (diff && !failed) printf("diff: %u frames, no difference\n", s.frames);
    if (coverage) {
        uint64_t total = s.cycles_native + s.cycles_interp;
        printf("coverage: %.2f%% native=%llu interp=%llu\n",
               total ? 100.0 * (double)s.cycles_native / (double)total : 0.0,
               (unsigned long long)s.cycles_native, (unsigned long long)s.cycles_interp);
    }
    if (misses && trace) {
        FILE *m = fopen(misses, "wb");
        if (!m) { perror(misses); failed = 1; }
        else {
            sms_misses_write(&s, m);
            failed |= fclose(m) != 0;
        }
    }
    if (ppm) {
        static uint32_t rgb[SMS_WIDTH * SMS_HEIGHT];
        for (unsigned y = 0; y < h0; y++)
            for (unsigned x = 0; x < w0; x++) rgb[y * w0 + x] = sms_color(&s, s.vdp.frame[(y + y0) * SMS_WIDTH + x + x0]);
        if (capture_ppm(ppm, rgb, (int)w0, (int)h0, (int)w0)) { perror(ppm); return 2; }
    }
    free(trace);
    free(rom);
    return failed;
}
