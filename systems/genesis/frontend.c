/* The Genesis / Mega Drive for the SDL3 frontend (core/frontend/system.h):
 * loading, battery saves (ROM.sav: the battery RAM as the header places
 * it), the pads, the picture, the sound (at the YM2612's own rate; SDL
 * resamples it). A recompiled game (genesis_recompile) plays its embedded
 * ROM when started without one, and notes the ROM code it had to interpret
 * in NAME.misses for the next build. */
#include <SDL3/SDL.h>
#include <string.h>

#include "m68k_misses.h"
#include "md.h"
#include "recomp_rt.h"
#include "system.h"

#ifndef APP_NAME
#define APP_NAME "genesis"
#endif

static const char SETTINGS[] =
    "# pad: 6 = the six-button pad (X, Y, Z, Mode on L, North, R, Select), 3 = the original three-button one\n"
    "# (for the few early games that misread a six-button pad)\n"
    "pad = 6\n";

static int six = 1;

static int sys_setting(const char *key, const char *val) {
    if (strcmp(key, "pad")) return 0;
    if (!strcmp(val, "6")) return six = 1, 1;
    if (!strcmp(val, "3")) return six = 0, 1;
    return 0;
}

static Md md;
static char sav_path[1024], misses_path[1024];

static void save_sav(void) {
    uint32_t size;
    uint8_t *battery = md_battery(&md, &size);
    if (battery && !SDL_SaveFile(sav_path, battery, size)) SDL_Log("%s: %s", sav_path, SDL_GetError());
}

static int sys_open(const char *path, const Settings *settings, SysInfo *info, char *err, size_t errlen) {
    const int embedded = !path && md_recomp_program && md_recomp_program->rom;
    if (!path && !embedded) return SDL_snprintf(err, errlen, "usage: %s ROM [--frames N] [--record FILE] [--replay FILE]", APP_NAME), 2;
    char msg[128], base[1024];
    int bad;
    if (embedded) {  /* saves and states: the ROM's file name next to the program */
        bad = md_load(&md, md_recomp_program->rom, md_recomp_program->rom_size, msg, sizeof msg);
        SDL_snprintf(base, sizeof base, "%s%s", SDL_GetBasePath(), md_recomp_program->rom_name);
        path = md_recomp_program->rom_name;
    } else {
        size_t size;
        uint8_t *rom = SDL_LoadFile(path, &size);
        if (!rom) return SDL_snprintf(err, errlen, "%s: %s", path, SDL_GetError()), 1;
        bad = md_load(&md, rom, size, msg, sizeof msg);
        SDL_free(rom);
        SDL_strlcpy(base, path, sizeof base);
    }
    if (bad) return SDL_snprintf(err, errlen, "%s: %s", path, msg), 1;
    md.pad6[0] = md.pad6[1] = (uint8_t)six;
    SDL_snprintf(sav_path, sizeof sav_path, "%s.sav", base);
    SDL_snprintf(info->state_path, sizeof info->state_path, "%s.state", base);
    SDL_snprintf(misses_path, sizeof misses_path, "%s%s.misses", SDL_GetBasePath(), APP_NAME);
    if (md.recomp_on && settings->record_misses) md.misses = SDL_calloc(md_code_end(&md) / 2 + 1, 1);
    size_t n;
    uint32_t size;
    uint8_t *battery = md_battery(&md, &size);
    uint8_t *sav = battery ? SDL_LoadFile(sav_path, &n) : NULL;
    if (sav && n == size) memcpy(battery, sav, n);
    SDL_free(sav);
    const char *name = path;
    for (const char *p = path; *p; p++)
        if (*p == '/' || *p == '\\') name = p + 1;
    SDL_strlcpy(info->name, name, sizeof info->name);
    SDL_strlcpy(info->tag, md.pal ? "Mega Drive, PAL" : "Genesis", sizeof info->tag);
    info->width = info->cols = 320;
    info->height = 240;
    info->lines = md.pal ? 240 : 224;  /* PAL shows V30's 240 lines; V28 games get a border */
    info->fps = md.pal ? 53203424.0 / (MD_LINE_CLOCKS * 313) : 53693175.0 / (MD_LINE_CLOCKS * 262);  /* 49.70, 59.92 */
    /* H40's pixels: 320 across the width H32 fills with 256 pixels of 8:7 (NTSC). shortcut: PAL's wider pixels are an estimate */
    info->aspect = md.pal ? 1.1 : 32.0 / 35.0;
    info->sample_rate = md_sample_rate(&md);
    info->channels = 2;
    return 0;
}

static void sys_reset(void) { md_reset(&md); }

static int sys_frame(const InputFrame *in, uint32_t *rgb, float *samples, int max) {
    md.pad[0] = in->pad[0], md.pad[1] = in->pad[1];
    md_run_frame(&md);
    const Vdp *v = &md.vdp;
    int top = (240 - v->frame_h) / 2;
    memset(rgb, 0, 320 * 240 * sizeof *rgb);
    for (int y = 0; y < v->frame_h; y++) {
        const uint32_t *src = v->frame + y * 320;
        uint32_t *dst = rgb + (top + y) * 320;
        /* H32 stretched to the width H40 fills, as on a TV. shortcut: nearest pixel, so every fourth is doubled */
        for (int x = 0; x < 320; x++) dst[x] = src[x * v->frame_w / 320];
    }
    return snd_take(&md.snd, samples, max);
}

static const char *sys_halted(char *buf, size_t len) {
    if (md.tmss_locked) SDL_snprintf(buf, len, "The game used the VDP before unlocking it (TMSS)\nF5 reset");
    else if (md.cpu.halted) SDL_snprintf(buf, len, "68000 halted (double fault) at $%06X\nF5 reset, F4 load state", md.cpu.pc & 0xFFFFFF);
    else return NULL;
    return buf;
}

static int sys_state_save(const char *path) { return md_state_save(&md, path); }
static int sys_state_load(const char *path, char *err, size_t errlen) { return md_state_load(&md, path, err, errlen); }
static const char *sys_key(int key, char *buf, size_t len) { (void)key, (void)buf, (void)len; return NULL; }


static void sys_close(void) {
    save_sav();
    if (md.misses && m68k_misses_save(misses_path, md.misses, md_code_end(&md) / 2)) SDL_Log("%s: cannot write", misses_path);
    SDL_free(md.misses);
    md.misses = NULL;
    md_free(&md);
}

extern const SystemDetector md_detector;
const System genesis_system = {&md_detector, APP_NAME, SETTINGS, sys_setting, sys_open, sys_reset, sys_frame,
    sys_halted, sys_state_save, sys_state_load, sys_key, sys_close};
