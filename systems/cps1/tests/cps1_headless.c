/* Runs a CPS-1 game (a zip) without a window, for tests and scripts:
 * --frames N, --play (a coin and Start for player 1, then walking right and
 * tapping button 1), --ppm FILE (the last frame), --wav FILE (the sound:
 * 16-bit, mono at CPS1_SAMPLE_RATE or Q-Sound stereo at CPS1_QSOUND_RATE), --state-at N FILE (a save state after
 * frame N), --load-state FILE (start from one; --play goes on from its frame),
 * --misses FILE (the main-CPU code the interpreter ran: "MISS $PC" lines, for
 * cps1recomp), --diff (an interpreter-only machine in lockstep: the CPUs and
 * RAMs compared after every line, the whole machine after every frame; exit
 * 1 at the first difference), --coverage (the share of 68000 clocks run as
 * recompiled code).
 * Prints the game, the frames run and the colours in the last frame. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "capture.h"
#include "cps1.h"
#include "file.h"
#include "input_log.h"
#include "recomp_rt.h"

/* The machine with what differs by design blanked: the pointers, the jump
 * buffer, the recompiled code's own fields. */
static void comparable(const Cps1 *src, Cps1 *out) {
    *out = *src;
    out->rom = NULL, out->cpu.bus = out->z80.bus = NULL, out->oki.rom = NULL, out->recomp = NULL, out->misses = NULL;
    out->qs.dsp = NULL, out->qs.rom = NULL;
    memset(&out->cpu.abort, 0, sizeof out->cpu.abort);
    out->recomp_on = 0, out->cycles_native = out->cycles_interp = 0;
}
static int same_line(const Cps1 *a, const Cps1 *b) {
    M68k x = a->cpu, y = b->cpu;
    x.bus = y.bus = NULL;
    memset(&x.abort, 0, sizeof x.abort), memset(&y.abort, 0, sizeof y.abort);
    Z80 p = a->z80, q = b->z80;
    p.bus = q.bus = NULL;
    return !memcmp(&x, &y, sizeof x) && !memcmp(&p, &q, sizeof p) && !memcmp(a->ram, b->ram, sizeof a->ram) &&
           !memcmp(a->gfxram, b->gfxram, sizeof a->gfxram) && !memcmp(a->z80_ram, b->z80_ram, sizeof a->z80_ram) &&
           !memcmp(a->qram, b->qram, sizeof a->qram);
}

static uint16_t scripted(long frame) {
    long k = frame % 60;
    if (frame >= 300 && frame < 304) return PAD_SELECT;  /* a coin, once the game has booted */
    if (frame >= 1300 && frame < 1304) return PAD_START;  /* on the title screen */
    uint16_t pad = 0;
    if (frame > 1500 && k >= 20) pad |= PAD_RIGHT;
    if (frame > 1500 && k < 4) pad |= PAD_B;
    return pad;
}

static Cps1 machine, ref, cx, cy;  /* ref: --diff's interpreter-only machine; cx, cy: compared copies */

int main(int argc, char **argv) {
    const char *path = NULL, *ppm = NULL, *wav = NULL, *state_in = NULL, *state_out = NULL, *misses = NULL;
    int diff = 0, coverage = 0;
    long state_at = -1;
    long frames = 60;
    int play = 0;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--frames") && i + 1 < argc) frames = atol(argv[++i]);
        else if (!strcmp(argv[i], "--ppm") && i + 1 < argc) ppm = argv[++i];
        else if (!strcmp(argv[i], "--wav") && i + 1 < argc) wav = argv[++i];
        else if (!strcmp(argv[i], "--load-state") && i + 1 < argc) state_in = argv[++i];
        else if (!strcmp(argv[i], "--state-at") && i + 2 < argc) state_at = atol(argv[++i]), state_out = argv[++i];
        else if (!strcmp(argv[i], "--play")) play = 1;
        else if (!strcmp(argv[i], "--misses") && i + 1 < argc) misses = argv[++i];
        else if (!strcmp(argv[i], "--diff")) diff = 1;
        else if (!strcmp(argv[i], "--coverage")) coverage = 1;
        else if (argv[i][0] != '-') path = argv[i];
        else return fprintf(stderr, "unknown option %s\n", argv[i]), 2;
    }
    if (!path) return fprintf(stderr, "usage: cps1_headless GAME.zip [--frames N] [--play] [--ppm FILE] [--wav FILE]"
                                 " [--state-at N FILE] [--load-state FILE] [--misses FILE] [--diff] [--coverage]\n"), 2;
    size_t size;
    uint8_t *data = file_read(path, &size);
    if (!data) return fprintf(stderr, "%s: cannot read\n", path), 1;
    Cps1Rom rom;
    char err[512];
    if (cps1_open(path, data, size, &rom, err, sizeof err)) return fprintf(stderr, "%s\n", err), 1;
    free(data);
    const Cps1Game *g = rom.game;

    cps1_init(&machine, &rom);
    if (state_in && cps1_state_load(&machine, state_in, err, sizeof err)) return fprintf(stderr, "%s\n", err), 2;
    if (diff) {
        cps1_init_with(&ref, &rom, NULL);
        if (state_in && cps1_state_load(&ref, state_in, err, sizeof err)) return fprintf(stderr, "%s\n", err), 2;
        if (!machine.recomp_on) printf("diff: no recompiled code for this game: both machines interpret\n");
    }
    if (misses && !(machine.misses = calloc(rom.size[CPS1_R_MAIN] / 2 + 1, 1))) return fprintf(stderr, "out of memory\n"), 2;
    FILE *w = wav ? capture_wav_open(wav) : NULL;
    if (wav && !w) return perror(wav), 2;
    static int16_t buf[CPS1_SND_BUF];
    for (long f = 0; f < frames; f++) {
        uint16_t pad = play ? scripted((long)machine.frames) : 0;
        cps1_set_input(&machine, 0, pad);
        if (diff) {
            cps1_set_input(&ref, 0, pad);
            do {
                cps1_line(&machine), cps1_line(&ref);
                if (!same_line(&machine, &ref)) {
                    printf("diff: frame %ld line %d: the CPUs or RAM differ (68000 pc $%06X / $%06X, clocks %llu / %llu)\n", f,
                           machine.line - 1, (unsigned)((machine.cpu.pc - 4) & 0xFFFFFF), (unsigned)((ref.cpu.pc - 4) & 0xFFFFFF),
                           (unsigned long long)machine.cpu.cycles, (unsigned long long)ref.cpu.cycles);
                    return 1;
                }
            } while (machine.line < CPS1_LINES);
            comparable(&machine, &cx), comparable(&ref, &cy);
            if (memcmp(&cx, &cy, sizeof cx)) return printf("diff: frame %ld: the machines differ\n", f), 1;
            cps1_take_sound(&ref, buf, CPS1_SND_BUF);
        } else {
            cps1_frame(&machine);
        }
        int n = cps1_take_sound(&machine, buf, CPS1_SND_BUF);
        if (w) capture_wav_samples(w, buf, (size_t)n);
        if (state_out && (long)machine.frames == state_at && cps1_state_save(&machine, state_out)) return perror(state_out), 2;
    }
    if (w && capture_wav_close(w, (unsigned)cps1_sample_rate(g), (unsigned)cps1_channels(g))) return perror(wav), 2;

    static uint8_t seen[0xC00];
    int colours = 0;
    for (int i = 0; i < CPS1_WIDTH * CPS1_HEIGHT; i++) {
        uint16_t c = machine.frame[i] % 0xC00;
        if (!seen[c]) seen[c] = 1, colours++;
    }
    if (ppm) {
        static uint32_t rgb[CPS1_WIDTH * CPS1_HEIGHT];
        int w, h;
        cps1_picture(&machine, rgb, &w, &h);  /* turned for a vertical monitor */
        if (capture_ppm(ppm, rgb, w, h, w)) return perror(ppm), 1;
    }
    if (diff) printf("diff: %ld frames, no difference\n", frames);
    if (coverage) {
        uint64_t all = machine.cycles_native + machine.cycles_interp;
        printf("coverage: %.2f%% of 68000 clocks recompiled\n", all ? 100.0 * (double)machine.cycles_native / (double)all : 0.0);
    }
    if (misses) {
        FILE *mf = fopen(misses, "w");
        if (!mf) return perror(misses), 2;
        for (uint32_t a = 0; a < rom.size[CPS1_R_MAIN]; a += 2)
            if (machine.misses[a >> 1]) fprintf(mf, "MISS $%06X\n", (unsigned)a);
        if (fclose(mf)) return perror(misses), 2;
    }
    printf("game=%s frames=%ld colours=%d%s\n", g->id, frames, colours, machine.cpu.halted ? " halted" : "");
    cps1_unload(&rom);
    return machine.cpu.halted ? 1 : 0;
}
