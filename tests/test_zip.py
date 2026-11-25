"""core/zip.c: zips that Python writes read back the same through zip_check
(stored and deflate entries, empty to 1 MB, a back-reference 32 KB away),
damaged zips fail cleanly, and, with the CPS-1 set ($CPS1_ROMS_DIR or
roms/CAPCOM - Play System I), every zip in it reads as Python reads it.
"""
import glob
import os
import subprocess
import tempfile
import unittest
import zipfile
import zlib

from tests.games import ROOT, built

BUILD = os.environ.get("NES_BUILD", os.path.join(ROOT, "build"))
CHECK = os.path.join(BUILD, "zip_check" + (".exe" if os.name == "nt" else ""))
SET = os.environ.get("CPS1_ROMS_DIR", os.path.join(ROOT, "roms", "CAPCOM - Play System I"))


def expected(path):
    with zipfile.ZipFile(path) as z:
        return [(i.filename, zlib.crc32(z.read(i)), i.file_size) for i in z.infolist()]


def run(path):
    r = subprocess.run([CHECK, path], capture_output=True, text=True, timeout=120)
    lines = [ln.rsplit(" ", 2) for ln in r.stdout.splitlines()]  # a name may hold spaces (MAME's "01 rk098")
    return r.returncode, [(n, int(c, 16), int(s)) for n, c, s in lines] if r.returncode == 0 else r


def contents():
    rnd = os.urandom(1 << 20)
    block = os.urandom(32768)
    return {"empty": b"", "one": b"x", "random": rnd, "repeat": b"ab" * (1 << 19),
            "far": block + os.urandom(100) + block[:4000] + os.urandom(60000)}


@built(CHECK, "build zip_check first (-DTESTS=ON)")
class TestZip(unittest.TestCase):
    def test_methods(self):
        with tempfile.TemporaryDirectory() as d:
            path = os.path.join(d, "t.zip")
            with zipfile.ZipFile(path, "w") as z:
                for name, data in contents().items():
                    z.writestr(name + ".stored", data, zipfile.ZIP_STORED)
                    for level in (1, 9):
                        z.writestr("%s.%d" % (name, level), data, zipfile.ZIP_DEFLATED, compresslevel=level)
            code, got = run(path)
            self.assertEqual(code, 0, got)
            self.assertEqual(got, expected(path))

    def test_damaged(self):
        with tempfile.TemporaryDirectory() as d:
            path = os.path.join(d, "t.zip")
            with zipfile.ZipFile(path, "w") as z:
                z.writestr("a", os.urandom(1000) * 50, zipfile.ZIP_DEFLATED)
            data = open(path, "rb").read()
            cut = os.path.join(d, "cut.zip")
            open(cut, "wb").write(data[: len(data) // 2])
            flip = bytearray(data)
            flip[30 + 1 + 200] ^= 0x55  # inside the deflated data (local header 30 bytes, name "a")
            flipped = os.path.join(d, "flip.zip")
            open(flipped, "wb").write(bytes(flip))
            for p in (cut, flipped):
                r = subprocess.run([CHECK, p], capture_output=True, timeout=60)
                self.assertEqual(r.returncode, 1, p)  # an error, not a crash

    @unittest.skipUnless(os.path.isdir(SET), "no CPS-1 set in " + SET)
    def test_set(self):
        for path in sorted(glob.glob(os.path.join(SET, "*.zip"))):
            with self.subTest(zip=os.path.basename(path)):
                code, got = run(path)
                self.assertEqual(code, 0, got)
                self.assertEqual(got, expected(path))


if __name__ == "__main__":
    unittest.main()
