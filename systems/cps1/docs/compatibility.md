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
| forgottn | Forgotten Worlds (World, newer) |  | chips missing |
| forgottna | Forgotten Worlds (World) | forgottn | no zip |
| forgottnu | Forgotten Worlds (USA, B-Board 88621B-2, Rev. C) | forgottn | no zip |
| forgottnue | Forgotten Worlds (USA, B-Board 88618B-2, Rev. E) | forgottn | no zip |
| forgottnuc | Forgotten Worlds (USA, B-Board 88618B-2, Rev. C) | forgottn | no zip |
| forgottnua | Forgotten Worlds (USA, B-Board 88618B-2, Rev. A) | forgottn | boot-tested (as forgottn.zip) |
| forgottnuaa | Forgotten Worlds (USA, B-Board 88618B-2, Rev. AA) | forgottn | no zip |
| forgottnj | Forgotten Worlds (Japan) (English prototype) | forgottn | no zip |
| lostwrld | Lost Worlds (Japan) | forgottn | chips missing |
| lostwrldo | Lost Worlds (Japan Old Ver.) | forgottn | no zip |
| ghouls | Ghouls'n Ghosts (World) |  | boot-tested |
| ghoulsu | Ghouls'n Ghosts (USA) | ghouls | boot-tested |
| daimakai | Daimakaimura (Japan) | ghouls | boot-tested |
| daimakair | Daimakaimura (Japan Resale Ver.) | ghouls | boot-tested (as daimakr2.zip) |
| strider | Strider (USA, B-Board 89624B-2) |  | boot-tested |
| striderua | Strider (USA, B-Board 89624B-3) | strider | boot-tested (as stridrua.zip) |
| strideruc | Strider (USA, B-Board 90629B-3, buggy Street Fighter II conversion) | strider | no zip |
| striderj | Strider Hiryu (Japan) | strider | boot-tested (as stridrja.zip) |
| striderjr | Strider Hiryu (Japan Resale Ver.) | strider | no zip |
| dynwar | Dynasty Wars (USA, B-Board 89624B-?) |  | boot-tested |
| dynwara | Dynasty Wars (USA, B-Board 88622B-3) | dynwar | boot-tested (as dynwaru.zip) |
| dynwarj | Tenchi wo Kurau (Japan) | dynwar | boot-tested |
| dynwarjr | Tenchi wo Kurau (Japan Resale Ver.) | dynwar | no zip |
| willow | Willow (World) |  | chips missing |
| willowu | Willow (USA) | willow | boot-tested (as willow.zip) |
| willowuo | Willow (USA Old Ver.) | willow | no zip |
| willowj | Willow (Japan) | willow | chips missing |
| unsquad | U.N. Squadron (USA) |  | boot-tested |
| area88 | Area 88 (Japan) | unsquad | boot-tested |
| area88r | Area 88 (Japan Resale Ver.) | unsquad | no zip |
| ffight | Final Fight (World, set 1) |  | boot-tested |
| ffighta | Final Fight (World, set 2) | ffight | no zip |
| ffightu | Final Fight (USA, set 1) | ffight | boot-tested |
| ffightu1 | Final Fight (USA, set 2) | ffight | no zip |
| ffightua | Final Fight (USA 900112) | ffight | boot-tested |
| ffightub | Final Fight (USA 900424) | ffight | chips missing |
| ffightuc | Final Fight (USA 900613) | ffight | boot-tested (as ffightub.zip) |
| ffightj | Final Fight (Japan) | ffight | boot-tested |
| ffightj1 | Final Fight (Japan 900112) | ffight | boot-tested (as ffightj2.zip) |
| ffightj2 | Final Fight (Japan 900305) | ffight | boot-tested (as ffightj1.zip) |
| ffightj3 | Final Fight (Japan 900405) | ffight | no zip |
| ffightj4 | Final Fight (Japan 900613) | ffight | no zip |
| ffightjh | Street Smart / Final Fight (Japan, hack) | ffight | no zip |
| ffightae | Final Fight 30th Anniversary Edition (World, hack) | ffight | no zip |
| 1941 | 1941: Counter Attack (World 900227) |  | chips missing |
| 1941r1 | 1941: Counter Attack (World) | 1941 | boot-tested (as 1941.zip) |
| 1941u | 1941: Counter Attack (USA 900227) | 1941 | no zip |
| 1941j | 1941: Counter Attack (Japan) | 1941 | chips missing |
| mercs | Mercs (World 900302) |  | boot-tested |
| mercsu | Mercs (USA 900608) | mercs | boot-tested (as mercsua.zip) |
| mercsur1 | Mercs (USA 900302) | mercs | boot-tested (as mercsu.zip) |
| mercsj | Senjou no Ookami II (Japan 900302) | mercs | boot-tested |
| mtwins | Mega Twins (World 900619) |  | boot-tested |
| chikij | Chiki Chiki Boys (Japan 900619) | mtwins | boot-tested |
| msword | Magic Sword: Heroic Fantasy (World 900725) |  | boot-tested |
| mswordr1 | Magic Sword: Heroic Fantasy (World 900623) | msword | boot-tested |
| mswordu | Magic Sword: Heroic Fantasy (USA 900725) | msword | boot-tested |
| mswordj | Magic Sword: Heroic Fantasy (Japan 900623) | msword | boot-tested |
| cawing | Carrier Air Wing (World 901012) |  | boot-tested |
| cawingr1 | Carrier Air Wing (World 901009) | cawing | boot-tested |
| cawingu | Carrier Air Wing (USA 901130) | cawing | chips missing |
| cawingur1 | Carrier Air Wing (USA 901012) | cawing | boot-tested (as cawingu.zip) |
| cawingj | U.S. Navy (Japan 901012) | cawing | boot-tested |
| cawingjr | U.S. Navy (Japan Resale Ver. 901130) | cawing | no zip |
| nemo | Nemo (World 901130) |  | boot-tested |
| nemor1 | Nemo (World 901109) | nemo | no zip |
| nemoj | Nemo (Japan 901120, 88622B-3 ROM board) | nemo | boot-tested |
| nemoja | Nemo (Japan 901120, 89625B-1 ROM board) | nemo | boot-tested (as nemoj.zip) |
| sf2 | Street Fighter II: The World Warrior (World 910522) |  | boot-tested |
| sf2ea | Street Fighter II: The World Warrior (World 910204) | sf2 | no zip |
| sf2eb | Street Fighter II: The World Warrior (World 910214) | sf2 | boot-tested |
| sf2ed | Street Fighter II: The World Warrior (World 910318) | sf2 | no zip |
| sf2ee | Street Fighter II: The World Warrior (World 910228) | sf2 | no zip |
| sf2ef | Street Fighter II: The World Warrior (World 910411) | sf2 | no zip |
| sf2em | Street Fighter II: The World Warrior (World 910129) | sf2 | no zip |
| sf2en | Street Fighter II: The World Warrior (World 910204, conversion) | sf2 | no zip |
| sf2ua | Street Fighter II: The World Warrior (USA 910206) | sf2 | boot-tested |
| sf2ub | Street Fighter II: The World Warrior (USA 910214) | sf2 | boot-tested |
| sf2uc | Street Fighter II: The World Warrior (USA 910306) | sf2 | no zip |
| sf2ud | Street Fighter II: The World Warrior (USA 910318) | sf2 | boot-tested |
| sf2ue | Street Fighter II: The World Warrior (USA 910228) | sf2 | boot-tested |
| sf2uf | Street Fighter II: The World Warrior (USA 910411) | sf2 | boot-tested |
| sf2ug | Street Fighter II: The World Warrior (USA 910522, Rev. G) | sf2 | no zip |
| sf2uh | Street Fighter II: The World Warrior (USA 910522, Rev. H) | sf2 | no zip |
| sf2ui | Street Fighter II: The World Warrior (USA 910522, Rev. I) | sf2 | boot-tested |
| sf2uk | Street Fighter II: The World Warrior (USA 911101) | sf2 | boot-tested |
| sf2um | Street Fighter II: The World Warrior (USA 920312) | sf2 | no zip |
| sf2j | Street Fighter II: The World Warrior (Japan 911210, CPS-B-13) | sf2 | boot-tested |
| sf2j17 | Street Fighter II: The World Warrior (Japan 911210, CPS-B-17) | sf2 | no zip |
| sf2ja | Street Fighter II: The World Warrior (Japan 910214) | sf2 | boot-tested |
| sf2jc | Street Fighter II: The World Warrior (Japan 910306) | sf2 | boot-tested |
| sf2jf | Street Fighter II: The World Warrior (Japan 910411) | sf2 | no zip |
| sf2jh | Street Fighter II: The World Warrior (Japan 910522) | sf2 | no zip |
| sf2jl | Street Fighter II: The World Warrior (Japan 920312) | sf2 | no zip |
| 3wonders | Three Wonders (World 910520) |  | boot-tested |
| 3wondersr1 | Three Wonders (World 910513) | 3wonders | no zip |
| 3wondersu | Three Wonders (USA 910520) | 3wonders | boot-tested (as 3wonderu.zip) |
| 3wondersb | Three Wonders (bootleg) | 3wonders | no zip |
| 3wondersh | Three Wonders (hack) | 3wonders | boot-tested (as 3wonderh.zip) |
| kod | The King of Dragons (World 910805) |  | chips missing |
| kodr1 | The King of Dragons (World 910711) | kod | boot-tested (as kod.zip) |
| kodr2 | The King of Dragons (World 910731) | kod | no zip |
| kodu | The King of Dragons (USA 910910) | kod | boot-tested |
| kodj | The King of Dragons (Japan 910805, B-Board 90629B-3) | kod | boot-tested |
| kodja | The King of Dragons (Japan 910805, B-Board 89625B-1) | kod | no zip |
| captcomm | Captain Commando (World 911202) |  | chips missing |
| captcommr1 | Captain Commando (World 911014) | captcomm | boot-tested (as captcomm.zip) |
| captcommu | Captain Commando (USA 910928) | captcomm | boot-tested (as captcomu.zip) |
| captcommj | Captain Commando (Japan 911202) | captcomm | boot-tested (as captcomj.zip) |
| captcommjr1 | Captain Commando (Japan 910928) | captcomm | no zip |
| knights | Knights of the Round (World 911127) |  | boot-tested |
| knightsu | Knights of the Round (USA 911127) | knights | boot-tested |
| knightsj | Knights of the Round (Japan 911127, B-Board 91634B-2) | knights | chips missing |
| knightsja | Knights of the Round (Japan 911127, B-Board 89625B-1) | knights | no zip |
| sf2ce | Street Fighter II': Champion Edition (World 920513) |  | chips missing |
| sf2ceea | Street Fighter II': Champion Edition (World 920313) | sf2ce | boot-tested (as sf2ce.zip) |
| sf2ceec | Street Fighter II': Champion Edition (World 920803) | sf2ce | no zip |
| sf2ceua | Street Fighter II': Champion Edition (USA 920313) | sf2ce | chips missing |
| sf2ceub | Street Fighter II': Champion Edition (USA 920513) | sf2ce | boot-tested |
| sf2ceuc | Street Fighter II': Champion Edition (USA 920803) | sf2ce | boot-tested |
| sf2cet | Street Fighter II': Champion Edition (Taiwan 920313) | sf2ce | no zip |
| sf2ceja | Street Fighter II': Champion Edition (Japan 920322) | sf2ce | no zip |
| sf2cejb | Street Fighter II': Champion Edition (Japan 920513) | sf2ce | boot-tested (as sf2cej.zip) |
| sf2cejc | Street Fighter II': Champion Edition (Japan 920803) | sf2ce | no zip |
| sf2red | Street Fighter II': Champion Edition (Red Wave, bootleg, set 1) | sf2ce | boot-tested |
| sf2v004 | Street Fighter II': Champion Edition (V004, bootleg) | sf2ce | boot-tested |
| sf2acc | Street Fighter II': Champion Edition (Accelerator!, bootleg, set 1) | sf2ce | no zip |
| sf2acca | Street Fighter II': Champion Edition (Accelerator!, bootleg, set 2) | sf2ce | no zip |
| sf2cebltw | Street Fighter II': Champion Edition ('Taiwan' bootleg with PAL) | sf2ce | no zip |
| sf2m3 | Street Fighter II': Champion Edition (M3, bootleg) | sf2ce | boot-tested |
| sf2ceupl | Street Fighter II': Champion Edition (Japan 920322, UPL bootleg?) | sf2ce | no zip |
| cworld2j | Adventure Quiz Capcom World 2 (Japan 920611) |  | boot-tested |
| cworld2ja | Adventure Quiz Capcom World 2 (Japan 920611, B-Board 90629B-3, no battery) | cworld2j | no zip |
| cworld2jb | Adventure Quiz Capcom World 2 (Japan 920611, B-Board 91634B-2) | cworld2j | no zip |
| varth | Varth: Operation Thunderstorm (World 920714) |  | boot-tested |
| varthr1 | Varth: Operation Thunderstorm (World 920612) | varth | boot-tested |
| varthu | Varth: Operation Thunderstorm (USA 920612) | varth | boot-tested |
| varthj | Varth: Operation Thunderstorm (Japan 920714) | varth | boot-tested |
| varthjr | Varth: Operation Thunderstorm (Japan Resale Ver. 920714) | varth | no zip |
| qadjr | Quiz & Dragons: Capcom Quiz Game (Japan Resale Ver. 940921) | qad | boot-tested (as qadj.zip) |
| wofhfh | Huo Feng Huang (Chinese bootleg of Sangokushi II) | wof | boot-tested |
| sf2hf | Street Fighter II': Hyper Fighting (World 921209) |  | chips missing |
| sf2hfu | Street Fighter II': Hyper Fighting (USA 921209) | sf2hf | no zip |
| sf2hfj | Street Fighter II' Turbo: Hyper Fighting (Japan 921209) | sf2hf | no zip |
| punisherbz | Biaofeng Zhanjing (Chinese bootleg of The Punisher) | punisher | no zip |
| pokonyan | Pokonyan! Balloon (Japan 940322) |  | no zip |
| mpumpkin | Magical Pumpkin: Puroland de Daibouken (Japan 960712) |  | no zip |
<!-- /sets -->

## Not supported yet

| Set | Game | Why |
|---|---|---|
| 3wondersbi | Three Wonders (Italian bootleg) | a ROM layout the loader cannot express |
| captcommb | Captain Commando (bootleg) | a ROM layout the loader cannot express |
| dino | Cadillacs and Dinosaurs (World 930201) | P7 (Q-Sound) |
| dinoa | Cadillacs and Dinosaurs (Asia TW 930223) | P7 (Q-Sound) |
| dinohunt | Dinosaur Hunter (Chinese bootleg of Cadillacs and Dinosaurs) | its own init (init_dinohunt) |
| dinoj | Cadillacs: Kyouryuu Shin Seiki (Japan 930201) | P7 (Q-Sound) |
| dinou | Cadillacs and Dinosaurs (USA 930201) | P7 (Q-Sound) |
| ganbare | Ganbare! Marine Kun (Japan 2K0411) | its own init (init_ganbare) |
| gulunpa | Gulun.Pa! (Japan 931220 L) (prototype) | a ROM layout the loader cannot express |
| knightsb2 | Knights of the Round (bootleg, World 911127) | a ROM layout the loader cannot express |
| mbomberj | Muscle Bomber: The Body Explosion (Japan 930713) | P7 (Q-Sound) |
| mbombrd | Muscle Bomber Duo: Ultimate Team Battle (World 931206) | P7 (Q-Sound) |
| mbombrdj | Muscle Bomber Duo: Heat Up Warriors (Japan 931206) | P7 (Q-Sound) |
| megaman | Mega Man: The Power Battle (CPS1, USA 951006) | P8 |
| megamana | Mega Man: The Power Battle (CPS1, Asia 951006) | P8 |
| pang3 | Pang! 3 (Europe 950601) | P8 |
| pang3b | Pang! 3 (bootleg, set 1) | P8 |
| pang3b2 | Pang! 3 (bootleg, set 2) | P8 |
| pang3b3 | Pang! 3 (bootleg, set 3) | P8 |
| pang3b4 | Pang! 3 (bootleg, set 4) | its own init (init_pang3b4) |
| pang3b5 | Pang! 3 (bootleg, set 5) | P8 |
| pang3j | Pang! 3: Kaitou Tachi no Karei na Gogo (Japan 950511) | P8 |
| pang3r1 | Pang! 3 (Europe 950511) | P8 |
| pmonster | Gamushara Battle! Puchi Monster (Japan 990519) | its own init (init_ganbare) |
| pnickj | Pnickies (Japan 940608) | P8 |
| punisher | The Punisher (World 930422) | P7 (Q-Sound) |
| punisherh | The Punisher (Hispanic 930422) | P7 (Q-Sound) |
| punisherj | The Punisher (Japan 930422) | P7 (Q-Sound) |
| punisheru | The Punisher (USA 930422) | P7 (Q-Sound) |
| qad | Quiz & Dragons: Capcom Quiz Game (USA 920701) | P8 |
| qtono2j | Quiz Tonosama no Yabou 2: Zenkoku-ban (Japan 950123) | P8 |
| rockmanj | Rockman: The Power Battle (CPS1, Japan 950922) | P8 |
| sf2accp2 | Street Fighter II': Champion Edition (Accelerator Pt.II, bootleg) | a black screen |
| sf2amf | Street Fighter II': Champion Edition (Alpha Magic-F, bootleg) | its own init (init_sf2hack) |
| sf2amf2 | Street Fighter II': Champion Edition (L735 Test Rom, bootleg, set 1) | its own init (init_sf2hack) |
| sf2amf3 | Street Fighter II': Champion Edition (L735 Test Rom, bootleg, set 2) | its own init (init_sf2hack) |
| sf2bhh | Street Fighter II': Champion Edition (Hung Hsi, bootleg) | its own init (init_sf2rb) |
| sf2ceblp | Street Fighter II': Champion Edition (protected bootleg on non-dash board) | its own init (init_sf2ceblp) |
| sf2ceds6 | Street Fighter II': Champion Edition (Dstreet-6, bootleg) | a ROM layout the loader cannot express |
| sf2cems6a | Street Fighter II': Champion Edition (Mstreet-6, bootleg, set 1) | a ROM layout the loader cannot express |
| sf2cems6b | Street Fighter II': Champion Edition (Mstreet-6, bootleg, set 2) | a ROM layout the loader cannot express |
| sf2cems6c | Street Fighter II': Champion Edition (Mstreet-6, bootleg, set 3) | a ROM layout the loader cannot express |
| sf2dkot2 | Street Fighter II': Champion Edition (Double K.O. Turbo II, bootleg) | a ROM layout the loader cannot express |
| sf2dongb | Street Fighter II': Champion Edition (Dongfang Bubai protection, bootleg) | its own init (init_sf2dongb) |
| sf2ebbl | Street Fighter II: The World Warrior (TAB Austria, bootleg, set 1) | its own init (init_sf2hack) |
| sf2ebbl2 | Street Fighter II: The World Warrior (TAB Austria, bootleg, set 3) | its own init (init_sf2hack) |
| sf2ebbl3 | Street Fighter II: The World Warrior (TAB Austria, bootleg, set 4) | its own init (init_sf2hack) |
| sf2koryu | Street Fighter II': Champion Edition (Xiang Long, Chinese bootleg) | its own init (init_sf2hack) |
| sf2level | Street Fighter II': Champion Edition (bootleg with level selection) | a ROM layout the loader cannot express |
| sf2m10 | Street Fighter II': Champion Edition (M10, bootleg) | a ROM layout the loader cannot express |
| sf2m2 | Street Fighter II': Champion Edition (M2, bootleg) | its own init (init_sf2hack) |
| sf2m4 | Street Fighter II': Champion Edition (M4, bootleg) | its own init (init_sf2hack) |
| sf2m5 | Street Fighter II': Champion Edition (M5, bootleg) | its own init (init_sf2hack) |
| sf2m6 | Street Fighter II': Champion Edition (M6, bootleg) | its own init (init_sf2hack) |
| sf2m7 | Street Fighter II': Champion Edition (M7, bootleg) | its own init (init_sf2hack) |
| sf2m8 | Street Fighter II': Champion Edition (M8, bootleg) | its own init (init_sf2m8) |
| sf2mkot | Street Fighter II': Magic KO Turbo!! - Nightmare Crack | its own init (init_sf2hack) |
| sf2qp1 | Street Fighter II: The World Warrior (Quicken Pt-I, bootleg) | a ROM layout the loader cannot express |
| sf2qp2 | Street Fighter II: The World Warrior (Quicken, bootleg) | a ROM layout the loader cannot express |
| sf2rb | Street Fighter II': Champion Edition (Rainbow, bootleg, set 1) | its own init (init_sf2rb) |
| sf2rb2 | Street Fighter II': Champion Edition (Rainbow, bootleg, set 2) | its own init (init_sf2rb2) |
| sf2rb3 | Street Fighter II': Champion Edition (Rainbow, bootleg, set 3) | a black screen |
| sf2re | Street Fighter II': Champion Edition (RE, bootleg) | a ROM layout the loader cannot express |
| sf2reda | Street Fighter II': Champion Edition (Red Wave, bootleg, set 2) | a ROM layout the loader cannot express |
| sf2rk | Street Fighter II: The World Warrior (RK, bootleg) | its own init (init_sf2rk) |
| sf2rules | Street Fighter II: The World Warrior (bootleg with rules screen) | its own init (init_sf2hack) |
| sf2stt | Street Fighter II: The World Warrior (TAB Austria, bootleg, set 2) | its own init (init_sf2hack) |
| sf2thndr | Street Fighter II: The World Warrior (Thunder Edition, bootleg, set 1) | its own init (init_sf2thndr) |
| sf2thndr2 | Street Fighter II: The World Warrior (Thunder Edition, bootleg, set 2) | its own init (init_sf2thndr) |
| sf2yyc | Street Fighter II': Champion Edition (YYC, bootleg) | its own init (init_sf2hack) |
| slammast | Saturday Night Slam Masters (World 930713) | P7 (Q-Sound) |
| slammastu | Saturday Night Slam Masters (USA 930713) | P7 (Q-Sound) |
| varthb2 | Varth: Operation Thunderstorm (bootleg, set 2) | a ROM layout the loader cannot express |
| varthb3 | Varth: Operation Thunderstorm (bootleg, set 3) | a ROM layout the loader cannot express |
| wof | Warriors of Fate (World 921031) | P7 (Q-Sound) |
| wofa | Sangokushi II (Asia 921005) | P7 (Q-Sound) |
| wofj | Tenchi wo Kurau II: Sekiheki no Tatakai (Japan 921031) | P7 (Q-Sound) |
| wofr1 | Warriors of Fate (World 921002) | P7 (Q-Sound) |
| wofu | Warriors of Fate (USA 921031) | P7 (Q-Sound) |
| wonder3 | Wonder 3 (Japan 910520) | a ROM layout the loader cannot express |
