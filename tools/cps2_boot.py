"""Run a bounded headless boot probe for every generated CPS-2 set."""

import argparse
import os
import subprocess
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

from cps2_rom_audit import TABLE, read_table


def probe(exe, folder, name, seconds):
    env = {key: value for key, value in os.environ.items()
           if key not in {"CPS2_PLAY", "CPS2_FRAME", "CPS2_PCM"}}
    env["CPS2_BOOT_PROBE"] = "1"
    try:
        result = subprocess.run(
            [str(exe), str(folder), name, str(seconds * 16_000_000)],
            capture_output=True, text=True, errors="replace", env=env, timeout=120,
        )
    except subprocess.TimeoutExpired:
        return "Timeout", "Exceeded the 120-second host limit"
    if not result.returncode:
        return "Boot progress", ""
    reason = result.stderr.strip().replace("\n", " ") or f"Runner exit {result.returncode}"
    return ("Undumped chip" if "undumped in MAME" in reason else "Failed"), reason


def main():
    cli = argparse.ArgumentParser(description=__doc__)
    cli.add_argument("runner", type=Path)
    cli.add_argument("folder", type=Path)
    cli.add_argument("--seconds", type=int, default=10)
    cli.add_argument("--jobs", type=int, default=4)
    args = cli.parse_args()
    if not args.runner.is_file() or not args.folder.is_dir():
        cli.error("expected a headless runner executable and ROM folder")
    if args.jobs < 1 or args.seconds < 1:
        cli.error("--jobs and --seconds must be positive")
    names = sorted(read_table(TABLE))
    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        results = list(pool.map(
            lambda name: probe(args.runner.resolve(), args.folder, name, args.seconds), names
        ))
    counts = Counter(status for status, _ in results)
    print("# CPS-2 compatibility\n")
    print(f"Test budget is {args.seconds} emulated seconds per set. Boot progress requires")
    print("two different non-uniform frames and a 68000 that remains running through")
    print("the budget. This probe does not verify title recognition or gameplay.\n")
    print(", ".join(f"{count} {status.lower()}" for status, count in sorted(counts.items()))
          + f" across {len(names)} sets.\n")
    print("| Set | Result | Detail |\n| --- | --- | --- |")
    for name, (status, detail) in zip(names, results):
        print(f"| `{name}` | {status} | {detail.replace('|', '&#124;')} |")


if __name__ == "__main__":
    main()
