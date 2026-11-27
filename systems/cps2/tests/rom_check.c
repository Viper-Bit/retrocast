/* Load a catalog set and print region sizes and CRCs. */
#include "roms.h"
#include "file.h"
#ifdef CPS2_CHECK_MACHINE
#include "machine.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int check(const Cps2Game *game, const char *folder, uint64_t cycles)
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
        } else {
            printf("reset pc %06x sp %06x\n", (unsigned)(machine->cpu.pc - 4),
                   (unsigned)machine->cpu.a[7]);
            cps2_machine_run(machine, cycles);
            printf("pc %06x graphics %08x\n", (unsigned)(machine->cpu.pc - 4),
                   (unsigned)zip_crc32(machine->graphics, sizeof(machine->graphics)));
            if (machine->cpu.halted)
                status = EXIT_FAILURE;
            cps2_machine_destroy(machine);
        }
        free(machine);
    }
#else
    (void)cycles;
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
#ifdef CPS2_CHECK_MACHINE
    valid |= argc == 4;
#endif
    const Cps2Game *game = valid ? cps2_find_game(argv[2]) : NULL;
    if (!game) {
        fprintf(stderr, "Usage: %s ROM_FOLDER SET_ID [CYCLES]\n", argv[0]);
        return EXIT_FAILURE;
    }
    return check(game, argv[1], argc == 4 ? strtoull(argv[3], NULL, 10) : 0);
}
