/* The CPS-1 behind core/frontend/system.h: a game's zip matched to the game
 * table and loaded, both players' controls (buttons 1-3 = B, A, X; Start;
 * a coin on Select), the 384x224 picture on a 4:3 monitor, mono sound
 * (stereo on the Q-Sound board), save states, the EEPROM of the Q-Sound
 * board and Pang! 3 in GAME.eeprom next to the zip (MAME's nvram layout). No settings yet
 * (the DIP switches keep their defaults). */
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
static char misses_path[1024];  /* a recompiled game's NAME.misses, next to the program */
static char eeprom_path[1024];  /* GAME.eeprom, or "": the board has none */

static int sys_setting(const char *key, const char *value) { (void)key, (void)value; return 0; }

static int sys_open(const char *path, const Settings *settings, SysInfo *info, char *err, size_t errlen) {
    (void)settings;
    if (!path && cps1_recomp_program)  /* a recompiled game: its zip is not built in (the graphics are megabytes) */
        return snprintf(err, errlen, "%s is recompiled; open its zip: drop %s.zip on the program, or give it as an argument",
                        cps1_recomp_program->game_id, cps1_recomp_program->game_id), 2;
    if (!path) return snprintf(err, errlen, "usage: retrocast game.zip"), 2;
    size_t size = 0;
    uint8_t *data = SDL_LoadFile(path, &size);
    if (!data) return snprintf(err, errlen, "%s: %s", path, SDL_GetError()), 1;
    int bad = cps1_open(path, data, size, &rom, err, errlen);
    SDL_free(data);
    if (bad) return 1;
    const Cps1Game *g = rom.game;
    loaded = 1;
    cps1_init(&machine, &rom);
#ifdef APP_NAME
    SDL_snprintf(misses_path, sizeof misses_path, "%s%s.misses", SDL_GetBasePath(), APP_NAME);
#endif
    if (machine.recomp_on && settings->record_misses) machine.misses = SDL_calloc(rom.size[CPS1_R_MAIN] / 2 + 1, 1);
    snprintf(info->name, sizeof info->name, "%s", g->title);
    snprintf(info->tag, sizeof info->tag, "%s", g->id);
    size_t n = strlen(path);
    int ext = n > 4 && !SDL_strcasecmp(path + n - 4, ".zip") ? 4 : 0;
    snprintf(info->state_path, sizeof info->state_path, "%.*s.state", (int)(n - (size_t)ext), path);
    eeprom_path[0] = 0;
    if (cps1_has_eeprom(g)) {  /* the settings the game keeps: read back if saved */
        snprintf(eeprom_path, sizeof eeprom_path, "%.*s.eeprom", (int)(n - (size_t)ext), path);
        size_t got = 0;
        void *saved = SDL_LoadFile(eeprom_path, &got);
        if (saved && got == sizeof machine.eeprom.data) memcpy(machine.eeprom.data, saved, got);
        SDL_free(saved);
    }
    int turned = g->rotate == 270;  /* a vertical monitor */
    info->width = info->cols = turned ? CPS1_HEIGHT : CPS1_WIDTH;
    info->height = info->lines = turned ? CPS1_WIDTH : CPS1_HEIGHT;
    info->fps = 8000000.0 / 512 / CPS1_LINES;  /* 59.64 */
    info->aspect = turned ? (3.0 / 4) / ((double)CPS1_HEIGHT / CPS1_WIDTH)  /* the picture fills a 4:3 monitor */
                          : (4.0 / 3) / ((double)CPS1_WIDTH / CPS1_HEIGHT);
    info->sample_rate = cps1_sample_rate(g);
    info->channels = cps1_channels(g);
    return 0;
}

static void sys_reset(void) {
    static uint8_t eeprom[sizeof machine.eeprom.data];
    uint8_t *misses = machine.misses;  /* the session's, kept */
    memcpy(eeprom, machine.eeprom.data, sizeof eeprom);  /* not erased by a reset */
    cps1_init(&machine, &rom);
    machine.misses = misses;
    if (*eeprom_path) memcpy(machine.eeprom.data, eeprom, sizeof eeprom);
}

/* NAME.misses: the file's lines and this session's; rewritten only when the
 * session found new code, so the next build does not recompile for nothing. */
static void save_misses(void) {
    uint32_t n = rom.size[CPS1_R_MAIN] / 2, fresh = 0;
    for (uint32_t i = 0; i < n; i++) fresh += machine.misses[i];
    FILE *f = fopen(misses_path, "r");
    char line[64];
    unsigned pc;
    while (f && fgets(line, sizeof line, f)) {
        if (sscanf(line, "MISS $%x", &pc) != 1 || pc / 2 >= n) continue;
        if (machine.misses[pc / 2] == 1) fresh--;  /* known already */
        machine.misses[pc / 2] = 2;
    }
    if (f) fclose(f);
    if (!fresh) return;
    if (!(f = fopen(misses_path, "w"))) { SDL_Log("%s: cannot write", misses_path); return; }
    for (uint32_t i = 0; i < n; i++)
        if (machine.misses[i]) fprintf(f, "MISS $%06X\n", (unsigned)i * 2);
    fclose(f);
}

static int sys_frame(const InputFrame *in, uint32_t *rgb, float *samples, int max) {
    static int16_t snd[CPS1_SND_BUF];
    cps1_set_input(&machine, 0, in->pad[0]);
    cps1_set_input(&machine, 1, in->pad[1]);
    cps1_frame(&machine);
    int w, h;
    cps1_picture(&machine, rgb, &w, &h);
    int ch = cps1_channels(rom.game), n = cps1_take_sound(&machine, snd, max * ch < CPS1_SND_BUF ? max * ch : CPS1_SND_BUF);
    for (int i = 0; i < n; i++) samples[i] = snd[i] / 32768.0f;
    return n / ch;  /* sample frames */
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
    if (loaded && *eeprom_path && !SDL_SaveFile(eeprom_path, machine.eeprom.data, sizeof machine.eeprom.data))
        SDL_Log("%s: %s", eeprom_path, SDL_GetError());
    if (machine.misses && *misses_path) save_misses();
    SDL_free(machine.misses);
    machine.misses = NULL;
    if (loaded) cps1_unload(&rom), loaded = 0;
}

extern const SystemDetector cps1_detector;
const System cps1_system = {&cps1_detector, "cps1", SETTINGS, sys_setting, sys_open, sys_reset, sys_frame,
                            sys_halted, sys_state_save, sys_state_load, sys_key, sys_close};
