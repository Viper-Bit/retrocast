#include "roms.h"
#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cps2_open(const Cps2Game *game, const char *folder, Cps2Rom *rom,
              char *error, size_t error_size)
{
    size_t depth = 0;
    for (const Cps2Game *g = game; g; g = g->parent ? cps2_find_game(g->parent) : NULL)
        ++depth;
    Zip *archives = calloc(depth + 1, sizeof(*archives));
    uint8_t **data = calloc(depth + 1, sizeof(*data));
    size_t count = 0;
    int status = -1;
    if (!archives || !data) {
        snprintf(error, error_size, "out of memory");
        goto done;
    }

    for (const char *id = game->id; id;) {
        size_t capacity = strlen(folder) + strlen(id) + sizeof("/.zip");
        char *path = malloc(capacity);
        if (!path) {
            snprintf(error, error_size, "out of memory");
            goto done;
        }
        snprintf(path, capacity, "%s/%s.zip", folder, id);
        size_t size;
        uint8_t *bytes = file_read(path, &size);
        if (bytes) {
            if (zip_open(&archives[count], bytes, size)) {
                snprintf(error, error_size, "%s: invalid ZIP", path);
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

    status = cps2_load(game, archives, count, rom, error, error_size);
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
