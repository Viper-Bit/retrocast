#include "capture.h"

#include <string.h>

int capture_ppm(const char *path, const uint32_t *rgb, int w, int h, int stride) {
    FILE *f = fopen(path, "wb");
    if (!f) return -1;
    fprintf(f, "P6\n%d %d\n255\n", w, h);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            uint32_t c = rgb[(size_t)y * (size_t)stride + (size_t)x];
            uint8_t px[3] = {(uint8_t)(c >> 16), (uint8_t)(c >> 8), (uint8_t)c};
            fwrite(px, 1, 3, f);
        }
    int failed = ferror(f);
    return fclose(f) || failed ? -1 : 0;
}

#define WAV_HEADER 44

FILE *capture_wav_open(const char *path) {
    FILE *f = fopen(path, "wb");
    static const uint8_t room[WAV_HEADER];
    if (f) fwrite(room, 1, sizeof room, f);  /* the header, once the size is known */
    return f;
}

void capture_wav_samples(FILE *f, const int16_t *s, size_t n) {
    for (size_t i = 0; i < n; i++) {
        uint8_t b[2] = {(uint8_t)s[i], (uint8_t)((uint16_t)s[i] >> 8)};
        fwrite(b, 1, 2, f);
    }
}

static void put32(uint8_t *p, uint32_t v) { p[0] = (uint8_t)v, p[1] = (uint8_t)(v >> 8), p[2] = (uint8_t)(v >> 16), p[3] = (uint8_t)(v >> 24); }

int capture_wav_close(FILE *f, unsigned rate, unsigned channels) {
    long end = ftell(f);
    uint32_t data = end > WAV_HEADER ? (uint32_t)(end - WAV_HEADER) : 0;
    uint8_t h[WAV_HEADER] = "RIFF....WAVEfmt ";
    put32(h + 4, 36 + data);
    put32(h + 16, 16);
    put32(h + 20, 1 | channels << 16);              /* PCM, channels */
    put32(h + 24, rate);
    put32(h + 28, rate * channels * 2);             /* bytes a second */
    put32(h + 32, channels * 2 | 16u << 16);        /* block align, 16 bits */
    memcpy(h + 36, "data", 4);
    put32(h + 40, data);
    int failed = end < 0 || fseek(f, 0, SEEK_SET) || fwrite(h, 1, sizeof h, f) != sizeof h || ferror(f);
    return fclose(f) || failed ? -1 : 0;
}
