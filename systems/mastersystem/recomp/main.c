/* smsrecomp ROM -o OUT.c [--misses TRACE]... [--no-rom]
 *
 * Recompiles the reachable Z80 instructions of a Master System ROM into C
 * basic blocks. Code is keyed by the ROM page mapped into its 16 KB slot and
 * its address, so the same page seen at another slot, or a bank switch, never
 * runs the wrong code. A block runs instruction after instruction and returns
 * to the runtime when the line is over, an interrupt it would take is due,
 * the CPU halts, or the page under the next instruction changed; every
 * instruction is also an entry point (a switch at the top), and a block
 * chains to the next one when that is known here. Operand bytes and
 * addresses are baked in as constants; every bus cycle still happens.
 *
 * Entry points: the reset and RST/NMI vectors, "MISS $PC page P" lines from
 * sms_headless --misses (a play trace or the user's NAME.misses), and the
 * targets and fallthrough of what they reach. DD CB / FD CB instructions and
 * the DD/FD opcodes that run as base ones stay in the interpreter.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loader.h"
#include "sms.h"
#include "template.h"
#include "z80.h"

#define MAX_INS 200000
#define MAX_PENDING 200000
#define MAX_MISSES 200000

#define MAX_BLOCK 256

typedef struct { unsigned page; uint16_t pc; } At;
typedef struct {
    unsigned page;
    uint16_t pc, next, target;      /* target: a constant jump target, else $FFFF */
    uint8_t jump;
    unsigned block;                 /* the block it is in */
} Ins;

typedef struct {
    At pending[MAX_PENDING];
    unsigned npending;
    Ins *ins;
    unsigned n, cap;
    uint8_t *seen;                    /* by sms_code_index(page, pc): 1 = queued */
    unsigned banks;
    int fixed_vectors;
    const uint8_t *rom;
    size_t size;
} Work;

typedef struct {
    int table;
    uint8_t op;
    unsigned nprefix;                 /* M1 fetches before the opcode's M1 */
    uint16_t operand_pc;              /* address of the first template @F */
    uint16_t next;                    /* address after the instruction */
    int jump;                         /* a template has @J or @B */
    uint16_t target;                  /* a constant @J 0xXXXX, else 0xFFFF */
} Decoded;

static void usage(void) {
    fprintf(stderr, "usage: smsrecomp ROM -o OUT.c [--misses TRACE]... [--no-rom]\n");
    exit(2);
}

static void add(Work *w, unsigned page, uint16_t pc) {
    if (pc >= SMS_CODE_SPAN || page >= w->banks) return;
    if (pc < 0x0400 && page != 0 && w->fixed_vectors) return;  /* the fixed vector page */
    if (w->seen[sms_code_index(page, pc)]) return;
    if (w->npending == MAX_PENDING) return;
    w->pending[w->npending++] = (At){page, pc};
    w->seen[sms_code_index(page, pc)] = 1;
}

static uint8_t rom_byte(const Work *w, unsigned page, uint16_t pc) {
    size_t off = (size_t)page * SMS_ROM_BANK + (pc & (SMS_ROM_BANK - 1));
    return off < w->size ? w->rom[off] : 0xFF;
}

/* The 64 KB image template_expand reads operand bytes from. The decoded
 * page fills every slot: an instruction's operands are in its own slot,
 * and instructions that cross a slot boundary are not recompiled. */
static void build_mem(uint8_t mem[0x10000], const Work *w, unsigned page) {
    memset(mem, 0xFF, 0x10000);
    unsigned p = page % w->banks;
    for (unsigned slot = 0; slot < 3; slot++)
        for (unsigned i = 0; i < SMS_ROM_BANK; i++) {
            size_t off = (size_t)p * SMS_ROM_BANK + i;
            mem[slot * SMS_ROM_BANK + i] = off < w->size ? w->rom[off] : 0xFF;
        }
}

static void expand_line(Buf *o, const char *indent, const char *line, uint32_t *pc,
                        const uint8_t *mem, uint32_t at, unsigned *fetched, int *jump) {
    bprintf(o, "%s", indent);
    template_expand(o, line, pc, mem, 0xFFFF, at, fetched, jump);
    bprintf(o, "\n");
}

/* Decode a prefix sequence and the template lines. A zero return means the
 * instruction is left to the interpreter. */
static int decode(const Work *w, unsigned page, uint16_t pc, Decoded *d, Lines *l, uint8_t *mem) {
    uint8_t op = rom_byte(w, page, pc);
    memset(d, 0, sizeof *d);
    d->op = op;
    d->target = 0xFFFF;
    d->table = Z80_T_BASE;
    d->operand_pc = (uint16_t)(pc + 1);
    if (op == 0xCB || op == 0xED) {
        d->table = op == 0xCB ? Z80_T_CB : Z80_T_ED;
        d->nprefix = 1;
        d->op = rom_byte(w, page, (uint16_t)(pc + 1));
        d->operand_pc = (uint16_t)(pc + 2);
    } else if (op == 0xDD || op == 0xFD) {
        uint8_t op2 = rom_byte(w, page, (uint16_t)(pc + 1));
        if (op2 == 0xCB || op2 == 0xDD || op2 == 0xED || op2 == 0xFD) return 0;
        d->table = op == 0xDD ? Z80_T_DD : Z80_T_FD;
        d->op = op2;
        d->nprefix = 1;
        d->operand_pc = (uint16_t)(pc + 2);
    }
    char name[64];
    if (!z80_body(d->table, d->op, l, name, sizeof name)) return 0;
    build_mem(mem, w, page);
    unsigned fetched = 0;
    uint32_t p = d->operand_pc;
    Buf probe = {0};
    for (int k = 0; k < l->n; k++)
        expand_line(&probe, "", l->s[k], &p, mem, pc, &fetched, &d->jump);
    free(probe.s);
    for (int k = 0; k < l->n; k++)  /* template_expand reports @J; a taken @B leaves the block too */
        if (strstr(l->s[k], "@B")) d->jump = 1;
    d->next = (uint16_t)p;
    unsigned expected = 0;
    for (uint32_t a = d->operand_pc; a != d->next; a = (a + 1) & 0xFFFF)
        expected |= 1u << ((a - pc) & 15);
    if (fetched != expected) return 0;  /* template and operand decoding disagree */
    if ((pc >> 14) != (d->next >> 14)) return 0;  /* crosses a 16 KB slot */
    if (d->jump) {
        for (int k = 0; k < l->n; k++) {
            const char *s = strstr(l->s[k], "@J 0x");
            unsigned t = 0;
            if (s && sscanf(s + 5, "%4x", &t) == 1) { d->target = (uint16_t)t; break; }
        }
        if (d->target == 0xFFFF) {
            /* JP nn / CALL nn, JR e / DJNZ e: the target is in the operand
             * bytes we just decoded, so follow it within the same page. */
            uint8_t op0 = rom_byte(w, page, pc);
            if (op0 == 0xC3 || op0 == 0xCD) {
                unsigned lo = mem[d->operand_pc & 0xFFFF], hi = mem[(d->operand_pc + 1) & 0xFFFF];
                d->target = (uint16_t)(lo | hi << 8);
            } else if (op0 == 0x18 || op0 == 0x10 || op0 == 0x20 || op0 == 0x28 ||
                       op0 == 0x30 || op0 == 0x38) {
                int8_t e = (int8_t)mem[d->operand_pc & 0xFFFF];
                d->target = (uint16_t)(d->next + e);
            }
        }
    }
    return 1;
}

/* The page check after an instruction: the code at `next` is this page's
 * only while the page stays mapped in next's slot (the vectors always are). */
static void page_check(Buf *o, const Work *w, unsigned page, uint16_t next) {
    if (next < 0x0400 && w->fixed_vectors) return;
    bprintf(o, " || s->cart.page[%u] != %u", 1 + (next >> 14), page);
}

static void emit_ins(Buf *o, const Work *w, const Decoded *d, const Lines *l,
                     const uint8_t *mem, unsigned page, uint16_t pc) {
    bprintf(o, "i_%04X:  /* $%02X */\n", pc, rom_byte(w, page, pc));
    bprintf(o, "    c->qprev = c->q; c->q = 0; c->p = 0; c->ei = 0;\n");
    bprintf(o, "    (void)z80_m1(c);\n");
    for (unsigned k = 0; k < d->nprefix; k++) bprintf(o, "    (void)z80_m1(c);  /* prefix */\n");
    if (d->table == Z80_T_DD || d->table == Z80_T_FD)  /* as the interpreter's DD/FD case */
        bprintf(o, "    c->qprev = 0;\n");
    bprintf(o, "    {\n        c->pc = 0x%04X;\n", d->next);
    unsigned fetched = 0;
    uint32_t p = d->operand_pc;
    int jump = 0;
    for (int k = 0; k < l->n; k++) expand_line(o, "        ", l->s[k], &p, mem, pc, &fetched, &jump);
    bprintf(o, "    }\n");
}

static int by_page_pc(const void *x, const void *y) {
    const Ins *a = x, *b = y;
    if (a->page != b->page) return a->page < b->page ? -1 : 1;
    return a->pc < b->pc ? -1 : a->pc > b->pc;
}

/* The instruction at (page, pc), or NULL. */
static const Ins *find(const Work *w, unsigned page, uint16_t pc) {
    Ins key = {page, pc, 0, 0, 0, 0};
    return bsearch(&key, w->ins, w->n, sizeof *w->ins, by_page_pc);
}

static void string_literal(Buf *o, const char *s) {
    bprintf(o, "\"");
    for (; *s; s++) {
        if (*s == '"' || *s == '\\') bprintf(o, "\\%c", *s);
        else if (*s == '\n') bprintf(o, "\\n");
        else bprintf(o, "%c", *s);
    }
    bprintf(o, "\"");
}

static void load_misses(Work *w, const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return;  /* a game's own .misses need not exist yet */
    char line[128];
    unsigned n = 0;
    while (fgets(line, sizeof line, f) && n++ < MAX_MISSES) {
        unsigned pc = 0, page = 0;
        if (sscanf(line, "MISS $%x page %u", &pc, &page) == 2 && pc < 0x10000)
            add(w, page, (uint16_t)pc);
    }
    fclose(f);
}

static void recompile(Work *w, Buf *o, const char *name, int embed, uint32_t hash) {
    static uint8_t mem[0x10000];
    /* 1. every instruction reachable from the entry points */
    while (w->npending) {
        At a = w->pending[--w->npending];
        Decoded d;
        Lines l;
        if (w->n == MAX_INS || !decode(w, a.page, a.pc, &d, &l, mem)) continue;
        if (w->n == w->cap) {
            w->cap = w->cap ? w->cap * 2 : 1024;
            w->ins = realloc(w->ins, (size_t)w->cap * sizeof *w->ins);
            if (!w->ins) exit(1);
        }
        w->ins[w->n++] = (Ins){a.page, a.pc, d.next, d.target, (uint8_t)(d.jump != 0), 0};
        add(w, a.page, d.next);  /* after a jump too: a conditional one falls through */
        if (d.target != 0xFFFF) add(w, a.page, d.target);
    }
    /* 2. blocks: runs of consecutive instructions in one slot, ended by a jump */
    qsort(w->ins, w->n, sizeof *w->ins, by_page_pc);
    unsigned nblocks = 0;
    for (unsigned i = 0, len = 0; i < w->n; i++, len++) {
        const Ins *prev = i ? &w->ins[i - 1] : NULL;
        if (!prev || prev->page != w->ins[i].page || prev->next != w->ins[i].pc || prev->jump ||
            (prev->pc >> 14) != (w->ins[i].pc >> 14) || len == MAX_BLOCK)
            nblocks++, len = 0;
        w->ins[i].block = nblocks - 1;
    }

    bprintf(o, "/* Generated by smsrecomp from %s. Do not edit. */\n", name);
    bprintf(o, "#include \"z80_ops.h\"\n#include \"sms.h\"\n#include \"recomp_rt.h\"\n\n");
    if (embed) {
        bprintf(o, "static const unsigned char rom_data[] = {");
        for (size_t k = 0; k < w->size; k++) bprintf(o, "%s0x%02X,", k % 24 ? "" : "\n    ", w->rom[k]);
        bprintf(o, "\n};\n\n");
    }
    for (unsigned b = 0; b < nblocks; b++) bprintf(o, "static void b%u(Z80 *c);\n", b);
    bprintf(o, "\n");

    /* 3. the blocks */
    for (unsigned i = 0; i < w->n;) {
        unsigned b = w->ins[i].block, first = i, last = i;
        while (last + 1 < w->n && w->ins[last + 1].block == b) last++;
        unsigned page = w->ins[first].page;
        bprintf(o, "/* page %u, $%04X-$%04X */\nstatic void b%u(Z80 *c) {\n    Sms *const s = c->bus;\n    switch (c->pc) {\n",
                page, w->ins[first].pc, w->ins[last].pc, b);
        for (unsigned k = first; k <= last; k++) bprintf(o, "    case 0x%04X: goto i_%04X;\n", w->ins[k].pc, w->ins[k].pc);
        bprintf(o, "    default: return;\n    }\n");
        for (unsigned k = first; k <= last; k++) {
            const Ins *n = &w->ins[k];
            Decoded d;
            Lines l;
            decode(w, page, n->pc, &d, &l, mem);
            emit_ins(o, w, &d, &l, mem, page, n->pc);
            bprintf(o, "    if (SMS_STOP(s)");
            if (!n->jump) page_check(o, w, page, n->next);
            bprintf(o, ") return;\n");
        }
        /* chain to the next block: the fallthrough, or the jump's constant target */
        const Ins *end = &w->ins[last];
        uint16_t to[2] = {end->next, end->target};
        for (int k = 0; k < 2; k++) {
            if (to[k] == 0xFFFF || (k == 1 && to[1] == to[0])) continue;
            const Ins *t = find(w, page, to[k]);
            if (!t) continue;
            bprintf(o, "    if (c->pc == 0x%04X", to[k]);
            if (end->jump) {
                bprintf(o, " && !(0");
                page_check(o, w, page, to[k]);
                bprintf(o, ")");
            }
            bprintf(o, ") RECOMP_CHAIN(b%u);\n", t->block);
        }
        bprintf(o, "    return;\n}\n\n");
        i = last + 1;
    }

    /* 4. the lookup: any instruction's block, by page and address */
    bprintf(o, "static SmsRecompFn lookup(uint16_t pc, unsigned page) {\n    switch (page) {\n");
    for (unsigned i = 0; i < w->n;) {
        unsigned page = w->ins[i].page;
        bprintf(o, "    case %u:\n        switch (pc) {\n", page);
        for (; i < w->n && w->ins[i].page == page; i++)
            bprintf(o, "        case 0x%04X: return b%u;\n", w->ins[i].pc, w->ins[i].block);
        bprintf(o, "        default: return NULL;\n        }\n");
    }
    bprintf(o, "    default: return NULL;\n    }\n}\n\n");
    bprintf(o, "static const SmsRecompProgram program = {0x%08Xu, ", hash);
    string_literal(o, name);
    if (embed) bprintf(o, ", lookup, rom_data, %zu};\n", w->size);
    else bprintf(o, ", lookup, NULL, %zu};\n", w->size);
    bprintf(o, "const SmsRecompProgram *const sms_recomp_program = &program;\n");
    fprintf(stderr, "smsrecomp: %u instructions in %u blocks\n", w->n, nblocks);
}

int main(int argc, char **argv) {
    const char *rom_path = NULL, *out = NULL;
    const char *misses[64];
    int nmisses = 0, embed = 1;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-o") && i + 1 < argc) out = argv[++i];
        else if (!strcmp(argv[i], "--misses") && i + 1 < argc && nmisses < 64) misses[nmisses++] = argv[++i];
        else if (!strcmp(argv[i], "--no-rom")) embed = 0;
        else if (argv[i][0] != '-' && !rom_path) rom_path = argv[i];
        else usage();
    }
    if (!rom_path || !out) usage();
    uint8_t *rom = NULL;
    size_t size = 0;
    char err[256];
    if (sms_load_rom(rom_path, &rom, &size, err, sizeof err)) { fprintf(stderr, "%s\n", err); return 1; }
    Work *w = calloc(1, sizeof *w);  /* the queue is ~1.6 MB: heap, not stack */
    if (!w) return 1;
    w->rom = rom;
    w->size = size;
    w->banks = (unsigned)((size + SMS_ROM_BANK - 1) / SMS_ROM_BANK);
    w->fixed_vectors = sms_mapper(rom, size) == SMS_MAPPER_SEGA;
    w->seen = calloc(sms_code_index(w->banks, 0), 1);
    if (!w->seen) return 1;
    for (unsigned v = 0; v <= 0x38; v += 8) add(w, 0, (uint16_t)v);  /* RST $00-$38 */
    add(w, 0, 0x0066);                                              /* NMI (Pause) */
    add(w, 0, 0x0000);                                              /* reset */
    for (int i = 0; i < nmisses; i++) load_misses(w, misses[i]);

    Buf o = {0};
    recompile(w, &o, rom_path, embed, sms_rom_hash(rom, size));
    buf_write_file(out, &o);
    free(o.s);
    free(w->ins);
    free(w->seen);
    free(w);
    free(rom);
    return 0;
}
