#include "eeprom.h"

#include <string.h>

enum { IDLE, ADDR7, DEVICE, ADDR_HI, ADDR_LO, WRITE, READ };

typedef struct { const char *code; uint16_t size; uint8_t mode, page, wiring; } Game;
enum { SEGA, EA, ACCLAIM_1, ACCLAIM_2 };  /* wirings, below */

/* Product codes (header $183, 8 characters) and their chips, from MAME's table. */
static const Game GAMES[] = {
    {"MK-1215", 128, 1, 3, SEGA},      /* Evander Holyfield's 'Real Deal' Boxing */
    {"MK-1228", 128, 1, 3, SEGA},      /* Greatest Heavyweights */
    {"G-5538", 128, 1, 3, SEGA},       /* Greatest Heavyweights (Japan) */
    {"00004076", 128, 1, 3, SEGA},     /* Honoo no Toukyuuji - Dodge Danpei */
    {"G-4060", 128, 1, 3, SEGA},       /* Wonder Boy V - Monster World III */
    {"00001211", 128, 1, 3, SEGA},     /* Sports Talk Baseball */
    {"T-12046", 128, 1, 3, SEGA},      /* Mega Man - The Wily Wars */
    {"T-12053", 128, 1, 3, SEGA},      /* Rockman - Mega World, The Wily Wars (USA) */
    {"T-50396", 128, 2, 3, EA},        /* NHLPA Hockey 93 */
    {"T-50236", 128, 2, 3, EA},        /* NHLPA Hockey 93 (sample) */
    {"T-50176", 128, 2, 3, EA},        /* Rings of Power */
    {"T-081326", 256, 2, 3, ACCLAIM_1},/* NBA Jam */
    {"T-81033", 256, 2, 3, ACCLAIM_1}, /* NBA Jam (Japan) */
    {"T-81406", 512, 2, 3, ACCLAIM_2}, /* NBA Jam TE, Blockbuster World Video Game Championship II */
    {"T-081276", 256, 2, 3, ACCLAIM_2},/* NFL Quarterback Club */
    {"T-081586", 2048, 2, 7, ACCLAIM_2},/* NFL Quarterback Club 96 */
    {"T-81576", 8192, 3, 7, ACCLAIM_2},/* College Slam */
    {"T-81476", 8192, 3, 7, ACCLAIM_2},/* Frank Thomas Big Hurt Baseball */
};

void md_eeprom_setup(MdEeprom *e, const uint8_t *rom) {
    memset(e, 0, sizeof *e);
    char code[9];
    memcpy(code, rom + 0x183, 8);
    code[8] = 0;
    for (int i = 7; i >= 0 && code[i] == ' '; i--) code[i] = 0;
    const Game *g = NULL;
    for (unsigned i = 0; i < sizeof GAMES / sizeof GAMES[0]; i++)
        if (!strcmp(code, GAMES[i].code)) g = &GAMES[i];
    static const Game flagged = {"", 128, 1, 3, SEGA};  /* the header's EEPROM flag ("RA", $E8, $40): Sega's */
    if (!g && rom[0x1B0] == 'R' && rom[0x1B1] == 'A' && rom[0x1B2] == 0xE8 && rom[0x1B3] == 0x40) g = &flagged;
    if (!g) return;
    e->size = g->size, e->mode = g->mode, e->page = g->page;
    switch (g->wiring) {
    case SEGA: e->sda_in = e->sda_out = e->scl = 0x200001, e->sda_in_bit = e->sda_out_bit = 0, e->scl_bit = 1; break;
    case EA: e->sda_in = e->sda_out = e->scl = 0x200001, e->sda_in_bit = e->sda_out_bit = 7, e->scl_bit = 6; break;
    case ACCLAIM_1: e->sda_in = e->sda_out = e->scl = 0x200001, e->sda_in_bit = 1, e->sda_out_bit = 0, e->scl_bit = 1; break;
    default: e->sda_in = e->sda_out = 0x200001, e->scl = 0x200000, e->sda_in_bit = e->sda_out_bit = e->scl_bit = 0;
    }
    memset(e->mem, 0xFF, sizeof e->mem);
    e->line_scl = e->line_sda = e->out = 1;
}

static void receive(MdEeprom *e, uint8_t byte) {  /* a whole byte from the 68000; sets the ack */
    uint16_t mask = (uint16_t)(e->size - 1);
    e->out = 0;
    switch (e->state) {
    case ADDR7:
        e->addr = (uint16_t)(byte >> 1 & mask);
        e->state = byte & 1 ? READ : WRITE;
        break;
    case DEVICE:
        if ((byte & 0xF0) != 0xA0) { e->state = IDLE, e->out = 1; return; }
        e->block = byte >> 1 & 7;
        e->state = byte & 1 ? READ : e->mode == 3 ? ADDR_HI : ADDR_LO;
        break;
    case ADDR_HI:
        e->block = byte;
        e->state = ADDR_LO;
        break;
    case ADDR_LO:
        e->addr = (uint16_t)((e->block << 8 | byte) & mask);
        e->state = WRITE;
        break;
    case WRITE:
        e->mem[e->addr] = byte;
        e->addr = (uint16_t)((e->addr & ~e->page) | ((e->addr + 1) & e->page));
        break;
    }
    if (e->state == READ) e->data = e->mem[e->addr], e->acked = 1;
}

void md_eeprom_lines(MdEeprom *e, int scl, int sda) {
    scl = !!scl, sda = !!sda;
    if (e->line_scl && scl && sda != e->line_sda) {  /* SDA moves while SCL is high: a start or a stop */
        e->state = sda ? IDLE : e->mode == 1 ? ADDR7 : DEVICE;
        e->bit = e->shift = 0, e->out = 1;
    } else if (!e->line_scl && scl && e->state != IDLE) {  /* SCL rises: a bit is clocked (bit counts them) */
        if (e->bit < 8) {
            if (e->state != READ) e->shift = (uint8_t)(e->shift << 1 | sda);
            e->bit++;
        } else if (e->bit == 9) {  /* the ninth clock: the ack */
            if (e->state == READ && !e->acked) e->master_ack = !sda;
            e->bit = 10;
        }
    } else if (e->line_scl && !scl && e->state != IDLE) {  /* SCL falls: the chip sets SDA for the next clock */
        if (e->bit == 8) {  /* eight bits in: ack them, or release SDA for the 68000's ack */
            e->bit = 9;
            if (e->state == READ && !e->acked) e->out = 1;
            else receive(e, e->shift);
        } else if (e->bit == 10) {  /* the ack is over */
            e->bit = 0, e->shift = 0;
            if (e->state != READ) e->out = 1;
            else if (e->acked) e->acked = 0, e->out = e->data >> 7;
            else if (e->master_ack) {
                e->addr = (uint16_t)((e->addr + 1) & (e->size - 1));
                e->data = e->mem[e->addr], e->out = e->data >> 7;
            } else e->state = IDLE, e->out = 1;
        } else if (e->state == READ && !e->acked) {
            e->out = e->data >> (7 - e->bit) & 1;
        }
    }
    e->line_scl = (uint8_t)scl, e->line_sda = (uint8_t)sda;
}

int md_eeprom_write(MdEeprom *e, uint32_t a, uint8_t v) {
    if (!e->size || (a != e->scl && a != e->sda_out)) return 0;
    int scl = a == e->scl ? v >> e->scl_bit & 1 : e->line_scl;
    int sda = a == e->sda_out ? v >> e->sda_out_bit & 1 : e->line_sda;
    md_eeprom_lines(e, scl, sda);
    return 1;
}

uint8_t md_eeprom_read(const MdEeprom *e, uint32_t a) {
    return a == e->sda_in ? (uint8_t)((e->line_sda & e->out) << e->sda_in_bit) : 0;
}
