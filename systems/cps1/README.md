# Capcom Play System I (CPS-1)

The CPS-1 part of [retrocast](../../README.md), its first arcade board.
A game is the zip of its chip dumps, as MAME and FBNeo sets have them
(`ffight.zip`): `retrocast ffight.zip` plays it, `cps1_headless` runs one
without a window.

## Status
- **Games** (67 sets, the plain boards): every set of MAME 0.289's
  `cps1.cpp` that a zip in the set here holds whole, by CRC: 1941, Three
  Wonders, Area 88, Carrier Air Wing, Chiki Chiki Boys, Capcom World 2,
  Daimakaimura, Dynasty Wars, Final Fight, Forgotten Worlds and Lost Worlds,
  Ghouls'n Ghosts, Knights of the Round, The King of Dragons, Mercs, Magic
  Sword, Mega Twins, Nemo, Street Fighter II, Champion Edition and Hyper
  Fighting, Strider, U.N. Squadron, Varth, Willow, with their regional
  versions and revisions (`ffightj`, `sf2ue`, ...). Each with its set's chip
  layout, CPS-B (and where it sits: revision E of Street Fighter II has it
  at $8001C0), graphics ROM mapper, DIP defaults and clock. Not yet: the
  Q-Sound games and the odd boards ([roadmap](docs/roadmap.md)); bootlegs
  needing their own protection or input wiring (MAME's `init_sf2hack`,
  `init_sf2rb`); sets loading part of a chip (`captcomb`, `daimakr2`,
  `wofhfh`); `sf2accp2` and `sf2rb3` (a black screen, not found yet).
- **Clone zips**: a zip holding only a clone's own chips takes the rest
  from its parent's zip beside it (`sf2hf.zip` from `sf2ce.zip`).
  `captcomu.zip` (Captain Commando, USA) needs `captcomm.zip`, which the
  set here lacks.
- **Zips**: read by `core/zip.c` (our own inflate); a game is matched by the
  CRCs and sizes of its files, so names, PAL dumps and the clones of a
  merged set do not matter.
- **CPUs**: the shared 68000 and Z80 (`cpu/m68k`, `cpu/z80`), their own
  copies (`cps1_` prefix) so they and the Genesis and Master System fit in
  one program; the Z80 runs line by line after the 68000.
- **Sound**: the YM2151 (8 FM channels on the operator shared with the
  Genesis, `core/audio/fm.c`; DT1/DT2, the LFO, noise, timers and their IRQ)
  and the OKI MSM6295 (4 ADPCM voices, pin 7's two rates), mixed to mono
  at 55,930 Hz with MAME's CPS-1 weights. Checked on Final Fight: the
  YM2151 against ymfm (the same level and spectrum), the OKI bit-exact
  against MAME's, the mix against MAME's recording (verification log).
- **Picture**: the palette (six pages, uploaded on a palette-base write),
  scroll1-3 with flips and scroll2's row scroll, sprites of up to 16x16
  blocks, layer order and the priority masks, the board's graphics ROM
  mapper (which tile codes each layer may use), the two star layers,
  flip screen, vertical monitors (1941, Mercs, Varth turned as MAME does).
  The frame is drawn at once from VBlank's state, as MAME draws it (the
  CPS-1 has no raster interrupt).
- **Detection**: a zip holding every file of a game in the table, by CRC
  and size, in `retrocast` and in the build (`cmake/detect_system.cmake`
  reads the table from `games.c`).
- **Save states**: F2 / F4 (`GAME.state` next to the zip), refused for
  another game or version.
- **Not yet**: the recompiler; DIP switch settings (their defaults).

## Controls and settings
Both players: buttons 1, 2, 3 on the pad's B, A and X (keyboard Z, X, S;
gamepad South, East, North), a coin on Select (Right Shift, gamepad Back),
Start. Street Fighter II's kicks (buttons 4-6) are on Y, L and R (keyboard
A, Q, W). Forgotten Worlds' rotary dial turns with L and R, 20 steps a
frame as MAME's keys turn it. A third player (Knights of the Round, The
King of Dragons, Mercs) is read in `cps1_headless` only: `retrocast` has
two pads. `cps1.ini` next to `retrocast` has no CPS-1 settings yet (the
DIP switches keep each game's defaults).

## Running
`retrocast GAME.zip` plays it. `cps1_headless GAME.zip [--frames N]
[--play] [--ppm FILE] [--wav FILE] [--state-at N FILE] [--load-state FILE]`:
`--play` drops a coin, presses Start on the title (frame 1,300), then walks
right; `--ppm` saves the last frame, `--wav` the sound; a loaded state goes
on from its frame.

## Docs
- [Roadmap](docs/roadmap.md)
- [Verification log](docs/verification-log.md)
