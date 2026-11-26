#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "capture.h"
#include "atari.h"
#include "loader.h"
#include "palette.h"

static InputFrame scripted_input(int frame) {
    static const uint16_t directions[] = {PAD_RIGHT, PAD_UP, PAD_LEFT, PAD_DOWN};
    InputFrame input = {0};
    if (frame >= 30 && frame < 35) input.pad[0] |= PAD_START;
    if (frame >= 60 && frame % 20 < 10) input.pad[0] |= PAD_A;
    if (frame >= 75) input.pad[0] |= directions[(frame / 25) % 4];
    return input;
}

int main(int argc, char **argv) {
    const char *path = argc > 1 && argv[1][0] != '-' ? argv[1] : NULL;
    int embedded = !path && a26_recomp_program && a26_recomp_program->rom;
    if (!path && !embedded) {
        fprintf(stderr, "usage: atari2600_headless ROM [--frames N] [--record FILE] [--replay FILE] [--diff] [--coverage]\n");
        return 2;
    }
    const char *name = path ? path : a26_recomp_program->rom_name;
    int frames = 60, play = 0, diff = 0, coverage = 0;
    int pal = a26_recomp_program ? a26_recomp_program->pal : (strstr(name, "(Europe)") != NULL || strstr(name, "(PAL)") != NULL);
    A26CartType mapper = A26_CART_AUTO;
    if (a26_recomp_program) mapper = (A26CartType)a26_recomp_program->mapper;
    const char *ppm = NULL, *trace_path = NULL, *load_path = NULL, *save_path = NULL;
    const char *record_path = NULL, *replay_path = NULL;
    int frame_limit = 0;
    int save_at = -1;
    for (int i = path ? 2 : 1; i < argc; i++) {
        if (!strcmp(argv[i], "--frames") && i + 1 < argc) {
            char *end;
            errno = 0;
            long value = strtol(argv[++i], &end, 10);
            if (errno || !*argv[i] || *end || value < 0 || value > INT_MAX) {
                fprintf(stderr, "invalid frame count: %s\n", argv[i]);
                return 2;
            }
            frame_limit = 1;
            frames = (int)value;
        }
        else if (!strcmp(argv[i], "--play")) play = 1;
        else if (!strcmp(argv[i], "--record") && i + 1 < argc) record_path = argv[++i];
        else if (!strcmp(argv[i], "--replay") && i + 1 < argc) replay_path = argv[++i];
        else if (!strcmp(argv[i], "--diff")) diff = 1;
        else if (!strcmp(argv[i], "--coverage")) coverage = 1;
        else if (!strcmp(argv[i], "--trace") && i + 1 < argc) trace_path = argv[++i];
        else if (!strcmp(argv[i], "--load-state") && i + 1 < argc) load_path = argv[++i];
        else if (!strcmp(argv[i], "--state-at") && i + 2 < argc) { save_at = atoi(argv[++i]); save_path = argv[++i]; }
        else if (!strcmp(argv[i], "--pal")) pal = 1;
        else if (!strcmp(argv[i], "--region") && i + 1 < argc) {
            const char *value = argv[++i];
            if (!strcmp(value, "ntsc")) pal = 0;
            else if (!strcmp(value, "pal")) pal = 1;
            else if (!strcmp(value, "auto")) pal = a26_recomp_program ? a26_recomp_program->pal :
                (strstr(name, "(Europe)") != NULL || strstr(name, "(PAL)") != NULL);
            else { fprintf(stderr, "invalid region: %s\n", value); return 2; }
        } else if (!strcmp(argv[i], "--mapper") && i + 1 < argc) {
            static const char *const names[] = {"auto", "2k", "4k", "f8", "f6", "f4", "f8sc", "f6sc", "f4sc", "fa", "e0", "e7", "3f"};
            const char *value = argv[++i];
            unsigned j;
            for (j = 0; j < sizeof names / sizeof names[0]; j++) if (!strcmp(value, names[j])) break;
            if (j == sizeof names / sizeof names[0]) { fprintf(stderr, "invalid mapper: %s\n", value); return 2; }
            mapper = (A26CartType)j;
        }
        else if (!strcmp(argv[i], "--ppm") && i + 1 < argc) ppm = argv[++i];
        else { fprintf(stderr, "unknown option: %s\n", argv[i]); return 2; }
    }
    uint8_t *rom;
    size_t size;
    char err[256];
    if (embedded) {
        size = a26_recomp_program->rom_size;
        rom = malloc(size);
        if (!rom) return 1;
        memcpy(rom, a26_recomp_program->rom, size);
    } else if (a26_load_rom(path, &rom, &size, err, sizeof err)) { fprintf(stderr, "%s\n", err); return 1; }
    Atari2600 machine;
    if (a26_init(&machine, rom, size, mapper, pal)) { fprintf(stderr, "unsupported cartridge\n"); free(rom); return 1; }
    if (a26_recomp_program && !machine.program) { fprintf(stderr, "ROM or hardware configuration does not match compiled code\n"); free(rom); return 1; }
    Atari2600 reference;
    if (diff) {
        if (!machine.program) { fprintf(stderr, "--diff needs recompiled code\n"); free(rom); return 2; }
        if (a26_init(&reference, rom, size, mapper, pal)) { free(rom); return 1; }
        reference.program = NULL;
        machine.reference = &reference;
    }
    uint8_t trace[8 * 4096] = {0};
    if (trace_path) machine.trace = trace;
    if (load_path && (a26_load(&machine, load_path) || (diff && a26_load(&reference, load_path)))) {
        fprintf(stderr, "cannot load state\n"); free(rom); return 1;
    }
    InputLog replay = {0};
    FILE *record = NULL;
    int result = 1;
    if (replay_path && (input_log_load(replay_path, &replay) || strcmp(replay.system, "a26") ||
                        replay.count > INT_MAX)) {
        fprintf(stderr, "cannot load Atari 2600 recording: %s\n", replay_path);
        goto done;
    }
    if (replay_path && !frame_limit) frames = (int)replay.count;
    if (record_path && !(record = input_log_create(record_path, "a26", 2))) {
        fprintf(stderr, "cannot create recording: %s\n", record_path);
        goto done;
    }
    for (int i = 0; i < frames && !machine.bus.cpu.jammed; i++) {
        InputFrame input = {0};
        if (i < replay.count) input = replay.frames[i];
        else if (play) input = scripted_input(i);
        if (record) input_log_write(record, input, 2);
        if (input.flags & INPUT_RESET) {
            uint64_t compiled = machine.compiled_cycles, total = machine.total_cycles;
            if (a26_init(&machine, rom, size, mapper, pal) ||
                (diff && a26_init(&reference, rom, size, mapper, pal))) goto done;
            machine.trace = trace_path ? trace : NULL;
            machine.compiled_cycles = compiled;
            machine.total_cycles = total;
            if (diff) {
                reference.program = NULL;
                machine.reference = &reference;
            }
        }
        a26_frame(&machine, &input);
        machine.tia.sample_count = 0;
        if (diff) reference.tia.sample_count = 0;
        if (save_path && i + 1 == save_at && a26_save(&machine, save_path)) {
            fprintf(stderr, "cannot save state\n"); goto done;
        }
        if (machine.diff_failed) break;
    }
    printf("frames=%u cycles=%llu pc=%04X bank=%u jammed=%u\n", machine.tia.frames,
           (unsigned long long)machine.bus.cpu.cycles, machine.bus.cpu.pc,
           machine.bus.cart.bank, machine.bus.cpu.jammed);
    if (diff && !machine.diff_failed) printf("diff=matched\n");
    if (coverage) printf("coverage=%.2f%% compiled_cycles=%llu total_cycles=%llu\n",
        machine.total_cycles ? 100.0 * (double)machine.compiled_cycles / (double)machine.total_cycles : 0.0,
        (unsigned long long)machine.compiled_cycles, (unsigned long long)machine.total_cycles);
    if (trace_path) {
        FILE *f = fopen(trace_path, "wb");
        if (!f || fwrite(trace, 1, sizeof trace, f) != sizeof trace) {
            if (f) fclose(f);
            fprintf(stderr, "cannot write trace\n"); goto done;
        }
        if (fclose(f)) goto done;
    }
    if (ppm) {
        static uint32_t rgb[A26_WIDTH * A26_HEIGHT];
        for (unsigned i = 0; i < A26_WIDTH * A26_HEIGHT; i++) {
            uint8_t pixel = machine.tia.frame[i];
            rgb[i] = (pixel & 1) ? 0 : a26_palette_color(pixel, pal);
        }
        if (capture_ppm(ppm, rgb, A26_WIDTH, A26_HEIGHT, A26_WIDTH)) goto done;
    }
    result = machine.bus.cpu.jammed || machine.diff_failed ? 1 : 0;
done:
    if (record) {
        int failed = ferror(record);
        if (fclose(record) || failed) {
            fprintf(stderr, "cannot write recording: %s\n", record_path);
            result = 1;
        }
    }
    input_log_free(&replay);
    free(rom);
    return result;
}
