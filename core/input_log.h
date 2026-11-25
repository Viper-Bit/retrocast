/* Input recordings, for replays and regression tests.
 * File, version 2: "RCIN", version byte 2, the system (4 bytes, zero
 * padded: "nes", "gb"), then 5 bytes per frame: pad 1 buttons, pad 2
 * buttons (16 bits each, little endian), flags (bit 0: reset before this
 * frame). Version 3 ("RCIN", 3; four-player games): the same with four
 * pads, 9 bytes per frame. Version 1 ("NESI", 1; NES only) had 1 byte per
 * pad; all three load.
 * Emulation is deterministic from power-on, so a recording replays exactly. */
#ifndef CORE_INPUT_LOG_H
#define CORE_INPUT_LOG_H

#include <stdint.h>
#include <stdio.h>

/* Buttons as the frontend reports them, the same for every system; each
 * system reads the ones its pad has. The low byte is the NES controller's
 * shift-register order (and was all of a version 1 recording); X, Y, L and
 * R are the SNES-style rest (gamepad north, west, shoulders). Bits 12-15
 * are free for pads with more buttons. */
enum {
    PAD_A = 0x01, PAD_B = 0x02, PAD_SELECT = 0x04, PAD_START = 0x08,
    PAD_UP = 0x10, PAD_DOWN = 0x20, PAD_LEFT = 0x40, PAD_RIGHT = 0x80,
    PAD_X = 0x100, PAD_Y = 0x200, PAD_L = 0x400, PAD_R = 0x800
};
enum { INPUT_RESET = 0x01 };

typedef struct { uint16_t pad[4]; uint8_t flags; } InputFrame;  /* players 1-4 */

typedef struct {
    InputFrame *frames;
    long count;
    char system[5];  /* who recorded it ("nes" for version 1) */
} InputLog;

/* pads: 2 (version 2) or 4 (version 3); input_log_write takes the same. */
FILE *input_log_create(const char *path, const char *system, int pads);  /* writes the header; NULL on error */
void input_log_write(FILE *f, InputFrame fr, int pads);
int input_log_load(const char *path, InputLog *log);  /* 0 ok, -1 error */
void input_log_free(InputLog *log);

/* Real pads cannot press left+right or up+down; keyboards and sticks can,
 * and some games misbehave. Drop both directions of such a pair. */
uint16_t input_clean(uint16_t buttons);

#endif
