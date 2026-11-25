# The Game Boy (included from ../../CMakeLists.txt, which sets GEN_DIR; the
# root calls gb_recompile for the Game Boy games in ROMS). gbrecomp is the
# recompiler, on the SM83's instruction templates (cpu/sm83), which also
# make the interpreter's switch.
add_executable(gbrecomp recomp/main.c recomp/recomp.c runtime/cart.c)
target_include_directories(gbrecomp PRIVATE runtime)
target_link_libraries(gbrecomp PRIVATE sm83_templates core)

# The Game Boy system (bus, timer, interrupts, PPU, sound, cartridges).
add_library(gbcore STATIC runtime/gb.c runtime/ppu.c runtime/apu.c runtime/cart.c runtime/cgb_compat.c runtime/detect.c)
target_include_directories(gbcore PUBLIC runtime)
target_link_libraries(gbcore PUBLIC sm83 core)
# Programs without recompiled code link this (gb_recomp_program = NULL).
add_library(gb_recomp_none STATIC runtime/recomp_none.c)
target_include_directories(gb_recomp_none PUBLIC runtime)
target_link_libraries(gb_recomp_none PUBLIC sm83)

# Test ROMs report on the serial port (tests/gb/test_roms.py)
add_executable(gb_headless tests/gb_headless.c)
target_link_libraries(gb_headless PRIVATE gbcore gb_recomp_none)

if(FRONTEND)
    frontend_system(gb gbcore gb_recomp_none)  # in retrocast
endif()

# gb_recompile(NAME ROM) generates ${GEN_DIR}/NAME.c with gbrecomp and builds
# NAME_headless (and NAME with the frontend). AUTO_HINTS: the game is first
# traced in the interpreter with scripted input (gb_headless --play
# --misses), so the code that session reached is recompiled; once per ROM.
# Hints: systems/gb/games/NAME.toml when present (systems/gb/recomp/main.c has the format).
# NAME.misses next to the program: ROM code your own sessions had to
# interpret (the frontend writes it, setting record_misses); always passed to
# gbrecomp, so playing and rebuilding recompiles what you reached.
#
# EMBED_ROM=OFF: the program needs the ROM file at start (the generated
# code still holds the game's code: not for sharing either).
function(gb_recompile name rom)
    set(out ${GEN_DIR}/${name}.c)
    set(args "")
    set(hints "")
    if(ARGC GREATER 2 AND EXISTS "${ARGV2}")
        set(hints "${ARGV2}")
        list(APPEND args --hints "${ARGV2}")
    endif()
    set(trace "")
    if(AUTO_HINTS)
        set(trace ${GEN_DIR}/${name}.trace)
        add_custom_command(
            OUTPUT ${trace}
            COMMAND gb_headless "${rom}" --play --frames ${AUTO_HINTS_FRAMES} --misses ${trace}
            DEPENDS "${rom}"  # not gb_headless: runtime changes do not re-trace every game
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Tracing ${name} in the interpreter (${AUTO_HINTS_FRAMES} frames)")
        list(APPEND args --misses ${trace})
    endif()
    set(played ${CMAKE_BINARY_DIR}/${name}.misses)
    if(NOT EXISTS ${played})
        file(TOUCH ${played})
    endif()
    list(APPEND args --misses ${played})
    if(NOT EMBED_ROM)
        list(APPEND args --no-rom)
    endif()
    add_custom_command(
        OUTPUT ${out}
        COMMAND gbrecomp "${rom}" -o ${out} ${args}
        DEPENDS "${rom}" ${hints} ${trace} ${played} gbrecomp
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Recompiling ${name}")
    add_library(${name}_code STATIC ${out})
    target_link_libraries(${name}_code PUBLIC gbcore)
    add_executable(${name}_headless ${CMAKE_SOURCE_DIR}/systems/gb/tests/gb_headless.c)
    target_link_libraries(${name}_headless PRIVATE gbcore ${name}_code)
    if(FRONTEND)
        frontend(${name} gb)
        target_link_libraries(${name} PRIVATE gbcore ${name}_code)
    endif()
endfunction()

# blargg's cpu_instrs (public, tests/fetch_test_roms.py), recompiled with a
# trace: tests/gb/test_recomp.py runs it and diffs it against the interpreter.
set(GB_TEST_ROM ${CMAKE_SOURCE_DIR}/tests/roms/gb/blargg/cpu_instrs/cpu_instrs.gb)
if(TESTS AND EXISTS ${GB_TEST_ROM})
    set(AUTO_HINTS ON)
    gb_recompile(gbtest_cpu_instrs ${GB_TEST_ROM})
    unset(AUTO_HINTS)  # the cache value again, for the games
endif()
