# CPS-1 verification log

What was checked, how, and the result. Newest first. A claim without a
reproducible check is not "verified".

Checks of shared parts: [docs/verification-log.md](../../../docs/verification-log.md).

## 2026-11-25 · P8 · the odd ones
- **Table**: 210 sets, regenerated from MAME 0.289 by the scratchpad
  generator (the existing rows unchanged but for two new columns: a
  chip's part, MAME's bootleg kludge); 19 left out, each with its reason
  ([unsupported](unsupported.md)). `sf2m3` and `sf2ceupl` moved out:
  MAME runs them on their own memory maps; on ours they booted but read
  no inputs.
- **Self-checks** (`cps1_tests`): Pang! 3's decryption (the first half
  plain, $12AB to $1223 and $0000 to $00D8 by MAME's rules, worked by
  hand); its EEPROM read through $80017A; a chip in two halves and
  re-loaded and cut (ROM_CONTINUE, ROM_RELOAD, ROM_IGNORE); four byte
  chips by 4; no priority port (qad); sf2hack's DIP bytes, sf2thndr's
  mirror, each protection's values and 0 elsewhere, sf2rk's bit swap;
  the ROM space past the chips reading 0.
- **Boot** (3,000 frames of `--play`, a picture, by eye): megamana,
  pnickj, qad, qadjr; pang3b (the folder's `pang3.zip`); captcommb,
  3wondersb (now as 3wonders draws); sf2rb, sf2rb2, sf2m2, sf2m4, sf2m5,
  sf2m7, sf2yyc, sf2koryu; sf2accp2 (black before: it reads $180CA6,
  past its ROM, and needs 0 there, as MAME's zero-filled region gives)
  and sf2rb3 (black before the regenerated table) in play.
- **Not checked**: pictures against MAME's (no MAME here); black
  background tiles in sf2yyc, sf2accp2 and sf2rb3; Pang! 3's decrypted
  sets, rockmanj and qtono2j (their zips each lack a chip).

## 2026-11-24 · P7 · the Q-Sound games
- **References**: MAME 0.289's sources (tag `mame0289`): `kabuki.cpp` and
  `qsoundhle.cpp` copied into small harnesses built in the scratchpad (C, and
  C++20 for MAME's shift semantics), not committed. No MAME program was run.
- **The table, regenerated** from `cps1.cpp` / `cps1_v.cpp` by a rebuilt
  generator (scratchpad): byte for byte the old table but for the old
  generator's mistakes, now fixed: DIP defaults MAME sets through macros
  (`CPS1_DIFFICULTY_1` and others: 84 sets' defaults changed, such as
  difficulty "Normal" where the table had the easiest), five
  128 KB sound chips listed as 64 KB (`daimakair`, `dynwarjr`, `area88r`,
  `cawingjr`, `wofhfh`: those zips could not open before), four sets on
  MAME's 12 MHz machines run at 10 (`sf2m3`, `sf2ceupl`, `wofhfh`,
  `punisherbz`); `wonder3` and `sf2redp2` added. Then the 18 Q-Sound sets.
- **Kabuki**: the four keys' first 32 bytes against MAME's (`test_kabuki`);
  the first 32 KB of wof, dino, punisher and slammast's Z80 ROMs decoded
  by both: opcodes and data identical.
- **Q-Sound chip**: one voice with pan and echo on a made-up chip ROM, 512
  samples against MAME's code (`test_qsound_as_mame`; UBSan clean). Then
  Warriors of Fate, 3,000 frames of `--play`: its 114,222 chip writes
  logged by a temporary build, replayed through MAME's code with the real
  `dl-1425.bin` and the game's samples: 1,209,230 stereo samples, all
  identical to what our machine played.
- **The board** (`cps1_tests`): shared RAM on the 68000's low bytes, $FF
  above; 251 Z80 interrupts in 60 frames (250 Hz); bank 2 at $8000; a game
  refused without `qsound.zip`, the file named; an EEPROM byte written
  through $F1C006 kept by a save state. The 93C46: write and read back,
  write refused before EWEN, the 8-bit mode, erase.
- **Boot**: every Q-Sound zip of the folder whole by CRC, 3,000 frames of
  `--play`: wof (wofr1), wofa, wofj, wofu, dino, dinoj, punisher,
  punisheru, punisherj, slammast, slammastu, mbombrd: a picture, none
  halted; wof, dino, punisher, slammast and mbombrd in play by eye (four
  wrestlers in mbombrd). `dinou.zip`, `mbomberj.zip` and `mbombrdj.zip`
  each lack a chip.
- **Recompiled** (`-DROMS` with wof.zip and dino.zip): `--diff --coverage`,
  3,000 frames of `--play`: no difference; 97.26% and 97.67% of 68000
  clocks recompiled.
- **Not checked**: pictures against MAME's (no MAME program here); the
  window played by hand; the EEPROM file by hand.

## 2026-11-24 · P6 · the recompiler
- **Shared core**: `mdtest_random.c` generated before and after moving the
  recompiler to `cpu/m68k/m68k_recomp.c`: byte-identical; the Genesis
  lockstep test (`test_recomp`) passes.
- **Hook** (`cps1_tests`): a stand-in program runs only where its hash
  matches the main-CPU region (`test_recomp_gate`); a state saved by the
  interpreter, loaded with recompiled code, keeps it on
  (`test_recomp_state`). Exact-output tests (picture, sound, states)
  unchanged after `cps1_frame` became 262 `cps1_line` calls.
- **Lockstep** (`TestRecomp`, `-DROMS` with ffight.zip and sf2.zip,
  6,000-frame traces): 3,000 frames of `--play --diff`, the CPUs and RAMs
  equal after every line and the machine after every frame. ffight 5,829
  blocks, 96.15% of 68000 clocks recompiled; sf2 4,671 blocks, 96.42%.
- **Speed**: 6,000 frames of ffight headless: 16.05 s interpreted, 15.59 s
  recompiled. The 68000 is a small part of a CPS-1 frame here; the picture
  and the YM2151 take most of it.
- **Not checked**: the recompiled window played by hand.

## 2026-11-24 · P5 · the table from MAME's list, not the folder
- **The table**: every set of MAME 0.289's `cps1.cpp` on the plain boards
  (147), MAME's chips and CRCs, whatever the folder holds; 18 more are left
  out for a layout the loader cannot express (bootlegs' ROM_CONTINUE,
  ROM_LOAD32), listed in [unsupported](unsupported.md) with the
  Q-Sound, P8 and own-init sets.
- **Audit** (`tools/cps1_audit.py` on the folder, after taking 37 zips from
  CPS-new): 112 sets whole (some in a zip named otherwise), 8 with chips
  missing (mostly a zip holding another revision than its name:
  `forgottn.zip` is `forgottnua`, `willow.zip` is `willowu`), 27 without
  a zip.
- **Boot test** (`TestBoot`): every zip in the folder that opens as a
  table set, 3,000 frames of `--play`: a picture, none halted. A MAME split
  clone (`sf2ua.zip`, 17 of 23 chips from `sf2.zip`) runs
  (`test_split_clone`).

## 2026-11-24 · P5 · every plain-board set in the new folder
- **The folder**: rebuilt from a MAME split set (CPS-new) and the old
  folders, by CRC against MAME 0.289; the old contents kept in
  `D:\roms\_old-cps`. All 21 earlier games are recognised in the new zips;
  `cworld2j.zip` is the old one (the new lacks chip q5_35).
- **The table**: generated over the whole folder: 67 sets. A zip counts
  as a set when every chip is there by CRC (or as another dump under the
  chip's name, as cworld2j's `q535.bin`), with its parent's zip.
- **Revision E of Street Fighter II** (`sf2ue`): stopped on "CPS NG": its
  B-board maps the CPS-B at $8001C0 (MAME's `init_sf2ee`); now mapped
  there (`cps1_tests`: `test_cpsb_high`).
- **Boot test**: the 67 games, 3,000 frames of `--play`: each shows a
  picture and none halts.
- **Left out, with the reason**: 10 bootlegs needing MAME's `init_sf2hack`
  / `init_sf2rb` / `init_sf2rb2`; `captcomb`, `daimakr2`, `wofhfh` (a chip
  loaded in part); `sf2accp2`, `sf2rb3` (a black screen).

## 2026-11-24 · P5 · the plain-board games
- **Which set each zip is**: every zip's CRCs against MAME 0.289's sets
  (leaving out the PAL dumps, whose versions differ): 20 match a set
  whole; cworld2j differs in one chip (another dump; its own CRC is
  used); sf2hf holds 7 chips and takes 15 from sf2ce.zip; captcomu holds
  4 of 15, its parent captcomm.zip is not in the set.
- **The table**: generated from MAME's layouts, configs, mappers and DIP
  defaults with the zips' CRCs; the generator checks it read as many
  chips as each region lists (a first run had dropped 4 chips of willow
  and kod, behind block comments).
- **Self-checks** (`cps1_tests`): the 8-bit graphics layout, a mapper
  larger than the ROM, flip screen, a star at its place and colour, a
  picture turned for a vertical monitor, a 12 MHz frame (768 clocks a
  line, VBlank and the sound unchanged), the extra port as player 3 and
  as kicks, DIP defaults, the dial (+60 in 3 frames, back past zero),
  a clone loading from its parent's zip or naming it when it is missing,
  the zip matching two games taking the one with more of its own files.
- **Boot test** (`TestBoot`): 21 games, 1,800 frames of `--play`: each
  shows a picture of 8 or more colours (dynwar's frame is its text intro)
  and none halts.
- **Against MAME** (its snapshots at frame 1,800, a coin at 300 and Start
  at 1,300 as `--play`; the sets MAME refuses for missing PAL dumps run
  from copies with placeholder files): cawing, dynwar, forgottn, ghouls,
  knights, mercs, msword, nemo, strider, unsquad, varth and willow show the
  same picture; 1941, 3wonders, cworld2j, ffight, kod, mtwins and the
  Street Fighter IIs the same game at another moment (the CPUs' timing is
  not MAME's; the Street Fighter IIs: our `--play` presses button 1, which
  picks a fighter). Ghouls'n Ghosts' grey castle is MAME's too.
- **Not checked**: each game played by hand; three players; the dial by
  hand.

## 2026-11-24 · P4 · the window, detection, save states
- **Save states** (`cps1_tests`): a state with a sound command pending,
  loaded into a second machine, gives the same 20 frames and samples; a
  state of another game, cut short, with a wrong magic or damaged inside
  (a CRC-32 over the state) is refused and the machine is unchanged. `test_ffight_state`: a state at frame 1,400
  of Final Fight, loaded and run 100 frames, gives the same picture as
  1,500 frames straight.
- **Detection** (`test_detect`): the C detector and the CMake rule both
  say `cps1` for `ffight.zip` and refuse `sfa.zip` (CPS-2); a `games.c`
  with one file line laid out otherwise stops the CMake rule, naming the
  file, and so does a game listing no files (it would match any zip); a
  CRC written without its leading zero still matches. `ROMS` with a
  CPS-1 zip stops the configure with a message.
- **retrocast**: opens `ffight.zip` with the title "Final Fight (World)
  (ffight)"; a CPS-2 zip gives "not a game of a known system".
- **Graphics ROM mapper**: played by hand, Final Fight's Game Over screen
  showed stale scroll tiles over the background; MAME's shows black. With
  the S224B mapper (MAME's table) those codes are not drawn: the same
  screen (`cps1_headless --play`, frame 7,500) is clean. `cps1_tests`:
  the mapper's ranges, its shifts, and a scroll2 tile hidden by it.
- **By hand** (the user, `retrocast`): Final Fight played to Game Over
  in the window, pads, sound and picture as in MAME but for the mapper
  above.

## 2026-11-23 · P3 · the OKI and the mix against MAME
- **How**: MAME 0.289 (the official Windows build, SHA-256 checked) ran
  Final Fight for 82 s, a coin at frame 300 and Start at 1,300, logging
  every write to $F000-$F002 with its time (a Lua tap) and recording its
  sound (`-wavwrite`, 55,930 Hz). Our `s224b.1a` PAL dump differs from
  MAME's; MAME does not emulate it.
- **OKI, bit-exact**: MAME's 664 OKI commands played at their sample
  positions through our `oki6295.c` and through MAME's okim6295 logic
  (its source, rebuilt standalone): 633,538 samples (295,953 not
  silent), none different. Before: MAME's volume table (steps 5, 7, 8),
  a busy voice ignoring a start, a phrase needing its end after its
  start, and the exact sum (no division per voice) differed.
- **Mix**: MAME's recording fitted, in 50 ms windows of power, as the
  YM2151 (ymfm on MAME's own writes) plus the OKI (ours on MAME's
  commands): weights 0.703 and 0.1446 against ours, 0.700 and 0.150
  (MAME's routing: 0.35 a YM2151 side, 0.30 the OKI); 99.1% of the power
  explained. Before, the OKI was 4x too quiet.

## 2026-11-23 · P3 · the YM2151 against ymfm
- **How**: Final Fight's 173,836 YM2151 register writes (80 s of play,
  logged with their sample) played through our YM2151 and through ymfm
  (Aaron Giles, BSD-3, commit 81aec25; built outside the repository, not
  linked into retrocast), compared in 73 ms windows; then each part alone
  with register scripts.
- **Before**: the LFO's rate and depths, the noise, and summed carriers
  (a 14-bit clip, the YM2612's) differed, and a decay at its sustain
  level took one step too many (-0.75 dB on a held note).
- **After**: pitch within 1.2 cents on 195 notes (key code, fraction, DT2)
  and DT1 0-7 exact; attack within 3% and release exact at every rate;
  vibrato and tremolo depth and rate for each waveform; noise at every
  frequency (level and spectrum identical); the 8 algorithms with
  feedback 55-60 dB below the signal; the whole song at the same level
  (median 0.0 dB) and spectrum (correlation median 1.00, centroid ratio
  1.00). `cps1_tests` pins the sustain hold, the LFO counter and the
  carrier sum.
- **Genesis**: the envelope's new order (the state changes before the
  step, as in ymfm's YM2612) leaves `md_tests`' YM2612 hash unchanged.

## 2026-11-23 · P3 · sound
- **Genesis unchanged**: a YM2612 program (two channels, algorithms 4
  and 7, feedback, the LFO) hashes the same before and after moving the
  operator to `core/audio/fm.c` (`md_tests`); the Genesis tests pass.
- **Self-checks** (`cps1_tests`): KC $4A is 437-443 Hz and $5A 874-886 Hz
  (zero crossings over a second); timer A of 1000 raises its IRQ at the
  24th sample, timer B of 255 at the 16th, a flag reset clears it; a note
  is silent within 2,000 samples of key off; OKI nibbles 0, 8, 8, 0 give
  2, 0, -2, 0; status, stop, and phrases that end before they start or
  lie past the ROM; the 68000's command reaches the Z80 (the last of two
  writes), the bank, the YM2151's IRQ reaching RST $38, 938 samples a
  frame and a full buffer that stops filling.
- **Final Fight** (`--play`, Start on the title): the attract mode is
  silent (as the game sets it); from the start of play, music and effects
  at an RMS of 1,500-3,200 a second; the first stage drawn right
  (`--ppm`, by eye).
- **Not checked**: by ear against the arcade; the LFO and noise.

## 2026-11-23 · P1-P2 · zips, the machine and the picture
- **Zips** (`tests/test_zip.py`): stored and deflated entries Python
  writes read back with the same CRC and size; a cut zip and one with a
  flipped data byte exit with an error; all 32 zips of the set read as
  Python reads them.
- **Self-checks** (`cps1_tests`): load layouts (even/odd bytes, word
  swap, graphics interleave), extra zip entries ignored, a missing file
  named by CRC, a non-CPS-1 zip scoring 0; VBlank three times in three
  frames, inputs active low, the CPS-B ID and multiplier, unmapped reads;
  the palette's brightness rule, a tile of each scroll layer at its
  screen pixel, a flipped two-block sprite, a high-priority scroll2 pen
  over a sprite.
- **Final Fight** (`cps1_headless ffight.zip --frames 1200 --play --ppm`,
  checked by eye): the warning screen at frame 600, the title with
  "CREDIT =1" at 1,200, in the right colours. The CPS-B-04 palette
  control is at $2A (where the game writes $3F).
- **Detection**: `ffight.zip` is `cps1`; CPS-1 games not yet in the table
  and a CPS-2 zip are not.
- **Builds**: MinGW gcc with `-DWERROR=ON -DTESTS=ON`, every system; the
  Genesis tests pass on its 68000 copy.
- **Not checked**: sound, the window, other games.
