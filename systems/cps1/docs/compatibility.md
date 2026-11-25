# CPS-1 compatibility

Temporary: the sets the CPS-1 runtime knows, until a generated page replaces
this file. Every set MAME 0.289's `cps1.cpp` lists on the boards done so
far is in the game table (`runtime/games.c`), with MAME's chips and CRCs.
"Here" is the maintainer's folder at the last run of
`python tools/cps1_audit.py FOLDER --md`: *boot-tested* (whole, run by
`TestBoot`), *chips missing*, or *no zip* (in the table, never run).
Run the same command on your own folder to see what yours lacks.

## Supported sets

<!-- sets -->
| Set | Game | Parent | Here |
|---|---|---|---|
| forgottn | Forgotten Worlds (World, newer) |  | boot-tested |
| forgottna | Forgotten Worlds (World) | forgottn | boot-tested |
| forgottnu | Forgotten Worlds (USA, B-Board 88621B-2, Rev. C) | forgottn | boot-tested |
| forgottnue | Forgotten Worlds (USA, B-Board 88618B-2, Rev. E) | forgottn | boot-tested |
| forgottnuc | Forgotten Worlds (USA, B-Board 88618B-2, Rev. C) | forgottn | boot-tested |
| forgottnua | Forgotten Worlds (USA, B-Board 88618B-2, Rev. A) | forgottn | boot-tested |
| forgottnuaa | Forgotten Worlds (USA, B-Board 88618B-2, Rev. AA) | forgottn | boot-tested |
| forgottnj | Forgotten Worlds (Japan) (English prototype) | forgottn | boot-tested |
| lostwrld | Lost Worlds (Japan) | forgottn | boot-tested |
| lostwrldo | Lost Worlds (Japan Old Ver.) | forgottn | boot-tested |
| ghouls | Ghouls'n Ghosts (World) |  | boot-tested |
| ghoulsu | Ghouls'n Ghosts (USA) | ghouls | boot-tested |
| daimakai | Daimakaimura (Japan) | ghouls | boot-tested |
| daimakair | Daimakaimura (Japan Resale Ver.) | ghouls | boot-tested |
| strider | Strider (USA, B-Board 89624B-2) |  | boot-tested |
| striderua | Strider (USA, B-Board 89624B-3) | strider | boot-tested |
| strideruc | Strider (USA, B-Board 90629B-3, buggy Street Fighter II conversion) | strider | boot-tested |
| striderj | Strider Hiryu (Japan) | strider | boot-tested |
| striderjr | Strider Hiryu (Japan Resale Ver.) | strider | boot-tested |
| dynwar | Dynasty Wars (USA, B-Board 89624B-?) |  | boot-tested |
| dynwara | Dynasty Wars (USA, B-Board 88622B-3) | dynwar | boot-tested |
| dynwarj | Tenchi wo Kurau (Japan) | dynwar | boot-tested |
| dynwarjr | Tenchi wo Kurau (Japan Resale Ver.) | dynwar | boot-tested |
| willow | Willow (World) |  | boot-tested |
| willowu | Willow (USA) | willow | boot-tested |
| willowuo | Willow (USA Old Ver.) | willow | boot-tested |
| willowj | Willow (Japan) | willow | boot-tested |
| unsquad | U.N. Squadron (USA) |  | boot-tested |
| area88 | Area 88 (Japan) | unsquad | boot-tested |
| area88r | Area 88 (Japan Resale Ver.) | unsquad | boot-tested |
| ffight | Final Fight (World, set 1) |  | boot-tested |
| ffighta | Final Fight (World, set 2) | ffight | boot-tested |
| ffightu | Final Fight (USA, set 1) | ffight | boot-tested |
| ffightu1 | Final Fight (USA, set 2) | ffight | boot-tested |
| ffightua | Final Fight (USA 900112) | ffight | boot-tested |
| ffightub | Final Fight (USA 900424) | ffight | boot-tested |
| ffightuc | Final Fight (USA 900613) | ffight | boot-tested |
| ffightj | Final Fight (Japan) | ffight | boot-tested |
| ffightj1 | Final Fight (Japan 900112) | ffight | boot-tested |
| ffightj2 | Final Fight (Japan 900305) | ffight | boot-tested |
| ffightj3 | Final Fight (Japan 900405) | ffight | boot-tested |
| ffightj4 | Final Fight (Japan 900613) | ffight | boot-tested |
| ffightjh | Street Smart / Final Fight (Japan, hack) | ffight | boot-tested |
| ffightae | Final Fight 30th Anniversary Edition (World, hack) | ffight | boot-tested |
| 1941 | 1941: Counter Attack (World 900227) |  | boot-tested |
| 1941r1 | 1941: Counter Attack (World) | 1941 | boot-tested |
| 1941u | 1941: Counter Attack (USA 900227) | 1941 | boot-tested |
| 1941j | 1941: Counter Attack (Japan) | 1941 | boot-tested |
| mercs | Mercs (World 900302) |  | boot-tested |
| mercsu | Mercs (USA 900608) | mercs | boot-tested |
| mercsur1 | Mercs (USA 900302) | mercs | boot-tested |
| mercsj | Senjou no Ookami II (Japan 900302) | mercs | boot-tested |
| mtwins | Mega Twins (World 900619) |  | boot-tested |
| chikij | Chiki Chiki Boys (Japan 900619) | mtwins | boot-tested |
| msword | Magic Sword: Heroic Fantasy (World 900725) |  | boot-tested |
| mswordr1 | Magic Sword: Heroic Fantasy (World 900623) | msword | boot-tested |
| mswordu | Magic Sword: Heroic Fantasy (USA 900725) | msword | boot-tested |
| mswordj | Magic Sword: Heroic Fantasy (Japan 900623) | msword | boot-tested |
| cawing | Carrier Air Wing (World 901012) |  | boot-tested |
| cawingr1 | Carrier Air Wing (World 901009) | cawing | boot-tested |
| cawingu | Carrier Air Wing (USA 901130) | cawing | boot-tested |
| cawingur1 | Carrier Air Wing (USA 901012) | cawing | boot-tested |
| cawingj | U.S. Navy (Japan 901012) | cawing | boot-tested |
| cawingjr | U.S. Navy (Japan Resale Ver. 901130) | cawing | boot-tested |
| nemo | Nemo (World 901130) |  | boot-tested |
| nemor1 | Nemo (World 901109) | nemo | boot-tested |
| nemoj | Nemo (Japan 901120, 88622B-3 ROM board) | nemo | boot-tested |
| nemoja | Nemo (Japan 901120, 89625B-1 ROM board) | nemo | boot-tested |
| sf2 | Street Fighter II: The World Warrior (World 910522) |  | boot-tested |
| sf2ea | Street Fighter II: The World Warrior (World 910204) | sf2 | boot-tested |
| sf2eb | Street Fighter II: The World Warrior (World 910214) | sf2 | boot-tested |
| sf2ed | Street Fighter II: The World Warrior (World 910318) | sf2 | boot-tested |
| sf2ee | Street Fighter II: The World Warrior (World 910228) | sf2 | boot-tested |
| sf2ef | Street Fighter II: The World Warrior (World 910411) | sf2 | boot-tested |
| sf2em | Street Fighter II: The World Warrior (World 910129) | sf2 | boot-tested |
| sf2en | Street Fighter II: The World Warrior (World 910204, conversion) | sf2 | boot-tested |
| sf2ua | Street Fighter II: The World Warrior (USA 910206) | sf2 | boot-tested |
| sf2ub | Street Fighter II: The World Warrior (USA 910214) | sf2 | boot-tested |
| sf2uc | Street Fighter II: The World Warrior (USA 910306) | sf2 | boot-tested |
| sf2ud | Street Fighter II: The World Warrior (USA 910318) | sf2 | boot-tested |
| sf2ue | Street Fighter II: The World Warrior (USA 910228) | sf2 | boot-tested |
| sf2uf | Street Fighter II: The World Warrior (USA 910411) | sf2 | boot-tested |
| sf2ug | Street Fighter II: The World Warrior (USA 910522, Rev. G) | sf2 | boot-tested |
| sf2uh | Street Fighter II: The World Warrior (USA 910522, Rev. H) | sf2 | boot-tested |
| sf2ui | Street Fighter II: The World Warrior (USA 910522, Rev. I) | sf2 | boot-tested |
| sf2uk | Street Fighter II: The World Warrior (USA 911101) | sf2 | boot-tested |
| sf2um | Street Fighter II: The World Warrior (USA 920312) | sf2 | boot-tested |
| sf2j | Street Fighter II: The World Warrior (Japan 911210, CPS-B-13) | sf2 | boot-tested |
| sf2j17 | Street Fighter II: The World Warrior (Japan 911210, CPS-B-17) | sf2 | boot-tested |
| sf2ja | Street Fighter II: The World Warrior (Japan 910214) | sf2 | boot-tested |
| sf2jc | Street Fighter II: The World Warrior (Japan 910306) | sf2 | boot-tested |
| sf2jf | Street Fighter II: The World Warrior (Japan 910411) | sf2 | boot-tested |
| sf2jh | Street Fighter II: The World Warrior (Japan 910522) | sf2 | boot-tested |
| sf2jl | Street Fighter II: The World Warrior (Japan 920312) | sf2 | boot-tested |
| sf2ebbl | Street Fighter II: The World Warrior (TAB Austria, bootleg, set 1) | sf2 | boot-tested |
| sf2ebbl2 | Street Fighter II: The World Warrior (TAB Austria, bootleg, set 3) | sf2 | boot-tested |
| sf2ebbl3 | Street Fighter II: The World Warrior (TAB Austria, bootleg, set 4) | sf2 | boot-tested |
| sf2rk | Street Fighter II: The World Warrior (RK, bootleg) | sf2 | boot-tested |
| sf2qp1 | Street Fighter II: The World Warrior (Quicken Pt-I, bootleg) | sf2 | boot-tested |
| sf2qp2 | Street Fighter II: The World Warrior (Quicken, bootleg) | sf2 | boot-tested |
| sf2thndr | Street Fighter II: The World Warrior (Thunder Edition, bootleg, set 1) | sf2 | boot-tested |
| sf2thndr2 | Street Fighter II: The World Warrior (Thunder Edition, bootleg, set 2) | sf2 | boot-tested |
| sf2rules | Street Fighter II: The World Warrior (bootleg with rules screen) | sf2 | boot-tested |
| 3wonders | Three Wonders (World 910520) |  | boot-tested |
| 3wondersr1 | Three Wonders (World 910513) | 3wonders | boot-tested |
| 3wondersu | Three Wonders (USA 910520) | 3wonders | boot-tested |
| wonder3 | Wonder 3 (Japan 910520) | 3wonders | boot-tested |
| 3wondersb | Three Wonders (bootleg) | 3wonders | boot-tested |
| 3wondersh | Three Wonders (hack) | 3wonders | boot-tested |
| kod | The King of Dragons (World 910805) |  | boot-tested |
| kodr1 | The King of Dragons (World 910711) | kod | boot-tested |
| kodr2 | The King of Dragons (World 910731) | kod | boot-tested |
| kodu | The King of Dragons (USA 910910) | kod | boot-tested |
| kodj | The King of Dragons (Japan 910805, B-Board 90629B-3) | kod | boot-tested |
| kodja | The King of Dragons (Japan 910805, B-Board 89625B-1) | kod | boot-tested |
| captcomm | Captain Commando (World 911202) |  | boot-tested |
| captcommr1 | Captain Commando (World 911014) | captcomm | boot-tested |
| captcommu | Captain Commando (USA 910928) | captcomm | boot-tested |
| captcommj | Captain Commando (Japan 911202) | captcomm | boot-tested |
| captcommjr1 | Captain Commando (Japan 910928) | captcomm | boot-tested |
| captcommb | Captain Commando (bootleg) | captcomm | boot-tested |
| knights | Knights of the Round (World 911127) |  | boot-tested |
| knightsu | Knights of the Round (USA 911127) | knights | boot-tested |
| knightsj | Knights of the Round (Japan 911127, B-Board 91634B-2) | knights | boot-tested |
| knightsja | Knights of the Round (Japan 911127, B-Board 89625B-1) | knights | boot-tested |
| knightsb2 | Knights of the Round (bootleg, World 911127) | knights | boot-tested |
| sf2ce | Street Fighter II': Champion Edition (World 920513) |  | boot-tested |
| sf2ceea | Street Fighter II': Champion Edition (World 920313) | sf2ce | boot-tested |
| sf2ceec | Street Fighter II': Champion Edition (World 920803) | sf2ce | boot-tested |
| sf2ceua | Street Fighter II': Champion Edition (USA 920313) | sf2ce | boot-tested |
| sf2ceub | Street Fighter II': Champion Edition (USA 920513) | sf2ce | boot-tested |
| sf2ceuc | Street Fighter II': Champion Edition (USA 920803) | sf2ce | boot-tested |
| sf2cet | Street Fighter II': Champion Edition (Taiwan 920313) | sf2ce | boot-tested |
| sf2ceja | Street Fighter II': Champion Edition (Japan 920322) | sf2ce | boot-tested |
| sf2cejb | Street Fighter II': Champion Edition (Japan 920513) | sf2ce | boot-tested |
| sf2cejc | Street Fighter II': Champion Edition (Japan 920803) | sf2ce | boot-tested |
| sf2bhh | Street Fighter II': Champion Edition (Hung Hsi, bootleg) | sf2ce | boot-tested |
| sf2cebltw | Street Fighter II': Champion Edition ('Taiwan' bootleg with PAL) | sf2ce | boot-tested |
| sf2rb | Street Fighter II': Champion Edition (Rainbow, bootleg, set 1) | sf2ce | boot-tested |
| sf2rb2 | Street Fighter II': Champion Edition (Rainbow, bootleg, set 2) | sf2ce | boot-tested |
| sf2rb3 | Street Fighter II': Champion Edition (Rainbow, bootleg, set 3) | sf2ce | boot-tested |
| sf2red | Street Fighter II': Champion Edition (Red Wave, bootleg, set 1) | sf2ce | boot-tested |
| sf2reda | Street Fighter II': Champion Edition (Red Wave, bootleg, set 2) | sf2ce | boot-tested |
| sf2redp2 | Street Fighter II': Champion Edition (Red Wave PtII, bootleg) | sf2ce | boot-tested |
| sf2v004 | Street Fighter II': Champion Edition (V004, bootleg) | sf2ce | boot-tested |
| sf2acc | Street Fighter II': Champion Edition (Accelerator!, bootleg, set 1) | sf2ce | boot-tested |
| sf2acca | Street Fighter II': Champion Edition (Accelerator!, bootleg, set 2) | sf2ce | boot-tested |
| sf2accp2 | Street Fighter II': Champion Edition (Accelerator Pt.II, bootleg) | sf2ce | boot-tested |
| sf2amf2 | Street Fighter II': Champion Edition (L735 Test Rom, bootleg, set 1) | sf2ce | boot-tested |
| sf2amf3 | Street Fighter II': Champion Edition (L735 Test Rom, bootleg, set 2) | sf2ce | boot-tested |
| sf2dkot2 | Street Fighter II': Champion Edition (Double K.O. Turbo II, bootleg) | sf2ce | boot-tested |
| sf2ceblp | Street Fighter II': Champion Edition (protected bootleg on non-dash board) | sf2ce | boot-tested |
| sf2m2 | Street Fighter II': Champion Edition (M2, bootleg) | sf2ce | boot-tested |
| sf2m4 | Street Fighter II': Champion Edition (M4, bootleg) | sf2ce | boot-tested |
| sf2m5 | Street Fighter II': Champion Edition (M5, bootleg) | sf2ce | boot-tested |
| sf2m6 | Street Fighter II': Champion Edition (M6, bootleg) | sf2ce | boot-tested |
| sf2m7 | Street Fighter II': Champion Edition (M7, bootleg) | sf2ce | boot-tested |
| sf2yyc | Street Fighter II': Champion Edition (YYC, bootleg) | sf2ce | boot-tested |
| sf2koryu | Street Fighter II': Champion Edition (Xiang Long, Chinese bootleg) | sf2ce | boot-tested |
| sf2dongb | Street Fighter II': Champion Edition (Dongfang Bubai protection, bootleg) | sf2ce | boot-tested |
| sf2mkot | Street Fighter II': Magic KO Turbo!! - Nightmare Crack | sf2ce | boot-tested |
| cworld2j | Adventure Quiz Capcom World 2 (Japan 920611) |  | boot-tested |
| cworld2ja | Adventure Quiz Capcom World 2 (Japan 920611, B-Board 90629B-3, no battery) | cworld2j | boot-tested |
| cworld2jb | Adventure Quiz Capcom World 2 (Japan 920611, B-Board 91634B-2) | cworld2j | boot-tested |
| varth | Varth: Operation Thunderstorm (World 920714) |  | boot-tested |
| varthr1 | Varth: Operation Thunderstorm (World 920612) | varth | boot-tested |
| varthu | Varth: Operation Thunderstorm (USA 920612) | varth | boot-tested |
| varthj | Varth: Operation Thunderstorm (Japan 920714) | varth | boot-tested |
| varthjr | Varth: Operation Thunderstorm (Japan Resale Ver. 920714) | varth | boot-tested |
| qad | Quiz & Dragons: Capcom Quiz Game (USA 920701) |  | boot-tested |
| qadjr | Quiz & Dragons: Capcom Quiz Game (Japan Resale Ver. 940921) | qad | boot-tested |
| wof | Warriors of Fate (World 921031) |  | boot-tested |
| wofr1 | Warriors of Fate (World 921002) | wof | boot-tested |
| wofu | Warriors of Fate (USA 921031) | wof | boot-tested |
| wofa | Sangokushi II (Asia 921005) | wof | boot-tested |
| wofj | Tenchi wo Kurau II: Sekiheki no Tatakai (Japan 921031) | wof | boot-tested |
| wofhfh | Huo Feng Huang (Chinese bootleg of Sangokushi II) | wof | boot-tested |
| sf2hf | Street Fighter II': Hyper Fighting (World 921209) |  | boot-tested |
| sf2hfu | Street Fighter II': Hyper Fighting (USA 921209) | sf2hf | boot-tested |
| sf2hfj | Street Fighter II' Turbo: Hyper Fighting (Japan 921209) | sf2hf | boot-tested |
| dino | Cadillacs and Dinosaurs (World 930201) |  | boot-tested |
| dinou | Cadillacs and Dinosaurs (USA 930201) | dino | boot-tested |
| dinoa | Cadillacs and Dinosaurs (Asia TW 930223) | dino | boot-tested |
| dinoj | Cadillacs: Kyouryuu Shin Seiki (Japan 930201) | dino | boot-tested |
| dinohunt | Dinosaur Hunter (Chinese bootleg of Cadillacs and Dinosaurs) | dino | boot-tested |
| punisher | The Punisher (World 930422) |  | boot-tested |
| punisheru | The Punisher (USA 930422) | punisher | boot-tested |
| punisherh | The Punisher (Hispanic 930422) | punisher | boot-tested |
| punisherj | The Punisher (Japan 930422) | punisher | boot-tested |
| punisherbz | Biaofeng Zhanjing (Chinese bootleg of The Punisher) | punisher | boot-tested |
| slammast | Saturday Night Slam Masters (World 930713) |  | boot-tested |
| slammastu | Saturday Night Slam Masters (USA 930713) | slammast | boot-tested |
| mbomberj | Muscle Bomber: The Body Explosion (Japan 930713) | slammast | boot-tested |
| mbombrd | Muscle Bomber Duo: Ultimate Team Battle (World 931206) |  | boot-tested |
| mbombrdj | Muscle Bomber Duo: Heat Up Warriors (Japan 931206) | mbombrd | boot-tested |
| pnickj | Pnickies (Japan 940608) |  | boot-tested |
| qtono2j | Quiz Tonosama no Yabou 2: Zenkoku-ban (Japan 950123) |  | boot-tested |
| megaman | Mega Man: The Power Battle (CPS1, USA 951006) |  | boot-tested |
| megamana | Mega Man: The Power Battle (CPS1, Asia 951006) | megaman | boot-tested |
| rockmanj | Rockman: The Power Battle (CPS1, Japan 950922) | megaman | boot-tested |
| pokonyan | Pokonyan! Balloon (Japan 940322) |  | boot-tested |
| mpumpkin | Magical Pumpkin: Puroland de Daibouken (Japan 960712) |  | boot-tested |
| pang3 | Pang! 3 (Europe 950601) |  | boot-tested |
| pang3r1 | Pang! 3 (Europe 950511) | pang3 | boot-tested |
| pang3j | Pang! 3: Kaitou Tachi no Karei na Gogo (Japan 950511) | pang3 | boot-tested |
| pang3b | Pang! 3 (bootleg, set 1) | pang3 | boot-tested |
| pang3b2 | Pang! 3 (bootleg, set 2) | pang3 | boot-tested |
| pang3b3 | Pang! 3 (bootleg, set 3) | pang3 | boot-tested |
| pang3b4 | Pang! 3 (bootleg, set 4) | pang3 | boot-tested |
| pang3b5 | Pang! 3 (bootleg, set 5) | pang3 | boot-tested |
<!-- /sets -->

## Not supported yet

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
