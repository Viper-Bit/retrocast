# Architecture

How the project is built, for every system. Each system's own details:
[NES](../systems/nes/docs/architecture.md), [Game Boy](../systems/gb/docs/architecture.md).

## Goals
1. Run games as native executables built from their recompiled CPU code.
2. Be correct first: every layer is checked against an independent reference.
3. Keep the output readable: generated C, one function per basic block,
   named by bank and address (`b_07_C079`), so the binary also decompiles
   cleanly in IDA/Ghidra.

Non-goals for now: netplay.

## Layout
```
retrocast/
  CMakeLists.txt     build defaults, SDL3, retrocast, frontend(), ROMS / FDS_BIOS / AUTO_HINTS / EMBED_ROM
  cmake/             SDL3 build options; detect_system.cmake: the system of a ROM, for ROMS
  core/              shared by every system
    input_log.c      input recordings, pad bits
    detect.c         which system a file is for, from its bytes; system_detect.c: the same as a program
    frontend/        sdl3_main.c settings.c tv_frame.c; system.h: a system's interface (System)
    recomp/          template.c: instruction templates and their PC markers
  cpu/               CPUs, one folder each, shared by every system with that CPU
    README.md        what cpu/ holds and how a system uses a CPU
    6502/            e.g. the 6502: opcode table, templates, interpreter, switch generator
    ...              one folder per CPU (the table in cpu/README.md)
  systems/           one folder per system
    nes/               the NES and the Famicom Disk System
      README.md, docs/ its status, mappers, roadmap, verification log
      CMakeLists.txt   nes_recompile(), nes_headless, nesrecomp
      recomp/          nesrecomp: analysis, emitter
      runtime/         bus, PPU, APU, mappers, disk drive; recomp_rt.h
      frontend.c       the NES behind core/frontend/system.h
      tests/           C test runners (cpu_tests.c, nes_headless.c)
      games/           per-game hints (<name>.toml)
    gb/                the Game Boy and Game Boy Color, laid out the same way
      README.md, docs/
      CMakeLists.txt   gb_recompile(), gb_headless, gbrecomp
      recomp/          gbrecomp: recomp.c (regions, blocks), main.c
      runtime/         bus (gb.c), PPU, APU, cartridges; recomp_rt.h
      frontend.c, tests/
    ...                the other systems, laid out the same way
  tests/             Python unittest suite: one folder per system; fetch_test_roms.py, shared helpers
  tools/             bench.py, smoke_games.py, make_release.py, ci_systems.py, ...
  dist/              README.txt for the release archives
  docs/              this: what is shared
```
A new system is a new folder in `systems/`, beside the others, with the same parts.
A new CPU is a new folder in `cpu/` (see [cpu/README.md](../cpu/README.md)).
`tools/ci_systems.py` has the table of which systems use each CPU, so a
change under `cpu/6502/` tests the NES. Code moves to `core/` once a
second system needs it.

## The pipeline
```
              build time (CMake)                                  run time
ROM ─► trace: <sys>_headless --play --misses (interpreter) ─┐
    └► <sys>recomp: decode, blocks, emit C, embed ROM ◄──────┘
                 └► gen/<game>.c ─► cc + <sys>/runtime + core ─► <game>(.exe)
                                                                  │
               dispatch: (pc, bank mapped at pc) → block function ┤
                        none → the interpreter, one instruction   │
               core/frontend: SDL3 window, sound, gamepads,       │
                        settings, states, recordings              ┘
```

## Instruction templates
Each CPU's instructions are written once, as a few lines of C per opcode
(e.g. `cpu/6502/c6502.c`; see [cpu/README.md](../cpu/README.md)). The
generator in each CPU folder (e.g. `cpu6502_gen`) writes that CPU's
interpreter switch (the 68000: its handlers) from them, and the recompilers build the recompiled
blocks from the same lines, so bus traffic and cycle counts of both are
identical by construction. The templates never name the PC in C:
every use is a marker (`core/recomp/template.h`: operand fetch, read at the
PC, its value, step, jump, branch; for the 68000's prefetch queue also
the extension word, the refill and the queued word), which the interpreter
expands to run-time C and the recompiler to constants (the code bytes and
addresses it knows). A raw `c->pc` in a template stops the build, and so do operand
fetches that stop matching the instruction's size, so a template change
cannot silently read the wrong bytes.

## Recompiled code
- **Blocks**: one C function per basic block. A `switch (c->pc)` at the
  top makes every instruction an entry point (code resumes mid-block after
  an interrupt without falling back). After each instruction the block
  returns if the interpreter would do something else next (an interrupt
  is due, the frame is over), so recompiled and interpreted runs take the
  same steps.
- **Chaining**: a block continues in the next one when it is known at
  build time and in the same region (`RECOMP_CHAIN`, a guaranteed tail
  call with clang and gcc 15+; other compilers return to the dispatcher).
- **Banks**: code is compiled per region (a ROM bank in an address window)
  and looked up by the bank mapped at run time, so a wrong guess about
  banking costs coverage, never correctness. After a store that may switch
  banks, a block checks its own bank and returns if it changed.
- **Identity**: the generated code carries an FNV-1a hash of the ROM; the
  runtime uses it only if the loaded ROM matches.
- **Embedded ROM**: the generated C also holds the whole ROM, used when no
  ROM path is given. Data is read through pointers whose range no static
  analysis can bound, so leaving bytes out could break a game late. A build
  therefore contains the game and must not be shared.

## Missed code: the feedback loop
Static decoding cannot see every target (jump tables, returns used as
jumps, code in RAM). The interpreter runs what was missed, and
`<sys>_headless --misses` lists it; run without recompiled code it lists
every instruction executed, so one interpreter run is a complete trace of
that session. With `AUTO_HINTS` (on by default) the build traces each game
with scripted input before recompiling it. The NES also keeps hints per
game and the misses of your own play (`systems/nes/README.md`).

## The interpreter
Every system has a reference interpreter, sharing the CPU struct and the
bus with the recompiled code. It runs what the recompiler did not see and
interrupt entry; it runs whole games on its own (`build/retrocast`);
and it is the **oracle**: validated against independent tests (per-opcode
suites, test ROMs), then the recompiled code is diffed against it.

## What the lockstep diff proves, and what it does not
`<game>_headless --diff` runs an interpreter-only machine beside the
recompiled one and stops at the first difference. Since both share the
templates, a match proves that translation, block discovery and bank
handling are right: the recompiled program does what the interpreter
does. It cannot catch an instruction both get wrong. That rests on the
interpreter's own checks (rungs 2, 3 and 6 below).

## Save states
The whole machine is one struct per system, the same in interpreter and
recompiled builds (recompiled code keeps no state of its own), so a state
saved by one loads in the other: header (magic, version, struct size, game
hash), then the struct. Pointers (ROM data, bus, linked code) are re-created
on load. Shortcut: the raw struct ties a state to one build layout; a
field-wise format is needed once states must survive program updates.

## Frontend
SDL3 window, audio and gamepads (`core/frontend/`), the same for every
system. A system plugs in through `core/frontend/system.h`: it loads the
game and its saves, runs a frame (input in, picture and sound out), saves
and loads states, says why a game halted, and takes the keys and settings
that are its own. The frontend does the rest.
- **One program, every system**: each `systems/<sys>/frontend.c` exports
  one `System` table (static functions behind it, no global names), and
  CMake writes the list of the systems a program links (`system_list`):
  `retrocast` gets every system in `SYSTEMS`, a recompiled game its own one.
- **Which system** (`core/detect.h`): each system has a detector over the
  file's bytes, scoring it 0-100: 100 for a header the console itself
  checks (NES and FDS headers or a raw FDS disk side, the Game Boy's logo
  and header checksum, the Genesis "SEGA" at $100, the Sega 8-bit "TMR
  SEGA" whose region tells the Master System from the Game Gear), a guess for the Atari
  2600 (no header: a cartridge size and a reset vector into the cartridge
  window), too weak to decide alone: the `.a26` extension confirms it.
  The best score wins; the extension adds 20 (ties, and the Atari); two
  sure answers or none is an error, and `--system` decides. The build's
  `ROMS` list uses the same rules (`cmake/detect_system.cmake`;
  `tests/test_detect.py` runs both on the same files).
- **Two systems on one CPU**: the NES and the Atari 2600 both run the
  shared 6502, the Genesis and the Master System the Z80, each with its own
  bus functions; each gets its own copy of the interpreter
  (`cpu/README.md`). The Game Gear is a mode of the Master System, not a
  system of its own in the build, with its own detector and `System`
  table.
- **Shared sound chips** (`core/audio/`): a chip lives in its system's
  folder while one system uses it, and moves here when a second needs it.
  Now: the FM operator of the Yamaha OPN / OPM chips (`fm.c`), under the
  Genesis' YM2612 and the CPS-1's YM2151; the Q-Sound chip (`qsound.c`),
  for the CPS-1 now and the CPS-2 next.
- **Shared chips that are not sound** (`core/devices/`), by the same rule:
  the 93C46 serial EEPROM (`eeprom93c46.c`; the CPS-1's Q-Sound board and
  Pang! 3, the CPS-2 next).
- **Shared plumbing** (`core/`): a whole file read (`file.c`), the
  headless programs' pictures and sound (`capture.c`: PPM and WAV), zips
  (`zip.c`), recordings (`input_log.c`), detection (`detect.c`). A
  recompiled 68000 game's `NAME.misses` is written by
  `cpu/m68k/m68k_misses.c`, for the Genesis and the CPS-1.
- **Sound**: the system names its rate and channels (`SysInfo`: the NES
  mono, the Game Boy stereo) and returns sample frames, interleaved.
- **Input**: one set of 16-bit buttons per player for every system (A, B,
  X, Y, L, R, Select, Start, the directions; 4 bits free), from the
  keyboard and up to four gamepads; each system reads the ones its pad has,
  and says how many players its game has (`SysInfo.players`).
- **Recordings** (`core/input_log.c`): version 2 names the system and keeps
  16 bits per pad; version 3 the same for four pads (a game with more than
  two players); version 1 (NES, a byte per pad) still loads.

The emulator runs on its own
thread, so window moves and device changes do not stall the sound.
Settings come from `<program>.ini` next to the program (`settings.c`);
`retrocast` keeps one per system (`nes.ini`, `gb.ini`, ...).
Scaling is done by the frontend (fit, integer or stretch), so the optional
TV frame (`tv_frame.c`) and the picture scale together.

## Verification ladder (each rung must pass before the next)
1. The opcode table matches an independent table.
2. The interpreter matches a reference log (NES: `nestest.log`).
3. The interpreter passes per-opcode tests cycle by cycle (SingleStepTests).
4. Recompiled test code matches the same references.
5. Lockstep diff: games run recompiled and interpreted side by side, the
   first divergence printed.
6. The system's test ROMs (blargg, mooneye, acid2 and others) pass in the
   interpreter build.
7. Frame-hash regression for the recompiled games in a build (NES:
   `tests/nes/test_regression.py`).
