#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "atari.h"
#include "loader.h"
#include "palette.h"
#include "system.h"

#ifndef APP_NAME
#define APP_NAME "atari2600"
#endif

static const char SETTINGS[] = "# region: auto, ntsc, or pal\nregion = auto\n# mapper: auto, 2k, 4k, f8, f6, f4, f8sc, f6sc, f4sc, fa, e0, e7, or 3f\nmapper = auto\n";
static int region = -1;
static A26CartType mapper = A26_CART_AUTO;
static Atari2600 machine;
static uint8_t *rom;
static size_t rom_size;
static int selected_pal;

static int sys_setting(const char *key, const char *value) {
    if (!strcmp(key, "region")) {
        if (!strcmp(value, "auto")) region = -1;
        else if (!strcmp(value, "ntsc")) region = 0;
        else if (!strcmp(value, "pal")) region = 1;
        else return 0;
        return 1;
    }
    if (!strcmp(key, "mapper")) {
        static const char *const names[] = {"auto", "2k", "4k", "f8", "f6", "f4", "f8sc", "f6sc", "f4sc", "fa", "e0", "e7", "3f"};
        for (unsigned i = 0; i < sizeof names / sizeof names[0]; i++) {
            if (!strcmp(value, names[i])) { mapper = (A26CartType)i; return 1; }
        }
    }
    return 0;
}

static int sys_open(const char *path, const Settings *settings, SysInfo *info, char *err, size_t errlen) {
    (void)settings;
    int embedded = !path && a26_recomp_program && a26_recomp_program->rom;
    if (!path && !embedded) { snprintf(err, errlen, "usage: atari2600 ROM [--frames N]"); return 1; }
    if (embedded) {
        path = a26_recomp_program->rom_name;
        rom_size = a26_recomp_program->rom_size;
        rom = malloc(rom_size);
        if (!rom) { snprintf(err, errlen, "out of memory"); return 1; }
        memcpy(rom, a26_recomp_program->rom, rom_size);
    } else if (a26_load_rom(path, &rom, &rom_size, err, errlen)) return 1;
    selected_pal = region < 0 ? (a26_recomp_program ? a26_recomp_program->pal :
        (strstr(path, "(Europe)") != NULL || strstr(path, "(PAL)") != NULL)) : region;
    if (mapper == A26_CART_AUTO && a26_recomp_program) mapper = (A26CartType)a26_recomp_program->mapper;
    if (a26_init(&machine, rom, rom_size, mapper, selected_pal)) {
        snprintf(err, errlen, "unsupported ROM size for selected mapper");
        free(rom); rom = NULL; return 1;
    }
    if (a26_recomp_program && !machine.program) {
        snprintf(err, errlen, "ROM or hardware configuration does not match compiled code");
        free(rom); rom = NULL; return 1;
    }
    const char *name = path;
    for (const char *p = path; *p; p++) if (*p == '/' || *p == '\\') name = p + 1;
    snprintf(info->name, sizeof info->name, "%s", name);
    snprintf(info->tag, sizeof info->tag, "%s", selected_pal ? "PAL" : "NTSC");
    if (embedded) snprintf(info->state_path, sizeof info->state_path, "%s%s.state", SDL_GetBasePath(), name);
    else snprintf(info->state_path, sizeof info->state_path, "%s.state", path);
    info->width = info->cols = A26_WIDTH;
    info->height = info->lines = selected_pal ? 228 : 192;
    info->fps = selected_pal ? 50.0 : 60.0;
    info->aspect = 1.2;
    info->sample_rate = 44100;
    info->channels = 1;
    return 0;
}

static void sys_reset(void) { (void)a26_init(&machine, rom, rom_size, mapper, selected_pal); }

static int sys_frame(const InputFrame *input, uint32_t *rgb, float *samples, int max) {
    a26_frame(&machine, input);
    unsigned top = selected_pal ? 45 : 37;
    unsigned lines = selected_pal ? 228 : 192;
    for (unsigned i = 0; i < A26_WIDTH * lines; i++) {
        uint8_t pixel = machine.tia.frame[top * A26_WIDTH + i];
        rgb[i] = (pixel & 1) ? 0 : a26_palette_color(pixel, selected_pal);
    }
    return a26_tia_samples(&machine.tia, samples, max);
}

static const char *sys_halted(char *buf, size_t len) {
    if (!machine.bus.cpu.jammed) return NULL;
    snprintf(buf, len, "CPU halted at $%04X", machine.bus.cpu.pc);
    return buf;
}
static int sys_state_save(const char *path) { return a26_save(&machine, path); }
static int sys_state_load(const char *path, char *err, size_t len) {
    if (!a26_load(&machine, path)) return 0;
    snprintf(err, len, "Could not load Atari 2600 state"); return -1;
}
static const char *sys_key(int key, char *buf, size_t len) { (void)key; (void)buf; (void)len; return NULL; }
static void sys_close(void) { free(rom); rom = NULL; }

extern const SystemDetector a26_detector;
const System atari2600_system = {&a26_detector, APP_NAME, SETTINGS, sys_setting, sys_open, sys_reset, sys_frame,
    sys_halted, sys_state_save, sys_state_load, sys_key, sys_close};
