/* gbrecomp: the Game Boy recompiler (build-time tool).
 *   gbrecomp ROM -o OUT.c [--hints GAME.toml]... [--misses TRACE]... [--no-rom]
 *                                   recompile ROM; TRACE: gb_headless --misses output or a
 *                                   program's NAME.misses (each "MISS $PC bank B" an entry);
 *                                   --no-rom: do not embed the ROM (the program needs the file)
 * Hints (systems/gb/games/NAME.toml, TOML subset, as the NES's):
 *   rom_fnv1a = "1A2B3C4D"          # the dump they were made for (a warning if it differs)
 *   entries = [0x0150, 0x0200]      # code in bank 0, $0000-$3FFF
 *   banked = [[3, 0x4100]]          # [ROM bank, address $0000-$7FFF] of code
 *   data = [[3, 0x5000, 0x5100]]    # [ROM bank, first, end) never decoded as code
 *
 *   gbrecomp --ops                  every opcode: "CB? XX size name" (tests) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "cart.h"
#include "recomp.h"

static Region *region(Region **regions, const GbCart *cart, int bank, int window) {
    Region **r = &regions[bank * 2 + window];
    if (!*r) {
        if (!(*r = calloc(1, sizeof **r))) { fprintf(stderr, "gbrecomp: out of memory\n"); exit(2); }
        (*r)->bank = bank, (*r)->window = window;
        memcpy((*r)->mem + window * 0x4000, cart->rom + (size_t)bank * 0x4000, 0x4000);
    }
    return *r;
}

typedef struct { unsigned v[16384]; size_t n; } Ints;

static void bad(const char *path, const char *what) {
    fprintf(stderr, "%s: %s\n", path, what);
    exit(2);
}

/* The integers of `key = [...]` (nested arrays flattened); none if absent. */
static void hint_ints(const char *text, const char *path, const char *key, Ints *out) {
    size_t n = strlen(key);
    const char *p = text;
    for (; (p = strstr(p, key)); p += n) {
        const char *q = p + n;
        while (*q == ' ' || *q == '\t') q++;
        if ((p == text || p[-1] == '\n') && *q == '=') { p = q + 1; break; }
    }
    if (!p) return;
    while (*p == ' ' || *p == '\t') p++;
    if (*p != '[') bad(path, "a key is not an array");
    for (int depth = 0; *p;) {
        if (*p == '[') depth++, p++;
        else if (*p == ']') { p++; if (--depth == 0) return; }
        else if (*p >= '0' && *p <= '9') {
            char *end;
            if (out->n == sizeof out->v / sizeof *out->v) bad(path, "too many numbers in a key");
            out->v[out->n++] = (unsigned)strtoul(p, &end, 0);
            p = end;
        } else if (strchr(" \t\r\n,", *p)) p++;
        else bad(path, "unexpected character in an array");
    }
    bad(path, "unterminated array");
}

/* Hints into the regions; a missing file is fine (games/NAME.toml may not exist). */
static void load_hints(const char *path, Region **regions, const GbCart *cart, int nbanks) {
    FILE *f = fopen(path, "rb");
    if (!f) return;
    char *text = calloc(1, 1 << 20);
    size_t n = text ? fread(text, 1, (1 << 20) - 1, f) : 0;
    if (!text || ferror(f)) { perror(path); exit(2); }
    (void)n;  /* NUL-terminated by calloc */
    fclose(f);
    for (char *p = text; (p = strchr(p, '#'));)  /* comments (no '#' inside the strings we use) */
        while (*p && *p != '\n') *p++ = ' ';
    const char *h = strstr(text, "rom_fnv1a");
    unsigned want;
    if (h && (h = strchr(h, '"')) && sscanf(h, "\"%8x\"", &want) == 1 && want != fnv1a(cart->rom, cart->rom_size))
        fprintf(stderr, "gbrecomp: warning: %s is for another dump (rom_fnv1a %08X); entries may miss\n", path, want);
    Ints e = {0}, b = {0}, d = {0};
    hint_ints(text, path, "entries", &e);
    hint_ints(text, path, "banked", &b);
    hint_ints(text, path, "data", &d);
    if (b.n % 2 || d.n % 3) bad(path, "banked needs [bank, address], data [bank, first, end]");
    for (size_t i = 0; i < e.n; i++) {
        if (e.v[i] >= 0x4000) bad(path, "entries are bank 0 addresses below $4000 (use banked)");
        region(regions, cart, 0, 0)->entries[e.v[i]] = 1;
    }
    for (size_t i = 0; i < b.n; i += 2) {
        if (b.v[i] >= (unsigned)nbanks || b.v[i + 1] >= 0x8000) bad(path, "banked: bank or address outside the ROM");
        region(regions, cart, (int)b.v[i], (int)(b.v[i + 1] >> 14))->entries[b.v[i + 1]] = 1;
    }
    for (size_t i = 0; i < d.n; i += 3) {
        if (d.v[i] >= (unsigned)nbanks || d.v[i + 1] > d.v[i + 2] || d.v[i + 2] > 0x8000) bad(path, "data: bad range");
        for (unsigned a = d.v[i + 1]; a < d.v[i + 2]; a++) region(regions, cart, (int)d.v[i], (int)(a >> 14))->data[a] = 1;
    }
    free(text);
}

static int recompile(int argc, char **argv) {
    const char *rom_path = argv[1], *out = NULL;
    int embed = 1;
    for (int i = 2; i < argc; i++)
        if (!strcmp(argv[i], "-o") && i + 1 < argc) out = argv[++i];
        else if (!strcmp(argv[i], "--no-rom")) embed = 0;
        else if ((!strcmp(argv[i], "--misses") || !strcmp(argv[i], "--hints")) && i + 1 < argc) i++;  /* read below, once the ROM is in */
        else { fprintf(stderr, "gbrecomp: unknown option %s\n", argv[i]); return 2; }
    if (!out) { fprintf(stderr, "gbrecomp: -o OUT.c is needed\n"); return 2; }
    size_t size;
    uint8_t *data = file_read(rom_path, &size);
    if (!data) { perror(rom_path); return 2; }
    static GbCart cart;  /* the ROM as the runtime loads it (padded to a power of two) */
    char err[128];
    if (gb_cart_load(&cart, data, (size_t)size, err, sizeof err) != 0) { fprintf(stderr, "%s: %s\n", rom_path, err); return 2; }
    free(data);
    int nbanks = (int)(cart.rom_size / 0x4000);
    Region **regions = calloc((size_t)nbanks * 2, sizeof *regions);
    /* bank 0: the reset vector, RST and interrupt vectors */
    Region *r0 = region(regions, &cart, 0, 0);
    r0->entries[0x100] = 1;
    for (int v = 0; v <= 0x60; v += 8) r0->entries[v] = 1;
    for (int i = 2; i < argc; i++)
        if (!strcmp(argv[i], "--hints")) load_hints(argv[++i], regions, &cart, nbanks);
    long misses = 0;
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--misses")) continue;
        FILE *m = fopen(argv[++i], "r");
        if (!m) { perror(argv[i]); return 2; }
        char line[128];
        unsigned pc, bank;
        while (fgets(line, sizeof line, m))
            if (sscanf(line, "MISS $%x bank %u", &pc, &bank) == 2 && pc < 0x8000 && bank < (unsigned)nbanks)
                region(regions, &cart, (int)bank, (int)(pc >> 14))->entries[pc] = 1, misses++;
        fclose(m);
    }
    for (int r = 0; r < nbanks * 2; r++)
        if (regions[r]) explore(regions[r]);
    const char *name = rom_path;
    for (const char *p = rom_path; *p; p++)
        if (*p == '/' || *p == '\\') name = p + 1;
    Buf o = {0};
    emit_program(&o, regions, nbanks, name, cart.rom, cart.rom_size, embed);
    buf_write_file(out, &o);
    long ninstr = 0, nregions = 0;
    for (int r = 0; r < nbanks * 2; r++) {
        if (!regions[r]) continue;
        nregions++;
        for (uint32_t a = 0; a < 0x10000; a++) ninstr += regions[r]->instr[a];
    }
    printf("gbrecomp: %s: %ld instructions in %ld bank regions (%ld trace entries)\n", name, ninstr, nregions, misses);
    return 0;
}

int main(int argc, char **argv) {
    if (argc == 2 && !strcmp(argv[1], "--ops")) {
        Lines l;
        char name[32];
        for (int cb = 0; cb < 2; cb++)
            for (int i = 0; i < 256; i++) {
                sm83_body(i, cb, &l, name, sizeof name);
                printf("%s%02X %d %s\n", cb ? "CB" : "", i, cb ? 2 : sm83_size(i), name);
            }
        return 0;
    }
    if (argc >= 2 && argv[1][0] != '-') return recompile(argc, argv);
    fprintf(stderr, "usage: gbrecomp ROM -o OUT.c [--hints GAME.toml]... [--misses TRACE]... [--no-rom] | --ops\n");
    return 2;
}
