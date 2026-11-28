"""The site's game data, from boot runs (local only: it needs the games).

python tools/site_data.py SYSTEM FOLDER... [--frames N] [--images DIR] [--upload]

Runs every game of FOLDER in SYSTEM's headless program, sorts it into boots /
partial / not yet, writes DIR/data/SYSTEM.json and a 256-wide
WebP title screen per game into DIR/SYSTEM/ (never committed). --upload zips
DIR and replaces site-images.zip on the release "site-images", which the Pages
workflow downloads. Needs Pillow; 7-Zip for .7z archives.
"""
import argparse, concurrent.futures, datetime, hashlib, json, os, re, shutil, subprocess, sys, tempfile, zipfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUILD = os.environ.get("RETROCAST_BUILD", os.path.join(ROOT, "build"))
EXE = ".exe" if os.name == "nt" else ""
SEVENZIP = shutil.which("7z") or r"C:\Program Files\7-Zip\7z.exe"
# program, the game files it takes, frames to the title screen, whether it is played (play_args)
SYSTEMS = {
    "nes": ("nes_headless", (".nes",), 300, True),
    "gb": ("gb_headless", (".gb", ".gbc"), 900, True),
    "genesis": ("genesis_headless", (".md", ".gen", ".bin", ".smd"), 1200, True),
    "mastersystem": ("sms_headless", (".sms", ".gg"), 600, True),
    "atari2600": ("atari2600_headless", (".a26", ".bin"), 300, True),
    "cps1": ("cps1_headless", (".zip",), 1200, True),
    "cps2": ("cps2_headless", (".zip",), 1950, False),
}
STOPPED = re.compile(r"\bhalted\b|jammed=1|result: (halted|locked)")
RANK = {"ok": 0, "partial": 1, "no": 2}
NOT_GAMES = re.compile(r"\[BIOS\]|\(Pirate\)|\(Test Program\)|\(Program\)")  # BIOSes, pirate copies, test carts


def skipped(name):
    return bool(NOT_GAMES.search(name))


def cps1_unsupported():
    """{set: title} of the CPS-1 sets games.c doesn't hold, from systems/cps1/docs/unsupported.md."""
    with open(os.path.join(ROOT, "systems", "cps1", "docs", "unsupported.md"), encoding="utf-8") as f:
        part = f.read()
    return {s: t for s, t in re.findall(r"^\| (\w+) \| (.+?) \| .+ \|$", part, re.M) if s != "Set"}


def colours(ppm):
    """Distinct colours of a binary PPM (P6), or 0 if it isn't one."""
    parts = ppm.split(maxsplit=4)
    if len(parts) < 5 or parts[0] != b"P6":
        return 0
    px = parts[4]
    return len({px[i:i + 3] for i in range(0, len(px) - 2, 3)})


def classify(returncode, stdout, ppm):
    ran = returncode == 0 or "result: timeout" in stdout  # gb_headless exits 1 when no test-ROM result came: a game ran
    if not ran or ppm is None or STOPPED.search(stdout):
        return "no"
    return "partial" if colours(ppm) <= 2 else "ok"


def title_of(name):
    return name.split(" (")[0].strip()


def _region_first(name):
    return (0 if re.search(r"\((World|USA)", name) else 1, name)


def group(names):
    """No-Intro names -> {title: [names]}, the World or USA versions first."""
    out = {}
    for n in names:
        out.setdefault(title_of(n), []).append(n)
    return {t: sorted(v, key=_region_first) for t, v in out.items()}


def cps1_groups():
    """{title: [set ids]} from games.c: a parent and its clones, the parent first."""
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import cps1_audit
    t = cps1_audit.table()
    title = {gid: name for gid, name, *_ in t}
    by = {}
    for gid, _, parent, *_ in t:
        by.setdefault(parent if parent in title else gid, []).append(gid)
    return {title_of(title[p]): [p] + [c for c in v if c != p] for p, v in by.items()}


def image_name(gid):
    slug = re.sub(r"[^a-z0-9]+", "-", gid.lower()).strip("-")[:40]
    return slug if slug == gid else f"{slug}-{hashlib.sha1(gid.encode()).hexdigest()[:6]}"


def thumbnail(ppm_path, out_path):
    from PIL import Image, ImageDraw, ImageFont
    im = Image.open(ppm_path).convert("RGB")
    im = im.resize((256, round(im.height * 256 / im.width)), Image.LANCZOS)
    d = ImageDraw.Draw(im, "RGBA")
    font = ImageFont.load_default(size=10)
    text = "© its owner"
    w = d.textlength(text, font=font)
    d.text((im.width - w - 4, im.height - 14), text, font=font, fill=(255, 255, 255, 150),
           stroke_width=1, stroke_fill=(0, 0, 0, 150))
    os.makedirs(os.path.dirname(out_path), exist_ok=True)
    im.save(out_path, "WEBP", quality=80, method=6)


def input_variants(system):
    """The inputs tried in turn while the screen stays blank. The Genesis is left alone first, then Start is
    pressed (as the build's traces do): pressing can land some games on a black menu."""
    if system == "nes":
        return [["--play", "1"]]  # the NES's --play takes a seed
    if system == "genesis":
        return [[], [a for f in (300, 500, 700, 900, 1100, 1500, 2000, 2500, 3000) for a in ("--press", f"{f}:08")]]
    return [["--play"]]


def attempts(frames):
    """Frame counts to try while the screen is blank: some intros are long, some attract loops blank a while."""
    return list(dict.fromkeys((frames, frames * 5 // 4, frames * 2, frames * 5, max(frames * 5, 6000))))


def pick_rom(folder, exts):
    """The game in an unpacked archive: the largest file of the system's kinds (an archive may hold a patch too)."""
    found = [os.path.join(folder, f) for f in os.listdir(folder) if f.lower().endswith(exts)]
    return max(found, key=os.path.getsize) if found else None


def run_one(system, path, frames, tmp):
    prog, _, _, play = SYSTEMS[system]
    work = tempfile.mkdtemp(dir=tmp)
    rom = path
    if system != "cps1" and path.lower().endswith((".7z", ".zip")):
        subprocess.run([SEVENZIP, "e", "-y", "-o" + work, path], capture_output=True)
        rom = pick_rom(work, SYSTEMS[system][1])
        if not rom:
            return "no", None, ""
    ppm = os.path.join(work, "f.ppm")
    for n, inputs in [(n, i) for i in (input_variants(system) if play else [[]]) for n in attempts(frames)]:
        if os.path.exists(ppm):
            os.remove(ppm)
        cmd = [os.path.join(BUILD, prog + EXE), rom, "--frames", str(n), "--ppm", ppm] + inputs
        try:
            r = subprocess.run(cmd, capture_output=True, text=True, timeout=600, errors="replace")
            code, out = r.returncode, r.stdout
        except subprocess.TimeoutExpired:
            code, out = 1, ""
        data = None
        if os.path.exists(ppm):
            with open(ppm, "rb") as f:
                data = f.read()
        st = classify(code, out, data)
        if st != "partial":
            break
    return st, (ppm if data else None), out


def collect(system, folder):
    """{id: path} of the games in folder."""
    exts = SYSTEMS[system][1]
    out = {}
    if system == "cps1":  # MAME sets: the folder itself
        return {f[:-4]: os.path.join(folder, f) for f in sorted(os.listdir(folder)) if f.lower().endswith(".zip")}
    for root, _, files in os.walk(folder):  # consoles: subfolders too (0-9/, A/, ...)
        for f in sorted(files):
            stem, ext = os.path.splitext(f)
            if ext.lower() in exts + (".7z", ".zip") and not skipped(stem):
                out[stem] = os.path.join(root, f)
    return out


def cps2_site(folders, frames, images):
    from cps2_boot import probe
    from cps2_rom_audit import TABLE, read_table, stack

    catalog = read_table(TABLE)
    groups = {}
    for gid in catalog:
        parent = tuple(stack(catalog, gid))[-1]
        parent = parent if parent in catalog else gid
        groups.setdefault(parent, []).append(gid)
    runner = os.path.abspath(os.path.join(BUILD, "cps2_headless" + EXE))
    if not os.path.isfile(runner):
        raise FileNotFoundError(runner)
    folders = [os.path.abspath(folder) for folder in folders]

    def statuses(gid):
        for folder in folders:
            if probe(runner, folder, gid, 10)[0] == "Boot progress":
                return folder
        return None

    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as pool:
        booted = dict(zip(catalog, pool.map(statuses, catalog)))

    def entry(item):
        parent, members = item
        versions = [parent] + sorted(gid for gid in members if gid != parent)
        compatible = [gid for gid in versions if booted[gid]]
        image = None
        if compatible:
            gid = compatible[0]
            with tempfile.TemporaryDirectory() as work:
                ppm = os.path.join(work, "frame.ppm")
                env = {k: v for k, v in os.environ.items()
                       if k not in {"CPS2_PLAY", "CPS2_PCM", "CPS2_BOOT_PROBE",
                                    "CPS2_OPCODE_IMAGE", "CPS2_EXECUTED_PCS"}}
                env["CPS2_FRAME"] = ppm
                for n in (frames, frames + 120, frames + 240):
                    result = subprocess.run([runner, booted[gid], gid, str(n * 262 * 1024)],
                                            env=env, capture_output=True, timeout=120)
                    if result.returncode == 0 and os.path.isfile(ppm):
                        with open(ppm, "rb") as file:
                            usable = colours(file.read()) > 2
                        if usable:
                            image = image_name(gid)
                            thumbnail(ppm, os.path.join(images, "cps2", image + ".webp"))
                            break
        return {"title": title_of(catalog[parent]["title"]), "id": parent,
                "status": "ok" if compatible else "no", "versions": versions, "image": image,
                "failing": [gid for gid in versions if not booted[gid]]}

    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as pool:
        return list(pool.map(entry, groups.items()))


def make(system, folders, frames=None, images=None):
    frames = frames or SYSTEMS[system][2]
    if system == "cps2":
        write_data(system, cps2_site(folders, frames, images), images)
        return
    games = {}
    for folder in folders:
        games.update(collect(system, folder))
    if system == "cps1":
        groups = {t: [v for v in vs if v in games] for t, vs in cps1_groups().items()}
        groups = {t: vs for t, vs in groups.items() if vs}
    else:
        groups = group(list(games))
    result = {}
    with tempfile.TemporaryDirectory() as tmp, concurrent.futures.ThreadPoolExecutor(os.cpu_count()) as ex:
        def job(gid):
            st, ppm, _ = run_one(system, games[gid], frames, tmp)
            img = None
            if ppm and images and st == "ok":
                img = image_name(gid)
                thumbnail(ppm, os.path.join(images, system, img + ".webp"))
            return gid, st, img
        for gid, st, img in ex.map(job, [g for vs in groups.values() for g in vs]):
            result[gid] = (st, img)
            print(f"{st:8} {gid}", flush=True)
    if system == "cps1":  # the sets games.c can't run yet are listed too, as not yet
        for s, t in cps1_unsupported().items():
            groups.setdefault(title_of(t), []).append(s)
            result[s] = ("no", None)
    entries = []
    for t, vs in groups.items():
        st = min((result[v][0] for v in vs), key=RANK.get)
        img = next((result[v][1] for v in vs if result[v][1]), None)
        entries.append({"title": t, "id": vs[0], "status": st, "versions": vs, "image": img,
                        "failing": [v for v in vs if result[v][0] != "ok"]})
    write_data(system, entries, images)


def write_data(system, entries, images):
    entries.sort(key=lambda e: e["title"].lower())
    data = {"system": system, "made": datetime.date.today().isoformat(), "games": entries}
    path = os.path.join(images, "data", system + ".json")
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        json.dump(data, f, ensure_ascii=False, indent=0)
        f.write("\n")
    n = {k: sum(e["status"] == k for e in entries) for k in RANK}
    print(f"{system}: {len(entries)} games, {n} -> {path}")


def upload(images):
    z = os.path.join(tempfile.gettempdir(), "site-images.zip")
    with zipfile.ZipFile(z, "w", zipfile.ZIP_STORED) as zf:  # WebP is already compressed
        for root, _, files in os.walk(images):
            for f in files:
                if f.endswith((".webp", ".json")):
                    p = os.path.join(root, f)
                    zf.write(p, os.path.relpath(p, images).replace(os.sep, "/"))
    if subprocess.run(["gh", "release", "view", "site-images"], capture_output=True).returncode:
        subprocess.run(["gh", "release", "create", "site-images", "--latest=false", "--title", "Site images",
                        "--notes", "Only the website's small title-screen pictures (no games). Replaced by tools/site_data.py --upload."],
                       check=True)
    subprocess.run(["gh", "release", "upload", "site-images", z, "--clobber"], check=True)
    print("uploaded", z)
    # replacing an asset fires no release event: start the site build by hand
    subprocess.run(["gh", "workflow", "run", "pages.yml"])


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("system", choices=sorted(SYSTEMS))
    ap.add_argument("folders", nargs="+")
    ap.add_argument("--frames", type=int)
    ap.add_argument("--images", default=os.path.join(ROOT, "site-images"))
    ap.add_argument("--upload", action="store_true")
    a = ap.parse_args(argv)
    make(a.system, a.folders, a.frames, a.images)
    if a.upload:
        upload(a.images)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
