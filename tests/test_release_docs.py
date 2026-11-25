"""The release's two texts name every program the archive holds: dist/README.txt
(in the archive) and .github/release-notes.md (the release page). The list is
tools/make_release.py's PROGRAMS, so a new headless program or recompiler
there fails this test until both texts mention it."""
import os
import re
import sys
import unittest

from tests.games import ROOT

sys.path.insert(0, os.path.join(ROOT, "tools"))
from make_release import PROGRAMS  # noqa: E402


class TestReleaseDocs(unittest.TestCase):
    def check(self, rel):
        text = open(os.path.join(ROOT, rel), encoding="utf-8").read()
        for prog in PROGRAMS:
            with self.subTest(doc=rel, program=prog):
                self.assertRegex(text, r"(?<![\w-])" + re.escape(prog) + r"(?![\w-])")

    def test_readme_txt(self):
        self.check(os.path.join("dist", "README.txt"))

    def test_release_notes(self):
        self.check(os.path.join(".github", "release-notes.md"))


if __name__ == "__main__":
    unittest.main()
