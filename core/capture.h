/* A picture or sound written to a file, for the headless programs and tests:
 * a binary PPM of 0x00RRGGBB pixels, and a 16-bit PCM WAV whose header is
 * written when it is closed (so the sound can be streamed into it). */
#ifndef CORE_CAPTURE_H
#define CORE_CAPTURE_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* w x h pixels, a row every `stride` pixels; 0, or -1 (errno set) when the
 * file cannot be written. */
int capture_ppm(const char *path, const uint32_t *rgb, int w, int h, int stride);

FILE *capture_wav_open(const char *path);  /* NULL when it cannot be created */
void capture_wav_samples(FILE *f, const int16_t *s, size_t n);  /* n samples, channels interleaved */
int capture_wav_close(FILE *f, unsigned rate, unsigned channels);  /* 0, or -1 */

#endif
