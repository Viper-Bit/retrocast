/* The Master System VDP in mode 4, 192 lines (Charles MacDonald, "Sega
 * Master System VDP documentation", SMS Power). Ports: the control port
 * takes an address and a 2-bit code (0 VRAM read, 1 VRAM write, 2 register
 * write, 3 CRAM write); the data port reads through a one-byte buffer.
 * Each line is drawn when it starts, with the registers of that moment. */
#include <string.h>

#include "sms.h"

/* ---- ports ---- */
void sms_vdp_write_ctrl(SmsVdp *v, uint8_t val) {
    if (!v->latch) {
        v->addr = (uint16_t)((v->addr & 0x3F00) | val);
        v->latch = 1;
        return;
    }
    v->latch = 0;
    v->code = val >> 6;
    v->addr = (uint16_t)((val & 0x3F) << 8 | (v->addr & 0xFF));
    if (v->code == 0) {  /* VRAM read: the buffer is filled at once */
        v->buffer = v->vram[v->addr];
        v->addr = (v->addr + 1) & 0x3FFF;
    } else if (v->code == 2) {
        v->reg[val & 0x0F] = (uint8_t)v->addr;
    }
}

uint8_t sms_vdp_read_data(SmsVdp *v) {
    uint8_t r = v->buffer;
    v->latch = 0;
    v->buffer = v->vram[v->addr];
    v->addr = (v->addr + 1) & 0x3FFF;
    return r;
}

void sms_vdp_write_data(SmsVdp *v, uint8_t val) {
    v->latch = 0;
    if (v->code == 3 && v->gg) {
        /* 64 bytes, two per colour: an even address latches the low byte,
         * the odd one writes the colour */
        if (v->addr & 1) v->cram[v->addr >> 1 & 31] = (uint16_t)(v->cram_latch | (val & 0x0F) << 8);
        else v->cram_latch = val;
    } else if (v->code == 3) v->cram[v->addr & 0x1F] = val & 0x3F;
    else v->vram[v->addr] = val;
    v->buffer = val;
    v->addr = (v->addr + 1) & 0x3FFF;
}

/* Reading the status clears its flags and the pending line interrupt. */
uint8_t sms_vdp_read_status(SmsVdp *v) {
    uint8_t r = v->status | 0x1F;
    v->status = 0;
    v->line_flag = 0;
    v->latch = 0;
    return r;
}

/* The V counter jumps back after $DA (NTSC) or $F2 (PAL), so it fits a byte. */
uint8_t sms_vdp_vcount(const Sms *s) {
    unsigned l = s->line;
    if (!s->pal) return (uint8_t)(l <= 0xDA ? l : l - 6);
    return (uint8_t)(l <= 0xF2 ? l : l - 0x39);
}

/* shortcut: the H counter as the position in the line, pixel clocks / 2, without the
 * real counter's jump in the blanking; exact values only matter to light guns */
uint8_t sms_vdp_hcount(const Sms *s) {
    uint64_t t = s->cpu.tstates - s->line_start;
    if (t >= SMS_LINE_TSTATES) t = SMS_LINE_TSTATES - 1;
    return (uint8_t)(t * 3 / 4);
}

/* The TMS9918 modes' fixed palette as the SMS VDP shows it, --BBGGRR (Genesis Plus GX). */
static const uint8_t TMS[16] = {0x00, 0x00, 0x08, 0x0C, 0x10, 0x30, 0x01, 0x3C,
                                0x02, 0x03, 0x05, 0x0F, 0x04, 0x33, 0x15, 0x3F};

uint32_t sms_color(const Sms *s, unsigned index) {
    unsigned c = index >= 32 ? TMS[index & 15] : s->vdp.cram[index & 31];
    if (index >= 32) return 0xFF000000u | (uint32_t)(c & 3) * 85 << 16 | (uint32_t)(c >> 2 & 3) * 85 << 8 | (uint32_t)(c >> 4 & 3) * 85;
    if (s->vdp.gg)  /* ----BBBBGGGGRRRR */
        return 0xFF000000u | (c & 15) * 17u << 16 | (c >> 4 & 15) * 17u << 8 | (c >> 8 & 15) * 17u;
    return 0xFF000000u | (uint32_t)(c & 3) * 85 << 16 | (uint32_t)(c >> 2 & 3) * 85 << 8 | (uint32_t)(c >> 4 & 3) * 85;
}

/* ---- drawing ---- */
/* A tile row: 4 bytes, one bitplane each, the leftmost pixel in bit 7. */
static unsigned pixel(const uint8_t *row, unsigned x) {
    unsigned b = 7 - x;
    return (row[0] >> b & 1) | (row[1] >> b & 1) << 1 | (row[2] >> b & 1) << 2 | (row[3] >> b & 1) << 3;
}

/* Graphics I and II (reg 0 bit 1), the TMS9918 modes: 32x24 names of 8x8
 * patterns, two colours per pattern row (Graphics I: per 8 patterns),
 * colour 0 the backdrop; 32 sprites of 4 bytes, 4 to a line. Frame colours
 * 32-47 (sms_color). shortcut: no text or multicolour mode, no fifth-sprite
 * number in the status; add them if a game needs them. */
static void tms_line(SmsVdp *v, uint8_t *out, unsigned line) {
    unsigned backdrop = v->reg[7] & 15, g2 = v->reg[0] & 2;
    const uint8_t *names = &v->vram[(v->reg[2] & 0x0F) << 10 | (line >> 3) * 32];
    for (unsigned x = 0; x < SMS_WIDTH; x++) {
        unsigned n = names[x >> 3], pat, col;
        if (g2) {
            n |= (line >> 6) << 8;
            pat = ((v->reg[4] & 4) << 11) | ((n & ((v->reg[4] & 3) << 8 | 0xFF)) << 3);
            col = ((v->reg[3] & 0x80) << 6) | ((n & ((v->reg[3] & 0x7F) << 3 | 7)) << 3);
            pat |= line & 7, col |= line & 7;
        } else {
            pat = (v->reg[4] & 7) << 11 | n << 3 | (line & 7);
            col = v->reg[3] << 6 | n >> 3;
        }
        unsigned c = v->vram[col & 0x3FFF] >> (v->vram[pat & 0x3FFF] >> (7 - (x & 7)) & 1 ? 4 : 0) & 15;
        out[x] = (uint8_t)(32 + (c ? c : backdrop));
    }
    const uint8_t *sat = &v->vram[(v->reg[5] & 0x7F) << 7];
    unsigned size = v->reg[1] & 2 ? 16 : 8, zoom = v->reg[1] & 1 ? 2 : 1, found = 0;
    uint8_t taken[SMS_WIDTH] = {0};
    for (unsigned i = 0; i < 32; i++, sat += 4) {
        if (sat[0] == 0xD0) break;
        unsigned r = (line - (sat[0] + 1)) & 0xFF;
        if (r >= size * zoom) continue;
        if (++found > 4) { v->status |= 0x40; break; }
        r /= zoom;
        unsigned name = size == 16 ? sat[2] & 0xFC : sat[2], c = sat[3] & 15;
        int x0 = sat[1] - (sat[3] & 0x80 ? 32 : 0);
        for (unsigned px = 0; px < size * zoom; px++) {
            int x = x0 + (int)px;
            unsigned p = px / zoom;
            uint8_t bits = v->vram[((v->reg[6] & 7) << 11 | (name + (p >> 3) * 2) << 3 | r) & 0x3FFF];
            if (x < 0 || x >= SMS_WIDTH || !(bits >> (7 - (p & 7)) & 1)) continue;
            if (taken[x]) { v->status |= 0x20; continue; }
            taken[x] = 1;
            if (c) out[x] = (uint8_t)(32 + c);
        }
    }
}

static void draw_line(Sms *s, unsigned line) {
    SmsVdp *v = &s->vdp;
    uint8_t *out = v->frame + line * SMS_WIDTH;
    uint8_t backdrop = (uint8_t)(16 | (v->reg[7] & 15));
    if (!(v->reg[1] & 0x40)) { memset(out, backdrop, SMS_WIDTH); return; }  /* display off */
    if (!(v->reg[0] & 4)) { tms_line(v, out, line); return; }               /* not mode 4 */

    /* background: 32x28 tiles, scrolled; the top two rows (reg 0 bit 6) and
     * the right eight columns (bit 7) can be held still */
    uint8_t prio[SMS_WIDTH];
    uint16_t names = (uint16_t)((v->reg[2] & 0x0E) << 10);
    unsigned hs = (v->reg[0] & 0x40) && line < 16 ? 0 : v->reg[8];
    for (unsigned x = 0; x < SMS_WIDTH; x++) {
        unsigned y = (line + ((v->reg[0] & 0x80) && x >= 192 ? 0 : v->vscroll)) % 224;
        unsigned bx = (x - hs) & 255;  /* the scroll moves the plane right */
        const uint8_t *e = &v->vram[names + (y >> 3) * 64 + (bx >> 3) * 2];
        unsigned info = e[0] | e[1] << 8;
        unsigned row = info & 0x400 ? 7 - (y & 7) : y & 7;
        unsigned c = pixel(&v->vram[(info & 0x1FF) * 32 + row * 4], info & 0x200 ? 7 - (bx & 7) : bx & 7);
        out[x] = (uint8_t)((info & 0x800 ? 16 : 0) | c);
        prio[x] = (info & 0x1000) && c;  /* over sprites, where not colour 0 */
    }

    /* sprites: Y in the first 64 bytes of the table, then X and tile pairs at $80 */
    const uint8_t *sat = &v->vram[(v->reg[5] & 0x7E) << 7];
    unsigned h = v->reg[1] & 2 ? 16 : 8, zoom = v->reg[1] & 1 ? 2 : 1;
    unsigned base = v->reg[6] & 4 ? 256 : 0;
    uint8_t taken[SMS_WIDTH] = {0};
    unsigned found = 0;
    for (unsigned i = 0; i < 64; i++) {
        unsigned y = sat[i];
        if (y == 0xD0) break;  /* the end of the list in 192-line mode */
        unsigned r = (line - (y + 1)) & 0xFF;
        if (r >= h * zoom) continue;
        if (++found > 8) { v->status |= 0x40; break; }
        int x0 = (int)sat[0x80 + i * 2] - (v->reg[0] & 8 ? 8 : 0);
        unsigned tile = sat[0x81 + i * 2] | base;
        if (h == 16) tile &= ~1u;
        const uint8_t *bits = &v->vram[(tile * 32 + (r / zoom) * 4) & 0x3FFF];
        for (unsigned px = 0; px < 8 * zoom; px++) {
            int x = x0 + (int)px;
            if (x < 0 || x >= SMS_WIDTH) continue;
            unsigned c = pixel(bits, px / zoom);
            if (!c) continue;
            if (taken[x]) { v->status |= 0x20; continue; }  /* the earlier sprite stays in front */
            taken[x] = 1;
            if (!prio[x]) out[x] = (uint8_t)(16 | c);
        }
    }
    if (v->reg[0] & 0x20) memset(out, backdrop, 8);  /* the left column hidden */
}

/* A line's start: draw it (0-191), count the line interrupt (0-192, reload
 * after), raise the frame interrupt at line 193. */
void sms_vdp_line(Sms *s, unsigned line) {
    SmsVdp *v = &s->vdp;
    if (line == 0) v->vscroll = v->reg[9];
    if (line < SMS_HEIGHT) draw_line(s, line);
    if (line <= SMS_HEIGHT) {
        if (v->line_counter-- == 0) {
            v->line_counter = v->reg[10];
            v->line_flag = 1;
        }
    } else {
        v->line_counter = v->reg[10];
    }
    if (line == SMS_HEIGHT + 1) v->status |= 0x80;
}
