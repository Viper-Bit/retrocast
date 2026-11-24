retrocast - static recompiler for NES, Famicom Disk System, Game Boy, Game Boy Color,
Genesis / Mega Drive, Atari 2600, Master System, Game Gear and Capcom Play
System I (CPS-1) arcade games
https://github.com/Viper-Bit/retrocast

No games are included. Use your own legally dumped games (.nes, .fds, .gb, .gbc,
.md, .a26, .sms, .gg; CPS-1: the game's .zip as MAME and FBNeo name it).


WHAT IS IN HERE

  retrocast       Plays a game of any of these systems in the built-in
                  interpreter. Usage: retrocast path/to/game
                  The system is read from the file itself (its header);
                  --system nes|gb|md|a26|sms|gg picks one when the file does not
                  say (Atari 2600 games have no header: name them .a26;
                  Sega 8-bit games without one: .sms or .gg).
  nes_headless    The same without a window, for scripts and checks
                  (--frames N, --record/--replay, --diff, --coverage, ...).
  nesrecomp       The recompiler: turns a ROM into C source.
  gb_headless     The same without a window, for test ROMs (--frames N,
                  --wav FILE to record the sound).
  gbrecomp        The Game Boy recompiler: turns a ROM into C source.
  genesis_headless  The same without a window (--frames N, --ppm FILE,
                  --wav FILE, --diff, --coverage).
  mdrecomp        The Genesis recompiler (68000 code into C source).
  atari2600_headless  Atari 2600 interpreter without a window.
  atari2600recomp Atari 2600 recompiler.
  sms_headless    Master System interpreter without a window (--frames N,
                  --ppm FILE, --wav FILE, --diff, --coverage).
  smsrecomp       The Master System recompiler (Z80 code into C source).
  cps1_headless   CPS-1 interpreter without a window (--frames N, --ppm FILE,
                  --wav FILE, --state-at N FILE, --load-state FILE, --diff,
                  --coverage).
  cps1recomp      The CPS-1 recompiler (68000 code into C source).
  kit/            Everything needed to build a recompiled game into a
                  native program (see below), with SDL3 prebuilt.

On macOS, remove the download quarantine once before the first run:
  xattr -dr com.apple.quarantine retrocast-*


PLAYING

Keyboard: arrows, X = A, Z = B, (S = X, A = Y, Q = L, W = R for pads
that have them), Enter = Start, Right Shift = Select,
F5 = reset, F2 / F4 = save / load state, F6 = next disk side (FDS),
F10 = TV frame, F11 or Alt+Enter = fullscreen, Esc = quit.
Gamepads work too (first = player 1, second = player 2).
Genesis pad: A, B, C = keyboard A, Z, X (gamepad West, South, East);
X, Y, Z = Q, S, W (left shoulder, North, right shoulder); Mode = Right Shift.
Master System pad: button 1 = Z, button 2 = X, Pause = Enter.
CPS-1: buttons 1, 2, 3 = Z, X, S (gamepad South, East, North); a coin =
Right Shift (Back); Start = Enter; Street Fighter II's kicks = A, Q, W;
Forgotten Worlds' dial = Q, W.
Settings are in nes.ini / gb.ini / genesis.ini / atari2600.ini /
mastersystem.ini / cps1.ini next to
retrocast, one per system, created on first run.


RECOMPILING A GAME (the kit)

A recompiled game is C code compiled on your machine; it then runs the game
natively. You need CMake 3.20 or newer and a C compiler:
  Windows: Visual Studio or its Build Tools ("Desktop development with C++")
           - the prebuilt SDL3 is built with MSVC, so MinGW will not link it
  Linux:   gcc or clang (e.g. sudo apt install build-essential cmake)
  macOS:   Xcode command line tools (xcode-select --install) and CMake

From the folder this file is in:

  cmake -S kit -B build -DROMS="/path/to/My Game.nes"
  cmake --build build --config Release

The program is build/my_game (build/my_game.exe on Windows), plus
build/my_game_headless. Several games: separate the paths with ";".
A relative path is relative to the folder you run cmake from. The system
is read from each file, as retrocast does.

Code the recompiler cannot find on its own runs in the interpreter. Two
things recompile more of it:
  - the build plays each game for a while first (scripted, about 6 seconds)
    and recompiles everything that ran; -DAUTO_HINTS=OFF skips this;
  - your own play (NES, Game Boy, Genesis, Master System and CPS-1 games): the game notes code it had to
    interpret in build/my_game.misses, and the next
    "cmake --build build --config Release" recompiles it.

DO NOT SHARE RECOMPILED PROGRAMS: they contain the game.

CPS-1: give the game's .zip to -DROMS. The program does not contain the zip
(the graphics are megabytes): start it with the zip, e.g.
build/ffight "/path/to/ffight.zip" (a clone's zip needs its parent's beside it).


NES AND FAMICOM DISK SYSTEM

Famicom Disk System: .fds images need the FDS BIOS (8 KB, not included):
put it next to retrocast as disksys.rom, or set fds_bios in nes.ini. Disk sides
are swapped by themselves when a game asks (F6 by hand). The kit
recompiles disk games like the others, given the BIOS:
  cmake -S kit -B build -DROMS="/path/to/Disk Game.fds" -DFDS_BIOS="/path/to/disksys.rom"
The program carries the BIOS too (and build/fds, which plays any .fds
image with only the BIOS recompiled). Do not share them either.

Supported mappers and more: systems/nes/README.md on the project page.


GAME BOY AND GAME BOY COLOR

Color games run as on a Game Boy Color, the others as on the original
Game Boy (palette = green or gray in gb.ini; model = cgb runs those in the
Color's compatibility mode, with its colours). Battery saves are kept in
game.gb.sav next to the game, with the cartridge clock where there is one.
More: systems/gb/README.md on the project page.


GENESIS / MEGA DRIVE

The region comes from the game's header (the Americas when the game
allows it, else Japan, else Europe at 50 Hz). pad = 6 (six buttons) or 3 in
genesis.ini: a few early games misread a six-button pad. Battery saves are
kept in game.md.sav next to the game. Code the Z80 runs is always
interpreted (the 68000 copies it into the Z80's RAM). More:
systems/genesis/README.md on the project page.


MASTER SYSTEM / MARK III

Sega's and Codemasters' cartridges. NTSC unless the file name says
(Europe), or region = pal in mastersystem.ini. Games with cartridge RAM
keep it in game.sms.sav next to the game. More: systems/mastersystem/README.md
on the project page.


GAME GEAR

Sega's and Codemasters' cartridges. The LCD shows the central 160x144 of
the 256x192 picture, in 12-bit colour (sound is mono). sms_headless and
smsrecomp run Game Gear games too. Games with cartridge RAM keep it in
game.gg.sav next to the game. More: systems/mastersystem/README.md on the
project page.


LICENSES

retrocast: GPL-3.0-or-later (LICENSE); the source is on the project page.
SDL3 (linked into the game programs and the kit): zlib license (LICENSE-SDL3.txt).
