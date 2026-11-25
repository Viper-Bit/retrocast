"""The site's game data, from boot runs (local only: it needs the games).

python tools/site_data.py SYSTEM FOLDER [--frames N] [--images DIR] [--upload]

Runs every game of FOLDER in SYSTEM's headless program, sorts it into boots /
partial / not yet, writes site/data/SYSTEM.json (committed) and a 256-wide
WebP title screen per game into DIR/SYSTEM/ (never committed). --upload zips
DIR and replaces site-images.zip on the release "site-images", which the Pages
workflow downloads. Needs Pillow; 7-Zip for .7z archives.
"""
import argparse, concurrent.futures, datetime, hashlib, json, os, re, shutil, subprocess, sys, tempfile, zipfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUILD = os.path.join(ROOT, "build")
EXE = ".exe" if os.name == "nt" else ""
SEVENZIP = shutil.which("7z") or r"C:\Program Files\7-Zip\7z.exe"
# program, the game files it takes, frames to the title screen, whether it has --play
SYSTEMS = {
    "nes": ("nes_headless", (".nes",), 300, True),
    "gb": ("gb_headless", (".gb", ".gbc"), 900, True),
    "genesis": ("genesis_headless", (".md", ".gen", ".bin", ".smd"), 1200, False),
    "mastersystem": ("sms_headless", (".sms", ".gg"), 600, True),
    "atari2600": ("atari2600_headless", (".a26", ".bin"), 300, True),
    "cps1": ("cps1_headless", (".zip",), 1200, True),
}
STOPPED = re.compile(r"\bhalted\b|jammed=1|result: (halted|locked)")
RANK = {"ok": 0, "partial": 1, "no": 2}


def colours(ppm):
    """Distinct colours of a binary PPM (P6), or 0 if it isn't one."""
    parts = ppm.split(maxsplit=4)
    if len(parts) < 5 or parts[0] != b"P6":
        return 0
    px = parts[4]
    return len({px[i:i + 3] for i in range(0, len(px) - 2, 3)})


def classify(returncode, stdout, ppm):
    if returncode != 0 or ppm is None or STOPPED.search(stdout):
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


def run_one(system, path, frames, tmp):
    prog, _, _, play = SYSTEMS[system]
    work = tempfile.mkdtemp(dir=tmp)
    rom = path
    if system != "cps1" and path.lower().endswith((".7z", ".zip")):
        subprocess.run([SEVENZIP, "e", "-y", "-o" + work, path], capture_output=True)
        found = [f for f in os.listdir(work) if f.lower().endswith(SYSTEMS[system][1])]
        if not found:
            return "no", None, ""
        rom = os.path.join(work, found[0])
    ppm = os.path.join(work, "f.ppm")
    for n in (frames, frames * 5):  # one retry, five times as long, when the screen is blank (long intros)
        if os.path.exists(ppm):
            os.remove(ppm)
        cmd = [os.path.join(BUILD, prog + EXE), rom, "--frames", str(n), "--ppm", ppm] + (["--play"] if play else [])
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
    for f in sorted(os.listdir(folder)):
        stem, ext = os.path.splitext(f)
        if system == "cps1":
            if ext.lower() == ".zip":
                out[stem] = os.path.join(folder, f)
        elif ext.lower() in exts + (".7z", ".zip"):
            out[stem] = os.path.join(folder, f)
    return out


def make(system, folder, frames=None, images=None):
    frames = frames or SYSTEMS[system][2]
    games = collect(system, folder)
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
    entries = []
    for t, vs in groups.items():
        st = min((result[v][0] for v in vs), key=RANK.get)
        img = next((result[v][1] for v in vs if result[v][1]), None)
        entries.append({"title": t, "id": vs[0], "status": st, "versions": vs, "image": img})
    entries.sort(key=lambda e: e["title"].lower())
    data = {"system": system, "made": datetime.date.today().isoformat(), "games": entries}
    path = os.path.join(ROOT, "site", "data", system + ".json")
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
                if f.endswith(".webp"):
                    p = os.path.join(root, f)
                    zf.write(p, os.path.relpath(p, images).replace(os.sep, "/"))
    if subprocess.run(["gh", "release", "view", "site-images"], capture_output=True).returncode:
        subprocess.run(["gh", "release", "create", "site-images", "--latest=false", "--title", "Site images",
                        "--notes", "Only the website's small title-screen pictures (no games). Replaced by tools/site_data.py --upload."],
                       check=True)
    subprocess.run(["gh", "release", "upload", "site-images", z, "--clobber"], check=True)
    print("uploaded", z)


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("system", choices=sorted(SYSTEMS))
    ap.add_argument("folder")
    ap.add_argument("--frames", type=int)
    ap.add_argument("--images", default=os.path.join(ROOT, "site-images"))
    ap.add_argument("--upload", action="store_true")
    a = ap.parse_args(argv)
    make(a.system, a.folder, a.frames, a.images)
    if a.upload:
        upload(a.images)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
