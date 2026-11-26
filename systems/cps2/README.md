# CPS-2 ROM inventory

The [CPS-2 plan](https://github.com/Viper-Bit/retrocast/issues/67) starts with ROM
metadata. The checked-in [game table](games.json) comes from
[MAME mame0289's CPS-2 driver](https://github.com/mamedev/mame/blob/mame0289/src/mame/capcom/cps2.cpp).
It records parent sets, board variants, region sizes, load operations, CRCs,
and SHA-1 hashes. It contains metadata only.

## Audit a folder

```powershell
python tools/cps2_audit.py 'D:/roms/CAPCOM - Play System II'
python tools/cps2_audit.py 'D:/roms/CAPCOM - Play System II' --verify --set ssf2 --set ssf2u
```

The audit matches size and CRC in the set ZIP and its parent chain, so split,
merged, and non-merged MAME layouts work. It lists each missing chip by region,
name, byte count, and CRC. A copy in an unrelated ZIP is listed as a hint.
`--verify` reads matching ZIP members and checks their CRC and SHA-1. The
shared QSound DSP ZIP is reported separately from the game set counts.

A complete set has all the catalogued chip dumps in its archive or parent
chain. An incomplete set has an archive or a named folder inside its parent's
ZIP and some requirement is missing. The audit flags entries that MAME marks
undumped. These are file coverage results. Game execution and decryption will
be checked with the loader.

## Regenerate the table

```powershell
python tools/cps2_gen_games.py path/to/cps2.cpp mame0289
python -m unittest tests.test_cps2_tools
```

Pass the release tag matching the source when updating the table.
