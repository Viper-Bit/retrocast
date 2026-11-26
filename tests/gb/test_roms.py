"""Game Boy test ROMs (blargg, mooneye) through gb_headless (systems/gb/tests/gb_headless.c).

The ROMs come from the c-sp/game-boy-test-roms collection, one pinned and
hash-checked zip (tests/fetch_test_roms.py fetch_gb_test_roms). Every ROM in
SUITES must pass, except the ones in OPEN, which must still fail (so a fix
shows up here and moves them out). The ROMs report on the serial port or in
cartridge RAM; no picture is needed.
"""
import os
import hashlib
import subprocess
import tempfile
import unittest

from tests.fetch_test_roms import fetch_gb_test_roms

from tests.games import ROOT  # noqa: E402
from tests.games import built
BUILD = os.environ.get("NES_BUILD", os.path.join(ROOT, "build"))
RUNNER = os.path.join(BUILD, "gb_headless" + (".exe" if os.name == "nt" else ""))

SUITES = [
    "blargg/cpu_instrs", "blargg/instr_timing", "blargg/mem_timing", "blargg/mem_timing-2",
    "blargg/halt_bug.gb", "blargg/dmg_sound/rom_singles", "blargg/cgb_sound/rom_singles", "mooneye-test-suite/acceptance", "mooneye-test-suite/emulator-only",
    # DMG games that check the boot state of a Color (compatibility mode)
    "mooneye-test-suite/misc/boot_div-A.gb", "mooneye-test-suite/misc/boot_div-cgb0.gb",
    "mooneye-test-suite/misc/boot_div-cgbABCDE.gb", "mooneye-test-suite/misc/boot_hwio-C.gb",
    "mooneye-test-suite/misc/boot_regs-A.gb", "mooneye-test-suite/misc/boot_regs-cgb.gb",
]
# ROMs that check the boot state of a model: run as that model (gb_headless --model); the rest as the header asks
MODELS = {
    "boot_div-S": "sgb", "boot_div2-S": "sgb2", "boot_hwio-S": "sgb", "boot_regs-sgb": "sgb", "boot_regs-sgb2": "sgb2",
    "boot_div-dmg0": "dmg0", "boot_hwio-dmg0": "dmg0", "boot_regs-dmg0": "dmg0", "boot_regs-mgb": "mgb",
    "boot_div-A": "agb", "boot_regs-A": "agb", "boot_div-cgb0": "cgb0", "boot_div-cgbABCDE": "cgb",
    "boot_hwio-C": "cgb", "boot_regs-cgb": "cgb",
}
OPEN = {  # none now; a ROM that fails goes here with the reason
}


def roms(base):
    out = []
    for s in SUITES:
        p = os.path.join(base, *s.split("/"))
        if p.endswith(".gb"):
            out.append(s)
            continue
        for d, _, files in os.walk(p):
            out += [os.path.relpath(os.path.join(d, f), base).replace(os.sep, "/") for f in files if f.endswith(".gb")]
    return sorted(out)


@built(RUNNER, "build gb_headless first")
class TestGbRoms(unittest.TestCase):
    def test_roms(self):
        base = fetch_gb_test_roms()
        found = roms(base)
        self.assertGreater(len(found), 100)
        for rom in found:
            with self.subTest(rom=rom):
                model = MODELS.get(os.path.basename(rom)[:-3])
                r = subprocess.run([RUNNER, os.path.join(base, rom), "--frames", "4000"] + (["--model", model] if model else []),
                                   capture_output=True, text=True, timeout=300)
                last = r.stdout.strip().splitlines()[-1] if r.stdout.strip() else r.stderr
                if rom in OPEN:
                    self.assertNotEqual(last, "result: passed", f"passes now: take it out of OPEN ({OPEN[rom]})")
                else:
                    self.assertEqual(last, "result: passed", r.stdout[-500:] + r.stderr)
        self.assertEqual(sorted(set(OPEN) - set(found)), [], "OPEN lists ROMs that are not in the suites")


@built(RUNNER, "build gb_headless first")
class TestSpeedSwitch(unittest.TestCase):
    """The CGB speed-switch ROMs show their result on the screen.
    AGE prints "TEST PASSED!"; gambatte's start_stop ROMs print the
    two-digit value in their name (compared with each other: same out, same picture)."""
    PASSED_TITLE = "de78e0120f9452b597645d384b355feb"  # md5 of the first 14 rows of AGE's "TEST PASSED!"

    def shot(self, rom, rows, *args):
        with tempfile.TemporaryDirectory() as tmp:
            out = os.path.join(tmp, "f.ppm")
            subprocess.run([RUNNER, rom, "--frames", "300", "--ppm", out, *args], capture_output=True)
            with open(out, "rb") as f:
                return f.read().split(b"\n", 3)[3][:160 * 3 * rows]

    def test_age_speed_switch(self):
        folder = os.path.join(fetch_gb_test_roms(), "age-test-roms", "speed-switch")
        for name, model in (
            ("div-cgbBCE", "cgb"),
            ("tima-cgbBC", "cgb"),
            ("tima-cgbE", "cgb-e"),
            ("ch2-lc-delay-cgbBCE", "cgb"),
            ("mode0-cgbBCE", "cgb"),
            ("stop-prefetch-cgbBCE", "cgb"),
        ):
            with self.subTest(name=name):
                rom = os.path.join(folder, f"spsw-{name}.gb")
                self.assertEqual(hashlib.md5(self.shot(rom, 14, "--model", model)).hexdigest(), self.PASSED_TITLE)

    def test_gambatte_start_stop(self):
        d = os.path.join(fetch_gb_test_roms(), "gambatte", "div")
        shots = {}
        for n in sorted(os.listdir(d)):
            if n.startswith("start_stop"):
                shots.setdefault(n.split("_out")[1][:2], []).append(self.shot(os.path.join(d, n), 8))
        self.assertEqual(sorted(shots), ["00", "01"])
        for out, group in shots.items():
            self.assertEqual(len(group), 2)
            self.assertEqual(group[0], group[1], f"out{out}")
        self.assertNotEqual(shots["00"][0], shots["01"][0])


if __name__ == "__main__":
    unittest.main()
