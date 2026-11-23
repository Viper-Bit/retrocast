/* Matching a zip to the game table, and placing each chip (cps1.h). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cps1.h"

/* The number of the game's own files, if all are in the zip; else 0. */
static int own_files(const Zip *z, const Cps1Game *g) {
    int n = 0;
    for (int i = 0; i < g->nfiles; i++) {
        if (g->files[i].from_parent) continue;
        if (!zip_find_crc(z, g->files[i].crc, g->files[i].size)) return 0;
        n++;
    }
    return n;
}

const Cps1Game *cps1_match_in(const Zip *z, const Cps1Game *games, int n) {
    const Cps1Game *best = NULL;
    int most = 0;
    for (int i = 0; i < n; i++) {
        int k = own_files(z, &games[i]);
        if (k > most) most = k, best = &games[i];
    }
    return best;
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

static int load_from(const Cps1Game *g, const Zip *z, const Zip *pz, Cps1Rom *r, char *err, size_t errlen) {
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
        const Zip *from = z;  /* a merged zip holds its parent's chips too */
        const ZipEntry *e = zip_find_crc(z, f->crc, f->size);
        if (!e && f->from_parent && pz) e = zip_find_crc(from = pz, f->crc, f->size);
        uint8_t *chip = e ? malloc(f->size) : NULL;
        if (!e || !chip || zip_read(from, e, chip)) {
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

int cps1_load(const Cps1Game *g, const Zip *z, Cps1Rom *r, char *err, size_t errlen) {
    return load_from(g, z, NULL, r, err, errlen);
}

int cps1_open_in(const char *path, const uint8_t *data, size_t size, const Cps1Game *games, int n, Cps1Rom *r,
                 char *err, size_t errlen) {
    Zip z, pz;
    const Cps1Game *g = zip_open(&z, data, size) ? NULL : cps1_match_in(&z, games, n);
    size_t base = strlen(path), end;
    while (base && path[base - 1] != '/' && path[base - 1] != '\\') base--;
    end = strlen(path) > base + 4 ? strlen(path) - 4 : base;
    for (int i = 0; g && i < n; i++)  /* a merged zip matches its clones too: the set named like the zip */
        if (strlen(games[i].id) == end - base && !strncmp(games[i].id, path + base, end - base) && own_files(&z, &games[i])) g = &games[i];
    if (!g) {
        if (z.entries) zip_close(&z);
        return snprintf(err, errlen, "%s: not a CPS-1 game this program knows", path), -1;
    }
    uint8_t *pdata = NULL;
    int bad = 0;
    int need_parent = 0;
    for (int i = 0; g->parent && i < g->nfiles; i++)
        need_parent |= g->files[i].from_parent && !zip_find_crc(&z, g->files[i].crc, g->files[i].size);
    if (need_parent) {  /* "<folder>/<parent>.zip" */
        char ppath[1024];
        size_t dir = strlen(path);
        while (dir && path[dir - 1] != '/' && path[dir - 1] != '\\') dir--;
        snprintf(ppath, sizeof ppath, "%.*s%s.zip", (int)dir, path, g->parent);
        FILE *f = fopen(ppath, "rb");
        long n2 = -1;
        if (f && !fseek(f, 0, SEEK_END)) n2 = ftell(f);
        if (f && n2 > 0 && !fseek(f, 0, SEEK_SET) && (pdata = malloc((size_t)n2)) && fread(pdata, 1, (size_t)n2, f) == (size_t)n2 &&
            !zip_open(&pz, pdata, (size_t)n2)) {
            bad = load_from(g, &z, &pz, r, err, errlen);
            zip_close(&pz);
        } else {
            bad = -1;
            snprintf(err, errlen, "%s: %s needs %s.zip beside it", path, g->id, g->parent);
        }
        if (f) fclose(f);
    } else {
        bad = load_from(g, &z, NULL, r, err, errlen);
    }
    free(pdata);
    zip_close(&z);
    return bad ? -1 : 0;
}

int cps1_open(const char *path, const uint8_t *data, size_t size, Cps1Rom *r, char *err, size_t errlen) {
    return cps1_open_in(path, data, size, cps1_games, cps1_game_count, r, err, errlen);
}
