// Standalone checker: a 20-byte key followed by program bytes on stdin.
#include "cps2crypt.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

int main(void)
{
#ifdef _WIN32
    _setmode(_fileno(stdin), _O_BINARY);
    _setmode(_fileno(stdout), _O_BINARY);
#endif
    enum { KEY_SIZE = 20, MAX_PROGRAM = 0x1000000 };
    uint8_t key[KEY_SIZE];
    uint16_t *rom = malloc(MAX_PROGRAM);
    uint16_t *opcodes = NULL;
    size_t words = 0;
    int status = EXIT_FAILURE;

    if (!rom || fread(key, 1, KEY_SIZE, stdin) != KEY_SIZE)
        goto done;
    int high, low;
    while ((high = getchar()) != EOF) {
        low = getchar();
        if (low == EOF || words == MAX_PROGRAM / 2)
            goto done;
        rom[words++] = (uint16_t)((high << 8) | low);
    }
    if (ferror(stdin) || !words)
        goto done;
    opcodes = malloc(words * sizeof(*opcodes));
    if (!opcodes)
        goto done;
    cps2_decrypt(rom, opcodes, (int)(words * 2), key);
    for (size_t i = 0; i < words; ++i)
        if (putchar(opcodes[i] >> 8) == EOF || putchar(opcodes[i] & 255) == EOF)
            goto done;
    if (fflush(stdout) == 0)
        status = EXIT_SUCCESS;

done:
    free(opcodes);
    free(rom);
    if (status != EXIT_SUCCESS)
        fputs("Could not decrypt CPS-2 input\n", stderr);
    return status;
}
