/* nesrecomp: recompile an NES ROM to C (docs/architecture.md).
 *
 *   nesrecomp ROM -o OUT.c [--hints GAME.toml]... [--misses RUN.txt]... [--save-hints OUT.toml]
 *             [--no-rom]               do not embed the ROM (the program then needs the file)
 *             [--bios disksys.rom]     ROM is a Famicom Disk System image (.fds)
 *   nesrecomp --ops                    the opcode table, one line per opcode (tests)
 *   nesrecomp --info ROM               iNES header summary (tests)
 *
 * ROM may also be the Famicom Disk System BIOS (8 KB): its code at $E000 is
 * recompiled, and the program it builds plays .fds disk images with it.
 * With --bios, ROM is an .fds image: the BIOS is recompiled and embedded,
 * and so is the code of each file on the disk that is loaded into RAM
 * (from $0200), wherever the hints or --misses show it ran. A disk file's
 * code only runs while RAM holds it (recomp_rt.h), since another file may
 * be loaded at the same address later.
 *
 * GAME.toml (all keys optional; only this subset of TOML is read):
 *   prg_fnv1a = "65D2E392"           # the dump the hints were made for
 *   entries   = [0xCE67, ...]        # extra entry points in assumed-bank windows
 *   banked    = [[5, 0x8123], ...]   # [8 KB PRG bank, address] entry points
 *   no_return = [0xD123, ...]        # subroutines that never return to the caller
 *   ram       = [[0x1A2B3C4D, 0x6123], ...]  # [FNV-1a of an FDS disk file, address] entry points
 *
 * --misses takes the output of `nes_headless ROM --misses` (addresses the
 * runtime interpreted). An interpreter-only nes_headless reports every
 * instruction it ran, so one run is a complete trace of that session. The
 * first address of each run of misses becomes a banked entry (FDS: RAM
 * misses carry the instruction's bytes, which tell the disk file); --save-hints
 * writes the merged hints (marked 'runtime') for games/<name>.toml. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>

#include "file.h"
#include "cart.h"
#include "recomp.h"

typedef struct {
    size_t n, cap;
    uint32_t *v;
} List;

static void push(List *l, uint32_t x) {
    if (l->n == l->cap) l->v = realloc(l->v, (l->cap = l->cap * 2 + 16) * sizeof *l->v);
    l->v[l->n++] = x;
}

typedef struct {
    List entries, no_return, banked;  /* banked: bank << 16 | address */
    List ram;                         /* pairs: disk file hash, address */
    char prg_fnv1a[16];
} Hints;

/* A file of an FDS disk that may hold code: loaded into RAM from $0200
 * ($0200-$07FF or $6000-$DFFF; below is the stack). One per content. */
typedef struct {
    uint32_t hash, addr, size;
    const uint8_t *data;
} DiskFile;

enum { MAX_FILES = 1024 };

static int disk_files(const uint8_t *d, size_t size, DiskFile *out) {
    if (size >= 16 && !memcmp(d, "FDS\x1a", 4)) d += 16, size -= 16;
    int n = 0;
    for (size_t s = 0; s + FDS_SIDE <= size; s += FDS_SIDE) {
        const uint8_t *p = d + s;
        /* block 1 (56 bytes), block 2 (2), then file header (16) + data (1 + size) pairs */
        for (size_t j = 58; j + 17 <= FDS_SIDE && p[j] == 3 && p[j + 16] == 4;) {
            uint32_t addr = p[j + 11] | p[j + 12] << 8, len = p[j + 13] | p[j + 14] << 8, end = addr + len;
            int prg = p[j + 15] == 0;
            const uint8_t *data = p + j + 17;
            if (j + 17 + len > FDS_SIDE) break;
            j += 17 + len;
            if (!prg || !len || !((addr >= 0x200 && end <= 0x800) || (addr >= 0x6000 && end <= 0xE000))) continue;
            uint32_t h = fnv1a(data, len);
            int dup = 0;
            for (int i = 0; i < n; i++) dup |= out[i].hash == h && out[i].addr == addr;
            if (!dup && n < MAX_FILES) out[n++] = (DiskFile){h, addr, len, data};
        }
    }
    return n;
}

static uint8_t *read_file(const char *path, size_t *size) {
    uint8_t *buf = file_read(path, size);  /* a zero byte past the end: hints files are text */
    if (!buf) { perror(path); exit(2); }
    return buf;
}

static int cmp_u32(const void *a, const void *b) {
    uint32_t x = *(const uint32_t *)a, y = *(const uint32_t *)b;
    return (x > y) - (x < y);
}

/* ---- hints (TOML subset) ---- */

/* Start of the value of `key = ` at the beginning of a line, or NULL. */
static const char *toml_value(const char *text, const char *key) {
    size_t n = strlen(key);
    for (const char *p = text; (p = strstr(p, key)); p += n) {
        if (p != text && p[-1] != '\n') continue;
        const char *q = p + n;
        while (*q == ' ' || *q == '\t') q++;
        if (*q != '=') continue;
        for (q++; *q == ' ' || *q == '\t'; q++) {}
        return q;
    }
    return NULL;
}

/* All integers of the [...] value at p (nested arrays flattened). */
static void toml_ints(const char *p, List *out, const char *path, const char *key) {
    if (!p) return;
    if (*p != '[') { fprintf(stderr, "%s: %s is not an array\n", path, key); exit(2); }
    for (int depth = 0; *p; ) {
        if (*p == '[') depth++, p++;
        else if (*p == ']') { p++; if (--depth == 0) return; }
        else if (*p >= '0' && *p <= '9') {
            char *end;
            int hex = p[0] == '0' && (p[1] == 'x' || p[1] == 'X');
            push(out, (uint32_t)strtoul(hex ? p + 2 : p, &end, hex ? 16 : 10));
            p = end;
        } else if (strchr(" \t\r\n,", *p)) p++;
        else { fprintf(stderr, "%s: unexpected '%c' in %s\n", path, *p, key); exit(2); }
    }
    fprintf(stderr, "%s: unterminated %s\n", path, key);
    exit(2);
}

static void load_hints(const char *path, Hints *h) {
    size_t size;
    char *text = (char *)read_file(path, &size);
    /* drop comments (no '#' inside the strings we use) */
    for (char *p = text; (p = strchr(p, '#'));)
        while (*p && *p != '\n') *p++ = ' ';
    toml_ints(toml_value(text, "entries"), &h->entries, path, "entries");
    toml_ints(toml_value(text, "no_return"), &h->no_return, path, "no_return");
    List pairs = {0};
    toml_ints(toml_value(text, "banked"), &pairs, path, "banked");
    if (pairs.n % 2) { fprintf(stderr, "%s: banked needs [bank, address] pairs\n", path); exit(2); }
    for (size_t i = 0; i < pairs.n; i += 2) push(&h->banked, pairs.v[i] << 16 | (pairs.v[i + 1] & 0xFFFF));
    free(pairs.v);
    size_t had = h->ram.n;
    toml_ints(toml_value(text, "ram"), &h->ram, path, "ram");
    if ((h->ram.n - had) % 2) { fprintf(stderr, "%s: ram needs [file hash, address] pairs\n", path); exit(2); }
    const char *v = toml_value(text, "prg_fnv1a");
    if (v && sscanf(v, "\"%8[0-9A-Fa-f]\"", h->prg_fnv1a) != 1) { fprintf(stderr, "%s: bad prg_fnv1a\n", path); exit(2); }
    for (char *p = h->prg_fnv1a; *p; p++) *p = (char)toupper((unsigned char)*p);
    qsort(h->banked.v, h->banked.n, sizeof *h->banked.v, cmp_u32);
    free(text);
}

static int contains(const List *l, uint32_t x) {
    for (size_t i = 0; i < l->n; i++)
        if (l->v[i] == x) return 1;
    return 0;
}

static int contains_pair(const List *l, uint32_t x, uint32_t y) {
    for (size_t i = 0; i + 1 < l->n; i += 2)
        if (l->v[i] == x && l->v[i + 1] == y) return 1;
    return 0;
}

static void render_hints(Buf *o, const Hints *h, const List *found, const List *ram_found, uint32_t prg_hash) {
    bprintf(o, "# Recompiler hints (see recomp/main.c).\n");
    bprintf(o, "# Entries marked 'runtime' were found by running the game (nesrecomp --misses).\n");
    bprintf(o, "prg_fnv1a = \"%08X\"  # the dump these hints belong to\n", prg_hash);
    bprintf(o, "entries = [\n");
    for (size_t i = 0; i < h->entries.n; i++) bprintf(o, "    0x%04X,\n", h->entries.v[i]);
    bprintf(o, "]\nbanked = [  # [8 KB PRG bank, address]\n");
    for (size_t i = 0; i < h->banked.n; i++) {
        uint32_t x = h->banked.v[i];
        bprintf(o, "    [%u, 0x%04X],%s\n", x >> 16, x & 0xFFFF, contains(found, x) ? "  # runtime" : "");
    }
    bprintf(o, "]\n");
    if (h->ram.n) {
        bprintf(o, "ram = [  # [FDS disk file FNV-1a, address]\n");
        for (size_t i = 0; i + 1 < h->ram.n; i += 2)
            bprintf(o, "    [0x%08X, 0x%04X],%s\n", h->ram.v[i], h->ram.v[i + 1],
                    contains_pair(ram_found, h->ram.v[i], h->ram.v[i + 1]) ? "  # runtime" : "");
        bprintf(o, "]\n");
    }
    if (h->no_return.n) {
        bprintf(o, "no_return = [");
        for (size_t i = 0; i < h->no_return.n; i++) bprintf(o, i ? ", 0x%04X" : "0x%04X", h->no_return.v[i]);
        bprintf(o, "]\n");
    }
}

/* Merge the chain starts of a --misses file into h->banked (and h->ram for
 * the disk files); new ones go to `found` (`ram_found`). */
static void add_misses(const char *path, const Rom *r, Hints *h, List *found, const DiskFile *files, int nfiles,
                       List *ram_found) {
    size_t size;
    char *text = (char *)read_file(path, &size);
    int nbanks = (int)(r->prg_size / 0x2000), k = unit_windows(r), layout[4];
    assumed_layout(r, layout);
    /* misses per (bank, window) */
    AddrSet **groups = calloc((size_t)nbanks * 4, sizeof *groups);
    long nrom = 0, nram = 0, nfile = 0;
    AddrSet **in_file = calloc((size_t)nfiles + 1, sizeof *in_file);
    for (char *line = text, *next; line; line = next) {
        if ((next = strchr(line, '\n'))) next++;
        unsigned addr, count, bank, bytes;
        char ram[8];
        if (sscanf(line, "MISS $%4x %u (RAM %6x)", &addr, &count, &bytes) == 3) {  /* FDS: with its bytes */
            uint8_t k[3] = {(uint8_t)(bytes >> 16), (uint8_t)(bytes >> 8), (uint8_t)bytes};
            int len = OPS[k[0]].size, hit = 0;
            for (int f = 0; f < nfiles; f++) {
                const DiskFile *F = &files[f];
                if (addr < F->addr || addr + len > F->addr + F->size || memcmp(F->data + addr - F->addr, k, len)) continue;
                if (!in_file[f]) in_file[f] = calloc(1, sizeof **in_file);
                in_file[f]->b[addr] = 1;
                hit = 1;
            }
            nfile += hit, nram += !hit;
        } else if (sscanf(line, "MISS $%4x %u bank %u", &addr, &count, &bank) == 3 && addr >= 0x8000 &&
            (int)bank < nbanks) {
            int key = (int)bank * 4 + window_of(addr);
            if (!groups[key]) groups[key] = calloc(1, sizeof **groups);
            nrom += !groups[key]->b[addr];
            groups[key]->b[addr] = 1;
        } else if (sscanf(line, "MISS $%4x %u (%3s", &addr, &count, ram) == 3) {
            nram++;
        }
    }
    static uint8_t mem[0x10000];
    static AddrSet starts;
    long nnew = 0;
    for (int f = 0; f < nfiles; f++) {
        if (!in_file[f]) continue;
        const DiskFile *F = &files[f];
        memset(mem, 0, sizeof mem);
        memcpy(mem + F->addr, F->data, F->size);
        chain_starts(mem, in_file[f], &starts);
        for (uint32_t a = F->addr; a < F->addr + F->size; a++)
            if (starts.b[a] && !contains_pair(&h->ram, F->hash, a))
                push(&h->ram, F->hash), push(&h->ram, a), push(ram_found, F->hash), push(ram_found, a), nnew++;
        free(in_file[f]);
    }
    free(in_file);
    for (int key = 0; key < nbanks * 4; key++) {
        if (!groups[key]) continue;
        int b = key / 4, w = key % 4, w0 = w - w % k, b0 = b - w % k, lay[4];
        memcpy(lay, layout, sizeof lay);
        for (int i = 0; i < k; i++) lay[w0 + i] = b0 + i;
        view(r, lay, mem);
        chain_starts(mem, groups[key], &starts);
        for (uint32_t a = 0x8000; a < 0x10000; a++) {
            uint32_t x = (uint32_t)b << 16 | a;
            if (starts.b[a] && !contains(&h->banked, x)) push(&h->banked, x), push(found, x), nnew++;
        }
        free(groups[key]);
    }
    free(groups);
    qsort(h->banked.v, h->banked.n, sizeof *h->banked.v, cmp_u32);
    fprintf(stderr, "%s: %ld ROM misses, %ld RAM (%ld in disk files); %ld new entries\n", path, nrom,
            nram + nfile, nfile, nnew);
    free(text);
}

/* ---- exploration ---- */

static void vectors(const Rom *r, uint16_t v[3]) {  /* NMI, RESET, IRQ: last 6 bytes of PRG */
    const uint8_t *p = r->prg + r->prg_size - 6;
    for (int i = 0; i < 3; i++) v[i] = (uint16_t)(p[i * 2] | p[i * 2 + 1] << 8);
}

/* Decode every reachable region: one over $8000-$FFFF for mappers that never
 * switch PRG, else one per (bank, unit) so code never assumes a bank it
 * cannot check. Returns the number of regions, sorted by (bank, window). */
static int explore_regions(const Rom *r, const Hints *h, Region **out) {
    int layout[4], nbanks = (int)(r->prg_size / 0x2000), k = unit_windows(r);
    AddrSet *no_return = calloc(1, sizeof *no_return);
    for (size_t i = 0; i < h->no_return.n; i++) no_return->b[h->no_return.v[i] & 0xFFFF] = 1;
    if (assumed_layout(r, layout) != 0) {
        fprintf(stderr, "mapper %d not supported by the recompiler\n", r->mapper);
        exit(2);
    }
    uint16_t vec[3];
    vectors(r, vec);
    if (!prg_bank_reg(r)) {
        Region *R = *out = calloc(1, sizeof *R);
        R->prog = calloc(1, sizeof *R->prog);
        R->mem = malloc(0x10000);
        memcpy(R->banks, layout, sizeof layout);
        view(r, layout, R->mem);
        /* from the first window with ROM (FDS: $E000; below it is RAM) */
        uint32_t lo = 0x8000;
        while (lo < 0x10000 && layout[window_of(lo)] < 0) lo += 0x2000;
        for (int i = 0; i < 3; i++) R->prog->entries.b[vec[i]] |= vec[i] >= lo;
        for (size_t i = 0; i < h->entries.n; i++) {
            uint32_t a = h->entries.v[i] & 0xFFFF;
            R->prog->entries.b[a] |= a >= lo;
        }
        for (size_t i = 0; i < h->banked.n; i++) {
            uint32_t a = h->banked.v[i] & 0xFFFF;
            R->prog->entries.b[a] |= a >= lo;
        }
        explore(R->prog, R->mem, lo, 0x10000, no_return);
        free(no_return);
        return 1;
    }
    /* seeds[(bank of the unit's first window) * 64K + address] */
    uint8_t *seeds = calloc((size_t)nbanks << 16, 1), *done = calloc((size_t)nbanks << 16, 1);
    Region *regions = calloc((size_t)nbanks * 4, sizeof *regions);  /* by bank0 * 4 + w0 */
#define ADD(addr, bank) do {                                                         \
        uint32_t a_ = (addr);                                                        \
        int b_ = (bank), w_ = window_of(a_);                                         \
        if (a_ < 0x8000) break;                    /* RAM: interpreter only */       \
        if (b_ < 0) b_ = layout[w_];               /* bank unknown: runtime/hints */ \
        if (b_ < 0 || b_ - w_ % k < 0 || b_ - w_ % k + k > nbanks) break;            \
        seeds[(size_t)(b_ - w_ % k) << 16 | a_] = 1;                                 \
    } while (0)
    for (int i = 0; i < 3; i++) ADD(vec[i], -1);
    for (size_t i = 0; i < h->entries.n; i++) ADD(h->entries.v[i] & 0xFFFF, -1);
    for (size_t i = 0; i < h->banked.n; i++) ADD(h->banked.v[i] & 0xFFFF, (int)(h->banked.v[i] >> 16));
    uint8_t *touched = malloc((size_t)nbanks * 4);
    for (int again = 1; again;) {
        again = 0;
        memset(touched, 0, (size_t)nbanks * 4);
        for (size_t s = 0; s < (size_t)nbanks << 16; s++) {
            if (!seeds[s] || done[s]) continue;
            done[s] = 1;
            int bank0 = (int)(s >> 16), a = (int)(s & 0xFFFF), w0 = window_of(a) - window_of(a) % k;
            Region *R = &regions[bank0 * 4 + w0];
            if (!R->prog) {
                R->prog = calloc(1, sizeof *R->prog);
                R->mem = malloc(0x10000);
                int lay[4];
                memcpy(lay, layout, sizeof lay);
                for (int w = 0; w < 4; w++) R->banks[w] = -1;
                for (int i = 0; i < k; i++) lay[w0 + i] = R->banks[w0 + i] = bank0 + i;
                view(r, lay, R->mem);
            }
            R->prog->entries.b[a] = 1;
            touched[bank0 * 4 + w0] = 1;
        }
        for (int key = 0; key < nbanks * 4; key++) {
            if (!touched[key]) continue;
            Region *R = &regions[key];
            uint32_t lo = 0x8000 + (key % 4) * 0x2000, hi = lo + k * 0x2000;
            explore(R->prog, R->mem, lo, hi, no_return);
            for (uint32_t t = 0; t < 0x10000; t++)
                if (R->prog->external.b[t] && !(t >= lo && t < hi)) ADD(t, -1);  /* inside: straddles the unit's end */
            again = 1;
        }
    }
#undef ADD
    int n = 0;
    for (int key = 0; key < nbanks * 4; key++)
        if (regions[key].prog) regions[n++] = regions[key];
    *out = regions;
    free(seeds), free(done), free(touched), free(no_return);
    return n;
}

static const char *basename_of(const char *path) {
    const char *b = path;
    for (const char *p = path; *p; p++)
        if (*p == '/' || *p == '\\') b = p + 1;
    return b;
}

static int load_rom(const char *path, Cart *cart, uint8_t **file, size_t *size) {
    char err[128];
    *file = read_file(path, size);
    if (cart_is_fds(*file, *size)) {
        fprintf(stderr, "%s: a Famicom Disk System image: give the BIOS with --bios disksys.rom\n", path);
        return 2;
    }
    if (*size == 0x2000) {  /* no iNES file is 8 KB: the FDS BIOS, at $E000 */
        memset(cart, 0, sizeof *cart);
        cart->prg = *file;
        cart->prg_size = 0x2000;
        cart->mapper = 20;
        cart->chr_ram = 1;
        cart->mirroring = MIRROR_VERTICAL;
        return 0;
    }
    if (cart_load(cart, *file, *size, err, sizeof err) != 0) {
        fprintf(stderr, "%s: %s\n", path, err);
        return 2;
    }
    return 0;
}

static void summary(const Cart *c, char *out, size_t len) {
    static const char *const MIRROR[] = {"horizontal", "vertical", "four", "single-low", "single-high"};
    uint16_t v[3];
    Rom r = {c->prg, c->prg_size, c->mapper};
    vectors(&r, v);
    char chr[16];
    if (!c->chr_rom_size) snprintf(chr, sizeof chr, "RAM");
    else snprintf(chr, sizeof chr, c->chr_ram ? "%u KB + RAM" : "%u KB", c->chr_rom_size / 1024);
    snprintf(out, len, "mapper %d, PRG %u KB, CHR %s, %s mirroring, NMI=$%04X RESET=$%04X IRQ=$%04X",
             c->mapper, c->prg_size / 1024, chr, MIRROR[c->mirroring], v[0], v[1], v[2]);
}

static int usage(void) {
    fprintf(stderr, "usage: nesrecomp ROM -o OUT.c [--hints GAME.toml]... [--misses RUN.txt]... [--save-hints OUT.toml]\n"
                    "                 [--no-rom] [--bios disksys.rom]\n"
                    "       nesrecomp --ops | --info ROM\n");
    return 2;
}

int main(int argc, char **argv) {
    ops_init();
    Buf o = {0};
    if (argc == 2 && !strcmp(argv[1], "--ops")) {
        for (int i = 0; i < 256; i++)
            printf("%02X %s %s %d %d %d %d\n", i, OPS[i].mn, OPS[i].mode, OPS[i].size, OPS[i].cycles,
                   OPS[i].official, page_penalty(&OPS[i]));
        return 0;
    }
    Cart cart;
    uint8_t *file;
    size_t size;
    char text[160];
    if (argc == 3 && !strcmp(argv[1], "--info")) {
        if (load_rom(argv[2], &cart, &file, &size)) return 2;
        summary(&cart, text, sizeof text);
        printf("%s\n", text);
        return 0;
    }
    if (argc < 2 || argv[1][0] == '-') return usage();
    const char *rom_path = argv[1], *output = NULL, *save_hints = NULL, *bios_path = NULL;
    const char *misses[64], *hints_paths[8];
    int nmisses = 0, nhints = 0, embed = 1;
    for (int i = 2; i < argc; i++) {
        if (!strcmp(argv[i], "-o") && i + 1 < argc) output = argv[++i];
        else if (!strcmp(argv[i], "--hints") && i + 1 < argc && nhints < 8) hints_paths[nhints++] = argv[++i];
        else if (!strcmp(argv[i], "--bios") && i + 1 < argc) bios_path = argv[++i];
        else if (!strcmp(argv[i], "--misses") && i + 1 < argc && nmisses < 64) misses[nmisses++] = argv[++i];
        else if (!strcmp(argv[i], "--save-hints") && i + 1 < argc) save_hints = argv[++i];
        else if (!strcmp(argv[i], "--no-rom")) embed = 0;
        else return usage();
    }
    if (!output && !save_hints) return usage();
    if (load_rom(bios_path ? bios_path : rom_path, &cart, &file, &size)) return 2;
    uint8_t *disk = NULL;  /* --bios: the .fds image */
    size_t disk_size = 0;
    static DiskFile files[MAX_FILES];
    int nfiles = 0;
    if (bios_path) {
        if (size != 0x2000) { fprintf(stderr, "%s: not an 8 KB FDS BIOS\n", bios_path); return 2; }
        disk = read_file(rom_path, &disk_size);
        if (!cart_is_fds(disk, disk_size)) { fprintf(stderr, "%s: not an .fds disk image\n", rom_path); return 2; }
        nfiles = disk_files(disk, disk_size, files);
    }
    Rom rom = {cart.prg, cart.prg_size, cart.mapper};
    uint32_t prg_hash = fnv1a(cart.prg, cart.prg_size);
    Hints hints = {0};
    char want[16];
    snprintf(want, sizeof want, "%08X", prg_hash);
    for (int i = 0; i < nhints; i++) {
        FILE *f = fopen(hints_paths[i], "rb");  /* optional: games/<name>.toml may not exist yet */
        if (!f) continue;
        fclose(f);
        hints.prg_fnv1a[0] = 0;
        load_hints(hints_paths[i], &hints);
        if (hints.prg_fnv1a[0] && strcmp(hints.prg_fnv1a, want))
            fprintf(stderr, "warning: %s was made for another dump (PRG %s); its entries may be wrong here "
                            "(the runtime stays correct, misses go up)\n", hints_paths[i], hints.prg_fnv1a);
    }
    List found = {0}, ram_found = {0};
    for (int i = 0; i < nmisses; i++) add_misses(misses[i], &rom, &hints, &found, files, nfiles, &ram_found);
    if (save_hints) {
        render_hints(&o, &hints, &found, &ram_found, prg_hash);
        buf_write_file(save_hints, &o);
        o.len = 0;
    }
    if (!output) return 0;

    Region *regions;
    int n = explore_regions(&rom, &hints, &regions), nrom_regions = n;
    regions = realloc(regions, (size_t)(n + nfiles) * sizeof *regions);
    for (int f = 0; f < nfiles; f++) {  /* disk files: from their entries only */
        const DiskFile *F = &files[f];
        Region *R = &regions[n];
        memset(R, 0, sizeof *R);
        R->ram = 1, R->file = f, R->lo = F->addr, R->hi = F->addr + F->size;
        R->prog = calloc(1, sizeof *R->prog);
        R->mem = calloc(1, 0x10000);
        memcpy(R->mem + F->addr, F->data, F->size);
        int any = 0;
        for (size_t i = 0; i + 1 < hints.ram.n; i += 2)
            if (hints.ram.v[i] == F->hash && hints.ram.v[i + 1] >= R->lo && hints.ram.v[i + 1] < R->hi)
                R->prog->entries.b[hints.ram.v[i + 1]] = 1, any = 1;
        if (!any) { free(R->prog), free(R->mem); continue; }
        explore(R->prog, R->mem, R->lo, R->hi, NULL);
        n++;
    }
    const char *name = basename_of(rom_path);
    const uint8_t *image = disk ? disk : cart.mapper == 20 ? NULL : file;  /* the BIOS goes in `bios` */
    size_t image_size = disk ? disk_size : size;
    emit_program(&o, regions, n, name, prg_hash, (int)(cart.prg_size / 0x2000), prg_bank_reg(&rom),
                 embed ? image : NULL, embed && image ? image_size : 0, cart.mapper == 20 ? 0xE445 : 0,
                 cart.mapper == 20 ? cart.prg : NULL);
    buf_write_file(output, &o);
    long ninstr = 0, nindirect = 0, nram = 0;
    for (int i = 0; i < n; i++)
        for (uint32_t a = 0; a < 0x10000; a++) {
            ninstr += regions[i].prog->instrs.b[a], nindirect += regions[i].prog->indirect.b[a];
            nram += regions[i].ram && regions[i].prog->instrs.b[a];
        }
    summary(&cart, text, sizeof text);
    printf("%s: %s\n  %ld instructions in %d regions, %ld indirect jumps -> %s\n", name, text, ninstr, n,
           nindirect, output);
    if (disk)
        printf("  disk: %d files that may hold code; %ld instructions in %d of them\n", nfiles, nram,
               n - nrom_regions);
    return 0;
}
