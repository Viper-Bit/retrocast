import json, os, sys, tempfile, unittest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "tools"))
import site_build

TITLE = 'Ghouls\'n <Ghosts> & "Pokémon"'


def game(title, gid, status="ok", image=None):
    return {"title": title, "id": gid, "status": status, "versions": [gid], "image": image}


class SiteBuild(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.data = os.path.join(self.tmp.name, "data")
        self.imgs = os.path.join(self.tmp.name, "imgs")
        self.out = os.path.join(self.tmp.name, "out")
        os.makedirs(self.data)
        os.makedirs(os.path.join(self.imgs, "cps1"))

    def tearDown(self):
        self.tmp.cleanup()

    def put(self, sysid, games):
        with open(os.path.join(self.data, sysid + ".json"), "w", encoding="utf-8") as f:
            json.dump({"system": sysid, "made": "2026-11-26", "games": games}, f)

    def pic(self, name):
        with open(os.path.join(self.imgs, "cps1", name + ".webp"), "wb") as f:
            f.write(b"RIFF")

    def build(self, release=None):
        site_build.build(self.out, self.data, self.imgs, release or {"tag": "v0", "assets": []})

    def read(self, *p):
        with open(os.path.join(self.out, *p), encoding="utf-8") as f:
            return f.read()

    def test_home_and_pages(self):
        self.put("cps1", [game("Final Fight", "ffight")])
        self.put("nes", [game("Tetris", "Tetris (World)", "no")])
        self.build()
        home = self.read("index.html")
        self.assertIn("Capcom Play System I", home)
        self.assertIn("NES / Famicom", home)
        self.assertIn("1 of 1 play", home)
        self.assertIn("0 of 1 play", home)
        for s in ("cps1", "nes"):
            self.assertTrue(os.path.exists(os.path.join(self.out, s, "index.html")))
            self.assertEqual(json.loads(self.read("data", s + ".json"))["system"], s)

    def test_no_data_system(self):
        self.put("cps1", [game("Final Fight", "ffight")])
        self.build()
        self.assertIn("not tested yet", self.read("index.html"))
        self.assertIn("No games tested yet", self.read("gb", "index.html"))

    def test_missing_image(self):
        self.pic("ffight")
        self.put("cps1", [game("Final Fight", "ffight", image="ffight"), game("Strider", "strider", image="strider")])
        self.build()
        g = {x["id"]: x for x in json.loads(self.read("data", "cps1.json"))["games"]}
        self.assertEqual(g["ffight"]["image"], "ffight")
        self.assertIsNone(g["strider"]["image"])
        self.assertTrue(os.path.exists(os.path.join(self.out, "img", "cps1", "ffight.webp")))

    def test_escaping(self):
        self.put("cps1", [game(TITLE, "ghouls", image="ghouls")])
        self.pic("ghouls")
        self.build()
        for root, _, files in os.walk(self.out):
            for f in files:
                if f.endswith(".html"):
                    with open(os.path.join(root, f), encoding="utf-8") as h:
                        self.assertNotIn("<Ghosts>", h.read())
        self.assertEqual(json.loads(self.read("data", "cps1.json"))["games"][0]["title"], TITLE)

    def test_release_links(self):
        names = ["retrocast-v0.7.1-windows-x64.zip", "retrocast-v0.7.1-linux-arm64.tar.gz"]
        self.build({"tag": "v0.7.1", "assets": names})
        home = self.read("index.html")
        for n in names:
            self.assertIn("https://github.com/Viper-Bit/retrocast/releases/download/v0.7.1/" + n, home)
        site_build.build(self.out, self.data, self.imgs, None, fetch=False)
        home = self.read("index.html")
        self.assertIn("https://github.com/Viper-Bit/retrocast/releases", home)
        self.assertNotIn("releases/download/", home)


if __name__ == "__main__":
    unittest.main()
