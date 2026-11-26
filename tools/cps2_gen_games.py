"""Generate the CPS-2 ROM manifest from a pinned MAME cps2.cpp."""

import argparse
import csv
import json
import re
from pathlib import Path


TABLE = Path(__file__).resolve().parents[1] / "systems" / "cps2" / "games.json"
LOADS = {"ROM_LOAD", "ROM_LOAD16_BYTE", "ROM_LOAD16_WORD_SWAP",
         "ROM_LOAD64_BYTE", "ROM_LOAD64_WORD"}


def generate(source, tag):
    sizes = dict(re.findall(r"^#define\s+(CODE_SIZE|QSOUND_SIZE)\s+(0x[\dA-Fa-f]+)\b", source, re.M))

    def number(value):
        return int(sizes.get(value, value), 0)

    blocks = re.findall(r"^ROM_START\(\s*(\w+)\s*\)(.*?)^ROM_END\b", source, re.M | re.S)
    layouts = {}
    for name, block in blocks:
        if name in layouts:
            raise ValueError(f"{name}: duplicate ROM_START")
        regions = layouts[name] = {}
        block = re.sub(r"/\*.*?\*/|//[^\n]*", "", block, flags=re.S)
        chip = None
        for line in filter(None, map(str.strip, block.splitlines())):
            statement = re.fullmatch(r"(ROM_\w+)\s*\((.*)\)", line)
            if not statement:
                raise ValueError(f"{name}: unrecognized ROM statement: {line}")
            op, body = statement.groups()
            args = [arg.strip() for arg in body.split(",")]
            if op in ("ROM_REGION", "ROM_REGION16_BE"):
                length, region, flags = args
                if flags not in ("0", "ROMREGION_ERASEFF"):
                    raise ValueError(f"{name}: unsupported region flags {flags}")
                region = json.loads(region)
                if region in regions:
                    raise ValueError(f"{name}: duplicate region {region}")
                entries = []
                regions[region] = {"size": number(length), "erase": 255 if flags != "0" else 0,
                                   "big_endian_words": op == "ROM_REGION16_BE", "entries": entries}
                chip = None
            elif op in LOADS:
                filename, offset, length, hashes = args
                checksums = re.fullmatch(r"(BAD_DUMP\s+)?CRC\(([0-9A-Fa-f]{8})\)\s+SHA1\(([0-9A-Fa-f]{40})\)", hashes)
                if not checksums and hashes != "NO_DUMP":
                    raise ValueError(f"{name}: unsupported chip hashes {hashes}")
                chip = {"load": op, "name": json.loads(filename), "size": number(length),
                        "parts": [{"offset": number(offset), "size": number(length)}]}
                if checksums:
                    bad, crc, sha1 = checksums.groups()
                    chip.update(crc=crc.lower(), sha1=sha1.lower())
                    if bad:
                        chip["bad_dump"] = True
                entries.append(chip)
            elif op == "ROM_CONTINUE" and chip is not None:
                offset, length = map(number, args)
                chip["parts"].append({"offset": offset, "size": length})
                chip["size"] += length
            elif op == "ROM_IGNORE" and chip is not None:
                length, = map(number, args)
                chip["parts"].append({"ignore": length})
                chip["size"] += length
            elif op == "ROM_FILL":
                offset, length, value = map(number, args)
                entries.append({"fill": value, "offset": offset, "size": length})
                chip = None
            else:
                raise ValueError(f"{name}: unsupported ROM operation {op}")

    games = {}
    for row in re.findall(r"^GAME\(\s*(.*?)\)\s*(?://[^\n]*)?$", source, re.M):
        fields = [x.strip() for x in next(csv.reader([row], skipinitialspace=True, escapechar="\\"))]
        year, name, parent, machine, inputs, _, init, rotation, maker, title, flags = fields
        if name in games:
            raise ValueError(f"duplicate GAME {name}")
        games[name] = {"year": year, "parent": None if parent == "0" else parent, "machine": machine,
                       "inputs": inputs, "init": init, "rotation": rotation, "manufacturer": maker,
                       "title": title, "flags": flags, "regions": layouts[name]}
    if not games or games.keys() != layouts.keys():
        raise ValueError("GAME and ROM_START sets disagree")
    for name, game in games.items():
        parents = {name}
        while game["parent"]:
            parent = game["parent"]
            if parent in parents:
                raise ValueError(f"{name}: invalid parent chain at {parent}")
            parents.add(parent)
            if parent not in games:  # a parent may belong to another MAME driver
                break
            game = games[parent]
    return {"mame": tag, "games": games}


def main():
    cli = argparse.ArgumentParser(description=__doc__)
    cli.add_argument("source", type=Path, help="MAME src/mame/capcom/cps2.cpp")
    cli.add_argument("tag", help="MAME release tag for the source")
    cli.add_argument("--out", type=Path, default=TABLE)
    args = cli.parse_args()
    manifest = generate(args.source.read_text(encoding="utf-8"), args.tag)
    # Keep each set on one line so a regeneration only changes affected rows.
    rows = (f"    {json.dumps(name)}: {json.dumps(game, ensure_ascii=False, separators=(',', ':'))}"
            for name, game in manifest["games"].items())
    text = '{\n  "mame": ' + json.dumps(manifest["mame"]) + ',\n  "games": {\n' + ',\n'.join(rows) + '\n  }\n}\n'
    args.out.write_text(text, encoding="utf-8", newline="\n")
    print(f"{len(manifest['games'])} sets from {args.tag} -> {args.out}")


if __name__ == "__main__":
    main()
