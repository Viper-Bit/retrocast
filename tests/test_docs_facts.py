"""Facts the docs repeat from the code, checked so they can't drift: the number
of CPS-1 sets (runtime/games.c) and which systems use each shared CPU."""
import os
import re
import sys
import unittest

from tests.games import ROOT

sys.path.insert(0, os.path.join(ROOT, "tools"))
import cps1_audit  # noqa: E402


def read(rel):
    with open(os.path.join(ROOT, rel), encoding="utf-8") as f:
        return f.read()


class TestDocsFacts(unittest.TestCase):
    def test_cps1_set_count(self):
        n = len(cps1_audit.table())
        for rel in ("docs/roadmap.md", "README.md"):
            for m in re.findall(r"(\d+) (?:CPS-1 )?sets", read(rel)):
                with self.subTest(doc=rel):
                    self.assertEqual(int(m), n)

    def test_cpu_table(self):
        rows = {r.split("|")[1].strip(): r for r in read("cpu/README.md").splitlines() if r.startswith("| ")}
        self.assertIn("CPS-1", rows["Z80"])
        self.assertIn("CPS-1", rows["68000"])

    def test_readme_cpu_list(self):
        line = next(l for l in read("README.md").splitlines() if "cpu/README.md" in l)
        for cpu in ("6502", "SM83", "Z80", "68000"):
            self.assertIn(cpu, line)


if __name__ == "__main__":
    unittest.main()
