/* The CPS-1 behind core/frontend/system.h: a game's zip matched to the game
 * table and loaded, both players' controls (buttons 1-3 = B, A, X; Start;
 * a coin on Select), the 384x224 picture on a 4:3 monitor, mono sound,
 * save states. No battery RAM and no settings yet (the DIP switches keep
 * their defaults). */
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cps1.h"
#include "system.h"

static const char SETTINGS[] = "";
static Cps1 machine;
static Cps1Rom rom;
static int loaded;

static int sys_setting(const char *key, const char *value) { (void)key, (void)value; return 0; }

static int sys_open(const char *path, const Settings *settings, SysInfo *info, char *err, size_t errlen) {
    (void)settings;
    if (!path) return snprintf(err, errlen, "usage: retrocast game.zip"), 2;  /* recompiled CPS-1 games: later */
    size_t size = 0;
    uint8_t *data = SDL_LoadFile(path, &size);
    if (!data) return snprintf(err, errlen, "%s: %s", path, SDL_GetError()), 1;
    int bad = cps1_open(path, data, size, &rom, err, errlen);
    SDL_free(data);
    if (bad) return 1;
    const Cps1Game *g = rom.game;
    loaded = 1;
    cps1_init(&machine, &rom);
    snprintf(info->name, sizeof info->name, "%s", g->title);
    snprintf(info->tag, sizeof info->tag, "%s", g->id);
    size_t n = strlen(path);
    int ext = n > 4 && !SDL_strcasecmp(path + n - 4, ".zip") ? 4 : 0;
    snprintf(info->state_path, sizeof info->state_path, "%.*s.state", (int)(n - (size_t)ext), path);
    info->width = info->cols = CPS1_WIDTH;
    info->height = info->lines = CPS1_HEIGHT;
    info->fps = 8000000.0 / 512 / CPS1_LINES;  /* 59.64 */
    info->aspect = (4.0 / 3) / ((double)CPS1_WIDTH / CPS1_HEIGHT);  /* the picture fills a 4:3 monitor */
    info->sample_rate = CPS1_SAMPLE_RATE;
    info->channels = 1;
    return 0;
}

static void sys_reset(void) { cps1_init(&machine, &rom); }

static int sys_frame(const InputFrame *in, uint32_t *rgb, float *samples, int max) {
    static int16_t snd[CPS1_SND_BUF];
    cps1_set_input(&machine, 0, in->pad[0]);
    cps1_set_input(&machine, 1, in->pad[1]);
    cps1_frame(&machine);
    for (int i = 0; i < CPS1_WIDTH * CPS1_HEIGHT; i++) rgb[i] = cps1_color(&machine, machine.frame[i]);
    int n = cps1_take_sound(&machine, snd, max < CPS1_SND_BUF ? max : CPS1_SND_BUF);
    for (int i = 0; i < n; i++) samples[i] = snd[i] / 32768.0f;
    return n;
}

static const char *sys_halted(char *buf, size_t len) {
    if (!machine.cpu.halted) return NULL;
    snprintf(buf, len, "the 68000 stopped (a double bus fault)\nat $%06X", (unsigned)machine.cpu.pc);
    return buf;
}
static int sys_state_save(const char *path) { return cps1_state_save(&machine, path); }
static int sys_state_load(const char *path, char *err, size_t len) { return cps1_state_load(&machine, path, err, len) ? -1 : 0; }
static const char *sys_key(int key, char *buf, size_t len) { (void)key, (void)buf, (void)len; return NULL; }
static void sys_close(void) {
    if (loaded) cps1_unload(&rom), loaded = 0;
}

extern const SystemDetector cps1_detector;
const System cps1_system = {&cps1_detector, "cps1", SETTINGS, sys_setting, sys_open, sys_reset, sys_frame,
                            sys_halted, sys_state_save, sys_state_load, sys_key, sys_close};
