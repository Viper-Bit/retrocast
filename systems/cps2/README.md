# Capcom Play System II (CPS-2)

The CPS-2 arcade board in [retrocast](../../README.md). Run a game from its
MAME ZIPs with `cps2_headless ROM_FOLDER SET_ID CYCLES`. The release ships
the headless runner and recompiler.

## Status

- **Games**: 324 sets from MAME 0.289. The [compatibility list](docs/compatibility.md)
  records observable boot progress for 323 sets. `gigaman2` stops at ROM
  loading because its MCU is undumped. Title and gameplay checks cover the
  representative parent and clone in the [verification log](docs/verification-log.md).
- **Zips**: the shared ZIP reader loads chips by size and CRC and applies
  the compiled table's wiring, continuations, and fills.
- **CPUs**: copies of the shared 68000 and Z80 use the `cps2_` prefix.
  The 68000 reads original ROM bytes for data and the separate decrypted
  stream for opcode fetches.
- **Sound**: the 8 MHz Z80 uses shared RAM, banked ROM, and a 250 Hz
  interrupt. QSound produces stereo at about 24,038 Hz. Its DSP tables
  come from `dl-1425.bin` in `qsound.zip`.
- **Picture**: 384×224 output, three scroll layers, a latched palette,
  banked object RAM, sprite priorities, and raster interrupts.
- **Recompiled**: the shared 68000 recompiler emits C from the opcode
  image. An execution trace improves coverage. The interpreter runs code
  outside the generated blocks. Lockstep passed for `ssf2`, `ssf2u`, and
  the Phoenix set `ssf2ud`.
- **Current scope**: headless execution and scripted input. The SDL
  frontend, automatic ZIP detection, and saved states are open.

## Loading a game

1. Give the runner a ROM directory and MAME set ID, such as `ssf2u`.
2. The loader checks the named set ZIP, then its parent ZIPs. A clone can
   use a split archive or live entirely inside a merged parent archive.
3. Each chip is matched by size and CRC, regardless of its member name.
   Missing or undumped chips are reported with their set and region.
4. Put `qsound.zip` in the same directory to run the machine.

Use `python tools/cps2_rom_audit.py '<ROM-FOLDER>' --verify` to audit a folder,
or add repeatable `--set` arguments for specific sets. The tool reads the
generated `runtime/games.c` table. Regenerate it with
`python tools/cps2_table.py path/to/cps2.cpp mame0289`. The
[monthly MAME check](../../.github/workflows/mame-cps2.yml) reports set
and region changes against the latest release.

## Controls and settings

Set `CPS2_PLAY=fight` to send coin, start, character selection, and
in-round input after the initial clock budget. `CPS2_PLAY=idle` omits
the last player input. The headless runner starts with a fresh EEPROM.

## Running

```powershell
cmake -S . -B build/cps2-headless -DFRONTEND=OFF -DSYSTEMS=cps2
cmake --build build/cps2-headless --target cps2_headless cps2_recompile
build/cps2-headless/cps2_headless.exe '<ROM-FOLDER>' ssf2 528000000
```

The last argument is the 68000 clock budget. Omit it to print loaded
region sizes and CRCs. Set `CPS2_FRAME` to a PPM path for the final
frame, or `CPS2_PCM` to a path for raw signed 16-bit little-endian stereo.
Run the catalog sweep with `python tools/cps2_boot.py RUNNER '<ROM-FOLDER>'`.

### Recompiling and lockstep

```powershell
$env:CPS2_OPCODE_IMAGE = 'build/cps2-headless/ssf2.op'
$env:CPS2_EXECUTED_PCS = 'build/cps2-headless/ssf2.pcs'
$env:CPS2_PLAY = 'fight'
build/cps2-headless/cps2_headless.exe '<ROM-FOLDER>' ssf2 432000000
Remove-Item Env:CPS2_OPCODE_IMAGE,Env:CPS2_EXECUTED_PCS
build/cps2-headless/cps2_recompile.exe build/cps2-headless/ssf2.op build/cps2-headless/ssf2.c build/cps2-headless/ssf2.pcs
cmake -S . -B build/cps2-headless -DCPS2_RECOMP_SOURCE=build/cps2-headless/ssf2.c
cmake --build build/cps2-headless --target cps2_headless
build/cps2-headless/cps2_headless.exe '<ROM-FOLDER>' ssf2 432000000 --diff
Remove-Item Env:CPS2_PLAY
```

Keep ROM-derived images, traces, and generated code local. `--diff`
compares the machine against an interpreter-only instance every 16
scanlines and at scripted input boundaries. Use `-DCPS2_RECOMP_SOURCE=`
to restore the interpreter-only build.

## Docs

- [Roadmap](https://github.com/Viper-Bit/retrocast/issues/67)
- [Compatibility list](docs/compatibility.md)
- [Verification log](docs/verification-log.md)
