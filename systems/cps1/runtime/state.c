/* Save states (cps1.h): "CPS1ST02", the game's id (16 bytes), the size of
 * Cps1, the CRC-32 of what follows, then Cps1 with its pointers cleared;
 * loading checks all four and reads into a copy, so a refused file (cut,
 * damaged, another game or version) leaves the machine as it was. */
#include <stdio.h>
#include <string.h>

#include "cps1.h"

static const char MAGIC[8] = {'C', 'P', 'S', '1', 'S', 'T', '0', '2'};

int cps1_state_save(const Cps1 *s, const char *path) {
    static Cps1 copy;
    char id[16] = {0};
    strncpy(id, s->rom->game->id, sizeof id - 1);
    copy = *s;
    copy.rom = NULL, copy.cpu.bus = NULL, copy.z80.bus = NULL, copy.oki.rom = NULL, copy.recomp = NULL, copy.misses = NULL;
    uint32_t size = sizeof copy, crc = zip_crc32((const uint8_t *)&copy, sizeof copy);
    FILE *f = fopen(path, "wb");
    if (!f) return 1;
    int bad = fwrite(MAGIC, 1, 8, f) != 8 || fwrite(id, 1, 16, f) != 16 || fwrite(&size, 4, 1, f) != 1 ||
              fwrite(&crc, 4, 1, f) != 1 || fwrite(&copy, 1, sizeof copy, f) != sizeof copy;
    return fclose(f) || bad;
}

int cps1_state_load(Cps1 *s, const char *path, char *err, size_t errlen) {
    static Cps1 loaded;
    char magic[8], id[17] = {0};
    uint32_t size = 0, crc = 0;
    FILE *f = fopen(path, "rb");
    if (!f) return snprintf(err, errlen, "cannot open state %s", path), 1;
    int bad = fread(magic, 1, 8, f) != 8 || memcmp(magic, MAGIC, 8) || fread(id, 1, 16, f) != 16 ||
              fread(&size, 4, 1, f) != 1 || size != sizeof loaded || fread(&crc, 4, 1, f) != 1 ||
              fread(&loaded, 1, sizeof loaded, f) != sizeof loaded ||
              zip_crc32((const uint8_t *)&loaded, sizeof loaded) != crc;
    fclose(f);
    if (bad) return snprintf(err, errlen, "%s: not a CPS-1 state of this version, or damaged", path), 1;
    if (strncmp(id, s->rom->game->id, 16))
        return snprintf(err, errlen, "%s: a state of %s, not %s", path, id, s->rom->game->id), 1;
    const Cps1Rom *rom = s->rom;
    const Cps1RecompProgram *recomp = s->recomp;  /* this program's code and misses, not the file's */
    uint8_t recomp_on = s->recomp_on, *misses = s->misses;
    *s = loaded;
    s->rom = rom, s->cpu.bus = s, s->z80.bus = s;
    s->recomp = recomp, s->recomp_on = recomp_on, s->misses = misses;
    s->oki.rom = rom->region[CPS1_R_OKI], s->oki.size = rom->size[CPS1_R_OKI];  /* the ROM's, not the file's */
    if (s->snd_n < 0 || s->snd_n > CPS1_SND_BUF) s->snd_n = 0;
    return 0;
}
