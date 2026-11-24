cmake_minimum_required(VERSION 3.20)
project(retrocast C)

# Release unless asked otherwise: tests, timings and playable speed assume it.
# (Multi-config generators such as Visual Studio: cmake --build build --config Release;
# without it, cmake --build always asks MSBuild for Debug.)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Programs in build/ with every generator (the $<> stops Visual Studio adding
# Release/ or Debug/): NAME.misses is written next to the program and read
# from here, and the tests look for build/NAME.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}>)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra)
endif()

set(GEN_DIR ${CMAKE_BINARY_DIR}/gen)
include(cmake/detect_system.cmake)  # detect_system(): which system a ROM is for
set(NES_DIR ${CMAKE_SOURCE_DIR}/systems/nes)

# Shared by every system: input recordings and the pad bits (core/).
add_library(core STATIC core/input_log.c core/detect.c core/zip.c core/eeprom93c46.c core/audio/fm.c core/audio/qsound.c)
target_include_directories(core PUBLIC core core/audio)
# Instruction templates for the recompilers (build-time tools).
add_library(recomp_template STATIC core/recomp/template.c)
target_include_directories(recomp_template PUBLIC core/recomp)

# Options were named NES_* before: a build folder configured then keeps its
# values under the new names (unless given anew).
foreach(old NES_GAMES NES_EMBED_ROM NES_AUTO_HINTS NES_AUTO_HINTS_FRAMES NES_FRONTEND NES_SDL3_PREFIX)
    if(DEFINED CACHE{${old}})
        string(REPLACE "NES_GAMES" "ROMS" new "${old}")
        string(REPLACE "NES_" "" new "${new}")
        if(NOT DEFINED CACHE{${new}})
            set(${new} "${${old}}" CACHE STRING "")
        endif()
        unset(${old} CACHE)
        message(STATUS "${old} is now ${new}")
    endif()
endforeach()

# SDL3 frontend (zlib license), linked statically; turn off with
# -DFRONTEND=OFF for headless builds (CI, tests). A prebuilt SDL3 in
# SDL3_PREFIX (the release kit ships one in sdl3/) is used when present;
# otherwise SDL3 is fetched and built (cmake/sdl3_options.cmake).
option(FRONTEND "Build the SDL3 frontend" ON)
set(SDL3_PREFIX "${CMAKE_SOURCE_DIR}/sdl3" CACHE PATH "Prebuilt static SDL3 (install prefix)")
if(FRONTEND)
    # only this prefix: a system SDL3 (often shared-only) is never picked up
    find_package(SDL3 CONFIG QUIET COMPONENTS SDL3-static PATHS "${SDL3_PREFIX}" NO_DEFAULT_PATH)
    if(NOT SDL3_FOUND)
        include(FetchContent)
        include(cmake/sdl3_options.cmake)
        FetchContent_Declare(SDL3
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-3.4.20
            GIT_SHALLOW TRUE)
        FetchContent_MakeAvailable(SDL3)
    endif()
    # A game window (no console window on Windows) for the systems listed
    # (core/frontend/system.h: each systems/<sys>/frontend.c exports
    # <sys>_system; system_list is written here).
    function(frontend_window target)
        set(list ${GEN_DIR}/system_list_${target}.c)
        set(text "#include \"system.h\"
")
        set(items "")
        foreach(sys IN LISTS ARGN)
            string(APPEND text "extern const System ${sys}_system;
")
            string(APPEND items "&${sys}_system, ")
        endforeach()
        string(APPEND text "const System *const system_list[] = {${items}NULL};
")
        file(CONFIGURE OUTPUT ${list} CONTENT "${text}")
        add_executable(${target} WIN32 ${CMAKE_SOURCE_DIR}/core/frontend/sdl3_main.c
            ${CMAKE_SOURCE_DIR}/core/frontend/settings.c ${CMAKE_SOURCE_DIR}/core/frontend/tv_frame.c ${list})
        target_include_directories(${target} PRIVATE ${CMAKE_SOURCE_DIR}/core/frontend)
        target_compile_definitions(${target} PRIVATE APP_NAME="${target}")
        target_link_libraries(${target} PRIVATE core SDL3::SDL3-static)
    endfunction()
    # A recompiled game's window: its one system (the caller links the
    # system's libraries and the game's code); settings in TARGET.ini.
    function(frontend target sys)
        frontend_window(${target} ${sys})
        target_sources(${target} PRIVATE ${CMAKE_SOURCE_DIR}/systems/${sys}/frontend.c)
    endfunction()
    # A system in retrocast, the window program for every system in
    # SYSTEMS: its frontend.c (settings in <sys>.ini) with its libraries.
    function(frontend_system sys)
        add_library(${sys}_window OBJECT ${CMAKE_SOURCE_DIR}/systems/${sys}/frontend.c)
        target_include_directories(${sys}_window PRIVATE ${CMAKE_SOURCE_DIR}/core/frontend)
        target_link_libraries(${sys}_window PUBLIC ${ARGN} core SDL3::SDL3-static)
        set_property(GLOBAL APPEND PROPERTY RETROCAST_SYSTEMS ${sys})
    endfunction()
endif()

# ---- Recompiled programs ----
# Options for every system's recompile function (systems/nes/CMakeLists.txt:
# nes_recompile): AUTO_HINTS traces each game in the interpreter first,
# EMBED_ROM puts the ROM in the program.
option(AUTO_HINTS "Trace each game in the interpreter before recompiling it" ON)
option(EMBED_ROM "Embed the ROM in recompiled programs" ON)
set(AUTO_HINTS_FRAMES 6000 CACHE STRING "Frames of scripted play traced by AUTO_HINTS")

# Your own games (never committed): -DROMS="a.nes;b.fds;c.gb;d.gbc;e.md" (.fds needs FDS_BIOS).
# Target name = file name without "(...)"/"[...]" tags, lower case,
# non-alphanumerics -> '_' (e.g. "Arkista's Ring (U) [!].nes" -> arkista_s_ring);
# hints are read from systems/nes/games/<name>.toml or systems/gb/games/<name>.toml when present.
set(ROMS "" CACHE STRING "ROM files to recompile (semicolon-separated); the system is read from each file")
# Relative paths are relative to the folder cmake was run from (for the
# release kit that is the archive folder, not kit/), else to this source
# folder. CMake has no variable for the former, but a cmake -P child sees it
# as CMAKE_SOURCE_DIR. The absolute paths go back into the cache, so later
# re-configures (from cmake --build, an IDE) resolve nothing again.
set(FDS_BIOS "" CACHE FILEPATH "FDS BIOS (8 KB) to recompile into fds and fds_headless")
if(ROMS OR FDS_BIOS)
    file(WRITE ${CMAKE_BINARY_DIR}/print_cwd.cmake
        "execute_process(COMMAND \"\${CMAKE_COMMAND}\" -E echo \"\${CMAKE_SOURCE_DIR}\")\n")
    execute_process(COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/print_cwd.cmake
        OUTPUT_VARIABLE cwd OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()
if(FDS_BIOS)  # the same resolution as ROMS below
    get_filename_component(from_cwd "${FDS_BIOS}" ABSOLUTE BASE_DIR "${cwd}")
    get_filename_component(from_src "${FDS_BIOS}" ABSOLUTE BASE_DIR "${CMAKE_SOURCE_DIR}")
    if(EXISTS "${from_cwd}")
        set(FDS_BIOS "${from_cwd}" CACHE FILEPATH "FDS BIOS (8 KB) to recompile into fds and fds_headless" FORCE)
    elseif(EXISTS "${from_src}")
        set(FDS_BIOS "${from_src}" CACHE FILEPATH "FDS BIOS (8 KB) to recompile into fds and fds_headless" FORCE)
    else()
        message(FATAL_ERROR "FDS_BIOS: not found: ${FDS_BIOS} (looked in ${cwd} and ${CMAKE_SOURCE_DIR})")
    endif()
endif()
if(ROMS)
    set(absolute_roms "")
    foreach(rom IN LISTS ROMS)
        get_filename_component(from_cwd "${rom}" ABSOLUTE BASE_DIR "${cwd}")
        get_filename_component(from_src "${rom}" ABSOLUTE BASE_DIR "${CMAKE_SOURCE_DIR}")
        if(EXISTS "${from_cwd}")
            list(APPEND absolute_roms "${from_cwd}")
        elseif(EXISTS "${from_src}")
            list(APPEND absolute_roms "${from_src}")
        else()
            message(FATAL_ERROR "ROMS: not found: ${rom} (looked in ${cwd} and ${CMAKE_SOURCE_DIR})")
        endif()
    endforeach()
    set(ROMS "${absolute_roms}" CACHE STRING "ROM files to recompile (semicolon-separated); the system is read from each file" FORCE)
endif()

# Warnings as errors (CI): our code only, SDL3 above is not affected.
# -DTESTS=ON (CI, contributors): the test programs and the test ROMs'
# recompiles the Python tests run (tests/); off, a build makes only the
# programs, the recompilers and your games.
option(TESTS "Build the test programs and test recompiles" OFF)

# Float results the same with every compiler: no fused multiply-add where the
# C source has a multiply then an add (gcc fuses by default when its target
# CPU has FMA). Our code only, as for warnings below.
add_compile_options($<$<NOT:$<C_COMPILER_ID:MSVC>>:-ffp-contract=off>)

option(WERROR "Treat compiler warnings as errors" OFF)
if(WERROR)
    add_compile_options($<IF:$<C_COMPILER_ID:MSVC>,/WX,-Werror>)
endif()

# The systems to build (CI builds the ones a change touches).
set(SYSTEMS "nes;gb;genesis;atari2600;mastersystem;cps1" CACHE STRING "Systems to build (semicolon-separated): nes, gb, genesis, atari2600, mastersystem (with the Game Gear), cps1")
# The CPUs they use (cpu/): added once each, before the systems.
set(CPU_nes 6502)
set(CPU_gb sm83)
set(CPU_genesis "m68k;z80")  # the 68000 and the Z80
set(CPU_atari2600 6502)
set(CPU_mastersystem z80)
set(CPU_cps1 "m68k;z80")
set(cpus "")
foreach(sys IN LISTS SYSTEMS)
    if(NOT sys MATCHES "^(nes|gb|genesis|atari2600|mastersystem|cps1)$")
        message(FATAL_ERROR "SYSTEMS: unknown system ${sys} (nes, gb, genesis, atari2600, mastersystem, cps1)")
    endif()
    list(APPEND cpus ${CPU_${sys}})
endforeach()
list(REMOVE_DUPLICATES cpus)
foreach(cpu IN LISTS cpus)
    add_subdirectory(cpu/${cpu} ${CMAKE_BINARY_DIR}/cpu_${cpu})
endforeach()
foreach(sys IN LISTS SYSTEMS)
    add_subdirectory(systems/${sys} ${CMAKE_BINARY_DIR}/sys_${sys})  # not build/<sys>: that is the program (no .exe off Windows)
endforeach()
if(TESTS)
    add_executable(zip_check core/zip_check.c)  # tests/test_zip.py
    target_link_libraries(zip_check PRIVATE core)
    # system_detect FILE: the system a file is for, from its bytes (core/detect.h;
    # each system's detector and the library it is in)
    set(DETECTOR_nes nes_detector nescore)
    set(DETECTOR_gb gb_detector gbcore)
    set(DETECTOR_genesis md_detector mdcore)
    set(DETECTOR_atari2600 a26_detector atari2600_cart)
    set(DETECTOR_mastersystem sms_detector smscore)
    set(DETECTOR_cps1 cps1_detector cps1core)
    set(text "#include \"detect.h\"
    ")
    set(items "")
    set(libs "")
    foreach(sys IN LISTS SYSTEMS)
        list(GET DETECTOR_${sys} 0 det)
        list(GET DETECTOR_${sys} 1 lib)
        string(APPEND text "extern const SystemDetector ${det};
    ")
        string(APPEND items "&${det}, ")
        list(APPEND libs ${lib})
    endforeach()
    list(LENGTH SYSTEMS count)
    if("mastersystem" IN_LIST SYSTEMS)  # the Game Gear is a mode of it, with its own detector
        string(APPEND text "extern const SystemDetector gg_detector;
    ")
        string(APPEND items "&gg_detector, ")
        math(EXPR count "${count} + 1")
    endif()
    string(APPEND text "const SystemDetector *const detector_list[] = {${items}};
    const int detector_count = ${count};
    ")
    file(CONFIGURE OUTPUT ${GEN_DIR}/detector_list.c CONTENT "${text}")
    add_executable(system_detect core/system_detect.c ${GEN_DIR}/detector_list.c)
    target_link_libraries(system_detect PRIVATE ${libs} core)
endif()

if(FRONTEND)
    # retrocast: plays a game of any system above, picked from the file's
    # bytes (core/detect.h) or --system
    get_property(window_systems GLOBAL PROPERTY RETROCAST_SYSTEMS)
    frontend_window(retrocast ${window_systems})
    foreach(sys IN LISTS window_systems)
        target_link_libraries(retrocast PRIVATE ${sys}_window)
    endforeach()
endif()

foreach(rom IN LISTS ROMS)
    get_filename_component(stem "${rom}" NAME_WLE)
    string(REGEX REPLACE "[ ]*[[(][^])]*[])]" "" stem "${stem}")  # drop (U), [!], ...
    string(TOLOWER "${stem}" name)
    string(REGEX REPLACE "[^a-z0-9]+" "_" name "${name}")
    string(REGEX REPLACE "^_+|_+$" "" name "${name}")
    detect_system("${rom}" sys)  # from the file's bytes, as retrocast does
    if(sys STREQUAL "gamegear")
        set(sys mastersystem)  # a mode of the Master System
    endif()
    if(NOT sys IN_LIST SYSTEMS)
        message(FATAL_ERROR "ROMS: ${rom} is a ${sys} game, but SYSTEMS is ${SYSTEMS}")
    elseif(sys STREQUAL "genesis")
        genesis_recompile(${name} "${rom}")
    elseif(sys STREQUAL "gb")
        gb_recompile(${name} "${rom}" ${CMAKE_SOURCE_DIR}/systems/gb/games/${name}.toml)
    elseif(sys STREQUAL "atari2600")
        atari2600_recompile(${name} "${rom}" ${CMAKE_SOURCE_DIR}/systems/atari2600/games/${name}.toml)
    elseif(sys STREQUAL "mastersystem")
        sms_recompile(${name} "${rom}")
    elseif(sys STREQUAL "cps1")
        cps1_recompile(${name} "${rom}")
    else()
        nes_recompile(${name} "${rom}" ${NES_DIR}/games/${name}.toml)
        list(APPEND game_names ${name})
    endif()
endforeach()
# for tests/nes/test_regression.py: the games this build recompiles
list(JOIN game_names "\n" game_lines)
file(WRITE ${CMAKE_BINARY_DIR}/nes_games.txt "${game_lines}\n")
