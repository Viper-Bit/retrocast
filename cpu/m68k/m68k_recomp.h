/* The 68000 recompiler's analysis and emitting, shared by the systems'
 * recompilers (systems/genesis/recomp, systems/cps1/recomp). One region of
 * code from address 0; one C function per basic block; each instruction is
 * the interpreter's template with `op` a constant (m68k_recomp.c). */
#ifndef M68K_RECOMP_H
#define M68K_RECOMP_H

#include <stddef.h>
#include <stdint.h>

#include "m68k.h"

typedef struct {
    const uint8_t *code;      /* big-endian 68000 code, from address 0 */
    uint32_t end;             /* code below this address is recompiled */
    const char *bus_decl;     /* each block's first line, e.g. "Md *const m = c->bus;" */
    const char *after;        /* after each instruction, before the stop test ("" for none) */
    const char *stop;         /* the hand-back condition, e.g. "MD_STOP(m, c)" */
    const char *fn_type;      /* the lookup's return type, e.g. "MdRecompFn" */
    uint8_t *entries;         /* a byte per address below end + 8: set by the caller (vectors, misses) */
    /* filled by m68k_recomp_analyse */
    uint8_t *instr, *starts;
    long nblocks, ninstr;
} M68kRecomp;

/* Follows the code from the entries, finds the blocks. 0, or -1 (out of memory). */
int m68k_recomp_analyse(M68kRecomp *r);
/* The prototypes, the blocks, and `static FN lookup(uint32_t at)`. 0, or -1
 * (an instruction in no block; a message on stderr). */
int m68k_recomp_emit(const M68kRecomp *r, Buf *o);
void m68k_recomp_free(M68kRecomp *r);
uint32_t m68k_recomp_hash(const uint8_t *d, size_t n);  /* FNV-1a */

#endif
