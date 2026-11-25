"""Names CPS-1 zips by MAME 0.289's sets (games.c) from their contents, and says
what each set still needs. Zips are matched by CRC, whatever they are called.

    python tools/cps1_fix.py DIR [DIR...]             the plan only: each zip's set, what it lacks
    python tools/cps1_fix.py DIR [DIR...] --to OUT    copies them into OUT as SET.zip, then audits OUT
    ... --to OUT --whole                               each copy holds every chip its game needs, a
                                                       clone's parent chips too (MAME's non-merged sets)

A zip is a set's when it holds all the set's own chips (a clone's parent
chips may sit in the parent's zip). One holding several sets is named for the
one it holds most chips of. A chip a zip lacks is looked for by CRC in every zip
of the folders (versions of a game share most chips) and, with --to, added
to the copy. A set already whole in OUT is never overwritten; one lacking
there is replaced only by a copy that is whole.
"""
import os
import shutil
import zipfile
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cps1_audit import audit, crcs, table  # noqa: E402


def best_set(have, games, name=None):
    """(set id, missing [(name, crc)]) for the zip's CRCs, or None when it matches nothing."""
    best = None
    for gid, _, _, files, _ in games:
        own = [(n, c) for c, n, fp in files if not fp]
        got = sum(c in have for _, c in own)
        if not own or got * 2 < len(own):
            continue  # under half its own chips: not this set
        score = (got == len(own), gid == name, sum(c in have for c, _, _ in files), got)
        if not best or score > best[0]:
            best = (score, gid, [(n, c) for c, n, fp in files if not fp and c not in have])
    return best and best[1:]


def plan(dirs, games):
    """{set: (path, missing)}: per set, the source zip that fills most of it."""
    out = {}
    for d in dirs:
        for f in sorted(os.listdir(d)):
            if not f.lower().endswith(".zip"):
                continue
            path = os.path.join(d, f)
            have = crcs(path)
            m = best_set(have, games, f[:-4].lower()) if have else None
            if not m:
                print("  ?  %-28s not a set retrocast knows yet (or not CPS-1)" % f)
                continue
            gid, missing = m
            if gid not in out or len(missing) < len(out[gid][1]):
                out[gid] = (path, missing)
    return out


def index(dirs):
    """{crc: (zip path, member)} over every zip of the folders: where a chip can be taken from."""
    out = {}
    for d in dirs:
        for f in sorted(os.listdir(d)):
            if f.lower().endswith(".zip"):
                try:
                    with zipfile.ZipFile(os.path.join(d, f)) as z:
                        for i in z.infolist():
                            out.setdefault(i.CRC, (os.path.join(d, f), i.filename))
                except (OSError, zipfile.BadZipFile):
                    pass
    return out


def main(argv):
    to = argv[argv.index("--to") + 1] if "--to" in argv else None
    dirs = [a for i, a in enumerate(argv) if not a.startswith("--") and (i == 0 or argv[i - 1] != "--to")]
    if not dirs:
        print(__doc__)
        return 2
    if to and any(os.path.abspath(d) == os.path.abspath(to) for d in dirs):
        print("--to must be a folder other than the sources (renames there can swap names, ffightj1 <-> ffightj2)")
        return 2
    if to:
        os.makedirs(to, exist_ok=True)
    games = table()
    parent = {g: p for g, _, p, *_ in games}
    shared = {g: [(n, c) for c, n, fp in f if fp] for g, _, _, f, _ in games}  # the chips a clone takes from its parent
    whole = "--whole" in argv  # the chips a clone takes from its parent
    found = plan(dirs, games)
    where = index(dirs)
    now = audit(to) if to else {}
    for gid in sorted(found):
        path, missing = found[gid]
        if whole:  # the parent's chips into the copy as well
            have = crcs(path)
            missing = missing + [(n, c) for n, c in shared[gid] if c not in have]
        fill = [(n, c) + where[c] for n, c in missing if c in where]  # chips the zip lacks, found in another zip
        missing = [(n, c) for n, c in missing if c not in where]
        name = os.path.basename(path)
        need = "" if all(c in where for _, c in shared[gid]) else "  (needs %s.zip beside it)" % parent[gid]
        state = "whole" if not missing else "lacks %s" % ", ".join("%s (%08x)" % m for m in missing)
        arrow = name if name == gid + ".zip" else "%s -> %s.zip" % (name, gid)
        print("  %-38s %s%s" % (arrow, state, need))
        for n, c, src, member in fill if not whole else []:
            print("      %s (%08x) from %s" % (n, c, os.path.relpath(src, os.path.dirname(path)) if os.path.dirname(src) != os.path.dirname(path) else os.path.basename(src)))
        if not to:
            continue
        dest = os.path.join(to, gid + ".zip")
        here = now.get(gid, (None, None, "absent", []))[2]
        if os.path.abspath(path) == os.path.abspath(dest) or here == "whole":
            continue
        if whole:
            here = "absent" if os.path.exists(dest) and not (set(c for _, c in shared[gid]) <= crcs(dest)) else here
        if here == "lacking" and missing:
            continue  # not better than what is there
        if os.path.exists(dest):
            os.replace(dest, dest + ".old")  # kept, not lost
        shutil.copy2(path, dest)
        if fill:  # the chips it lacked, under MAME's names: the zip is whole on its own
            with zipfile.ZipFile(dest, "a", zipfile.ZIP_DEFLATED) as out:
                for n, c, src, member in fill:
                    with zipfile.ZipFile(src) as z:
                        out.writestr(n, z.read(member))
    if to:
        result = audit(to)
        for status in ("whole", "lacking", "absent"):
            sets = [g for g, v in result.items() if v[2] == status]
            print("%s in %s: %d%s" % (status, to, len(sets), "" if status == "whole" else ": " + " ".join(sets)))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
