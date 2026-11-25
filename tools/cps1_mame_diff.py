"""What changed between two CPS-1 game tables (games.c as
tools/cps1_gen_games.py writes it): sets added, removed, retitled, chips
added, removed or with another CRC. Markdown lines, for the scheduled MAME
check's issue (.github/workflows/mame-cps1.yml).

    python tools/cps1_mame_diff.py OLD_GAMES_C NEW_GAMES_C
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cps1_audit import table  # noqa: E402


def diff(old_path, new_path):
    old = {g[0]: g for g in table(old_path)}
    new = {g[0]: g for g in table(new_path)}
    out = ["- **%s** (%s): added" % (g, new[g][1]) for g in new if g not in old]
    out += ["- **%s** (%s): removed" % (g, old[g][1]) for g in old if g not in new]
    for g in (g for g in new if g in old):
        (_, t0, p0, f0, _), (_, t1, p1, f1, _) = old[g], new[g]
        notes = []
        if t0 != t1:
            notes.append("title %s -> %s" % (t0, t1))
        if p0 != p1:
            notes.append("parent %s -> %s" % (p0, p1))
        a = {n: c for c, n, _ in f0}
        b = {n: c for c, n, _ in f1}
        notes += ["%s %08x -> %08x" % (n, a[n], b[n]) for n in b if n in a and a[n] != b[n]]
        notes += ["%s (%08x) added" % (n, b[n]) for n in b if n not in a]
        notes += ["%s (%08x) removed" % (n, a[n]) for n in a if n not in b]
        if notes:
            out.append("- **%s**: %s" % (g, "; ".join(notes)))
    return out


if __name__ == "__main__":
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    print("\n".join(diff(sys.argv[1], sys.argv[2])) or "no change")
