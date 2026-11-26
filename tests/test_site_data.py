import os, sys, unittest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "tools"))
import site_data


def ppm(colours, w=16, h=16):
    px = b"".join(bytes((i % colours * 5, 0, 0)) for i in range(w * h))
    return b"P6\n%d %d\n255\n" % (w, h) + px


class Classify(unittest.TestCase):
    def test_classify(self):
        c = site_data.classify
        self.assertEqual(c(0, "game=ffight frames=3000 colours=190\n", ppm(50)), "ok")
        self.assertEqual(c(0, "game=ffight frames=3000 colours=190 halted\n", ppm(50)), "no")
        self.assertEqual(c(0, "result: locked\n", ppm(50)), "no")
        self.assertEqual(c(0, "frames=300 cycles=1 pc=F008 bank=0 jammed=1\n", ppm(50)), "no")
        self.assertEqual(c(0, "frames=300 jammed=0\n", ppm(50)), "ok")
        self.assertEqual(c(0, "", ppm(1)), "partial")
        self.assertEqual(c(1, "", ppm(50)), "no")
        self.assertEqual(c(1, "result: timeout\n", ppm(50)), "ok")  # gb_headless: a game, not a test ROM
        self.assertEqual(c(0, "", None), "no")


class Group(unittest.TestCase):
    def test_group(self):
        g = site_data.group(["Tetris (World) (Rev 1)", "Tetris (Japan)", "Tetris (World)", "Columns (USA, Europe)"])
        self.assertEqual(sorted(g), ["Columns", "Tetris"])
        self.assertEqual(g["Tetris"][:2], ["Tetris (World)", "Tetris (World) (Rev 1)"])
        self.assertEqual(g["Tetris"][2], "Tetris (Japan)")

    def test_cps1_versions(self):
        g = site_data.cps1_groups()
        sf2 = next(v for t, v in g.items() if v[0] == "sf2")
        self.assertIn("sf2j", sf2)
        self.assertTrue(all(t and " (" not in t for t in g))

    def test_not_games_skipped(self):
        for n in ["[BIOS] Sega Master System (USA) (v1.3)", "110-in-1 (Asia) (En) (Pirate)",
                  "Controller Test Program (Japan) (En) (Test Program)"]:
            self.assertTrue(site_data.skipped(n), n)
        for n in ["Micro Machines (Europe) (Unl)", "Tetris (World)"]:
            self.assertFalse(site_data.skipped(n), n)

    def test_attempts(self):  # a blank screen is tried again later: intros and attract loops
        self.assertEqual(site_data.attempts(1200), [1200, 1500, 2400, 6000])
        self.assertEqual(site_data.attempts(300), [300, 375, 600, 1500, 6000])

    def test_genesis_presses_start(self):  # untouched first (as before), then with Start: pressing can land on a black menu
        plain, pressed = site_data.input_variants("genesis")
        self.assertEqual(plain, [])
        self.assertIn("--press", pressed)
        self.assertTrue(all(a.endswith(":08") for a in pressed[1::2]))
        self.assertEqual(site_data.input_variants("nes"), [["--play", "1"]])

    def test_pick_rom(self):  # an archive with the game and a small extra (Sonic & Knuckles' lock-on patch)
        import tempfile
        with tempfile.TemporaryDirectory() as d:
            for name, size in [("patch.bin", 256), ("game.bin", 2048), ("readme.txt", 9999)]:
                with open(os.path.join(d, name), "wb") as f:
                    f.write(b"x" * size)
            self.assertEqual(os.path.basename(site_data.pick_rom(d, (".bin",))), "game.bin")
            self.assertIsNone(site_data.pick_rom(d, (".nes",)))

    def test_cps1_unsupported(self):
        u = site_data.cps1_unsupported()
        self.assertIn("ganbare", u)
        self.assertTrue(u["sf2m3"].startswith("Street Fighter II'"))


if __name__ == "__main__":
    unittest.main()
