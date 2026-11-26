# Sega Master System / Mark III and Game Gear

The Master System and Game Gear part of [retrocast](../../README.md): `retrocast` plays a
raw `.sms` or `.gg`, `sms_headless` runs one without a window, and `smsrecomp`
recompiles one (through `-DROMS`, see the
[root README](../../README.md#recompiling-a-game)).

## Status
- **CPU**: the shared Z80 (`cpu/z80`), which passes every SingleStepTests
  z80 file; this system links its own copy (`sms_` prefix) so it and the
  Genesis fit in one program.
- **Recompiled**: the code reached by a trace of scripted play and by your
  own play (`NAME.misses`), as C basic blocks; `--diff` compares every
  frame with the interpreter. Ten games ran 3,000 frames without a
  difference, 68-99.9% of their cycles recompiled; no faster than the
  interpreter, since drawing the picture costs far more than the Z80.
- **Cartridges**: Sega's mapper with cartridge RAM (kept in `game.sms.sav`),
  Codemasters' mapper; raw `.sms`, with or without a 512-byte copier
  header. No BIOS needed. Not yet: Korean and other mappers.
- **Picture**: the VDP's mode 4 at 192 lines: scrolling and its locks,
  flipped tiles, priority, 8x8, 8x16 and zoomed sprites, eight a line,
  frame and line interrupts; the TMS9918's Graphics I and II with their
  sprites (the Korean MSX ports). Not yet: text and multicolour modes, the
  SMS2's 224- and 240-line modes, palette changes within a frame.
- **Sound**: the PSG, 44,100 Hz mono. Not yet: the FM sound unit.
- **Games**: of every 5th game in the No-Intro set, 124 of 137 reach a
  title screen or play ([verification log](docs/verification-log.md)).
- **Game Gear**: a mode of the same machine, chosen by the header's region
  (5-7) or, without a header, a `.gg` name; a Master System cartridge runs
  in Master System mode, as on the console. The 160x144 LCD, the 12-bit
  palette, Start on port $00 (no Pause), 60 Hz only. Not yet: stereo (port
  $06 is ignored; the sound is mono).
- **Detection**: the "TMR SEGA" header with a Master System region (or Game
  Gear's, as `gg`); a game without one needs the `.sms` or `.gg` extension
  (or `--system sms` / `gg`).

## Controls and settings
Button 1 = B (keyboard Z), button 2 = A (keyboard X), the console's Pause
button = Start (Enter), the Game Gear's Start button on a Game Gear; both
pads. `mastersystem.ini` (`gamegear.ini` for the Game Gear) next to
`retrocast`: `region = auto` (PAL when the file name has `(Europe)`), `ntsc`
or `pal`; the Game Gear is always 60 Hz.

## Playing and testing
```
cmake -S . -B build -DSYSTEMS=mastersystem -DTESTS=ON
cmake --build build --config Release
build/retrocast path/to/game.sms
build/sms_headless path/to/game.sms --frames 600 --play --ppm last.ppm --wav sound.wav
python -m unittest discover -s tests/mastersystem -t .
```
The boot test plays four games from `roms/Sega - Master System - Mark III`
(or `MASTER_SYSTEM_ROMS_DIR`; .7z files, read with 7z on the PATH) and is
skipped without them; likewise four Game Gear games from
`roms/Sega - Game Gear` (or `GAME_GEAR_ROMS_DIR`).

## Docs
- [docs/roadmap.md](docs/roadmap.md): milestones S1-S4 and what is not modelled
- [docs/verification-log.md](docs/verification-log.md): what was checked, and how
