"""The 68000 recompiler (systems/genesis/recomp) against the interpreter, in
lockstep: genesis_headless --diff compares the CPUs, the Z80 and the RAMs
after every line and the whole machine after every frame.

CI: a ROM of random instructions made at build time
(systems/genesis/tests/random_rom.c, mdtest_random). Locally, the games recompiled
through -DROMS can be diffed the same way (NAME_headless ROM --diff).
"""
import os
import re
import subprocess
import unittest

from tests.games import ROOT, built

BUILD = os.environ.get("NES_BUILD", os.path.join(ROOT, "build"))
EXE = ".exe" if os.name == "nt" else ""
RUNNER = os.path.join(BUILD, "mdtest_random_headless" + EXE)
ROM = os.path.join(BUILD, "gen", "mdtest_random.md")


@built(RUNNER, "build the C runtime first")
class TestRecompiledRandom(unittest.TestCase):
    def test_lockstep(self):
        r = subprocess.run([RUNNER, ROM, "--frames", "120", "--diff", "--coverage"], capture_output=True, text=True)
        self.assertIn("diff: 120 frames, no difference", r.stdout, r.stdout + r.stderr)
        share = float(re.search(r"coverage: ([\d.]+)%", r.stdout).group(1))
        self.assertGreater(share, 90, r.stdout)

    def test_trace_run_succeeds_unbooted(self):  # the build's trace step: the file is the result, booted or not
        import tempfile
        headless = os.path.join(BUILD, "genesis_headless" + EXE)
        with tempfile.TemporaryDirectory() as d:
            out = os.path.join(d, "t.trace")
            r = subprocess.run([headless, ROM, "--frames", "1", "--misses", out], capture_output=True, text=True)
            self.assertIn("result: timeout", r.stdout)
            self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
            self.assertTrue(os.path.exists(out))


if __name__ == "__main__":
    unittest.main()
