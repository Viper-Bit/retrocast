"""tools/cps1_mame_diff.py: what changed between two CPS-1 game tables (games.c
as tools/cps1_gen_games.py writes it), as the scheduled MAME check reports
it. The table against itself: no change; one set removed, one chip's CRC
changed, one set retitled: each named."""
import os
import sys
import tempfile
import unittest

from tests.games import ROOT

sys.path.insert(0, os.path.join(ROOT, "tools"))
from cps1_mame_diff import diff  # noqa: E402

GAMES_C = os.path.join(ROOT, "systems", "cps1", "runtime", "games.c")


class TestMameDiff(unittest.TestCase):
    def test_same_table(self):
        self.assertEqual(diff(GAMES_C, GAMES_C), [])

    def test_changes_named(self):
        src = open(GAMES_C, encoding="utf-8").read()
        a = src.index('    {"ffightu",')  # the next set's entry starts where this one ends
        b = src.index('\n    {"', a + 1) + 1
        changed = src[:a] + src[b:]                                  # ffightu removed
        changed = changed.replace("0x0c8dc3fc", "0x12345678", 1)     # the first set holding ff_34.9f (CRC 0c8dc3fc)
        changed = changed.replace('"Final Fight (World, set 1)"', '"Final Fight (World)"', 1)
        with tempfile.TemporaryDirectory() as d:
            new = os.path.join(d, "games.c")
            open(new, "w", encoding="utf-8").write(changed)
            lines = diff(GAMES_C, new)
        text = "\n".join(lines)
        self.assertIn("ffightu", text)
        self.assertIn("removed", text)
        self.assertIn("0c8dc3fc", text)
        self.assertIn("12345678", text)
        self.assertIn("Final Fight (World)", text)


if __name__ == "__main__":
    unittest.main()
