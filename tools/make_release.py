"""Build one release archive for the platform this runs on.

    python tools/make_release.py --name retrocast-v0.1.0-windows-x64 [--work DIR] [--out DIR]

1. SDL3 (release-3.4.20), static, with the frontend's options (cmake/sdl3_options.cmake),
   installed into the staged kit/sdl3.
2. retrocast (the window program for every system), the headless programs and
   the recompilers, Release, linked against that SDL3.
3. Stage: the programs, the recompile kit (this project's CMakeLists.txt, cmake/,
   core/, cpu/, systems/ and the prebuilt SDL3), README.txt, licenses.
4. Kit check: recompile tiny generated ROMs with the staged kit, as a user
   would, and run the result headless.
5. Archive: NAME.zip on Windows, NAME.tar.gz elsewhere, in --out.
Used by .github/workflows/release.yml; needs git, CMake >= 3.20, a C compiler.
"""
import argparse
import os
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SDL_TAG = "release-3.4.20"  # as in CMakeLists.txt
WIN = os.name == "nt"
EXE = ".exe" if WIN else ""
KIT_FILES = ["CMakeLists.txt", "cmake", "core", "cpu", "systems"]


# The programs in the archive; dist/README.txt and .github/release-notes.md
# name each (tests/test_release_docs.py).
PROGRAMS = ("retrocast", "nes_headless", "nesrecomp", "gb_headless", "gbrecomp",
            "genesis_headless", "mdrecomp", "atari2600_headless", "atari2600recomp",
            "sms_headless", "smsrecomp", "cps1_headless", "cps1recomp",
            "cps2_headless", "cps2_recompile")

def run(*cmd, cwd=None):
    print("+", " ".join(cmd), flush=True)
    subprocess.run(cmd, check=True, cwd=cwd)


def cmake_build(src, build, *defs):
    """Configure and build Release (single- or multi-config generators)."""
    run("cmake", "-S", src, "-B", build, "-DCMAKE_BUILD_TYPE=Release", *defs)
    run("cmake", "--build", build, "--config", "Release", "--parallel")


def tiny_rom(path):
    """NROM-128 that loops forever: enough to build and boot a recompiled program."""
    prg = bytearray(0x4000)
    prg[0:3] = bytes([0x4C, 0x00, 0xC0])  # $C000: JMP $C000
    prg[-6:] = bytes([0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0])  # NMI, RESET, IRQ = $C000
    with open(path, "wb") as f:
        f.write(b"NES\x1a\x01\x01\x00\x00" + bytes(8) + prg + bytes(0x2000))


GB_LOGO = bytes.fromhex("CEED6666CC0D000B03730083000C000D0008111F8889000EDCCC6EE6DDDDD999"
                        "BBBB67636E0EECCCDDDC999FBBB9333E")


def tiny_gb_rom(path):
    """A 32 KB Game Boy cartridge: the logo and header checksum the boot ROM
    checks (and detection reads), then "Passed" sent on the serial port, the
    way test ROMs report (gb_headless exits 0 on it), then a loop."""
    rom = bytearray(0x8000)
    rom[0x100:0x104] = bytes([0x00, 0xC3, 0x50, 0x01])  # NOP; JP $0150
    rom[0x104:0x134] = GB_LOGO
    rom[0x134:0x13C] = b"KITCHECK"
    x = 0
    for b in rom[0x134:0x14D]:
        x = (x - b - 1) & 0xFF
    rom[0x14D] = x
    rom[0x150:0x167] = bytes([0x21, 0x70, 0x01,  # LD HL,$0170
                              0x2A, 0xB7, 0x28, 0x0E,  # next: LD A,(HL+); OR A; JR Z,done
                              0xE0, 0x01, 0x3E, 0x81, 0xE0, 0x02,  # LDH (SB),A; LD A,$81; LDH (SC),A
                              0xF0, 0x02, 0xCB, 0x7F, 0x20, 0xFA,  # wait: LDH A,(SC); BIT 7,A; JR NZ,wait
                              0x18, 0xEE,  # JR next
                              0x18, 0xFE])  # done: JR done
    rom[0x170:0x176] = b"Passed"  # then 0: the ROM is zeroed
    with open(path, "wb") as f:
        f.write(rom)


def tiny_sms_rom(path):
    """A 32 KB Master System cartridge: "TMR SEGA" with an export region at
    $7FF0, then a loop that counts in RAM and writes a VDP register."""
    rom = bytearray(0x8000)
    rom[0:15] = bytes([0xF3, 0x31, 0xF0, 0xDF,  # DI; LD SP,$DFF0
                       0x21, 0x00, 0xC0,  # LD HL,$C000
                       0x34,  # loop: INC (HL)
                       0x3E, 0x81, 0xD3, 0xBF,  # LD A,$81; OUT ($BF),A
                       0xD3, 0xBF,  # OUT ($BF),A
                       0x18])  # JR loop
    rom[15] = (7 - 16) & 0xFF
    rom[0x7FF0:0x7FF8] = b"TMR SEGA"
    rom[0x7FFF] = 0x4C  # export Master System, 32 KB
    with open(path, "wb") as f:
        f.write(rom)


def tiny_gg_rom(path):
    """A 32 KB Game Gear cartridge: "TMR SEGA" with a GG export region at
    $7FF0, then the same count-and-write-VDP loop as the Master System one."""
    rom = bytearray(0x8000)
    rom[0:15] = bytes([0xF3, 0x31, 0xF0, 0xDF,  # DI; LD SP,$DFF0
                       0x21, 0x00, 0xC0,  # LD HL,$C000
                       0x34,  # loop: INC (HL)
                       0x3E, 0x81, 0xD3, 0xBF,  # LD A,$81; OUT ($BF),A
                       0xD3, 0xBF,  # OUT ($BF),A
                       0x18])  # JR loop
    rom[15] = (7 - 16) & 0xFF
    rom[0x7FF0:0x7FF8] = b"TMR SEGA"
    rom[0x7FFF] = 0x6C  # export Game Gear, 32 KB
    with open(path, "wb") as f:
        f.write(rom)


def tiny_md_rom(path):
    """A Genesis cartridge: vectors, the "SEGA" header, the TMSS unlock, one VDP
    register write (the headless program and the build's trace count a game
    as running from its first VDP write), then a loop."""
    rom = bytearray(0x400)
    rom[0:8] = bytes([0x00, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x02, 0x00])  # SSP $FFFE00, PC $200
    rom[0x100:0x110] = b"SEGA MEGA DRIVE "
    rom[0x200:0x212] = bytes([0x23, 0xFC, 0x53, 0x45, 0x47, 0x41, 0x00, 0xA1, 0x40, 0x00,  # MOVE.L #'SEGA',$A14000
                              0x33, 0xFC, 0x81, 0x04, 0x00, 0xC0, 0x00, 0x04,  # MOVE.W #$8104,$C00004
                              0x60, 0xFE])  # BRA.S to itself
    with open(path, "wb") as f:
        f.write(rom)


def tiny_atari_rom(path):
    rom = bytearray(2048)
    rom[:3] = bytes([0x4C, 0x00, 0xF0])  # JMP $F000
    rom[-4:-2] = bytes([0x00, 0xF0])
    with open(path, "wb") as f:
        f.write(rom)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--name", required=True, help="archive and folder name")
    ap.add_argument("--work", default=os.path.join(ROOT, "out", "release"))
    ap.add_argument("--out", default=os.path.join(ROOT, "out", "dist"))
    a = ap.parse_args()
    work, stage = os.path.abspath(a.work), os.path.join(os.path.abspath(a.work), a.name)
    if os.path.exists(work):
        shutil.rmtree(work)
    os.makedirs(stage)
    kit = os.path.join(stage, "kit")

    # 1. SDL3, installed into the kit
    sdl_src = os.path.join(work, "SDL")
    run("git", "clone", "--depth", "1", "--branch", SDL_TAG, "https://github.com/libsdl-org/SDL.git", sdl_src)
    sdl_build = os.path.join(work, "sdl-build")
    cmake_build(sdl_src, sdl_build, "-C", os.path.join(ROOT, "cmake", "sdl3_options.cmake"),
                "-DCMAKE_INSTALL_PREFIX=" + os.path.join(kit, "sdl3"))
    run("cmake", "--install", sdl_build, "--config", "Release")

    # 2. the programs, against that SDL3
    build = os.path.join(work, "build")
    cmake_build(ROOT, build, "-DSDL3_PREFIX=" + os.path.join(kit, "sdl3"))

    # 3. stage
    for prog in PROGRAMS:  # no CPS-1 kit check: a game is a real zip, matched by CRC
        shutil.copy2(os.path.join(build, prog + EXE), stage)
    for item in KIT_FILES:
        src = os.path.join(ROOT, item)
        if os.path.isdir(src):
            shutil.copytree(src, os.path.join(kit, item))
        else:
            shutil.copy2(src, kit)
    shutil.copy2(os.path.join(ROOT, "dist", "README.txt"), stage)
    shutil.copy2(os.path.join(ROOT, "LICENSE"), stage)
    shutil.copy2(os.path.join(sdl_src, "LICENSE.txt"), os.path.join(stage, "LICENSE-SDL3.txt"))

    # 4. kit check: recompile a ROM with the staged kit, then run it
    rom = os.path.join(work, "kit_check.nes")
    tiny_rom(rom)
    gb_rom = os.path.join(work, "kit_check_gb.gb")
    tiny_gb_rom(gb_rom)
    sms_rom = os.path.join(work, "kit_check_sms.sms")
    tiny_sms_rom(sms_rom)
    gg_rom = os.path.join(work, "kit_check_gg.gg")
    tiny_gg_rom(gg_rom)
    md_rom = os.path.join(work, "kit_check_md.md")
    tiny_md_rom(md_rom)
    atari_rom = os.path.join(work, "kit_check_atari.a26")
    tiny_atari_rom(atari_rom)
    kit_build = os.path.join(work, "kit-build")
    cmake_build(kit, kit_build, "-DROMS=" + ";".join((rom, gb_rom, md_rom, atari_rom, sms_rom, gg_rom)))
    run(os.path.join(kit_build, "kit_check_headless" + EXE), "--frames", "30")
    run(os.path.join(stage, "nes_headless" + EXE), rom, "--frames", "30")
    run(os.path.join(kit_build, "kit_check_gb_headless" + EXE), gb_rom, "--frames", "30", "--diff")
    run(os.path.join(stage, "gb_headless" + EXE), gb_rom, "--frames", "30")
    run(os.path.join(kit_build, "kit_check_sms_headless" + EXE), sms_rom, "--frames", "30", "--diff")
    run(os.path.join(stage, "sms_headless" + EXE), sms_rom, "--frames", "30")
    run(os.path.join(kit_build, "kit_check_gg_headless" + EXE), gg_rom, "--frames", "30", "--diff")
    run(os.path.join(stage, "sms_headless" + EXE), gg_rom, "--frames", "30")
    run(os.path.join(kit_build, "kit_check_md_headless" + EXE), md_rom, "--frames", "30", "--diff")
    run(os.path.join(stage, "genesis_headless" + EXE), md_rom, "--frames", "30")
    run(os.path.join(kit_build, "kit_check_atari_headless" + EXE), "--frames", "2", "--diff")
    run(os.path.join(stage, "atari2600_headless" + EXE), atari_rom, "--frames", "2")

    # 5. archive
    os.makedirs(a.out, exist_ok=True)
    archive = os.path.join(os.path.abspath(a.out), a.name + (".zip" if WIN else ".tar.gz"))
    fmt = ["--format=zip"] if WIN else []
    run("cmake", "-E", "tar", "cf" if WIN else "czf", archive, *fmt, a.name, cwd=work)
    print("archive:", archive)
    return 0


if __name__ == "__main__":
    sys.exit(main())
