/* The 93C46 serial EEPROM (eeprom93c46.h), adapted from MAME 0.289's
 * eepromser.cpp and eeprom.cpp. license:BSD-3-Clause; copyright-holders:
 * Aaron Giles (MAME). */
#include "eeprom93c46.h"

#include <string.h>

enum { IN_RESET, WAIT_START, WAIT_COMMAND, READING, WAIT_DATA, WAIT_DONE };
enum { CMD_READ, CMD_WRITE, CMD_ERASE, CMD_LOCK, CMD_UNLOCK, CMD_WRITEALL, CMD_ERASEALL };

static int data_bits(const Eeprom93c46 *e) { return e->org8 ? 8 : 16; }
static int ready(const Eeprom93c46 *e, uint64_t now) { return now >= e->busy_until; }

static uint32_t cell(const Eeprom93c46 *e, const uint8_t *data, unsigned a) {
    return e->org8 ? data[a] : (uint32_t)(data[a * 2] | data[a * 2 + 1] << 8);
}

static void set_cell(Eeprom93c46 *e, uint8_t *data, unsigned a, uint32_t v) {
    if (e->org8) data[a] = (uint8_t)v;
    else data[a * 2] = (uint8_t)v, data[a * 2 + 1] = (uint8_t)(v >> 8);
}

void eeprom_init(Eeprom93c46 *e, int org8) {
    memset(e, 0, sizeof *e);
    memset(e->data, 0xFF, sizeof e->data);
    e->org8 = (uint8_t)(org8 != 0);
    e->locked = 1;
}

/* MAME's times: a write 1.75 ms, an erase 1 ms, WRAL and ERAL 8 ms. */
static void busy(Eeprom93c46 *e, uint64_t now, unsigned us) {
    e->busy_until = now + us;
    e->state = WAIT_DONE;
}

static void execute(Eeprom93c46 *e, uint8_t *data, int n, unsigned cells, uint64_t now) {
    e->address = (uint16_t)(e->accum & (cells - 1));
    switch (e->accum >> n) {
    case 0: {
        static const uint8_t sub[4] = {CMD_LOCK, CMD_WRITEALL, CMD_ERASEALL, CMD_UNLOCK};
        e->command = sub[e->accum >> (n - 2) & 3];
        e->address = 0;
        break;
    }
    case 1: e->command = CMD_WRITE; break;
    case 2: e->command = CMD_READ; break;
    default: e->command = CMD_ERASE; break;
    }
    e->bits = 0;
    switch (e->command) {
    case CMD_READ: e->shift = 0, e->state = READING; break;  /* the dummy 0 before the first clock */
    case CMD_WRITE:
    case CMD_WRITEALL: e->shift = 0, e->state = WAIT_DATA; break;
    case CMD_ERASE:
        if (e->locked) e->state = IN_RESET;
        else set_cell(e, data, e->address, 0xFFFF), busy(e, now, 1000);
        break;
    case CMD_ERASEALL:
        if (e->locked) e->state = IN_RESET;
        else memset(data, 0xFF, cells * (e->org8 ? 1 : 2)), busy(e, now, 8000);
        break;
    case CMD_LOCK: e->locked = 1, e->state = IN_RESET; break;
    default: e->locked = 0, e->state = IN_RESET; break;  /* EWEN */
    }
}

static void execute_write(Eeprom93c46 *e, uint8_t *data, unsigned cells, uint64_t now) {
    if (e->locked) {
        e->state = IN_RESET;
    } else if (e->command == CMD_WRITE) {
        set_cell(e, data, e->address & (cells - 1), e->shift), busy(e, now, 1750);
    } else {  /* WRAL: ANDed into each cell, as MAME (an ERAL comes first) */
        for (unsigned a = 0; a < cells; a++) set_cell(e, data, a, cell(e, data, a) & e->shift);
        busy(e, now, 8000);
    }
}

static void clk_rising(Eeprom93c46 *e, uint8_t *data, int n, unsigned cells, uint64_t now) {
    switch (e->state) {
    case WAIT_START:
        if (e->di && ready(e, now)) e->accum = 0, e->bits = 0, e->state = WAIT_COMMAND;
        break;
    case WAIT_COMMAND:
        e->accum = (uint16_t)(e->accum << 1 | e->di);
        if (++e->bits == 2 + n) execute(e, data, n, cells, now);
        break;
    case READING:  /* the first clock loads the cell; later ones shift 1s in behind it */
        e->shift = e->bits++ == 0 ? cell(e, data, e->address & (cells - 1)) << (32 - data_bits(e)) : e->shift << 1 | 1;
        break;
    case WAIT_DATA:
        e->shift = e->shift << 1 | e->di;
        if (++e->bits == data_bits(e)) execute_write(e, data, cells, now);
        break;
    default: break;
    }
}

static void write_lines(Eeprom93c46 *e, uint8_t *data, int addr_bits, unsigned cells,
                        int cs, int clk, int di, uint64_t now) {
    e->di = (uint8_t)(di & 1);
    if ((clk & 1) != e->clk) {
        e->clk = (uint8_t)(clk & 1);
        if (e->clk) clk_rising(e, data, addr_bits, cells, now);
    }
    if ((cs & 1) != e->cs) {  /* after CLK: a clock in the write that raises CS is not a start bit, as in MAME */
        e->cs = (uint8_t)(cs & 1);
        if (e->cs && e->state == IN_RESET) e->state = WAIT_START;
        else if (!e->cs) e->state = IN_RESET;
    }
}

void eeprom_write_lines(Eeprom93c46 *e, int cs, int clk, int di, uint64_t now) {
    int n = e->org8 ? 7 : 6;
    write_lines(e, e->data, n, 1u << n, cs, clk, di, now);
}

void eeprom93lc56_write(Eeprom93c46 *e, uint8_t data[256], uint8_t port, uint64_t now) {
    /* 128 words, with one ignored high address bit in the command. */
    write_lines(e, data, 8, 128, port >> 7, port >> 6 & 1, port >> 1 & 1, now);
}

int eeprom_do(const Eeprom93c46 *e, uint64_t now) {
    if (e->state == WAIT_START) return ready(e, now);
    if (e->state == READING) return (int)(e->shift >> 31 & 1);
    return 1;  /* tristate, pulled up */
}
