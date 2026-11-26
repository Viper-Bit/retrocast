/* The PPU, DMG and CGB mode (Pan Docs "Rendering", "LCDC", "STAT", "Tile
 * Data", "Tile Maps", "OAM", "Palettes", "BG Map Attributes", "LCD Color
 * Palettes"): 456 dots a line, 154 lines; mode 2 (OAM scan) dots
 * 0-79, mode 3 (drawing) 172 dots and more for SCX, the window and
 * objects, then mode 0 (hblank); lines 144-153 mode 1 (vblank).
 * Mode 3 is drawn a dot at a time (stepped with the CPU's M-cycles), so a
 * register write in the middle of a line takes effect at its pixel.
 * shortcut: not a FIFO: a tile row (and an object) is fetched whole at
 * the dot its first pixel is due, not over the 6 dots hardware takes. */
#include <string.h>

#include "gb.h"

/* The game uses the Color's features (not a DMG game on a Color: compatibility mode) */
static int cgb_game(const Gb *g) { return g->cgb && !g->compat; }

int ppu_mode(const Gb *g) { return g->lcdc & 0x80 ? g->mode : 0; }
/* The mode a CPU read of STAT, or an access to VRAM, OAM or palette RAM,
 * finds: the one a dot before the end of the cycle (mooneye intr_2_*_timing);
 * interrupts use the real one. */
int ppu_vmode(const Gb *g) { return g->lcdc & 0x80 ? g->mode_seen : 0; }

/* The STAT interrupt line is the OR of its enabled sources; it fires on a rising edge.
 * DMG: the mode 2 source also pulses as vblank begins, line 144's first cycle (mooneye vblank_stat_intr). */
static int stat_line(const Gb *g, uint8_t stat) {
    int mode = ppu_mode(g);
    return (g->lcdc & 0x80) && (((stat & 0x40) && g->ly == g->lyc) || ((stat & 0x20) && (mode == 2 || (!g->cgb && g->ly == 144 && g->dot < 4))) ||
                                ((stat & 0x10) && mode == 1) || ((stat & 0x08) && mode == 0));
}
void ppu_stat_update(Gb *g) {
    if (!(g->lcdc & 0x80)) return;  /* LCD off: the comparison clock stops, the line holds (mooneye stat_lyc_onoff) */
    uint8_t line = (uint8_t)stat_line(g, g->stat);
    if (line && !g->stat_line) g->ifl |= INT_STAT;
    g->stat_line = line;
}

/* DMG quirk: a write to STAT enables every source for a moment, so in
 * hblank, vblank or on LY = LYC it raises the interrupt (games rely on it,
 * Pan Docs "STAT"). Not on the CGB (a CGB game's STAT handler that writes
 * STAT would re-enter itself until the stack overran). */
void ppu_stat_write(Gb *g, uint8_t v) {
    if (!g->cgb && stat_line(g, 0x78) && !g->stat_line) g->ifl |= INT_STAT;
    g->stat = v & 0x78;
    ppu_stat_update(g);
}

void ppu_lcdc_write(Gb *g, uint8_t v) {
    if ((g->lcdc & 0x80) && !(v & 0x80)) {  /* LCD off: line 0, a blank screen; the LY=LYC flag stays as it is */
        g->coin_hold = (uint8_t)(g->ly_seen == g->ly && g->ly == g->lyc);
        g->ly = 0, g->dot = 0, g->mode = 0;
        for (int i = 0; i < 160 * 144; i++) g->frame[i] = g->cgb ? 0x7FFF : 0;  /* white */
        g->frame_count++;
    }
    /* turned on: line 0 has no mode 2, starts in mode 0 and 4 dots in (452 long), mode 3 two dots late (mooneye lcdon_timing) */
    if (!(g->lcdc & 0x80) && (v & 0x80)) g->ly = g->ly_seen = 0, g->dot = 4, g->mode = 0, g->wy_hit = 0, g->win_line = 0;
    /* LCDC.4 changed in mode 3: for 5 dots the tile data read finds the tile number instead (cgb-acid-hell) */
    if (g->mode == 3 && ((g->lcdc ^ v) & 0x10) && (v & 0x80)) g->m3.glitch = 5;
    g->lcdc = v;
    ppu_stat_update(g);
}

/* CGB: colour ci of palette p, RGB555 */
static uint16_t cgb_colour(const uint8_t *pal, int p, int ci) {
    return (uint16_t)(pal[p * 8 + ci * 2] | (pal[p * 8 + ci * 2 + 1] & 0x7F) << 8);
}

/* The 2-bit colour of pixel x of the tile row at `row` (VRAM offset, bank 1 from $2000). */
static int tile_pixel(const Gb *g, unsigned row, int x) {
    return (g->vram[row] >> (7 - x) & 1) | (g->vram[row + 1] >> (7 - x) & 1) << 1;
}
static unsigned tile_row(const Gb *g, uint8_t tile, int y) {  /* BG/window: LCDC bit 4 picks the addressing */
    return g->lcdc & 0x10 ? tile * 16u + y * 2u : (unsigned)(0x1000 + (int8_t)tile * 16 + y * 2);
}

/* Up to 10 objects on this line, in OAM order (Pan Docs "OAM": the scan);
 * sorted by X (stable), the order they are fetched in. */
static int scan_objects(const Gb *g, uint8_t out[10]) {
    int h = g->lcdc & 4 ? 16 : 8, n = 0;
    for (int i = 0; i < 40 && n < 10; i++) {
        int y = g->oam[i * 4] - 16;
        if (g->ly >= y && g->ly < y + h) out[n++] = (uint8_t)i;
    }
    for (int i = 1; i < n; i++)
        for (int j = i; j > 0 && g->oam[out[j] * 4 + 1] < g->oam[out[j - 1] * 4 + 1]; j--) {
            uint8_t t = out[j];
            out[j] = out[j - 1], out[j - 1] = t;
        }
    return n;
}

/* The next 8 background (or window) pixels, in three steps like the
 * hardware: the map entry (tile number, attributes), then the row's two
 * bytes; each reads the registers as they are at that dot. */
static void fetch_step(Gb *g) {
    if (g->m3.stage == 0) {
        unsigned map, tx, ty;
        if (g->m3.win) map = g->lcdc & 0x40 ? 0x1C00 : 0x1800, tx = g->m3.wcol++, ty = g->win_line;
        else map = g->lcdc & 0x08 ? 0x1C00 : 0x1800, tx = ((g->scx >> 3) + g->m3.col++) & 31u, ty = (g->scy + g->ly) & 255u;
        unsigned at = map + (ty / 8) * 32 + tx;
        g->m3.ntile = g->vram[at];
        /* CGB: bank 1 holds each map entry's attributes: palette, tile bank, flips, priority */
        g->m3.nattr = cgb_game(g) ? g->vram[0x2000 + at] : 0;
        g->m3.ny = (uint8_t)(g->m3.nattr & 0x40 ? 7 - (ty & 7) : ty & 7);
    } else {
        unsigned row = tile_row(g, g->m3.ntile, g->m3.ny) + (g->m3.nattr & 8 ? 0x2000u : 0);
        if (g->m3.stage == 1) g->m3.nlo = g->vram[row];
        else g->m3.nhi = g->m3.glitch ? g->m3.ntile : g->vram[row + 1], g->m3.glitch = 0;
    }
    g->m3.stage++;
}
static void fetch_row(Gb *g) {  /* a whole row now (mode 3's start, the window's) */
    g->m3.stage = 0;
    while (g->m3.stage < 3) fetch_step(g);
}
static void next_row(Gb *g) {
    while (g->m3.stage < 3) fetch_step(g);
    g->m3.lo = g->m3.nlo, g->m3.hi = g->m3.nhi, g->m3.attr = g->m3.nattr, g->m3.pos = 0, g->m3.stage = 0;
}

/* An object's row into the line's object pixels. Priority (Pan Docs "OAM"):
 * DMG: the lowest X wins, then the lowest OAM index (the fetch order);
 * CGB: the lowest OAM index. Only opaque pixels count. */
static void fetch_obj(Gb *g, int idx) {
    const uint8_t *o = g->oam + idx * 4;
    int h = g->lcdc & 4 ? 16 : 8, y = g->ly - (o[0] - 16), sx = o[1] - 8;
    if (o[3] & 0x40) y = h - 1 - y;  /* Y flip */
    uint8_t tile = h == 16 ? (uint8_t)((o[2] & 0xFE) | (y >= 8)) : o[2];
    unsigned row = tile * 16u + (unsigned)(y & 7) * 2u + (cgb_game(g) && (o[3] & 8) ? 0x2000u : 0);
    for (int p = 0; p < 8; p++) {
        int x = sx + p;
        if (x < 0 || x >= 160) continue;
        int ci = tile_pixel(g, row, o[3] & 0x20 ? 7 - p : p);
        if (ci && (!g->m3.ob_ci[x] || (cgb_game(g) && !g->opri && idx < g->m3.ob_ix[x])))
            g->m3.ob_ci[x] = (uint8_t)ci, g->m3.ob_fl[x] = o[3], g->m3.ob_ix[x] = (uint8_t)idx;
    }
}

static void put_pixel(Gb *g) {
    int x = g->m3.x, ci = 0, attr = g->m3.attr;
    if (cgb_game(g) || (g->lcdc & 1)) {  /* DMG and compatibility mode: bit 0 off blanks background and window */
        int bit = attr & 0x20 ? g->m3.pos : 7 - g->m3.pos;
        ci = (g->m3.lo >> bit & 1) | (g->m3.hi >> bit & 1) << 1;
    }
    g->m3.pos++;
    uint16_t *out = g->fb + g->ly * 160 + x;
    const int shade = g->io[0x47] >> (ci * 2) & 3;
    if (!g->cgb) *out = (uint16_t)shade;
    else *out = g->compat ? cgb_colour(g->bg_pal, 0, shade) : cgb_colour(g->bg_pal, attr & 7, ci);
    /* an object's priority bit decides against background colours 1-3 (CGB:
     * so does the map's; LCDC bit 0 off: the objects are always in front) */
    int oc = g->m3.ob_ci[x];
    if (!oc || !(g->lcdc & 2)) return;
    int fl = g->m3.ob_fl[x];
    if (g->cgb) {
        if ((g->lcdc & 1) && ci && ((fl & 0x80) || (attr & 0x80))) return;
        *out = g->compat ? cgb_colour(g->obj_pal, fl >> 4 & 1, g->io[fl & 0x10 ? 0x49 : 0x48] >> (oc * 2) & 3)
                         : cgb_colour(g->obj_pal, fl & 7, oc);
    } else {
        if ((fl & 0x80) && ci) return;  /* behind background colours 1-3 */
        *out = (uint8_t)(g->io[fl & 0x10 ? 0x49 : 0x48] >> (oc * 2) & 3);
    }
}

/* Mode 3 starts: 12 dots, + SCX mod 8, before the first pixel; then a pixel
 * a dot, with stalls: 6 when the window starts, 6-11 per object (Pan Docs
 * "Mode 3 length"). */
static void mode3_start(Gb *g) {
    if (g->ly == g->wy) g->wy_hit = 1;
    g->m3.nobj = (uint8_t)scan_objects(g, g->m3.objs);
    g->m3.otile = -1;
    g->m3.next = 0, g->m3.x = 0, g->m3.win = 0, g->m3.col = 0, g->m3.wcol = 0;
    memset(g->m3.ob_ci, 0, sizeof g->m3.ob_ci);
    g->m3.fine = g->scx & 7;
    g->m3.stall = 12 + g->m3.fine;
    fetch_row(g);
    next_row(g);
    g->m3.pos = g->m3.fine;
}

/* One dot of mode 3. */
static void mode3_dot(Gb *g) {
    if (g->m3.glitch) g->m3.glitch--;
    if (g->m3.stall) { g->m3.stall--; return; }
    int x = g->m3.x;
    int wx = g->wx - 7;
    if (!g->m3.win && (g->lcdc & 0x20) && (cgb_game(g) || (g->lcdc & 1)) && g->wy_hit && g->wx <= 166 && x == (wx < 0 ? 0 : wx)) {
        g->m3.win = 1, g->m3.stall = 5;
        g->m3.stage = 0;
        fetch_row(g);
        next_row(g);
        g->m3.pos = wx < 0 ? (uint8_t)-wx : 0;
        return;
    }
    if (g->m3.next < g->m3.nobj) {
        int ox = g->oam[g->m3.objs[g->m3.next] * 4 + 1];
        if (ox - 8 <= x) {
            int idx = g->m3.objs[g->m3.next++];
            if (g->lcdc & 2) {
                /* the first object in a background tile waits for the fetcher: up to 5 dots more */
                int tile = (ox + g->scx) >> 3, skew = (ox + g->scx) & 7;
                fetch_obj(g, idx);
                g->m3.stall = (uint8_t)(5 + (tile != g->m3.otile && skew < 5 ? 5 - skew : 0));
                g->m3.otile = tile;
                return;
            }
        }
    }
    if (g->m3.pos == 8) next_row(g);
    put_pixel(g);
    /* the next row is read as pixels 1, 3 and 5 of this one go out (fixed offsets, tuned on cgb-acid-hell) */
    if (g->m3.stage == 0 && g->m3.pos >= 1) fetch_step(g);
    else if (g->m3.stage == 1 && g->m3.pos >= 3) fetch_step(g);
    else if (g->m3.stage == 2 && g->m3.pos >= 5) fetch_step(g);
    if (++g->m3.x == 160) {
        g->mode = 0, g->hdma_due = g->hdma_on;
        if (g->m3.win) g->win_line++;
    }
}

void ppu_tick(Gb *g, int step) {
    if (!(g->lcdc & 0x80)) {
        g->mode_seen = 0;
        return;
    }
    int next = g->dot + step;
    if (g->mode != 3 && next < 456 && (g->mode != 2 || next < 80) && !(g->mode == 0 && g->ly == 0 && g->dot < 82 && next >= 82)) {
        g->mode_seen = g->mode, g->ly_seen = g->ly, g->dot = next;  /* nothing happens inside this cycle */
        ppu_stat_update(g);
        return;
    }
    for (int n = step; n--;) {
        if (!n) g->mode_seen = g->mode, g->ly_seen = g->ly;  /* a read finds the mode and LY a dot before the cycle's end */
        g->dot++;
        if (g->mode == 3) mode3_dot(g);
        if (g->dot == 456) {
            g->dot = 0;
            if (++g->ly == 154) g->ly = 0, g->wy_hit = 0, g->win_line = 0;
            if (g->ly == 144) {
                g->mode = 1;
                g->ifl |= INT_VBLANK;
                memcpy(g->frame, g->fb, sizeof g->frame);
                g->frame_count++;
            } else if (g->ly < 144) {
                g->mode = 2;
            }
        } else if ((g->mode == 2 && g->dot == 80) || (g->mode == 0 && g->ly == 0 && g->dot == 82)) {
            g->mode = 3, mode3_start(g);
        }
    }
    ppu_stat_update(g);
}
