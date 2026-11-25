"""Generates systems/cps1/runtime/games.c from MAME 0.289's cps1.cpp and
cps1_v.cpp (tag mame0289: src/mame/capcom/), which are not in this repository.

    python3 tools/cps1_gen_games.py MAME_DIR OUT_GAMES_C [--left OUT_MD]

--left writes the markdown rows of the sets left out, with the reason (the
"Not supported yet" table of systems/cps1/docs/compatibility.md).
"""
import re
import sys

MAME = sys.argv[1]
SRC = open(MAME + "/cps1.cpp", encoding="utf-8").read()
VSRC = open(MAME + "/cps1_v.cpp", encoding="utf-8").read()


def num(s):
    s = s.strip()
    return int(s, 0)


def split_args(s):
    """Top-level comma split of a macro's arguments, quotes and parentheses respected."""
    out, depth, cur, q = [], 0, "", False
    for i, ch in enumerate(s):
        if q:
            cur += ch
            if ch == '"' and s[i - 1] != "\\":
                q = False
            continue
        if ch == '"':
            q = True
        elif ch in "({":
            depth += 1
        elif ch in ")}":
            depth -= 1
        elif ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
            continue
        cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def strip_comments(t):
    t = re.sub(r"/\*.*?\*/", "", t, flags=re.S)
    return re.sub(r"//[^\n]*", "", t)


# ---- cps1_v.cpp: CPS-B configs, mappers, the config table ----

V = strip_comments(VSRC)
cpsb = {}
for m in re.finditer(r"^#define (CPS_B_\w+|HACK_B_\w+)\s+(.*)$", V, re.M):
    body = m.group(2).replace("__not_applicable__", "-1,-1,-1,-1,-1,-1,-1")
    vals = [int(x, 0) for x in re.findall(r"-?0x[0-9a-fA-F]+|-?\d+", body)]
    assert len(vals) == 20, (m.group(1), vals)
    cpsb[m.group(1)] = vals

mapper_banks, mapper_ranges = {}, {}
for m in re.finditer(r"^#define (mapper_\w+)\s+\{([^}]*)\},\s*(\w+)", V, re.M):
    mapper_banks[m.group(1)] = ([int(x, 0) for x in m.group(2).split(",")], m.group(3))
for m in re.finditer(r"static const struct gfx_range (\w+)\[\]\s*=\s*\{(.*?)\n\};", V, re.S):
    ranges = []
    for r in re.finditer(r"\{\s*([A-Z0-9_ |]+?)\s*,\s*(0x[0-9a-fA-F]+)\s*,\s*(0x[0-9a-fA-F]+)\s*,\s*(\d+)\s*\}", m.group(2)):
        ranges.append(([t.strip() for t in r.group(1).split("|")], int(r.group(2), 16), int(r.group(3), 16), int(r.group(4))))
    mapper_ranges[m.group(1)] = ranges

config = {}
table = V[V.index("cps1_config_table[]="):]
for m in re.finditer(r'\{"(\w+)",\s*(\w+),\s*(\w+)\s*(?:,([^}]*))?\}', table):
    extra = [int(x, 0) for x in m.group(4).split(",")] if m.group(4) else []
    extra += [0] * (4 - len(extra))
    config[m.group(1)] = (m.group(2), m.group(3), extra)

# ---- cps1.cpp: games, ROMs, inputs, machines ----

S = SRC
games = []
for m in re.finditer(r"^GAME\(\s*(.*?)\)\s*(?://.*)?$", S, re.M):
    a = split_args(m.group(1))
    games.append(dict(year=a[0], id=a[1], parent=None if a[2] == "0" else a[2], machine=a[3], input=a[4],
                      init=a[6], rot=a[7], title=a[9]))

roms = {}
for m in re.finditer(r"^ROM_START\(\s*(\w+)\s*\)(.*?)^ROM_END", S, re.M | re.S):
    roms[m.group(1)] = strip_comments(m.group(2))

defines = {"CODE_SIZE": 0x400000}


def parse_rom(gid):
    """[(region, kind, name, offset, size, crc, extras)], stars offset or -1; extras: [(op, args)]."""
    files, region, stars = [], None, -1
    for line in roms[gid].splitlines():
        line = line.strip()
        m = re.match(r"(ROM_\w+)\s*\((.*)\)\s*$", line)
        if not m:
            continue
        op, args = m.group(1), split_args(m.group(2))
        if op.startswith("ROM_REGION"):
            region = args[1].strip('"')
        elif op == "ROM_COPY":
            if region == "stars":
                assert args[0] == '"gfx"'
                stars = num(args[1])
        elif op in ("ROM_CONTINUE", "ROM_IGNORE", "ROM_RELOAD", "ROM_FILL"):
            if files and files[-1][0] == region:
                files[-1][6].append((op, [num(x) if re.match(r"^(0x)?[0-9a-fA-F]+$", x) else x for x in args]))
            elif op == "ROM_FILL":
                files.append((region, op, None, 0, 0, 0, [(op, args)]))
        elif op.startswith("ROM_LOAD"):
            crc = re.search(r"CRC\((\w+)\)", args[3]) if len(args) > 3 else None
            files.append((region, op, args[0].strip('"'), num(args[1]), num(args[2]), int(crc.group(1), 16) if crc else None, []))
    return files, stars


# Input ports: statements per INPUT_PORTS block, macros expanded.
macros = {}
for m in re.finditer(r"^#define (\w+)\(\w*\)\s*\\\n((?:.*\\\n)*.*)$", S, re.M):
    macros[m.group(1)] = [l.rstrip("\\").strip() for l in m.group(2).splitlines()]
inputs = {}
for m in re.finditer(r"INPUT_PORTS_START\(\s*(\w+)\s*\)(.*?)INPUT_PORTS_END", S, re.S):
    stmts = []
    for line in strip_comments(m.group(2)).splitlines():
        line = line.strip()
        mm = re.match(r"(\w+)\s*\(", line)
        if mm and mm.group(1) in macros:
            stmts += macros[mm.group(1)]
        elif line:
            stmts.append(line)
    inputs[m.group(1)] = stmts


def ports_of(name, ports=None, cur=None):
    """{port: {mask: (value, kind)}} with kind the IPT type for PORT_BIT."""
    ports = {} if ports is None else ports
    state = {"cur": cur}
    for st in inputs[name]:
        for mm in re.finditer(r"(PORT_\w+)\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)", st):
            op, args = mm.group(1), split_args(mm.group(2))
            if op == "PORT_INCLUDE":
                ports_of(args[0], ports)
            elif op == "PORT_START":
                state["cur"] = args[0].strip('" ')
                ports[state["cur"]] = {}
            elif op == "PORT_MODIFY":
                state["cur"] = args[0].strip('" ')
            elif op in ("PORT_DIPNAME", "PORT_DIPUNUSED", "PORT_DIPUNUSED_DIPLOC", "PORT_DIPUNKNOWN", "PORT_DIPUNKNOWN_DIPLOC"):
                ports[state["cur"]][num(args[0])] = (num(args[1]), "DIP")
            elif op in ("PORT_SERVICE", "PORT_SERVICE_DIPLOC", "PORT_SERVICE_NO_TOGGLE"):
                mask = num(args[0])
                ports[state["cur"]][mask] = (mask if args[1] == "IP_ACTIVE_LOW" else 0, "SERVICE")
            elif op == "PORT_BIT":
                mask = num(args[0])
                v = mask if args[1] == "IP_ACTIVE_LOW" else 0 if args[1] == "IP_ACTIVE_HIGH" else num(args[1])
                kind = args[2]
                pl = re.search(r"PORT_PLAYER\((\d)\)", st)
                ports[state["cur"]][mask] = (v, kind + ("/P" + pl.group(1) if pl else ""))
            elif op == "PORT_PLAYER":
                pass
    return ports


def port_value(fields):
    v = 0
    for mask, (val, _) in fields.items():
        v = (v & ~mask) | (val & mask)
    return v & 0xFF


MACHINE_MHZ = {"cps1_10MHz": 10, "forgottn": 10, "ganbare": 10, "sf2cems6": 10, "cps1_12MHz": 12, "pang3": 12,
               "qsound": 12, "wofhfh": 12, "sf2m3": 12, "sf2m10": 12, "varthb2": 12, "varthb3": 12}
REGION = {"maincpu": "CPS1_R_MAIN", "gfx": "CPS1_R_GFX", "audiocpu": "CPS1_R_SOUND", "oki": "CPS1_R_OKI", "qsound": "CPS1_R_QSOUND"}
IGNORED_REGIONS = {"user1",  # bootlegs' "unknown (bootleg priority?)": no code reads it
                   "protection_pic",  # sf2ceblp's PIC: its protection is init_sf2ceblp's
                   "aboardplds", "bboardplds", "cboardplds", "dboardplds", "plds", "pal", "patchpld", "stars", "audiorom_raw"}
INITS = {"empty_init": "CPS1_INIT_NONE", "init_sf2ee": "CPS1_INIT_NONE", "init_wof": "CPS1_INIT_WOF", "init_dino": "CPS1_INIT_DINO",
         "init_punisher": "CPS1_INIT_PUNISHER", "init_slammast": "CPS1_INIT_SLAMMAST", "init_pang3": "CPS1_INIT_PANG3",
         "init_pang3b": "CPS1_INIT_PANG3B", "init_sf2hack": "CPS1_INIT_SF2HACK", "init_sf2rk": "CPS1_INIT_SF2RK",
         "init_sf2thndr": "CPS1_INIT_SF2THNDR", "init_sf2rb": "CPS1_INIT_SF2RB", "init_sf2rb2": "CPS1_INIT_SF2RB2",
         "init_sf2dongb": "CPS1_INIT_SF2DONGB", "init_sf2ceblp": "CPS1_INIT_SF2CEBLP", "init_pang3b4": "CPS1_INIT_PANG3B4",
         "init_dinohunt": "CPS1_INIT_DINOHUNT"}


def layout(g):
    """(rows, region sizes, stars) or a reason string; a row: (crc, chip size, region, load, offset, skip, len, name)."""
    files, stars = parse_rom(g["id"])
    rows, sizes = [], {}
    for region, op, name, off, size, crc, extras in files:
        if region in IGNORED_REGIONS:
            continue
        if crc is None and op != "ROM_FILL":
            return "a chip MAME lists as not dumped"
        if region not in REGION or op == "ROM_FILL":
            return "a ROM layout the loader cannot express"
        if region == "audiocpu":  # the Z80's first 32 KB, then its banks from $10000 (MAME) = $8000 here
            if off != 0 or size != 0x8000:
                return "a ROM layout the loader cannot express"
            total, used = size, size
            for e in extras:
                if e[0] == "ROM_CONTINUE" and e[1][0] == 0x10000 and used == total:
                    total += e[1][1]; used = total
                elif e[0] == "ROM_IGNORE":
                    total += e[1][0]
                else:
                    return "a ROM layout the loader cannot express"
            parts, load = [(0, 0, 0 if used == total else used)], "CPS1_LOAD_PLAIN"
        else:
            kinds = {"maincpu": {"ROM_LOAD16_BYTE": "BYTE", "ROM_LOAD16_WORD_SWAP": "CPS1_LOAD_SWAP16", "ROM_LOAD16_WORD": "CPS1_LOAD_PLAIN"},
                     "gfx": {"ROM_LOAD64_WORD": "CPS1_LOAD_GFX4", "ROM_LOAD64_BYTE": "CPS1_LOAD_GFX8", "ROM_LOAD32_BYTE": "CPS1_LOAD_BYTE4"}}
            load = kinds.get(region, {"ROM_LOAD": "CPS1_LOAD_PLAIN"}).get(op)
            if not load:
                return "a ROM layout the loader cannot express"
            total, consumed, parts = size, size, [(off, 0, size)]
            for e in extras:
                if e[0] == "ROM_CONTINUE":
                    parts.append((e[1][0], consumed, e[1][1])); consumed += e[1][1]; total += e[1][1]
                elif e[0] == "ROM_RELOAD":
                    parts.append((e[1][0], 0, e[1][1]))
                elif e[0] == "ROM_IGNORE":
                    total += e[1][0]
                else:
                    return "a ROM layout the loader cannot express"
            if len(parts) == 1 and total == size:
                parts = [(off, 0, 0)]  # the whole chip
        r = REGION[region]
        for poff, skip, ln in parts:
            pload = ("CPS1_LOAD_ODD" if poff & 1 else "CPS1_LOAD_EVEN") if load == "BYTE" else load
            n = ln or total
            foot = {"CPS1_LOAD_EVEN": n * 2 - 1, "CPS1_LOAD_ODD": n * 2 - 1, "CPS1_LOAD_GFX4": n * 4 - 2,
                    "CPS1_LOAD_GFX8": n * 8 - 7, "CPS1_LOAD_BYTE4": n * 4 - 3}.get(pload, n)
            sizes[r] = max(sizes.get(r, 0), poff + foot)
            rows.append((crc, total, r, pload, poff, skip, ln, name))
    return rows, sizes, stars


def left_reason(g):
    if g["machine"] == "qsound" and g["init"] not in INITS:
        return "its own init (%s)" % g["init"]
    if g["init"] not in INITS:
        return "its own init (%s)" % g["init"]
    if g["machine"] in ("sf2m3", "sf2m10", "sf2cems6", "varthb2", "varthb3"):
        return "its own memory map (MAME's %s machine)" % g["machine"]
    return None


def fmt_cpsb(v):
    def port(x):
        return "CPS1_NONE" if x < 0 else "0x%02X" % x
    return "{%s, 0x%04X, %s, %s, %s, %s, %s, {%s}, %s, {%s}}" % (
        port(v[0]), v[1] & 0xFFFF, port(v[2]), port(v[3]), port(v[4]), port(v[5]), port(v[9]),
        ", ".join(port(x) for x in v[10:14]), port(v[14]), ", ".join("0x%02X" % x for x in v[15:20]))


def fmt_mapper(name):
    banks, tname = mapper_banks[name]
    rs = mapper_ranges[tname]
    return "{{%s}, %d, {%s}}" % (", ".join("0x%X" % b for b in banks), len(rs), ", ".join(
        "{%s, 0x%04X, 0x%04X, %d}" % (" | ".join(t.replace("GFXTYPE_", "CPS1_GFX_") for t in types), s, e, b) for types, s, e, b in rs))


def main():
    out_path = sys.argv[2]
    by_id = {g["id"]: g for g in games}
    entries, left = [], []
    for g in games:
        reason = left_reason(g)
        lay = None
        if not reason:
            lay = layout(g)
            if isinstance(lay, str):
                reason = lay
        if not reason and g["id"] not in config:
            reason = "no CPS-B config in MAME's table"
        if reason:
            left.append((g, reason))
            continue
        entries.append((g, lay))
    used_b = sorted({config[g["id"]][0] for g, _ in entries})
    used_m = sorted({config[g["id"]][1] for g, _ in entries})
    o = []
    o.append(HEADER)
    o.append("/* Graphics ROM mappers: bank sizes, then ranges (layers, first, last, bank)\n * in 64-byte units (cps1.h). */")
    for m in used_m:
        o.append("#define %s %s" % (m.upper().replace("MAPPER_", "MAPPER_"), fmt_mapper(m)))
    o.append("")
    o.append("/* CPS-B configs (MAME's CPS_B_* and, for hacks and bootlegs, HACK_B_*): ID port and value,\n"
             " * multiplier ports, layer control, priority masks, palette control, layer enable bits (cps1.h). */")
    for b in used_b:
        o.append("#define %s %s" % (b.replace("CPS_B_", "CPSB_"), fmt_cpsb(cpsb[b])))
    o.append("")
    o.append("const Cps1Game cps1_games[] = {")
    for g, (rows, sizes, stars) in entries:
        gid = g["id"]
        b, mp, (in2, in3, _out2, kludge) = config[gid]
        parent = g["parent"]
        parent_crcs = set()
        if parent:
            prow = layout(by_id[parent])
            if not isinstance(prow, str):
                parent_crcs = {r[0] for r in prow[0]}
            else:
                parent_crcs = {f[5] for f in parse_rom(parent)[0] if f[5] is not None}
        ports = ports_of(g["input"])
        dips = [port_value(ports.get(p, {})) if p in ports else 0xFF for p in ("DSWA", "DSWB", "DSWC")]
        in2p = ports.get("IN2", {})
        kinds = " ".join(k for _, k in in2p.values())
        in3p = " ".join(k for _, k in ports.get("IN3", {}).values())
        extra = ("CPS1_EXTRA_KICKS" if "BUTTON4" in kinds else "CPS1_EXTRA_P4" if "/P4" in in3p else
                 "CPS1_EXTRA_P3" if "/P3" in kinds else "CPS1_EXTRA_NONE")
        z80_raw = 1 if re.search(r'"audiorom_raw"', roms[gid]) else 0
        group = "CPS1_QSOUND" if g["machine"] == "qsound" else "CPS1_PLAIN"
        reg = [sizes.get(r, 0) // 1024 for r in ("CPS1_R_MAIN", "CPS1_R_GFX", "CPS1_R_SOUND", "CPS1_R_OKI")]
        if group == "CPS1_QSOUND":
            reg[3] = sizes.get("CPS1_R_QSOUND", 0) // 1024
        o.append("    /* MAME %s (%s), %s %s */" % (gid, g["machine"], b, mp))
        o.append("    {\"%s\", %s, %s, {%s}, %s, %d, {" % (gid, g["title"], group, ", ".join("%d * K" % x for x in reg),
                                                         b.replace("CPS_B_", "CPSB_"), len(rows)))
        for crc, total, r, load, off, skip, ln, name in rows:
            o.append("        {0x%08x, %d * K, %s, %s, 0x%06X, %s, %s, %d},  /* %s */" % (
                crc, total // 1024, r, load, off, "0x%06X" % skip if skip else "0", "0x%06X" % ln if ln else "0",
                1 if crc in parent_crcs else 0, name))
        o.append("    }, %s, %d, {%s}, %s, %s, %s, %d, %s, %s, %d, %d, %s, %d, %s}," % (
            mp.upper(), MACHINE_MHZ[g["machine"]], ", ".join("0x%02X" % d for d in dips),
            "0x%02X" % in2 if in2 else "CPS1_NONE", "0x%02X" % in3 if in3 else "CPS1_NONE",
            '"%s"' % parent if parent else "NULL", 1 if g["machine"] == "forgottn" else 0,
            "0x%06X" % stars if stars >= 0 else "-1", extra, 270 if g["rot"] == "ROT270" else 0,
            1 if g["init"] == "init_sf2ee" else 0, INITS[g["init"]], z80_raw, "0x%02X" % kludge if kludge else "0"))
    o.append("};")
    o.append("const int cps1_game_count = (int)(sizeof cps1_games / sizeof cps1_games[0]);")
    open(out_path, "w", encoding="utf-8", newline="\n").write("\n".join(o) + "\n")
    if "--left" in sys.argv:
        rows = ["| %s | %s | %s |" % (g["id"], g["title"].strip('"').replace('\\"', '"'), r) for g, r in sorted(left, key=lambda x: x[0]["id"])]
        open(sys.argv[sys.argv.index("--left") + 1], "w").write("\n".join(rows) + "\n")
    print("%d sets, %d left out" % (len(entries), len(left)))


HEADER = """/* The game table: where each chip of a game goes, which CPS-B and graphics
 * ROM mapper (PAL) its board has, its 68000's clock, its DIP switch
 * defaults and extra inputs (cps1.h). The layouts, configs, mappers and DIP
 * defaults and CRCs are MAME 0.289's (cps1.cpp, cps1_v.cpp; docs/sources.md):
 * every set it lists on these boards, generated. Keep the layout: the build's
 * detection reads this file (cmake/detect_system.cmake). */
#include "cps1.h"

#define K 1024
"""

main()
