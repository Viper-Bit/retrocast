"""CPS-1: the runtime self-checks, and Final Fight reaching its title.

Needs the C build (-DTESTS=ON). The game test needs the CPS-1 set (.zip
files) in roms/CAPCOM - Play System I or $CPS1_ROMS_DIR; it skips without
it. Final Fight plays 1,200 frames, a coin tapped, and must end on its
title, a picture of many colours; with Start pressed on the title, the
last 10 seconds of 2,400 frames of play must not be silent.
"""
import os
import re
import subprocess
import tempfile
import array
import math
import unittest
import wave
import zipfile

from tests.games import ROOT, built

BUILD = os.environ.get("NES_BUILD", os.path.join(ROOT, "build"))
EXE = ".exe" if os.name == "nt" else ""
TESTS = os.path.join(BUILD, "cps1_tests" + EXE)
RUNNER = os.path.join(BUILD, "cps1_headless" + EXE)
SET = os.environ.get("CPS1_ROMS_DIR", os.path.join(ROOT, "roms", "CAPCOM - Play System I"))


@built(TESTS, "build the CPS-1 self-checks first")
class TestRuntime(unittest.TestCase):
    def test_self_checks(self):
        r = subprocess.run([TESTS], capture_output=True, text=True, timeout=60)
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)


@built(RUNNER, "build the CPS-1 headless program first")
class TestHeadless(unittest.TestCase):
    def test_unknown_zip(self):
        with tempfile.TemporaryDirectory() as d:
            path = os.path.join(d, "x.zip")
            with zipfile.ZipFile(path, "w") as z:
                z.writestr("x.bin", os.urandom(4096))
            r = subprocess.run([RUNNER, path, "--frames", "1"], capture_output=True, text=True, timeout=60)
            self.assertEqual(r.returncode, 1)
            self.assertIn("not a CPS-1 game", r.stdout + r.stderr)

    @unittest.skipUnless(os.path.exists(os.path.join(SET, "ffight.zip")), "no ffight.zip in " + SET)
    def test_ffight_title(self):
        with tempfile.TemporaryDirectory() as d:
            ppm = os.path.join(d, "out.ppm")
            r = subprocess.run([RUNNER, os.path.join(SET, "ffight.zip"), "--frames", "1200", "--play", "--ppm", ppm],
                               capture_output=True, text=True, timeout=300)
            self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
            m = re.search(r"colours=(\d+)", r.stdout)
            self.assertIsNotNone(m, r.stdout)
            self.assertGreaterEqual(int(m.group(1)), 16, r.stdout)
            self.assertTrue(os.path.getsize(ppm) > 384 * 224 * 3)

    @unittest.skipUnless(os.path.exists(os.path.join(SET, "ffight.zip")), "no ffight.zip in " + SET)
    def test_ffight_sound(self):
        with tempfile.TemporaryDirectory() as d:
            out = os.path.join(d, "out.wav")
            r = subprocess.run([RUNNER, os.path.join(SET, "ffight.zip"), "--frames", "2400", "--play", "--wav", out],
                               capture_output=True, text=True, timeout=300)
            self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
            with wave.open(out) as w:
                self.assertEqual((w.getnchannels(), w.getsampwidth(), w.getframerate()), (1, 2, 55930))
                rate = w.getframerate()
                data = array.array("h", w.readframes(w.getnframes()))
            last = data[-10 * rate:]
            rms = math.sqrt(sum(x * x for x in last) / len(last))
            self.assertGreater(rms, 300)
            self.assertGreater(len(set(last)), 100)

    @unittest.skipUnless(os.path.exists(os.path.join(SET, "ffight.zip")), "no ffight.zip in " + SET)
    def test_ffight_state(self):  # a state at 1,400, loaded and run 100 frames: the same picture as 1,500 straight
        game = os.path.join(SET, "ffight.zip")
        with tempfile.TemporaryDirectory() as d:
            st, a, b = (os.path.join(d, n) for n in ("s.state", "a.ppm", "b.ppm"))
            r = subprocess.run([RUNNER, game, "--frames", "1500", "--play", "--state-at", "1400", st, "--ppm", a],
                               capture_output=True, text=True, timeout=300)
            self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
            r = subprocess.run([RUNNER, game, "--frames", "100", "--play", "--load-state", st, "--ppm", b],
                               capture_output=True, text=True, timeout=300)
            self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
            self.assertEqual(open(a, "rb").read(), open(b, "rb").read())

    @unittest.skipUnless(all(os.path.exists(os.path.join(SET, z)) for z in ("sf2hf.zip", "sf2ce.zip")), "no sf2hf.zip and sf2ce.zip in " + SET)
    def test_sf2hf(self):  # a clone zip: the rest of its chips from sf2ce.zip beside it
        r = subprocess.run([RUNNER, os.path.join(SET, "sf2hf.zip"), "--frames", "1500"], capture_output=True, text=True, timeout=300)
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        self.assertGreaterEqual(int(re.search(r"colours=(\d+)", r.stdout).group(1)), 16, r.stdout)


# every game in the table (systems/cps1/runtime/games.c)
GAMES = tuple(re.findall(r'^    \{"(\w+)"', open(os.path.join(ROOT, "systems", "cps1", "runtime", "games.c"), encoding="utf-8").read(), re.M))


@built(RUNNER, "build the CPS-1 headless program first")
@unittest.skipUnless(os.path.isdir(SET), "no CPS-1 set in " + SET)
class TestBoot(unittest.TestCase):
    def test_games_show_a_picture(self):  # each game in the table, 3,000 frames of --play: a picture, not halted
        for game in GAMES:
            path = os.path.join(SET, game + ".zip")
            if not os.path.exists(path):
                continue
            with self.subTest(game=game):
                r = subprocess.run([RUNNER, path, "--frames", "3000", "--play"], capture_output=True, text=True, timeout=300)
                self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
                self.assertNotIn("halted", r.stdout)
                self.assertGreaterEqual(int(re.search(r"colours=(\d+)", r.stdout).group(1)), 8, r.stdout)  # dynwar: its text intro


if __name__ == "__main__":
    unittest.main()
