/* Matching a zip to the game table, and placing each chip (cps1.h). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cps1.h"

static int has_all(const Zip *z, const Cps1Game *g) {
    for (int i = 0; i < g->nfiles; i++)
        if (!zip_find_crc(z, g->files[i].crc, g->files[i].size)) return 0;
    return 1;
}

const Cps1Game *cps1_match_in(const Zip *z, const Cps1Game *games, int n) {
    for (int i = 0; i < n; i++)
        if (has_all(z, &games[i])) return &games[i];
    return NULL;
}

const Cps1Game *cps1_match(const Zip *z) { return cps1_match_in(z, cps1_games, cps1_game_count); }

/* Where byte i of a chip goes, or past the region's end. */
static uint32_t place(const Cps1File *f, uint32_t i) {
    switch (f->load) {
    case CPS1_LOAD_EVEN:
    case CPS1_LOAD_ODD: return f->offset + i * 2;
    case CPS1_LOAD_SWAP16: return f->offset + (i ^ 1);
    case CPS1_LOAD_GFX4: return f->offset + (i >> 1) * 8 + (i & 1);
    case CPS1_LOAD_GFX8: return f->offset + i * 8;
    default: return f->offset + i;
    }
}

int cps1_load(const Cps1Game *g, const Zip *z, Cps1Rom *r, char *err, size_t errlen) {
    memset(r, 0, sizeof *r);
    r->game = g;
    for (int k = 0; k < CPS1_REGIONS; k++) {
        r->size[k] = g->region_size[k];
        if (r->size[k] && !(r->region[k] = calloc(r->size[k], 1))) {
            snprintf(err, errlen, "out of memory");
            return cps1_unload(r), -1;
        }
    }
    for (int i = 0; i < g->nfiles; i++) {
        const Cps1File *f = &g->files[i];
        const ZipEntry *e = zip_find_crc(z, f->crc, f->size);
        uint8_t *chip = e ? malloc(f->size) : NULL;
        if (!e || !chip || zip_read(z, e, chip)) {
            snprintf(err, errlen, "%s: the file with CRC %08x is %s", g->id, (unsigned)f->crc, e ? "damaged" : "missing");
            free(chip);
            return cps1_unload(r), -1;
        }
        for (uint32_t b = 0; b < f->size; b++) {
            uint32_t at = place(f, b);
            if (at >= r->size[f->region]) {
                snprintf(err, errlen, "%s: the file with CRC %08x does not fit its region", g->id, (unsigned)f->crc);
                free(chip);
                return cps1_unload(r), -1;
            }
            r->region[f->region][at] = chip[b];
        }
        free(chip);
    }
    return 0;
}

void cps1_unload(Cps1Rom *r) {
    for (int k = 0; k < CPS1_REGIONS; k++) free(r->region[k]);
    memset(r, 0, sizeof *r);
}
