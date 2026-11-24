# The Capcom Play System I (included from ../../CMakeLists.txt). Its CPUs are
# in cpu/m68k and cpu/z80, listed in the root CMakeLists.txt (CPU_cps1).

# Its own copy of the 68000 interpreter: the bus functions are global
# symbols, so the Genesis and the CPS-1 cannot share one in retrocast.
m68k_library(cps1_m68k cps1_)
z80_library(cps1_z80 cps1_)  # the sound CPU, its own copy as well
add_library(cps1core STATIC runtime/ym2151.c runtime/oki6295.c runtime/state.c runtime/cps1.c runtime/video.c runtime/games.c runtime/load.c runtime/detect.c)
target_include_directories(cps1core PUBLIC runtime ${Z80_DIR})  # cps1.h holds a Z80
if(NOT MSVC)
    target_link_libraries(cps1core PUBLIC m)  # ym2151.c
endif()
target_link_libraries(cps1core PUBLIC cps1_m68k core PRIVATE cps1_z80)  # Z80_PREFIX stays inside: the Master System has its own

# Programs without recompiled code link this (cps1_recomp_program = NULL).
add_library(cps1_recomp_none STATIC runtime/recomp_none.c)
target_link_libraries(cps1_recomp_none PUBLIC cps1core)

if(TESTS)
    add_executable(cps1_tests tests/cps1_tests.c)
    target_link_libraries(cps1_tests PRIVATE cps1core cps1_recomp_none)
endif()

# Runs a game without a window (tests/cps1/test_cps1.py)
add_executable(cps1_headless tests/cps1_headless.c)
target_link_libraries(cps1_headless PRIVATE cps1core cps1_recomp_none)

if(FRONTEND)
    frontend_system(cps1 cps1core cps1_recomp_none)
endif()
