#ifndef CPS2_ROMS_H
#define CPS2_ROMS_H

#include "zip.h"

typedef enum {
    CPS2_LINEAR, CPS2_BYTE16, CPS2_SWAP16, CPS2_BYTE64, CPS2_WORD64,
    CPS2_FILL, CPS2_UNDUMPED
} Cps2Wiring;

typedef struct {
    const char *name;
    uint32_t crc, chip_size, source, offset, length;
    Cps2Wiring wiring;
} Cps2Load;

typedef struct {
    const char *tag;
    uint32_t size;
    uint8_t erase;
    const Cps2Load *loads;
    size_t count;
} Cps2Region;

typedef struct {
    const char *id, *parent, *machine, *inputs, *init, *rotation, *title;
    const Cps2Region *regions;
    size_t count;
} Cps2Game;

typedef struct {
    const Cps2Game *game;
    uint8_t **regions;
} Cps2Rom;

extern const Cps2Game cps2_games[];
extern const size_t cps2_game_count;

const Cps2Game *cps2_find_game(const char *id);
/* Archives are supplied in set-to-parent order. On failure out is empty. */
int cps2_load(const Cps2Game *game, const Zip *archives, size_t archive_count,
              Cps2Rom *out, char *error, size_t error_size);
void cps2_unload(Cps2Rom *rom);
const uint8_t *cps2_region(const Cps2Rom *rom, const char *tag, size_t *size);

#endif
