#include "roms.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const Cps2Game *cps2_find_game(const char *id)
{
    for (size_t i = 0; i < cps2_game_count; ++i)
        if (!strcmp(id, cps2_games[i].id))
            return &cps2_games[i];
    return NULL;
}

void cps2_unload(Cps2Rom *rom)
{
    if (rom->regions)
        for (size_t i = 0; i < rom->game->count; ++i)
            free(rom->regions[i]);
    free(rom->regions);
    *rom = (Cps2Rom){0};
}

const uint8_t *cps2_region(const Cps2Rom *rom, const char *tag, size_t *size)
{
    *size = 0;
    if (rom->game)
        for (size_t i = 0; i < rom->game->count; ++i)
            if (!strcmp(tag, rom->game->regions[i].tag)) {
                *size = rom->game->regions[i].size;
                return rom->regions[i];
            }
    return NULL;
}

static int read_chip(const Cps2Load *load, const Zip *archives, size_t count, uint8_t *chip)
{
    for (size_t i = 0; i < count; ++i) {
        const ZipEntry *entry = zip_find_crc(&archives[i], load->crc, load->chip_size);
        if (entry && !zip_read(&archives[i], entry, chip))
            return 0;
    }
    return -1;
}

static size_t wired_offset(Cps2Wiring wiring, size_t byte)
{
    switch (wiring) {
    case CPS2_BYTE16: return byte * 2;
    case CPS2_SWAP16: return byte ^ 1;
    case CPS2_BYTE64: return byte * 8;
    case CPS2_WORD64: return byte / 2 * 8 + byte % 2;
    default: return byte;
    }
}

int cps2_load(const Cps2Game *game, const Zip *archives, size_t archive_count,
              Cps2Rom *out, char *error, size_t error_size)
{
    *out = (Cps2Rom){.game = game, .regions = calloc(game->count, sizeof(*out->regions))};
    uint8_t *chip = NULL;
    const char *problem = "out of memory", *tag = "", *name = "";
    if (!out->regions)
        goto fail;

    for (size_t r = 0; r < game->count; ++r) {
        const Cps2Region *region = &game->regions[r];
        tag = region->tag;
        name = "";
        problem = "out of memory";
        uint8_t *bytes = out->regions[r] = malloc(region->size);
        if (!bytes)
            goto fail;
        memset(bytes, region->erase, region->size);
        const Cps2Load *previous = NULL;
        for (size_t i = 0; i < region->count; ++i) {
            const Cps2Load *load = &region->loads[i];
            name = load->name ? load->name : "";
            if (load->wiring == CPS2_UNDUMPED) {
                problem = "undumped in MAME";
                goto fail;
            }
            if (load->offset > region->size || !load->length ||
                ((load->wiring == CPS2_SWAP16 || load->wiring == CPS2_WORD64) &&
                 load->length % 2) ||
                wired_offset(load->wiring, load->length - 1) +
                (load->wiring == CPS2_SWAP16) >= region->size - load->offset) {
                problem = "load outside region";
                goto fail;
            }
            if (load->wiring == CPS2_FILL) {
                memset(bytes + load->offset, load->crc, load->length);
                continue;
            }
            if (load->source > load->chip_size || load->length > load->chip_size - load->source) {
                problem = "load outside chip";
                goto fail;
            }
            if (!previous || previous->crc != load->crc || previous->chip_size != load->chip_size) {
                uint8_t *buffer = realloc(chip, load->chip_size);
                problem = "out of memory";
                if (!buffer)
                    goto fail;
                chip = buffer;
                problem = "missing or damaged chip";
                if (read_chip(load, archives, archive_count, chip))
                    goto fail;
                previous = load;
            }
            for (size_t b = 0; b < load->length; ++b)
                bytes[load->offset + wired_offset(load->wiring, b)] = chip[load->source + b];
        }
    }
    free(chip);
    return 0;

fail:
    snprintf(error, error_size, "%s %s %s: %s", game->id, tag, name, problem);
    free(chip);
    cps2_unload(out);
    return -1;
}
