/* Genesis without a window, for tests (tests/genesis/test_boot.py,
 * tools/genesis_sheet.py, tests/genesis/test_recomp.py); NAME_headless is
 * the same with a game's recompiled code.
 *   genesis_headless ROM [--frames N] [--boot] [--ppm FILE] [--wav FILE] [--press F:BUTTONS]...
 *                    [--misses FILE] [--diff] [--coverage]
 *   --boot   stop at the game's first VDP port write (D1's boot check)
 *   --ppm    write the last whole frame (256 or 320 by 224 or 240)
 *   --wav    write the sound (16-bit stereo at the YM2612's rate, 53,267 Hz NTSC)
 *   --press  hold pad 1's buttons (core/input_log.h PAD_* bits, hex) for
 *            6 frames from frame F
 *   --misses write the ROM code the interpreter ran ("MISS $PC", entries
 *            for mdrecomp; without recompiled code: everything run)
 *   --diff   run an interpreter-only machine in lockstep: the CPUs, the Z80
 *            and the RAMs must match after every line, the whole machine
 *            after every frame (exit code 1 at the first difference)
 *   --coverage  print the share of the 68000's clocks run by recompiled code
 * Runs N frames (default 300), or fewer on a TMSS lock or a halted 68000,
 * and reports which. Last line "result: booted|locked|halted|timeout"
 * (booted: the VDP was written); exit code 0 only for booted. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "capture.h"
#include "file.h"
#include "md.h"
#include "recomp_rt.h"

/* The machine with what differs by design blanked: the pointers, the jump
 * buffer, the recompiled code's own fields. */
static void comparable(const Md *src, Md *out) {
    *out = *src;
    out->rom = out->sram = out->misses = NULL;
    out->cpu.bus = out->z80.bus = NULL;
    memset(&out->cpu.abort, 0, sizeof out->cpu.abort);
    out->recomp_on = 0, out->cycles_native = out->cycles_interp = 0;
}
static int same_line(const Md *a, const Md *b) {
    M68k x = a->cpu, y = b->cpu;
    x.bus = y.bus = NULL;
    memset(&x.abort, 0, sizeof x.abort), memset(&y.abort, 0, sizeof y.abort);
    Z80 p = a->z80, q = b->z80;
    p.bus = q.bus = NULL;
    return !memcmp(&x, &y, sizeof x) && !memcmp(&p, &q, sizeof p) && !memcmp(a->wram, b->wram, sizeof a->wram) &&
           !memcmp(a->zram, b->zram, sizeof a->zram);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: genesis_headless ROM [--frames N]\n");
        return 2;
    }
    int frames = 300, boot = 0, npress = 0, press_at[64];
    unsigned press_pad[64];
    const char *ppm = NULL, *wav = NULL, *misses = NULL;
    int diff = 0, coverage = 0;
    for (int i = 2; i < argc; i++) {
        if (!strcmp(argv[i], "--frames") && i + 1 < argc) frames = atoi(argv[++i]);
        else if (!strcmp(argv[i], "--boot")) boot = 1;
        else if (!strcmp(argv[i], "--misses") && i + 1 < argc) misses = argv[++i];
        else if (!strcmp(argv[i], "--diff")) diff = 1;
        else if (!strcmp(argv[i], "--coverage")) coverage = 1;
        else if (!strcmp(argv[i], "--ppm") && i + 1 < argc) ppm = argv[++i];
        else if (!strcmp(argv[i], "--wav") && i + 1 < argc) wav = argv[++i];
        else if (!strcmp(argv[i], "--press") && i + 1 < argc && npress < 64 &&
                 sscanf(argv[++i], "%d:%x", &press_at[npress], &press_pad[npress]) == 2) npress++;
        else { fprintf(stderr, "genesis_headless: bad argument %s\n", argv[i]); return 2; }
    }
    size_t size;
    uint8_t *rom = file_read(argv[1], &size);
    if (!rom) {
        fprintf(stderr, "%s: cannot read\n", argv[1]);
        return 2;
    }
    static Md m;
    char err[128];
    if (md_load(&m, rom, size, err, sizeof err)) {
        fprintf(stderr, "%s: %s\n", argv[1], err);
        return 2;
    }
    static Md ref;  /* --diff: the same game in the interpreter alone */
    if (diff) {
        md_load(&ref, rom, size, err, sizeof err);
        ref.recomp_on = 0;
        if (!m.recomp_on) printf("diff: no recompiled code for this ROM: both machines interpret\n");
    }
    free(rom);
    if (misses && !(m.misses = calloc(md_code_end(&m) / 2 + 1, 1))) { fprintf(stderr, "out of memory\n"); return 2; }
    FILE *w = wav ? capture_wav_open(wav) : NULL;
    if (wav && !w) { fprintf(stderr, "%s: cannot write\n", wav); return 2; }
    static float buf[2 * SND_BUF];
    for (int f = 0; f < frames && !m.cpu.halted && !(boot && m.vdp_writes); f++) {
        m.pad[0] = 0;
        for (int k = 0; k < npress; k++)
            if (f >= press_at[k] && f < press_at[k] + 6) m.pad[0] |= (uint16_t)press_pad[k];
        if (diff) {
            ref.pad[0] = m.pad[0];
            for (int line = 0; m.frame_count == (uint32_t)f; line++) {
                md_run_line(&m), md_run_line(&ref);
                if (!same_line(&m, &ref)) {
                    printf("diff: frame %d line %d: the CPUs, Z80 or RAM differ (68000 pc $%06X / $%06X, clocks %llu / %llu)\n", f,
                           line, (m.cpu.pc - 4) & 0xFFFFFF, (ref.cpu.pc - 4) & 0xFFFFFF, (unsigned long long)m.cpu.cycles,
                           (unsigned long long)ref.cpu.cycles);
                    return 1;
                }
            }
            static Md x, y;
            comparable(&m, &x), comparable(&ref, &y);
            if (memcmp(&x, &y, sizeof x)) { printf("diff: frame %d: the machines differ\n", f); return 1; }
            snd_take(&ref.snd, buf, SND_BUF);
        } else {
            md_run_frame(&m);
        }
        int n = snd_take(&m.snd, buf, SND_BUF);
        for (int k = 0; w && k < 2 * n; k++) {
            int16_t s = (int16_t)(buf[k] * 32767);
            capture_wav_samples(w, &s, 1);
        }
    }
    if (w && capture_wav_close(w, (unsigned)md_sample_rate(&m), 2)) { fprintf(stderr, "%s: cannot write\n", wav); return 2; }
    if (ppm) {
        if (capture_ppm(ppm, m.vdp.frame, m.vdp.frame_w, m.vdp.frame_h, 320)) { fprintf(stderr, "%s: cannot write\n", ppm); return 2; }
    }
    if (diff) printf("diff: %d frames, no difference\n", frames);
    if (coverage) {
        uint64_t all = m.cycles_native + m.cycles_interp;
        printf("coverage: %.2f%% of 68000 clocks recompiled\n", all ? 100.0 * (double)m.cycles_native / (double)all : 0.0);
    }
    if (misses) {
        FILE *o = fopen(misses, "w");
        if (!o) { fprintf(stderr, "%s: cannot write\n", misses); return 2; }
        for (uint32_t a = 0; a < md_code_end(&m); a += 2)
            if (m.misses[a >> 1]) fprintf(o, "MISS $%06X\n", a);
        fclose(o);
    }
    if (m.vdp_writes) printf("vdp: first write in frame %d\n", m.vdp_first_frame);
    else printf("vdp: no writes\n");
    printf("68000: pc $%06X, %llu clocks\n", m.cpu.pc, (unsigned long long)m.cpu.cycles);
    const char *r = m.tmss_locked ? "locked" : m.cpu.halted ? "halted" : m.vdp_writes ? "booted" : "timeout";
    if (m.tmss_locked) printf("tmss: the VDP was used before \"SEGA\" was written to $A14000\n");
    printf("result: %s\n", r);
    md_free(&m);
    return strcmp(r, "booted") != 0;
}
