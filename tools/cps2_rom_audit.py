"""Report CPS-2 archive coverage, including missing chips in split or merged sets."""

import argparse
import csv
import re
import zipfile
from collections import Counter, defaultdict
from pathlib import Path, PurePosixPath

TABLE = Path(__file__).resolve().parents[1] / "systems/cps2/runtime/games.c"
DSP = (0x6000, "d6cf5ef5")


def read_table(path):
    """Read the initializer format emitted by cps2_table.py."""
    source = path.read_text(encoding="utf-8")
    arrays = {}
    for name, body in re.findall(
            r"(?:Cps2Load|Cps2Region|Cps2Game) (\w+)\[\] = \{\n(.*?)^\};",
            source, re.M | re.S):
        rows = []
        for line in body.splitlines():
            if not line.strip().startswith("{") or not line.endswith("},"):
                raise ValueError(f"{name}: invalid initializer")
            row, = csv.reader([line.strip()[1:-2]], skipinitialspace=True,
                              escapechar="\\", strict=True)
            rows.append(row)
        arrays[name] = rows
    games = {}
    for name, parent, _, _, _, _, title, regions, _ in arrays["cps2_games"]:
        chips = set()
        for tag, _, _, entries, _ in arrays[regions]:
            for chip, crc, length, _, _, _, wiring in (arrays[entries] if entries != "NULL" else []):
                if wiring != "CPS2_FILL":
                    key = None if wiring == "CPS2_UNDUMPED" else (int(length), crc[2:])
                    chips.add((tag, chip, key))
        games[name] = {"parent": None if parent == "NULL" else parent, "title": title, "chips": chips}
    return games


def stack(games, name):
    while name:
        yield name
        name = games.get(name, {}).get("parent")


def inventory(folder, expected, verify):
    """Find expected chips by (length, CRC), validating actual bytes on request."""
    locations = defaultdict(set)
    names, nested, errors = set(), defaultdict(set), []
    for path in sorted(folder.iterdir()):
        if not path.is_file() or path.suffix.lower() != ".zip":
            continue
        name = path.stem.lower()
        names.add(name)
        try:
            with zipfile.ZipFile(path) as archive:
                for member in archive.infolist():
                    if member.is_dir():
                        continue
                    parts = PurePosixPath(member.filename.replace("\\", "/")).parts
                    if len(parts) > 1:
                        nested[name].add(parts[0].lower())
                    key = member.file_size, f"{member.CRC:08x}"
                    if key not in expected:
                        continue
                    if verify:
                        try:
                            with archive.open(member) as blob:
                                while blob.read(1 << 20):
                                    pass
                        except (OSError, ValueError, RuntimeError, NotImplementedError, zipfile.BadZipFile) as exc:
                            errors.append(f"{path.name}:{member.filename}: {exc}")
                            continue
                    locations[key].add(name)
        except (OSError, zipfile.BadZipFile) as exc:
            errors.append(f"{path.name}: {exc}")
    return locations, names, nested, errors


def audit(games, folder, selected, verify=False):
    expected = {DSP}
    for name in selected:
        expected.update(key for _, _, key in games[name]["chips"] if key is not None)
    locations, names, nested, errors = inventory(folder, expected, verify)
    results = {}
    for name in selected:
        chain = set(stack(games, name))
        present = name in names or any(name in nested[parent] for parent in chain - {name})
        missing = []
        for region, chip, key in sorted(games[name]["chips"], key=str):
            label = f"{region}/{chip}"
            if key is None:
                missing.append(f"{label}: undumped in MAME")
                continue
            providers = locations[key]
            if not providers.intersection(chain):
                hint = f"; found in {', '.join(sorted(providers))}" if providers else ""
                missing.append(f"{label}: {key[0]} bytes, CRC {key[1]}{hint}")
        status = "complete" if not missing else "incomplete" if present else "absent"
        results[name] = status, missing
    return results, "qsound" in locations[DSP], errors


def main():
    cli = argparse.ArgumentParser(description=__doc__)
    cli.add_argument("folder", type=Path, help="directory containing MAME ZIPs")
    cli.add_argument("--set", action="append", dest="selected", help="report a specific set (repeatable)")
    cli.add_argument("--verify", action="store_true", help="read matching members and check CRC-32")
    args = cli.parse_args()
    if not args.folder.is_dir():
        cli.error(f"not a directory: {args.folder}")
    games = read_table(TABLE)
    selected = args.selected or list(games)
    if unknown := set(selected) - games.keys():
        cli.error(f"unknown set: {', '.join(sorted(unknown))}")
    results, dsp, errors = audit(games, args.folder, selected, args.verify)
    print(f"CPS-2 ({'verified bytes' if args.verify else 'ZIP metadata'}): {args.folder}")
    counts = Counter(status for status, _ in results.values())
    print(", ".join(f"{counts[status]} {status}" for status in ("complete", "incomplete", "absent")))
    print(f"QSound DSP: {'present' if dsp else 'missing qsound.zip / dl-1425.bin (24576 bytes, CRC d6cf5ef5)'}")
    for error in errors:
        print(f"Unreadable: {error}")
    for name, (status, missing) in results.items():
        if args.selected or status == "incomplete":
            print(f"{name}: {status} - {games[name]['title']}")
            for chip in missing:
                print(f"  {chip}")
    if absent := [name for name, (status, _) in results.items() if status == "absent"]:
        print("Absent sets: " + ", ".join(absent))
    return bool(errors or (args.selected and any(status != "complete" for status, _ in results.values())))


if __name__ == "__main__":
    raise SystemExit(main())
