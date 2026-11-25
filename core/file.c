#include "file.h"

#include <stdio.h>
#include <stdlib.h>

uint8_t *file_read(const char *path, size_t *size) {
    FILE *f = fopen(path, "rb");
    long n = -1;
    uint8_t *data = NULL;
    if (f && !fseek(f, 0, SEEK_END)) n = ftell(f);
    if (f && n >= 0 && !fseek(f, 0, SEEK_SET) && (data = malloc((size_t)n + 1)) &&
        fread(data, 1, (size_t)n, f) == (size_t)n) {
        data[n] = 0;
        *size = (size_t)n;
    } else {
        free(data);
        data = NULL;
    }
    if (f) fclose(f);
    return data;
}
