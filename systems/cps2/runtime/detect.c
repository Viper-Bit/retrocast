#include "detect.h"
#include "roms.h"

#include <string.h>

static int score(const uint8_t *data, size_t size)
{
    Zip archive;
    if (zip_open(&archive, data, size))
        return 0;
    int found = 0;
    for (size_t g = 0; g < cps2_game_count && !found; ++g) {
        const Cps2Game *game = &cps2_games[g];
        for (size_t r = 0; r < game->count && !found; ++r) {
            const Cps2Region *region = &game->regions[r];
            if (strcmp(region->tag, "maincpu"))
                continue;
            for (size_t i = 0; i < region->count && !found; ++i) {
                const Cps2Load *chip = &region->loads[i];
                found = chip->wiring < CPS2_FILL &&
                        zip_find_crc(&archive, chip->crc, chip->chip_size) != NULL;
            }
        }
    }
    zip_close(&archive);
    return found ? 100 : 0;
}

const SystemDetector cps2_detector = {"cps2", "Capcom Play System II", ".zip", score};
