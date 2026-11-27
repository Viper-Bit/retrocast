m68k_library(cps2_m68k cps2_)
z80_library(cps2_z80 cps2_)
add_library(cps2core STATIC runtime/machine.c runtime/video.c runtime/sound.c runtime/cps2crypt.c
                           runtime/load.c runtime/games.c)
target_include_directories(cps2core PUBLIC runtime)
target_link_libraries(cps2core PUBLIC cps2_m68k cps2_z80 core)

add_executable(cps2_headless tests/rom_check.c)
target_compile_definitions(cps2_headless PRIVATE CPS2_CHECK_MACHINE)
target_link_libraries(cps2_headless PRIVATE cps2core)

if(TESTS)
    add_executable(cps2_machine_test tests/machine_test.c)
    target_link_libraries(cps2_machine_test PRIVATE cps2core)
endif()
