#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c6502.h"
#include "cart.h"
#include "loader.h"

static void string_literal(Buf *out, const char *value) {
    bprintf(out, "\"");
    for (; *value; value++) {
        unsigned char c = (unsigned char)*value;
        if (c == '"' || c == '\\') bprintf(out, "\\%c", c);
        else if (c < 32 || c >= 127) bprintf(out, "\\%03o", c);
        else bprintf(out, "%c", c);
    }
    bprintf(out, "\"");
}

static int mapper_value(const char *value) {
    static const char *const names[] = {"auto", "2k", "4k", "f8", "f6", "f4"};
    for (int i = 0; i < 6; i++) if (!strcmp(value, names[i])) return i;
    return -1;
}

static int read_hints(const char *path, int *mapper, int *pal, int auto_pal) {
    FILE *file = fopen(path, "r");
    if (!file) { fprintf(stderr, "cannot open hints %s\n", path); return -1; }
    char line[512], key[32], value[32];
    int failed = 0;
    while (fgets(line, sizeof line, file)) {
        if (sscanf(line, " %31[a-zA-Z_]", key) != 1) continue;
        if (strcmp(key, "mapper") && strcmp(key, "region")) continue;
        if (sscanf(line, " %31[a-zA-Z_] = \"%31[^\"]\"", key, value) != 2) { failed = 1; break; }
        if (!strcmp(key, "mapper")) {
            *mapper = mapper_value(value);
            if (*mapper < 0) failed = 1;
        } else if (!strcmp(key, "region")) {
            if (!strcmp(value, "ntsc")) *pal = 0;
            else if (!strcmp(value, "pal")) *pal = 1;
            else if (!strcmp(value, "auto")) *pal = auto_pal;
            else failed = 1;
        }
        if (failed) break;
    }
    if (ferror(file)) failed = 1;
    fclose(file);
    if (failed) fprintf(stderr, "invalid Atari configuration in %s\n", path);
    return failed ? -1 : 0;
}

static int safe_instruction(unsigned offset, const Op *op, unsigned banks) {
    if (offset + op->size > 4096) return 0;
    if (banks > 1) {
        unsigned first = banks == 2 ? 0xFF8 : banks == 4 ? 0xFF6 : 0xFF4;
        for (unsigned i = 0; i < op->size; i++)
            if (offset + i >= first && offset + i < first + banks) return 0;
    }
    return 1;
}

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "usage: atari2600recomp ROM -o FILE [--trace FILE] [--hints FILE] [--no-rom] [--region ntsc|pal] [--mapper TYPE]\n");
        return 2;
    }
    const char *path = argv[1], *output = NULL, *trace_path = NULL;
    int embed = 1, mapper = A26_CART_AUTO;
    int pal = strstr(path, "(Europe)") != NULL || strstr(path, "(PAL)") != NULL;
    for (int i = 2; i < argc; i++) {
        if (!strcmp(argv[i], "-o") && i + 1 < argc) output = argv[++i];
        else if (!strcmp(argv[i], "--trace") && i + 1 < argc) trace_path = argv[++i];
        else if (!strcmp(argv[i], "--hints") && i + 1 < argc) {
            int auto_pal = strstr(path, "(Europe)") != NULL || strstr(path, "(PAL)") != NULL;
            if (read_hints(argv[++i], &mapper, &pal, auto_pal)) return 2;
        }
        else if (!strcmp(argv[i], "--no-rom")) embed = 0;
        else if (!strcmp(argv[i], "--region") && i + 1 < argc) {
            const char *value = argv[++i];
            if (!strcmp(value, "ntsc")) pal = 0;
            else if (!strcmp(value, "pal")) pal = 1;
            else if (!strcmp(value, "auto")) pal = strstr(path, "(Europe)") != NULL || strstr(path, "(PAL)") != NULL;
            else { fprintf(stderr, "invalid region %s\n", value); return 2; }
        } else if (!strcmp(argv[i], "--mapper") && i + 1 < argc) {
            mapper = mapper_value(argv[++i]);
            if (mapper < 0) { fprintf(stderr, "invalid mapper\n"); return 2; }
        } else { fprintf(stderr, "unknown option %s\n", argv[i]); return 2; }
    }
    if (!output) { fprintf(stderr, "missing -o\n"); return 2; }
    uint8_t *rom, trace[8 * 4096] = {0};
    size_t size;
    char err[256];
    if (a26_load_rom(path, &rom, &size, err, sizeof err)) { fprintf(stderr, "%s\n", err); return 1; }
    A26Cart cart;
    if (a26_cart_init(&cart, rom, size, (A26CartType)mapper)) {
        fprintf(stderr, "unsupported cartridge\n"); free(rom); return 1;
    }
    if (!a26_cart_recompilable(cart.type)) {  /* sliced banks and cartridge RAM: the emulator runs these */
        fprintf(stderr, "this cartridge's bankswitching is not recompiled yet: play it in the emulator\n");
        free(rom); return 1;
    }
    if (trace_path) {
        FILE *f = fopen(trace_path, "rb");
        if (!f || fread(trace, 1, sizeof trace, f) != sizeof trace) {
            fprintf(stderr, "invalid trace %s\n", trace_path);
            if (f) fclose(f);
            free(rom); return 1;
        }
        fclose(f);
    }
    unsigned mask = cart.type == A26_CART_2K ? 0x7FF : 0xFFF;
    size_t base = (cart.banks - 1) * 4096;
    unsigned reset = rom[base + (0xFFC & mask)] | (unsigned)rom[base + (0xFFD & mask)] << 8;
    if (reset & 0x1000) trace[(cart.banks - 1) * 4096 + (reset & 0xFFF)] = 1;
    ops_init();
    Buf out = {0};
    bprintf(&out, "/* Generated Atari 2600 code. */\n#include \"cpu6502_ops.h\"\n#include \"recomp.h\"\n\n");
    unsigned generated = 0;
    for (unsigned bank = 0; bank < cart.banks; bank++) {
        for (unsigned offset = 0; offset < 4096; offset++) {
            if (!trace[bank * 4096 + offset]) continue;
            const Op *op = &OPS[rom[bank * 4096 + (offset & mask)]];
            if (!safe_instruction(offset, op, cart.banks)) continue;
            bprintf(&out, "static void b%u_%03x(Cpu *c) {\n    (void)rd(c, c->pc++);\n", bank, offset);
            Lines lines;
            body(op, &lines);
            for (int i = 0; i < lines.n; i++) if (*lines.s[i]) template_plain(&out, "    ", lines.s[i]);
            bprintf(&out, "}\n");
            generated++;
        }
    }
    bprintf(&out, "static A26RecompFn lookup(unsigned bank, unsigned offset) {\n    switch (bank * 4096 + offset) {\n");
    for (unsigned bank = 0; bank < cart.banks; bank++) {
        for (unsigned offset = 0; offset < 4096; offset++) {
            if (!trace[bank * 4096 + offset]) continue;
            const Op *op = &OPS[rom[bank * 4096 + (offset & mask)]];
            if (safe_instruction(offset, op, cart.banks))
                bprintf(&out, "    case %u: return b%u_%03x;\n", bank * 4096 + offset, bank, offset);
        }
    }
    bprintf(&out, "    default: return NULL;\n    }\n}\n");
    if (embed) {
        bprintf(&out, "static const uint8_t rom_data[] = {\n");
        for (size_t i = 0; i < size; i++) bprintf(&out, "%s0x%02x,", i % 16 ? "" : "\n", rom[i]);
        bprintf(&out, "\n};\n");
    }
    uint32_t hash = 2166136261u;
    for (size_t i = 0; i < size; i++) hash = (hash ^ rom[i]) * 16777619u;
    bprintf(&out, "static const A26RecompProgram program = {0x%08x, %s, %zu, ", hash,
            embed ? "rom_data" : "NULL", size);
    const char *name = path;
    for (const char *p = path; *p; p++) if (*p == '/' || *p == '\\') name = p + 1;
    string_literal(&out, name);
    bprintf(&out, ", %d, %d, lookup};\nconst A26RecompProgram *const a26_recomp_program = &program;\n", cart.type, pal);
    buf_write_file(output, &out);
    free(out.s);
    free(rom);
    printf("recompiled %u Atari 2600 instruction entries\n", generated);
    return 0;
}
