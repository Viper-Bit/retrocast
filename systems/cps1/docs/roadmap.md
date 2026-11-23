# CPS-1 roadmap

The order rule ([docs/roadmap.md](../../../docs/roadmap.md)): the reference
before the thing it checks. A milestone is done when its exit test passes.

| Milestone | Content | State |
|---|---|---|
| P1 | `core/zip`: directory, inflate, CRC | done |
| P2 | the 68000 machine, CPS-A/CPS-B picture, the game table with Final Fight | done |
| P3 | sound: Z80, YM2151, OKI MSM6295 | done |
| P4 | the window (`retrocast`, `cps1.ini`), CMake detection, save states | done |
| P5 | every plain-board game (their mappers); stars, flip screen, vertical monitors | done |
| P6 | the recompiler (`cps1recomp`, `-DROMS`, `--diff`) | open |
| P7 | the Q-Sound games: dino, punisher, wof, slammasu, mbombrd | open |
| P8 | the rest: pang3, megaman, pnickj, qad, qtono2 | open |

## P1 · Zips
- [x] `core/zip.c`: the end record and central directory, stored and
  deflate entries, the CRC-32 check; no ZIP64.
- [x] **Exit:** `tests/test_zip.py`: zips Python writes (stored, levels 1
  and 9, empty to 1 MB, a back-reference 32 KB away) read back the same;
  cut and corrupted zips fail cleanly; every zip in the set reads as
  Python reads it.

## P2 · The machine and the picture
- [x] The 68000 map, inputs and DIP switches, the CPS-B ID port and
  multiplier, VBlank on level 2; the palette, three scroll layers,
  sprites and priority; the game table (Final Fight).
- [x] **Exit:** `cps1_tests`; Final Fight reaches its title in
  `cps1_headless --ppm`, checked by eye.

## P5 · The plain-board games
- [x] 20 more games from MAME 0.289's sets (layouts, CPS-B, mappers, DIP
  defaults, clocks), an 8-bit graphics load layout; clone zips with their
  parent's; 12 MHz boards; the extra input port (Street Fighter II's
  kicks, a third player); Forgotten Worlds' dial; the two star layers,
  flip screen, vertical monitors.
- [x] **Exit:** the boot test (`TestBoot`: 21 games, 1,800 frames of
  `--play`, a picture and no halt); a contact sheet of every game next to
  MAME's picture at the same frame, checked by eye.
- Open: captcomu (its parent `captcomm.zip` is not in the set); a third
  and fourth player in `retrocast`.

## P4 · The window, detection, save states
- [x] The graphics ROM mapper per board (Final Fight's S224B): a tile code
  outside its layer's range is not drawn, as on the board.
- [x] `cps1_system` in `retrocast` (384x224 on a 4:3 monitor, both
  players, a coin on Select, mono sound, F2 / F4); save states with the
  game's id; `cmake/detect_system.cmake` matches a zip to `games.c`'s CRCs.
- [x] **Exit:** `test_detect` (the C detector and the CMake rule agree on
  Final Fight and refuse a CPS-2 zip; a `games.c` the rule cannot read
  stops it); `test_ffight_state`; Final Fight played by hand in
  `retrocast` to Game Over.

## P3 · Sound
- [x] The Z80 (ROM, bank, RAM, the command and fade latches), the YM2151
  on `core/audio/fm.c` (moved from the Genesis, sample-identical there), the
  OKI MSM6295, the mix (mono, 55,930 Hz), `cps1_headless --wav`.
- [x] **Exit:** `cps1_tests` (pitch, timers, release, ADPCM, the latch, the
  bank, the YM2151's IRQ, the sample buffer); Final Fight's play is not
  silent (`test_ffight_sound`).
