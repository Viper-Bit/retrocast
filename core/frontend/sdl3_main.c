/* SDL3 frontend: runs a game on one of the systems the program links
 * (system.h: retrocast every system built, a recompiled game its own one),
 * recompiled code where linked, else interpreted.
 * Usage: PROGRAM ROM [--system ID] [--frames N] [--record FILE] [--replay FILE]
 *   ROM may be left out in recompiled builds: the ROM they embed is used.
 *   --system ID  the system (nes, gb, md, a26) when the file's bytes do not
 *                tell it (core/detect.h)
 *   --frames N   quit after N frames (smoke tests)
 *   --record     save the input of every frame (core/input_log.h)
 *   --replay     play a recording back; live input resumes when it ends
 * Keyboard (player 1): arrows, X = A, Z = B, S = X, A = Y, Q = L, W = R,
 * Enter = Start, Right Shift = Select (each system reads the buttons its
 * pad has), F5 = reset, Esc = quit. F2 = save state, F4 = load state,
 * F10 = TV frame on/off, F11 or Alt+Enter = fullscreen on/off; other keys
 * go to the system (NES: F6 = next disk side).
 * Settings: <program>.ini next to the program (settings.c); in retrocast
 * one per system (nes.ini, gb.ini, genesis.ini, atari2600.ini).
 * Gamepads: in the order connected, players 1-4 (3 and 4 where the game
 * has them: SysInfo.players); hot-plug works.
 * D-pad or left stick; East = A, South = B (NES layout: B left of A),
 * North = X, West = Y, shoulders = L and R, Back = Select, Start = Start. */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "input_log.h"
#include "settings.h"
#include "system.h"
#include "tv_frame.h"

#ifndef APP_NAME
#define APP_NAME "retrocast"  /* CMake sets the program's name */
#endif

enum { MAX_W = 512, MAX_H = 480, MAX_FRAMES = 8192, STICK_DEADZONE = 16000 };  /* MAX_FRAMES: sample frames */

static SysInfo info;
static const System *sys;

static SDL_Gamepad *gamepads[4];

static uint16_t keyboard_buttons(void) {
    const bool *k = SDL_GetKeyboardState(NULL);
    uint16_t b = 0;
    if (k[SDL_SCANCODE_X]) b |= PAD_A;
    if (k[SDL_SCANCODE_Z]) b |= PAD_B;
    if (k[SDL_SCANCODE_S]) b |= PAD_X;
    if (k[SDL_SCANCODE_A]) b |= PAD_Y;
    if (k[SDL_SCANCODE_Q]) b |= PAD_L;
    if (k[SDL_SCANCODE_W]) b |= PAD_R;
    if (k[SDL_SCANCODE_RSHIFT]) b |= PAD_SELECT;
    if (k[SDL_SCANCODE_RETURN] && !(SDL_GetModState() & SDL_KMOD_ALT)) b |= PAD_START;  /* Alt+Enter: fullscreen */
    if (k[SDL_SCANCODE_UP]) b |= PAD_UP;
    if (k[SDL_SCANCODE_DOWN]) b |= PAD_DOWN;
    if (k[SDL_SCANCODE_LEFT]) b |= PAD_LEFT;
    if (k[SDL_SCANCODE_RIGHT]) b |= PAD_RIGHT;
    return b;
}

static uint16_t gamepad_buttons(SDL_Gamepad *g) {
    if (!g) return 0;
    static const struct { SDL_GamepadButton button; uint16_t bit; } map[] = {
        {SDL_GAMEPAD_BUTTON_EAST, PAD_A},       {SDL_GAMEPAD_BUTTON_SOUTH, PAD_B},
        {SDL_GAMEPAD_BUTTON_NORTH, PAD_X},      {SDL_GAMEPAD_BUTTON_WEST, PAD_Y},
        {SDL_GAMEPAD_BUTTON_LEFT_SHOULDER, PAD_L}, {SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER, PAD_R},
        {SDL_GAMEPAD_BUTTON_BACK, PAD_SELECT},  {SDL_GAMEPAD_BUTTON_START, PAD_START},
        {SDL_GAMEPAD_BUTTON_DPAD_UP, PAD_UP},   {SDL_GAMEPAD_BUTTON_DPAD_DOWN, PAD_DOWN},
        {SDL_GAMEPAD_BUTTON_DPAD_LEFT, PAD_LEFT}, {SDL_GAMEPAD_BUTTON_DPAD_RIGHT, PAD_RIGHT},
    };
    uint16_t b = 0;
    for (size_t i = 0; i < sizeof map / sizeof *map; i++)
        if (SDL_GetGamepadButton(g, map[i].button)) b |= map[i].bit;
    int x = SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_LEFTX);
    int y = SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_LEFTY);
    if (x < -STICK_DEADZONE) b |= PAD_LEFT;
    if (x > STICK_DEADZONE) b |= PAD_RIGHT;
    if (y < -STICK_DEADZONE) b |= PAD_UP;
    if (y > STICK_DEADZONE) b |= PAD_DOWN;
    return b;
}

static void gamepad_event(const SDL_Event *e) {
    if (e->type == SDL_EVENT_GAMEPAD_ADDED) {
        for (int i = 0; i < 4; i++)
            if (gamepads[i] && SDL_GetGamepadID(gamepads[i]) == e->gdevice.which) return;
        for (int i = 0; i < 4; i++) {
            if (gamepads[i]) continue;
            gamepads[i] = SDL_OpenGamepad(e->gdevice.which);
            if (gamepads[i]) SDL_Log("player %d: %s", i + 1, SDL_GetGamepadName(gamepads[i]));
            return;
        }
    } else if (e->type == SDL_EVENT_GAMEPAD_REMOVED) {
        for (int i = 0; i < 4; i++) {
            if (gamepads[i] && SDL_GetGamepadID(gamepads[i]) == e->gdevice.which) {
                SDL_Log("player %d: gamepad disconnected", i + 1);
                SDL_CloseGamepad(gamepads[i]);
                gamepads[i] = NULL;
            }
        }
    }
}

static SDL_Texture *make_tv_frame(SDL_Renderer *ren, int width, int lines) {
    const int w = tv_w(width) * TV_RES, h = tv_h(lines) * TV_RES;
    uint8_t *px = SDL_malloc((size_t)w * h * 4);
    tv_frame_render(px, width, lines);
    SDL_Texture *t = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, w, h);
    if (t) {
        SDL_UpdateTexture(t, NULL, px, w * 4);
        SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
        SDL_SetTextureScaleMode(t, SDL_SCALEMODE_LINEAR);
    }
    SDL_free(px);
    return t;
}

/* Draw the picture's visible columns and lines (info.cols x info.lines,
 * centred in the frame buffer), `width` units wide (the columns times the
 * pixel aspect: NES 256 square pixels, 293 for 8:7, 355 for PAL), and the
 * frame over it, scaled into the output. Integer scaling applies to the
 * lines; with 8:7 pixels the width follows (the pixel-art scale mode keeps
 * the uneven columns sharp). banner: NULL-terminated lines of text drawn
 * over the picture in SDL's built-in 8x8 font, one font pixel per game pixel. */
static void present(SDL_Renderer *ren, SDL_Texture *pic, SDL_Texture *frame, int scale, int width, int cols,
                    int lines, const char *const *banner) {
    int W, H;
    SDL_GetCurrentRenderOutputSize(ren, &W, &H);
    float cw = (float)(frame ? tv_w(width) : width), ch = (float)(frame ? tv_h(lines) : lines);  /* content, in units */
    float sx = W / cw, sy = H / ch;
    if (scale != SCALE_STRETCH) {
        sx = sy = SDL_min(sx, sy);
        if (scale == SCALE_INTEGER && sx >= 1) sx = sy = SDL_floorf(sx);
    }
    SDL_FRect content = {SDL_floorf((W - cw * sx) / 2), SDL_floorf((H - ch * sy) / 2), cw * sx, ch * sy};
    SDL_FRect picture = {content.x + (frame ? TV_LEFT * sx : 0), content.y + (frame ? TV_TOP * sy : 0),
                         width * sx, lines * sy};
    SDL_FRect src = {(info.width - cols) / 2.0f, (info.height - lines) / 2.0f, (float)cols, (float)lines};
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    SDL_RenderTexture(ren, pic, &src, &picture);
    if (frame) SDL_RenderTexture(ren, frame, NULL, &content);
    const float k = SDL_max(1.0f, SDL_floorf(sy));
    SDL_SetRenderScale(ren, k, k);
    for (int i = 0; banner && banner[i]; i++) {
        float x = picture.x / k + 16, y = picture.y / k + 16 + i * 12;
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderFillRect(ren, &(SDL_FRect){x - 2, y - 2, SDL_strlen(banner[i]) * 8.0f + 4, 12});
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderDebugText(ren, x, y, banner[i]);
    }
    SDL_SetRenderScale(ren, 1, 1);
    SDL_RenderPresent(ren);
}

/* The emulator runs on its own thread, paced to the game's frame rate and
 * feeding the audio. The main thread only handles the window, events and
 * input: when Windows holds it (title bar dragged, a gamepad being
 * plugged in) the picture stops for a moment but the game and its sound go on. */
typedef struct {
    SDL_Mutex *lock;          /* the system, fb, fb_new, halt */
    uint32_t fb[MAX_W * MAX_H];
    int fb_new;
    char halt[256];           /* why the game stopped (System.halted), or "" */
    SDL_AtomicInt pads, pads34, reset, quit, done;  /* pads: player 1 | player 2 << 16; pads34: players 3 and 4 */
    SDL_AudioStream *audio;
    double fps;
    long max_frames;
    InputLog *replay;
    FILE *record;
} Emu;

static int emu_thread(void *arg) {
    Emu *u = arg;
    static float samples[MAX_FRAMES * 2];  /* interleaved when stereo */
    const double frame_ns = 1e9 / u->fps;
    uint64_t next = SDL_GetTicksNS();
    for (long frame = 0; !SDL_GetAtomicInt(&u->quit) && (u->max_frames <= 0 || frame < u->max_frames); frame++) {
        InputFrame in;
        int reset = SDL_SetAtomicInt(&u->reset, 0);
        if (frame < u->replay->count) {
            in = u->replay->frames[frame];
        } else {
            int pads = SDL_GetAtomicInt(&u->pads);
            int pads34 = SDL_GetAtomicInt(&u->pads34);
            in.pad[0] = (uint16_t)pads, in.pad[1] = (uint16_t)((unsigned)pads >> 16);
            in.pad[2] = (uint16_t)pads34, in.pad[3] = (uint16_t)((unsigned)pads34 >> 16);
            in.flags = reset ? INPUT_RESET : 0;
        }
        if (u->record) input_log_write(u->record, in, info.players);

        SDL_LockMutex(u->lock);
        if (in.flags & INPUT_RESET) sys->reset();
        int ns = sys->frame(&in, u->fb, samples, MAX_FRAMES);  /* sample frames */
        u->fb_new = 1;
        char halt[256];
        const char *h = sys->halted(halt, sizeof halt);
        SDL_strlcpy(u->halt, h ? h : "", sizeof u->halt);
        SDL_UnlockMutex(u->lock);

        if (u->audio) {
            const int frame_bytes = info.channels * (int)sizeof(float);
            SDL_PutAudioStreamData(u->audio, samples, ns * frame_bytes);
            const float target = 3.0f * info.sample_rate / (float)u->fps;
            float queued = (float)SDL_GetAudioStreamQueued(u->audio) / (float)frame_bytes;
            float ratio = 1.0f + 0.005f * (queued - target) / target;
            SDL_SetAudioStreamFrequencyRatio(u->audio, ratio < 0.995f ? 0.995f : ratio > 1.005f ? 1.005f : ratio);
        }
        next += (uint64_t)frame_ns;  /* pace to the game's rate regardless of monitor rate */
        uint64_t now = SDL_GetTicksNS();
        if (next > now) SDL_DelayPrecise(next - now);
        else {  /* fell behind: don't try to catch up */
            if (now - next > 3 * (uint64_t)frame_ns)  /* the audio queue ran dry */
                SDL_Log("frame %ld: %.0f ms late", frame, (now - next) / 1e6);
            next = now;
        }
    }
    SDL_SetAtomicInt(&u->done, 1);
    return 0;
}

/* A start-up error: logged, and shown in a box (the program has no console
 * when started from a file manager). Returns the exit code. */
static int fail(const char *fmt, ...) {
    char msg[1024];
    va_list ap;
    va_start(ap, fmt);
    SDL_vsnprintf(msg, sizeof msg, fmt, ap);
    va_end(ap);
    SDL_Log("%s", msg);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, APP_NAME, msg, NULL);
    return 1;
}

/* The system to run: --system, the only one linked, or the one the file's
 * bytes name (core/detect.h). NULL with a message in err. */
static const System *pick_system(const char *rom_path, const char *wanted, char *err, size_t errlen) {
    int n = 0;
    while (system_list[n]) n++;
    if (wanted) {
        for (int i = 0; i < n; i++)
            if (!strcmp(wanted, system_list[i]->detector->id) || !strcmp(wanted, system_list[i]->app))
                return system_list[i];
        SDL_snprintf(err, errlen, "--system %s: not one of", wanted);
        for (int i = 0; i < n; i++) SDL_strlcat(err, i ? ", " : " ", errlen), SDL_strlcat(err, system_list[i]->detector->id, errlen);
        return NULL;
    }
    if (n == 1) return system_list[0];
    if (!rom_path) return SDL_snprintf(err, errlen, "usage: %s ROM [--system ID] [--frames N] [--record FILE] [--replay FILE]", APP_NAME), NULL;
    size_t size;
    void *data = SDL_LoadFile(rom_path, &size);
    if (!data) return SDL_snprintf(err, errlen, "%s: %s", rom_path, SDL_GetError()), NULL;
    const SystemDetector *dets[16];
    for (int i = 0; i < n && i < 16; i++) dets[i] = system_list[i]->detector;
    int k = detect_system(dets, n < 16 ? n : 16, data, size, rom_path, err, errlen);
    SDL_free(data);
    if (k < 0) return NULL;
    SDL_Log("%s: %s (--system %s)", rom_path, system_list[k]->detector->name, system_list[k]->detector->id);
    return system_list[k];
}

int main(int argc, char **argv) {
    const char *rom_path = argc > 1 && argv[1][0] != '-' ? argv[1] : NULL;
    long max_frames = 0;
    const char *record = NULL, *replay = NULL, *wanted = NULL;
    for (int i = rom_path ? 2 : 1; i + 1 < argc; i++) {
        if (!strcmp(argv[i], "--frames")) max_frames = atol(argv[++i]);
        else if (!strcmp(argv[i], "--record")) record = argv[++i];
        else if (!strcmp(argv[i], "--replay")) replay = argv[++i];
        else if (!strcmp(argv[i], "--system")) wanted = argv[++i];
    }
    char err[1024];
    if (!(sys = pick_system(rom_path, wanted, err, sizeof err))) return rom_path ? fail("%s", err) : (SDL_Log("%s", err), 2);
    char ini_path[1024];
    SDL_snprintf(ini_path, sizeof ini_path, "%s%s.ini", SDL_GetBasePath(), sys->app);
    Settings cfg;
    settings_load(&cfg, ini_path, sys->settings, sys->setting);
    int opened = sys->open(rom_path, &cfg, &info, err, sizeof err);
    if (opened == 2) return SDL_Log("%s", err), 2;  /* usage */
    if (opened) return fail("%s", err);
    if (info.width > MAX_W || info.height > MAX_H) return fail("picture too large: %dx%d", info.width, info.height);

    InputLog replay_log = {0};
    if (replay && input_log_load(replay, &replay_log) != 0) {
        SDL_Log("%s: not an input recording", replay);
        return 1;
    }
    if (replay && strcmp(replay_log.system, sys->detector->id)) {
        SDL_Log("%s: recorded on another system (%s), this is %s", replay, replay_log.system, sys->detector->id);
        return 1;
    }
    FILE *record_file = NULL;
    if (record && !(record_file = input_log_create(record, sys->detector->id, info.players))) {
        SDL_Log("%s: cannot create", record);
        return 1;
    }

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        SDL_Log("SDL_Init: %s", SDL_GetError());
        return 1;
    }
    SDL_Window *win;
    SDL_Renderer *ren;
    /* starting size: window_scale x the content, smaller if the screen is */
    const int lines = info.lines, cols = info.cols;
    const int width = !cfg.aspect_tv ? cols : (int)(cols * info.aspect + 0.5);  /* NES 8:7: 256 -> 292.6, rounded */
    int k = cfg.window_scale, cw = cfg.tv_frame ? tv_w(width) : width, ch = cfg.tv_frame ? tv_h(lines) : lines;
    SDL_Rect usable;
    if (SDL_GetDisplayUsableBounds(SDL_GetPrimaryDisplay(), &usable))
        while (k > 1 && (cw * k > usable.w || ch * k > usable.h - 40)) k--;
    /* the title: the game and the console it runs as, e.g. "Game (PAL)" */
    char heading[300], title[512];
    SDL_snprintf(heading, sizeof heading, "%s (%s)", info.name, info.tag);
    SDL_snprintf(title, sizeof title, "%s", heading);
    if (!SDL_CreateWindowAndRenderer(title, cw * k, ch * k, SDL_WINDOW_RESIZABLE, &win, &ren)) {
        SDL_Log("window: %s", SDL_GetError());
        return 1;
    }
    /* vsync, so scrolling does not tear; the pacing below (60.1 Hz, PAL 50 Hz)
     * still sets the speed. Not on displays slower than the game: waiting for
     * them would slow it down.
     * shortcut: checked once at start, not when the window moves to another display */
    const SDL_DisplayMode *mode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(win));
    const double fps = info.fps;
    if (!mode || mode->refresh_rate == 0 || mode->refresh_rate >= fps - 1) SDL_SetRenderVSync(ren, 1);
    if (cfg.fullscreen) SDL_SetWindowFullscreen(win, true);
    SDL_Texture *frame_tex = cfg.tv_frame ? make_tv_frame(ren, width, lines) : NULL;
    uint64_t message_until = 0;  /* a short message in the title bar */
    SDL_Texture *tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_XRGB8888,
                                         SDL_TEXTUREACCESS_STREAMING, info.width, info.height);
    SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_PIXELART);

    /* Audio: float at the system's rate and channels. Video sets the pace (NES 60.1 or 50 Hz);
     * the playback rate is nudged (+-0.5%) to keep about 3 frames queued, so
     * the two clocks never drift apart (no crackle, no growing latency). */
    const SDL_AudioSpec spec = {SDL_AUDIO_F32, info.channels, info.sample_rate};
    /* no audio device is not fatal: play silent */
    SDL_AudioStream *audio = NULL;
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) &&
        (audio = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL)))
        SDL_ResumeAudioStreamDevice(audio);
    else SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "no audio, playing without sound: %s", SDL_GetError());

    static Emu emu;
    emu.lock = SDL_CreateMutex();
    emu.audio = audio;
    emu.fps = fps;
    emu.max_frames = max_frames;
    emu.replay = &replay_log;
    emu.record = record_file;
    SDL_Thread *thread = SDL_CreateThread(emu_thread, "emulator", &emu);
    if (!thread) {
        SDL_Log("thread: %s", SDL_GetError());
        return 1;
    }
    static uint32_t fb[MAX_W * MAX_H];
    int running = 1;
    while (running && !SDL_GetAtomicInt(&emu.done)) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = 0;
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) running = 0;
            if (e.type == SDL_EVENT_KEY_DOWN && !e.key.repeat) {
                const char *msg = NULL;
                char err[128], text[160];
                if (e.key.key == SDLK_F5) SDL_SetAtomicInt(&emu.reset, 1);
                if (e.key.key == SDLK_F11 || (e.key.key == SDLK_RETURN && (e.key.mod & SDL_KMOD_ALT)))
                    SDL_SetWindowFullscreen(win, !(SDL_GetWindowFlags(win) & SDL_WINDOW_FULLSCREEN));
                if (e.key.key == SDLK_F10) {
                    if (frame_tex) SDL_DestroyTexture(frame_tex), frame_tex = NULL;
                    else frame_tex = make_tv_frame(ren, width, lines);
                }
                SDL_LockMutex(emu.lock);
                if (e.key.key == SDLK_F2) msg = sys->state_save(info.state_path) == 0 ? "state saved" : "could not save state";
                if (e.key.key == SDLK_F4) {
                    if (sys->state_load(info.state_path, err, sizeof err) == 0) msg = "state loaded";
                    else SDL_snprintf(text, sizeof text, "no state loaded (%s)", err), msg = text;
                }
                if (!msg) msg = sys->key(e.key.key, text, sizeof text);
                SDL_UnlockMutex(emu.lock);
                if (msg) {
                    SDL_snprintf(title, sizeof title, "%s - %s", heading, msg);
                    SDL_SetWindowTitle(win, title);
                    message_until = SDL_GetTicks() + 2000;
                }
            }
            gamepad_event(&e);
        }
        SDL_SetAtomicInt(&emu.pads, (int)(input_clean(keyboard_buttons() | gamepad_buttons(gamepads[0])) |
                                          (unsigned)input_clean(gamepad_buttons(gamepads[1])) << 16));
        SDL_SetAtomicInt(&emu.pads34, (int)(input_clean(gamepad_buttons(gamepads[2])) |
                                            (unsigned)input_clean(gamepad_buttons(gamepads[3])) << 16));

        SDL_LockMutex(emu.lock);
        const int fresh = emu.fb_new;
        char halt[256];
        SDL_strlcpy(halt, emu.halt, sizeof halt);
        if (fresh) SDL_memcpy(fb, emu.fb, sizeof fb), emu.fb_new = 0;
        SDL_UnlockMutex(emu.lock);
        if (!fresh) {
            SDL_Delay(1);
            continue;
        }
        const char *banner[8] = {NULL};  /* the halt message, a line each */
        char *p = halt;
        for (int n = 0; *p && n < 7; n++) {
            banner[n] = p;
            char *nl = SDL_strchr(p, '\n');
            if (!nl) break;
            *nl = 0, p = nl + 1;
        }
        SDL_UpdateTexture(tex, NULL, fb, info.width * sizeof fb[0]);
        present(ren, tex, frame_tex, cfg.scale, width, cols, lines, halt[0] ? banner : NULL);
        if (message_until && SDL_GetTicks() > message_until) {
            SDL_SetWindowTitle(win, heading);
            message_until = 0;
        }
    }
    SDL_SetAtomicInt(&emu.quit, 1);
    SDL_WaitThread(thread, NULL);
    SDL_DestroyMutex(emu.lock);
    if (record_file) fclose(record_file);
    input_log_free(&replay_log);
    for (int i = 0; i < 4; i++)
        if (gamepads[i]) SDL_CloseGamepad(gamepads[i]);
    sys->close();
    if (audio) SDL_DestroyAudioStream(audio);
    SDL_DestroyTexture(tex);
    if (frame_tex) SDL_DestroyTexture(frame_tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
