#ifndef CPS2_RECOMP_RT_H
#define CPS2_RECOMP_RT_H

#include "machine.h"

#define CPS2_STOP(s, c) ((c)->cycles >= (s)->deadline || (c)->cycles >= (s)->line_clock || \
                        (c)->cycles >= (s)->raster_clock || (c)->ipl || (c)->ipl_seen || \
                        (c)->stopped || (c)->halted || (c)->trace)

/* The dispatcher rechecks the queued opcode and instruction boundary. */
#define RECOMP_CHAIN(f) return

#endif
