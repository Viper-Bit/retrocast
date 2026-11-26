#include "cart.h"

#include <string.h>

/* Detection follows Stella's CartDetector (docs/sources.md): the size, then
   byte signatures of the bankswitching instructions. */
static int find(const uint8_t *rom, size_t size, const uint8_t *sig, size_t len, int hits) {
    for (size_t i = 0; i + len <= size; i++)
        if (!memcmp(rom + i, sig, len) && --hits == 0) return 1;
    return 0;
}

static int any3(const uint8_t *rom, size_t size, const uint8_t (*sigs)[3], size_t n) {
    for (size_t i = 0; i < n; i++)
        if (find(rom, size, sigs[i], 3, 1)) return 1;
    return 0;
}

static int superchip(const uint8_t *rom, size_t size) {  /* each 4K bank's RAM area repeats its first 128 bytes */
    for (size_t b = 0; b < size; b += 4096)
        if (memcmp(rom + b, rom + b + 128, 128)) return 0;
    return 1;
}

static const uint8_t E0_SIGS[][3] = {{0x8D, 0xE0, 0x1F}, {0x8D, 0xE0, 0x5F}, {0x8D, 0xE9, 0xFF}, {0x0C, 0xE0, 0x1F},
                                     {0xAD, 0xE0, 0x1F}, {0xAD, 0xE9, 0xFF}, {0xAD, 0xED, 0xFF}, {0xAD, 0xF3, 0xBF}};
static const uint8_t E7_SIGS[][3] = {{0xAD, 0xE2, 0xFF}, {0xAD, 0xE5, 0xFF}, {0xAD, 0xE5, 0x1F}, {0xAD, 0xE7, 0x1F},
                                     {0x0C, 0xE7, 0x1F}, {0x8D, 0xE7, 0xFF}, {0x8D, 0xE7, 0x1F}};
static const uint8_t E78K_SIGS[][3] = {{0xAD, 0xE4, 0xFF}, {0xAD, 0xE5, 0xFF}, {0xAD, 0xE6, 0xFF}};
static const uint8_t STA_3F[] = {0x85, 0x3F};

static A26CartType detect(const uint8_t *rom, size_t size) {
    switch (size) {
    case 2048: return A26_CART_2K;
    case 4096: return A26_CART_4K;
    case 8192:
        if (superchip(rom, size)) return A26_CART_F8SC;
        if (any3(rom, size, E0_SIGS, 8)) return A26_CART_E0;
        if (find(rom, size, STA_3F, 2, 2)) return A26_CART_3F;
        if (any3(rom, size, E78K_SIGS, 3)) return A26_CART_E7;
        return A26_CART_F8;
    case 12288: return any3(rom, size, E7_SIGS, 7) ? A26_CART_E7 : A26_CART_FA;
    case 16384:
        if (superchip(rom, size)) return A26_CART_F6SC;
        return any3(rom, size, E7_SIGS, 7) ? A26_CART_E7 : A26_CART_F6;
    case 32768:
        if (superchip(rom, size)) return A26_CART_F4SC;
        return find(rom, size, STA_3F, 2, 2) ? A26_CART_3F : A26_CART_F4;
    default: return A26_CART_AUTO;
    }
}

int a26_cart_init(A26Cart *cart, const uint8_t *rom, size_t size, A26CartType type) {
    if (!cart || !rom) return -1;
    if (type == A26_CART_AUTO) type = detect(rom, size);
    unsigned banks = 1;
    int ok;
    switch (type) {
    case A26_CART_2K: ok = size == 2048; break;
    case A26_CART_4K: ok = size == 4096; break;
    case A26_CART_F8: case A26_CART_F8SC: banks = 2; ok = size == 8192; break;
    case A26_CART_F6: case A26_CART_F6SC: banks = 4; ok = size == 16384; break;
    case A26_CART_F4: case A26_CART_F4SC: banks = 8; ok = size == 32768; break;
    case A26_CART_FA: banks = 3; ok = size == 12288; break;
    case A26_CART_E0: ok = size == 8192; break;
    case A26_CART_E7: ok = size == 8192 || size == 12288 || size == 16384; break;
    case A26_CART_3F: ok = size >= 4096 && size % 2048 == 0 && size / 2048 <= 256; break;
    default: ok = 0;
    }
    if (!ok) return -1;
    memset(cart, 0, sizeof *cart);
    cart->rom = rom;
    cart->size = size;
    cart->type = type;
    cart->banks = banks;
    a26_cart_reset(cart);
    return 0;
}

void a26_cart_reset(A26Cart *cart) {
    cart->bank = cart->banks - 1;
    if (cart->type == A26_CART_E0) {  /* Stella's start: 4, 5, 6 (the last 1K is fixed) */
        cart->slice[0] = 4; cart->slice[1] = 5; cart->slice[2] = 6;
    } else {
        cart->slice[0] = cart->slice[1] = 0;
    }
}

int a26_cart_recompilable(A26CartType type) {
    return type >= A26_CART_2K && type <= A26_CART_F4;
}

static unsigned e7_banks(const A26Cart *cart) { return (unsigned)(cart->size / 2048); }

/* Hotspot selection occurs on both reads and writes, including dummy cycles. */
static void select_bank(A26Cart *cart, unsigned offset) {
    unsigned first;
    switch (cart->type) {
    case A26_CART_E0:
        if (offset >= 0xFE0 && offset <= 0xFF7) cart->slice[(offset - 0xFE0) >> 3] = (uint8_t)(offset & 7);
        return;
    case A26_CART_E7: {
        unsigned n = e7_banks(cart);
        if (offset >= 0xFE8 && offset <= 0xFEB) cart->slice[1] = (uint8_t)(offset & 3);
        else if (n == 4 && offset >= 0xFE4 && offset <= 0xFE7) cart->slice[0] = (uint8_t)(offset & 3);
        else if (n == 6 && offset >= 0xFE0 && offset <= 0xFE7) {
            static const uint8_t six[8] = {0, 1, 0, 1, 2, 3, 4, 5};
            cart->slice[0] = six[offset & 7];
        } else if (n == 8 && offset >= 0xFE0 && offset <= 0xFE7) cart->slice[0] = (uint8_t)(offset & 7);
        return;
    }
    case A26_CART_3F: case A26_CART_2K: case A26_CART_4K: return;
    case A26_CART_F6: case A26_CART_F6SC: first = 0xFF6; break;
    case A26_CART_F4: case A26_CART_F4SC: first = 0xFF4; break;
    default: first = 0xFF8;  /* F8, F8SC, FA */
    }
    if (offset >= first && offset < first + cart->banks) cart->bank = offset - first;
}

static unsigned ram_size(A26CartType type) {
    return type == A26_CART_FA ? 256 : (type >= A26_CART_F8SC && type <= A26_CART_F4SC) ? 128 : 0;
}

/* shortcut: a read of a RAM write port returns the RAM byte; the real cart
   writes the bus's floating value there. Upgrade if a game relies on it. */
uint8_t a26_cart_read(A26Cart *cart, uint16_t address) {
    unsigned offset = address & 0x0FFF;
    select_bank(cart, offset);
    unsigned ram = ram_size(cart->type);
    switch (cart->type) {
    case A26_CART_2K: return cart->rom[offset & 0x7FF];
    case A26_CART_E0: {
        unsigned seg = offset >> 10, slice = seg == 3 ? 7 : cart->slice[seg];
        return cart->rom[slice * 1024 + (offset & 0x3FF)];
    }
    case A26_CART_E7: {
        unsigned last = e7_banks(cart) - 1;
        if (offset < 0x800) {
            if (cart->slice[0] == last) return cart->ram[offset & 0x3FF];  /* 1K of RAM: write $1000, read $1400 */
            return cart->rom[cart->slice[0] * 2048 + offset];
        }
        if (offset < 0xA00) return cart->ram[0x400 + cart->slice[1] * 256 + (offset & 0xFF)];
        return cart->rom[last * 2048 + (offset & 0x7FF)];
    }
    case A26_CART_3F: {
        unsigned n = (unsigned)(cart->size / 2048);
        return offset < 0x800 ? cart->rom[(cart->slice[0] % n) * 2048 + offset] : cart->rom[(n - 1) * 2048 + offset - 0x800];
    }
    default:
        if (offset < 2 * ram) return cart->ram[offset % ram];
        return cart->rom[cart->bank * 4096 + offset];
    }
}

void a26_cart_write(A26Cart *cart, uint16_t address, uint8_t value) {
    unsigned offset = address & 0x0FFF;
    select_bank(cart, offset);
    unsigned ram = ram_size(cart->type);
    if (cart->type == A26_CART_E7) {
        if (offset < 0x400 && cart->slice[0] == e7_banks(cart) - 1) cart->ram[offset] = value;
        else if (offset >= 0x800 && offset < 0x900) cart->ram[0x400 + cart->slice[1] * 256 + (offset & 0xFF)] = value;
    } else if (offset < ram) {
        cart->ram[offset] = value;
    }
}

void a26_cart_tia_write(A26Cart *cart, uint16_t address, uint8_t value) {
    if (cart->type == A26_CART_3F && (address & 0x1FFF) < 0x40) cart->slice[0] = value;
}
