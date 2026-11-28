"""Which system a file is for, from its bytes (core/detect.h): the C
detectors (system_detect, as retrocast picks the system) and the CMake rules
for the ROMS list (cmake/detect_system.cmake) on the same made-up files; both
must give the same answer."""
import io
import os
import shutil
import struct
import subprocess
import tempfile
import unittest
import zipfile

from tests.games import ROOT, built

BUILD = os.environ.get("NES_BUILD", os.path.join(ROOT, "build"))
EXE = ".exe" if os.name == "nt" else ""
RUNNER = os.path.join(BUILD, "system_detect" + EXE)
CMAKE_ID = {"nes": "nes", "gb": "gb", "genesis": "md", "atari2600": "a26", "mastersystem": "sms", "gamegear": "gg", "cps1": "cps1"}
LOGO = bytes.fromhex("ceed6666cc0d000b03730083000c000d0008111f8889000edccc6ee6ddddd999"
                     "bbbb67636e0eecccdddc999fbbb9333e")


def gb(checksum_ok=True):
    rom = bytearray(0x8000)
    rom[0x104:0x134] = LOGO
    rom[0x134:0x13F] = b"TEST"
    x = 0
    for b in rom[0x134:0x14D]:
        x = (x - b - 1) & 0xFF
    rom[0x14D] = x if checksum_ok else x ^ 1
    return bytes(rom)


def genesis(sega=b"SEGA MEGA DRIVE "):
    rom = bytearray(0x400)
    rom[0x100:0x100 + len(sega)] = sega
    return bytes(rom)


def atari(size=4096, vector_ok=True):
    rom = bytearray(size)
    rom[-3] = 0xF0 if vector_ok else 0x00  # reset vector's high byte: $Fxxx is in $1000-$1FFF
    return bytes(rom)


def sms(header=True, region=0x4):
    rom = bytearray(0x8000)
    if header:
        rom[0x7FF0:0x7FF8] = b"TMR SEGA"
        rom[0x7FFF] = region << 4 | 0xC
    return bytes(rom)


def gg(region=0x6):
    rom = bytearray(0x8000)
    rom[0x7FF0:0x7FF8] = b"TMR SEGA"
    rom[0x7FFF] = region << 4 | 0xC
    return bytes(rom)


def nes():
    return b"NES\x1a\x01\x01" + bytes(10) + bytes(0x4000 + 0x2000)


def both_headers():  # an iNES header and "SEGA" at $100: two sure answers
    rom = bytearray(nes()[:0x600])
    rom[0x100:0x104] = b"SEGA"
    return bytes(rom)


def zipped():
    b = io.BytesIO()
    with zipfile.ZipFile(b, "w") as z:
        z.writestr("game.bin", bytes(range(256)) * 64)
    return b.getvalue()


CASES = [  # file name, bytes, expected id (None: refused)
    ("other.zip", zipped(), None),  # a zip of no CPS-1 game
    ("game.nes", nes(), "nes"),
    ("disk.fds", b"FDS\x1a\x01" + bytes(11) + bytes(65500), "nes"),
    ("raw.fds", b"\x01*NINTENDO-HVC*" + bytes(65500), "nes"),
    ("game.gb", gb(), "gb"),
    ("game.gbc", gb(), "gb"),
    ("no_extension", gb(), "gb"),
    ("hacked.gb", gb(checksum_ok=False), "gb"),  # logo only: 70, + the extension
    ("game.md", genesis(), "md"),
    ("game.bin", genesis(b" SEGA GENESIS"), "md"),
    ("game.sms", sms(), "sms"),
    ("no_extension_sms", sms(), "sms"),
    ("japan.sms", sms(header=False), "sms"),  # no header: weak, the extension decides
    ("japan.bin", sms(header=False), None),
    ("game.gg", gg(), "gg"),
    ("game.sms", gg(), "gg"),  # the region nibble decides, not the extension
    ("no_extension_gg", gg(region=0x5), "gg"),
    ("game.a26", atari(), "a26"),
    ("bank.a26", atari(8192, vector_ok=False), "a26"),  # weak, the extension decides
    ("game.bin", atari(2048), None),  # weak: without .a26 (or --system) no system is picked
    ("both.nes", both_headers(), "nes"),  # two sure answers, the extension decides
    ("both.rom", both_headers(), None),  # two sure answers, nothing decides: --system
    ("random.bin", bytes(range(256)) * 5, None),
    ("odd.a26", atari(3000), None),  # not a cartridge size
    ("tiny.nes", b"NES", None),
]


@built(RUNNER, "build system_detect first")
class TestDetect(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tmp = tempfile.TemporaryDirectory()

    @classmethod
    def tearDownClass(cls):
        cls.tmp.cleanup()

    def write(self, i, name, data):
        d = os.path.join(self.tmp.name, str(i))
        os.makedirs(d, exist_ok=True)
        path = os.path.join(d, name)
        with open(path, "wb") as f:
            f.write(data)
        return path

    def test_c_detectors(self):
        built_ids = subprocess.run([RUNNER, "--systems"], capture_output=True, text=True).stdout.split()
        if not set(CMAKE_ID.values()).issubset(built_ids):
            self.skipTest("needs every system built (SYSTEMS), not " + " ".join(built_ids))
        for i, (name, data, want) in enumerate(CASES):
            with self.subTest(file=name, want=want):
                r = subprocess.run([RUNNER, self.write(i, name, data)], capture_output=True, text=True)
                if want is None:
                    self.assertEqual(r.returncode, 1, r.stdout)
                    self.assertIn("--system", r.stderr)
                else:
                    self.assertEqual((r.returncode, r.stdout.strip()), (0, want), r.stderr)

    def test_cps2_program_chip(self):
        built_ids = subprocess.run([RUNNER, "--systems"], capture_output=True, text=True).stdout.split()
        if "cps2" not in built_ids:
            self.skipTest("CPS-2 detector is absent")
        file = io.BytesIO()
        with zipfile.ZipFile(file, "w") as archive:
            archive.writestr("renamed.bin", b"x")
        raw = bytearray(file.getvalue())
        central = raw.index(b"PK\x01\x02")
        # Detection reads the central directory. The ROM loader checks actual bytes.
        struct.pack_into("<I", raw, central + 16, 0xaf654792)
        struct.pack_into("<I", raw, central + 24, 524288)
        result = subprocess.run([RUNNER, self.write("cps2", "ssf2.zip", raw)],
                                capture_output=True, text=True)
        self.assertEqual((result.returncode, result.stdout.strip()), (0, "cps2"), result.stderr)

    @unittest.skipUnless(shutil.which("cmake"), "no cmake")
    def test_cmake_rules_agree(self):
        script = os.path.join(ROOT, "cmake", "detect_system.cmake")
        for i, (name, data, want) in enumerate(CASES):
            with self.subTest(file=name, want=want):
                r = subprocess.run(["cmake", "-DFILE=" + self.write(i, name, data), "-P", script],
                                   capture_output=True, text=True)
                if want is None:
                    self.assertNotEqual(r.returncode, 0, r.stderr)
                else:
                    self.assertEqual(r.returncode, 0, r.stderr)
                    self.assertEqual(CMAKE_ID[r.stderr.strip()], want)  # message() prints to stderr

CPS1 = os.environ.get("CPS1_ROMS_DIR", os.path.join(ROOT, "roms", "CAPCOM - Play System I"))
CPS2_ZIP = os.path.join(os.path.dirname(CPS1), "CAPCOM - Play System II", "sfa.zip")
SCRIPT = os.path.join(ROOT, "cmake", "detect_system.cmake")


class TestCps1(unittest.TestCase):
    """A CPS-1 zip is matched to the game table (systems/cps1/runtime/games.c)
    by its files' CRCs: the C detector and the CMake rule, which reads the
    table itself."""

    def cmake(self, path, *defs):
        return subprocess.run(["cmake", "-DFILE=" + path, *defs, "-P", SCRIPT], capture_output=True, text=True)

    @unittest.skipUnless(os.path.exists(os.path.join(CPS1, "ffight.zip")), "no ffight.zip in " + CPS1)
    @built(RUNNER, "build system_detect first (-DTESTS=ON)")
    def test_cps1_zip(self):
        game = os.path.join(CPS1, "ffight.zip")
        r = subprocess.run([RUNNER, game], capture_output=True, text=True)
        self.assertEqual((r.returncode, r.stdout.strip()), (0, "cps1"), r.stderr)
        r = self.cmake(game)
        self.assertEqual((r.returncode, r.stderr.strip()), (0, "cps1"))
        if os.path.exists(CPS2_ZIP):
            result = subprocess.run([RUNNER, CPS2_ZIP], capture_output=True, text=True)
            self.assertNotEqual(result.stdout.strip(), "cps1")
            r = self.cmake(CPS2_ZIP)
            self.assertNotEqual(r.returncode, 0)
            self.assertIn("not a game", r.stderr)

    @unittest.skipUnless(shutil.which("cmake"), "no cmake")
    def test_cps1_table_parse(self):  # a games.c the rule cannot read fails loudly
        src = open(os.path.join(ROOT, "systems", "cps1", "runtime", "games.c"), encoding="utf-8").read()
        broken = src.replace("{0xf9a5ce83,", "{ 0xf9a5ce83,", 1)
        self.assertNotEqual(src, broken)
        with tempfile.TemporaryDirectory() as d:
            games = os.path.join(d, "games.c")
            open(games, "w", encoding="utf-8").write(broken)
            other = os.path.join(d, "game.nes")
            open(other, "wb").write(nes())
            r = self.cmake(other, "-DGAMES_C=" + games)
            self.assertNotEqual(r.returncode, 0, r.stderr)
            self.assertIn("games.c", r.stderr)
            empty = '\n    {"empty", "Empty", CPS1_PLAIN, {0}, CPSB_04, 0, {\n    }},\n};'
            zero = src.replace("\n};", empty, 1)  # a game of no files would match any zip
            open(games, "w", encoding="utf-8").write(zero)
            r = self.cmake(other, "-DGAMES_C=" + games)
            self.assertNotEqual(r.returncode, 0, r.stderr)
            self.assertIn("games.c", r.stderr)

    @unittest.skipUnless(os.path.exists(os.path.join(CPS1, "ffight.zip")), "no ffight.zip in " + CPS1)
    def test_cps1_short_crc(self):  # 0x0b605e44 written 0xb605e44 is the same number in C, and in the rule
        src = open(os.path.join(ROOT, "systems", "cps1", "runtime", "games.c"), encoding="utf-8").read()
        with tempfile.TemporaryDirectory() as d:
            games = os.path.join(d, "games.c")
            open(games, "w", encoding="utf-8").write(src.replace("{0x0b605e44,", "{0xb605e44,", 1))
            r = self.cmake(os.path.join(CPS1, "ffight.zip"), "-DGAMES_C=" + games)
            self.assertEqual((r.returncode, r.stderr.strip()), (0, "cps1"))


if __name__ == "__main__":
    unittest.main()
