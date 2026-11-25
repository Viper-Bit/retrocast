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

  One headless program and one recompiler per system:

    System                     Headless            Recompiler
    NES, Famicom Disk System   nes_headless        nesrecomp
    Game Boy, Game Boy Color   gb_headless         gbrecomp
    Genesis / Mega Drive       genesis_headless    mdrecomp
    Atari 2600                 atari2600_headless  atari2600recomp
    Master System, Game Gear   sms_headless        smsrecomp
    CPS-1                      cps1_headless       cps1recomp

    *_headless      Plays a game without a window, for scripts and checks
                    (frames to run, pictures, sound, recordings, ...).
    *recomp         Turns a game into C source (the kit below runs it).
    Run one without arguments for its options.

  kit/            Everything needed to build a recompiled game into a
                  native program (see below), with SDL3 prebuilt.

On macOS, remove the download quarantine once before the first run:
  xattr -dr com.apple.quarantine retrocast-*


PLAYING

Keyboard: arrows, X = A, Z = B, (S = X, A = Y, Q = L, W = R for pads
that have them), Enter = Start, Right Shift = Select,
F5 = reset, F2 / F4 = save / load state, F6 = next disk side (FDS),
F10 = TV frame, F11 or Alt+Enter = fullscreen, Esc = quit.
Gamepads work too: players 1-4 in the order connected (3 and 4 in the
CPS-1 games that have them).
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
build/ffight "/path/to/ffight.zip".


CPS-1 (CAPCOM PLAY SYSTEM I)

A game is its MAME / FBNeo zip, matched by its chips' CRCs whatever it is
called; only the chips the board reads are needed. A chip the zip lacks is
looked for in the parent's zip, then in every zip in the same folder. The
Q-Sound games (Warriors of Fate, Cadillacs and Dinosaurs, The Punisher,
Slam Masters, Muscle Bomber) also need qsound.zip in that folder; they
keep their settings in game.eeprom next to the zip, as Pang! 3 does.
Which sets are supported: systems/cps1/docs/compatibility.md on the
project page.


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
