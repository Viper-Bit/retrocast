"""Input recordings (core/input_log.c) through nes_headless, with a made-up
ROM that reads pad 1 into $00 every frame (no game needed): version 1
("NESI", a byte per pad), version 2 ("RCIN", the system, 16 bits per pad)
and version 3 (four pads, for four-player games) give the same input; a recording of another system is refused."""
import os
import struct
import subprocess
import tempfile
import unittest

from tests.nes.test_mappers import RUNNER, ines, vectors
from tests.games import built

A, START, X = 0x01, 0x08, 0x100
# strobe $4016, then 8 reads, each bit rotated into $01 (A ends in bit 7);
# the whole byte copied to $00 (so a peek between reads sees a finished one); forever
READ_PAD = bytes([0xA9, 0x01, 0x8D, 0x16, 0x40, 0xA9, 0x00, 0x8D, 0x16, 0x40, 0xA2, 0x08,
                  0xAD, 0x16, 0x40, 0x4A, 0x26, 0x01, 0xCA, 0xD0, 0xF7,
                  0xA5, 0x01, 0x85, 0x00, 0x4C, 0x00, 0x80])


def v1(frames, pad):
    return b"NESI\x01" + struct.pack("BBB", pad, 0, 0) * frames


def v2(frames, pad, system=b"nes\0"):
    return b"RCIN\x02" + system + struct.pack("<HHB", pad, 0, 0) * frames


def v3(frames, pad, system=b"nes\0"):
    return b"RCIN\x03" + system + struct.pack("<HHHHB", pad, 0, 0x0F, 0x0F, 0) * frames


@built(RUNNER, "build the C runtime first (see tests/nes/test_cpu.py)")
class TestRecording(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        prg = bytearray(0x8000)
        prg[:len(READ_PAD)] = READ_PAD
        vectors(prg, 0x8000, 0x8000)
        cls.tmp = tempfile.TemporaryDirectory()
        cls.rom = os.path.join(cls.tmp.name, "pad.nes")
        with open(cls.rom, "wb") as f:
            f.write(ines(0, prg))

    @classmethod
    def tearDownClass(cls):
        cls.tmp.cleanup()

    def run_nes(self, *args):
        return subprocess.run([RUNNER, self.rom, *args], capture_output=True, text=True, timeout=60)

    def replay(self, data):
        path = os.path.join(self.tmp.name, "in.rec")
        with open(path, "wb") as f:
            f.write(data)
        r = self.run_nes("--replay", path, "--peek", "0")
        line = [ln for ln in r.stdout.splitlines() if ln.startswith("PEEK")]
        return int(line[0].split("=")[1], 16) if line else r

    def test_both_versions_give_the_same_pad(self):
        self.assertEqual(self.replay(v1(10, A | START)), 0x90)
        self.assertEqual(self.replay(v2(10, A | START | X)), 0x90)  # X: not on the NES pad
        self.assertEqual(self.replay(v3(10, A | START)), 0x90)  # pads 3 and 4: not read by the NES

    def test_record_writes_version_2(self):
        path = os.path.join(self.tmp.name, "out.rec")
        self.run_nes("--frames", "3", "--press", "0:9", "--record", path)
        with open(path, "rb") as f:
            data = f.read()
        self.assertEqual(data[:9], b"RCIN\x02nes\0")
        self.assertEqual(len(data), 9 + 3 * 5)
        self.assertEqual(struct.unpack("<HHB", data[9:14]), (A | START, 0, 0))

    def test_other_system_refused(self):
        r = self.replay(v2(5, A, b"gb\0\0"))
        self.assertIsInstance(r, subprocess.CompletedProcess)
        self.assertEqual(r.returncode, 2)
        self.assertIn("another system", r.stderr)


if __name__ == "__main__":
    unittest.main()
