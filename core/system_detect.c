/* system_detect FILE: the id of the system FILE is for (core/detect.h),
 * among the systems built; exit 1 with the reason when none or two fit.
 * system_detect --systems: the ids of the systems built.
 * For tests (tests/test_detect.py) and scripts. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "detect.h"

extern const SystemDetector *const detector_list[];  /* written by CMake */
extern const int detector_count;

int main(int argc, char **argv) {
    if (argc != 2) return fprintf(stderr, "usage: system_detect FILE | --systems\n"), 2;
    if (!strcmp(argv[1], "--systems")) {
        for (int i = 0; i < detector_count; i++) printf("%s\n", detector_list[i]->id);
        return 0;
    }
    size_t size;
    unsigned char *data = file_read(argv[1], &size);
    if (!data) return perror(argv[1]), 2;
    char err[512];
    int k = detect_system(detector_list, detector_count, data, (size_t)size, argv[1], err, sizeof err);
    free(data);
    if (k < 0) return fprintf(stderr, "%s\n", err), 1;
    printf("%s\n", detector_list[k]->id);
    return 0;
}
