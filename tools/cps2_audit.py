"""Report CPS-2 archive coverage, including missing chips in split or merged sets."""

import argparse
import hashlib
import json
import zipfile
from collections import Counter, defaultdict
from pathlib import Path, PurePosixPath

from cps2_gen_games import TABLE


# MAME's qsound_hle DSP dump includes 0x4000 bytes ignored after the tables.
DSP = (0x6000, "d6cf5ef5", "555f50fe5cdf127619da7d854c03f4a244a0c501")


def chips(game):
    for region, layout in game["regions"].items():
        for entry in layout["entries"]:
            if "name" in entry:
                yield region, entry


def identity(chip):
    return chip["size"], chip["crc"], chip["sha1"]


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
                    hashes = expected.get(key)
                    if not hashes:
                        continue
                    if verify:
                        try:
                            with archive.open(member) as blob:
                                digest = hashlib.file_digest(blob, "sha1").hexdigest()
                            if digest not in hashes:
                                raise ValueError("SHA-1 mismatch")
                        except (OSError, ValueError, RuntimeError, NotImplementedError, zipfile.BadZipFile) as exc:
                            errors.append(f"{path.name}:{member.filename}: {exc}")
                            continue
                        locations[*key, digest].add(name)
                    else:
                        for digest in hashes:
                            locations[*key, digest].add(name)
        except (OSError, zipfile.BadZipFile) as exc:
            errors.append(f"{path.name}: {exc}")
    return locations, names, nested, errors


def audit(games, folder, selected, verify=False):
    expected = defaultdict(set)
    expected[DSP[:2]].add(DSP[2])
    for name in selected:
        for _, chip in chips(games[name]):
            if "crc" in chip:
                size, crc, sha1 = identity(chip)
                expected[size, crc].add(sha1)
    locations, names, nested, errors = inventory(folder, expected, verify)
    results = {}
    for name in selected:
        chain = set(stack(games, name))
        present = name in names or any(name in nested[parent] for parent in chain - {name})
        missing = []
        for region, chip in chips(games[name]):
            label = f"{region}/{chip['name']}"
            if "crc" not in chip:
                missing.append(f"{label}: undumped in MAME")
                continue
            providers = locations[identity(chip)]
            if not providers.intersection(chain):
                hint = f"; found in {', '.join(sorted(providers))}" if providers else ""
                missing.append(f"{label}: {chip['size']} bytes, CRC {chip['crc']}{hint}")
        status = "complete" if not missing else "incomplete" if present else "absent"
        results[name] = status, missing
    return results, "qsound" in locations[DSP], errors


def main():
    cli = argparse.ArgumentParser(description=__doc__)
    cli.add_argument("folder", type=Path, help="directory containing MAME ZIPs")
    cli.add_argument("--set", action="append", dest="selected", help="report a specific set (repeatable)")
    cli.add_argument("--verify", action="store_true", help="read matching members and check both CRC and SHA-1")
    args = cli.parse_args()
    if not args.folder.is_dir():
        cli.error(f"not a directory: {args.folder}")
    manifest = json.loads(TABLE.read_text(encoding="utf-8"))
    games = manifest["games"]
    selected = args.selected or list(games)
    if unknown := set(selected) - games.keys():
        cli.error(f"unknown set: {', '.join(sorted(unknown))}")
    results, dsp, errors = audit(games, args.folder, selected, args.verify)
    print(f"{manifest['mame']} ({'verified bytes' if args.verify else 'ZIP metadata'}): {args.folder}")
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
