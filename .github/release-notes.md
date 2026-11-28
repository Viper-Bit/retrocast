retrocast is a static recompiler for retro consoles and arcade boards: it translates a game's machine code into C and builds it into a native program, with a small runtime per system and an SDL3 window, sound and gamepads. Recompiled games are checked cycle by cycle against a built-in reference interpreter.

Systems: NES and Famicom Disk System (6502), Game Boy and Game Boy Color (SM83), Genesis / Mega Drive (68000 and Z80), Atari 2600 (6507), Master System / Mark III and Game Gear (Z80), Capcom Play System I (68000 and Z80), and Capcom Play System II (68000 and Z80).

No games are included: bring your own legally dumped ROMs and disk images (disk games also need the FDS BIOS; Game Boy games need no BIOS). CPS-1 games are MAME / FBNeo zips, matched by their chips' CRCs whatever their names; the Q-Sound games also need `qsound.zip`.

## Downloads

Windows (x64, arm64), Linux (x64, arm64; glibc 2.35+), macOS (Apple Silicon). Each archive has:

- `retrocast` runs the systems with SDL support. It identifies the system from the file, with `--system` available for manual selection.
- one headless program (`*_headless`: the game without a window, for scripts and checks) and one recompiler (`*recomp`: the game to C) per system; each prints its options when run without arguments:

| System | Headless | Recompiler |
|---|---|---|
| NES, Famicom Disk System | `nes_headless` | `nesrecomp` |
| Game Boy, Game Boy Color | `gb_headless` | `gbrecomp` |
| Genesis / Mega Drive | `genesis_headless` | `mdrecomp` |
| Atari 2600 | `atari2600_headless` | `atari2600recomp` |
| Master System, Game Gear | `sms_headless` | `smsrecomp` |
| CPS-1 | `cps1_headless` | `cps1recomp` |
| CPS-2 | `cps2_headless` | `cps2_recompile` |

- `kit/`: recompiles your own ROMs into native programs with only CMake and a C compiler installed (SDL3 comes prebuilt)

`README.txt` in the archive explains how to play and how to recompile. macOS builds are unsigned: run `xattr -dr com.apple.quarantine retrocast-*` once after unpacking.

**Do not share recompiled programs: they contain the game.**

Supported cartridges and known limitations: [NES](https://github.com/Viper-Bit/retrocast/blob/main/systems/nes/README.md#mappers), [Game Boy](https://github.com/Viper-Bit/retrocast/blob/main/systems/gb/README.md#not-yet), [Genesis](https://github.com/Viper-Bit/retrocast/blob/main/systems/genesis/README.md#status), [Atari 2600](https://github.com/Viper-Bit/retrocast/blob/main/systems/atari2600/README.md#status), [Master System and Game Gear](https://github.com/Viper-Bit/retrocast/blob/main/systems/mastersystem/README.md#status), [CPS-1](https://github.com/Viper-Bit/retrocast/blob/main/systems/cps1/README.md#status).
