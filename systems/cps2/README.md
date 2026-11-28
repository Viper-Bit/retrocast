# CPS-2 opcode decryption

The C decryptor takes program words and a verified 20-byte key and writes
a separate opcode buffer. The machine can continue to read the original
program words for data accesses.

Build the standalone checker with a C compiler:

```sh
cc -std=c11 -O2 systems/cps2/runtime/decrypt_main.c systems/cps2/runtime/cps2crypt.c -o cps2-decrypt
```

The checker reads the key followed by big-endian program bytes on standard
input and writes big-endian opcode bytes to standard output.

## ROM table and loader

Generate the compiled table from the pinned MAME source:

```sh
python tools/cps2_table.py path/to/cps2.cpp mame0289
```

The C loader uses the shared ZIP reader and places verified chips in bus byte
order. The standalone checker looks for the requested set ZIP and its parent
ZIPs, so a clone inside a merged parent archive works too.

```sh
cc -std=c11 -O2 -Icore -Isystems/cps2/runtime systems/cps2/tests/rom_check.c systems/cps2/runtime/load.c systems/cps2/runtime/games.c core/zip.c core/file.c -o cps2-rom-check
./cps2-rom-check "/path/to/CAPCOM - Play System II" ssf2u
```

Each output row gives the region tag, size in bytes, and CRC-32. The checker
reports missing, damaged, and undumped chips by set, region, and chip name.

## Audit a ROM folder

```powershell
python tools/cps2_rom_audit.py 'D:/roms/CAPCOM - Play System II' --verify
```

The audit reads the compiled table's C source, reports missing chips across
split and merged sets, and checks for the shared QSound DSP. Use repeatable
`--set` arguments to audit specific sets. By default it compares ZIP directory
entries. With `--verify` it also decompresses matching entries and checks CRC-32.

## Run the experimental headless machine

```powershell
cmake -S . -B build/cps2-headless -DFRONTEND=OFF -DCPS2_HEADLESS=ON '-DSYSTEMS='
cmake --build build/cps2-headless --target cps2_headless
$env:CPS2_FRAME = 'ssf2.ppm'
build/cps2-headless/cps2_headless.exe 'D:/roms/CAPCOM - Play System II' ssf2 528000000
Remove-Item Env:CPS2_FRAME
```

The final argument is the 68000 clock budget. Set `CPS2_PLAY=fight` to send
scripted coin, start, character select, and player inputs after that budget.
`CPS2_PLAY=idle` runs the same sequence with the last player input omitted.
The optional capture is a 384×224 PPM. The headless runner is opt-in.
Machine runs look for `qsound.zip` in the ROM folder. Set `CPS2_PCM` to
capture signed 16-bit little-endian stereo at the native QSound rate
(60 MHz / 2496, approximately 24,038 Hz).

## Compatibility

The [CPS-2 roadmap](https://github.com/Viper-Bit/retrocast/issues/67) tracks
the phases. The [verification log](docs/verification-log.md) records the
reference checks and the [compatibility list](docs/compatibility.md) covers
the full ROM catalog.

```powershell
python tools/cps2_boot.py build/cps2-headless/cps2_headless.exe 'D:/roms/CAPCOM - Play System II'
```

## Recompile and check lockstep

Generate native C for one set using its opcode image and a local execution
trace. Both files contain data derived from the ROM. Keep them and the
generated code in the build directory.

```powershell
cmake --build build/cps2-headless --target cps2_headless cps2_recompile
$env:CPS2_OPCODE_IMAGE = 'build/cps2-headless/ssf2.op'
$env:CPS2_EXECUTED_PCS = 'build/cps2-headless/ssf2.pcs'
$env:CPS2_PLAY = 'fight'
build/cps2-headless/cps2_headless.exe 'D:/roms/CAPCOM - Play System II' ssf2 432000000
Remove-Item Env:CPS2_OPCODE_IMAGE,Env:CPS2_EXECUTED_PCS
build/cps2-headless/cps2_recompile.exe build/cps2-headless/ssf2.op build/cps2-headless/ssf2.c build/cps2-headless/ssf2.pcs
cmake -S . -B build/cps2-headless -DCPS2_RECOMP_SOURCE=build/cps2-headless/ssf2.c
cmake --build build/cps2-headless --target cps2_headless
build/cps2-headless/cps2_headless.exe 'D:/roms/CAPCOM - Play System II' ssf2 432000000 --diff
Remove-Item Env:CPS2_PLAY
```

`--diff` compares the CPUs, video, audio device, and memory against an
interpreter-only instance every 16 scanlines and at the ends of the scripted
input intervals. It requires some native execution. Set
`-DCPS2_RECOMP_SOURCE=` to return to the interpreter-only build.
