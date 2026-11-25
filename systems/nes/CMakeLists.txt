# The NES and Famicom Disk System (included from ../../CMakeLists.txt, which
# sets GEN_DIR, NES_DIR and the options). Functions use absolute paths: the
# root calls nes_recompile for the games in ROMS.

# The recompiler is a build-time tool, on the 6502's opcode table and C
# templates (cpu/6502), which also make the interpreter's switch.
add_executable(nesrecomp recomp/main.c recomp/analyze.c recomp/emit.c runtime/cart.c runtime/fds.c)
target_include_directories(nesrecomp PRIVATE runtime)
target_link_libraries(nesrecomp PRIVATE cpu6502_templates core)

# Programs without recompiled code link this instead (recomp_program = NULL).
add_library(recomp_none STATIC runtime/recomp_none.c)
target_include_directories(recomp_none PUBLIC runtime)
target_link_libraries(recomp_none PUBLIC cpu6502)

if(TESTS)
    add_executable(cpu_tests tests/cpu_tests.c)
    target_link_libraries(cpu_tests PRIVATE cpu6502 recomp_none)
endif()

# The NES system: bus, PPU, cartridge (implements cpu_read/cpu_write).
add_library(nescore STATIC runtime/nes.c runtime/ppu.c runtime/apu.c runtime/cart.c runtime/fds.c
    runtime/palette.c runtime/detect.c)
target_include_directories(nescore PUBLIC runtime)
target_link_libraries(nescore PUBLIC cpu6502 core)
if(NOT MSVC)
    target_link_libraries(nescore PUBLIC m)
endif()

add_executable(nes_headless tests/nes_headless.c)
target_link_libraries(nes_headless PRIVATE nescore recomp_none)

if(FRONTEND)
    # A game window (core/frontend) with the NES as its system (frontend.c).
    function(nes_frontend target code)
        frontend(${target} nes)
        target_link_libraries(${target} PRIVATE nescore ${code})
    endfunction()
    frontend_system(nes nescore recomp_none)  # in retrocast
endif()

# ---- Recompiled programs (M5) ----
# nes_recompile(NAME ROM [HINTS]) generates ${GEN_DIR}/NAME.c with nesrecomp
# (the ROM is embedded) and builds NAME_headless (and NAME with the frontend).
# An .fds disk image also needs FDS_BIOS: the BIOS is recompiled and embedded
# with it, and the code of the disk's files wherever it ran (nesrecomp --bios).
#
# AUTO_HINTS (on by default): first run the game in the interpreter with
# scripted input (nes_headless --play) and give every address it ran to
# nesrecomp, so code reached in that session is recompiled without hand-made
# hints (~6 s per game; coverage from as low as 0.3% static to 99.9%, systems/nes/docs/verification-log.md).
# Traced once per ROM: a rebuilt nes_headless does not trace again. The merged
# hints are written to ${GEN_DIR}/NAME.toml; copy them to systems/nes/games/ to keep them.
#
# NAME.misses next to the program: ROM code your own sessions had to
# interpret (the frontend writes it, setting record_misses); always passed to
# nesrecomp, so playing and rebuilding recompiles what you reached.
#
# EMBED_ROM=OFF: the program carries no ROM and needs the file at start
# (the generated code still holds the game's code bytes: not for sharing
# either). FDS programs always carry the BIOS.
function(nes_recompile name rom)
    set(out ${GEN_DIR}/${name}.c)
    set(hints "")
    set(hint_args "")
    if(ARGC GREATER 2 AND EXISTS "${ARGV2}")
        set(hints "${ARGV2}")
        set(hint_args --hints "${ARGV2}")
    endif()
    set(bios_args "")
    get_filename_component(ext "${rom}" LAST_EXT)
    string(TOLOWER "${ext}" ext)
    if(ext STREQUAL ".fds")
        if(NOT FDS_BIOS)
            message(FATAL_ERROR "${rom}: Famicom Disk System games need the BIOS: -DFDS_BIOS=path/to/disksys.rom")
        endif()
        set(bios_args --bios "${FDS_BIOS}")
        list(APPEND hints "${FDS_BIOS}" ${NES_DIR}/games/fds.toml)  # BIOS entries
        list(APPEND hint_args --hints ${NES_DIR}/games/fds.toml)
    endif()
    set(trace "")
    if(AUTO_HINTS)
        set(trace ${GEN_DIR}/${name}.trace)
        add_custom_command(
            OUTPUT ${trace}
            COMMAND nes_headless "${rom}" ${bios_args} --play 1 --frames ${AUTO_HINTS_FRAMES} --misses --out ${trace}
            # nes_headless as COMMAND is built first (target-level dependency) but is
            # no file dependency: runtime changes do not re-trace every game
            DEPENDS "${rom}"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Tracing ${name} in the interpreter (${AUTO_HINTS_FRAMES} frames)")
        list(APPEND hint_args --misses ${trace} --save-hints ${GEN_DIR}/${name}.toml)
    endif()
    set(played ${CMAKE_BINARY_DIR}/${name}.misses)
    if(NOT EXISTS ${played})
        file(TOUCH ${played})
    endif()
    list(APPEND hint_args --misses ${played})
    if(NOT EMBED_ROM)
        list(APPEND hint_args --no-rom)
    endif()
    add_custom_command(
        OUTPUT ${out}
        COMMAND nesrecomp "${rom}" -o ${out} ${hint_args} ${bios_args}
        DEPENDS "${rom}" ${hints} ${trace} ${played} nesrecomp
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Recompiling ${name}")
    add_library(${name}_code STATIC ${out})
    # bus helpers out of line in generated code: thousands of blocks with them
    # inlined outgrow the CPU caches (Kirby: 8.6 -> 4.6 MB, 19.9x -> 23.4x, systems/nes/docs/verification-log.md)
    target_compile_definitions(${name}_code PRIVATE CPU_OPS_OUTLINE)
    target_include_directories(${name}_code PUBLIC ${NES_DIR}/runtime)  # recomp_rt.h
    target_link_libraries(${name}_code PUBLIC cpu6502)
    add_executable(${name}_headless ${NES_DIR}/tests/nes_headless.c)
    target_link_libraries(${name}_headless PRIVATE nescore ${name}_code)
    if(FRONTEND)
        nes_frontend(${name} ${name}_code)
    endif()
endfunction()

# nestest (public, fetched by tests/fetch_test_roms.py): checks the recompiler
# against nestest.log through the CPU test runner.
set(NESTEST_ROM ${CMAKE_SOURCE_DIR}/tests/roms/nestest.nes)
if(TESTS AND EXISTS ${NESTEST_ROM})
    # hand-made hints only: tests/nes/test_recomp.py compares its blocks with nestest.log
    set(AUTO_HINTS OFF)
    nes_recompile(nestest ${NESTEST_ROM} ${CMAKE_SOURCE_DIR}/tests/nes/data/nestest.toml)
    unset(AUTO_HINTS)  # the cache value again, for the games
    add_executable(nestest_recomp_tests tests/cpu_tests.c)
    target_link_libraries(nestest_recomp_tests PRIVATE nestest_code)
endif()

# Famicom Disk System: -DFDS_BIOS=disksys.rom (your 8 KB BIOS, never
# committed) also recompiles the BIOS alone into fds and fds_headless, which
# play any .fds image with it embedded (no fds_bios setting needed); the
# games' code stays interpreted there (.fds files in ROMS recompile it). No
# tracing (it would need a disk): hints come from games/fds.toml and
# fds.misses, which the program writes as you play.
if(FDS_BIOS)
    set(AUTO_HINTS OFF)
    nes_recompile(fds "${FDS_BIOS}" ${NES_DIR}/games/fds.toml)
    unset(AUTO_HINTS)  # the cache value again
endif()
