#include "m68k_misses.h"

#include <stdio.h>

int m68k_misses_save(const char *path, uint8_t *slots, uint32_t n) {
    uint32_t fresh = 0;
    for (uint32_t i = 0; i < n; i++) fresh += slots[i];
    FILE *f = fopen(path, "r");
    char line[64];
    unsigned pc;
    while (f && fgets(line, sizeof line, f)) {
        if (sscanf(line, "MISS $%x", &pc) != 1 || pc / 2 >= n) continue;
        if (slots[pc / 2] == 1) fresh--;  /* known already */
        slots[pc / 2] = 2;
    }
    if (f) fclose(f);
    if (!fresh) return 0;
    if (!(f = fopen(path, "w"))) return -1;
    for (uint32_t i = 0; i < n; i++)
        if (slots[i]) fprintf(f, "MISS $%06X\n", (unsigned)i * 2);
    return fclose(f) ? -1 : 0;
}
