/* A whole file read into memory. */
#ifndef CORE_FILE_H
#define CORE_FILE_H

#include <stddef.h>
#include <stdint.h>

/* The file's bytes (malloc'd, the caller frees; one zero byte past the end,
 * so a text file is a string) and their count in *size; NULL when it cannot
 * be read. */
uint8_t *file_read(const char *path, size_t *size);

#endif
