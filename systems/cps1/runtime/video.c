/* The CPS-A / CPS-B picture (cps1.h): the palette, three scroll layers and
 * sprites, drawn a frame at a time into s->frame as palette indices.
 *   graphics: 4 bits a pixel, pen 15 transparent; a row of 8 pixels is 4
 *     bytes, one per plane (bit 7 the leftmost pixel, byte n plane n).
 *     A 16x16 tile (sprites, scroll2) is 128 bytes, rows of 8; a 32x32 tile
 *     (scroll3) 512, rows of 16; an 8x8 scroll1 tile is half of a 64-byte
 *     block, rows of 8 bytes: the left half in even map columns, the right
 *     half in odd ones.
 *   maps (64x64 tiles, 4 bytes each: code, attributes) are scanned in
 *     blocks of 32 (scroll1), 16 (scroll2) or 8 (scroll3) rows. Attributes:
 *     bits 0-4 palette, 5 flip X, 6 flip Y, 7-8 the priority group.
 *   sprites: 4 words (x, y, code, attributes), to an attribute $FFxx;
 *     attributes add the block count (bits 8-11 across, 12-15 down) and
 *     the first entry is drawn on top.
 *   the palette: 6 pages of 512 colours (sprites, scroll1-3, stars 1-2),
 *     copied from graphics RAM when the palette base is written, the pages
 *     the CPS-B's palette control enables; each word is brightness and
 *     4-bit red, green, blue.
 *   layers: the CPS-B layer control orders them bottom to top (bits 6-7,
 *     8-9, 10-11, 12-13: 0 sprites, 1-3 scroll1-3) and enables them; pens of
 *     the layer just below the sprites listed in its group's priority mask
 *     are drawn over the sprites.
 * Sources: docs/sources.md (CPS-1). */
#include <string.h>

#include "cps1.h"

enum { A_OBJ = 0x00, A_SCROLL1 = 0x02, A_SCROLL2 = 0x04, A_SCROLL3 = 0x06, A_OTHER = 0x08, A_PALETTE = 0x0A,
       A_S1X = 0x0C, A_S1Y = 0x0E, A_S2X = 0x10, A_S2Y = 0x12, A_S3X = 0x14, A_S3Y = 0x16,
       A_ROWSCROLL = 0x20, A_VIDEO = 0x22 };
enum { BACKGROUND = 0xBFF, RAW_X = 64, RAW_Y = 16 };

static uint16_t areg(const Cps1 *s, unsigned off) { return s->cpsa[off >> 1]; }

/* a table in graphics RAM from a CPS-A base register, aligned to `align` */
static const uint8_t *base(const Cps1 *s, unsigned off, uint32_t align) {
    uint32_t a = ((uint32_t)areg(s, off) << 8 & 0x3FFFF) & ~(align - 1);
    return a < sizeof s->gfxram ? s->gfxram + a : s->gfxram;
}

static uint16_t word(const uint8_t *p) { return (uint16_t)(p[0] << 8 | p[1]); }

int cps1_gfx_map(const Cps1Mapper *m, int type, int code) {
    if (!m->n) return code;
    int shift = type == CPS1_GFX_SCROLL1 ? 0 : type == CPS1_GFX_SCROLL3 ? 3 : 1;
    uint32_t unit = (uint32_t)code << shift;
    for (int i = 0; i < m->n; i++) {
        const Cps1Range *r = &m->range[i];
        if (unit < r->start || unit > r->end || !(r->type & type)) continue;
        uint32_t base = 0;
        for (int b = 0; b < r->bank; b++) base += m->bank_size[b];
        return (int)((base + (unit & (m->bank_size[r->bank] - 1))) >> shift);
    }
    return -1;
}

void cps1_palette_upload(Cps1 *s) {
    const uint8_t *src = base(s, A_PALETTE, 0x400), *start = src, *end = s->gfxram + sizeof s->gfxram;
    uint16_t ctrl = s->cpsb[s->rom->game->b.pal_ctrl >> 1];
    for (int page = 0; page < 6; page++) {
        if (ctrl >> page & 1) {
            for (int i = 0; i < 0x200 && src + 2 <= end; i++, src += 2) s->pal[page * 0x200 + i] = word(src);
        } else if (src != start) {
            src += 0x400;  /* a page left out after one copied leaves a gap */
        }
    }
}

uint32_t cps1_color(const Cps1 *s, uint16_t index) {
    uint16_t v = s->pal[index % 0xC00];
    unsigned bright = 0x0F + (v >> 12 & 0xF) * 2;
    unsigned r = (v >> 8 & 0xF) * 0x11 * bright / 0x2D, g = (v >> 4 & 0xF) * 0x11 * bright / 0x2D,
             b = (v & 0xF) * 0x11 * bright / 0x2D;
    return r << 16 | g << 8 | b;
}

/* pen (0-15) of pixel (x, y) in the tile at addr, rows of rowbytes */
static unsigned pen(const Cps1Rom *r, uint32_t addr, unsigned rowbytes, unsigned x, unsigned y) {
    uint32_t at = addr + y * rowbytes + (x >> 3) * 4;
    if (at + 4 > r->size[CPS1_R_GFX]) return 15;
    const uint8_t *b = r->region[CPS1_R_GFX] + at;
    unsigned bit = 7 - (x & 7);
    return (b[0] >> bit & 1) | (b[1] >> bit & 1) << 1 | (b[2] >> bit & 1) << 2 | (b[3] >> bit & 1) << 3;
}

typedef struct {
    unsigned tile, rowbytes, block;  /* tile size in pixels; bytes a tile row; rows per scan block */
    unsigned bytes;                  /* bytes a tile code steps */
    unsigned map, sx, sy;            /* CPS-A registers */
    uint16_t pal_base;
} Layer;

static const Layer layers[4] = {
    {0},
    {8, 8, 32, 64, A_SCROLL1, A_S1X, A_S1Y, 0x200},
    {16, 8, 16, 128, A_SCROLL2, A_S2X, A_S2Y, 0x400},
    {32, 16, 8, 512, A_SCROLL3, A_S3X, A_S3Y, 0x600},
};

/* The layer's pen at a screen pixel: 15 when transparent; *index and *group
 * filled otherwise. */
/* A bootleg's scroll X offsets for layers 1-3 (MAME's bootleg_kludge). */
static unsigned kludge_x(const Cps1 *s, int n) {
    static const int16_t offs[16][3] = {[1] = {-0x0C, -0x0E, -0x10}, [2] = {-0x10, -0x10, -0x10}, [3] = {-0x08, -0x0B, -0x0C},
                                        [0xE] = {-0x46, -0x40, -0x46}, [0xF] = {-0x40, -0x40, -0x40}};
    static const int16_t wonders[3] = {4, 6, 0xA};  /* 3wondersb */
    uint8_t k = s->rom->game->kludge;
    return (unsigned)(k == 0x88 ? wonders[n - 1] : offs[k & 15][n - 1]);
}

static unsigned layer_pixel(const Cps1 *s, int n, unsigned x, unsigned y, uint16_t *index, unsigned *group) {
    const Layer *l = &layers[n];
    const uint8_t *map = base(s, l->map, 0x4000);
    unsigned size = l->tile * 64, mx = x + RAW_X + areg(s, l->sx) + kludge_x(s, n), my = (y + RAW_Y + areg(s, l->sy)) & (size - 1);
    if (n == 2 && areg(s, A_VIDEO) & 1) {  /* row scroll: an X offset per map row */
        const uint8_t *other = base(s, A_OTHER, 0x800);
        mx += word(other + ((my + areg(s, A_ROWSCROLL)) & 0x3FF) * 2);
    }
    mx &= size - 1;
    unsigned col = mx / l->tile, row = my / l->tile, b = l->block;
    unsigned i = (row & (b - 1)) + ((col & 0x3F) * b) + ((row & ~(b - 1) & 0x3F) << 6);
    const uint8_t *e = map + i * 4;
    if (e + 4 > s->gfxram + sizeof s->gfxram) return 15;
    uint16_t attr = word(e + 2);
    int code = cps1_gfx_map(&s->rom->game->mapper, n == 1 ? CPS1_GFX_SCROLL1 : n == 2 ? CPS1_GFX_SCROLL2 : CPS1_GFX_SCROLL3, word(e));
    if (code < 0) return 15;  /* the board's PAL leaves it out */
    unsigned px = mx % l->tile, py = my % l->tile;
    if (attr & 0x20) px = l->tile - 1 - px;
    if (attr & 0x40) py = l->tile - 1 - py;
    if (n == 1) px += (col & 1) * 8;  /* scroll1: the half of the 64-byte block */
    unsigned p = pen(s->rom, (uint32_t)code * l->bytes, l->rowbytes, px, py);
    *index = (uint16_t)(l->pal_base + (attr & 0x1F) * 16 + p);
    *group = attr >> 7 & 3;
    return p;
}

/* The frame is drawn at once from VBlank's state, as MAME draws it: the
 * CPS-1 has no raster interrupt to time a change within a frame by. */
static void draw_sprites(Cps1 *s, const uint8_t *high) {
    const uint8_t *obj = base(s, A_OBJ, 0x800);
    int last = 0;
    uint8_t kludge = s->rom->game->kludge;
    if ((kludge & 15) == 3)  /* captcommb: CPS-2's end marker, Y of $8000 or more */
        while (last < 256 && word(obj + last * 8 + 2) < 0x8000) last++;
    else
        while (last < 256 && (word(obj + last * 8 + 6) & 0xFF00) != 0xFF00) last++;
    for (int i = 0; i < last; i++) {  /* the first entry ends on top; some bootlegs' the last */
        int k = kludge & 0x40 ? i : last - 1 - i;
        const uint8_t *e = obj + k * 8;
        unsigned x = word(e), y = word(e + 2), code = word(e + 4), attr = word(e + 6);
        unsigned nx = (attr >> 8 & 0xF) + 1, ny = (attr >> 12 & 0xF) + 1, fx = attr >> 5 & 1, fy = attr >> 6 & 1;
        for (unsigned by = 0; by < ny; by++)
            for (unsigned bx = 0; bx < nx; bx++) {
                int c = cps1_gfx_map(&s->rom->game->mapper, CPS1_GFX_SPRITES,
                                     (int)((code & ~0xFu) + ((code + bx) & 0xF) + 0x10 * by));
                if (c < 0) continue;
                unsigned ox = x + 16 * (fx ? nx - 1 - bx : bx), oy = y + 16 * (fy ? ny - 1 - by : by);
                for (unsigned ty = 0; ty < 16; ty++)
                    for (unsigned tx = 0; tx < 16; tx++) {
                        int sx = (int)((ox + tx - RAW_X) & 0x1FF), sy = (int)((oy + ty - RAW_Y) & 0x1FF);
                        if (sx >= CPS1_WIDTH || sy >= CPS1_HEIGHT || high[sy * CPS1_WIDTH + sx]) continue;
                        unsigned p = pen(s->rom, (uint32_t)c * 128u, 8, fx ? 15 - tx : tx, fy ? 15 - ty : ty);
                        if (p != 15) s->frame[sy * CPS1_WIDTH + sx] = (uint16_t)((attr & 0x1F) * 16 + p);
                    }
            }
    }
}

/* The two star layers (MAME's cps1_render_stars): 4,096 star bytes 8 apart
 * from the game's star ROM, byte +4 the first layer (scrolled by CPS-A
 * $1C/$1E, colours $A00), byte +0 the second ($18/$1A, $800); column
 * (index / 256) x 32 + the byte's low 5 bits, row index % 256, a low 5 bits
 * of 15 meaning none; the colour steps every 16 frames. */
static void draw_stars(Cps1 *s, uint16_t ctrl) {
    const Cps1Game *g = s->rom->game;
    if (g->stars < 0 || (uint32_t)g->stars + 0x8000 > s->rom->size[CPS1_R_GFX]) return;
    const uint8_t *rom = s->rom->region[CPS1_R_GFX] + g->stars;
    for (int layer = 0; layer < 2; layer++) {
        if (!(ctrl & g->b.layer_enable[3 + layer])) continue;
        unsigned sx_reg = areg(s, layer ? 0x18 : 0x1C), sy_reg = areg(s, layer ? 0x1A : 0x1E);
        uint16_t base = layer ? 0x800 : 0xA00;
        for (unsigned offs = 0; offs < 0x1000; offs++) {
            unsigned col = rom[8 * offs + (layer ? 0 : 4)];
            if ((col & 0x1F) == 0x0F) continue;
            int sx = (int)(((offs / 256) * 32 - sx_reg + (col & 0x1F)) & 0x1FF) - RAW_X;
            int sy = (int)((offs % 256 - sy_reg) & 0xFF) - RAW_Y;
            if (sx < 0 || sx >= CPS1_WIDTH || sy < 0 || sy >= CPS1_HEIGHT) continue;
            unsigned cnt = (unsigned)(s->frames / 16) % (col & 0x80 ? 15 : 16);
            s->frame[sy * CPS1_WIDTH + sx] = (uint16_t)(base + ((col & 0xE0) >> 1) + cnt);
        }
    }
}

void cps1_render(Cps1 *s) {
    static uint8_t high[CPS1_WIDTH * CPS1_HEIGHT];
    const Cps1B *b = &s->rom->game->b;
    uint8_t kludge = s->rom->game->kludge;  /* bootlegs' wiring, set each frame as MAME does */
    if ((kludge & 15) == 1 || (kludge & 15) == 2) s->cpsa[A_OBJ >> 1] = 0x9100;
    if (kludge == 0x88) {  /* 3wondersb: registers wired, not written */
        s->cpsb[0x30 >> 1] = 0x3F;
        s->cpsa[A_VIDEO >> 1] = 0x3E, s->cpsa[A_SCROLL2 >> 1] = 0x90C0, s->cpsa[A_SCROLL3 >> 1] = 0x9100, s->cpsa[A_PALETTE >> 1] = 0x9140;
    }
    if (kludge & 0x80) cps1_palette_upload(s);  /* the palette taken every frame */
    uint16_t ctrl = s->cpsb[b->layer_ctrl >> 1];
    int order[4] = {ctrl >> 6 & 3, ctrl >> 8 & 3, ctrl >> 10 & 3, ctrl >> 12 & 3};
    for (int i = 0; i < CPS1_WIDTH * CPS1_HEIGHT; i++) s->frame[i] = BACKGROUND;
    memset(high, 0, sizeof high);
    draw_stars(s, ctrl);
    for (int k = 0; k < 4; k++) {
        int n = order[k];
        if (n == 0) {
            draw_sprites(s, high);
            continue;
        }
        if (!(ctrl & b->layer_enable[n - 1])) continue;
        int below_sprites = k < 3 && order[k + 1] == 0;
        for (unsigned y = 0; y < CPS1_HEIGHT; y++)
            for (unsigned x = 0; x < CPS1_WIDTH; x++) {
                uint16_t index;
                unsigned group, p = layer_pixel(s, n, x, y, &index, &group);
                if (p == 15) continue;
                s->frame[y * CPS1_WIDTH + x] = index;
                if (below_sprites && b->prio[group] != CPS1_NONE && s->cpsb[b->prio[group] >> 1] >> p & 1)  /* no port (qad): none */
                    high[y * CPS1_WIDTH + x] = 1;
            }
    }
    if (areg(s, A_VIDEO) & 0x8000)  /* flip screen: the picture turned 180 degrees */
        for (int a = 0, b = CPS1_WIDTH * CPS1_HEIGHT - 1; a < b; a++, b--) {
            uint16_t t = s->frame[a];
            s->frame[a] = s->frame[b], s->frame[b] = t;
        }
}

void cps1_picture(const Cps1 *s, uint32_t *rgb, int *w, int *h) {
    int turned = s->rom->game->rotate == 270;
    *w = turned ? CPS1_HEIGHT : CPS1_WIDTH, *h = turned ? CPS1_WIDTH : CPS1_HEIGHT;
    for (int y = 0; y < CPS1_HEIGHT; y++)
        for (int x = 0; x < CPS1_WIDTH; x++) {
            uint32_t c = cps1_color(s, s->frame[y * CPS1_WIDTH + x]);
            if (turned) rgb[(CPS1_WIDTH - 1 - x) * CPS1_HEIGHT + y] = c;  /* 90 degrees anticlockwise */
            else rgb[y * CPS1_WIDTH + x] = c;
        }
}
