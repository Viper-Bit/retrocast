# CPS-1 verification log

What was checked, how, and the result. Newest first. A claim without a
reproducible check is not "verified".

Checks of shared parts: [docs/verification-log.md](../../../docs/verification-log.md).

## 2026-11-24 · P5 · every plain-board set in the new folder
- **The folder**: rebuilt from a MAME split set (CPS-new) and the old
  folders, by CRC against MAME 0.289; the old contents kept in
  `D:oms\_old-cps`. All 21 earlier games are recognised in the new zips;
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
