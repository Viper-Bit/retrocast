#include "input_log.h"

#include <stdlib.h>
#include <string.h>

static const char V1[5] = {'N', 'E', 'S', 'I', 1}, V2[5] = {'R', 'C', 'I', 'N', 2},
                  V3[5] = {'R', 'C', 'I', 'N', 3};

FILE *input_log_create(const char *path, const char *system, int pads) {
    FILE *f = fopen(path, "wb");
    char sys[4] = {0};
    for (size_t i = 0; i < sizeof sys && system[i]; i++) sys[i] = system[i];
    if (f) fwrite(pads > 2 ? V3 : V2, 1, sizeof V2, f), fwrite(sys, 1, sizeof sys, f);
    return f;
}

void input_log_write(FILE *f, InputFrame fr, int pads) {
    uint8_t b[9];
    int n = pads > 2 ? 4 : 2;
    for (int i = 0; i < n; i++) b[i * 2] = (uint8_t)fr.pad[i], b[i * 2 + 1] = (uint8_t)(fr.pad[i] >> 8);
    b[n * 2] = fr.flags;
    fwrite(b, 1, (size_t)n * 2 + 1, f);
}

int input_log_load(const char *path, InputLog *log) {
    memset(log, 0, sizeof *log);
    FILE *f = fopen(path, "rb");
    if (!f) return -1;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char head[9] = {0};
    int v = 0, ok = size >= 5 && fread(head, 1, 5, f) == 5;  /* v: 1, 2 or 3 */
    if (ok && (!memcmp(head, V2, 5) || !memcmp(head, V3, 5))) v = head[4], ok = fread(head + 5, 1, 4, f) == 4;
    else if (ok && !memcmp(head, V1, 5)) v = 1;
    else ok = 0;
    long body = size - (v > 1 ? 9 : 5), per = v == 3 ? 9 : v == 2 ? 5 : 3;
    if (!ok || body % per) { fclose(f); return -1; }
    memcpy(log->system, v > 1 ? head + 5 : "nes", 4);
    log->count = body / per;
    if ((uintmax_t)log->count > (SIZE_MAX - 1) / sizeof *log->frames) {
        fclose(f);
        return -1;
    }
    log->frames = malloc((size_t)log->count * sizeof *log->frames + 1);
    if (!log->frames) {
        fclose(f);
        return -1;
    }
    for (long i = 0; i < log->count; i++) {
        uint8_t b[9];
        if (fread(b, 1, (size_t)per, f) != (size_t)per) { fclose(f); input_log_free(log); return -1; }
        InputFrame fr = {{0}, b[per - 1]};
        for (int k = 0; k < (v == 3 ? 4 : 2); k++) fr.pad[k] = v == 1 ? b[k] : (uint16_t)(b[k * 2] | b[k * 2 + 1] << 8);
        log->frames[i] = fr;
    }
    fclose(f);
    return 0;
}

void input_log_free(InputLog *log) {
    free(log->frames);
    memset(log, 0, sizeof *log);
}

uint16_t input_clean(uint16_t b) {
    if ((b & (PAD_LEFT | PAD_RIGHT)) == (PAD_LEFT | PAD_RIGHT)) b &= (uint16_t)~(PAD_LEFT | PAD_RIGHT);
    if ((b & (PAD_UP | PAD_DOWN)) == (PAD_UP | PAD_DOWN)) b &= (uint16_t)~(PAD_UP | PAD_DOWN);
    return b;
}
