/* CPS-2 adapter for the shared SDL frontend. */
#include "machine.h"
#include "system.h"

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Cps2Machine machine;
static Cps2Rom rom;
static char *folder;
static char eeprom_path[1024];
static int rotation, players, six_buttons;
static uint64_t frame_clock;
static float *audio;
static int audio_frames, audio_capacity;

static int start_machine(void)
{
    frame_clock = 0;
    if (cps2_machine_init(&machine, &rom))
        return -1;
    if (cps2_sound_open(&machine, &rom, folder)) {
        cps2_machine_destroy(&machine);
        return -1;
    }
    return 0;
}

static void close_game(void)
{
    if (folder && *eeprom_path &&
        !SDL_SaveFile(eeprom_path, machine.eeprom.data, sizeof(machine.eeprom.data)))
        SDL_Log("%s: %s", eeprom_path, SDL_GetError());
    cps2_machine_destroy(&machine);
    cps2_unload(&rom);
    free(folder);
    folder = NULL;
    eeprom_path[0] = 0;
}

static int open_game(const char *path, const Settings *settings, SysInfo *info,
                     char *error, size_t error_size)
{
    (void)settings;
    if (!path)
        return snprintf(error, error_size, "usage: retrocast SET.zip"), 2;
    const char *base = path;
    for (const char *p = path; *p; ++p)
        if (*p == '/' || *p == '\\')
            base = p + 1;
    size_t length = strlen(base);
    char id[32];
    if (length <= 4 || length - 4 >= sizeof(id) || SDL_strcasecmp(base + length - 4, ".zip"))
        return snprintf(error, error_size, "Expected a named CPS-2 MAME set ZIP"), 1;
    memcpy(id, base, length - 4);
    id[length - 4] = 0;
    const Cps2Game *game = cps2_find_game(id);
    if (!game)
        return snprintf(error, error_size, "Unknown CPS-2 MAME set: %s", id), 1;

    size_t directory = (size_t)(base - path);
    folder = malloc(directory + 2);
    if (!folder)
        return snprintf(error, error_size, "out of memory"), 1;
    if (directory)
        memcpy(folder, path, directory);
    else
        folder[directory++] = '.';
    folder[directory] = 0;
    if (cps2_open(game, folder, &rom, error, error_size)) {
        close_game();
        return 1;
    }
    if (start_machine()) {
        close_game();
        return snprintf(error, error_size, "%s: could not initialize CPS-2. Check qsound.zip.", id), 1;
    }

    snprintf(eeprom_path, sizeof(eeprom_path), "%s/%s.eeprom", folder, id);
    size_t size = 0;
    void *saved = SDL_LoadFile(eeprom_path, &size);
    if (saved && size == sizeof(machine.eeprom.data))
        memcpy(machine.eeprom.data, saved, size);
    SDL_free(saved);
    rotation = !strcmp(game->rotation, "ROT270") ? 270 : !strcmp(game->rotation, "ROT90") ? 90 : 0;
    players = strstr(game->inputs, "4p") || strstr(game->inputs, "3p") ? 4 : 2;
    six_buttons = strstr(game->inputs, "6b") != NULL;
    info->width = info->cols = rotation ? 224 : 384;
    info->height = info->lines = rotation ? 384 : 224;
    info->fps = 8000000.0 / (512 * 262);
    info->aspect = (rotation ? 0.75 : 4.0 / 3) * info->height / info->width;
    info->sample_rate = (QSOUND_CLOCK + QSOUND_CLOCKS_PER_SAMPLE / 2) / QSOUND_CLOCKS_PER_SAMPLE;
    info->channels = 2;
    info->players = players;
    snprintf(info->name, sizeof(info->name), "%s", game->title);
    snprintf(info->tag, sizeof(info->tag), "%.15s", id);
    return 0;
}

static void reset(void)
{
    uint8_t eeprom[sizeof(machine.eeprom.data)];
    memcpy(eeprom, machine.eeprom.data, sizeof(eeprom));
    cps2_machine_destroy(&machine);
    if (start_machine())
        machine.cpu.halted = 1;
    memcpy(machine.eeprom.data, eeprom, sizeof(eeprom));
}

static void sample(void *context, const int16_t stereo[2])
{
    (void)context;
    if (audio_frames < audio_capacity) {
        audio[audio_frames * 2] = stereo[0] / 32768.0f;
        audio[audio_frames * 2 + 1] = stereo[1] / 32768.0f;
        ++audio_frames;
    }
}

static uint16_t buttons(uint16_t pad)
{
    return (pad & PAD_RIGHT ? 1 : 0) | (pad & PAD_LEFT ? 2 : 0) |
           (pad & PAD_DOWN ? 4 : 0) | (pad & PAD_UP ? 8 : 0) |
           (pad & PAD_B ? 16 : 0) | (pad & PAD_A ? 32 : 0) |
           (pad & PAD_X ? 64 : 0) | (!six_buttons && (pad & PAD_Y) ? 128 : 0);
}

static int frame(const InputFrame *input, uint32_t *rgb, float *samples, int max)
{
    machine.inputs[0] = machine.inputs[1] = machine.inputs[2] = 0xffff;
    for (int p = 0; p < players; ++p) {
        uint16_t pad = input->pad[p];
        machine.inputs[p / 2] &= (uint16_t)~(buttons(pad) << ((p & 1) * 8));
        if (pad & PAD_START) machine.inputs[2] &= (uint16_t)~(0x100 << p);
        if (pad & PAD_SELECT) machine.inputs[2] &= (uint16_t)~(0x1000 << p);
        if (six_buttons && p < 2) {
            if (pad & PAD_Y) machine.inputs[1] &= (uint16_t)~(1 << (p * 4));
            if (pad & PAD_L) machine.inputs[1] &= (uint16_t)~(2 << (p * 4));
            if (pad & PAD_R) machine.inputs[p ? 2 : 1] &= (uint16_t)~(p ? 0x4000 : 4);
        }
    }
    audio = samples;
    audio_frames = 0;
    audio_capacity = max;
    machine.audio_sample = sample;
    frame_clock += 262 * 1024;
    cps2_machine_run(&machine, frame_clock);
    if (!rotation)
        memcpy(rgb, machine.frame, sizeof(machine.frame));
    else
        for (int y = 0; y < 224; ++y)
            for (int x = 0; x < 384; ++x) {
                int at = rotation == 90 ? x * 224 + 223 - y : (383 - x) * 224 + y;
                rgb[at] = machine.frame[y * 384 + x];
            }
    return audio_frames;
}

static const char *halted(char *text, size_t size)
{
    if (!machine.cpu.halted)
        return NULL;
    snprintf(text, size, "CPS-2 68000 halted at $%06x", (unsigned)machine.cpu.pc);
    return text;
}

static int setting(const char *key, const char *value) { (void)key; (void)value; return 0; }
static int save(const char *path) { (void)path; return -1; }
static int load(const char *path, char *error, size_t size)
{
    (void)path;
    snprintf(error, size, "CPS-2 save states are unavailable");
    return -1;
}
static const char *key(int code, char *text, size_t size)
{ (void)code; (void)text; (void)size; return NULL; }

extern const SystemDetector cps2_detector;
const System cps2_system = {&cps2_detector, "cps2", "", setting, open_game, reset, frame,
                            halted, save, load, key, close_game};
