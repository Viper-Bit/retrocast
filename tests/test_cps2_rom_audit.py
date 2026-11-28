import subprocess
import sys
import tempfile
import unittest
import zipfile
import zlib
from pathlib import Path

from tools.cps2_rom_audit import TABLE, audit, read_table


class TestCps2RomAudit(unittest.TestCase):
    def test_mame_diff_reports_region_and_crc(self):
        tool = TABLE.parents[3] / "tools" / "cps2_mame_diff.py"
        with tempfile.TemporaryDirectory() as temp:
            changed = Path(temp) / "games.c"
            changed.write_text(TABLE.read_text(encoding="utf-8").replace(
                "0xaf654792", "0xaf654793", 1), encoding="utf-8")
            actual = subprocess.check_output(
                [sys.executable, tool, TABLE, changed], text=True, encoding="utf-8")
            self.assertEqual(actual.strip(), "- **ssf2 / maincpu** removed ssfe-03b "
                             "(CRC af654792), added ssfe-03b (CRC af654793)")

    def test_compiled_table(self):
        games = read_table(TABLE)
        self.assertEqual(len(games), 324)
        self.assertEqual(games["ssf2u"]["parent"], "ssf2")
        self.assertIn(("maincpu", "ssfu.03a", (524288, "72f29c33")), games["ssf2u"]["chips"])
        self.assertIn(("mcu", "89c4051.bin", None), games["gigaman2"]["chips"])

    def test_merged_archive_and_missing_chip(self):
        chip = b"synthetic"
        key = len(chip), f"{zlib.crc32(chip):08x}"
        games = {"clone": {"parent": "parent", "chips": {("key", "clone.key", key)}}}
        with tempfile.TemporaryDirectory() as temp:
            folder = Path(temp)
            with zipfile.ZipFile(folder / "parent.zip", "w") as archive:
                archive.writestr("clone/clone.key", chip)
            self.assertEqual(audit(games, folder, ["clone"], True)[0]["clone"], ("complete", []))
            games["clone"]["chips"].add(("mcu", "mcu.bin", None))
            self.assertEqual(audit(games, folder, ["clone"], True)[0]["clone"],
                             ("incomplete", ["mcu/mcu.bin: undumped in MAME"]))
