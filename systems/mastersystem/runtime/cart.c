/* The cartridge: the "TMR SEGA" header and the mappers (SMS Power,
 * Development: Mappers). Three 16 KB slots at $0000, $4000 and $8000.
 * Sega's: banked by writes to $FFFD-$FFFF; the first 1 KB stays on bank 0
 * so the vectors survive banking; $FFFC bit 3 maps cartridge RAM over slot
 * 2, bit 2 picks which of its two 16 KB banks (sms.c). Codemasters': a
 * write to $0000, $4000 or $8000 picks that slot's bank, no fixed 1 KB. */
#include <string.h>

#include "sms.h"
#include "zip.h"

long sms_header(const uint8_t *data, size_t size) {
    static const long at[] = {0x1FF0, 0x3FF0, 0x7FF0};
    for (unsigned i = 0; i < sizeof at / sizeof at[0]; i++)
        if ((size_t)at[i] + 16 <= size && !memcmp(data + at[i], "TMR SEGA", 8))
            return at[i];
    return -1;
}

/* Codemasters games carry their own header: a checksum at $7FE6 and its
 * complement to $10000 at $7FE8 (SMS Power, ROM header). */
int sms_is_codemasters(const uint8_t *d, size_t size) {
    if (size < 0x8000) return 0;
    unsigned sum = d[0x7FE6] | d[0x7FE7] << 8, inv = d[0x7FE8] | d[0x7FE9] << 8;
    return sum && ((sum + inv) & 0xFFFF) == 0;
}

unsigned sms_mapper(const uint8_t *rom, size_t size) {
    switch (zip_crc32(rom, size)) {  /* Gearsystem's cartridge database */
    case 0x89B79E77: case 0x97D03541: case 0x929222C4: case 0x18FB98A3:
        return SMS_MAPPER_KOREAN;
    case 0x445525E2: case 0x83F0EEDE: case 0xA05258F5: case 0x06965ED9:
    case 0x77EFE84A: case 0xF89AF3CC: case 0x9195C34C: case 0x0A77FA5E:
        return SMS_MAPPER_MSX;
    case 0xE316C06D: return SMS_MAPPER_NEMESIS;
    default:
        return sms_is_codemasters(rom, size) ? SMS_MAPPER_CODEMASTERS : SMS_MAPPER_SEGA;
    }
}

int sms_gg_mode(const uint8_t *data, size_t size, const char *path) {
    long h = sms_header(data, size);
    unsigned region = h >= 0 ? data[h + 15] >> 4 : 0;
    if (region >= 3 && region <= 7) return region >= 5;
    size_t n = path ? strlen(path) : 0;
    return n >= 3 && (path[n - 3] == '.') && (path[n - 2] | 32) == 'g' && (path[n - 1] | 32) == 'g';
}

uint32_t sms_cart_addr(const SmsCart *c, uint16_t a) {
    if (sms_mapped_8k(c)) {
        if (a < 0x2000 && c->mapper == SMS_MAPPER_NEMESIS && c->size >= 0x2000)
            return (uint32_t)(c->size - 0x2000) + a;
        if (a < 0x4000) return a;
        unsigned banks = (unsigned)((c->size + 0x1FFF) / 0x2000);
        unsigned bank = banks ? c->page[(a >> 13) & 3] % banks : 0;
        return bank * 0x2000u + (a & 0x1FFF);
    }
    if (a < 0x0400 && c->mapper == SMS_MAPPER_SEGA) return a;
    unsigned banks = (unsigned)((c->size + SMS_ROM_BANK - 1) / SMS_ROM_BANK);
    unsigned bank = banks ? c->page[1 + (a >> 14)] % banks : 0;
    return (uint32_t)bank * SMS_ROM_BANK + (a & (SMS_ROM_BANK - 1));
}
