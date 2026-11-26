# Game Boy architecture

The Game Boy and Game Boy Color parts. What every system shares
(templates, blocks, chaining, states, frontend):
[docs/architecture.md](../../../docs/architecture.md).

## Components
| Part | Notes |
|------|-------|
| `cpu/sm83/` | the SM83, shared with other systems: the templates (`sm83.c`, C per opcode from the opcode's bit fields), the interpreter (`sm83_cpu.c`), its switch generator, the SingleStepTests runner (`sm83_tests.c`); see [cpu/README.md](../../../cpu/README.md) |
| `systems/gb/recomp/` | `gbrecomp`: `recomp.c` (regions, blocks, emitter), `main.c` |
| `systems/gb/runtime/` | `gb.c` (bus, timer, serial, joypad, OAM DMA, HDMA, dispatch, states), `ppu.c`, `apu.c`, `cart.c` (MBC1/2/3/5, the MBC3 clock), `recomp_rt.h` |
| `systems/gb/frontend.c` | the Game Boy behind `core/frontend/system.h`: battery saves with the clock, the DMG palette setting |
| `systems/gb/tests/` | `gb_headless.c` (test ROMs, traces, `--diff`) |

## Timing
Everything counts in M-cycles (4 clocks). Each bus access of the CPU, and
each internal cycle, first steps the rest of the machine by one M-cycle
(`gb.c` `tick`): timer, serial, OAM DMA, PPU (4 dots), sound, the
cartridge's clock. So every register access happens at its exact cycle,
with no catch-up scheme (and no speed gain from recompiling either: the
per-cycle stepping is most of the time).

## PPU
`ppu_tick` steps the PPU one dot at a time (4 a cycle, 2 in double speed).
Mode 3 is drawn as it goes (`mode3_dot`): 12 dots + SCX mod 8 before the
first pixel, then a pixel a dot, with stalls of 6 when the window starts
and 6-11 for an object (the extra dots only for the first object in a
background tile). The background is read a row at a time in three steps
(map entry, low byte, high byte) at fixed pixels, so a write to LCDC,
SCX, SCY or the palettes takes effect at its own pixel; objects are read
whole when their X is reached. An LCDC.4 change a few dots before the high
byte is read makes it read the tile number instead (what cgb-acid-hell
shows). The mode the CPU reads (STAT, VRAM, OAM, CGB palette RAM) is the
one a dot before the cycle ends, and the STAT interrupt line uses the real
one. After the LCD is turned on line 0 has no mode 2 and is 452 dots long.

## Models
A game whose header asks for the Color ($0143 bit 7) runs in CGB mode, any
other as on the original Game Boy; `model` (`gb.ini`, `gb_headless
--model`) forces one. A Game Boy game on a Color runs in compatibility mode
(`Gb.compat`, set with `cgb`): DMG rules in the PPU (the map attributes, VRAM
bank 1 and OAM-order priority are off), but the colour comes from palette
RAM: BGP, OBP0 and OBP1 pick the shade, palettes 0 and 1 hold the colours the
boot ROM chose (`cgb_compat.c`). Boot state comes from one table in
`gb_load_model` (registers, DIV, with a second DIV for compatibility mode);
`dmg0`, `mgb`, `sgb`, `sgb2`, `cgb0` and `agb` differ from the base models
in that state only. CGB mode adds VRAM bank 1, WRAM banks 1-7, palette RAM, the map attributes and
OAM-order object priority in the PPU, HDMA, the CGB's own WRAM bus during
OAM DMA, the sound chip's CGB details, and double speed: the CPU, timer,
serial and OAM DMA run twice as fast, the PPU (2 dots per cycle), sound
and the cartridge clock keep their pace. The speed switch (STOP with KEY1
armed) resets DIV and holds instruction execution for 32,768 M-cycles at
the new speed. Both execution paths use the same timer, APU and PPU logic. HDMA blocks move inside the CPU's
bus cycle, so recompiled code waits for them where the interpreter does.

## Recompiled code
- **Regions**: one 16 KB ROM bank as seen in one window ($0000-$3FFF or
  $4000-$7FFF). Static flow is followed inside the window only; the bank
  in the other window is not known at build time, so flow into it is
  resolved at run time.
- **Entries**: the reset, RST and interrupt vectors in bank 0, and every
  (bank, address) the trace ran (`gb_headless --misses`, by `AUTO_HINTS`),
  the program's own `NAME.misses` (written by the frontend when you play)
  and the hint file `systems/gb/games/NAME.toml` (entries, and data ranges that are
  never decoded).
- **Blocks end** at jumps, calls, returns, HALT, STOP and EI (IME turns on
  in the dispatcher, before the next instruction).
- **Dispatch** (`gb_step`): interrupt entry and halted cycles as in the
  interpreter; then the block for (pc, bank mapped at pc), else one
  instruction interpreted. After either: the HALT bug and the CGB speed
  switch.

## Verification
SingleStepTests sm83, blargg and mooneye test ROMs, dmg-acid2 and
cgb-acid2, lockstep diffs of sampled games:
[verification-log.md](verification-log.md).
