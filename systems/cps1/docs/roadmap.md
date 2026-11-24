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
| P6 | the recompiler (`cps1recomp`, `-DROMS`, `--diff`) | done |
| P7 | the Q-Sound games: dino, punisher, wof, slammasu, mbombrd | done |
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

## P7 · The Q-Sound games
- [x] The game table rebuilt from MAME 0.289's `cps1.cpp` (DIP defaults
  MAME writes through macros, whole 128 KB sound chips, MAME's 12 MHz
  machines); Kabuki decryption (`runtime/kabuki.c`); the 93C46 serial
  EEPROM (`core/eeprom93c46.c`); the Q-Sound board (shared RAM, the 8 MHz
  Z80 and its 250 Hz interrupt, the bank, players 3-4, Slam Masters'
  protection read, `GAME.eeprom`); the Q-Sound chip, MAME's high-level
  version (`core/audio/qsound.c`), stereo at 24,038 Hz, its tables from
  `qsound.zip`.
- [x] **Exit:** the 18 Q-Sound sets in the table; every Q-Sound zip of the
  folder whole by CRC boots to a picture (`TestBoot`); Warriors of Fate's
  sound sample for sample against MAME's code (`test_wof_sound`); wof and
  dino recompiled with `--diff`, no difference in 3,000 frames.
- Open: a third and fourth player in `retrocast`; the Q-Sound DSP
  emulated instruction by instruction (MAME's low-level `qsound.cpp`, which
  its CPS-1 driver uses); pictures compared with MAME's (no MAME here).

## P6 · The recompiler
- [x] The 68000 recompiler's analysis and emitting shared with the Genesis
  (`cpu/m68k/m68k_recomp.c`; `mdrecomp` emits the same C as before);
  `cps1recomp`; the runtime's hook (`recomp_on` only for the code it was
  made from), `--misses`, `--diff`, `--coverage`; `-DROMS` with a zip;
  the window records `NAME.misses`.
- [x] **Exit:** `TestRecomp`: ffight and sf2, 3,000 frames of `--play`
  with `--diff`, no difference, 96% of 68000 clocks recompiled.
- Open: the Z80 recompiled (small); played by hand in the window.

## P5 · The plain-board games
- [x] 66 more sets from MAME 0.289's (layouts, CPS-B, mappers, DIP
  defaults, clocks; revision E's CPS-B address), an 8-bit graphics load layout; clone zips with their
  parent's; 12 MHz boards; the extra input port (Street Fighter II's
  kicks, a third player); Forgotten Worlds' dial; the two star layers,
  flip screen, vertical monitors.
- [x] **Exit:** the boot test (`TestBoot`: every game in the table, 3,000 frames of
  `--play`, a picture and no halt); a contact sheet of every game next to
  MAME's picture at the same frame, checked by eye.
- Open: bootlegs needing their own protection or input wiring; sets loading
  part of a chip; `sf2accp2` and `sf2rb3`; a fourth player (Captain
  Commando); a third and fourth player in `retrocast`.

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
