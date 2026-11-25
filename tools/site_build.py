"""Build the static site (GitHub Pages) from site/, its data and the thumbnails.

python tools/site_build.py OUT [--images DIR]

Templates + the game lists and thumbnails (DIR/data/<system>.json and DIR/<system>/, from the release asset
site-images.zip, unpacked to DIR) + the latest release's file names.
Standard library only: CI installs nothing.
"""
import argparse, html, json, os, re, shutil, subprocess, sys
from string import Template

REPO = "Viper-Bit/retrocast"
SITE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "site")
RELEASES = f"https://github.com/{REPO}/releases"
ASSET = re.compile(r"^retrocast-.+-(windows|linux|macos)-(x64|arm64)\.(zip|tar\.gz)$")
OS = {"windows": "win", "linux": "linux", "macos": "mac"}
FOOTER = """<footer><p>retrocast · GPL-3.0 · No games are included or linked: use your own legally dumped games. · Built from the repository by GitHub Actions.</p>
<p>Game names, title screens and trademarks belong to their owners; the small title screens only show which games the program runs.</p></footer>"""


def latest_release():
    """{"tag", "assets"} of the latest release, or None when it can't be read."""
    try:
        r = subprocess.run(["gh", "api", f"repos/{REPO}/releases/latest"], capture_output=True, text=True, timeout=60)
        j = json.loads(r.stdout)
        return {"tag": j["tag_name"], "assets": [a["name"] for a in j["assets"]]}
    except Exception:
        return None


def builds(release):
    out = []
    for name in (release or {}).get("assets", []):
        m = ASSET.match(name)
        if m:
            os_, arch = OS[m.group(1)], m.group(2)
            out.append({"os": os_, "arch": "Apple Silicon" if os_ == "mac" and arch == "arm64" else "Intel" if os_ == "mac" else arch.upper(), "file": name,
                        "url": f"{RELEASES}/download/{release['tag']}/{name}"})
    order = ["win", "linux", "mac"]
    return sorted(out, key=lambda b: (order.index(b["os"]), b["arch"] != "X64"))


def js(obj):
    """JSON safe inside a <script> element."""
    return json.dumps(obj, ensure_ascii=False).replace("<", "\\u003c").replace(">", "\\u003e").replace("&", "\\u0026")


def load(path):
    with open(path, encoding="utf-8") as f:
        return json.load(f)


def write(path, text):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write(text)


def build(out_dir, data_dir=None, images_dir=None, release=None, fetch=True):
    data_dir = data_dir or os.path.join(images_dir or "", "data")  # the lists ship in site-images.zip
    if release is None and fetch:
        release = latest_release()
    systems = load(os.path.join(SITE, "systems.json"))
    tpl = {n: Template(open(os.path.join(SITE, n), encoding="utf-8").read()) for n in ("index.html", "system.html")}
    if os.path.isdir(out_dir):
        shutil.rmtree(out_dir)
    os.makedirs(out_dir)
    for f in ("style.css", "app.js"):
        shutil.copy(os.path.join(SITE, f), out_dir)
    common = {"builds": builds(release), "tag": release["tag"] if release else "", "releases": RELEASES}

    cards, wall, total = [], [], 0
    for s in systems:
        sid, e = s["id"], html.escape
        p = os.path.join(data_dir, sid + ".json")
        data = load(p) if os.path.exists(p) else None
        games = data["games"] if data else []
        for g in games:  # keep a picture only if the thumbnails have it
            g.setdefault("image", None)
            if g.get("image") and not (images_dir and os.path.exists(os.path.join(images_dir, sid, g["image"] + ".webp"))):
                g["image"] = None
            if g.get("image"):
                os.makedirs(os.path.join(out_dir, "img", sid), exist_ok=True)
                shutil.copy(os.path.join(images_dir, sid, g["image"] + ".webp"), os.path.join(out_dir, "img", sid))
        if data:
            write(os.path.join(out_dir, "data", sid + ".json"), json.dumps(data, ensure_ascii=False))
        n = {k: sum(g["status"] == k for g in games) for k in ("ok", "partial", "no")}
        total += len(games)
        pics = [f"img/{sid}/{g['image']}.webp" for g in games if g.get("image") and g["status"] == "ok"]
        wall += pics[:4]
        pic = f'<img src="{e(pics[0])}" alt="">' if pics else ""
        if games:
            num = f'<span>{n["ok"]} of {len(games)} play</span><span>View games →</span>'
            bar = f'<div class="bar"><i data-w="{100 * n["ok"] / len(games):.1f}"></i></div>'
        else:
            num, bar = '<span>not tested yet</span>', '<div class="bar"><i data-w="0"></i></div>'
        cards.append(f'\n    <a class="sys" href="{sid}/"><div class="pic">{pic}</div><div class="body"><h3>{e(s["name"])}</h3>'
                     f'<div class="cpu">{e(s["cpu"])}</div>{bar}<div class="num">{num}</div></div></a>')

        if games:
            body = (f'<div class="tools"><div class="search"><input id="q" placeholder="Search {len(games)} {e(s["name"])} games…" aria-label="Search"></div>'
                    '<span class="chip on" data-f="all">All</span><span class="chip" data-f="ok">Boots</span>'
                    '<span class="chip" data-f="partial">Partial</span><span class="chip" data-f="no">Not yet</span>'
                    '<div class="view"><button id="v-grid" class="on" aria-label="Grid">▦</button><button id="v-list" aria-label="List">☰</button></div></div>'
                    '<div class="az" id="az"></div><div id="out"></div>')
        else:
            body = '<p class="sub">No games tested yet on this system. The list fills in when the boot runs are made.</p>'
        made = f' · tested {e(data["made"])}' if data and data.get("made") else ""
        write(os.path.join(out_dir, sid, "index.html"), tpl["system.html"].substitute(
            name=e(s["name"]), cpu=e(s["cpu"]), made=made, body=body, footer=FOOTER, **n,
            site=js(dict(common, id=sid, games=len(games)))))

    tag = release["tag"] if release else ""
    badges = f"<span>{len(systems)} systems</span>" + (f"<span>{total:,} games boot-tested</span>" if total else "") + \
             "<span>cycle-checked against an interpreter</span>"
    tagline = (f"{html.escape(tag)} · " if tag else "") + "the emulator, a headless program and a recompiler per system, and the kit to recompile your own games."
    write(os.path.join(out_dir, "index.html"), tpl["index.html"].substitute(
        badges=badges, cards="".join(cards), tagline=tagline, footer=FOOTER, site=js(dict(common, wall=wall))))
    write(os.path.join(out_dir, ".nojekyll"), "")


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("out")
    ap.add_argument("--images", help="the unpacked thumbnails: <dir>/<system>/<image>.webp")
    a = ap.parse_args(argv)
    build(a.out, images_dir=a.images)
    print("site built in", a.out)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
