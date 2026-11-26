# CPS-1 sets not supported yet

The sets of MAME 0.289's `cps1.cpp` that the game table (`runtime/games.c`)
leaves out, with the reason. `tools/cps1_gen_games.py --left` writes these rows;
the website lists them as not yet. Which sets run, and how each boots: the
[website](https://viper-bit.github.io/retrocast/cps1/).


| Set | Game | Why |
|---|---|---|
| 3wondersbi | Three Wonders (Italian bootleg) | a ROM layout the loader cannot express |
| cps1mult | CPS1 Multi Game | its own init (init_cps1mult) |
| ganbare | Ganbare! Marine Kun (Japan 2K0411) | its own init (init_ganbare) |
| gulunpa | Gulun.Pa! (Japan 931220 L) (prototype) | a ROM layout the loader cannot express |
| pmonster | Gamushara Battle! Puchi Monster (Japan 990519) | its own init (init_ganbare) |
| sf2amf | Street Fighter II': Champion Edition (Alpha Magic-F, bootleg) | a chip MAME lists as not dumped |
| sf2ceds6 | Street Fighter II': Champion Edition (Dstreet-6, bootleg) | its own memory map (MAME's sf2cems6 machine) |
| sf2cems6a | Street Fighter II': Champion Edition (Mstreet-6, bootleg, set 1) | its own memory map (MAME's sf2cems6 machine) |
| sf2cems6b | Street Fighter II': Champion Edition (Mstreet-6, bootleg, set 2) | its own memory map (MAME's sf2cems6 machine) |
| sf2cems6c | Street Fighter II': Champion Edition (Mstreet-6, bootleg, set 3) | its own memory map (MAME's sf2cems6 machine) |
| sf2ceupl | Street Fighter II': Champion Edition (Japan 920322, UPL bootleg?) | its own memory map (MAME's sf2m10 machine) |
| sf2level | Street Fighter II': Champion Edition (bootleg with level selection) | its own memory map (MAME's sf2m3 machine) |
| sf2m10 | Street Fighter II': Champion Edition (M10, bootleg) | its own memory map (MAME's sf2m10 machine) |
| sf2m3 | Street Fighter II': Champion Edition (M3, bootleg) | its own memory map (MAME's sf2m3 machine) |
| sf2m8 | Street Fighter II': Champion Edition (M8, bootleg) | its own init (init_sf2m8) |
| sf2re | Street Fighter II': Champion Edition (RE, bootleg) | its own memory map (MAME's sf2m3 machine) |
| sf2stt | Street Fighter II: The World Warrior (TAB Austria, bootleg, set 2) | a chip MAME lists as not dumped |
| varthb2 | Varth: Operation Thunderstorm (bootleg, set 2) | its own memory map (MAME's varthb2 machine) |
| varthb3 | Varth: Operation Thunderstorm (bootleg, set 3) | its own memory map (MAME's varthb3 machine) |
