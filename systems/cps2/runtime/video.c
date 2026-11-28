/* CPS-2 tile and object layout from MAME 0.289 cps2.cpp and cps1_v.cpp.
 * Tile addressing and palette conversion follow the CPS-1 renderer. */
#include "machine.h"

#include <stdlib.h>
#include <string.h>

static uint16_t word(const uint8_t *p)
{
    return (uint16_t)(p[0] << 8 | p[1]);
}

static unsigned base(const Cps2Machine *s, unsigned reg, unsigned align)
{
    return ((unsigned)word(s->cps_a + reg) << 8 & 0x3ffff) & ~(align - 1);
}

int cps2_video_init(Cps2Machine *s, const Cps2Rom *rom)
{
    const uint8_t *raw = cps2_region(rom, "gfx", &s->tile_size);
    if (!raw || !s->tile_size || s->tile_size % 0x200000)
        return -1;
    s->tiles = malloc(s->tile_size);
    if (!s->tiles)
        return -1;
    /* Unshuffle each bank: the even 64-bit groups precede the odd groups. */
    for (size_t bank = 0; bank < s->tile_size; bank += 0x200000) {
        for (unsigned i = 0; i < 0x40000; ++i) {
            unsigned source = ((i << 1) & 0x3ffff) | (i >> 17);
            memcpy(s->tiles + bank + i * 8, raw + bank + source * 8, 8);
        }
    }
    return 0;
}

void cps2_palette_upload(Cps2Machine *s)
{
    unsigned first = base(s, 0x0a, 0x400), at = first;
    unsigned control = word(s->cps_b + 0x30);
    for (unsigned page = 0; page < 6; ++page) {
        if (control & (1u << page)) {
            for (unsigned i = 0; i < 512 && at + 1 < sizeof(s->graphics); ++i, at += 2)
                s->palette[page * 512 + i] = word(s->graphics + at);
        } else if (at != first) {
            at += 0x400;
        }
    }
}

static uint32_t rgb(uint16_t v)
{
    unsigned light = 15 + 2 * (v >> 12);
    return ((v >> 8 & 15) * 17 * light / 45) << 16 |
           ((v >> 4 & 15) * 17 * light / 45) << 8 |
           (v & 15) * 17 * light / 45;
}

static unsigned pen(const Cps2Machine *s, unsigned address, unsigned x)
{
    address += (x >> 3) * 4;
    if (address + 4 > s->tile_size)
        return 15;
    const uint8_t *p = s->tiles + address;
    unsigned shift = 7 - (x & 7);
    return (p[0] >> shift & 1) | (p[1] >> shift & 1) << 1 |
           (p[2] >> shift & 1) << 2 | (p[3] >> shift & 1) << 3;
}

static unsigned tile_pixel(const Cps2Machine *s, unsigned layer, unsigned x, unsigned y)
{
    unsigned tile = 4u << layer, block = 256 / tile;
    unsigned mx = x + 64 + word(s->cps_a + 8 + layer * 4);
    unsigned my = (y + 16 + word(s->cps_a + 10 + layer * 4)) & (tile * 64 - 1);
    if (layer == 2 && (word(s->cps_a + 0x22) & 1)) {
        unsigned row = (y + 16 + word(s->cps_a + 0x20)) & 1023;
        unsigned address = base(s, 8, 0x800) + row * 2;
        if (address + 1 < sizeof(s->graphics))
            mx += word(s->graphics + address);
    }
    unsigned col = mx / tile & 63, row = my / tile;
    unsigned index = (row & (block - 1)) + col * block + ((row & ~(block - 1)) << 6);
    unsigned address = base(s, layer * 2, 0x4000) + index * 4;
    if (address + 3 >= sizeof(s->graphics))
        return 15;
    unsigned code = word(s->graphics + address), attr = word(s->graphics + address + 2);
    unsigned px = mx % tile, py = my % tile;
    if (attr & 0x20) px = tile - 1 - px;
    if (attr & 0x40) py = tile - 1 - py;
    if (layer == 1) px += (col & 1) * 8;
    unsigned pitch = layer == 3 ? 16 : 8;
    if (layer == 3) code &= 0x3fff;
    /* Scroll layers select the second 8 MiB bank through the CPS-B mapper. */
    unsigned address_bytes = (0x800000 + code * tile * pitch) % s->tile_size;
    return layer * 512 + (attr & 31) * 16 + pen(s, address_bytes + py * pitch, px);
}

static void draw_objects(Cps2Machine *s, unsigned y, uint8_t *coverage,
                         const unsigned masks[8], uint16_t *pixels)
{
    const uint8_t *objects = s->latched_objects;
    unsigned end = 0;
    while (end < sizeof(s->latched_objects) && word(objects + end + 2) < 0x8000 &&
           word(objects + end + 6) < 0xff00)
        end += 8;
    while (end) {
        end -= 8;
        unsigned x = word(objects + end), sy = word(objects + end + 2);
        unsigned code = word(objects + end + 4) + ((sy & 0x6000) << 3);
        unsigned attr = word(objects + end + 6), mask = masks[x >> 13];
        unsigned nx = 1 + (attr >> 8 & 15), ny = 1 + (attr >> 12);
        unsigned row = (y - sy + ((attr & 0x80) ? 0 : word(s->output + 10))) & 1023;
        if (row >= ny * 16)
            continue;
        if (attr & 0x40) row = ny * 16 - 1 - row;
        unsigned left = x - ((attr & 0x80) ? 0 : word(s->output + 8));
        for (unsigned col = 0; col < nx * 16; ++col) {
            unsigned at = (left + col) & 1023;
            if (at >= 384 || coverage[at] == 8)
                continue;
            unsigned px = (attr & 0x20) ? nx * 16 - 1 - col : col;
            unsigned tile = attr & 0x60 ? code + px / 16 : (code & ~15u) + ((code + px / 16) & 15);
            tile += row / 16 * 16;
            unsigned color = pen(s, tile * 128 % s->tile_size + (row & 15) * 8, px & 15);
            if (color == 15)
                continue;
            if (!(mask & (1u << coverage[at])))
                pixels[at] = (attr & 31) * 16 + color;
            coverage[at] = 8;
        }
    }
}

void cps2_video_render(Cps2Machine *s, unsigned end)
{
    unsigned control = word(s->cps_b + 0x26), video = word(s->cps_a + 0x22);
    unsigned layers[3] = {0}, priorities[3] = {0}, count = 0;
    for (unsigned shift = 6; shift <= 12 && count < 3; shift += 2) {
        unsigned layer = control >> shift & 3;
        if (layer) {
            layers[count] = layer;
            priorities[count++] = s->priority >> (4 * layer) & 15;
        }
    }
    unsigned a = priorities[0], b = priorities[1], c = priorities[2];
    unsigned first = 0xaa & ~(a > b ? 0x88 : 0) & ~(a > c ? 0xa0 : 0);
    unsigned second = 0xcc & ~(b > c ? 0xc0 : 0);
    unsigned masks[8] = {0xff};
    for (unsigned i = 1; i < 8; ++i)
        masks[i] = (i <= a) && (i <= b) && (i <= c) ? 0xfe :
                   (i <= a ? first : 0) | (i <= b ? second : 0) | (i <= c ? 0xf0 : 0);

    for (; s->rendered < end; ++s->rendered) {
        unsigned y = s->rendered;
        uint8_t coverage[384] = {0};
        uint16_t pixels[384];
        for (unsigned x = 0; x < 384; ++x) pixels[x] = 0xbff;
        for (unsigned i = 0; i < count; ++i) {
            unsigned layer = layers[i];
            if (!(control & (1u << layer)) || (layer == 2 && !(video & 4)) ||
                (layer == 3 && !(video & 8)))
                continue;
            for (unsigned x = 0; x < 384; ++x) {
                unsigned pixel = tile_pixel(s, layer, x, y);
                if ((pixel & 15) != 15) {
                    pixels[x] = (uint16_t)pixel;
                    coverage[x] |= 1u << i;
                }
            }
        }
        draw_objects(s, y, coverage, masks, pixels);
        for (unsigned x = 0; x < 384; ++x) {
            unsigned at = (video & 0x8000) ? (223 - y) * 384 + (383 - x) : y * 384 + x;
            s->frame[at] = rgb(s->palette[pixels[x]]);
        }
    }
}
