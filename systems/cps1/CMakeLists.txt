# The Capcom Play System I (included from ../../CMakeLists.txt). Its CPUs are
# in cpu/m68k and cpu/z80, listed in the root CMakeLists.txt (CPU_cps1).

# Its own copy of the 68000 interpreter: the bus functions are global
# symbols, so the Genesis and the CPS-1 cannot share one in retrocast.
m68k_library(cps1_m68k cps1_)
z80_library(cps1_z80 cps1_)  # the sound CPU, its own copy as well
add_library(cps1core STATIC runtime/ym2151.c runtime/oki6295.c runtime/kabuki.c runtime/state.c runtime/cps1.c runtime/video.c runtime/games.c runtime/load.c runtime/detect.c)
target_include_directories(cps1core PUBLIC runtime ${Z80_DIR})  # cps1.h holds a Z80
if(NOT MSVC)
    target_link_libraries(cps1core PUBLIC m)  # ym2151.c
endif()
target_link_libraries(cps1core PUBLIC cps1_m68k m68k_misses core PRIVATE cps1_z80)  # Z80_PREFIX stays inside: the Master System has its own

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

# cps1recomp: the 68000 recompiler, on the shared core (cpu/m68k/m68k_recomp.c).
add_executable(cps1recomp recomp/main.c)
target_link_libraries(cps1recomp PRIVATE cps1core cps1_recomp_none m68k_templates)

# cps1_recompile(NAME ZIP) generates ${GEN_DIR}/NAME.c with cps1recomp and
# builds NAME_headless (and NAME with the frontend), which open the zip at
# start (a clone's: its parent's zip beside it). AUTO_HINTS: the game is
# first traced in the interpreter with the scripted play of cps1_headless
# --play (cps1_headless --misses), so the code that session reached is
# recompiled; once per zip. NAME.misses next to the program: code your own
# sessions interpreted; always passed to cps1recomp, so playing and
# rebuilding recompiles what you reached.
function(cps1_recompile name zip)
    set(out ${GEN_DIR}/${name}.c)
    set(args "")
    set(trace "")
    if(AUTO_HINTS)
        set(trace ${GEN_DIR}/${name}.trace)
        add_custom_command(
            OUTPUT ${trace}
            COMMAND cps1_headless "${zip}" --frames ${AUTO_HINTS_FRAMES} --play --misses ${trace}
            DEPENDS "${zip}"  # not cps1_headless: runtime changes do not re-trace every game
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Tracing ${name} in the interpreter (${AUTO_HINTS_FRAMES} frames)")
        list(APPEND args --misses ${trace})
    endif()
    set(played ${CMAKE_BINARY_DIR}/${name}.misses)
    if(NOT EXISTS ${played})
        file(TOUCH ${played})
    endif()
    list(APPEND args --misses ${played})
    add_custom_command(
        OUTPUT ${out}
        COMMAND cps1recomp "${zip}" -o ${out} ${args}
        DEPENDS "${zip}" ${trace} ${played} cps1recomp
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Recompiling ${name}")
    add_library(${name}_code STATIC ${out})
    target_link_libraries(${name}_code PUBLIC cps1core)
    add_executable(${name}_headless ${CMAKE_SOURCE_DIR}/systems/cps1/tests/cps1_headless.c)
    target_link_libraries(${name}_headless PRIVATE cps1core ${name}_code)
    if(FRONTEND)
        frontend(${name} cps1)
        target_link_libraries(${name} PRIVATE cps1core ${name}_code)
    endif()
endfunction()
