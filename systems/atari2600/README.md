# Atari 2600

The Atari 2600 part of [retrocast](../../README.md): `retrocast` plays a raw
`.a26` cartridge in the interpreter, `atari2600_headless` runs one without
a window, `atari2600recomp` recompiles one (through `-DROMS`, see the
[root README](../../README.md#recompiling-a-game)).

## Status
- **CPU**: the shared 6502 core with NMOS decimal mode on. The NMOS
  SingleStepTests vectors for the decimal opcodes (ADC, SBC, ARR, RRA,
  ISC) and eight bus-cycle opcodes pass; the other opcodes are the NES's,
  checked there.
- **Cartridges**: 2K, 4K, F8, F6 and F4 (8K to 32K, bank hotspots on read
  and write), the Superchip's RAM (F8SC, F6SC, F4SC), CBS RAM Plus (FA),
  Parker Brothers (E0), M Network (E7) and Tigervision (3F), found by size
  and by Stella's byte signatures; the unit tests pass. The recompiler takes
  2K to F4; the rest play in the emulator. Not yet: Starpath Supercharger
  tapes, Pitfall II's DPC chip.
- **RIOT**: RAM, both ports, the timer with its four dividers and the
  edge flag; checked by unit tests.
- **Picture**: playfield, both players, missiles and ball, all
  collisions, horizontal motion and HMOVE blank, RSYNC, delayed writes;
  NTSC and PAL palettes. Checked by the unit tests, not by a public test
  ROM suite. Sprite size changes in mid-draw and late HMOVE quirks differ
  from hardware.
- **Sound**: both channels, mono, 44,100 Hz; checked that it plays and
  that the recompiled program makes the same samples. No reference
  recording.
- **Games**: four sampled games matched the interpreter in lockstep over
  600 scripted frames each ([verification log](docs/verification-log.md)).
- **Recompiled**: reachable code from a trace of scripted play, the rest
  in the interpreter; `--diff` compares every instruction. The share of
  cycles recompiled over many games is not measured.
- **Not yet**: paddles and other controllers, SECAM, the other cartridge
  schemes ([roadmap](docs/roadmap.md)).

## Playing and building
```
cmake -S . -B build -DSYSTEMS=atari2600
cmake --build build --config Release
build/retrocast path/to/game.a26
build/atari2600_headless path/to/game.a26 --frames 120
```

## Controls and settings
Arrow keys and X are the first joystick and its button; Enter and Right
Shift are console reset and select. F5 resets, F2 saves a state, F4 loads
it. Two gamepads work.

`atari2600.ini` has `mapper` (`auto`, `2k`, `4k`, `f8`, `f6`, `f4`, `f8sc`,
`f6sc`, `f4sc`, `fa`, `e0`, `e7`, `3f`) and
`region` (`auto`, `ntsc`, `pal`). Auto region takes `(Europe)` and `(PAL)`
in the file name. `atari2600_headless` takes `--mapper`, `--region`,
`--frames N`, `--play` (scripted input), `--record FILE` and
`--replay FILE` (controller and reset inputs; a replay runs the
recording's length), `--state-at F FILE` / `--load-state FILE`, `--ppm
FILE`, `--diff` and `--coverage`.

## Recompiling
Configure with `-DROMS="path/to/game.a26"` and build as above. The build
traces scripted play and produces the game and its `_headless`
counterpart. `AUTO_HINTS=OFF` skips the trace and compiles from the reset
entry. `EMBED_ROM=OFF` takes the ROM path at run time. Code the build did
not find runs in the interpreter. `systems/atari2600/games/<target>.toml` (the
normalised build target name) may set `region = "ntsc"` or `"pal"` and
`mapper = "2k"`, `"4k"`, `"f8"`, `"f6"` or `"f4"`; it applies to the
trace and the program. A program refuses another ROM, mapper or region.

## Docs
| File | Content |
|------|---------|
| [roadmap.md](docs/roadmap.md) | Milestones A1-A6, what is open |
| [verification-log.md](docs/verification-log.md) | What was checked, how, and the result |
