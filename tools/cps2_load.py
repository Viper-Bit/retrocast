"""Assemble CPS-2 ROM regions in MAME layout, in bus byte order."""

import argparse
import hashlib
import json
import subprocess
import zipfile
from collections import defaultdict
from contextlib import ExitStack
from pathlib import Path

from cps2_audit import identity, stack
from cps2_gen_games import TABLE


# Source byte lanes to destination byte lanes, repeated every stride.
WIRING = {
    "ROM_LOAD": (1, (0,)),
    "ROM_LOAD16_BYTE": (2, (0,)),
    "ROM_LOAD16_WORD_SWAP": (2, (1, 0)),
    "ROM_LOAD64_BYTE": (8, (0,)),
    "ROM_LOAD64_WORD": (8, (0, 1)),
}


def place(region, data, entry):
    stride, lanes = WIRING[entry["load"]]
    cursor = 0
    for part in entry["parts"]:
        if "ignore" in part:
            cursor += part["ignore"]
            continue
        offset, size = part["offset"], part["size"]
        chunk = data[cursor:cursor + size]
        cursor += size
        if len(chunk) != size or size % len(lanes):
            raise ValueError(f"invalid load size for {entry['name']}")
        for source, lane in enumerate(lanes):
            start = offset + lane
            count = size // len(lanes)
            if count and (start < 0 or start + (count - 1) * stride >= len(region)):
                raise ValueError(f"load outside region for {entry['name']}")
            region[start:start + count * stride:stride] = chunk[source::len(lanes)]
    if cursor != len(data):
        raise ValueError(f"unconsumed bytes for {entry['name']}")


def load_regions(games, folder, name):
    """Read and verify a set's chips through its ZIP and parent ZIPs."""
    layouts = games[name]["regions"]
    paths = {path.stem.lower(): path for path in folder.iterdir()
             if path.is_file() and path.suffix.lower() == ".zip"}
    with ExitStack() as files:
        members = defaultdict(list)
        for provider in stack(games, name):
            if provider not in paths:
                continue
            archive = files.enter_context(zipfile.ZipFile(paths[provider]))
            for member in archive.infolist():
                if not member.is_dir():
                    members[member.file_size, f"{member.CRC:08x}"].append((archive, member))

        regions = {}
        for tag, layout in layouts.items():
            region = bytearray([layout["erase"]]) * layout["size"]
            for entry in layout["entries"]:
                if "fill" in entry:
                    offset, size = entry["offset"], entry["size"]
                    if offset < 0 or offset + size > len(region):
                        raise ValueError(f"{name}/{tag}: fill outside region")
                    region[offset:offset + size] = bytes([entry["fill"]]) * size
                    continue
                label = f"{name}/{tag}/{entry['name']}"
                if "crc" not in entry:
                    raise ValueError(f"{label}: undumped in MAME")
                size, crc, sha1 = identity(entry)
                for archive, member in members[size, crc]:
                    try:
                        data = archive.read(member)
                    except (OSError, RuntimeError, zipfile.BadZipFile):
                        continue
                    if hashlib.sha1(data).hexdigest() == sha1:
                        place(region, data, entry)
                        break
                else:
                    raise ValueError(f"{label}: no verified chip (CRC {crc}, SHA-1 {sha1})")
            regions[tag] = bytes(region)
    return regions


def main():
    cli = argparse.ArgumentParser(description=__doc__)
    cli.add_argument("folder", type=Path)
    cli.add_argument("set")
    cli.add_argument("--decrypt", type=Path, help="path to compiled CPS-2 opcode checker")
    args = cli.parse_args()
    games = json.loads(TABLE.read_text(encoding="utf-8"))["games"]
    if args.set not in games:
        cli.error(f"unknown set: {args.set}")
    try:
        regions = load_regions(games, args.folder, args.set)
        if args.decrypt:
            key = regions.get("key")
            if key is not None:
                regions["opcodes"] = subprocess.run(
                    [str(args.decrypt.resolve())], input=key[:20] + regions["maincpu"],
                    stdout=subprocess.PIPE, check=True).stdout
            else:
                regions["opcodes"] = regions["maincpu"]
    except (OSError, ValueError, zipfile.BadZipFile, subprocess.CalledProcessError) as exc:
        cli.error(str(exc))
    for tag, data in regions.items():
        print(f"{tag:12} {len(data):9} {hashlib.sha1(data).hexdigest()}")


if __name__ == "__main__":
    main()
