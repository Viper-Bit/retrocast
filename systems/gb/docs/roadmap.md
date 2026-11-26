# Game Boy and Game Boy Color roadmap

Same order as the NES: the reference interpreter first, checked against
independent tests, then the system, then the recompiler. Shared code goes
to `core/` when the Game Boy is its second user ([architecture](../../../docs/architecture.md) "Frontend").

Exit tests and results: [verification-log.md](verification-log.md).

| Milestone | Content | State |
|---|---|---|
| [G1](#g1--sm83-cpu) | SM83 CPU from templates, interpreter | done |
| [G2](#g2--memory-timer-cartridges) | memory map, timer, interrupts, MBC1/2/3/5 | done |
| [G3](#g3--ppu-and-frontend) | PPU, the window program (core/frontend) | done |
| [G4](#g4--apu) | sound | done |
| [G5](#g5--recompiler) | recompiler, lockstep diff | done (code in RAM interpreted) |
| [G6](#g6--game-boy-color) | Game Boy Color | done |

## G1 · SM83 CPU
- [x] Instruction templates from the opcode bit fields (`cpu/sm83/sm83.c`),
  with the NES's PC markers, now in `core/recomp/template.c` (the NES
  recompiler uses them from there too).
- [x] The interpreter's switch (both tables, CB nested), written by
  `sm83_gen` (first `gbrecomp --cpu-switch`); `cpu/sm83/sm83_cpu.c`, one
  M-cycle per bus access or internal cycle.
- [x] **Exit:** SingleStepTests sm83, all 500 opcode files (registers, RAM,
  every M-cycle; HALT and STOP registers and RAM only). Met.

## G2 · Memory, timer, cartridges
- [x] Memory map (`systems/gb/runtime/gb.c`), everything stepped once per M-cycle
  before the CPU's access; IE/IF, interrupt entry with the vector chosen
  after the high push (IE can cancel it), HALT (a halted CPU keeps reading
  the opcode at PC) and the HALT bug; DIV/TIMA with the overflow delay, TMA
  reload and the TAC/DIV write edges; serial (internal clock, no partner);
  joypad; OAM DMA with the bus conflicts (the DMA's bus reads the byte in
  flight, OAM $FF); LY/STAT timing only, until G3.
- [x] MBC1, MBC2, MBC3 with the clock (counted in emulated time), MBC5
  (`systems/gb/runtime/cart.c`). Battery saves come with the window program (G3).
- [x] MBC7 banking, serial EEPROM and digital tilt controls.
- [x] **Exit:** blargg `cpu_instrs` (all 11 and combined), `instr_timing`,
  `mem_timing`, `mem_timing-2`, `halt_bug`; mooneye acceptance (timer,
  interrupts, OAM DMA, instruction timing, DMG boot state) and MBC1/2/5:
  102 ROMs pass (`tests/gb/test_roms.py`); since then `timer/rapid_toggle`
  (a TAC write that enables a bit falling in that cycle counts), the
  serial clock's phase (the first bit goes at DIV's next bit-8 fall) and
  the MBC1 multicart wiring (`systems/gb/runtime/cart.c`) pass. The boot tests
  of other models pass since G6; the 8 PPU timing tests belong to G3 (done there).

## G3 · PPU and frontend
- [x] `systems/gb/runtime/ppu.c`: background, window (its own line counter),
  objects (10 per line, DMG priority, flips, 8x16), palettes; mode 3 as
  long as SCX, the window and objects make it; VRAM/OAM closed to the CPU
  while the PPU uses them; the DMG STAT-write interrupt. Mode 3 is drawn a
  dot at a time (register writes in the middle of a line show at their
  pixel); LCD-on timing, the mode the CPU reads a dot late.
- [x] `gb` (`systems/gb/frontend.c` behind `core/frontend/system.h`): 160 x 144 at
  59.73 Hz, battery saves (`ROM.sav`; MBC3's clock moves on while the
  program is closed), save states (F2/F4), palette setting (green, gray).
- [x] **Exit:** dmg-acid2 pixel for pixel (`tests/gb/test_ppu.py`, with a
  save-state round trip); every 40th licensed title of a ~1,900-ROM set
  (41 games) reaches a title, menu or play screen; the 8 mooneye PPU
  timing tests (mode 3 lengths with objects, LCD-on timing, STAT details).

## G4 · APU
- [x] `systems/gb/runtime/apu.c`: two pulses (sweep on the first), wave, noise;
  the frame sequencer on DIV bit 12; the DMG details dmg_sound checks
  (length clocking on enable and trigger, sweep negate, lengths kept and
  writable while powered off, wave RAM reachable only in the cycle a
  sample is read, the retrigger corruption). Mixed to 48 kHz mono
  through the console's output capacitor.
- [x] **Exit:** blargg `dmg_sound`, the 12 singles (in `tests/gb/test_roms.py`)
  and the combined ROM.

## G5 · Recompiler
- [x] `gbrecomp` (`systems/gb/recomp/recomp.c`): regions of one ROM bank in one
  window, static flow followed inside the window; entries from the vectors
  and the interpreter's trace (`gb_headless --misses`, `AUTO_HINTS`); one C
  function per block from the templates, chaining inside the region; a bank
  check after stores that may switch it. `gb_step` runs a block when there
  is one for (PC, mapped bank), else interprets. `.gb` files in `ROMS` build
  `NAME` and `NAME_headless` with the ROM embedded.
- [x] **Exit:** `gb_headless --diff` (CPU after every step, the whole
  machine after every frame): 21 sampled games and blargg cpu_instrs in
  lockstep; 94.8-99.8% of CPU cycles recompiled in 19 of the 21.
- [x] Hint files (`systems/gb/games/NAME.toml`) and the misses of your own play
  (`NAME.misses`, written by the window program), as the NES has.
- [ ] Open: code run from WRAM (two of the 21 games: 29% and 74%), and speed: recompiled runs as
  fast as the interpreter, every access ticking the PPU and APU (a
  catch-up scheme, as the NES's, would be the next step).

## G6 · Game Boy Color
- [x] CGB mode for games whose header asks for it (`gb_headless --model`
  to force one): double speed (the PPU and sound keep their pace), VRAM
  bank 1, WRAM banks 1-7, palette RAM, map attributes (palette, bank,
  flips, priority), OAM-order object priority, general and HBlank HDMA
  (in the bus cycle, so recompiled code waits where the interpreter
  does), the CGB's separate WRAM bus during OAM DMA, no STAT-write
  interrupt and the APU's CGB details. The speed switch resets DIV and
  takes 32,768 M-cycles at the new speed. AGE's six standard switch tests pass.
- [x] **Exit:** cgb-acid2 pixel for pixel, blargg cgb_sound (12 singles
  and the combined ROM); 36 sampled Color games reach title, menu or
  play screens; 18 recompiled in lockstep.
- [x] Compatibility mode (`model = cgb`): a DMG game with the Color's
  palettes, picked from the header as the boot ROM does (palette table from
  SameBoy's boot ROM source), and the boot state of that mode (registers,
  DIV, I/O). `model = auto|dmg|cgb|cgb-e` in `gb.ini`.
- [x] Boot states of the other models (`gb_headless --model dmg0|mgb|sgb|
  sgb2|cgb0|agb`): the nine mooneye boot tests that were open and six of
  mooneye's `misc` boot tests now pass.
- [x] Palette RAM is closed during mode 3 (reads $FF, writes lost); the
  picture is drawn a dot at a time: cgb-acid-hell pixel for pixel.
- [ ] Open: a Color game's boot DIV is unchecked. The speed-switch interrupt
  edge cases, the boot ROM's button palettes, and the DMG logo tilemap remain open.

