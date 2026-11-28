# The website

`https://viper-bit.github.io/retrocast/`, built by `.github/workflows/pages.yml`
on a push to `main` that touches `site/`, on a published release, and by hand.

- `index.html`, `system.html`, `style.css`, `app.js`: the templates and their
  styles and scripts; `systems.json`: the systems, in order.
- The game lists and title screens are **never committed**: they live only in
  `site-images.zip` on the release `site-images`, as `data/<system>.json`
  (every game tested, its status: boots, partial: runs with a blank screen,
  not yet: fails to load or halts; its versions, the failing ones marked) and
  `<system>/<image>.webp`. BIOSes, pirate copies and test carts are left out.
- No game, and no link to one, is ever part of the site.

## Refreshing a system's list (where the games are)

    python tools/site_data.py cps1 "D:/roms/CAPCOM - Play System I"
    python tools/site_data.py cps2 "<ROM-FOLDER>"
    python tools/site_data.py mastersystem "D:/roms/Sega - Master System - Mark III" --upload

It runs every game in the system's headless program (`build/`), writes
`site-images/data/<system>.json` and the thumbnails into `site-images/<system>/`
(256 px WebP, about 8 KB, marked "© its owner"). `--upload` replaces
`site-images.zip` on the release with everything in `site-images/`, so keep
that folder whole. The upload redeploys the site; nothing to commit.

## Building it locally

    python tools/site_build.py _site --images site-images
    python -m http.server -d _site

The download menu lists the latest release's files, read from GitHub (`gh`).
