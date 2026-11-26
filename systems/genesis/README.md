# Sega Genesis / Mega Drive

The Genesis part of [retrocast](../../README.md). Playable in the
interpreter, with sound (`build/retrocast game.md`), or recompiled (`-DROMS=game.md`,
as in the [README](../../README.md#recompiling-a-game)).

## Status
- **Z80** (`cpu/z80`, the sound CPU): done (roadmap C1). Templates for
  every opcode (documented and undocumented), interpreter, interrupts;
  all 1,604 SingleStepTests z80 files pass: 1,604,000 tests, state, ports
  and every T-state of the bus.
- **68000** (`cpu/m68k`, the main CPU): the interpreter passes
  SingleStepTests m68000 on all 127 of its instruction families, every bus
  transaction with its clocks included (317,500 tests).
- **The machine** (roadmap D1): memory maps, I/O and pads, Z80 control,
  cartridge with battery RAM or a serial EEPROM (NBA Jam, NHLPA 93, Wily
  Wars, College Slam...; not Codemasters' J-Cart ones), TMSS, both CPUs on one clock; 1,556 of the
  1,566 games of the licensed set reach their first VDP writes.
- **The VDP** (roadmap D2): planes, window, sprites, priorities,
  shadow/highlight, DMA, interrupts, drawn a line at a time; samples of
  the licensed set reach title and play screens (`genesis_headless
  --ppm`, `tools/genesis_sheet.py`).
- **The window program** (roadmap D3): `retrocast` (settings in
  `genesis.ini`), the picture (H32 shown
  as wide as H40, as on a TV), both pads, battery saves (`ROM.sav`),
  save states (F2/F4), the reset button (F5), recordings.
- **Sound** (roadmap D4): the PSG and the YM2612 (6 FM channels, the DAC,
  LFO, timers, channel 3's special mode), stereo, at the YM2612's own
  rate (53,267 Hz). Not modelled: SSG-EG, CSM, the busy flag, the DAC's
  ladder effect and the console's output filter.
- **The recompiler** (roadmap D5): `mdrecomp` turns the 68000 code of the
  cartridge into C, one function per block, each instruction the
  interpreter's own handler with its opcode a constant; the Z80 stays
  interpreted. The build traces each game first (AUTO_HINTS: Start pressed
  now and then) and recompiles what that reached and what your own play
  interpreted (`NAME.misses`). A sample of 8 games runs in lockstep with the
  interpreter for 3,000 frames each, 94-99.97% of the 68000's clocks in
  recompiled code (verification-log.md). The speed gain is small for now:
  the sound chips and the Z80 take most of the time.

## Controls and settings
The buttons as the frontend names them ([README](../../README.md#controls-and-settings)):
the pad's A, B, C are Y, B, A (keyboard A, Z, X; gamepad West, South,
East); X, Y, Z are L, X, R (Q, S, W; left shoulder, North, right
shoulder); Mode is Select. In `genesis.ini`:
```
pad = 6             # 6 = six-button pad, 3 = three-button (a few early games misread a six-button one)
```
The region comes from the game's header (the Americas when allowed, else
Japan, else Europe at 50 Hz).

## Docs
| File | Content |
|------|---------|
| [roadmap.md](docs/roadmap.md) | The hardware facts the work builds on, milestones C1-C2 and D1-D5 |
| [verification-log.md](docs/verification-log.md) | What was checked, how, and the result |
