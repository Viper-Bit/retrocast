"use strict";
const S = window.SITE, $ = s => document.querySelector(s);
const esc = s => String(s).replace(/[&<>"']/g, c => ({"&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;"}[c]));
const OSI = {
 win: '<svg viewBox="0 0 24 24"><path d="M3 5.5l7.5-1v7H3zm8.5-1.2L21 3v8.5h-9.5zM3 12.5h7.5v7L3 18.5zm8.5 0H21V21l-9.5-1.3z"/></svg>',
 linux: '<svg viewBox="0 0 24 24"><path d="M12 2c-2.2 0-3.6 1.9-3.6 4.6 0 1.6.4 2.6-.6 4.3-1 1.6-2.8 3.4-2.8 6 0 .7.2 1.3.5 1.8-.8.3-1.5.9-1.5 1.6C4 21.6 6 22 8 22c1.4 0 2.4-.4 3-.9.3.1.7.1 1 .1s.7 0 1-.1c.6.5 1.6.9 3 .9 2 0 4-.4 4-1.6 0-.7-.7-1.3-1.5-1.6.3-.5.5-1.1.5-1.8 0-2.6-1.8-4.4-2.8-6-1-1.7-.6-2.7-.6-4.3C15.6 3.9 14.2 2 12 2zm-1.5 4a.8.8 0 110 1.6.8.8 0 010-1.6zm3 0a.8.8 0 110 1.6.8.8 0 010-1.6zM12 8.5l1.6 1.1L12 10.7l-1.6-1.1z"/></svg>',
 mac: '<svg viewBox="0 0 24 24"><path d="M16.4 12.6c0-2.4 2-3.6 2.1-3.7-1.1-1.7-2.9-1.9-3.5-1.9-1.5-.2-2.9.9-3.7.9-.8 0-1.9-.9-3.2-.8-1.6 0-3.1 1-4 2.4-1.7 3-.4 7.4 1.2 9.8.8 1.2 1.8 2.5 3 2.4 1.2 0 1.7-.8 3.2-.8s1.9.8 3.2.8c1.3 0 2.2-1.2 3-2.4.9-1.4 1.3-2.7 1.3-2.8-.1 0-2.6-1-2.6-3.9zM14 5.5c.7-.8 1.1-1.9 1-3-1 0-2.1.7-2.8 1.5-.6.7-1.2 1.8-1 2.9 1.1.1 2.1-.6 2.8-1.4z"/></svg>'};
const DL_ICON = '<svg viewBox="0 0 24 24"><path d="M11 3h2v10l3.5-3.5 1.4 1.4L12 16.8l-5.9-5.9 1.4-1.4L11 13zM4 19h16v2H4z"/></svg>';

/* the visitor's OS; null where there is no build (phones, tablets, others) */
function myOS() {
  const u = ((navigator.userAgentData && navigator.userAgentData.platform) || navigator.userAgent).toLowerCase();
  if (/android|iphone|ipad|ipod|cros|bsd/.test(u)) return null;
  return u.includes("win") ? "win" : u.includes("mac") ? "mac" : /linux|x11/.test(u) ? "linux" : null;
}
const OSNAME = {win: "Windows", linux: "Linux", mac: "macOS"};

function dlButton(id) {
  const el = document.getElementById(id); if (!el) return;
  const os = myOS(), B = S.builds, b = B.find(x => x.os == os);
  const main = b ? `<a class="btn primary" href="${esc(b.url)}" title="${esc(b.file)}">${OSI[b.os]} Download for ${OSNAME[b.os]}</a>`
                 : `<a class="btn primary" href="${esc(S.releases)}">${DL_ICON} All downloads</a>`;
  const items = B.map(x => `<a class="${x === b ? "cur" : ""}" href="${esc(x.url)}">${OSI[x.os]}<span>${OSNAME[x.os]} <span class="arch">(${esc(x.arch)})</span><small>${esc(x.file)}${x.os == "linux" ? " · glibc 2.35+" : ""}</small></span></a>`).join("");
  el.innerHTML = main + `<button class="btn primary caret" aria-label="All builds" aria-haspopup="true"><span>▾</span></button>
   <div class="menu">${B.length ? `<div class="hd">${esc(S.tag)} · all builds</div>` : ""}${items}<a href="${esc(S.releases)}"><span class="hd" style="padding:0">${B.length ? "Older releases" : "Releases"} on GitHub ↗</span></a></div>`;
  el.querySelector(".caret").addEventListener("click", e => { e.stopPropagation(); el.classList.toggle("open"); });
}
const closeMenus = () => document.querySelectorAll(".dl.open").forEach(d => d.classList.remove("open"));
document.addEventListener("click", closeMenus);
document.addEventListener("keydown", e => { if (e.key == "Escape") closeMenus(); });

/* theme, remembered */
const themeBtn = $("#theme"), setIcon = () => themeBtn.textContent = document.documentElement.dataset.theme == "light" ? "☀" : "☾";
setIcon();
themeBtn.addEventListener("click", () => {
  const h = document.documentElement; h.dataset.theme = h.dataset.theme == "light" ? "dark" : "light"; setIcon();
  try { localStorage.setItem("theme", h.dataset.theme); } catch (e) {}
});

/* a bigger picture after the pointer rests on a game, never on touch screens */
if (matchMedia("(hover:hover)").matches) {
  let peekT; const peek = document.createElement("div"); peek.className = "peek"; document.body.appendChild(peek);
  const hide = () => { clearTimeout(peekT); peek.classList.remove("on"); };
  document.addEventListener("mouseover", e => {
    const g = e.target.closest(".game"); if (!g) return; const img = g.querySelector(".pic img"); if (!img) return;
    clearTimeout(peekT);
    peekT = setTimeout(() => {
      peek.innerHTML = `<img src="${img.src}" alt=""><div>${esc(g.querySelector("h4").textContent)}</div>`;
      const r = g.getBoundingClientRect(), w = peek.offsetWidth || 520, h = w * 224 / 384 + 40;
      let x = r.right + 12; if (x + w > innerWidth - 8) x = r.left - w - 12; if (x < 8) x = Math.max(8, (innerWidth - w) / 2);
      const y = Math.min(Math.max(8, r.top + r.height / 2 - h / 2), innerHeight - h - 8);
      peek.style.left = x + "px"; peek.style.top = y + "px"; peek.classList.add("on");
    }, 450);
  });
  document.addEventListener("mouseout", e => { const g = e.target.closest(".game"); if (g && !g.contains(e.relatedTarget)) hide(); });
  addEventListener("scroll", hide, {passive: true});
}

/* sections fade in, bars fill */
const io = new IntersectionObserver(es => es.forEach(e => { if (e.isIntersecting) {
  e.target.classList.add("seen"); e.target.querySelectorAll(".bar i").forEach(b => b.style.width = b.dataset.w + "%"); } }), {threshold: .15});
document.querySelectorAll(".reveal").forEach(r => io.observe(r));

dlButton("dl-top"); dlButton("dl-hero");

/* home: the picture wall and the download cards */
if (S.wall) {
  const rows = document.querySelectorAll(".wall .row"), W = S.wall;
  if (W.length) rows.forEach((r, i) => {
    const sh = W.slice(i * 5).concat(W.slice(0, i * 5));
    r.innerHTML = sh.map(p => `<img src="${esc(p)}" alt="">`).join("").repeat(2);
  });
  const cards = $("#dl-cards");
  if (cards) cards.innerHTML = ["win", "linux", "mac"].map(os => {
    const bs = S.builds.filter(b => b.os == os); if (!bs.length) return "";
    return `<div class="step"><span class="n">${OSNAME[os].toUpperCase()}</span><b>${bs.map(b => esc(b.arch)).join(" · ")}${os == "linux" ? " (glibc 2.35+)" : ""}</b>` +
      bs.map(b => `<p><a class="vers" href="${esc(b.url)}">⬇ ${esc(b.file)}</a></p>`).join("") + `</div>`;
  }).join("") || `<div class="step"><b>All builds</b><p><a class="vers" href="${esc(S.releases)}">The releases on GitHub ↗</a></p></div>`;
}

/* a system's page: the game list */
let GAMES = [], F = "all", V = "grid";
const LABEL = {ok: "● BOOTS", partial: "● PARTIAL", no: "● NOT YET"}, CLS = {ok: "ok", partial: "part", no: "no"};
function render() {
  const q = $("#q").value.toLowerCase().trim();
  const list = GAMES.filter(g => (F == "all" || g.status == F) &&
    (!q || g.title.toLowerCase().includes(q) || g.versions.some(v => v.toLowerCase().includes(q))));
  const by = {};
  list.forEach(g => { const c = g.title[0] || "#", L = /[a-z]/i.test(c) ? c.toUpperCase() : "0-9"; (by[L] = by[L] || []).push(g); });
  $("#az").innerHTML = ["0-9", ..."ABCDEFGHIJKLMNOPQRSTUVWXYZ"].map(L => `<a class="${by[L] ? "" : "off"}" data-l="${L}">${L}</a>`).join("");
  let d = 0;
  $("#out").innerHTML = Object.keys(by).sort().map(L => `<div class="letter" id="L-${L}">${L}</div><div class="games ${V}">` + by[L].map(g => {
    const pic = g.image ? `<img src="../img/${esc(S.id)}/${esc(g.image)}.webp" loading="lazy" alt="">` : `<div class="nopic">no picture yet</div>`;
    const more = g.versions.length > 1 ? `<span class="vers">+${g.versions.length - 1} versions</span>` : "";
    return `<div class="game" style="animation-delay:${Math.min(d++, 40) * 35}ms"><div class="pic">${pic}<span class="status ${CLS[g.status]}">${LABEL[g.status]}</span></div>` +
      `<div class="body"><div><h4>${esc(g.title)}</h4><div class="meta"><span>${esc(g.id)}</span></div>` +
      `<div class="vlist">${g.versions.map(esc).join("<br>")}</div></div><div class="meta">${more}</div></div></div>`;
  }).join("") + `</div>`).join("") || `<p class="sub">No game matches “${esc(q)}”.</p>`;
}
if (S.id && S.games) {
  fetch(`../data/${S.id}.json`).then(r => r.json()).then(d => { GAMES = d.games.sort((a, b) => a.title.localeCompare(b.title)); render(); })
    .catch(() => $("#out").innerHTML = `<p class="sub">The game list could not be loaded.</p>`);
  $("#q").addEventListener("input", render);
  document.querySelectorAll(".chip").forEach(c => c.addEventListener("click", () => {
    document.querySelectorAll(".chip").forEach(x => x.classList.remove("on")); c.classList.add("on"); F = c.dataset.f; render(); }));
  ["grid", "list"].forEach(v => $("#v-" + v).addEventListener("click", () => {
    V = v; $("#v-grid").classList.toggle("on", v == "grid"); $("#v-list").classList.toggle("on", v == "list"); render(); }));
  $("#az").addEventListener("click", e => { const l = e.target.dataset.l; if (l) document.getElementById("L-" + l).scrollIntoView({behavior: "smooth", block: "center"}); });
  $("#out").addEventListener("click", e => { if (e.target.classList.contains("vers")) e.target.closest(".game").querySelector(".vlist").classList.toggle("on"); });
}
