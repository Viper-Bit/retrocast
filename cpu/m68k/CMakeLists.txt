# The 68000 (included from ../../CMakeLists.txt, which sets GEN_DIR, for the
# systems that use it). Knows no machine: the system implements m68k_read,
# m68k_write, m68k_idle, m68k_aborted, m68k_iack, m68k_reset_out (m68k_cpu.h).

# The instruction templates (m68k.c), for recompilers and the interpreter's
# handlers, so instruction semantics exist once.
add_library(m68k_templates STATIC m68k.c m68k_recomp.c)  # m68k_recomp.c: the recompilers' shared core
target_include_directories(m68k_templates PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(m68k_templates PUBLIC recomp_template)

# NAME.misses of a recompiled game (the Genesis and CPS-1 frontends): once,
# not in m68k_library's per-system copies.
add_library(m68k_misses STATIC m68k_misses.c)
target_include_directories(m68k_misses PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(m68k_gen m68k_gen.c)
target_link_libraries(m68k_gen PRIVATE m68k_templates)

# WORKING_DIRECTORY: see cpu/6502/CMakeLists.txt
add_custom_command(
    OUTPUT ${GEN_DIR}/m68k_handlers.inc
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GEN_DIR}
    COMMAND m68k_gen ${GEN_DIR}/m68k_handlers.inc
    DEPENDS m68k_gen
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating the 68000 interpreter's handlers")

# The interpreter (m68k_cpu.c) and the instruction helpers (m68k_ops.h).
# m68k_library(NAME PREFIX): another copy with its functions and the bus it
# calls renamed PREFIXm68k_step, PREFIXm68k_read, ... (m68k_cpu.h), for a
# second system with this CPU in the same program.
set(M68K_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")  # seen from the systems' folders
function(m68k_library name prefix)
    add_library(${name} STATIC ${M68K_DIR}/m68k_cpu.c ${GEN_DIR}/m68k_handlers.inc)
    target_include_directories(${name} PUBLIC ${M68K_DIR} PRIVATE ${GEN_DIR})
    if(prefix)
        target_compile_definitions(${name} PUBLIC M68K_PREFIX=${prefix})
        add_dependencies(${name} m68k)  # the handlers' rule belongs to this folder's target
    endif()
endfunction()
m68k_library(m68k "")

if(TESTS)
    # SingleStepTests m68000 on a flat bus (tests/genesis/test_m68k.py)
    add_executable(m68k_tests m68k_tests.c)
    target_link_libraries(m68k_tests PRIVATE m68k)
endif()
