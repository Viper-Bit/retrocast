"""Which of the CPS-1 sets retrocast knows (systems/cps1/runtime/games.c, MAME
0.289's) a folder of zips holds whole, which lack chips and which are absent.
A set's own chips are found by CRC in its zip; the rest in any zip of the
folder (a split clone's parent's, or another version sharing them), as the loader does;
a Q-Sound set also needs qsound.zip (the chip's ROM, dl-1425.bin) in the folder.

    python tools/cps1_audit.py [FOLDER]        the lists, on the console
"""
import os
import re
import sys
import zipfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GAMES_C = os.path.join(ROOT, "systems", "cps1", "runtime", "games.c")


def table(path=GAMES_C):
    """[(id, title, parent, [(crc, name, from_parent)], qsound)] in games.c's order."""
    src = open(path, encoding="utf-8").read()
    out = []
    for m in re.finditer(r'^    \{"(\w+)", "((?:[^"\\]|\\.)*)",(.*?)^    \}, ([^\n]*)', src, re.M | re.S):
        files = [(int(c, 16), n, fp == "1") for c, fp, n in
                 re.findall(r"\{0x([0-9a-f]+), \d+ \* K, \w+, \w+, 0x[0-9A-F]+, (?:0|0x[0-9A-F]+), (?:0|0x[0-9A-F]+), ([01])\},  /\* (.+?) \*/", m.group(3))]
        parent = re.search(r'"(\w+)"', m.group(4))
        out.append((m.group(1), m.group(2).replace('\\"', '"'), parent.group(1) if parent else None, files,
                    m.group(3).lstrip().startswith("CPS1_QSOUND")))
    assert out and all(f for _, _, _, f, _ in out), "games.c's layout changed"
    return out


def crcs(path):
    try:
        with zipfile.ZipFile(path) as z:
            return {i.CRC for i in z.infolist()}
    except (OSError, zipfile.BadZipFile):
        return None


def audit(folder):
    """{id: (title, parent, status, notes)}; status: whole (notes: the zip, when it is
    named otherwise), lacking (notes: the missing chips), absent."""
    zips = {f[:-4]: crcs(os.path.join(folder, f)) for f in os.listdir(folder) if f.endswith(".zip")} if os.path.isdir(folder) else {}
    zips = {k: v for k, v in zips.items() if v is not None}
    games = table()
    every = set().union(*zips.values())  # the loader takes a chip by CRC from any zip of the folder

    def holds(z, files, parent):  # the zip has the set's own chips, the rest anywhere in the folder
        have = every
        return all(c in zips[z] for c, _, fp in files if not fp) and all(c in have for c, _, _ in files)

    sets_in = {z: [g for g, _, p, f, _ in games if holds(z, f, p)] for z in zips}
    dsp = 0xD6CF5EF5 in zips.get("qsound", set())
    out = {}
    for gid, title, parent, files, qsound in games:
        at = [z for z in ([gid] if gid in zips else []) + sorted(zips) if gid in sets_in[z]]
        if at and qsound and not dsp:
            out[gid] = (title, parent, "lacking", ["needs qsound.zip (dl-1425.bin, d6cf5ef5) in the folder"])
        elif at:
            out[gid] = (title, parent, "whole", [] if at[0] == gid else ["as %s.zip" % at[0]])
        elif gid in zips:
            have = every
            other = sets_in[gid]
            out[gid] = (title, parent, "lacking", (["%s.zip holds %s" % (gid, ", ".join(other))] if other else []) +
                        ["missing %s (%08x)" % (n, c) for c, n, _ in files if c not in have])
        else:
            out[gid] = (title, parent, "absent", [])
    return out


def main(argv):
    folder = next((a for a in argv if not a.startswith("--")), os.path.join(ROOT, "roms", "CAPCOM - Play System I"))
    result = audit(folder)
    for status in ("lacking", "absent", "whole"):
        sets = [(g, v) for g, v in result.items() if v[2] == status]
        print("%s: %d" % (status, len(sets)))
        for g, (title, parent, _, notes) in sets:
            print("  %-10s %s%s" % (g, title, " (parent %s)" % parent if parent else ""))
            for note in notes:
                print("     ", note)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
