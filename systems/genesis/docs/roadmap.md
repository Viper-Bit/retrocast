# Genesis / Mega Drive roadmap

The order rule ([docs/roadmap.md](../../../docs/roadmap.md)): the reference
before the thing it checks. The two CPUs come first, each against its
public single-step corpus, then the machine around them, then the
recompiler. A milestone is done when its exit test passes in CI.

| Milestone | Content | State |
|---|---|---|
| [C1](#c1--z80-cpuz80) | Z80 templates and interpreter (`cpu/z80`) | done |
| [C2](#c2--68000-cpum68k) | 68000 templates and interpreter (`cpu/m68k`) | done |
| [D1](#d1--the-machine) | memory map, I/O, Z80 bus arbitration, cartridges | done but the public test ROMs |
| [D2](#d2--vdp) | the VDP: planes, window, sprites, DMA, interrupts | done but the public test ROMs |
| [D3](#d3--window-program) | the window program, pads, save states | done |
| [D4](#d4--sound) | SN76489 and YM2612 | done but the reference recording |
| [D5](#d5--recompiler) | the 68000 recompiler, lockstep `--diff` | done |

## The hardware
Facts the milestones build on (NTSC; PAL where it differs). Sources:
Sega's Genesis technical overview and software manual as reproduced on
plutiedev.com and the SpritesMind / Sega Retro wikis; each milestone
checks what it uses against a test ROM or the single-step corpora, and
corrects this list where they disagree.

- **Clocks**: master clock 53.693175 MHz (PAL 53.203424). 68000 =
  master / 7 (7.67 MHz), Z80 = master / 15 (3.58 MHz). The YM2612 runs
  at master / 7, the SN76489 (inside the VDP) at master / 15.
- **68000 memory map**:
  - `$000000-$3FFFFF` cartridge ROM, linear (no bank register; the few
    larger games use a mapper at `$A130F3-$A130FF`). Battery RAM, when the
    header says so, is switched in over ROM by `$A130F1`.
  - `$400000-$7FFFFF` expansion (Mega-CD): not emulated.
  - `$A00000-$A0FFFF` the Z80's space as the 68000 sees it (only while
    it holds the Z80 bus).
  - `$A10000-$A1001F` I/O: version register `$A10001`, pad data
    `$A10003/5/7`, pad control `$A10009/B/D`.
  - `$A11100` Z80 bus request, `$A11200` Z80 reset; `$A14000` TMSS
    (later models: the game writes "SEGA" there or the VDP stays locked).
  - `$C00000-$C0001F` VDP: data `$C00000`, control `$C00004`, H/V
    counter `$C00008`, PSG `$C00011`.
  - `$E00000-$FFFFFF` work RAM, 64 KB, mirrored (games use `$FF0000`).
- **Z80 memory map**: `$0000-$1FFF` 8 KB RAM (mirrored at `$2000`),
  `$4000-$4003` YM2612, `$6000` bank register (9 bits, written one bit at
  a time), `$7F11` PSG, `$7F00-$7F1F` VDP, `$8000-$FFFF` a 32 KB window
  into the 68000's space at the bank.
- **Interrupts** (68000 autovectors): vertical blank level 6, horizontal
  (line counter) level 4, external (pad port) level 2. The Z80 gets its
  interrupt (IM 1) at vertical blank.
- **VDP**: 64 KB VRAM, 64 colours of 9 bits in CRAM (4 palettes of 16),
  40 words of vertical scroll RAM, 24 registers. Two scrolling planes (A,
  B), a window plane, sprites; one priority bit per tile and per sprite;
  shadow/highlight mode. Widths 256 (H32) or 320 (H40) pixels, 224 lines
  (240 on PAL in V30). Sprites: 80 in H40 (64 in H32), 20 per line (16),
  each 1-4 by 1-4 tiles. DMA: 68000 memory to VRAM, CRAM or VSRAM; VRAM
  fill; VRAM copy; the 68000 stops while it copies from its memory.
  262 lines a frame (PAL 313).

## C1 · Z80 (cpu/z80)
- [x] Templates for every opcode, documented and undocumented (CB, DD,
  ED, FD, DDCB, FDCB tables), written once as for the SM83; the
  interpreter's switch generated from them (`z80_gen`); names prefixed
  `z80_` (cpu/README.md).
- [x] Interrupts (IM 0/1/2, NMI), HALT, the R register, the undocumented
  flags (bits 3 and 5, from WZ where the hardware takes them).
- [x] **Exit:** SingleStepTests z80 (pinned commit), every file: registers,
  flags, RAM, I/O ports, and the bus cycle by cycle.

## C2 · 68000 (cpu/m68k)
- [x] Templates per instruction and addressing mode, written once
  (`cpu/m68k/m68k.c`, markers `@W` `@N` `@Q` for the prefetch queue's
  words); the interpreter's 1,541 handlers and its 64K table generated
  from them (`m68k_gen`); the two-word prefetch queue; names prefixed
  `m68k_`.
- [x] Exceptions: address errors (the 7-word frame, the PC the microcode
  pushes, which register steps stand), illegal and privileged
  instructions, line A/F, TRAP, TRAPV, CHK, divide by zero, trace,
  interrupts by level (the last two not in the corpus). Bus errors are not
  raised (no system needs them yet).
- [x] **Exit:** SingleStepTests m68000 (pinned commit): all 127 families
  pass every test on state and on every bus transaction with its clocks;
  TAS and TRAPV by state only (the corpus' README: their logs are not
  reliable), both pass.

## D1 · The machine
- [x] The memory maps above, the I/O ports (3- and 6-button pads), the
  version register, Z80 bus request and reset, the Z80 bank, cartridge
  ROM and battery RAM from the header, TMSS (`systems/genesis/runtime/md.c`).
  Also the SSF2 bank registers (ROMs over 4 MB) and the region from the
  header (the Americas when allowed, else Japan, else Europe at 50 Hz).
  The console is a version 0 one (before TMSS): 14 early games (launch
  carts, After Burner II, Super Daisenryaku...) touch the VDP before
  writing "SEGA" and lock on a TMSS console, as on the real one; TMSS is
  enforced when the version register says 1.
- [x] Both CPUs on one master-clock timeline: the Z80 runs up to the
  68000's clock after each 68000 instruction; its INT at vertical blank.
- [x] **Exit, part 1:** a sample of the licensed set boots to its first
  VDP writes (`tests/genesis/test_boot.py`, local: every 40th game);
  the machine's self-checks (`systems/genesis/tests/md_tests.c`, CI). The whole
  set, once: 1,555 of 1,566 (verification-log.md).
- [ ] Open: Triple Play 96 and Triple Play Gold (a cartridge with its own
  ROM mapping), Phantasy Star Fukkokuban (halts on a double fault).
- [ ] **Exit, part 2:** public test ROMs for the memory map and the CPUs
  on the machine. None found yet that reports without a picture: the
  candidates (240p Test Suite's Z80 RAM and pad tests, flamewing's
  68k-bcd-verifier) show their results on screen; with D2 in, what is
  left is checking their licences and pinning them.
- Added later: serial EEPROM saves (`runtime/eeprom.c`: 24C01 to 24C65 on
  Sega's, EA's and Acclaim's wiring, by product code or the header's $E8
  $40 flag; not Codemasters' J-Cart), the open bus as the prefetched word.
- Left out: wait states of the Z80's window into the 68000's space.

## D2 · VDP
- [x] Registers, the data and control ports, VRAM/CRAM/VSRAM, the three
  DMA kinds with their timing, the H/V counter, the interrupts
  (`systems/genesis/runtime/vdp.c`). DMA runs at once: a 68000-to-VDP transfer
  stops the 68000 for the time it takes at the line's rate (18 or 205
  words a line in H40, 16 or 167 in H32); a fill or copy keeps the status'
  DMA bit set for its time.
- [x] Rendering, a line at a time once the CPUs have run through it:
  planes A and B with full and per-cell or per-line scrolling, per-column
  vertical scrolling, the window, sprites with their limits (20 or 16 a
  line, a line's worth of sprite pixels, 80 or 64 in the list) and x = 0
  masking, priorities, shadow/highlight with the operator colours, the
  left column blank; H32/H40, V28/V30.
- [x] **Exit, part 2:** a contact sheet of a sample of the licensed set
  reaches title or play screens (`tools/genesis_sheet.py`, local; looked
  at: verification-log.md); the VDP's self-checks (`systems/genesis/tests/md_tests.c`).
- [ ] **Exit, part 1:** public VDP test ROMs pixel for pixel. Candidates:
  Nemesis' Sprite Masking and Overflow Test ROM, the 240p Test Suite's
  patterns; neither has a licence we could check yet, and pixel checks
  need reference pictures from a console.
- Not modelled yet: changes in the middle of a line (a line is drawn from
  the state at its end), the FIFO and its waits, the HV counter latch,
  interlace (double-height tiles, the counters), mode 4, the sprite
  attribute cache, the uneven H counter, the console's colour levels
  (a linear scale for now), CRAM dots.

## D3 · Window program
- [x] `genesis` behind `core/frontend/system.h` (`systems/genesis/frontend.c`):
  picture, pads (3 and 6 buttons on the 16-bit input, the `pad` setting),
  save states (`md_state_save`: the machine and the battery RAM, checked
  against the ROM's hash), recordings (system "md"), battery saves
  (`ROM.sav`), the reset button. H32 is stretched to H40's width (nearest
  pixel); NTSC shows 224 lines, PAL 240.

## D4 · Sound
- [x] SN76489, then YM2612 (6 FM channels, channel 6 as DAC), stereo
  (`systems/genesis/runtime/sound.c`): the PSG's tones, noise (Sega's 16-bit
  LFSR) and 2 dB volume steps; the YM2612's phase (detune, multiple),
  envelopes (rates with key scaling, the increment tables), the eight
  algorithms with feedback, the LFO's AM and PM, timers A and B,
  channel 3's special mode, the DAC, panning. One sample every 144 YM2612
  clocks (53,267 Hz NTSC), on the master clock; the PSG averaged over each
  sample; the output's DC blocked as by the console's capacitors. The
  YM2612 resets with the Z80's reset line; a Z80 access through its window
  waits 3 T-states.
- [x] **Exit, part 1:** self-checks with known answers
  (`systems/genesis/tests/md_tests.c`): the PSG's and the YM2612's pitch to
  0.5 Hz of the formulas, a full-level operator's peak, the release,
  timer A to the sample, the DAC. Games' music on the A440 grid
  (verification-log.md). No public sound test ROM found.
- [ ] **Exit, part 2:** the output of a sample checked against a reference
  recording from a console: none at hand.
- Not modelled: SSG-EG, CSM, the busy flag, the DAC's ladder effect and
  9-bit steps, the console's low-pass filter, the 68000's wait on Z80
  window accesses; LFO PM is a smooth scale, not the chip's table; the
  PSG's level against the FM is an estimate.

## D5 · Recompiler
- [x] 68000 code from the cartridge recompiled (`systems/genesis/recomp/main.c`,
  `mdrecomp`): one region, the ROM that is always mapped (`md_code_end`:
  not the SSF2 banks, not where battery RAM can be switched in); entries
  from the vectors, the interpreter's trace (AUTO_HINTS) and play misses
  (`NAME.misses`); static flow through Bcc, BRA, BSR, DBcc and absolute or
  PC-relative JMP/JSR. Each instruction is the interpreter's handler body
  with `op` a constant (the 68000's templates hold two-path instructions
  such as DBcc, where the expander's straight-line PC constants would be
  wrong, so the PC stays a run-time value). A block ends after any
  instruction whose template can change the PC. Instruction lengths come
  from `m68k_ext_words`, checked at build time against the 39,853 templates
  without a branch. The Z80 runs from its RAM (the sound driver the 68000
  copies there), so it stays interpreted. Not done: per-game hint files.
- [x] **Exit:** `genesis_headless --diff` in lockstep on a sample, with
  the share of 68000 cycles recompiled: 8 games (every 200th of the
  licensed set), 3,000 frames each, no difference, 94.33-99.97% of the
  68000's clocks recompiled; in CI, a ROM of random instructions
  (`systems/genesis/tests/random_rom.c`, 100%).

## Later
- Arcade boards with the 68000 and Z80 (CPS-1, Neo Geo).
