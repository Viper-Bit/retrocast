/* Load a catalog set and print region sizes and CRCs. */
#include "roms.h"
#include "file.h"
#ifdef CPS2_CHECK_MACHINE
#include "machine.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef CPS2_CHECK_MACHINE
#ifdef CPS2_HAS_RECOMP
extern const Cps2Recomp cps2_recomp_program;
#endif
static Cps2Machine *reference;
static int mismatch;

static int write_opcodes(const Cps2Machine *machine, const char *path)
{
    if (machine->program_size < 256)
        return -1;
    FILE *file = fopen(path, "wb");
    if (!file)
        return -1;
    int failed = fwrite(machine->program, 1, 256, file) != 256;
    for (uint32_t a = 0; a < machine->program_size; a += 2) {
        uint16_t word = cps2_opcode(machine, a);
        fputc(word >> 8, file);
        fputc(word & 255, file);
    }
    failed |= ferror(file);
    return fclose(file) || failed ? -1 : 0;
}

static void scrub(Cps2Machine *state)
{
    state->cpu.bus = state->audio_cpu.bus = NULL;
    memset(state->cpu.abort, 0, sizeof(state->cpu.abort));
    state->program = state->audio_program = state->sound.rom = NULL;
    state->opcodes = NULL;
    state->sound.dsp = NULL;
    state->tiles = NULL;
    state->recomp = NULL;
    state->executed = NULL;
    state->audio_sample = NULL;
    state->audio_context = NULL;
    state->native_clocks = 0;
}

static void run(Cps2Machine *machine, uint64_t until)
{
    if (!reference) {
        cps2_machine_run(machine, until);
        return;
    }
    static Cps2Machine actual, expected;
    const uint64_t interval = 16 * 1024;
    memcpy(reference->inputs, machine->inputs, sizeof(machine->inputs));
    while (machine->cpu.cycles < until && !machine->cpu.halted && !mismatch) {
        uint64_t slice = until - machine->cpu.cycles;
        uint64_t target = machine->cpu.cycles + (slice < interval ? slice : interval);
        cps2_machine_run(machine, target);
        cps2_machine_run(reference, target);
        memcpy(&actual, machine, sizeof(actual));
        memcpy(&expected, reference, sizeof(expected));
        scrub(&actual);
        scrub(&expected);
        if (memcmp(&actual, &expected, sizeof(actual))) {
            fprintf(stderr, "CPS-2 lockstep mismatch at clock %llu (PC %06x vs %06x)\n",
                    (unsigned long long)machine->cpu.cycles, (unsigned)machine->cpu.pc,
                    (unsigned)reference->cpu.pc);
            mismatch = 1;
        }
    }
}

static int load_sound(Cps2Machine *machine, const Cps2Rom *rom, const char *folder)
{
    size_t capacity = strlen(folder) + sizeof("/qsound.zip");
    char *path = malloc(capacity);
    if (!path)
        return -1;
    snprintf(path, capacity, "%s/qsound.zip", folder);
    size_t size;
    uint8_t *bytes = file_read(path, &size);
    free(path);
    Zip archive;
    int status = -1;
    if (bytes && !zip_open(&archive, bytes, size)) {
        status = cps2_sound_init(machine, rom, &archive);
        zip_close(&archive);
    }
    free(bytes);
    return status;
}

static void write_sample(void *context, const int16_t sample[2])
{
    FILE *file = context;
    for (size_t i = 0; i < 2; ++i) {
        uint16_t word = (uint16_t)sample[i];
        fputc(word & 255, file);
        fputc(word >> 8, file);
    }
}

static int write_frame(const Cps2Machine *machine, const char *path)
{
    FILE *file = fopen(path, "wb");
    if (!file)
        return -1;
    fputs("P6\n384 224\n255\n", file);
    for (size_t i = 0; i < 384 * 224; ++i) {
        uint32_t pixel = machine->frame[i];
        fputc((pixel >> 16) & 255, file);
        fputc((pixel >> 8) & 255, file);
        fputc(pixel & 255, file);
    }
    int failed = ferror(file);
    return fclose(file) || failed ? -1 : 0;
}

static void play(Cps2Machine *machine, uint64_t at, int fight)
{
    /* Pulse coin, start, character select, and in-game input. */
    const uint64_t frame = 262 * 1024;
    machine->inputs[2] &= (uint16_t)~0x1000;
    run(machine, at + 2 * frame);
    machine->inputs[2] |= 0x1000;
    run(machine, at + 90 * frame);
    machine->inputs[2] &= (uint16_t)~0x0100;
    run(machine, at + 98 * frame);
    machine->inputs[2] |= 0x0100;
    run(machine, at + 240 * frame);
    machine->inputs[0] &= (uint16_t)~0x0011;
    run(machine, at + 248 * frame);
    machine->inputs[0] |= 0x0011;
    run(machine, at + 1020 * frame);
    if (fight)
        machine->inputs[0] &= (uint16_t)~0x0011;
    run(machine, at + 1040 * frame);
    machine->inputs[0] |= 0x0011;
    run(machine, at + 1050 * frame);
}

static int boot_probe(Cps2Machine *machine, uint64_t until)
{
    const uint64_t interval = 16 * 262 * 1024;
    uint32_t first = 0;
    int seen = 0, changed = 0;
    for (uint64_t target = interval; !machine->cpu.halted;) {
        if (target > until)
            target = until;
        run(machine, target);
        const uint32_t *pixels = machine->frame;
        for (size_t i = 1; i < sizeof(machine->frame) / sizeof(*pixels); ++i) {
            if (pixels[i] == pixels[0])
                continue;
            uint32_t crc = zip_crc32((const uint8_t *)pixels, sizeof(machine->frame));
            changed |= seen && crc != first;
            if (!seen)
                first = crc;
            seen = 1;
            break;
        }
        if (target == until)
            break;
        target += until - target < interval ? until - target : interval;
    }
    if (machine->cpu.halted)
        fputs("68000 halted during boot\n", stderr);
    else if (!changed)
        fputs("No changing, non-uniform video during boot\n", stderr);
    return machine->cpu.halted || !changed ? -1 : 0;
}
#endif

static int check(const Cps2Game *game, const char *folder, uint64_t cycles, int diff)
{
    size_t depth = 0;
    for (const Cps2Game *g = game; g; g = g->parent ? cps2_find_game(g->parent) : NULL)
        ++depth;
    Zip *archives = calloc(depth + 1, sizeof(*archives));
    uint8_t **data = calloc(depth + 1, sizeof(*data));
    size_t count = 0;
    int status = EXIT_FAILURE;
    if (!archives || !data) {
        fputs("out of memory\n", stderr);
        goto done;
    }

    for (const char *id = game->id; id;) {
        size_t capacity = strlen(folder) + strlen(id) + sizeof("/.zip");
        char *path = malloc(capacity);
        if (!path) {
            fputs("out of memory\n", stderr);
            goto done;
        }
        snprintf(path, capacity, "%s/%s.zip", folder, id);
        size_t size;
        uint8_t *bytes = file_read(path, &size);
        if (bytes) {
            if (zip_open(&archives[count], bytes, size)) {
                fprintf(stderr, "%s: invalid ZIP\n", path);
                free(bytes);
                free(path);
                goto done;
            }
            data[count++] = bytes;
        }
        free(path);
        const Cps2Game *entry = cps2_find_game(id);
        id = entry ? entry->parent : NULL;
    }

    Cps2Rom rom;
    char error[256];
    if (cps2_load(game, archives, count, &rom, error, sizeof(error))) {
        fprintf(stderr, "%s\n", error);
        goto done;
    }
    for (size_t i = 0; i < game->count; ++i) {
        const Cps2Region *region = &game->regions[i];
        printf("%s %u %08x\n", region->tag, (unsigned)region->size,
               (unsigned)zip_crc32(rom.regions[i], region->size));
    }
    status = EXIT_SUCCESS;
#ifdef CPS2_CHECK_MACHINE
    if (cycles) {
        Cps2Machine *machine = malloc(sizeof(*machine));
        if (!machine || cps2_machine_init(machine, &rom)) {
            fputs("Could not initialize CPS-2 machine\n", stderr);
            status = EXIT_FAILURE;
        } else if (load_sound(machine, &rom, folder)) {
            fputs("CPS-2 sound needs audiocpu, qsound, and qsound.zip (CRC d6cf5ef5)\n", stderr);
            cps2_machine_destroy(machine);
            status = EXIT_FAILURE;
        } else {
            const char *image = getenv("CPS2_OPCODE_IMAGE");
            const char *trace = getenv("CPS2_EXECUTED_PCS");
            if (trace)
                machine->executed = calloc(machine->program_size, 1);
            if (trace && !machine->executed) {
                fputs("Could not allocate executed-PC bitmap\n", stderr);
                status = EXIT_FAILURE;
                goto machine_done;
            }
            if (image && write_opcodes(machine, image)) {
                fprintf(stderr, "Could not write opcode image: %s\n", image);
                status = EXIT_FAILURE;
            }
#ifdef CPS2_HAS_RECOMP
            if (!cps2_machine_set_recomp(machine, &cps2_recomp_program)) {
                fputs("Generated code does not match this opcode image\n", stderr);
                status = EXIT_FAILURE;
            }
#endif
            if (diff) {
                reference = malloc(sizeof(*reference));
                if (!reference || cps2_machine_init(reference, &rom) ||
                    load_sound(reference, &rom, folder)) {
                    fputs("Could not initialize lockstep interpreter\n", stderr);
                    status = EXIT_FAILURE;
                    goto machine_done;
                }
            }
            const char *audio_path = getenv("CPS2_PCM");
            FILE *audio = audio_path ? fopen(audio_path, "wb") : NULL;
            if (audio) {
                machine->audio_sample = write_sample;
                machine->audio_context = audio;
            } else if (audio_path) {
                perror(audio_path);
                status = EXIT_FAILURE;
            }
            printf("reset pc %06x sp %06x\n", (unsigned)(machine->cpu.pc - 4),
                   (unsigned)machine->cpu.a[7]);
            if (getenv("CPS2_BOOT_PROBE")) {
                if (boot_probe(machine, cycles))
                    status = EXIT_FAILURE;
            } else {
                run(machine, cycles);
            }
            const char *script = getenv("CPS2_PLAY");
            if (script)
                play(machine, cycles, strcmp(script, "idle") != 0);
            printf("pc %06x graphics %08x frame %08x\n", (unsigned)(machine->cpu.pc - 4),
                   (unsigned)zip_crc32(machine->graphics, sizeof(machine->graphics)),
                   (unsigned)zip_crc32((const uint8_t *)machine->frame, sizeof(machine->frame)));
            if (machine->cpu.halted)
                status = EXIT_FAILURE;
            if (diff) {
                if (mismatch || !machine->native_clocks) {
                    fputs("Lockstep failed or no native code ran\n", stderr);
                    status = EXIT_FAILURE;
                } else {
                    printf("Lockstep passed, %llu native clocks of %llu\n",
                           (unsigned long long)machine->native_clocks,
                           (unsigned long long)machine->cpu.cycles);
                }
            }
            if (audio) {
                int failed = ferror(audio);
                if (fclose(audio) || failed)
                    status = EXIT_FAILURE;
            }
            const char *capture = getenv("CPS2_FRAME");
            if (capture && write_frame(machine, capture)) {
                perror(capture);
                status = EXIT_FAILURE;
            }
            if (trace) {
                FILE *file = fopen(trace, "wb");
                if (!file) {
                    perror(trace);
                    status = EXIT_FAILURE;
                } else {
                    int failed = fwrite(machine->executed, 1, machine->program_size, file)
                                 != machine->program_size;
                    if (fclose(file) || failed)
                        status = EXIT_FAILURE;
                }
            }
machine_done:
            if (reference) {
                cps2_machine_destroy(reference);
                free(reference);
                reference = NULL;
            }
            free(machine->executed);
            cps2_machine_destroy(machine);
        }
        free(machine);
    }
#else
    (void)cycles;
    (void)diff;
#endif
    cps2_unload(&rom);
done:
    while (count) {
        --count;
        zip_close(&archives[count]);
        free(data[count]);
    }
    free(archives);
    free(data);
    return status;
}

int main(int argc, char **argv)
{
    int valid = argc == 3;
    int diff = 0;
#ifdef CPS2_CHECK_MACHINE
    valid |= argc == 4;
#ifdef CPS2_HAS_RECOMP
    diff = argc == 5 && !strcmp(argv[4], "--diff");
    valid |= diff;
#endif
#endif
    const Cps2Game *game = valid ? cps2_find_game(argv[2]) : NULL;
    if (!game) {
        fprintf(stderr, "Usage: %s ROM_FOLDER SET_ID [CYCLES]\n", argv[0]);
        return EXIT_FAILURE;
    }
    return check(game, argv[1], argc >= 4 ? strtoull(argv[3], NULL, 10) : 0, diff);
}
