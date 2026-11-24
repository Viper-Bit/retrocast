/* The 68000 recompiler's analysis and emitting (m68k_recomp.h).
 *
 * Static flow is followed from the entries: Bcc, BRA, BSR, DBcc, and JMP
 * and JSR to absolute or PC-relative targets; the rest (jump tables,
 * returns) is resolved at run time by the lookup. One C function per basic
 * block. Each instruction is the interpreter's own handler body (the
 * template, m68k.c, as the interpreter expands it) with `op` a constant, so
 * the compiler folds the register fields and bus traffic and timing are the
 * interpreter's by construction. A block ends after any instruction whose
 * template can change the PC (branches, jumps, traps, conditional
 * exceptions, privileged and SR writes). After each instruction the
 * system's `after` code runs and the block returns if `stop` holds. */
#include "m68k_recomp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const M68kRecomp *R;  /* the one being worked on (a build-time tool, one at a time) */

static uint16_t word(uint32_t a) { return (uint16_t)(R->code[a] << 8 | R->code[a + 1]); }

typedef struct {
    uint32_t pc;
    uint16_t op;
    uint8_t len;
    uint8_t flow;  /* the template can change the PC: the block ends here */
} Ins;

static int decode(uint32_t pc, Ins *i) {
    if (pc & 1 || pc + 2 > R->end) return 0;
    i->pc = pc, i->op = word(pc), i->len = (uint8_t)(2 + 2 * m68k_ext_words(i->op));
    if (pc + i->len > R->end) return 0;
    Lines l;
    m68k_body(i->op, &l);
    i->flow = 0;
    for (int k = 0; k < l.n; k++) i->flow |= strstr(l.s[k], "@J") || strstr(l.s[k], "@B");
    return 1;
}

/* Can the next instruction run after this one (BSR and JSR: on return)? */
static int falls_through(const Ins *i) {
    uint16_t op = i->op;
    Lines l;
    if (!m68k_body(op, &l)) return 0;  /* illegal, line A, line F */
    return (op & 0xFF00) != 0x6000 && (op & 0xFFC0) != 0x4EC0 && op != 0x4E73 && op != 0x4E75 && op != 0x4E77 &&
           (op & 0xFFF0) != 0x4E40;  /* BRA JMP RTE RTS RTR TRAP */
}

/* The static target of a branch, DBcc, JMP or JSR; -1 if none (or not code). */
static long target(const Ins *i) {
    uint16_t op = i->op;
    uint32_t t;
    if ((op & 0xF000) == 0x6000) t = i->pc + 2 + (op & 0xFF ? (uint32_t)(int8_t)op : (uint32_t)(int16_t)word(i->pc + 2));
    else if ((op & 0xF0F8) == 0x50C8) t = i->pc + 2 + (uint32_t)(int16_t)word(i->pc + 2);
    else if ((op & 0xFF80) == 0x4E80 && op & 0x3F) {
        if ((op & 0x3F) == 0x38) t = (uint32_t)(int16_t)word(i->pc + 2);
        else if ((op & 0x3F) == 0x39) t = (uint32_t)word(i->pc + 2) << 16 | word(i->pc + 4);
        else if ((op & 0x3F) == 0x3A) t = i->pc + 2 + (uint32_t)(int16_t)word(i->pc + 2);
        else return -1;
    } else return -1;
    t &= 0xFFFFFF;
    return t & 1 || t >= R->end ? -1 : (long)t;
}

static int explore(uint8_t *instr) {
    uint32_t end = R->end;
    uint32_t *work = malloc(sizeof *work * (end / 2 + 1));
    if (!work) return -1;
    size_t n = 0;
    for (uint32_t a = 0; a < end; a += 2)
        if (R->entries[a]) work[n++] = a;
    while (n) {
        uint32_t pc = work[--n];
        Ins i;
        if (instr[pc] || !decode(pc, &i)) continue;
        instr[pc] = 1;
        long t = target(&i);
        if (t >= 0 && !instr[t]) work[n++] = (uint32_t)t;
        if (falls_through(&i) && pc + i.len < end && !instr[pc + i.len]) work[n++] = pc + i.len;
    }
    free(work);
    return 0;
}

/* Block starts: static targets, what follows a block's last instruction,
 * and entries no other instruction falls into. */
static int block_starts(const uint8_t *instr, uint8_t *starts) {
    uint32_t end = R->end;
    uint8_t *fallen_into = calloc(end + 8, 1);
    if (!fallen_into) return -1;
    for (uint32_t a = 0; a < end; a += 2) {
        Ins i;
        if (!instr[a] || !decode(a, &i)) continue;
        long t = target(&i);
        if (t >= 0 && instr[t]) starts[t] = 1;
        uint32_t next = a + i.len;
        if (!falls_through(&i) || next >= end || !instr[next]) continue;
        if (i.flow) starts[next] = 1;
        else fallen_into[next] = 1;
    }
    for (uint32_t a = 0; a < end; a += 2)
        if (instr[a] && R->entries[a] && !fallen_into[a]) starts[a] = 1;
    free(fallen_into);
    return 0;
}

static int block_instrs(uint32_t start, Ins *out) {
    int n = 0;
    for (uint32_t pc = start;;) {
        decode(pc, &out[n]);
        const Ins *i = &out[n++];
        uint32_t next = pc + i->len;
        if (i->flow || !falls_through(i) || next >= R->end || !R->instr[next] || R->starts[next]) return n;
        pc = next;
    }
}

static void emit_block(Buf *o, uint32_t start, const Ins *ins, int n) {
    bprintf(o, "static void b_%06X(M68k *c) {\n    %s\n    switch ((c->pc - 4) & 0xFFFFFF) {\n", start, R->bus_decl);
    for (int k = 0; k < n; k++) bprintf(o, "    case 0x%06X: goto i_%06X;\n", ins[k].pc, ins[k].pc);
    bprintf(o, "    default: return;\n    }\n");
    for (int k = 0; k < n; k++) {
        const Ins *i = &ins[k];
        bprintf(o, "i_%06X: /*", i->pc);
        for (int w = 0; w < i->len; w += 2) bprintf(o, " %04X", word(i->pc + (uint32_t)w));
        bprintf(o, " */\n    c->ae_adj = -2;\n    c->trace = (c->sr & M68K_T) != 0;\n    c->op = 0x%04X;\n", i->op);
        bprintf(o, "    {\n        const uint16_t op = 0x%04X;\n        (void)op;\n", i->op);
        Lines l;
        m68k_body(i->op, &l);
        for (int k2 = 0; k2 < l.n; k2++) template_plain(o, "        ", l.s[k2]);
        bprintf(o, "    }\n");
        if (*R->after) bprintf(o, "    %s\n", R->after);
        bprintf(o, "    if (%s) return;\n", R->stop);
    }
    /* chaining: to a block known from here */
    const Ins *last = &ins[n - 1];
    long next[2] = {target(last), falls_through(last) ? (long)(last->pc + last->len) : -1};
    int chained = 0;
    for (int k = 0; k < 2; k++) {
        if (next[k] < 0 || (uint32_t)next[k] >= R->end || !R->starts[next[k]] || (k == 1 && next[1] == next[0])) continue;
        if (!chained++) bprintf(o, "    switch ((c->pc - 4) & 0xFFFFFF) {\n");
        bprintf(o, "    case 0x%06lX: RECOMP_CHAIN(b_%06lX);\n", next[k], next[k]);
    }
    if (chained) bprintf(o, "    }\n");
    bprintf(o, "}\n\n");
}

int m68k_recomp_analyse(M68kRecomp *r) {
    R = r;
    r->instr = calloc(r->end + 8, 1), r->starts = calloc(r->end + 8, 1);
    if (!r->instr || !r->starts || explore(r->instr) || block_starts(r->instr, r->starts)) return -1;
    r->nblocks = r->ninstr = 0;
    for (uint32_t a = 0; a < r->end; a += 2) r->nblocks += r->starts[a], r->ninstr += r->instr[a];
    return 0;
}

int m68k_recomp_emit(const M68kRecomp *r, Buf *o) {
    R = r;
    uint32_t end = r->end;
    long ninstr = r->ninstr;
    for (uint32_t a = 0; a < end; a += 2)  /* prototypes: blocks chain to each other */
        if (r->starts[a]) bprintf(o, "static void b_%06X(M68k *c);\n", a);
    bprintf(o, "\n");
    Ins *ins = malloc(sizeof *ins * (end / 2 + 1));
    uint32_t *block_of = calloc(end / 2 + 1, sizeof *block_of);  /* instruction -> block start + 1 */
    if (!ins || !block_of) return free(ins), free(block_of), fprintf(stderr, "recomp: out of memory\n"), -1;
    for (uint32_t s = 0; s < end; s += 2) {
        if (!r->starts[s]) continue;
        int n = block_instrs(s, ins);
        emit_block(o, s, ins, n);
        for (int k = 0; k < n; k++)
            if (!block_of[ins[k].pc >> 1]) block_of[ins[k].pc >> 1] = s + 1;
    }
    free(ins);
    for (uint32_t a = 0; a < end; a += 2)
        if (r->instr[a] && !block_of[a >> 1]) return free(block_of), fprintf(stderr, "recomp: $%06X is in no block\n", a), -1;
    /* lookup: the instructions in address order, binary searched */
    bprintf(o, "static const uint32_t ins_at[%ld] = {", ninstr ? ninstr : 1);
    long k = 0;
    for (uint32_t a = 0; a < end; a += 2)
        if (r->instr[a]) bprintf(o, k++ % 8 ? "0x%06X," : "\n    0x%06X,", a);
    bprintf(o, "%s\n};\nstatic const %s ins_block[%ld] = {", ninstr ? "" : "0", r->fn_type, ninstr ? ninstr : 1);
    k = 0;
    for (uint32_t a = 0; a < end; a += 2)
        if (r->instr[a]) bprintf(o, k++ % 4 ? "b_%06X," : "\n    b_%06X,", block_of[a >> 1] - 1);
    bprintf(o, "%s\n};\n\n", ninstr ? "" : "0");
    free(block_of);
    bprintf(o, "static %s lookup(uint32_t at) {\n    size_t lo = 0, hi = %ld;\n", r->fn_type, ninstr);
    bprintf(o, "    while (lo < hi) {\n        size_t mid = (lo + hi) / 2;\n");
    bprintf(o, "        if (ins_at[mid] < at) lo = mid + 1;\n        else hi = mid;\n    }\n");
    bprintf(o, "    return lo < %ld && ins_at[lo] == at ? ins_block[lo] : 0;\n}\n\n", ninstr);
    return 0;
}

void m68k_recomp_free(M68kRecomp *r) {
    free(r->instr), free(r->starts);
    r->instr = r->starts = NULL;
}

uint32_t m68k_recomp_hash(const uint8_t *d, size_t n) {
    uint32_t h = 2166136261u;
    for (size_t i = 0; i < n; i++) h = (h ^ d[i]) * 16777619u;
    return h;
}
