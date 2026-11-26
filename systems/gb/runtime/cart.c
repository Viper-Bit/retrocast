#include "cart.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gb_cart_load(GbCart *c, const uint8_t *d, size_t size, char *err, size_t errlen) {
    memset(c, 0, sizeof *c);
    if (size < 0x8000 || size > 0x800000) return snprintf(err, errlen, "not a Game Boy ROM (%zu bytes)", size), -1;
    static const struct { uint8_t type, mbc, battery, rtc; } TYPES[] = {
        {0x00, MBC_NONE, 0, 0}, {0x08, MBC_NONE, 0, 0}, {0x09, MBC_NONE, 1, 0},
        {0x01, MBC_1, 0, 0}, {0x02, MBC_1, 0, 0}, {0x03, MBC_1, 1, 0},
        {0x05, MBC_2, 0, 0}, {0x06, MBC_2, 1, 0},
        {0x0F, MBC_3, 1, 1}, {0x10, MBC_3, 1, 1}, {0x11, MBC_3, 0, 0}, {0x12, MBC_3, 0, 0}, {0x13, MBC_3, 1, 0},
        {0x19, MBC_5, 0, 0}, {0x1A, MBC_5, 0, 0}, {0x1B, MBC_5, 1, 0},
        {0x1C, MBC_5, 0, 0}, {0x1D, MBC_5, 0, 0}, {0x1E, MBC_5, 1, 0},  /* rumble: the motor is ignored */
        {0x22, MBC_7, 1, 0}, {0xFE, MBC_HUC3, 1, 1}, {0xFF, MBC_HUC1, 1, 0},
    };
    uint8_t type = d[0x147];
    int k = -1;
    for (size_t i = 0; i < sizeof TYPES / sizeof *TYPES; i++)
        if (TYPES[i].type == type) k = (int)i;
    if (k < 0) return snprintf(err, errlen, "cartridge type $%02X not supported yet", type), -1;
    /* the ROM size from the header, but never more than the file */
    uint32_t rom = d[0x148] <= 8 ? 0x8000u << d[0x148] : 0;
    while (rom > size) rom >>= 1;
    if (!rom) rom = 0x8000;
    static const uint32_t RAM[] = {0, 0x800, 0x2000, 0x8000, 0x20000, 0x10000};
    c->rom = malloc(rom);
    if (!c->rom) return snprintf(err, errlen, "out of memory"), -1;
    memcpy(c->rom, d, rom);
    c->rom_size = rom;
    c->type = type;
    c->mbc = TYPES[k].mbc, c->battery = TYPES[k].battery, c->has_rtc = TYPES[k].rtc;
    c->ram_size = c->mbc == MBC_2 ? 0x200 : d[0x149] < 6 ? RAM[d[0x149]] : 0;
    /* a type with RAM but size 0 in the header (some test ROMs): 8 KB */
    static const uint8_t WITH_RAM[] = {0x02, 0x03, 0x08, 0x09, 0x10, 0x12, 0x13, 0x1A, 0x1B, 0x1D, 0x1E};
    if (!c->ram_size && memchr(WITH_RAM, type, sizeof WITH_RAM)) c->ram_size = 0x2000;
    if (c->mbc == MBC_7) {
        c->ram_size = 256;
        memset(c->ram, 0xFF, c->ram_size);
        eeprom_init(&c->eeprom, 0);
        c->tilt_x = c->tilt_y = 0x8000;
    }
    if (c->mbc == MBC_HUC1 || c->mbc == MBC_HUC3) c->ram_on = 1;
    c->rom_bank = 1;
    /* MBC1 multicart: 8 Mbit, and bank $10 (at $40000) has a header with the logo too */
    c->multicart = c->mbc == MBC_1 && rom == 0x100000 && !memcmp(d + 0x104, d + 0x40104, 0x30);
    memcpy(c->title, d + 0x134, 16);
    for (int i = 0; i < 16; i++)
        if ((unsigned char)c->title[i] < 0x20 || (unsigned char)c->title[i] > 0x7E) c->title[i] = 0;
    return 0;
}

void gb_cart_free(GbCart *c) {
    free(c->rom);
    c->rom = NULL;
}

/* The ROM bank seen at $0000-$3FFF (zero = 0) and at $4000-$7FFF (high = 1). */
static uint32_t rom_bank(const GbCart *c, int high) {
    uint32_t b;
    switch (c->mbc) {
    case MBC_1: {  /* a 0 in the 5-bit register reads as 1; mode 1 also banks $0000 */
        uint32_t low = c->rom_bank & 0x1F ? c->rom_bank & 0x1F : 1, sh = c->multicart ? 4 : 5;
        if (c->multicart) low &= 0x0F;  /* the 0 -> 1 rule sees all five bits */
        b = high ? (uint32_t)c->bank2 << sh | low : c->mode ? (uint32_t)c->bank2 << sh : 0;
        break;
    }
    case MBC_2: case MBC_3: b = high ? (c->rom_bank ? c->rom_bank : 1) : 0; break;
    case MBC_5: case MBC_7: case MBC_HUC1: case MBC_HUC3: b = high ? c->rom_bank : 0; break;
    default: b = (uint32_t)high;
    }
    return b & (c->rom_size / 0x4000 - 1);
}

uint32_t gb_cart_bank(const GbCart *c, uint16_t a) { return rom_bank(c, a >= 0x4000); }

static int ram_offset(const GbCart *c, uint16_t a) {  /* -1: no RAM there */
    if (!c->ram_on || !c->ram_size) return -1;
    uint32_t bank = c->mbc == MBC_1 ? (c->mode ? c->bank2 : 0) : c->bank2;
    return (int)((bank * 0x2000 + (a & 0x1FFF)) % c->ram_size);
}

static uint64_t mbc7_us(const GbCart *c) {
    return c->mbc7_cycles * 15625 / 16384;  /* 1,048,576 M-cycles per second */
}

static uint8_t mbc7_read(const GbCart *c, uint16_t a) {
    if (!c->ram_on || !c->bank2 || a >= 0xB000) return 0xFF;
    switch (a >> 4 & 15) {
    case 2: return (uint8_t)c->tilt_x;
    case 3: return (uint8_t)(c->tilt_x >> 8);
    case 4: return (uint8_t)c->tilt_y;
    case 5: return (uint8_t)(c->tilt_y >> 8);
    case 6: return 0;
    case 8:
        return (uint8_t)(c->eeprom.cs << 7 | c->eeprom.clk << 6 | c->eeprom.di << 1 |
                         eeprom_do(&c->eeprom, mbc7_us(c)));
    default: return 0xFF;
    }
}

static void mbc7_write(GbCart *c, uint16_t a, uint8_t v) {
    if (!c->ram_on || !c->bank2 || a >= 0xB000) return;
    switch (a >> 4 & 15) {
    case 0:
        if (v == 0x55) {
            c->tilt_ready = 1;
            c->tilt_x = c->tilt_y = 0x8000;
        }
        break;
    case 1:
        if (v == 0xAA && c->tilt_ready) {
            c->tilt_ready = 0;
            c->tilt_x = (uint16_t)(0x81D0 + 0x70 * c->tilt_dx);
            c->tilt_y = (uint16_t)(0x81D0 + 0x70 * c->tilt_dy);
        }
        break;
    case 8: eeprom93lc56_write(&c->eeprom, c->ram, v, mbc7_us(c)); break;
    }
}

static unsigned huc3_nibble(const GbCart *c, unsigned addr) {
    return c->huc3.nvram[addr >> 1] >> ((addr & 1) * 4) & 15;
}

static void huc3_put(GbCart *c, unsigned addr, unsigned v) {
    unsigned shift = (addr & 1) * 4;
    uint8_t *byte = &c->huc3.nvram[addr >> 1];
    *byte = (uint8_t)((*byte & ~(15u << shift)) | (v & 15) << shift);
}

static void huc3_exec(GbCart *c) {
    unsigned cmd = c->huc3.command >> 4, arg = c->huc3.command & 15;
    switch (cmd) {
    case 1: c->huc3.command = (uint8_t)(0x10 | huc3_nibble(c, c->huc3.addr++)); break;
    case 3: huc3_put(c, c->huc3.addr++, arg); break;
    case 4: c->huc3.addr = (uint8_t)((c->huc3.addr & 0xF0) | arg); break;
    case 5: c->huc3.addr = (uint8_t)((c->huc3.addr & 0x0F) | arg << 4); break;
    case 6:
        if (arg == 0) {
            unsigned minutes = c->rtc[2] * 60u + c->rtc[1];
            unsigned days = c->rtc[3] | (c->rtc[4] & 15) << 8;
            for (unsigned i = 0; i < 3; i++) {
                huc3_put(c, i, minutes >> (4 * i));
                huc3_put(c, i + 3, days >> (4 * i));
            }
        } else if (arg == 1) {
            unsigned minutes = (huc3_nibble(c, 0) | huc3_nibble(c, 1) << 4 | huc3_nibble(c, 2) << 8) % 1440;
            c->rtc[0] = 0;
            c->rtc[1] = (uint8_t)(minutes % 60);
            c->rtc[2] = (uint8_t)(minutes / 60);
            c->rtc[3] = (uint8_t)(huc3_nibble(c, 3) | huc3_nibble(c, 4) << 4);
            c->rtc[4] = (uint8_t)huc3_nibble(c, 5);
            c->rtc_cycles = 0;
        } else if (arg == 2) {
            c->huc3.command = 0x61;
        }
        break;
    }
}

uint8_t gb_cart_read(const GbCart *c, uint16_t a) {
    if (a < 0x8000) return c->rom[rom_bank(c, a >= 0x4000) * 0x4000 + (a & 0x3FFF)];
    if (c->mbc == MBC_7) return mbc7_read(c, a);
    if (c->mbc == MBC_2) return c->ram_on ? (uint8_t)(0xF0 | c->ram[a & 0x1FF]) : 0xFF;
    if (c->mbc == MBC_3 && c->bank2 >= 0x08) {  /* the clock, as latched */
        static const uint8_t MASK[5] = {0x3F, 0x3F, 0x1F, 0xFF, 0xC1};
        return c->ram_on && c->bank2 <= 0x0C ? (uint8_t)(c->rtc_latched[c->bank2 - 8] & MASK[c->bank2 - 8]) : 0xFF;
    }
    if (c->mbc == MBC_HUC1 && c->mode == 0x0E) return 0xC0;  /* no incoming IR */
    if (c->mbc == MBC_HUC3 && !c->ram_on) {
        switch (c->mode) {
        case 0x0C: return 0x80 | c->huc3.command;
        case 0x0D: return 0xFF;  /* MCU is ready */
        case 0x0E: return 0xFE;  /* no incoming IR */
        default: return 0xFF;
        }
    }
    int o = ram_offset(c, a);
    return o < 0 ? 0xFF : c->ram[o];
}

void gb_cart_write(GbCart *c, uint16_t a, uint8_t v) {
    if (a >= 0xA000) {
        if (c->mbc == MBC_7) {
            mbc7_write(c, a, v);
        } else if (c->mbc == MBC_2) {
            if (c->ram_on) c->ram[a & 0x1FF] = v & 0x0F;
        } else if (c->mbc == MBC_3 && c->bank2 >= 0x08) {
            if (c->ram_on && c->bank2 <= 0x0C) {
                c->rtc[c->bank2 - 8] = v;
                if (c->bank2 == 0x08) c->rtc_cycles = 0;  /* writing the seconds restarts the second */
            }
        } else if (c->mbc == MBC_HUC3 && c->mode != 0x0A) {
            if (c->mode == 0x0B) c->huc3.command = v & 0x7F;
            else if (c->mode == 0x0D && !(v & 1)) huc3_exec(c);
        } else if (c->mbc != MBC_HUC1 || c->mode != 0x0E) {
            int o = ram_offset(c, a);
            if (o >= 0) c->ram[o] = v;
        }
        return;
    }
    switch (c->mbc) {
    case MBC_1:
        if (a < 0x2000) c->ram_on = (v & 0x0F) == 0x0A;
        else if (a < 0x4000) c->rom_bank = v & 0x1F;
        else if (a < 0x6000) c->bank2 = v & 3;
        else c->mode = v & 1;
        break;
    case MBC_2:  /* address bit 8 picks the register */
        if (a < 0x4000) {
            if (a & 0x100) c->rom_bank = v & 0x0F;
            else c->ram_on = (v & 0x0F) == 0x0A;
        }
        break;
    case MBC_3:
        if (a < 0x2000) c->ram_on = (v & 0x0F) == 0x0A;
        else if (a < 0x4000) c->rom_bank = v & 0x7F;
        else if (a < 0x6000) c->bank2 = v;
        else {  /* $00 then $01: copy the clock into the readable registers */
            if (c->latch_prev == 0 && v == 1) memcpy(c->rtc_latched, c->rtc, 5);
            c->latch_prev = v;
        }
        break;
    case MBC_HUC1:
    case MBC_HUC3:
        if (a < 0x2000) {
            c->mode = v & 15;
            if (c->mbc == MBC_HUC3) c->ram_on = c->mode == 0 || c->mode == 0x0A;
        } else if (a < 0x4000) c->rom_bank = v & 0x7F;
        else if (a < 0x6000) c->bank2 = v & 3;
        break;
    case MBC_7:
        if (a < 0x2000) c->ram_on = (v & 0x0F) == 0x0A;
        else if (a < 0x4000) c->rom_bank = v & 0x7F;
        else if (a < 0x6000) c->bank2 = v == 0x40;
        break;
    case MBC_5:
        if (a < 0x2000) c->ram_on = (v & 0x0F) == 0x0A;
        else if (a < 0x3000) c->rom_bank = (uint16_t)((c->rom_bank & 0x100) | v);
        else if (a < 0x4000) c->rom_bank = (uint16_t)((c->rom_bank & 0xFF) | (v & 1) << 8);
        else if (a < 0x6000) c->bank2 = v & 0x0F;
        break;
    }
}

static void rtc_second(GbCart *c) {
    if (++c->rtc[0] != 60) return;
    c->rtc[0] = 0;
    if (++c->rtc[1] != 60) return;
    c->rtc[1] = 0;
    if (++c->rtc[2] != 24) return;
    c->rtc[2] = 0;
    if (c->mbc == MBC_HUC3) {
        if (++c->rtc[3] == 0) c->rtc[4] = (c->rtc[4] + 1) & 15;
        return;
    }
    unsigned day = (c->rtc[3] | (c->rtc[4] & 1) << 8) + 1;
    if (day == 512) day = 0, c->rtc[4] |= 0x80;  /* day counter carry */
    c->rtc[3] = (uint8_t)day;
    c->rtc[4] = (uint8_t)((c->rtc[4] & 0xFE) | (day >> 8));
}

void gb_cart_tick(GbCart *c) {
    if (c->mbc == MBC_7) c->mbc7_cycles++;
    if (!c->has_rtc || (c->rtc[4] & 0x40)) return;  /* no clock, or halted */
    if (++c->rtc_cycles < 1048576) return;          /* M-cycles per second */
    c->rtc_cycles = 0;
    rtc_second(c);
}

void gb_cart_rtc_advance(GbCart *c, uint64_t seconds) {
    if (!c->has_rtc || (c->rtc[4] & 0x40)) return;
    if (c->mbc == MBC_HUC3) {
        seconds %= 4096ull * 86400;
        seconds += ((c->rtc[3] | (c->rtc[4] & 15) << 8) * 24ull + c->rtc[2]) * 3600 +
                   c->rtc[1] * 60ull + c->rtc[0];
        unsigned day = (unsigned)(seconds / 86400) & 4095;
        c->rtc[0] = (uint8_t)(seconds % 60);
        c->rtc[1] = (uint8_t)(seconds / 60 % 60);
        c->rtc[2] = (uint8_t)(seconds / 3600 % 24);
        c->rtc[3] = (uint8_t)day;
        c->rtc[4] = (uint8_t)(day >> 8);
        return;
    }
    if (seconds > 512ull * 86400) seconds = 512ull * 86400 + 1;  /* past the day counter: it carried */
    while (seconds--) rtc_second(c);
}
