/* NAME.misses of a recompiled 68000 game: the code it interpreted, as
 * "MISS $PC" lines, read by the next build (the Genesis and the CPS-1). */
#ifndef M68K_MISSES_H
#define M68K_MISSES_H

#include <stdint.h>

/* slots[i] != 0: the word at address i * 2 was interpreted this session
 * (n slots). Merges the file's lines into slots (as 2) and rewrites the file
 * only when the session found new code, so the next build does not
 * recompile for nothing. 0, or -1 when the file cannot be written. */
int m68k_misses_save(const char *path, uint8_t *slots, uint32_t n);

#endif
