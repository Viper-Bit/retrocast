"""Print set and region differences between two generated CPS-2 C tables."""

import argparse
from pathlib import Path

from cps2_rom_audit import read_table


def diff(old, new):
    for name in sorted(old.keys() | new.keys()):
        if name not in old:
            yield f"- **{name}** added ({new[name]['title']})"
        elif name not in new:
            yield f"- **{name}** removed ({old[name]['title']})"
        else:
            before, after = old[name], new[name]
            for key in ("parent", "title", "machine", "inputs", "init", "rotation"):
                if before[key] != after[key]:
                    yield f"- **{name}** {key}: {before[key]} → {after[key]}"
            left, right = before["layouts"], after["layouts"]
            for tag in sorted(left.keys() | right.keys()):
                if tag not in left:
                    yield f"- **{name} / {tag}** region added"
                elif tag not in right:
                    yield f"- **{name} / {tag}** region removed"
                elif left[tag] != right[tag]:
                    gone = before["chips"] - after["chips"]
                    added = after["chips"] - before["chips"]
                    details = []
                    for action, chips in (("removed", gone), ("added", added)):
                        for region, chip, identity in sorted(chips, key=str):
                            if tag == region:
                                detail = f"CRC {identity[1]}" if identity else "undumped"
                                details.append(f"{action} {chip} ({detail})")
                    yield f"- **{name} / {tag}** " + (", ".join(details) or "ROM layout changed")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("old", type=Path)
    parser.add_argument("new", type=Path)
    args = parser.parse_args()
    print("\n".join(diff(read_table(args.old), read_table(args.new))) or "no change")
