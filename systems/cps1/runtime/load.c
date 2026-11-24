/* Matching a zip to the game table, and placing each chip (cps1.h). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cps1.h"
#include "kabuki.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <strings.h>
#endif

/* How many of the game's own files the zip holds (*all: every one). */
static int own_files(const Zip *z, const Cps1Game *g, int *all) {
    int n = 0, total = 0;
    for (int i = 0; i < g->nfiles; i++) {
        if (g->files[i].from_parent) continue;
        total++;
        n += zip_find_crc(z, g->files[i].crc, g->files[i].size) != NULL;
    }
    if (all) *all = n == total;
    return n * 2 >= total && n ? n : 0;  /* under half its own files: not this game */
}

/* The game the zip holds most of: whole ones first (the rest of a partial one is looked for in the folder). */
const Cps1Game *cps1_match_in(const Zip *z, const Cps1Game *games, int n) {
    const Cps1Game *best = NULL;
    int most = 0, best_all = 0;
    for (int i = 0; i < n; i++) {
        int all, k = own_files(z, &games[i], &all);
        if (k && (all > best_all || (all == best_all && k > most))) most = k, best_all = all, best = &games[i];
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

static int alloc_regions(const Cps1Game *g, Cps1Rom *r, char *err, size_t errlen) {
    memset(r, 0, sizeof *r);
    r->game = g;
    for (int k = 0; k < CPS1_REGIONS; k++) {
        r->size[k] = g->region_size[k];
        if (r->size[k] && !(r->region[k] = calloc(r->size[k], 1))) {
            snprintf(err, errlen, "out of memory");
            return cps1_unload(r), -1;
        }
    }
    return 0;
}

/* Places each chip not yet done[] that z holds, by CRC, whatever its name; -1 (err set) when one is damaged. */
static int take(const Cps1Game *g, const Zip *z, Cps1Rom *r, char *done, char *err, size_t errlen) {
    for (int i = 0; i < g->nfiles; i++) {
        const Cps1File *f = &g->files[i];
        const ZipEntry *e = done[i] ? NULL : zip_find_crc(z, f->crc, f->size);
        if (!e) continue;
        uint8_t *chip = malloc(f->size);
        if (!chip || zip_read(z, e, chip)) {
            snprintf(err, errlen, "%s: the file with CRC %08x is damaged", g->id, (unsigned)f->crc);
            return free(chip), -1;
        }
        for (uint32_t b = 0; b < f->size; b++) {
            uint32_t at = place(f, b);
            if (at >= r->size[f->region]) {
                snprintf(err, errlen, "%s: the file with CRC %08x does not fit its region", g->id, (unsigned)f->crc);
                return free(chip), -1;
            }
            r->region[f->region][at] = chip[b];
        }
        free(chip);
        done[i] = 1;
    }
    return 0;
}

/* Once every chip is placed: what MAME's init does to them; -1 (err set) when out of memory. */
static int finish(const Cps1Game *g, Cps1Rom *r, char *err, size_t errlen) {
    if (g->group == CPS1_QSOUND && r->size[CPS1_R_SOUND] >= 0x8000) {
        uint8_t *z80 = r->region[CPS1_R_SOUND];
        if (!(r->z80_op = malloc(0x8000)) || (g->z80_raw && !(r->z80_raw = malloc(0x8000))))
            return snprintf(err, errlen, "out of memory"), -1;
        if (r->z80_raw) memcpy(r->z80_raw, z80, 0x8000);
        if (g->init >= CPS1_INIT_WOF && g->init <= CPS1_INIT_SLAMMAST) cps1_kabuki(g->init, z80, r->z80_op, z80);  /* data in place, as MAME */
        else memcpy(r->z80_op, z80, 0x8000);  /* no key: plain code (the tests' boards) */
    }
    return 0;
}

static int missing(const Cps1Game *g, const char *done) {
    for (int i = 0; i < g->nfiles; i++)
        if (!done[i]) return i;
    return -1;
}

void cps1_unload(Cps1Rom *r) {
    for (int k = 0; k < CPS1_REGIONS; k++) free(r->region[k]);
    free(r->z80_op), free(r->z80_raw);
    memset(r, 0, sizeof *r);
}

int cps1_load(const Cps1Game *g, const Zip *z, Cps1Rom *r, char *err, size_t errlen) {
    char done[sizeof ((Cps1Game *)0)->files / sizeof (Cps1File)] = {0};
    if (alloc_regions(g, r, err, errlen) || take(g, z, r, done, err, errlen)) return cps1_unload(r), -1;
    int i = missing(g, done);
    if (i < 0) return finish(g, r, err, errlen) ? (cps1_unload(r), -1) : 0;
    snprintf(err, errlen, "%s: the file with CRC %08x is missing", g->id, (unsigned)g->files[i].crc);
    return cps1_unload(r), -1;
}

/* take() from the zip at path; -1 when a chip there is damaged. */
static int take_path(const char *path, const Cps1Game *g, Cps1Rom *r, char *done, char *err, size_t errlen) {
    FILE *f = fopen(path, "rb");
    long n = -1;
    uint8_t *data = NULL;
    Zip z;
    int bad = 0;
    if (f && !fseek(f, 0, SEEK_END)) n = ftell(f);
    if (f && n > 0 && !fseek(f, 0, SEEK_SET) && (data = malloc((size_t)n)) && fread(data, 1, (size_t)n, f) == (size_t)n &&
        !zip_open(&z, data, (size_t)n)) {
        bad = take(g, &z, r, done, err, errlen);
        zip_close(&z);
    }
    if (f) fclose(f);
    free(data);
    return bad;
}

/* take_path() on each .zip of dir but skip1 and skip2, until no chip is missing. */
static int take_folder(const char *dir, const char *skip1, const char *skip2, const Cps1Game *g, Cps1Rom *r, char *done,
                       char *err, size_t errlen) {
    char p[1024];
    int bad = 0;
#ifdef _WIN32
    WIN32_FIND_DATAA d;
    snprintf(p, sizeof p, "%s*.zip", *dir ? dir : "./");
    HANDLE h = FindFirstFileA(p, &d);
    if (h == INVALID_HANDLE_VALUE) return 0;
    do {
        if (snprintf(p, sizeof p, "%s%s", dir, d.cFileName) >= (int)sizeof p) continue;  /* too long a path: not opened cut short */
        if (_stricmp(p, skip1) && _stricmp(p, skip2)) bad = take_path(p, g, r, done, err, errlen);
    } while (!bad && missing(g, done) >= 0 && FindNextFileA(h, &d));
    FindClose(h);
#else
    DIR *dd = opendir(*dir ? dir : ".");
    struct dirent *e;
    while (dd && !bad && missing(g, done) >= 0 && (e = readdir(dd))) {
        size_t n = strlen(e->d_name);
        if (n < 4 || strcasecmp(e->d_name + n - 4, ".zip")) continue;
        if (snprintf(p, sizeof p, "%s%s", dir, e->d_name) >= (int)sizeof p) continue;  /* too long a path: not opened cut short */
        if (strcmp(p, skip1) && strcmp(p, skip2)) bad = take_path(p, g, r, done, err, errlen);
    }
    if (dd) closedir(dd);
#endif
    return bad;
}

/* "<folder of path><name>.zip" read whole and opened; NULL if it cannot be. */
static uint8_t *open_beside(const char *path, const char *name, Zip *z) {
    char p[1024];
    size_t dir = strlen(path);
    while (dir && path[dir - 1] != '/' && path[dir - 1] != '\\') dir--;
    snprintf(p, sizeof p, "%.*s%s.zip", (int)dir, path, name);
    FILE *f = fopen(p, "rb");
    long n = -1;
    uint8_t *data = NULL;
    if (f && !fseek(f, 0, SEEK_END)) n = ftell(f);
    if (f && n > 0 && !fseek(f, 0, SEEK_SET) && (data = malloc((size_t)n)) && fread(data, 1, (size_t)n, f) == (size_t)n &&
        !zip_open(z, data, (size_t)n)) {
        fclose(f);
        return data;
    }
    if (f) fclose(f);
    free(data);
    return NULL;
}

/* The Q-Sound chip ROM, dl-1425.bin (24 KB) from qsound.zip: its first 4,096
 * words, little-endian, as MAME loads them. */
static int load_dsp(const char *path, const Cps1Game *g, Cps1Rom *r, char *err, size_t errlen) {
    Zip z;
    uint8_t *data = open_beside(path, "qsound", &z), *dsp = NULL;
    const ZipEntry *e = data ? zip_find_crc(&z, 0xD6CF5EF5u, 0x6000) : NULL;
    int bad = !e || !(dsp = malloc(0x6000)) || zip_read(&z, e, dsp);
    if (bad) snprintf(err, errlen, "%s: %s needs qsound.zip beside it (dl-1425.bin, CRC d6cf5ef5)", path, g->id);
    else for (int i = 0; i < 4096; i++) r->dsp[i] = (uint16_t)(dsp[i * 2] | dsp[i * 2 + 1] << 8);
    if (data) zip_close(&z);
    free(dsp), free(data);
    return bad ? -1 : 0;
}

int cps1_open_in(const char *path, const uint8_t *data, size_t size, const Cps1Game *games, int n, Cps1Rom *r,
                 char *err, size_t errlen) {
    Zip z;
    const Cps1Game *g = zip_open(&z, data, size) ? NULL : cps1_match_in(&z, games, n);
    size_t base = strlen(path), end;
    while (base && path[base - 1] != '/' && path[base - 1] != '\\') base--;
    end = strlen(path) > base + 4 ? strlen(path) - 4 : base;
    for (int i = 0; g && i < n; i++)  /* a merged zip matches its clones too: the set named like the zip */
        if (strlen(games[i].id) == end - base && !strncmp(games[i].id, path + base, end - base) && own_files(&z, &games[i], NULL)) g = &games[i];
    if (!g) {
        if (z.entries) zip_close(&z);
        return snprintf(err, errlen, "%s: not a CPS-1 game this program knows", path), -1;
    }
    /* the zip, then "<folder>/<parent>.zip", then every zip of the folder: a chip by CRC wherever it is */
    char done[sizeof ((Cps1Game *)0)->files / sizeof (Cps1File)] = {0}, ppath[1024] = "", dir[1024];
    int bad = alloc_regions(g, r, err, errlen) || take(g, &z, r, done, err, errlen);
    zip_close(&z);
    if (!bad && g->parent && missing(g, done) >= 0) {
        snprintf(ppath, sizeof ppath, "%.*s%s.zip", (int)base, path, g->parent);
        bad = take_path(ppath, g, r, done, err, errlen);
    }
    snprintf(dir, sizeof dir, "%.*s", (int)base, path);
    if (!bad && missing(g, done) >= 0) bad = take_folder(dir, path, ppath, g, r, done, err, errlen);
    int i = bad ? -1 : missing(g, done);
    if (i >= 0) {
        bad = 1;
        if (g->parent)
            snprintf(err, errlen, "%s: %s lacks the file with CRC %08x; its parent %s.zip, or any zip holding it, beside it", path, g->id, (unsigned)g->files[i].crc, g->parent);
        else
            snprintf(err, errlen, "%s: %s lacks the file with CRC %08x; any zip holding it beside it", path, g->id, (unsigned)g->files[i].crc);
    }
    if (!bad) bad = finish(g, r, err, errlen) || (g->group == CPS1_QSOUND && load_dsp(path, g, r, err, errlen));
    if (bad) cps1_unload(r);
    return bad ? -1 : 0;
}

int cps1_open(const char *path, const uint8_t *data, size_t size, Cps1Rom *r, char *err, size_t errlen) {
    return cps1_open_in(path, data, size, cps1_games, cps1_game_count, r, err, errlen);
}
