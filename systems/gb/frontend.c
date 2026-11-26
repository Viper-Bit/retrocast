/* The Game Boy for the SDL3 frontend (core/frontend/system.h): loading,
 * battery saves (ROM.sav: the cartridge RAM, then for MBC3 the clock and
 * when it was saved, so it moves on while the program is closed), the
 * screen's palette, the sound. A recompiled game (gb_recompile) plays its
 * embedded ROM when started without one. */
#include <SDL3/SDL.h>
#include <string.h>
#include <time.h>

#include "gb.h"
#include "recomp_rt.h"
#include "system.h"

#ifndef APP_NAME
#define APP_NAME "gb"
#endif

static const char SETTINGS[] =
    "# palette: the four shades: green = the original screen's tint, gray = neutral grays\n"
    "palette = green\n"
    "# model: dmg, cgb, cgb-e or auto (cgb and cgb-e colourise original Game Boy games)\n"
    "# (the game's header decides)\n"
    "model = auto\n";

static int gray, model = GB_MODEL_AUTO;

static int sys_setting(const char *key, const char *val) {
    if (!strcmp(key, "model")) {
        if (!strcmp(val, "auto")) return model = GB_MODEL_AUTO, 1;
        if (!strcmp(val, "dmg")) return model = GB_MODEL_DMG, 1;
        if (!strcmp(val, "cgb")) return model = GB_MODEL_CGB, 1;
        if (!strcmp(val, "cgb-e")) return model = GB_MODEL_CGB_E, 1;
        return 0;
    }
    if (strcmp(key, "palette")) return 0;
    if (!strcmp(val, "green")) return gray = 0, 1;
    if (!strcmp(val, "gray")) return gray = 1, 1;
    return 0;
}

static Gb gb;
static uint8_t *rom;
static size_t rom_size;
static char sav_path[1024], misses_path[1024];
enum { RTC_BYTES = 5 + 5 + 8 };  /* the clock, as latched, the time of saving (seconds, little endian) */

static void load_sav(void) {
    size_t size;
    uint8_t *d = SDL_LoadFile(sav_path, &size);
    GbCart *c = &gb.cart;
    if (d && (size == c->ram_size || (c->has_rtc && size == c->ram_size + RTC_BYTES))) {
        memcpy(c->ram, d, c->ram_size);
        if (size > c->ram_size) {
            const uint8_t *r = d + c->ram_size;
            memcpy(c->rtc, r, 5);
            memcpy(c->rtc_latched, r + 5, 5);
            uint64_t then = 0;
            for (int i = 7; i >= 0; i--) then = then << 8 | r[10 + i];
            uint64_t now = (uint64_t)time(NULL);
            if (now > then) gb_cart_rtc_advance(c, now - then);
        }
    }
    SDL_free(d);
}

static void save_sav(void) {
    GbCart *c = &gb.cart;
    if (!c->battery || !c->ram_size) return;
    uint8_t d[sizeof c->ram + RTC_BYTES];
    size_t n = c->ram_size;
    memcpy(d, c->ram, n);
    if (c->has_rtc) {
        memcpy(d + n, c->rtc, 5);
        memcpy(d + n + 5, c->rtc_latched, 5);
        uint64_t now = (uint64_t)time(NULL);
        for (int i = 0; i < 8; i++) d[n + 10 + i] = (uint8_t)(now >> (8 * i));
        n += RTC_BYTES;
    }
    if (!SDL_SaveFile(sav_path, d, n)) SDL_Log("%s: %s", sav_path, SDL_GetError());
}

static int sys_open(const char *path, const Settings *settings, SysInfo *info, char *err, size_t errlen) {
    const int embedded = !path && gb_recomp_program && gb_recomp_program->rom;
    if (!path && !embedded) return SDL_snprintf(err, errlen, "usage: %s ROM [--frames N] [--record FILE] [--replay FILE]", APP_NAME), 2;
    if (embedded) {  /* saves and states: the ROM's file name next to the program */
        rom_size = gb_recomp_program->rom_size;
        rom = SDL_malloc(rom_size);
        if (!rom) return SDL_snprintf(err, errlen, "out of memory"), 1;
        SDL_memcpy(rom, gb_recomp_program->rom, rom_size);
        SDL_snprintf(sav_path, sizeof sav_path, "%s%s", SDL_GetBasePath(), gb_recomp_program->rom_name);
        path = gb_recomp_program->rom_name;
    } else {
        rom = SDL_LoadFile(path, &rom_size);
        if (!rom) return SDL_snprintf(err, errlen, "%s: %s", path, SDL_GetError()), 1;
        SDL_strlcpy(sav_path, path, sizeof sav_path);
    }
    char msg[128];
    if (gb_load_model(&gb, rom, rom_size, model, msg, sizeof msg) != 0) return SDL_snprintf(err, errlen, "%s: %s", path, msg), 1;
    SDL_snprintf(info->state_path, sizeof info->state_path, "%s.state", sav_path);
    SDL_strlcat(sav_path, ".sav", sizeof sav_path);
    if (gb.cart.battery) load_sav();
    /* recompiled game: note the ROM code interpreted, in <program>.misses (read by the next build) */
    SDL_snprintf(misses_path, sizeof misses_path, "%s%s.misses", SDL_GetBasePath(), APP_NAME);
    if (gb.recomp_on && settings->record_misses) gb.misses = SDL_calloc(gb_miss_slots(&gb), 1);
    const char *name = path;  /* the settings' palette is for DMG games on a DMG; CGB games bring their own colours */
    for (const char *p = path; *p; p++)
        if (*p == '/' || *p == '\\') name = p + 1;
    SDL_strlcpy(info->name, name, sizeof info->name);
    SDL_strlcpy(info->tag, gb.cgb ? "Game Boy Color" : "Game Boy", sizeof info->tag);
    info->width = info->cols = 160;
    info->height = info->lines = 144;
    info->fps = 4194304.0 / 70224;  /* 59.73 Hz */
    info->aspect = 1.0;
    info->sample_rate = GB_SAMPLE_RATE;
    info->channels = 2;  /* NR51 pans each channel left, right or both */
    return 0;
}

/* The power button: the same game, its cartridge RAM and clock kept. */
static void sys_reset(void) {
    static GbCart keep;
    keep = gb.cart;
    uint8_t *misses = gb.misses;  /* gb_load clears the Gb */
    gb_free(&gb);
    char err[128];
    int bad = gb_load_model(&gb, rom, rom_size, model, err, sizeof err);
    gb.misses = misses;
    if (bad) return;
    memcpy(gb.cart.ram, keep.ram, sizeof keep.ram);
    memcpy(gb.cart.rtc, keep.rtc, sizeof keep.rtc);
}

static int sys_frame(const InputFrame *in, uint32_t *rgb, float *samples, int max) {
    static const uint32_t GREEN[4] = {0xE0F8D0, 0x88C070, 0x346856, 0x081820};
    static const uint32_t GRAY[4] = {0xFFFFFF, 0xAAAAAA, 0x555555, 0x000000};
    const uint32_t *pal = gray ? GRAY : GREEN;
    gb_set_pad(&gb, (uint8_t)in->pad[0]);  /* the Game Boy's buttons: the low byte */
    gb_run_frame(&gb);
    if (gb.cgb)  /* RGB555; 5 bits to 8 as (c << 3) | (c >> 2) */
        for (int i = 0; i < 160 * 144; i++) {
            uint32_t c = gb.frame[i], r = c & 31, gr = c >> 5 & 31, b = c >> 10 & 31;
            rgb[i] = (r << 3 | r >> 2) << 16 | (gr << 3 | gr >> 2) << 8 | (b << 3 | b >> 2);
        }
    else
        for (int i = 0; i < 160 * 144; i++) rgb[i] = pal[gb.frame[i] & 3];
    return gb_apu_take_samples(&gb, samples, max);
}

static const char *sys_halted(char *buf, size_t len) {
    if (!gb.cpu.jammed) return NULL;
    SDL_snprintf(buf, len, "CPU locked up at $%04X\nF5 reset, F4 load state", (uint16_t)(gb.cpu.pc - 1));
    return buf;
}

static int sys_state_save(const char *path) { return gb_state_save(&gb, path); }
static int sys_state_load(const char *path, char *err, size_t errlen) { return gb_state_load(&gb, path, err, errlen); }
static const char *sys_key(int key, char *buf, size_t len) { (void)key, (void)buf, (void)len; return NULL; }

static void sys_close(void) {
    save_sav();
    /* rewrite the misses file only when this session found new ROM code, so
     * the next build does not rerun the recompiler for nothing */
    if (gb.misses && gb_misses_merge(&gb, misses_path) != 0) {
        FILE *f = fopen(misses_path, "w");
        if (f) gb_misses_write(&gb, f), fclose(f);
        else SDL_Log("%s: cannot write", misses_path);
    }
    SDL_free(gb.misses);
    gb_free(&gb);
    SDL_free(rom);
}

extern const SystemDetector gb_detector;
const System gb_system = {&gb_detector, APP_NAME, SETTINGS, sys_setting, sys_open, sys_reset, sys_frame,
    sys_halted, sys_state_save, sys_state_load, sys_key, sys_close};
