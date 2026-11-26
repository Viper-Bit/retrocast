# Master System / Mark III roadmap

Order rule ([docs/roadmap.md](../../../docs/roadmap.md)): the reference before
the thing it checks. The Z80 interpreter comes first, against its public
single-step corpus; then the machine and the window program; last the Z80
recompiler and its lockstep diff.

| Milestone | Content | State |
|---|---|---|
| [S1](#s1--the-machine) | cartridge and mappers, RAM, I/O, VDP, PSG, interrupts, headless | done (public test ROMs open) |
| [S2](#s2--window-program) | window program, pads and Pause, cartridge RAM saves, save states | done |
| [S3](#s3--recompiler) | Z80 recompiler, lockstep `--diff` | done |

## S1 · The machine
- [x] **Z80**: the shared interpreter in `cpu/z80`, checked against all
  SingleStepTests z80 files (CPU milestone C1, Genesis). The Master System
  links its own copy with prefixed bus functions (`z80_library(sms_z80
  sms_)`), so it and the Genesis share one `retrocast` program.
- [x] **Cartridge**: the `TMR SEGA` header at $1FF0/$3FF0/$7FF0 and its
  region; Sega's mapper (three 16 KB slots at $FFFD-$FFFF, the fixed first
  1 KB, cartridge RAM over slot 2 through $FFFC) and Codemasters' (banks
  written at $0000/$4000/$8000, found by its header's checksum); a raw
  `.sms`, with or without a 512-byte copier header.
- [x] **RAM and I/O**: 8 KB at $C000, mirrored; the mapper registers
  written through to RAM. Ports decoded by A7, A6 and A0: memory and I/O
  control ($3E/$3F), V and H counters, VDP, PSG, both pads, Reset, the TH
  lines as the I/O control sets them (an export console).
- [x] **VDP, TMS9918 modes**: Graphics I and II, the fixed palette, 4-byte
  sprites four a line (the Korean MSX ports). Not text or multicolour.
- [x] **VDP**: mode 4 at 192 lines. Ports with the read buffer, the frame
  and line interrupts and the status flags; 4-bitplane tiles, scrolling
  (with the top-row and right-column locks), flips, the second palette,
  priority over sprites, the hidden left column; sprites from the split
  table, 8x8 and 8x16, zoomed, eight a line with the overflow flag, and
  collisions.
- [x] **PSG**: three tones and noise (white noise taps bits 0 and 3), at
  the Z80 clock / 16, 44,100 Hz mono.
- [x] **Timing**: 228 T-states a line, 262 lines (NTSC) or 313 (PAL);
  interrupts checked before each instruction; Pause is the NMI.
- [x] **Exit:** `sms_tests` (header, both mappers, cartridge RAM, ports,
  VDP ports, tile and sprite drawing, interrupts, frame length, Pause,
  states) and `tests/mastersystem/test_sms.py` (four games, one on the
  Codemasters mapper, show a picture after 900 frames of scripted play).
- [ ] Open: public test ROMs (ZEXALL on the console, FluBBa's VDP tests,
  the SMS Test Suite) in `tests/fetch_test_roms.py`.

## S2 · Window program
- [x] `retrocast` plays a `.sms`: the picture, both pads (button 1 = B,
  button 2 = A, Start = Pause), NTSC or PAL (`region` in
  `mastersystem.ini`, else `(Europe)` in the file name), cartridge RAM in
  `game.sms.sav`, save states.
- [x] **Exit:** `retrocast` builds with every system, and `system_detect`
  names Master System files `sms` (`tests/test_detect.py`).

## S3 · Recompiler
- [x] `smsrecomp` turns the reachable code into C basic blocks from the
  instruction templates of `cpu/z80` (opcode and operand bytes as
  constants, every bus cycle kept). Code is keyed by the ROM page mapped in
  its slot and its address; a block returns to the runtime when the line
  ends, an interrupt the Z80 would take is due, the CPU halts, or the page
  under the next instruction changed, and chains to the next block when
  it is known. Entry points: reset, RST, NMI, a trace of scripted play and
  the code your own play reached (`NAME.misses`, written by the window
  program); then the targets and fallthrough of what they reach. DD CB /
  FD CB instructions and the DD/FD opcodes that run as base ones stay in
  the interpreter.
- [x] `sms_headless --diff` runs the interpreter alongside and names the
  first thing they disagree on (T-states, registers, RAM, cartridge, VDP,
  PSG); `--misses` writes a trace, `--coverage` the recompiled share.
  `-DROMS` builds `NAME` (window) and `NAME_headless`; the release kit
  checks a small ROM through it.
- [x] **Exit:** `tests/mastersystem/test_recomp.py`: a ROM of random
  instructions from every table but DD CB / FD CB, memory writes and
  conditional branches included, all recompiled, 600 frames in lockstep.
  Ten games, 3,000 frames of scripted play each: no difference, 68-99.9%
  of cycles recompiled (verification log).
- Speed: the recompiled programs run as fast as the interpreter, not
  faster. A Master System game's Z80 costs little next to drawing the
  picture (three quarters of the time); a faster renderer is where speed
  would come from.

## S4 · Game Gear
- [x] A mode of this machine (`Sms.vdp.gg`, chosen by `sms_gg_mode`: a
  header's region 5-7, else a `.gg` name; a Master System cartridge runs in
  Master System mode, as on the console): the 64-byte palette of 12-bit
  colours written in byte pairs, ports $00-$06 (Start on bit 7 of $00, the
  region, the link port read as unplugged), no Pause/NMI, 60 Hz only, the
  LCD's central 160x144 in the window and in `sms_headless --ppm`.
  `retrocast` detects it as its own system (`gg`, `gamegear.ini`);
  `-DROMS` recompiles it with `smsrecomp`.
- [x] **Exit:** `sms_tests` (palette, port $00, no NMI, mode choice); the
  boot test plays four Game Gear games; two recompiled games ran 3,000
  frames with `--diff` without a difference.
- Open: the stereo register ($06) is ignored, the sound is mono.

## Later
- Game Gear stereo (port $06).
- Not modelled: the BIOS, the SMS2 VDP's 224- and 240-line modes, the
  Korean and other mappers, the light phaser, paddles and other
  controllers, the FM sound unit, raster effects on the palette within a
  frame (colours are taken at the frame's end), the exact H counter.
