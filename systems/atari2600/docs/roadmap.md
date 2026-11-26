# Atari 2600 roadmap

The order rule ([docs/roadmap.md](../../../docs/roadmap.md)): the reference
before the thing it checks. The CPU first, then the cartridge and the
chips around it, then the window program and the recompiler. A milestone
is done when its exit test passes in CI. The 2600 has no public test ROM
suite wired in yet, so the exits below are the project's own tests (in
`systems/atari2600/tests/` and `tests/atari2600/`); "not checked" marks what no
test touches.

| Milestone | Content | State |
|---|---|---|
| [A1](#a1--cpu-cpu6502) | the 6507 as the shared `cpu/6502`, NMOS decimal mode | done with open items (13 opcodes in the NMOS vectors) |
| [A2](#a2--cartridges-and-riot) | cartridge banking, bus, RIOT | done with open items (schemes missing) |
| [A3](#a3--tia-picture) | the TIA picture, collisions, input | done with open items (quirks, paddles, SECAM) |
| [A4](#a4--sound) | TIA audio | done with open items (no reference recording) |
| [A5](#a5--window-program) | window program, states, recordings, headless | done |
| [A6](#a6--recompiler) | recompiler, lockstep `--diff`, play-to-trace | done with open items |

## A1 · CPU (cpu/6502)
- [x] The 6502 core is shared with the NES (`cpu/6502`); the Atari
  switches decimal mode on (`decimal_enabled`, off for the NES's 2A03);
  the bus test checks the flag is set.
- [x] The 13-bit address bus: RAM, TIA and RIOT mirrors and the cartridge
  window decoded from the low 13 address bits (`bus.c`).
- [x] **Exit:** the SingleStepTests 6502 (NMOS) vectors for ADC, SBC, ARR,
  RRA and ISC (decimal arithmetic) and for BRK, JSR, RTI, JMP (ind), STA
  (ind),Y, LDA abs,X, a branch and INC abs,X (bus cycles), in
  `tests/nes/test_cpu.py` (`sst-nmos`).
- [ ] The other opcodes are not run against the NMOS vectors; they are
  the NES's, checked against the nes6502 vectors and nestest.
- [ ] Unmapped 6507 behaviour (no IRQ or NMI pin): not checked.

## A2 · Cartridges and RIOT
- [x] ROM only: 2K (mirrored) and 4K; Atari banking F8 (8K), F6 (16K), F4
  (32K), the bank picked by a read or a write of the hotspot, power-on in
  the last bank. Other sizes are refused (`cart.c`; `atari2600_cart_tests`,
  `tests/atari2600/test_cart.py`).
- [x] More schemes, for the emulator: Superchip RAM (F8SC, F6SC, F4SC), FA,
  E0, E7 (8K, 12K, 16K) and 3F, detected as Stella does; their slices and
  RAM are in the save state (`A26STAT3`; older states still load). The
  recompiler refuses them. Open: Starpath Supercharger, DPC.
- [x] Scheme and region from the size, the file name (`(Europe)`,
  `(PAL)`) or a setting (`mapper`, `region`).
- [x] RIOT: 128 bytes of RAM and its mirrors, ports A and B with their
  direction registers, the timer with its four dividers and the
  underflow flag, the PA7 edge flag (`riot.c`; `atari2600_bus_tests`).
- [x] **Exit:** `atari2600_cart_tests` and `atari2600_bus_tests`, run by
  `tests/atari2600/test_cart.py`.
- [ ] Missing schemes: F8SC, F6SC and F4SC (Superchip RAM), E0, E7, FE,
  3F, 3E, F0, FA, CV, UA, DPC, DPC+, CDF and the rest. A game on one of
  them is not supported. Cartridge RAM of any kind is not there.
- [ ] The timer and the PA7 flag are checked by unit tests only; Stella
  is consulted, no reference ROM runs them (not checked beyond that).

## A3 · TIA picture
- [x] Playfield (reflect, score mode, priority), two players (copies,
  double and quad size, reflect, delayed graphics), two missiles, the
  ball with its size and delay, the NTSC and PAL palettes (`tia.c`,
  `palette.c`).
- [x] The collision bits and CXCLR; RESxx positions, HMOVE with the
  extended blank, HMCLR; the delayed register writes; VSYNC, VBLANK,
  WSYNC, RSYNC; frames of any length.
- [x] Input: joystick directions on RIOT port A, switches on port B,
  fire buttons INPT4/5 with the latch (VBLANK bit 6).
- [x] **Exit:** `atari2600_runtime_tests`: score-mode priority and
  collision, delayed player graphics, RESMP, HMOVE timing and its blank,
  RSYNC, frames of different lengths, input, and a save state round trip.
- [ ] Sprite size changes while the object is being drawn (NUSIZ in the
  middle of a line): not modelled as on hardware.
- [ ] Late HMOVE and other motion quirks: only the cases the tests above
  check are modelled; the rest is not checked.
- [ ] Paddles (INPT0-3 are not driven), SECAM (the palette is NTSC or
  PAL), the driving controller and keypads: missing.
- [ ] No public test ROM suite (a TIA test cartridge) is run yet, so the
  picture is judged by the unit tests and by games.

## A4 · Sound
- [x] The two audio channels: the 5-bit divider and the pulse and noise
  counters of the 16 waveforms, volume; adapted from Stella's channel
  logic; mono, 44,100 Hz, from the colour clock (NTSC or PAL).
- [x] **Exit:** `atari2600_runtime_tests` writes AUDV and checks that
  audible samples come out; lockstep `--diff` compares the samples of
  the interpreter and the recompiled program.
- [ ] No reference recording: the waveforms are not compared with
  hardware or another emulator's output.
- [ ] The mix is a linear sum of the two volumes; the console's output
  curve is not modelled.

## A5 · Window program
- [x] `atari2600` (SDL window, embedded ROM when recompiled) and
  `atari2600_headless`; NTSC 192 lines at 60 Hz, PAL 228 lines at 50 Hz.
- [x] Joystick on the arrows and X, reset and select on Enter and Right
  Shift, two gamepads, F5 reset, F2 save state, F4 load state; a state
  is checked against the ROM, the region and its ranges before it loads.
- [x] `--record` and `--replay` (controller and reset inputs), `--play`
  scripted input, `--state-at`, `--load-state`, `--ppm`.
- [x] **Exit:** `test_record_and_replay` and
  `test_states_transfer_both_directions` (`tests/atari2600/test_recomp.py`),
  `test_runtime_and_save_states` (`test_cart.py`).
- [ ] The difficulty and colour switches have no key; not checked.

## A6 · Recompiler
- [x] `atari2600recomp`: reachable instructions to C per bank, from a
  trace of scripted play (`--trace`) or the reset entry (`AUTO_HINTS=OFF`);
  `systems/atari2600/games/<target>.toml` sets `mapper` and `region`.
- [x] Code the build did not find, and fetches that touch a bank
  hotspot, run in the interpreter.
- [x] A program refuses to start with another ROM, mapper or region.
- [x] `--diff` runs the interpreter in lockstep and reports the first
  difference (CPU, bank, RIOT, TIA, frame, audio); `--coverage` reports
  the compiled share of CPU cycles.
- [x] **Exit:** `tests/atari2600/test_recomp.py`: lockstep and fallback,
  a wrong program caught by `--diff`, hotspot fetches, hints, external
  ROM, configuration mismatch. Four sampled games matched the
  interpreter over 600 scripted frames each (verification log).
- [ ] No coverage figure over a larger set of games, so the share of
  cycles recompiled is not known in general.
- [ ] Speed against the interpreter: not checked.
