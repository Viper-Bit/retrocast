"""CPS-2 metadata and archive audit tests, with synthetic chips."""

import hashlib
import json
import sys
import tempfile
import unittest
import zipfile
import zlib
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from cps2_audit import audit
from cps2_gen_games import TABLE, generate


def hashes(data):
    return f"CRC({zlib.crc32(data):08x}) SHA1({hashlib.sha1(data).hexdigest()})"


SHARED = b"abcd"
PROGRAM = b"EF"
SOURCE = f'''
#define CODE_SIZE 0x10
ROM_START( base )
    ROM_REGION( CODE_SIZE, "maincpu", ROMREGION_ERASEFF )
    ROM_LOAD16_WORD_SWAP( "first.bin", 0, 2, {hashes(SHARED)} )
    ROM_CONTINUE( 4, 1 )
    ROM_IGNORE( 1 )
    ROM_FILL( 0xf, 1, 0x11 )
ROM_END
ROM_START( clone )
    ROM_REGION16_BE( CODE_SIZE, "maincpu", 0 )
    ROM_LOAD16_WORD_SWAP( "first.bin", 0, 2, {hashes(SHARED)} )
    ROM_CONTINUE( 4, 1 )
    ROM_IGNORE( 1 )
    ROM_LOAD( "clone.bin", 8, 2, {hashes(PROGRAM)} )
ROM_END
GAME( 1994, base, 0, cps2, pad, state, init, ROT0, "Maker", "Parent, 1994", FLAG )
GAME( 1994, clone, base, cps2, pad, state, init, ROT0, "Maker", "Clone", FLAG )
'''


class TestCps2Table(unittest.TestCase):
    def test_layout_and_file_length(self):
        table = generate(SOURCE, "mame-test")["games"]
        self.assertEqual(table["base"]["title"], "Parent, 1994")
        region = table["base"]["regions"]["maincpu"]
        self.assertEqual((region["size"], region["erase"]), (16, 255))
        chip, fill = region["entries"]
        self.assertEqual(chip["size"], 4)
        self.assertEqual(chip["parts"], [{"offset": 0, "size": 2}, {"offset": 4, "size": 1}, {"ignore": 1}])
        self.assertEqual(fill, {"fill": 17, "offset": 15, "size": 1})
        self.assertTrue(table["clone"]["regions"]["maincpu"]["big_endian_words"])
        self.assertEqual(table["clone"]["parent"], "base")
        with self.assertRaisesRegex(ValueError, "unsupported ROM operation"):
            generate(SOURCE.replace("ROM_FILL", "ROM_RELOAD"), "mame-test")

    def test_pinned_manifest(self):
        manifest = json.loads(TABLE.read_text(encoding="utf-8"))
        games = manifest["games"]
        self.assertGreater(len(games), 300)
        self.assertEqual(games["ssf2u"]["parent"], "ssf2")
        rom = games["1944"]["regions"]["audiocpu"]["entries"][0]
        self.assertEqual((rom["name"], rom["size"], rom["crc"]), ("nff.01", 0x20000, "d2e44318"))
        mcu = games["gigaman2"]["regions"]["mcu"]["entries"][0]
        self.assertNotIn("crc", mcu)


class TestCps2Audit(unittest.TestCase):
    def test_split_and_merged_sets(self):
        games = generate(SOURCE, "mame-test")["games"]
        with tempfile.TemporaryDirectory() as directory:
            folder = Path(directory)
            with zipfile.ZipFile(folder / "BASE.ZIP", "w") as z:
                z.writestr("renamed.bin", SHARED)
            with zipfile.ZipFile(folder / "clone.zip", "w") as z:
                z.writestr("clone.bin", b"bad bytes")
            with zipfile.ZipFile(folder / "other.zip", "w") as z:
                z.writestr("clone.bin", PROGRAM)
            result, dsp, errors = audit(games, folder, games, verify=True)
            self.assertEqual(result["base"], ("complete", []))
            self.assertEqual(result["clone"][0], "incomplete")
            self.assertIn("found in other", result["clone"][1][0])
            self.assertFalse(dsp)
            self.assertEqual(errors, [])
            with zipfile.ZipFile(folder / "clone.zip", "w") as z:
                z.writestr("renamed.bin", PROGRAM)
            result, _, _ = audit(games, folder, games, verify=True)
            self.assertEqual(result["clone"], ("complete", []))
            (folder / "clone.zip").unlink()
            with zipfile.ZipFile(folder / "BASE.ZIP", "a") as z:
                z.writestr("clone/clone.bin", PROGRAM)
            result, _, _ = audit(games, folder, games, verify=True)
            self.assertEqual(result["clone"], ("complete", []))

    def test_verification_rejects_wrong_hash(self):
        games = generate(SOURCE, "mame-test")["games"]
        games["base"]["regions"]["maincpu"]["entries"][0]["sha1"] = "0" * 40
        with tempfile.TemporaryDirectory() as directory:
            folder = Path(directory)
            with zipfile.ZipFile(folder / "base.zip", "w") as z:
                z.writestr("first.bin", SHARED)
            unverified, _, _ = audit(games, folder, ["base"])
            verified, _, errors = audit(games, folder, ["base"], verify=True)
            self.assertEqual(unverified["base"][0], "complete")
            self.assertEqual(verified["base"][0], "incomplete")
            self.assertIn("SHA-1 mismatch", errors[0])
