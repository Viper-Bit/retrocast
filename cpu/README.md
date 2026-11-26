# CPUs

`cpu/` holds one folder per CPU. A CPU folder has no machine in it: no
cartridge, picture or sound. The system supplies the bus functions the CPU
calls, so every system with the same CPU uses the same code.

| CPU | Systems | Tests | Folder |
|-----|---------|-------|--------|
| 6502 (the NES's 2A03) | NES and Famicom Disk System | SingleStepTests 2A03, nestest | [6502/](6502/) |
| 6507 (a 6502: 13 address lines, no IRQ or NMI, decimal mode) | Atari 2600, its own copy of the 6502 | NMOS decimal vectors | [6502/](6502/) |
| SM83 | Game Boy and Game Boy Color | SingleStepTests sm83 | [sm83/](sm83/) |
| Z80 | Genesis / Mega Drive and CPS-1 (sound CPU), Master System / Mark III and Game Gear (main CPU) | SingleStepTests z80 | [z80/](z80/) |
| 68000 | Genesis / Mega Drive and CPS-1 (main CPU) | SingleStepTests m68000 | [m68k/](m68k/) |

## What a CPU folder holds
- The instruction templates, written once: the opcode table and C per
  opcode (`ops.c`, `c6502.c`; `sm83.c`; `z80.c`, where the DD and FD
  tables are the base table's code made with IX or IY; `m68k.c`). The
  interpreter's switch and the recompiled code are both made from them.
  The 68000's templates read register numbers from `op` at run time, so
  one body serves every register: 1,541 handlers and a 64K table instead
  of a 64K-case switch.
- The interpreter: `cpu6502.c`, `cpu6502.h`, `cpu6502_ops.h`; `sm83_cpu.c`,
  `sm83_cpu.h`, `sm83_ops.h`; `z80_cpu.c`, `z80_cpu.h`, `z80_ops.h`;
  `m68k_cpu.c`, `m68k_cpu.h`, `m68k_ops.h`.
- The switch generator (`cpu6502_gen.c`, `sm83_gen.c`, `z80_gen.c`,
  `m68k_gen.c`), which writes the interpreter's opcode switch into
  `build/gen/` at build time.
- The CPU test runner (`sm83_tests.c`, `z80_tests.c`, `m68k_tests.c`). The 6502's runner is
  `systems/nes/tests/cpu_tests.c`, because it also runs nestest and recompiled code.
- `CMakeLists.txt`: the library and generator targets.

## How a system uses a CPU
1. The root `CMakeLists.txt` maps systems to CPUs (`set(CPU_nes 6502)`)
   and adds each selected CPU's folder once.
2. The system's `CMakeLists.txt` links the CPU library (`cpu6502` or
   `sm83`) and, for recompiled programs, the template library.
3. The system implements the bus functions its CPU calls: `cpu_read` and
   `cpu_write` for the 6502; `gb_read`, `gb_write`, `gb_idle` and
   `gb_irq_ack` for the SM83; `z80_fetch`, `z80_read`, `z80_write`,
   `z80_in`, `z80_out`, `z80_idle` and `z80_irq_ack` for the Z80. The CPU's
   header declares them.

`tools/ci_systems.py` has the same table, so a change under a CPU's folder
makes CI test the systems that use it.

## Several CPUs and systems in one program
`retrocast` links every system, so every CPU and, on the 6502, two systems
share one program. What makes that work:
- **Link symbols** are separate: the Z80 and 68000 prefix everything
  (`z80_*`, `m68k_*`), the SM83's interpreter is `gb_cpu_*`.
- **The 6502 on two systems** (the NES and the Atari 2600): each system
  implements the bus the interpreter calls (`cpu_read`, `cpu_write`), so
  each gets its own copy of the interpreter. `cpu6502_library(NAME PREFIX)`
  (`6502/CMakeLists.txt`) builds one with `CPU6502_PREFIX` defined, which
  renames `cpu_reset`, `cpu_step`, `cpu_read` and `cpu_write` (`cpu6502.h`);
  the Atari's code is compiled with the same prefix. Calls stay direct:
  the copies cost nothing at run time, and the generated switch and
  recompiled code are the same bytes for both. The Z80 (`z80_library`,
  `Z80_PREFIX`) and the 68000 (`m68k_library`, `M68K_PREFIX`) work the same
  way, for the Genesis next to the Master System and the CPS-1.
- **Names inside one file** still clash and do not need to: the `FLAG_*`
  enums of `cpu6502.h` and `sm83_cpu.h`, the static helpers of the ops
  headers (`rd`, `wr`, `fetch_k`, `op_ADC`, ...) and the 6502's template
  names (`Op`, `OPS`, `body`, ...) live in different translation units
  (each system's runtime and recompiler). Only a file including two CPUs'
  headers, or a tool linking two CPUs' templates (a combined recompiler),
  would need them prefixed.

A new CPU prefixes all of its names, as the Z80 and the 68000 do.
