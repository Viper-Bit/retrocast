# Capcom Play System I (CPS-1)

The CPS-1 part of [retrocast](../../README.md), its first arcade board.
A game is the zip of its chip dumps, as MAME and FBNeo sets have them
(`ffight.zip`): `retrocast ffight.zip` plays it, `cps1_headless` runs one
without a window.

## Status
- **Games** (210 sets: the plain boards, the Q-Sound games, Pang! 3 and
  most bootlegs): every set MAME 0.289's `cps1.cpp` lists, with MAME's chips and CRCs, the set's
  layout, CPS-B (and where it sits), graphics ROM mapper, DIP defaults and
  clock. A zip is matched by CRC, whatever its name. Which sets, which are
  tested, which are not supported yet and why:
  [compatibility](docs/compatibility.md). What your folder lacks:
  `python tools/cps1_audit.py FOLDER`. The table (`runtime/games.c`) is
  generated: `python tools/cps1_gen_games.py MAME_DIR runtime/games.c`,
  MAME_DIR holding `cps1.cpp` and `cps1_v.cpp` of MAME's `src/mame/capcom/`.
- **Zips**: read by `core/zip.c` (our own inflate); how a game is found
  and loaded: [Loading a game](#loading-a-game).
- **CPUs**: the shared 68000 and Z80 (`cpu/m68k`, `cpu/z80`), their own
  copies (`cps1_` prefix) so they and the Genesis and Master System fit in
  one program; the Z80 runs line by line after the 68000.
- **Sound**: the YM2151 (8 FM channels on the operator shared with the
  Genesis, `core/audio/fm.c`; DT1/DT2, the LFO, noise, timers and their IRQ)
  and the OKI MSM6295 (4 ADPCM voices, pin 7's two rates), mixed to mono
  at 55,930 Hz with MAME's CPS-1 weights. Checked on Final Fight: the
  YM2151 against ymfm (the same level and spectrum), the OKI bit-exact
  against MAME's, the mix against MAME's recording (verification log).
- **The Q-Sound board** (Warriors of Fate, Cadillacs and Dinosaurs, The
  Punisher, Saturday Night Slam Masters, Muscle Bomber Duo): the Z80 at 8 MHz
  with its Kabuki-encrypted code decoded at load (`runtime/kabuki.c`), RAM
  shared with the 68000, a 250 Hz interrupt; the Q-Sound chip
  (`core/audio/qsound.c`, MAME's high-level version) in stereo at 24,038 Hz,
  its tables from `qsound.zip` (MAME's name; `dl-1425.bin`) beside the game's
  zip, which must be there; players 3 and 4; the settings EEPROM (a 93C46,
  `core/devices/eeprom93c46.c`) kept in `GAME.eeprom` next to the zip, as MAME's
  nvram file (Pang! 3's too). Checked: the Kabuki decoding identical to MAME's on the four
  keys' games, the chip sample for sample on Warriors of Fate (verification log).
- **Picture**: the palette (six pages, uploaded on a palette-base write),
  scroll1-3 with flips and scroll2's row scroll, sprites of up to 16x16
  blocks, layer order and the priority masks, the board's graphics ROM
  mapper (which tile codes each layer may use), the two star layers,
  flip screen, vertical monitors (1941, Mercs, Varth turned as MAME does).
  The frame is drawn at once from VBlank's state, as MAME draws it (the
  CPS-1 has no raster interrupt).
- **Detection**: a zip holding at least half of a game's own files, by CRC
  and size, in `retrocast`; in the build (`cmake/detect_system.cmake`
  reads the table from `games.c`).
- **Save states**: F2 / F4 (`GAME.state` next to the zip), refused for
  another game or version; they carry the EEPROM.
- **Recompiled**: `cmake -B build -DROMS="path/ffight.zip"` makes
  `ffight` (and `ffight_headless`): the game's 68000 code as C, on the
  68000 recompiler the Genesis uses (`cpu/m68k/m68k_recomp.c`). The zip is
  not built in: give it to the program at start (a clone's: its parent's
  zip beside it). Code the build's trace did not reach is interpreted and
  written to `ffight.misses`; the next build recompiles it.
  `ffight_headless ZIP --diff` runs the interpreter in lockstep and stops at
  the first difference (checked on ffight, sf2, wof and dino). The Z80 is interpreted.
- **Bootlegs**: MAME's inits (protections, the DIP switches on the low
  byte, a CPS-B mirror, a graphics bit swap) and video quirks; chips
  loaded in parts. Sets on their own memory maps are not supported yet
  ([compatibility](docs/compatibility.md)).
- **Not yet**: DIP switch settings (their defaults).

## Loading a game
MAME's set list is the reference for which games exist and what each
chip's CRC is; its strictness is not. A dump that works keeps working,
whatever its zip is called and whichever MAME release it was made for:

1. **The zip's set**: found by the CRCs and sizes of the chips in it, not by
   names. A zip holding at least half of a set's own chips is that set;
   a whole set wins over a partial one, and where a zip holds several
   (a merged set), the set named like the zip.
2. **Only the chips the machine reads**: program, graphics, sound. PAL
   dumps and other files MAME lists but never reads are not asked for, so
   an older dump is not refused for lacking them.
3. **A chip the zip lacks** is looked for by CRC, in this order: the
   parent's zip beside it (`sf2.zip` for `sf2ua.zip`, MAME's split sets),
   then every other zip in the same folder, whatever it is called.
   Versions of a game share most chips, so a partial zip often plays from
   what the folder already holds. The search stops at the first zip that
   completes the set.
4. **Still missing**: the game does not start, and the message names the
   first missing chip's CRC and the parent's zip.

`python tools/cps1_audit.py FOLDER` lists which sets a folder holds whole,
partly or not at all, by the same rules. `python tools/cps1_fix.py DIR...
--to OUT` copies zips into OUT under MAME 0.289's names, adding to each
the chips it lacked from the other zips (so the copies work in MAME as
well, PAL dumps aside); it overwrites nothing whole. With `--whole`, each
copy also holds its parent's chips (MAME's non-merged sets): every zip
plays alone, in any folder.

## Controls and settings
Both players: buttons 1, 2, 3 on the pad's B, A and X (keyboard Z, X, S;
gamepad South, East, North), a coin on Select (Right Shift, gamepad Back),
Start. Street Fighter II's kicks (buttons 4-6) are on Y, L and R (keyboard
A, Q, W). Forgotten Worlds' rotary dial turns with L and R, 20 steps a
frame as MAME's keys turn it. A third player (Mercs, The King of Dragons,
Knights of the Round, Warriors of Fate, Cadillacs and Dinosaurs, Final
Fight 30th Anniversary) and a fourth (Captain Commando, the Slam Masters
games) play on the third and fourth gamepad, in the order they are
connected. A recording of such a game keeps all four pads
(`--record`, version 3). `cps1.ini` next to `retrocast` has no CPS-1 settings yet (the
DIP switches keep each game's defaults).

## Running
`retrocast GAME.zip` plays it. `cps1_headless GAME.zip [--frames N]
[--play] [--ppm FILE] [--wav FILE] [--state-at N FILE] [--load-state FILE]`:
`--play` drops a coin, presses Start on the title (frame 1,300), then walks
right; `--ppm` saves the last frame, `--wav` the sound (stereo on the Q-Sound
board); a loaded state goes on from its frame.

## Docs
- [Roadmap](docs/roadmap.md)
- [Verification log](docs/verification-log.md)
