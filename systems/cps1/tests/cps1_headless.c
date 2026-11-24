/* Runs a CPS-1 game (a zip) without a window, for tests and scripts:
 * --frames N, --play (a coin and Start for player 1, then walking right and
 * tapping button 1), --ppm FILE (the last frame), --wav FILE (the sound:
 * mono, 16-bit, at CPS1_SAMPLE_RATE), --state-at N FILE (a save state after
 * frame N), --load-state FILE (start from one; --play goes on from its frame).
 * Prints the game, the frames run and the colours in the last frame. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cps1.h"
#include "input_log.h"

static uint16_t scripted(long frame) {
    long k = frame % 60;
    if (frame >= 300 && frame < 304) return PAD_SELECT;  /* a coin, once the game has booted */
    if (frame >= 1300 && frame < 1304) return PAD_START;  /* on the title screen */
    uint16_t pad = 0;
    if (frame > 1500 && k >= 20) pad |= PAD_RIGHT;
    if (frame > 1500 && k < 4) pad |= PAD_B;
    return pad;
}

static int write_wav(FILE *w, long n) {  /* the header, once the sizes are known */
    uint32_t data = (uint32_t)n * 2, riff = data + 36, rate = CPS1_SAMPLE_RATE, bps = rate * 2;
    uint8_t h[44] = {'R', 'I', 'F', 'F', 0, 0, 0, 0, 'W', 'A', 'V', 'E', 'f', 'm', 't', ' ', 16, 0, 0, 0, 1, 0, 1, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 16, 0, 'd', 'a', 't', 'a'};
    memcpy(h + 4, &riff, 4), memcpy(h + 24, &rate, 4), memcpy(h + 28, &bps, 4), memcpy(h + 40, &data, 4);
    return fseek(w, 0, SEEK_SET) || fwrite(h, 1, 44, w) != 44;
}

static uint8_t *read_file(const char *path, size_t *size) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *data = n > 0 ? malloc((size_t)n) : NULL;
    if (data && fread(data, 1, (size_t)n, f) != (size_t)n) free(data), data = NULL;
    fclose(f);
    *size = (size_t)n;
    return data;
}

static Cps1 machine;

int main(int argc, char **argv) {
    const char *path = NULL, *ppm = NULL, *wav = NULL, *state_in = NULL, *state_out = NULL;
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
        else if (argv[i][0] != '-') path = argv[i];
        else return fprintf(stderr, "unknown option %s\n", argv[i]), 2;
    }
    if (!path) return fprintf(stderr, "usage: cps1_headless GAME.zip [--frames N] [--play] [--ppm FILE] [--wav FILE]"
                                 " [--state-at N FILE] [--load-state FILE]\n"), 2;
    size_t size;
    uint8_t *data = read_file(path, &size);
    if (!data) return fprintf(stderr, "%s: cannot read\n", path), 1;
    Cps1Rom rom;
    char err[512];
    if (cps1_open(path, data, size, &rom, err, sizeof err)) return fprintf(stderr, "%s\n", err), 1;
    free(data);
    const Cps1Game *g = rom.game;

    cps1_init(&machine, &rom);
    if (state_in && cps1_state_load(&machine, state_in, err, sizeof err)) return fprintf(stderr, "%s\n", err), 2;
    FILE *w = wav ? fopen(wav, "wb") : NULL;
    if (wav && (!w || fseek(w, 44, SEEK_SET))) return perror(wav), 2;
    long samples = 0;
    static int16_t buf[CPS1_SND_BUF];
    for (long f = 0; f < frames; f++) {
        cps1_set_input(&machine, 0, play ? scripted((long)machine.frames) : 0);
        cps1_frame(&machine);
        int n = cps1_take_sound(&machine, buf, CPS1_SND_BUF);
        if (w && fwrite(buf, sizeof *buf, (size_t)n, w) != (size_t)n) return perror(wav), 2;
        samples += n;
        if (state_out && (long)machine.frames == state_at && cps1_state_save(&machine, state_out)) return perror(state_out), 2;
    }
    if (w && (write_wav(w, samples) || fclose(w))) return perror(wav), 2;

    static uint8_t seen[0xC00];
    int colours = 0;
    for (int i = 0; i < CPS1_WIDTH * CPS1_HEIGHT; i++) {
        uint16_t c = machine.frame[i] % 0xC00;
        if (!seen[c]) seen[c] = 1, colours++;
    }
    if (ppm) {
        FILE *f = fopen(ppm, "wb");
        if (!f) return perror(ppm), 1;
        static uint32_t rgb[CPS1_WIDTH * CPS1_HEIGHT];
        int w, h;
        cps1_picture(&machine, rgb, &w, &h);  /* turned for a vertical monitor */
        fprintf(f, "P6\n%d %d\n255\n", w, h);
        for (int i = 0; i < CPS1_WIDTH * CPS1_HEIGHT; i++) {
            uint32_t c = rgb[i];
            uint8_t px[3] = {(uint8_t)(c >> 16), (uint8_t)(c >> 8), (uint8_t)c};
            fwrite(px, 1, 3, f);
        }
        fclose(f);
    }
    printf("game=%s frames=%ld colours=%d%s\n", g->id, frames, colours, machine.cpu.halted ? " halted" : "");
    cps1_unload(&rom);
    return machine.cpu.halted ? 1 : 0;
}
