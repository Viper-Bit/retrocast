/* zip_check FILE: each entry's name, CRC and size after reading it back
 * (core/zip.c, tests/test_zip.py); exit 1 on any error. */
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "zip.h"

int main(int argc, char **argv) {
    if (argc != 2) return fprintf(stderr, "usage: zip_check FILE\n"), 2;
    size_t n;
    uint8_t *data = file_read(argv[1], &n);
    if (!data) return perror(argv[1]), 1;
    Zip z;
    if (zip_open(&z, data, (size_t)n)) return fprintf(stderr, "%s: not a zip\n", argv[1]), 1;
    for (int i = 0; i < z.count; i++) {
        const ZipEntry *e = &z.entries[i];
        uint8_t *out = malloc(e->size ? e->size : 1);
        if (!out || zip_read(&z, e, out)) return fprintf(stderr, "%.*s: damaged\n", e->name_len, e->name), 1;
        printf("%.*s %08x %u\n", e->name_len, e->name, (unsigned)e->crc, (unsigned)e->size);
        free(out);
    }
    return 0;
}
