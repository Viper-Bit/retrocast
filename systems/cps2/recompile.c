#include "file.h"
#include "m68k_recomp.h"
#include "recomp/template.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 3 && argc != 4) {
        fprintf(stderr, "Usage: %s OPCODE_IMAGE OUTPUT_C [EXECUTED_PCS]\n", argv[0]);
        return 2;
    }
    size_t size;
    uint8_t *image = file_read(argv[1], &size);
    if (!image || size < 512 || size > 0x400100 || size % 2) {
        fputs("Invalid CPS-2 opcode image\n", stderr);
        free(image);
        return 1;
    }
    uint32_t end = (uint32_t)size - 256;
    uint8_t *entries = calloc(end + 8, 1);
    if (!entries) {
        free(image);
        return 1;
    }
    const uint8_t *code = image + 256;
    for (unsigned v = 1; v < 64; ++v) {
        const uint8_t *p = v == 1 ? code + 4 : image + v * 4;
        uint32_t address = (uint32_t)p[1] << 16 | (uint32_t)p[2] << 8 | p[3];
        if (!(address & 1) && address < end)
            entries[address] = 1;
    }
    if (argc == 4) {
        size_t trace_size;
        uint8_t *trace = file_read(argv[3], &trace_size);
        if (!trace || trace_size != end) {
            fputs("Executed-PC bitmap has the wrong size\n", stderr);
            free(trace);
            free(entries);
            free(image);
            return 1;
        }
        for (uint32_t i = 0; i < end; i += 2)
            entries[i] |= trace[i] != 0;
        free(trace);
    }
    M68kRecomp recomp = {
        .code = code, .end = end, .entries = entries,
        .bus_decl = "Cps2Machine *const s = c->bus;",
        .after = "if (s->audio_program) cps2_sound_run(s);",
        .stop = "CPS2_STOP(s, c)", .fn_type = "Cps2RecompFn",
    };
    Buf output = {0};
    bprintf(&output, "/* Generated CPS-2 68000 code. */\n"
                     "#include \"m68k_ops.h\"\n#include \"recomp_rt.h\"\n");
    int failed = m68k_recomp_analyse(&recomp) || m68k_recomp_emit(&recomp, &output);
    if (!failed) {
        bprintf(&output, "\nconst Cps2Recomp cps2_recomp_program = {0x%08xu, lookup};\n",
                (unsigned)m68k_recomp_hash(code, end));
        buf_write_file(argv[2], &output);
        printf("%ld blocks, %ld instructions\n", recomp.nblocks, recomp.ninstr);
    }
    m68k_recomp_free(&recomp);
    free(output.s);
    free(entries);
    free(image);
    return failed;
}
