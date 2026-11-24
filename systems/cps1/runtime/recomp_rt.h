/* Interface between the CPS-1 runtime and recompiled 68000 code
 * (systems/cps1/recomp). A block runs from the instruction in the CPU's
 * queue (c->pc - 4, any instruction of the block) and returns after the one
 * that ends it, or as soon as cps1_frame's loop would do something else
 * before the next instruction: the line is over, an interrupt level is
 * presented, the CPU stopped or is tracing (CPS1_STOP). The Z80 runs after
 * each line, in both, so a block does nothing for it. So recompiled and
 * interpreted runs take the same steps, cycle for cycle (cps1_headless
 * --diff checks it). The types are in cps1.h. */
#ifndef CPS1_RECOMP_RT_H
#define CPS1_RECOMP_RT_H

#include "cps1.h"

/* After an instruction: must the block hand back to the loop? */
#define CPS1_STOP(s, c) ((c)->cycles >= (s)->line_end || (c)->ipl || (c)->ipl_seen || (c)->stopped || (c)->trace)

/* Continuing in the next block: a guaranteed tail call where the compiler
 * has one, else back to the loop, which looks it up. */
#if defined(__clang__) || (defined(__GNUC__) && __GNUC__ >= 15)
#define RECOMP_CHAIN(f) __attribute__((musttail)) return f(c)
#else
#define RECOMP_CHAIN(f) return
#endif

#endif
