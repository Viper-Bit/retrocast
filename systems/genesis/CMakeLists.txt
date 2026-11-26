# The Sega Genesis / Mega Drive (included from ../../CMakeLists.txt). Its CPUs
# are in cpu/m68k and cpu/z80, listed in the root CMakeLists.txt (CPU_genesis).

# The machine: memory maps, I/O, Z80 control, cartridge, timeline (D1); the VDP (D2); sound (D4).
add_library(mdcore STATIC runtime/md.c runtime/eeprom.c runtime/vdp.c runtime/sound.c runtime/detect.c)
target_include_directories(mdcore PUBLIC runtime)
target_link_libraries(mdcore PUBLIC m68k m68k_misses z80 core)
if(NOT MSVC)
    target_link_libraries(mdcore PUBLIC m)
endif()

# mdrecomp: the 68000 recompiler, on the instruction templates (cpu/m68k),
# which also make the interpreter's handlers.
add_executable(mdrecomp recomp/main.c)
target_link_libraries(mdrecomp PRIVATE mdcore md_recomp_none m68k_templates)

# Programs without recompiled code link this (md_recomp_program = NULL).
add_library(md_recomp_none STATIC runtime/recomp_none.c)
target_link_libraries(md_recomp_none PUBLIC mdcore)

# Boots a ROM without a window (tests/genesis/test_boot.py)
add_executable(genesis_headless tests/genesis_headless.c)
target_link_libraries(genesis_headless PRIVATE mdcore md_recomp_none)

if(TESTS)
    # The machine's self-checks (tests/genesis/test_machine.py)
    add_executable(md_tests tests/md_tests.c)
    target_link_libraries(md_tests PRIVATE mdcore md_recomp_none)
endif()

if(FRONTEND)
    frontend_system(genesis mdcore md_recomp_none)  # in retrocast
endif()

# genesis_recompile(NAME ROM) generates ${GEN_DIR}/NAME.c with mdrecomp and
# builds NAME_headless (and NAME with the frontend). AUTO_HINTS: the game is
# first traced in the interpreter with Start pressed now and then
# (genesis_headless --misses), so the code that session reached is
# recompiled; once per ROM. NAME.misses next to the program: ROM code your
# own sessions interpreted (the frontend writes it, setting record_misses);
# always passed to mdrecomp, so playing and rebuilding recompiles what you
# reached. EMBED_ROM=OFF: the program needs the ROM file at start.
function(genesis_recompile name rom)
    set(out ${GEN_DIR}/${name}.c)
    set(args "")
    set(trace "")
    if(AUTO_HINTS)
        set(trace ${GEN_DIR}/${name}.trace)
        set(presses "")
        foreach(f 300 500 700 900 1100 1500 2000 2500 3000)
            list(APPEND presses --press ${f}:08)
        endforeach()
        add_custom_command(
            OUTPUT ${trace}
            COMMAND genesis_headless "${rom}" --frames ${AUTO_HINTS_FRAMES} ${presses} --misses ${trace}
            DEPENDS "${rom}"  # not genesis_headless: runtime changes do not re-trace every game
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
        COMMAND mdrecomp "${rom}" -o ${out} ${args}
        DEPENDS "${rom}" ${trace} ${played} mdrecomp
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Recompiling ${name}")
    add_library(${name}_code STATIC ${out})
    target_link_libraries(${name}_code PUBLIC mdcore)
    add_executable(${name}_headless ${CMAKE_SOURCE_DIR}/systems/genesis/tests/genesis_headless.c)
    target_link_libraries(${name}_headless PRIVATE mdcore ${name}_code)
    if(FRONTEND)
        frontend(${name} genesis)
        target_link_libraries(${name} PRIVATE mdcore ${name}_code)
    endif()
endfunction()

if(TESTS)
    # A ROM of random 68000 instructions (tests/random_rom.c), recompiled with a
    # trace: tests/genesis/test_recomp.py runs it in lockstep with the
    # interpreter (CI has no game ROMs).
    add_executable(random_rom tests/random_rom.c)
    target_link_libraries(random_rom PRIVATE m68k_templates)
    add_custom_command(
        OUTPUT ${GEN_DIR}/mdtest_random.md
        COMMAND ${CMAKE_COMMAND} -E make_directory ${GEN_DIR}
        COMMAND random_rom ${GEN_DIR}/mdtest_random.md
        DEPENDS random_rom
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Making a ROM of random 68000 instructions")
    set(AUTO_HINTS ON)
    genesis_recompile(mdtest_random ${GEN_DIR}/mdtest_random.md)
    unset(AUTO_HINTS)  # the cache value again, for the games
endif()
