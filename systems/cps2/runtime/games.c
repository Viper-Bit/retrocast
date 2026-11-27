/* Generated from MAME mame0289 cps2.cpp. */
#include "roms.h"

#define N(a) (sizeof(a) / sizeof((a)[0]))
static const Cps2Load chips_ssf2_maincpu[] = {
    {"ssfe-03b", 0xaf654792, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfe.04", 0xb082aa67, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfe.05", 0x02b9c137, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfe-06b", 0x1c8e44a8, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfe.07", 0x2409001d, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2_audiocpu[] = {
    {"ssf-01a", 0x71fcdfc9, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf-01a", 0x71fcdfc9, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2_key[] = {
    {"ssf2.key", 0xe469ccbb, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2[] = {
    {"maincpu", 4194304, 0, chips_ssf2_maincpu, N(chips_ssf2_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2_gfx, N(chips_ssf2_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2_audiocpu, N(chips_ssf2_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2_qsound, N(chips_ssf2_qsound)},
    {"key", 32, 0, chips_ssf2_key, N(chips_ssf2_key)},
};
static const Cps2Load chips_ssf2r1_maincpu[] = {
    {"ssfe.03", 0xa597745d, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfe.04", 0xb082aa67, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfe.05", 0x02b9c137, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfe.06", 0x70d470c5, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfe.07", 0x2409001d, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2r1_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2r1_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2r1_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2r1_key[] = {
    {"ssf2.key", 0xe469ccbb, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2r1[] = {
    {"maincpu", 4194304, 0, chips_ssf2r1_maincpu, N(chips_ssf2r1_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2r1_gfx, N(chips_ssf2r1_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2r1_audiocpu, N(chips_ssf2r1_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2r1_qsound, N(chips_ssf2r1_qsound)},
    {"key", 32, 0, chips_ssf2r1_key, N(chips_ssf2r1_key)},
};
static const Cps2Load chips_ssf2u_maincpu[] = {
    {"ssfu.03a", 0x72f29c33, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfu.04a", 0x935cea44, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfu.05", 0xa0acb28a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfu.06", 0x47413dcf, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfu.07", 0xe6066077, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2u_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2u_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2u_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2u_key[] = {
    {"ssf2u.key", 0x2f4f8e9d, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2u[] = {
    {"maincpu", 4194304, 0, chips_ssf2u_maincpu, N(chips_ssf2u_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2u_gfx, N(chips_ssf2u_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2u_audiocpu, N(chips_ssf2u_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2u_qsound, N(chips_ssf2u_qsound)},
    {"key", 32, 0, chips_ssf2u_key, N(chips_ssf2u_key)},
};
static const Cps2Load chips_ssf2us2_maincpu[] = {
    {"ssfu.03a", 0x72f29c33, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"super stf 2 super ii rom-08 usa", 0xd48d35c9, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfu.04a", 0x935cea44, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfu.05", 0xa0acb28a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfu.06", 0x47413dcf, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"super stf 2 super ii rom-07 usa", 0x460df588, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2us2_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2us2_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2us2_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2us2_plds[] = {
    {"gal_1_super2.bin", 0x0ff45f24, 279, 0, 0, 279, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2us2_key[] = {
    {"ssf2u.key", 0x2f4f8e9d, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2us2[] = {
    {"maincpu", 4194304, 0, chips_ssf2us2_maincpu, N(chips_ssf2us2_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2us2_gfx, N(chips_ssf2us2_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2us2_audiocpu, N(chips_ssf2us2_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2us2_qsound, N(chips_ssf2us2_qsound)},
    {"plds", 279, 0, chips_ssf2us2_plds, N(chips_ssf2us2_plds)},
    {"key", 32, 0, chips_ssf2us2_key, N(chips_ssf2us2_key)},
};
static const Cps2Load chips_ssf2a_maincpu[] = {
    {"ssfa.03b", 0x83a059bf, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfa.04a", 0x5d873642, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfa.05", 0xf8fb4de2, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfa.06b", 0x3185d19d, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfa.07", 0x36e29217, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2a_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2a_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2a_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2a_key[] = {
    {"ssf2a.key", 0x5fb6013f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2a[] = {
    {"maincpu", 4194304, 0, chips_ssf2a_maincpu, N(chips_ssf2a_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2a_gfx, N(chips_ssf2a_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2a_audiocpu, N(chips_ssf2a_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2a_qsound, N(chips_ssf2a_qsound)},
    {"key", 32, 0, chips_ssf2a_key, N(chips_ssf2a_key)},
};
static const Cps2Load chips_ssf2ar1_maincpu[] = {
    {"ssfa.03a", 0xd2a3c520, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfa.04a", 0x5d873642, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfa.05", 0xf8fb4de2, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfa.06", 0xaa8acee7, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfa.07", 0x36e29217, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2ar1_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2ar1_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2ar1_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2ar1_key[] = {
    {"ssf2a.key", 0x5fb6013f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2ar1[] = {
    {"maincpu", 4194304, 0, chips_ssf2ar1_maincpu, N(chips_ssf2ar1_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2ar1_gfx, N(chips_ssf2ar1_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2ar1_audiocpu, N(chips_ssf2ar1_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2ar1_qsound, N(chips_ssf2ar1_qsound)},
    {"key", 32, 0, chips_ssf2ar1_key, N(chips_ssf2ar1_key)},
};
static const Cps2Load chips_ssf2j_maincpu[] = {
    {"ssfj.03b", 0x5c2e356d, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfj.04a", 0x013bd55c, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfj.05", 0x0918d19a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfj.06b", 0x014e0c6d, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfj.07", 0xeb6a9b1b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2j_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2j_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2j_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2j_key[] = {
    {"ssf2j.key", 0xbca45cc2, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2j[] = {
    {"maincpu", 4194304, 0, chips_ssf2j_maincpu, N(chips_ssf2j_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2j_gfx, N(chips_ssf2j_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2j_audiocpu, N(chips_ssf2j_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2j_qsound, N(chips_ssf2j_qsound)},
    {"key", 32, 0, chips_ssf2j_key, N(chips_ssf2j_key)},
};
static const Cps2Load chips_ssf2jr1_maincpu[] = {
    {"ssfj.03a", 0x0bbf1304, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfj.04a", 0x013bd55c, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfj.05", 0x0918d19a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfj.06", 0xd808a6cd, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfj.07", 0xeb6a9b1b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2jr1_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2jr1_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2jr1_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2jr1_key[] = {
    {"ssf2j.key", 0xbca45cc2, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2jr1[] = {
    {"maincpu", 4194304, 0, chips_ssf2jr1_maincpu, N(chips_ssf2jr1_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2jr1_gfx, N(chips_ssf2jr1_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2jr1_audiocpu, N(chips_ssf2jr1_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2jr1_qsound, N(chips_ssf2jr1_qsound)},
    {"key", 32, 0, chips_ssf2jr1_key, N(chips_ssf2jr1_key)},
};
static const Cps2Load chips_ssf2jr2_maincpu[] = {
    {"ssfj.03", 0x7eb0efed, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfj.04", 0xd7322164, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfj.05", 0x0918d19a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfj.06", 0xd808a6cd, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfj.07", 0xeb6a9b1b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2jr2_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2jr2_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2jr2_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2jr2_key[] = {
    {"ssf2j.key", 0xbca45cc2, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2jr2[] = {
    {"maincpu", 4194304, 0, chips_ssf2jr2_maincpu, N(chips_ssf2jr2_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2jr2_gfx, N(chips_ssf2jr2_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2jr2_audiocpu, N(chips_ssf2jr2_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2jr2_qsound, N(chips_ssf2jr2_qsound)},
    {"key", 32, 0, chips_ssf2jr2_key, N(chips_ssf2jr2_key)},
};
static const Cps2Load chips_ssf2h_maincpu[] = {
    {"ssfh.03", 0xb086b355, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfh.04", 0x1e629b29, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfh.05", 0xb5997e10, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfh.06", 0x793b8fad, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfh.07", 0xcbb92ac3, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2h_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2h_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2h_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2h_key[] = {
    {"ssf2h.key", 0x8331bc8e, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2h[] = {
    {"maincpu", 4194304, 0, chips_ssf2h_maincpu, N(chips_ssf2h_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2h_gfx, N(chips_ssf2h_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2h_audiocpu, N(chips_ssf2h_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2h_qsound, N(chips_ssf2h_qsound)},
    {"key", 32, 0, chips_ssf2h_key, N(chips_ssf2h_key)},
};
static const Cps2Load chips_ssf2tb_maincpu[] = {
    {"ssfe.03tc", 0x496a8409, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfe.04tc", 0x4b45c18b, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfe.05t", 0x6a9c6444, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfe.06tb", 0xe4944fc3, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfe.07t", 0x2c9f4782, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2tb_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2tb_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tb_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tb_key[] = {
    {"ssf2tb.key", 0x1ecc92b2, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2tb[] = {
    {"maincpu", 4194304, 0, chips_ssf2tb_maincpu, N(chips_ssf2tb_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2tb_gfx, N(chips_ssf2tb_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2tb_audiocpu, N(chips_ssf2tb_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2tb_qsound, N(chips_ssf2tb_qsound)},
    {"key", 32, 0, chips_ssf2tb_key, N(chips_ssf2tb_key)},
};
static const Cps2Load chips_ssf2tbr1_maincpu[] = {
    {"ssfe.03t", 0x1e018e34, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfe.04t", 0xac92efaf, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfe.05t", 0x6a9c6444, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfe.06t", 0xf442562b, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfe.07t", 0x2c9f4782, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2tbr1_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2tbr1_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tbr1_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tbr1_key[] = {
    {"ssf2tb.key", 0x1ecc92b2, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2tbr1[] = {
    {"maincpu", 4194304, 0, chips_ssf2tbr1_maincpu, N(chips_ssf2tbr1_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2tbr1_gfx, N(chips_ssf2tbr1_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2tbr1_audiocpu, N(chips_ssf2tbr1_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2tbr1_qsound, N(chips_ssf2tbr1_qsound)},
    {"key", 32, 0, chips_ssf2tbr1_key, N(chips_ssf2tbr1_key)},
};
static const Cps2Load chips_ssf2tbu_maincpu[] = {
    {"ssfu.03t", 0x4635b35e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfu.04t", 0x2630b3dd, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfu.05t", 0xc0293c97, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfu.06t", 0xaaa33888, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfu.07t", 0x44c54534, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2tbu_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2tbu_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tbu_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tbu_key[] = {
    {"ssf2tbu.key", 0x1da3ccf3, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2tbu[] = {
    {"maincpu", 4194304, 0, chips_ssf2tbu_maincpu, N(chips_ssf2tbu_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2tbu_gfx, N(chips_ssf2tbu_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2tbu_audiocpu, N(chips_ssf2tbu_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2tbu_qsound, N(chips_ssf2tbu_qsound)},
    {"key", 32, 0, chips_ssf2tbu_key, N(chips_ssf2tbu_key)},
};
static const Cps2Load chips_ssf2tbj_maincpu[] = {
    {"ssftj.03b", 0xe78a3433, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssftj.04t", 0xb4dc1906, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssftj.05", 0xa7e35fbc, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfj.06tb", 0x0737c30d, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfj.07t", 0x1f239515, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2tbj_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2tbj_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tbj_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tbj_key[] = {
    {"ssf2tbj.key", 0xbcc2e017, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2tbj[] = {
    {"maincpu", 4194304, 0, chips_ssf2tbj_maincpu, N(chips_ssf2tbj_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2tbj_gfx, N(chips_ssf2tbj_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2tbj_audiocpu, N(chips_ssf2tbj_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2tbj_qsound, N(chips_ssf2tbj_qsound)},
    {"key", 32, 0, chips_ssf2tbj_key, N(chips_ssf2tbj_key)},
};
static const Cps2Load chips_ssf2tbj1_maincpu[] = {
    {"ssfj.03t", 0x980d4450, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfj.04t", 0xb4dc1906, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfj.05t", 0xa7e35fbc, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfj.06t", 0xcb592b30, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfj.07t", 0x1f239515, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2tbj1_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2tbj1_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tbj1_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tbj1_key[] = {
    {"ssf2tbj.key", 0xbcc2e017, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2tbj1[] = {
    {"maincpu", 4194304, 0, chips_ssf2tbj1_maincpu, N(chips_ssf2tbj1_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2tbj1_gfx, N(chips_ssf2tbj1_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2tbj1_audiocpu, N(chips_ssf2tbj1_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2tbj1_qsound, N(chips_ssf2tbj1_qsound)},
    {"key", 32, 0, chips_ssf2tbj1_key, N(chips_ssf2tbj1_key)},
};
static const Cps2Load chips_ssf2tba_maincpu[] = {
    {"ssfa.03tb", 0x8de631d2, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfa.04ta", 0xabef3042, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfa.05t", 0xedfa018f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfa.06tb", 0x2b9d1dbc, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfa.07t", 0xf4a25159, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2tba_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2tba_audiocpu[] = {
    {"ssf-01a", 0x71fcdfc9, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf-01a", 0x71fcdfc9, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tba_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tba_key[] = {
    {"ssf2tba.key", 0x8d2740ed, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2tba[] = {
    {"maincpu", 4194304, 0, chips_ssf2tba_maincpu, N(chips_ssf2tba_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2tba_gfx, N(chips_ssf2tba_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2tba_audiocpu, N(chips_ssf2tba_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2tba_qsound, N(chips_ssf2tba_qsound)},
    {"key", 32, 0, chips_ssf2tba_key, N(chips_ssf2tba_key)},
};
static const Cps2Load chips_ssf2tbh_maincpu[] = {
    {"ssfh.03tb", 0x6db7d28b, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfh.04t", 0x0fe7d895, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfh.05t", 0x41be4f2d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfh.06tb", 0xd2522eb1, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfh.07t", 0xb1c3a3c6, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2tbh_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2tbh_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tbh_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tbh_key[] = {
    {"ssf2tbh.key", 0xfddecf4f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2tbh[] = {
    {"maincpu", 4194304, 0, chips_ssf2tbh_maincpu, N(chips_ssf2tbh_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2tbh_gfx, N(chips_ssf2tbh_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2tbh_audiocpu, N(chips_ssf2tbh_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2tbh_qsound, N(chips_ssf2tbh_qsound)},
    {"key", 32, 0, chips_ssf2tbh_key, N(chips_ssf2tbh_key)},
};
static const Cps2Load chips_ecofghtr_maincpu[] = {
    {"uece.03", 0xec2c1137, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"uece.04", 0xb35f99db, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"uece.05", 0xd9d42d31, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"uece.06", 0x9d9771cf, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ecofghtr_gfx[] = {
    {"uec.13m", 0xdcaf1436, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"uec.15m", 0x2807df41, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"uec.17m", 0x8a708d02, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"uec.19m", 0xde7be0ef, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"uec.14m", 0x1a003558, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"uec.16m", 0x4ff8a6f9, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"uec.18m", 0xb167ae12, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"uec.20m", 0x1064bdc2, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ecofghtr_audiocpu[] = {
    {"uec.01", 0xc235bd15, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"uec.01", 0xc235bd15, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ecofghtr_qsound[] = {
    {"uec.11m", 0x81b25d39, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"uec.12m", 0x27729e52, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ecofghtr_key[] = {
    {"ecofghtr.key", 0x2250fd9e, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ecofghtr[] = {
    {"maincpu", 4194304, 0, chips_ecofghtr_maincpu, N(chips_ecofghtr_maincpu)},
    {"gfx", 12582912, 0, chips_ecofghtr_gfx, N(chips_ecofghtr_gfx)},
    {"audiocpu", 327680, 0, chips_ecofghtr_audiocpu, N(chips_ecofghtr_audiocpu)},
    {"qsound", 4194304, 0, chips_ecofghtr_qsound, N(chips_ecofghtr_qsound)},
    {"key", 32, 0, chips_ecofghtr_key, N(chips_ecofghtr_key)},
};
static const Cps2Load chips_ecofghtru_maincpu[] = {
    {"uecu.03a", 0x22d88a4d, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"uecu.04a", 0x6436cfcd, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"uecu.05a", 0x336f121b, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"uecu.06a", 0x6f99d984, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ecofghtru_gfx[] = {
    {"uec.13m", 0xdcaf1436, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"uec.15m", 0x2807df41, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"uec.17m", 0x8a708d02, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"uec.19m", 0xde7be0ef, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"uec.14m", 0x1a003558, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"uec.16m", 0x4ff8a6f9, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"uec.18m", 0xb167ae12, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"uec.20m", 0x1064bdc2, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ecofghtru_audiocpu[] = {
    {"uec.01", 0xc235bd15, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"uec.01", 0xc235bd15, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ecofghtru_qsound[] = {
    {"uec.11m", 0x81b25d39, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"uec.12m", 0x27729e52, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ecofghtru_key[] = {
    {"ecofghtru.key", 0x611aa137, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ecofghtru[] = {
    {"maincpu", 4194304, 0, chips_ecofghtru_maincpu, N(chips_ecofghtru_maincpu)},
    {"gfx", 12582912, 0, chips_ecofghtru_gfx, N(chips_ecofghtru_gfx)},
    {"audiocpu", 327680, 0, chips_ecofghtru_audiocpu, N(chips_ecofghtru_audiocpu)},
    {"qsound", 4194304, 0, chips_ecofghtru_qsound, N(chips_ecofghtru_qsound)},
    {"key", 32, 0, chips_ecofghtru_key, N(chips_ecofghtru_key)},
};
static const Cps2Load chips_ecofghtru1_maincpu[] = {
    {"uecu.03", 0x6792480c, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"uecu.04", 0x95ce69d5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"uecu.05", 0x3a1e78ad, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"uecu.06", 0xa3e2f3cc, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ecofghtru1_gfx[] = {
    {"uec.13m", 0xdcaf1436, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"uec.15m", 0x2807df41, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"uec.17m", 0x8a708d02, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"uec.19m", 0xde7be0ef, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"uec.14m", 0x1a003558, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"uec.16m", 0x4ff8a6f9, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"uec.18m", 0xb167ae12, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"uec.20m", 0x1064bdc2, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ecofghtru1_audiocpu[] = {
    {"uec.01", 0xc235bd15, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"uec.01", 0xc235bd15, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ecofghtru1_qsound[] = {
    {"uec.11m", 0x81b25d39, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"uec.12m", 0x27729e52, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ecofghtru1_key[] = {
    {"ecofghtru.key", 0x611aa137, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ecofghtru1[] = {
    {"maincpu", 4194304, 0, chips_ecofghtru1_maincpu, N(chips_ecofghtru1_maincpu)},
    {"gfx", 12582912, 0, chips_ecofghtru1_gfx, N(chips_ecofghtru1_gfx)},
    {"audiocpu", 327680, 0, chips_ecofghtru1_audiocpu, N(chips_ecofghtru1_audiocpu)},
    {"qsound", 4194304, 0, chips_ecofghtru1_qsound, N(chips_ecofghtru1_qsound)},
    {"key", 32, 0, chips_ecofghtru1_key, N(chips_ecofghtru1_key)},
};
static const Cps2Load chips_uecology_maincpu[] = {
    {"uecj.03", 0x94c40a4c, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"uecj.04", 0x8d6e3a09, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"uecj.05", 0x8604ecd7, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"uecj.06", 0xb7e1d31f, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_uecology_gfx[] = {
    {"uec.13m", 0xdcaf1436, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"uec.15m", 0x2807df41, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"uec.17m", 0x8a708d02, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"uec.19m", 0xde7be0ef, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"uec.14m", 0x1a003558, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"uec.16m", 0x4ff8a6f9, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"uec.18m", 0xb167ae12, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"uec.20m", 0x1064bdc2, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_uecology_audiocpu[] = {
    {"uec.01", 0xc235bd15, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"uec.01", 0xc235bd15, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_uecology_qsound[] = {
    {"uec.11m", 0x81b25d39, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"uec.12m", 0x27729e52, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_uecology_key[] = {
    {"uecology.key", 0x0bab792d, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_uecology[] = {
    {"maincpu", 4194304, 0, chips_uecology_maincpu, N(chips_uecology_maincpu)},
    {"gfx", 12582912, 0, chips_uecology_gfx, N(chips_uecology_gfx)},
    {"audiocpu", 327680, 0, chips_uecology_audiocpu, N(chips_uecology_audiocpu)},
    {"qsound", 4194304, 0, chips_uecology_qsound, N(chips_uecology_qsound)},
    {"key", 32, 0, chips_uecology_key, N(chips_uecology_key)},
};
static const Cps2Load chips_ecofghtra_maincpu[] = {
    {"ueca.03", 0xbd4589b1, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ueca.04", 0x1d134b7d, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ueca.05", 0x9c581fc7, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ueca.06", 0xc92a7c50, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ecofghtra_gfx[] = {
    {"uec.13m", 0xdcaf1436, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"uec.15m", 0x2807df41, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"uec.17m", 0x8a708d02, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"uec.19m", 0xde7be0ef, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"uec.14m", 0x1a003558, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"uec.16m", 0x4ff8a6f9, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"uec.18m", 0xb167ae12, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"uec.20m", 0x1064bdc2, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ecofghtra_audiocpu[] = {
    {"uec.01", 0xc235bd15, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"uec.01", 0xc235bd15, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ecofghtra_qsound[] = {
    {"uec.11m", 0x81b25d39, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"uec.12m", 0x27729e52, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ecofghtra_key[] = {
    {"ecofghtra.key", 0x4f99a9f5, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ecofghtra[] = {
    {"maincpu", 4194304, 0, chips_ecofghtra_maincpu, N(chips_ecofghtra_maincpu)},
    {"gfx", 12582912, 0, chips_ecofghtra_gfx, N(chips_ecofghtra_gfx)},
    {"audiocpu", 327680, 0, chips_ecofghtra_audiocpu, N(chips_ecofghtra_audiocpu)},
    {"qsound", 4194304, 0, chips_ecofghtra_qsound, N(chips_ecofghtra_qsound)},
    {"key", 32, 0, chips_ecofghtra_key, N(chips_ecofghtra_key)},
};
static const Cps2Load chips_ecofghtrh_maincpu[] = {
    {"uech.03", 0x14c9365e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"uech.04", 0x579495dc, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"uech.05", 0x96807a8e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"uech.06", 0x682b9dbc, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ecofghtrh_gfx[] = {
    {"uec.13m", 0xdcaf1436, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"uec.15m", 0x2807df41, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"uec.17m", 0x8a708d02, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"uec.19m", 0xde7be0ef, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"uec.14m", 0x1a003558, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"uec.16m", 0x4ff8a6f9, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"uec.18m", 0xb167ae12, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"uec.20m", 0x1064bdc2, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ecofghtrh_audiocpu[] = {
    {"uec.01", 0xc235bd15, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"uec.01", 0xc235bd15, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ecofghtrh_qsound[] = {
    {"uec.11m", 0x81b25d39, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"uec.12m", 0x27729e52, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ecofghtrh_key[] = {
    {"ecofghtrh.key", 0x9a9027c8, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ecofghtrh[] = {
    {"maincpu", 4194304, 0, chips_ecofghtrh_maincpu, N(chips_ecofghtrh_maincpu)},
    {"gfx", 12582912, 0, chips_ecofghtrh_gfx, N(chips_ecofghtrh_gfx)},
    {"audiocpu", 327680, 0, chips_ecofghtrh_audiocpu, N(chips_ecofghtrh_audiocpu)},
    {"qsound", 4194304, 0, chips_ecofghtrh_qsound, N(chips_ecofghtrh_qsound)},
    {"key", 32, 0, chips_ecofghtrh_key, N(chips_ecofghtrh_key)},
};
static const Cps2Load chips_ddtod_maincpu[] = {
    {"dade.03c", 0x8e73533d, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dade.04c", 0x00c2e82e, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dade.05c", 0xea996008, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dad.06a", 0x6225495a, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dad.07a", 0xb3480ec3, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddtod_gfx[] = {
    {"dad.13m", 0xda3cb7d6, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"dad.15m", 0x92b63172, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"dad.17m", 0xb98757f5, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"dad.19m", 0x8121ce46, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"dad.14m", 0x837e6f3f, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"dad.16m", 0xf0916bdb, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"dad.18m", 0xcef393ef, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"dad.20m", 0x8953fe9e, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ddtod_audiocpu[] = {
    {"dad.01", 0x3f5e2424, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dad.01", 0x3f5e2424, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ddtod_qsound[] = {
    {"dad.11m", 0x0c499b67, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dad.12m", 0x2f0b5a4e, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddtod_key[] = {
    {"ddtod.key", 0x41dfca41, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddtod[] = {
    {"maincpu", 4194304, 0, chips_ddtod_maincpu, N(chips_ddtod_maincpu)},
    {"gfx", 12582912, 0, chips_ddtod_gfx, N(chips_ddtod_gfx)},
    {"audiocpu", 327680, 0, chips_ddtod_audiocpu, N(chips_ddtod_audiocpu)},
    {"qsound", 4194304, 0, chips_ddtod_qsound, N(chips_ddtod_qsound)},
    {"key", 32, 0, chips_ddtod_key, N(chips_ddtod_key)},
};
static const Cps2Load chips_ddtodr1_maincpu[] = {
    {"dade.03a", 0x665a035e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dade.04a", 0x02613207, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dade.05a", 0x36845996, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dad.06", 0x13aa3e56, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dad.07", 0x431cb6dd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodr1_gfx[] = {
    {"dad.13m", 0xda3cb7d6, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"dad.15m", 0x92b63172, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"dad.17m", 0xb98757f5, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"dad.19m", 0x8121ce46, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"dad.14m", 0x837e6f3f, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"dad.16m", 0xf0916bdb, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"dad.18m", 0xcef393ef, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"dad.20m", 0x8953fe9e, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ddtodr1_audiocpu[] = {
    {"dad.01", 0x3f5e2424, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dad.01", 0x3f5e2424, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ddtodr1_qsound[] = {
    {"dad.11m", 0x0c499b67, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dad.12m", 0x2f0b5a4e, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodr1_key[] = {
    {"ddtod.key", 0x41dfca41, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddtodr1[] = {
    {"maincpu", 4194304, 0, chips_ddtodr1_maincpu, N(chips_ddtodr1_maincpu)},
    {"gfx", 12582912, 0, chips_ddtodr1_gfx, N(chips_ddtodr1_gfx)},
    {"audiocpu", 327680, 0, chips_ddtodr1_audiocpu, N(chips_ddtodr1_audiocpu)},
    {"qsound", 4194304, 0, chips_ddtodr1_qsound, N(chips_ddtodr1_qsound)},
    {"key", 32, 0, chips_ddtodr1_key, N(chips_ddtodr1_key)},
};
static const Cps2Load chips_ddtodu_maincpu[] = {
    {"dadu.03b", 0xa519905f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dadu.04b", 0x52562d38, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dadu.05b", 0xee1cfbfe, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dad.06", 0x13aa3e56, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dad.07", 0x431cb6dd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodu_gfx[] = {
    {"dad.13m", 0xda3cb7d6, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"dad.15m", 0x92b63172, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"dad.17m", 0xb98757f5, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"dad.19m", 0x8121ce46, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"dad.14m", 0x837e6f3f, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"dad.16m", 0xf0916bdb, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"dad.18m", 0xcef393ef, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"dad.20m", 0x8953fe9e, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ddtodu_audiocpu[] = {
    {"dad.01", 0x3f5e2424, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dad.01", 0x3f5e2424, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ddtodu_qsound[] = {
    {"dad.11m", 0x0c499b67, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dad.12m", 0x2f0b5a4e, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodu_key[] = {
    {"ddtodu.key", 0x7c03ec9e, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddtodu[] = {
    {"maincpu", 4194304, 0, chips_ddtodu_maincpu, N(chips_ddtodu_maincpu)},
    {"gfx", 12582912, 0, chips_ddtodu_gfx, N(chips_ddtodu_gfx)},
    {"audiocpu", 327680, 0, chips_ddtodu_audiocpu, N(chips_ddtodu_audiocpu)},
    {"qsound", 4194304, 0, chips_ddtodu_qsound, N(chips_ddtodu_qsound)},
    {"key", 32, 0, chips_ddtodu_key, N(chips_ddtodu_key)},
};
static const Cps2Load chips_ddtodur1_maincpu[] = {
    {"dadu.03a", 0x4413f177, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dadu.04a", 0x168de230, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dadu.05a", 0x03d39e91, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dad.06", 0x13aa3e56, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dad.07", 0x431cb6dd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodur1_gfx[] = {
    {"dad.13m", 0xda3cb7d6, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"dad.15m", 0x92b63172, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"dad.17m", 0xb98757f5, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"dad.19m", 0x8121ce46, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"dad.14m", 0x837e6f3f, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"dad.16m", 0xf0916bdb, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"dad.18m", 0xcef393ef, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"dad.20m", 0x8953fe9e, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ddtodur1_audiocpu[] = {
    {"dad.01", 0x3f5e2424, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dad.01", 0x3f5e2424, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ddtodur1_qsound[] = {
    {"dad.11m", 0x0c499b67, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dad.12m", 0x2f0b5a4e, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodur1_key[] = {
    {"ddtodu.key", 0x7c03ec9e, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddtodur1[] = {
    {"maincpu", 4194304, 0, chips_ddtodur1_maincpu, N(chips_ddtodur1_maincpu)},
    {"gfx", 12582912, 0, chips_ddtodur1_gfx, N(chips_ddtodur1_gfx)},
    {"audiocpu", 327680, 0, chips_ddtodur1_audiocpu, N(chips_ddtodur1_audiocpu)},
    {"qsound", 4194304, 0, chips_ddtodur1_qsound, N(chips_ddtodur1_qsound)},
    {"key", 32, 0, chips_ddtodur1_key, N(chips_ddtodur1_key)},
};
static const Cps2Load chips_ddtodj_maincpu[] = {
    {"dadj.03c", 0x0b1b5798, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dadj.04c", 0xc6a2fbc8, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dadj.05c", 0x189b15fe, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dad.06a", 0x6225495a, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dad.07a", 0xb3480ec3, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodj_gfx[] = {
    {"dad.13m", 0xda3cb7d6, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"dad.15m", 0x92b63172, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"dad.17m", 0xb98757f5, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"dad.19m", 0x8121ce46, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"dad.14m", 0x837e6f3f, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"dad.16m", 0xf0916bdb, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"dad.18m", 0xcef393ef, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"dad.20m", 0x8953fe9e, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ddtodj_audiocpu[] = {
    {"dad.01", 0x3f5e2424, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dad.01", 0x3f5e2424, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ddtodj_qsound[] = {
    {"dad.11m", 0x0c499b67, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dad.12m", 0x2f0b5a4e, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodj_key[] = {
    {"ddtodj.key", 0x5414dfca, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddtodj[] = {
    {"maincpu", 4194304, 0, chips_ddtodj_maincpu, N(chips_ddtodj_maincpu)},
    {"gfx", 12582912, 0, chips_ddtodj_gfx, N(chips_ddtodj_gfx)},
    {"audiocpu", 327680, 0, chips_ddtodj_audiocpu, N(chips_ddtodj_audiocpu)},
    {"qsound", 4194304, 0, chips_ddtodj_qsound, N(chips_ddtodj_qsound)},
    {"key", 32, 0, chips_ddtodj_key, N(chips_ddtodj_key)},
};
static const Cps2Load chips_ddtodjr1_maincpu[] = {
    {"dadj.03b", 0x87606b85, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dadj.04b", 0x24d49575, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dadj.05b", 0x56ce51f7, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dad.06", 0x13aa3e56, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dad.07", 0x431cb6dd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodjr1_gfx[] = {
    {"dad.13m", 0xda3cb7d6, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"dad.15m", 0x92b63172, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"dad.17m", 0xb98757f5, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"dad.19m", 0x8121ce46, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"dad.14m", 0x837e6f3f, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"dad.16m", 0xf0916bdb, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"dad.18m", 0xcef393ef, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"dad.20m", 0x8953fe9e, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ddtodjr1_audiocpu[] = {
    {"dad.01", 0x3f5e2424, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dad.01", 0x3f5e2424, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ddtodjr1_qsound[] = {
    {"dad.11m", 0x0c499b67, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dad.12m", 0x2f0b5a4e, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodjr1_key[] = {
    {"ddtodj.key", 0x5414dfca, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddtodjr1[] = {
    {"maincpu", 4194304, 0, chips_ddtodjr1_maincpu, N(chips_ddtodjr1_maincpu)},
    {"gfx", 12582912, 0, chips_ddtodjr1_gfx, N(chips_ddtodjr1_gfx)},
    {"audiocpu", 327680, 0, chips_ddtodjr1_audiocpu, N(chips_ddtodjr1_audiocpu)},
    {"qsound", 4194304, 0, chips_ddtodjr1_qsound, N(chips_ddtodjr1_qsound)},
    {"key", 32, 0, chips_ddtodjr1_key, N(chips_ddtodjr1_key)},
};
static const Cps2Load chips_ddtodjr2_maincpu[] = {
    {"dadj.03a", 0x711638dc, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dadj.04a", 0x4869639c, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dadj.05a", 0x484c0efa, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dad.06", 0x13aa3e56, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dad.07", 0x431cb6dd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodjr2_gfx[] = {
    {"dad.13m", 0xda3cb7d6, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"dad.15m", 0x92b63172, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"dad.17m", 0xb98757f5, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"dad.19m", 0x8121ce46, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"dad.14m", 0x837e6f3f, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"dad.16m", 0xf0916bdb, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"dad.18m", 0xcef393ef, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"dad.20m", 0x8953fe9e, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ddtodjr2_audiocpu[] = {
    {"dad.01", 0x3f5e2424, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dad.01", 0x3f5e2424, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ddtodjr2_qsound[] = {
    {"dad.11m", 0x0c499b67, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dad.12m", 0x2f0b5a4e, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodjr2_key[] = {
    {"ddtodj.key", 0x5414dfca, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddtodjr2[] = {
    {"maincpu", 4194304, 0, chips_ddtodjr2_maincpu, N(chips_ddtodjr2_maincpu)},
    {"gfx", 12582912, 0, chips_ddtodjr2_gfx, N(chips_ddtodjr2_gfx)},
    {"audiocpu", 327680, 0, chips_ddtodjr2_audiocpu, N(chips_ddtodjr2_audiocpu)},
    {"qsound", 4194304, 0, chips_ddtodjr2_qsound, N(chips_ddtodjr2_qsound)},
    {"key", 32, 0, chips_ddtodjr2_key, N(chips_ddtodjr2_key)},
};
static const Cps2Load chips_ddtoda_maincpu[] = {
    {"dada.03c", 0xbf243e15, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dada.04c", 0x76551eec, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dada.05c", 0x0a0ad827, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dad.06a", 0x6225495a, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dad.07a", 0xb3480ec3, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddtoda_gfx[] = {
    {"dad.13m", 0xda3cb7d6, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"dad.15m", 0x92b63172, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"dad.17m", 0xb98757f5, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"dad.19m", 0x8121ce46, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"dad.14m", 0x837e6f3f, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"dad.16m", 0xf0916bdb, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"dad.18m", 0xcef393ef, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"dad.20m", 0x8953fe9e, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ddtoda_audiocpu[] = {
    {"dad.01", 0x3f5e2424, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dad.01", 0x3f5e2424, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ddtoda_qsound[] = {
    {"dad.11m", 0x0c499b67, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dad.12m", 0x2f0b5a4e, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddtoda_key[] = {
    {"ddtoda.key", 0xe5e8d1b8, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddtoda[] = {
    {"maincpu", 4194304, 0, chips_ddtoda_maincpu, N(chips_ddtoda_maincpu)},
    {"gfx", 12582912, 0, chips_ddtoda_gfx, N(chips_ddtoda_gfx)},
    {"audiocpu", 327680, 0, chips_ddtoda_audiocpu, N(chips_ddtoda_audiocpu)},
    {"qsound", 4194304, 0, chips_ddtoda_qsound, N(chips_ddtoda_qsound)},
    {"key", 32, 0, chips_ddtoda_key, N(chips_ddtoda_key)},
};
static const Cps2Load chips_ddtodar1_maincpu[] = {
    {"dada.03a", 0xfc6f2dd7, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dada.04a", 0xd4be4009, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dada.05a", 0x6712d1cf, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dad.06", 0x13aa3e56, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dad.07", 0x431cb6dd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodar1_gfx[] = {
    {"dad.13m", 0xda3cb7d6, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"dad.15m", 0x92b63172, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"dad.17m", 0xb98757f5, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"dad.19m", 0x8121ce46, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"dad.14m", 0x837e6f3f, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"dad.16m", 0xf0916bdb, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"dad.18m", 0xcef393ef, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"dad.20m", 0x8953fe9e, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ddtodar1_audiocpu[] = {
    {"dad.01", 0x3f5e2424, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dad.01", 0x3f5e2424, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ddtodar1_qsound[] = {
    {"dad.11m", 0x0c499b67, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dad.12m", 0x2f0b5a4e, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodar1_key[] = {
    {"ddtoda.key", 0xe5e8d1b8, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddtodar1[] = {
    {"maincpu", 4194304, 0, chips_ddtodar1_maincpu, N(chips_ddtodar1_maincpu)},
    {"gfx", 12582912, 0, chips_ddtodar1_gfx, N(chips_ddtodar1_gfx)},
    {"audiocpu", 327680, 0, chips_ddtodar1_audiocpu, N(chips_ddtodar1_audiocpu)},
    {"qsound", 4194304, 0, chips_ddtodar1_qsound, N(chips_ddtodar1_qsound)},
    {"key", 32, 0, chips_ddtodar1_key, N(chips_ddtodar1_key)},
};
static const Cps2Load chips_ddtodh_maincpu[] = {
    {"dadh.03c", 0x5750a861, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dadh.04c", 0xcfbf1b56, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dadh.05c", 0xa6e562ba, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dad.06a", 0x6225495a, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dad.07a", 0xb3480ec3, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodh_gfx[] = {
    {"dad.13m", 0xda3cb7d6, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"dad.15m", 0x92b63172, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"dad.17m", 0xb98757f5, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"dad.19m", 0x8121ce46, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"dad.14m", 0x837e6f3f, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"dad.16m", 0xf0916bdb, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"dad.18m", 0xcef393ef, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"dad.20m", 0x8953fe9e, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ddtodh_audiocpu[] = {
    {"dad.01", 0x3f5e2424, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dad.01", 0x3f5e2424, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ddtodh_qsound[] = {
    {"dad.11m", 0x0c499b67, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dad.12m", 0x2f0b5a4e, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodh_key[] = {
    {"ddtodh.key", 0x65f33a1c, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddtodh[] = {
    {"maincpu", 4194304, 0, chips_ddtodh_maincpu, N(chips_ddtodh_maincpu)},
    {"gfx", 12582912, 0, chips_ddtodh_gfx, N(chips_ddtodh_gfx)},
    {"audiocpu", 327680, 0, chips_ddtodh_audiocpu, N(chips_ddtodh_audiocpu)},
    {"qsound", 4194304, 0, chips_ddtodh_qsound, N(chips_ddtodh_qsound)},
    {"key", 32, 0, chips_ddtodh_key, N(chips_ddtodh_key)},
};
static const Cps2Load chips_ddtodhr1_maincpu[] = {
    {"dadh.03b", 0xae0cb98e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dadh.04b", 0xb5774363, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dadh.05b", 0x6ce2a485, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dad.06", 0x13aa3e56, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dad.07", 0x431cb6dd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodhr1_gfx[] = {
    {"dad.13m", 0xda3cb7d6, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"dad.15m", 0x92b63172, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"dad.17m", 0xb98757f5, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"dad.19m", 0x8121ce46, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"dad.14m", 0x837e6f3f, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"dad.16m", 0xf0916bdb, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"dad.18m", 0xcef393ef, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"dad.20m", 0x8953fe9e, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ddtodhr1_audiocpu[] = {
    {"dad.01", 0x3f5e2424, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dad.01", 0x3f5e2424, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ddtodhr1_qsound[] = {
    {"dad.11m", 0x0c499b67, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dad.12m", 0x2f0b5a4e, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodhr1_key[] = {
    {"ddtodh.key", 0x65f33a1c, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddtodhr1[] = {
    {"maincpu", 4194304, 0, chips_ddtodhr1_maincpu, N(chips_ddtodhr1_maincpu)},
    {"gfx", 12582912, 0, chips_ddtodhr1_gfx, N(chips_ddtodhr1_gfx)},
    {"audiocpu", 327680, 0, chips_ddtodhr1_audiocpu, N(chips_ddtodhr1_audiocpu)},
    {"qsound", 4194304, 0, chips_ddtodhr1_qsound, N(chips_ddtodhr1_qsound)},
    {"key", 32, 0, chips_ddtodhr1_key, N(chips_ddtodhr1_key)},
};
static const Cps2Load chips_ddtodhr2_maincpu[] = {
    {"dadh.03a", 0x43d04aa3, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dadh.04a", 0x8b8d296c, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dadh.05a", 0xdaae6b14, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dad.06", 0x13aa3e56, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dad.07", 0x431cb6dd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodhr2_gfx[] = {
    {"dad.13m", 0xda3cb7d6, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"dad.15m", 0x92b63172, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"dad.17m", 0xb98757f5, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"dad.19m", 0x8121ce46, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"dad.14m", 0x837e6f3f, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"dad.16m", 0xf0916bdb, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"dad.18m", 0xcef393ef, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"dad.20m", 0x8953fe9e, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ddtodhr2_audiocpu[] = {
    {"dad.01", 0x3f5e2424, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dad.01", 0x3f5e2424, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ddtodhr2_qsound[] = {
    {"dad.11m", 0x0c499b67, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dad.12m", 0x2f0b5a4e, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodhr2_key[] = {
    {"ddtodh.key", 0x65f33a1c, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddtodhr2[] = {
    {"maincpu", 4194304, 0, chips_ddtodhr2_maincpu, N(chips_ddtodhr2_maincpu)},
    {"gfx", 12582912, 0, chips_ddtodhr2_gfx, N(chips_ddtodhr2_gfx)},
    {"audiocpu", 327680, 0, chips_ddtodhr2_audiocpu, N(chips_ddtodhr2_audiocpu)},
    {"qsound", 4194304, 0, chips_ddtodhr2_qsound, N(chips_ddtodhr2_qsound)},
    {"key", 32, 0, chips_ddtodhr2_key, N(chips_ddtodhr2_key)},
};
static const Cps2Load chips_ssf2t_maincpu[] = {
    {"sfxe.03c", 0x2fa1f396, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfxe.04a", 0xd0bc29c6, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfxe.05", 0x65222964, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfxe.06a", 0x8fe9f531, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sfxe.07", 0x8a7d0cb6, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sfxe.08", 0x74c24062, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sfx.09", 0x642fae3f, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2t_gfx[] = {
    {"sfx.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"sfx.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"sfx.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"sfx.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"sfx.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"sfx.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"sfx.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"sfx.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
    {"sfx.21m", 0xe32854af, 1048576, 0, 12582912, 1048576, CPS2_WORD64},
    {"sfx.23m", 0x760f2927, 1048576, 0, 12582914, 1048576, CPS2_WORD64},
    {"sfx.25m", 0x1ee90208, 1048576, 0, 12582916, 1048576, CPS2_WORD64},
    {"sfx.27m", 0xf814400f, 1048576, 0, 12582918, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2t_audiocpu[] = {
    {"sfx.01", 0xb47b8835, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfx.01", 0xb47b8835, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfx.02", 0x0022633f, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2t_qsound[] = {
    {"sfx.11m", 0x9bdbd476, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfx.12m", 0xa05e3aab, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2t_key[] = {
    {"ssf2t.key", 0x524d608e, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2t[] = {
    {"maincpu", 4194304, 0, chips_ssf2t_maincpu, N(chips_ssf2t_maincpu)},
    {"gfx", 16777216, 0, chips_ssf2t_gfx, N(chips_ssf2t_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2t_audiocpu, N(chips_ssf2t_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2t_qsound, N(chips_ssf2t_qsound)},
    {"key", 32, 0, chips_ssf2t_key, N(chips_ssf2t_key)},
};
static const Cps2Load chips_ssf2ta_maincpu[] = {
    {"sfxa.03c", 0x04b9ff34, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfxa.04a", 0x16ea5f7a, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfxa.05", 0x53d61f0c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfxa.06a", 0x066d09b5, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sfxa.07", 0xa428257b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sfxa.08", 0x39be596c, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sfx.09", 0x642fae3f, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2ta_gfx[] = {
    {"sfx.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"sfx.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"sfx.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"sfx.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"sfx.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"sfx.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"sfx.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"sfx.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
    {"sfx.21m", 0xe32854af, 1048576, 0, 12582912, 1048576, CPS2_WORD64},
    {"sfx.23m", 0x760f2927, 1048576, 0, 12582914, 1048576, CPS2_WORD64},
    {"sfx.25m", 0x1ee90208, 1048576, 0, 12582916, 1048576, CPS2_WORD64},
    {"sfx.27m", 0xf814400f, 1048576, 0, 12582918, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2ta_audiocpu[] = {
    {"sfx.01", 0xb47b8835, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfx.01", 0xb47b8835, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfx.02", 0x0022633f, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2ta_qsound[] = {
    {"sfx.11m", 0x9bdbd476, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfx.12m", 0xa05e3aab, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2ta_key[] = {
    {"ssf2ta.key", 0xc11fa8e9, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2ta[] = {
    {"maincpu", 4194304, 0, chips_ssf2ta_maincpu, N(chips_ssf2ta_maincpu)},
    {"gfx", 16777216, 0, chips_ssf2ta_gfx, N(chips_ssf2ta_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2ta_audiocpu, N(chips_ssf2ta_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2ta_qsound, N(chips_ssf2ta_qsound)},
    {"key", 32, 0, chips_ssf2ta_key, N(chips_ssf2ta_key)},
};
static const Cps2Load chips_ssf2th_maincpu[] = {
    {"sfxh.03c", 0xfbe80dfe, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfxh.04a", 0xef9dd4b1, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfxh.05", 0x09e56ecc, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfxh.06a", 0xe6f210be, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sfxh.07", 0x900ba1a4, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sfxh.08", 0xc15f0424, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sfxh.09", 0x5b92b3f9, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2th_gfx[] = {
    {"sfx.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"sfx.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"sfx.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"sfx.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"sfx.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"sfx.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"sfx.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"sfx.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
    {"sfx.21m", 0xe32854af, 1048576, 0, 12582912, 1048576, CPS2_WORD64},
    {"sfx.23m", 0x760f2927, 1048576, 0, 12582914, 1048576, CPS2_WORD64},
    {"sfx.25m", 0x1ee90208, 1048576, 0, 12582916, 1048576, CPS2_WORD64},
    {"sfx.27m", 0xf814400f, 1048576, 0, 12582918, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2th_audiocpu[] = {
    {"sfx.01", 0xb47b8835, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfx.01", 0xb47b8835, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfx.02", 0x0022633f, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2th_qsound[] = {
    {"sfx.11m", 0x9bdbd476, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfx.12m", 0xa05e3aab, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2th_key[] = {
    {"ssf2th.key", 0xf6ce6a35, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2th[] = {
    {"maincpu", 4194304, 0, chips_ssf2th_maincpu, N(chips_ssf2th_maincpu)},
    {"gfx", 16777216, 0, chips_ssf2th_gfx, N(chips_ssf2th_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2th_audiocpu, N(chips_ssf2th_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2th_qsound, N(chips_ssf2th_qsound)},
    {"key", 32, 0, chips_ssf2th_key, N(chips_ssf2th_key)},
};
static const Cps2Load chips_ssf2tu_maincpu[] = {
    {"sfxu.03e", 0xd6ff689e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfxu.04a", 0x532b5ffd, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfxu.05", 0xffa3c6de, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfxu.06b", 0x83f9382b, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sfxu.07a", 0x6ab673e8, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sfxu.08", 0xb3c71810, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sfx.09", 0x642fae3f, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2tu_gfx[] = {
    {"sfx.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"sfx.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"sfx.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"sfx.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"sfx.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"sfx.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"sfx.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"sfx.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
    {"sfx.21m", 0xe32854af, 1048576, 0, 12582912, 1048576, CPS2_WORD64},
    {"sfx.23m", 0x760f2927, 1048576, 0, 12582914, 1048576, CPS2_WORD64},
    {"sfx.25m", 0x1ee90208, 1048576, 0, 12582916, 1048576, CPS2_WORD64},
    {"sfx.27m", 0xf814400f, 1048576, 0, 12582918, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2tu_audiocpu[] = {
    {"sfx.01", 0xb47b8835, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfx.01", 0xb47b8835, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfx.02", 0x0022633f, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tu_qsound[] = {
    {"sfx.11m", 0x9bdbd476, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfx.12m", 0xa05e3aab, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2tu_key[] = {
    {"ssf2tu.key", 0xf7d62def, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2tu[] = {
    {"maincpu", 4194304, 0, chips_ssf2tu_maincpu, N(chips_ssf2tu_maincpu)},
    {"gfx", 16777216, 0, chips_ssf2tu_gfx, N(chips_ssf2tu_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2tu_audiocpu, N(chips_ssf2tu_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2tu_qsound, N(chips_ssf2tu_qsound)},
    {"key", 32, 0, chips_ssf2tu_key, N(chips_ssf2tu_key)},
};
static const Cps2Load chips_ssf2tur1_maincpu[] = {
    {"sfxu.03c", 0x86e4a335, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfxu.04a", 0x532b5ffd, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfxu.05", 0xffa3c6de, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfxu.06a", 0xe4c04c99, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sfxu.07", 0xd8199e41, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sfxu.08", 0xb3c71810, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sfx.09", 0x642fae3f, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2tur1_gfx[] = {
    {"sfx.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"sfx.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"sfx.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"sfx.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"sfx.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"sfx.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"sfx.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"sfx.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
    {"sfx.21m", 0xe32854af, 1048576, 0, 12582912, 1048576, CPS2_WORD64},
    {"sfx.23m", 0x760f2927, 1048576, 0, 12582914, 1048576, CPS2_WORD64},
    {"sfx.25m", 0x1ee90208, 1048576, 0, 12582916, 1048576, CPS2_WORD64},
    {"sfx.27m", 0xf814400f, 1048576, 0, 12582918, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2tur1_audiocpu[] = {
    {"sfx.01", 0xb47b8835, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfx.01", 0xb47b8835, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfx.02", 0x0022633f, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tur1_qsound[] = {
    {"sfx.11m", 0x9bdbd476, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfx.12m", 0xa05e3aab, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2tur1_key[] = {
    {"ssf2tu.key", 0xf7d62def, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2tur1[] = {
    {"maincpu", 4194304, 0, chips_ssf2tur1_maincpu, N(chips_ssf2tur1_maincpu)},
    {"gfx", 16777216, 0, chips_ssf2tur1_gfx, N(chips_ssf2tur1_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2tur1_audiocpu, N(chips_ssf2tur1_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2tur1_qsound, N(chips_ssf2tur1_qsound)},
    {"key", 32, 0, chips_ssf2tur1_key, N(chips_ssf2tur1_key)},
};
static const Cps2Load chips_ssf2xj_maincpu[] = {
    {"sfxj.03d", 0x50b52b37, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfxj.04a", 0xaf7767b4, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfxj.05", 0xf4ff18f5, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfxj.06b", 0x413477c2, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sfxj.07a", 0xa18b3d83, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sfxj.08", 0x2de76f10, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sfx.09", 0x642fae3f, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2xj_gfx[] = {
    {"sfx.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"sfx.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"sfx.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"sfx.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"sfx.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"sfx.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"sfx.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"sfx.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
    {"sfx.21m", 0xe32854af, 1048576, 0, 12582912, 1048576, CPS2_WORD64},
    {"sfx.23m", 0x760f2927, 1048576, 0, 12582914, 1048576, CPS2_WORD64},
    {"sfx.25m", 0x1ee90208, 1048576, 0, 12582916, 1048576, CPS2_WORD64},
    {"sfx.27m", 0xf814400f, 1048576, 0, 12582918, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2xj_audiocpu[] = {
    {"sfx.01", 0xb47b8835, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfx.01", 0xb47b8835, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfx.02", 0x0022633f, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2xj_qsound[] = {
    {"sfx.11m", 0x9bdbd476, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfx.12m", 0xa05e3aab, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2xj_key[] = {
    {"ssf2xj.key", 0x160d1424, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2xj[] = {
    {"maincpu", 4194304, 0, chips_ssf2xj_maincpu, N(chips_ssf2xj_maincpu)},
    {"gfx", 16777216, 0, chips_ssf2xj_gfx, N(chips_ssf2xj_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2xj_audiocpu, N(chips_ssf2xj_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2xj_qsound, N(chips_ssf2xj_qsound)},
    {"key", 32, 0, chips_ssf2xj_key, N(chips_ssf2xj_key)},
};
static const Cps2Load chips_ssf2xjr1_maincpu[] = {
    {"sfxj.03c", 0xa7417b79, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfxj.04a", 0xaf7767b4, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfxj.05", 0xf4ff18f5, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfxj.06a", 0x260d0370, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sfxj.07", 0x1324d02a, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sfxj.08", 0x2de76f10, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sfx.09", 0x642fae3f, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2xjr1_gfx[] = {
    {"sfx.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"sfx.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"sfx.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"sfx.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"sfx.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"sfx.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"sfx.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"sfx.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
    {"sfx.21m", 0xe32854af, 1048576, 0, 12582912, 1048576, CPS2_WORD64},
    {"sfx.23m", 0x760f2927, 1048576, 0, 12582914, 1048576, CPS2_WORD64},
    {"sfx.25m", 0x1ee90208, 1048576, 0, 12582916, 1048576, CPS2_WORD64},
    {"sfx.27m", 0xf814400f, 1048576, 0, 12582918, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2xjr1_audiocpu[] = {
    {"sfx.01", 0xb47b8835, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfx.01", 0xb47b8835, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfx.02", 0x0022633f, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2xjr1_qsound[] = {
    {"sfx.11m", 0x9bdbd476, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfx.12m", 0xa05e3aab, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2xjr1_key[] = {
    {"ssf2xj.key", 0x160d1424, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2xjr1[] = {
    {"maincpu", 4194304, 0, chips_ssf2xjr1_maincpu, N(chips_ssf2xjr1_maincpu)},
    {"gfx", 16777216, 0, chips_ssf2xjr1_gfx, N(chips_ssf2xjr1_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2xjr1_audiocpu, N(chips_ssf2xjr1_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2xjr1_qsound, N(chips_ssf2xjr1_qsound)},
    {"key", 32, 0, chips_ssf2xjr1_key, N(chips_ssf2xjr1_key)},
};
static const Cps2Load chips_ssf2xjr1r_maincpu[] = {
    {"sfxo.03c", 0x2ba33dc6, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfxo.04a", 0xba663dd7, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfxo.05", 0x1321625c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfxo.06a", 0x0cc490ed, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sfxo.07", 0x64b9015e, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sfxo.08", 0xb60f4b58, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sfxo.09", 0x642fae3f, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2xjr1r_gfx[] = {
    {"ssf.69", 0xe9123f9f, 524288, 0, 0, 524288, CPS2_WORD64},
    {"ssf.70", 0x2f8201f3, 524288, 0, 2097152, 524288, CPS2_WORD64},
    {"ssf.71", 0x0fa334b4, 524288, 0, 4194304, 524288, CPS2_WORD64},
    {"ssf.72", 0xb76740d3, 524288, 0, 6291456, 524288, CPS2_WORD64},
    {"ssf.73", 0x14f058ec, 524288, 0, 8388608, 524288, CPS2_WORD64},
    {"ssf.74", 0x800c3ae9, 524288, 0, 10485760, 524288, CPS2_WORD64},
    {"sfx.75", 0x06cf540b, 524288, 0, 12582912, 524288, CPS2_WORD64},
    {"sfx.76", 0x71084e42, 524288, 0, 14680064, 524288, CPS2_WORD64},
    {"ssf.59", 0x6eb3ee4d, 524288, 0, 2, 524288, CPS2_WORD64},
    {"ssf.60", 0x2bcf1eda, 524288, 0, 2097154, 524288, CPS2_WORD64},
    {"ssf.61", 0x3330cc11, 524288, 0, 4194306, 524288, CPS2_WORD64},
    {"ssf.62", 0x96e2ead3, 524288, 0, 6291458, 524288, CPS2_WORD64},
    {"ssf.63", 0xe356a275, 524288, 0, 8388610, 524288, CPS2_WORD64},
    {"ssf.64", 0xfec5698b, 524288, 0, 10485762, 524288, CPS2_WORD64},
    {"sfx.65", 0x69da0751, 524288, 0, 12582914, 524288, CPS2_WORD64},
    {"sfx.66", 0xcc53ec15, 524288, 0, 14680066, 524288, CPS2_WORD64},
    {"ssf.79", 0xcf0d44a8, 524288, 0, 4, 524288, CPS2_WORD64},
    {"ssf.80", 0x56a153a4, 524288, 0, 2097156, 524288, CPS2_WORD64},
    {"ssf.81", 0x5484e5f6, 524288, 0, 4194308, 524288, CPS2_WORD64},
    {"ssf.82", 0xfce6b7f5, 524288, 0, 6291460, 524288, CPS2_WORD64},
    {"ssf.83", 0x042d7970, 524288, 0, 8388612, 524288, CPS2_WORD64},
    {"ssf.84", 0x88c472e6, 524288, 0, 10485764, 524288, CPS2_WORD64},
    {"sfx.85", 0xa7d66348, 524288, 0, 12582916, 524288, CPS2_WORD64},
    {"sfx.86", 0xcf9119c8, 524288, 0, 14680068, 524288, CPS2_WORD64},
    {"ssf.89", 0x6d374ad9, 524288, 0, 6, 524288, CPS2_WORD64},
    {"ssf.90", 0x34cf8bcf, 524288, 0, 2097158, 524288, CPS2_WORD64},
    {"ssf.91", 0xd796ea3f, 524288, 0, 4194310, 524288, CPS2_WORD64},
    {"ssf.92", 0xc85fb7e3, 524288, 0, 6291462, 524288, CPS2_WORD64},
    {"ssf.93", 0x6c50c2b5, 524288, 0, 8388614, 524288, CPS2_WORD64},
    {"ssf.94", 0x59549f63, 524288, 0, 10485766, 524288, CPS2_WORD64},
    {"sfx.95", 0x86c97869, 524288, 0, 12582918, 524288, CPS2_WORD64},
    {"sfx.96", 0x1c0e1989, 524288, 0, 14680070, 524288, CPS2_WORD64},
};
static const Cps2Load chips_ssf2xjr1r_audiocpu[] = {
    {"sfx.01", 0xb47b8835, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfx.01", 0xb47b8835, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfx.02", 0x0022633f, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2xjr1r_qsound[] = {
    {"ssf.51a", 0x9eda6954, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssf.52a", 0x355f6589, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssf.53a", 0xd5d08a05, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssf.54a", 0x930725eb, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssf.55a", 0x827abf3c, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"ssf.56a", 0x3919c0e5, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"ssf.57a", 0x1ba9bfa6, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"ssf.58a", 0x0c89a272, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2xjr1r_key[] = {
    {"ssf2xjr1r.key", 0x82c86e63, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2xjr1r[] = {
    {"maincpu", 4194304, 0, chips_ssf2xjr1r_maincpu, N(chips_ssf2xjr1r_maincpu)},
    {"gfx", 16777216, 0, chips_ssf2xjr1r_gfx, N(chips_ssf2xjr1r_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2xjr1r_audiocpu, N(chips_ssf2xjr1r_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2xjr1r_qsound, N(chips_ssf2xjr1r_qsound)},
    {"key", 32, 0, chips_ssf2xjr1r_key, N(chips_ssf2xjr1r_key)},
};
static const Cps2Load chips_avsp_maincpu[] = {
    {"avpe.03d", 0x774334a9, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"avpe.04d", 0x7fa83769, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"avp.05d", 0xfbfb5d7a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"avp.06", 0x190b817f, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_avsp_gfx[] = {
    {"avp.13m", 0x8f8b5ae4, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"avp.15m", 0xb00280df, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"avp.17m", 0x94403195, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"avp.19m", 0xe1981245, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"avp.14m", 0x39933b1e, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"avp.16m", 0x85412860, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"avp.18m", 0x2e2beb06, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"avp.20m", 0xe4798d1a, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_avsp_audiocpu[] = {
    {"avp.01", 0x2d3b4220, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"avp.01", 0x2d3b4220, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_avsp_qsound[] = {
    {"avp.11m", 0x83499817, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"avp.12m", 0xf4110d49, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_avsp_key[] = {
    {"avsp.key", 0xe69fa35b, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_avsp[] = {
    {"maincpu", 4194304, 0, chips_avsp_maincpu, N(chips_avsp_maincpu)},
    {"gfx", 16777216, 0, chips_avsp_gfx, N(chips_avsp_gfx)},
    {"audiocpu", 327680, 0, chips_avsp_audiocpu, N(chips_avsp_audiocpu)},
    {"qsound", 4194304, 0, chips_avsp_qsound, N(chips_avsp_qsound)},
    {"key", 32, 0, chips_avsp_key, N(chips_avsp_key)},
};
static const Cps2Load chips_avspu_maincpu[] = {
    {"avpu.03d", 0x42757950, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"avpu.04d", 0x5abcdee6, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"avp.05d", 0xfbfb5d7a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"avp.06", 0x190b817f, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_avspu_gfx[] = {
    {"avp.13m", 0x8f8b5ae4, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"avp.15m", 0xb00280df, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"avp.17m", 0x94403195, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"avp.19m", 0xe1981245, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"avp.14m", 0x39933b1e, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"avp.16m", 0x85412860, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"avp.18m", 0x2e2beb06, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"avp.20m", 0xe4798d1a, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_avspu_audiocpu[] = {
    {"avp.01", 0x2d3b4220, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"avp.01", 0x2d3b4220, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_avspu_qsound[] = {
    {"avp.11m", 0x83499817, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"avp.12m", 0xf4110d49, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_avspu_key[] = {
    {"avspu.key", 0x4e68e346, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_avspu[] = {
    {"maincpu", 4194304, 0, chips_avspu_maincpu, N(chips_avspu_maincpu)},
    {"gfx", 16777216, 0, chips_avspu_gfx, N(chips_avspu_gfx)},
    {"audiocpu", 327680, 0, chips_avspu_audiocpu, N(chips_avspu_audiocpu)},
    {"qsound", 4194304, 0, chips_avspu_qsound, N(chips_avspu_qsound)},
    {"key", 32, 0, chips_avspu_key, N(chips_avspu_key)},
};
static const Cps2Load chips_avspj_maincpu[] = {
    {"avpj.03d", 0x49799119, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"avpj.04d", 0x8cd2bba8, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"avp.05d", 0xfbfb5d7a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"avp.06", 0x190b817f, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_avspj_gfx[] = {
    {"avp.13m", 0x8f8b5ae4, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"avp.15m", 0xb00280df, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"avp.17m", 0x94403195, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"avp.19m", 0xe1981245, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"avp.14m", 0x39933b1e, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"avp.16m", 0x85412860, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"avp.18m", 0x2e2beb06, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"avp.20m", 0xe4798d1a, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_avspj_audiocpu[] = {
    {"avp.01", 0x2d3b4220, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"avp.01", 0x2d3b4220, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_avspj_qsound[] = {
    {"avp.11m", 0x83499817, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"avp.12m", 0xf4110d49, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_avspj_key[] = {
    {"avspj.key", 0x3d5ccc08, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_avspj[] = {
    {"maincpu", 4194304, 0, chips_avspj_maincpu, N(chips_avspj_maincpu)},
    {"gfx", 16777216, 0, chips_avspj_gfx, N(chips_avspj_gfx)},
    {"audiocpu", 327680, 0, chips_avspj_audiocpu, N(chips_avspj_audiocpu)},
    {"qsound", 4194304, 0, chips_avspj_qsound, N(chips_avspj_qsound)},
    {"key", 32, 0, chips_avspj_key, N(chips_avspj_key)},
};
static const Cps2Load chips_avspa_maincpu[] = {
    {"avpa.03d", 0x6c1c1858, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"avpa.04d", 0x94f50b0c, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"avp.05d", 0xfbfb5d7a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"avp.06", 0x190b817f, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_avspa_gfx[] = {
    {"avp.13m", 0x8f8b5ae4, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"avp.15m", 0xb00280df, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"avp.17m", 0x94403195, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"avp.19m", 0xe1981245, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"avp.14m", 0x39933b1e, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"avp.16m", 0x85412860, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"avp.18m", 0x2e2beb06, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"avp.20m", 0xe4798d1a, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_avspa_audiocpu[] = {
    {"avp.01", 0x2d3b4220, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"avp.01", 0x2d3b4220, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_avspa_qsound[] = {
    {"avp.11m", 0x83499817, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"avp.12m", 0xf4110d49, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_avspa_key[] = {
    {"avspa.key", 0x728efc00, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_avspa[] = {
    {"maincpu", 4194304, 0, chips_avspa_maincpu, N(chips_avspa_maincpu)},
    {"gfx", 16777216, 0, chips_avspa_gfx, N(chips_avspa_gfx)},
    {"audiocpu", 327680, 0, chips_avspa_audiocpu, N(chips_avspa_audiocpu)},
    {"qsound", 4194304, 0, chips_avspa_qsound, N(chips_avspa_qsound)},
    {"key", 32, 0, chips_avspa_key, N(chips_avspa_key)},
};
static const Cps2Load chips_avsph_maincpu[] = {
    {"avph.03d", 0x3e440447, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"avph.04d", 0xaf6fc82f, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"avp.05d", 0xfbfb5d7a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"avp.06", 0x190b817f, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_avsph_gfx[] = {
    {"avp.13m", 0x8f8b5ae4, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"avp.15m", 0xb00280df, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"avp.17m", 0x94403195, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"avp.19m", 0xe1981245, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"avp.14m", 0x39933b1e, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"avp.16m", 0x85412860, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"avp.18m", 0x2e2beb06, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"avp.20m", 0xe4798d1a, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_avsph_audiocpu[] = {
    {"avp.01", 0x2d3b4220, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"avp.01", 0x2d3b4220, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_avsph_qsound[] = {
    {"avp.11m", 0x83499817, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"avp.12m", 0xf4110d49, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_avsph_key[] = {
    {"avsph.key", 0xcae7b680, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_avsph[] = {
    {"maincpu", 4194304, 0, chips_avsph_maincpu, N(chips_avsph_maincpu)},
    {"gfx", 16777216, 0, chips_avsph_gfx, N(chips_avsph_gfx)},
    {"audiocpu", 327680, 0, chips_avsph_audiocpu, N(chips_avsph_audiocpu)},
    {"qsound", 4194304, 0, chips_avsph_qsound, N(chips_avsph_qsound)},
    {"key", 32, 0, chips_avsph_key, N(chips_avsph_key)},
};
static const Cps2Load chips_dstlk_maincpu[] = {
    {"vame.03a", 0x004c9cff, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vame.04a", 0xae413ff2, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vame.05a", 0x60678756, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vame.06a", 0x912870b3, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vame.07a", 0xdabae3e8, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vame.08a", 0x2c6e3077, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vame.09a", 0xf16db74b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vame.10a", 0x701e2147, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_dstlk_gfx[] = {
    {"vam.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vam.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vam.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vam.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vam.14m", 0xbd87243c, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"vam.16m", 0xafec855f, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"vam.18m", 0x3a033625, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"vam.20m", 0x2bff6a89, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_dstlk_audiocpu[] = {
    {"vam.01", 0x64b685d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vam.01", 0x64b685d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vam.02", 0xcf7c97c7, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_dstlk_qsound[] = {
    {"vam.11m", 0x4a39deb2, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vam.12m", 0x1a3e5c03, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_dstlk_key[] = {
    {"dstlk.key", 0xcfa46dec, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_dstlk[] = {
    {"maincpu", 4194304, 0, chips_dstlk_maincpu, N(chips_dstlk_maincpu)},
    {"gfx", 20971520, 0, chips_dstlk_gfx, N(chips_dstlk_gfx)},
    {"audiocpu", 327680, 0, chips_dstlk_audiocpu, N(chips_dstlk_audiocpu)},
    {"qsound", 4194304, 0, chips_dstlk_qsound, N(chips_dstlk_qsound)},
    {"key", 32, 0, chips_dstlk_key, N(chips_dstlk_key)},
};
static const Cps2Load chips_dstlku_maincpu[] = {
    {"vamu.03b", 0x68a6343f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vamu.04b", 0x58161453, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vamu.05b", 0xdfc038b8, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vamu.06b", 0xc3842c89, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vamu.07b", 0x25b60b6e, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vamu.08b", 0x2113c596, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vamu.09b", 0x2d1e9ae5, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vamu.10b", 0x81145622, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_dstlku_gfx[] = {
    {"vam.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vam.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vam.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vam.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vam.14m", 0xbd87243c, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"vam.16m", 0xafec855f, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"vam.18m", 0x3a033625, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"vam.20m", 0x2bff6a89, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_dstlku_audiocpu[] = {
    {"vam.01", 0x64b685d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vam.01", 0x64b685d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vam.02", 0xcf7c97c7, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_dstlku_qsound[] = {
    {"vam.11m", 0x4a39deb2, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vam.12m", 0x1a3e5c03, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_dstlku_key[] = {
    {"dstlku.key", 0xc76091ba, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_dstlku[] = {
    {"maincpu", 4194304, 0, chips_dstlku_maincpu, N(chips_dstlku_maincpu)},
    {"gfx", 20971520, 0, chips_dstlku_gfx, N(chips_dstlku_gfx)},
    {"audiocpu", 327680, 0, chips_dstlku_audiocpu, N(chips_dstlku_audiocpu)},
    {"qsound", 4194304, 0, chips_dstlku_qsound, N(chips_dstlku_qsound)},
    {"key", 32, 0, chips_dstlku_key, N(chips_dstlku_key)},
};
static const Cps2Load chips_dstlkur1_maincpu[] = {
    {"vamu.03a", 0x628899f9, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vamu.04a", 0x696d9b25, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vamu.05a", 0x673ed50a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vamu.06a", 0xf2377be7, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vamu.07a", 0xd8f498c4, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vamu.08a", 0xe6a8a1a0, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vamu.09a", 0x8dd55b24, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vamu.10a", 0xc1a3d9be, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_dstlkur1_gfx[] = {
    {"vam.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vam.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vam.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vam.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vam.14m", 0xbd87243c, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"vam.16m", 0xafec855f, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"vam.18m", 0x3a033625, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"vam.20m", 0x2bff6a89, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_dstlkur1_audiocpu[] = {
    {"vam.01", 0x64b685d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vam.01", 0x64b685d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vam.02", 0xcf7c97c7, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_dstlkur1_qsound[] = {
    {"vam.11m", 0x4a39deb2, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vam.12m", 0x1a3e5c03, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_dstlkur1_key[] = {
    {"dstlku.key", 0xc76091ba, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_dstlkur1[] = {
    {"maincpu", 4194304, 0, chips_dstlkur1_maincpu, N(chips_dstlkur1_maincpu)},
    {"gfx", 20971520, 0, chips_dstlkur1_gfx, N(chips_dstlkur1_gfx)},
    {"audiocpu", 327680, 0, chips_dstlkur1_audiocpu, N(chips_dstlkur1_audiocpu)},
    {"qsound", 4194304, 0, chips_dstlkur1_qsound, N(chips_dstlkur1_qsound)},
    {"key", 32, 0, chips_dstlkur1_key, N(chips_dstlkur1_key)},
};
static const Cps2Load chips_dstlka_maincpu[] = {
    {"vama.03a", 0x294e0bec, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vama.04a", 0xbc18e128, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vama.05a", 0xe709fa59, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vama.06a", 0x55e4d387, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vama.07a", 0x24e8f981, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vama.08a", 0x743f3a8e, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vama.09a", 0x67fa5573, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vama.10a", 0x5e03d747, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_dstlka_gfx[] = {
    {"vam.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vam.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vam.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vam.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vam.14m", 0xbd87243c, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"vam.16m", 0xafec855f, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"vam.18m", 0x3a033625, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"vam.20m", 0x2bff6a89, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_dstlka_audiocpu[] = {
    {"vam.01", 0x64b685d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vam.01", 0x64b685d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vam.02", 0xcf7c97c7, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_dstlka_qsound[] = {
    {"vam.11m", 0x4a39deb2, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vam.12m", 0x1a3e5c03, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_dstlka_key[] = {
    {"dstlka.key", 0xd31d61bc, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_dstlka[] = {
    {"maincpu", 4194304, 0, chips_dstlka_maincpu, N(chips_dstlka_maincpu)},
    {"gfx", 20971520, 0, chips_dstlka_gfx, N(chips_dstlka_gfx)},
    {"audiocpu", 327680, 0, chips_dstlka_audiocpu, N(chips_dstlka_audiocpu)},
    {"qsound", 4194304, 0, chips_dstlka_qsound, N(chips_dstlka_qsound)},
    {"key", 32, 0, chips_dstlka_key, N(chips_dstlka_key)},
};
static const Cps2Load chips_dstlkh_maincpu[] = {
    {"vamh.03c", 0x4d7b9e8f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vamh.04c", 0x2217e9a0, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vamh.05c", 0x3a05b13c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vamh.06c", 0x11d70a1c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vamh.07c", 0xdb5a8767, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vamh.08c", 0x2a4fd79b, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vamh.09c", 0x15187632, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vamh.10c", 0x192d2d81, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_dstlkh_gfx[] = {
    {"vam.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vam.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vam.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vam.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vam.14m", 0xbd87243c, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"vam.16m", 0xafec855f, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"vam.18m", 0x3a033625, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"vam.20m", 0x2bff6a89, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_dstlkh_audiocpu[] = {
    {"vam.01", 0x64b685d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vam.01", 0x64b685d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vam.02", 0xcf7c97c7, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_dstlkh_qsound[] = {
    {"vam.11m", 0x4a39deb2, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vam.12m", 0x1a3e5c03, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_dstlkh_key[] = {
    {"dstlkh.key", 0xd748cb77, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_dstlkh[] = {
    {"maincpu", 4194304, 0, chips_dstlkh_maincpu, N(chips_dstlkh_maincpu)},
    {"gfx", 20971520, 0, chips_dstlkh_gfx, N(chips_dstlkh_gfx)},
    {"audiocpu", 327680, 0, chips_dstlkh_audiocpu, N(chips_dstlkh_audiocpu)},
    {"qsound", 4194304, 0, chips_dstlkh_qsound, N(chips_dstlkh_qsound)},
    {"key", 32, 0, chips_dstlkh_key, N(chips_dstlkh_key)},
};
static const Cps2Load chips_dstlkb_maincpu[] = {
    {"vamb.03a", 0x48831596, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vamb.04a", 0x2217e9a0, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vamb.05a", 0x3a05b13c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vamb.06a", 0x11d70a1c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vamb.07a", 0xdb5a8767, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vamb.08a", 0x2a4fd79b, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vamb.09a", 0x15187632, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vamb.10a", 0x192d2d81, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_dstlkb_gfx[] = {
    {"vam.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vam.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vam.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vam.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vam.14m", 0xbd87243c, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"vam.16m", 0xafec855f, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"vam.18m", 0x3a033625, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"vam.20m", 0x2bff6a89, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_dstlkb_audiocpu[] = {
    {"vam.01", 0x64b685d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vam.01", 0x64b685d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vam.02", 0xcf7c97c7, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_dstlkb_qsound[] = {
    {"vam.11m", 0x4a39deb2, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vam.12m", 0x1a3e5c03, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_dstlkb_key[] = {
    {"dstlkb.key", 0xd748cb77, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_dstlkb[] = {
    {"maincpu", 4194304, 0, chips_dstlkb_maincpu, N(chips_dstlkb_maincpu)},
    {"gfx", 20971520, 0, chips_dstlkb_gfx, N(chips_dstlkb_gfx)},
    {"audiocpu", 327680, 0, chips_dstlkb_audiocpu, N(chips_dstlkb_audiocpu)},
    {"qsound", 4194304, 0, chips_dstlkb_qsound, N(chips_dstlkb_qsound)},
    {"key", 32, 0, chips_dstlkb_key, N(chips_dstlkb_key)},
};
static const Cps2Load chips_vampj_maincpu[] = {
    {"vamj.03a", 0xf55d3722, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vamj.04b", 0x4d9c43c4, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vamj.05a", 0x6c497e92, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vamj.06a", 0xf1bbecb6, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vamj.07a", 0x1067ad84, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vamj.08a", 0x4b89f41f, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vamj.09a", 0xfc0a4aac, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vamj.10a", 0x9270c26b, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vampj_gfx[] = {
    {"vam.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vam.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vam.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vam.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vam.14m", 0xbd87243c, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"vam.16m", 0xafec855f, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"vam.18m", 0x3a033625, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"vam.20m", 0x2bff6a89, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_vampj_audiocpu[] = {
    {"vam.01", 0x64b685d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vam.01", 0x64b685d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vam.02", 0xcf7c97c7, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vampj_qsound[] = {
    {"vam.11m", 0x4a39deb2, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vam.12m", 0x1a3e5c03, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_vampj_key[] = {
    {"vampj.key", 0x8418cc6f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vampj[] = {
    {"maincpu", 4194304, 0, chips_vampj_maincpu, N(chips_vampj_maincpu)},
    {"gfx", 20971520, 0, chips_vampj_gfx, N(chips_vampj_gfx)},
    {"audiocpu", 327680, 0, chips_vampj_audiocpu, N(chips_vampj_audiocpu)},
    {"qsound", 4194304, 0, chips_vampj_qsound, N(chips_vampj_qsound)},
    {"key", 32, 0, chips_vampj_key, N(chips_vampj_key)},
};
static const Cps2Load chips_vampja_maincpu[] = {
    {"vamj.03a", 0xf55d3722, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vamj.04a", 0xfdcbdae3, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vamj.05a", 0x6c497e92, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vamj.06a", 0xf1bbecb6, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vamj.07a", 0x1067ad84, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vamj.08a", 0x4b89f41f, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vamj.09a", 0xfc0a4aac, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vamj.10a", 0x9270c26b, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vampja_gfx[] = {
    {"vam.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vam.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vam.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vam.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vam.14m", 0xbd87243c, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"vam.16m", 0xafec855f, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"vam.18m", 0x3a033625, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"vam.20m", 0x2bff6a89, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_vampja_audiocpu[] = {
    {"vam.01", 0x64b685d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vam.01", 0x64b685d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vam.02", 0xcf7c97c7, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vampja_qsound[] = {
    {"vam.11m", 0x4a39deb2, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vam.12m", 0x1a3e5c03, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_vampja_key[] = {
    {"vampj.key", 0x8418cc6f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vampja[] = {
    {"maincpu", 4194304, 0, chips_vampja_maincpu, N(chips_vampja_maincpu)},
    {"gfx", 20971520, 0, chips_vampja_gfx, N(chips_vampja_gfx)},
    {"audiocpu", 327680, 0, chips_vampja_audiocpu, N(chips_vampja_audiocpu)},
    {"qsound", 4194304, 0, chips_vampja_qsound, N(chips_vampja_qsound)},
    {"key", 32, 0, chips_vampja_key, N(chips_vampja_key)},
};
static const Cps2Load chips_vampjr1_maincpu[] = {
    {"vamj.03", 0x8895bf77, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vamj.04", 0x5027db3d, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vamj.05", 0x97c66fdb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vamj.06", 0x9b4c3426, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vamj.07", 0x303bc4fd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vamj.08", 0x3dea3646, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vamj.09", 0xc119a827, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vamj.10", 0x46593b79, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vampjr1_gfx[] = {
    {"vam.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vam.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vam.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vam.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vam.14m", 0xbd87243c, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"vam.16m", 0xafec855f, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"vam.18m", 0x3a033625, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"vam.20m", 0x2bff6a89, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_vampjr1_audiocpu[] = {
    {"vam.01", 0x64b685d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vam.01", 0x64b685d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vam.02", 0xcf7c97c7, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vampjr1_qsound[] = {
    {"vam.11m", 0x4a39deb2, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vam.12m", 0x1a3e5c03, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_vampjr1_key[] = {
    {"vampj.key", 0x8418cc6f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vampjr1[] = {
    {"maincpu", 4194304, 0, chips_vampjr1_maincpu, N(chips_vampjr1_maincpu)},
    {"gfx", 20971520, 0, chips_vampjr1_gfx, N(chips_vampjr1_gfx)},
    {"audiocpu", 327680, 0, chips_vampjr1_audiocpu, N(chips_vampjr1_audiocpu)},
    {"qsound", 4194304, 0, chips_vampjr1_qsound, N(chips_vampjr1_qsound)},
    {"key", 32, 0, chips_vampjr1_key, N(chips_vampjr1_key)},
};
static const Cps2Load chips_ringdest_maincpu[] = {
    {"smbe.03b", 0xb8016278, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"smbe.04b", 0x18c4c447, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"smbe.05b", 0x18ebda7f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"smbe.06b", 0x89c80007, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"smb.07", 0xb9a11577, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"smb.08", 0xf931b76b, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ringdest_gfx[] = {
    {"smb.13m", 0xd9b2d1de, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"smb.15m", 0x9a766d92, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"smb.17m", 0x51800f0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"smb.19m", 0x35757e96, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"smb.14m", 0xe5bfd0e7, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"smb.16m", 0xc56c0866, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"smb.18m", 0x4ded3910, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"smb.20m", 0x26ea1ec5, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
    {"smb.21m", 0x0a08c5fc, 524288, 0, 16777216, 524288, CPS2_WORD64},
    {"smb.23m", 0x0911b6c4, 524288, 0, 16777218, 524288, CPS2_WORD64},
    {"smb.25m", 0x82d6c4ec, 524288, 0, 16777220, 524288, CPS2_WORD64},
    {"smb.27m", 0x9b48678b, 524288, 0, 16777222, 524288, CPS2_WORD64},
};
static const Cps2Load chips_ringdest_audiocpu[] = {
    {"smb.01", 0x0abc229a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"smb.01", 0x0abc229a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"smb.02", 0xd051679a, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ringdest_qsound[] = {
    {"smb.11m", 0xc56935f9, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"smb.12m", 0x955b0782, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ringdest_key[] = {
    {"ringdest.key", 0x17f9269c, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ringdest[] = {
    {"maincpu", 4194304, 0, chips_ringdest_maincpu, N(chips_ringdest_maincpu)},
    {"gfx", 18874368, 0, chips_ringdest_gfx, N(chips_ringdest_gfx)},
    {"audiocpu", 327680, 0, chips_ringdest_audiocpu, N(chips_ringdest_audiocpu)},
    {"qsound", 4194304, 0, chips_ringdest_qsound, N(chips_ringdest_qsound)},
    {"key", 32, 0, chips_ringdest_key, N(chips_ringdest_key)},
};
static const Cps2Load chips_ringdesta_maincpu[] = {
    {"smba.03a", 0xd3744dfd, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"smba.04a", 0xf32d5b4f, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"smba.05a", 0x1016454f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"smba.06a", 0x94b420cd, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"smb.07", 0xb9a11577, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"smb.08", 0xf931b76b, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ringdesta_gfx[] = {
    {"smb.13m", 0xd9b2d1de, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"smb.15m", 0x9a766d92, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"smb.17m", 0x51800f0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"smb.19m", 0x35757e96, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"smb.14m", 0xe5bfd0e7, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"smb.16m", 0xc56c0866, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"smb.18m", 0x4ded3910, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"smb.20m", 0x26ea1ec5, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
    {"smb.21m", 0x0a08c5fc, 524288, 0, 16777216, 524288, CPS2_WORD64},
    {"smb.23m", 0x0911b6c4, 524288, 0, 16777218, 524288, CPS2_WORD64},
    {"smb.25m", 0x82d6c4ec, 524288, 0, 16777220, 524288, CPS2_WORD64},
    {"smb.27m", 0x9b48678b, 524288, 0, 16777222, 524288, CPS2_WORD64},
};
static const Cps2Load chips_ringdesta_audiocpu[] = {
    {"smb.01", 0x0abc229a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"smb.01", 0x0abc229a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"smb.02", 0xd051679a, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ringdesta_qsound[] = {
    {"smb.11m", 0xc56935f9, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"smb.12m", 0x955b0782, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ringdesta_key[] = {
    {"ringdesta.key", 0x905c9065, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ringdesta[] = {
    {"maincpu", 4194304, 0, chips_ringdesta_maincpu, N(chips_ringdesta_maincpu)},
    {"gfx", 18874368, 0, chips_ringdesta_gfx, N(chips_ringdesta_gfx)},
    {"audiocpu", 327680, 0, chips_ringdesta_audiocpu, N(chips_ringdesta_audiocpu)},
    {"qsound", 4194304, 0, chips_ringdesta_qsound, N(chips_ringdesta_qsound)},
    {"key", 32, 0, chips_ringdesta_key, N(chips_ringdesta_key)},
};
static const Cps2Load chips_ringdesth_maincpu[] = {
    {"smbh.03b", 0x2e316584, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"smbh.04b", 0x9950a23a, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"smbh.05b", 0x41e0b3fc, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"smbh.06b", 0x89c80007, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"smbh.07b", 0xb9a11577, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"smbh.08b", 0xf931b76b, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ringdesth_gfx[] = {
    {"smb.13m", 0xd9b2d1de, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"smb.15m", 0x9a766d92, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"smb.17m", 0x51800f0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"smb.19m", 0x35757e96, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"smb.14m", 0xe5bfd0e7, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"smb.16m", 0xc56c0866, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"smb.18m", 0x4ded3910, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"smb.20m", 0x26ea1ec5, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
    {"smb.21m", 0x0a08c5fc, 524288, 0, 16777216, 524288, CPS2_WORD64},
    {"smb.23m", 0x0911b6c4, 524288, 0, 16777218, 524288, CPS2_WORD64},
    {"smb.25m", 0x82d6c4ec, 524288, 0, 16777220, 524288, CPS2_WORD64},
    {"smb.27m", 0x9b48678b, 524288, 0, 16777222, 524288, CPS2_WORD64},
};
static const Cps2Load chips_ringdesth_audiocpu[] = {
    {"smb.01", 0x0abc229a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"smb.01", 0x0abc229a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"smb.02", 0xd051679a, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ringdesth_qsound[] = {
    {"smb.11m", 0xc56935f9, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"smb.12m", 0x955b0782, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ringdesth_key[] = {
    {"ringdesth.key", 0xffb8d049, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ringdesth[] = {
    {"maincpu", 4194304, 0, chips_ringdesth_maincpu, N(chips_ringdesth_maincpu)},
    {"gfx", 18874368, 0, chips_ringdesth_gfx, N(chips_ringdesth_gfx)},
    {"audiocpu", 327680, 0, chips_ringdesth_audiocpu, N(chips_ringdesth_audiocpu)},
    {"qsound", 4194304, 0, chips_ringdesth_qsound, N(chips_ringdesth_qsound)},
    {"key", 32, 0, chips_ringdesth_key, N(chips_ringdesth_key)},
};
static const Cps2Load chips_ringdestb_maincpu[] = {
    {"smbb.03b", 0x234eebcc, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"smbb.04b", 0x9950a23a, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"smbb.05b", 0x41e0b3fc, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"smbb.06b", 0x89c80007, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"smbb.07b", 0xb9a11577, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"smbb.08b", 0xf931b76b, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ringdestb_gfx[] = {
    {"smb.13m", 0xd9b2d1de, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"smb.15m", 0x9a766d92, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"smb.17m", 0x51800f0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"smb.19m", 0x35757e96, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"smb.14m", 0xe5bfd0e7, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"smb.16m", 0xc56c0866, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"smb.18m", 0x4ded3910, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"smb.20m", 0x26ea1ec5, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
    {"smb.21m", 0x0a08c5fc, 524288, 0, 16777216, 524288, CPS2_WORD64},
    {"smb.23m", 0x0911b6c4, 524288, 0, 16777218, 524288, CPS2_WORD64},
    {"smb.25m", 0x82d6c4ec, 524288, 0, 16777220, 524288, CPS2_WORD64},
    {"smb.27m", 0x9b48678b, 524288, 0, 16777222, 524288, CPS2_WORD64},
};
static const Cps2Load chips_ringdestb_audiocpu[] = {
    {"smb.01", 0x0abc229a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"smb.01", 0x0abc229a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"smb.02", 0xd051679a, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ringdestb_qsound[] = {
    {"smb.11m", 0xc56935f9, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"smb.12m", 0x955b0782, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ringdestb_key[] = {
    {"ringdesth.key", 0xffb8d049, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ringdestb[] = {
    {"maincpu", 4194304, 0, chips_ringdestb_maincpu, N(chips_ringdestb_maincpu)},
    {"gfx", 18874368, 0, chips_ringdestb_gfx, N(chips_ringdestb_gfx)},
    {"audiocpu", 327680, 0, chips_ringdestb_audiocpu, N(chips_ringdestb_audiocpu)},
    {"qsound", 4194304, 0, chips_ringdestb_qsound, N(chips_ringdestb_qsound)},
    {"key", 32, 0, chips_ringdestb_key, N(chips_ringdestb_key)},
};
static const Cps2Load chips_smbomb_maincpu[] = {
    {"smbj.03a", 0x1c5613de, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"smbj.04a", 0x29071ed7, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"smbj.05a", 0xeb20bce4, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"smbj.06a", 0x94b420cd, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"smb.07", 0xb9a11577, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"smb.08", 0xf931b76b, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_smbomb_gfx[] = {
    {"smb.13m", 0xd9b2d1de, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"smb.15m", 0x9a766d92, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"smb.17m", 0x51800f0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"smb.19m", 0x35757e96, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"smb.14m", 0xe5bfd0e7, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"smb.16m", 0xc56c0866, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"smb.18m", 0x4ded3910, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"smb.20m", 0x26ea1ec5, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
    {"smb.21m", 0x0a08c5fc, 524288, 0, 16777216, 524288, CPS2_WORD64},
    {"smb.23m", 0x0911b6c4, 524288, 0, 16777218, 524288, CPS2_WORD64},
    {"smb.25m", 0x82d6c4ec, 524288, 0, 16777220, 524288, CPS2_WORD64},
    {"smb.27m", 0x9b48678b, 524288, 0, 16777222, 524288, CPS2_WORD64},
};
static const Cps2Load chips_smbomb_audiocpu[] = {
    {"smb.01", 0x0abc229a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"smb.01", 0x0abc229a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"smb.02", 0xd051679a, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_smbomb_qsound[] = {
    {"smb.11m", 0xc56935f9, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"smb.12m", 0x955b0782, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_smbomb_key[] = {
    {"smbomb.key", 0xf690069b, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_smbomb[] = {
    {"maincpu", 4194304, 0, chips_smbomb_maincpu, N(chips_smbomb_maincpu)},
    {"gfx", 18874368, 0, chips_smbomb_gfx, N(chips_smbomb_gfx)},
    {"audiocpu", 327680, 0, chips_smbomb_audiocpu, N(chips_smbomb_audiocpu)},
    {"qsound", 4194304, 0, chips_smbomb_qsound, N(chips_smbomb_qsound)},
    {"key", 32, 0, chips_smbomb_key, N(chips_smbomb_key)},
};
static const Cps2Load chips_smbombr1_maincpu[] = {
    {"smbj.03", 0x52eafb10, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"smbj.04", 0xaa6e8078, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"smbj.05", 0xb69e7d5f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"smbj.06", 0x8d857b56, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"smb.07", 0xb9a11577, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"smb.08", 0xf931b76b, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_smbombr1_gfx[] = {
    {"smb.13m", 0xd9b2d1de, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"smb.15m", 0x9a766d92, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"smb.17m", 0x51800f0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"smb.19m", 0x35757e96, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"smb.14m", 0xe5bfd0e7, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"smb.16m", 0xc56c0866, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"smb.18m", 0x4ded3910, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"smb.20m", 0x26ea1ec5, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
    {"smb.21m", 0x0a08c5fc, 524288, 0, 16777216, 524288, CPS2_WORD64},
    {"smb.23m", 0x0911b6c4, 524288, 0, 16777218, 524288, CPS2_WORD64},
    {"smb.25m", 0x82d6c4ec, 524288, 0, 16777220, 524288, CPS2_WORD64},
    {"smb.27m", 0x9b48678b, 524288, 0, 16777222, 524288, CPS2_WORD64},
};
static const Cps2Load chips_smbombr1_audiocpu[] = {
    {"smb.01", 0x0abc229a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"smb.01", 0x0abc229a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"smb.02", 0xd051679a, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_smbombr1_qsound[] = {
    {"smb.11m", 0xc56935f9, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"smb.12m", 0x955b0782, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_smbombr1_key[] = {
    {"smbomb.key", 0xf690069b, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_smbombr1[] = {
    {"maincpu", 4194304, 0, chips_smbombr1_maincpu, N(chips_smbombr1_maincpu)},
    {"gfx", 18874368, 0, chips_smbombr1_gfx, N(chips_smbombr1_gfx)},
    {"audiocpu", 327680, 0, chips_smbombr1_audiocpu, N(chips_smbombr1_audiocpu)},
    {"qsound", 4194304, 0, chips_smbombr1_qsound, N(chips_smbombr1_qsound)},
    {"key", 32, 0, chips_smbombr1_key, N(chips_smbombr1_key)},
};
static const Cps2Load chips_armwar_maincpu[] = {
    {"pwge.03c", 0x31f74931, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pwge.04c", 0x16f34f5f, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pwge.05b", 0x4403ed08, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pwg.06", 0x87a60ce8, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"pwg.07", 0xf7b148df, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"pwg.08", 0xcc62823e, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"pwg.09a", 0x4c26baee, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"pwg.10", 0x07c4fb28, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_armwar_gfx[] = {
    {"pwg.13m", 0xae8fe08e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pwg.15m", 0xdb560f58, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pwg.17m", 0xbc475b94, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pwg.19m", 0x07439ff7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"pwg.14m", 0xc3f9ba63, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"pwg.16m", 0x815b0e7b, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"pwg.18m", 0x0109c71b, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"pwg.20m", 0xeb75ffbe, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_armwar_audiocpu[] = {
    {"pwg.01", 0x18a5c0e4, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pwg.01", 0x18a5c0e4, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pwg.02", 0xc9dfffa6, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_armwar_qsound[] = {
    {"pwg.11m", 0xa78f7433, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pwg.12m", 0x77438ed0, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_armwar_key[] = {
    {"armwar.key", 0xfe979382, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_armwar[] = {
    {"maincpu", 4194304, 0, chips_armwar_maincpu, N(chips_armwar_maincpu)},
    {"gfx", 20971520, 0, chips_armwar_gfx, N(chips_armwar_gfx)},
    {"audiocpu", 327680, 0, chips_armwar_audiocpu, N(chips_armwar_audiocpu)},
    {"qsound", 4194304, 0, chips_armwar_qsound, N(chips_armwar_qsound)},
    {"key", 32, 0, chips_armwar_key, N(chips_armwar_key)},
};
static const Cps2Load chips_armwarr1_maincpu[] = {
    {"pwge.03b", 0xe822e3e9, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pwge.04b", 0x4f89de39, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pwge.05a", 0x83df24e5, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pwg.06", 0x87a60ce8, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"pwg.07", 0xf7b148df, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"pwg.08", 0xcc62823e, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"pwg.09", 0xddc85ca6, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"pwg.10", 0x07c4fb28, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_armwarr1_gfx[] = {
    {"pwg.13m", 0xae8fe08e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pwg.15m", 0xdb560f58, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pwg.17m", 0xbc475b94, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pwg.19m", 0x07439ff7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"pwg.14m", 0xc3f9ba63, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"pwg.16m", 0x815b0e7b, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"pwg.18m", 0x0109c71b, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"pwg.20m", 0xeb75ffbe, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_armwarr1_audiocpu[] = {
    {"pwg.01", 0x18a5c0e4, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pwg.01", 0x18a5c0e4, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pwg.02", 0xc9dfffa6, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_armwarr1_qsound[] = {
    {"pwg.11m", 0xa78f7433, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pwg.12m", 0x77438ed0, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_armwarr1_key[] = {
    {"armwar.key", 0xfe979382, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_armwarr1[] = {
    {"maincpu", 4194304, 0, chips_armwarr1_maincpu, N(chips_armwarr1_maincpu)},
    {"gfx", 20971520, 0, chips_armwarr1_gfx, N(chips_armwarr1_gfx)},
    {"audiocpu", 327680, 0, chips_armwarr1_audiocpu, N(chips_armwarr1_audiocpu)},
    {"qsound", 4194304, 0, chips_armwarr1_qsound, N(chips_armwarr1_qsound)},
    {"key", 32, 0, chips_armwarr1_key, N(chips_armwarr1_key)},
};
static const Cps2Load chips_armwaru_maincpu[] = {
    {"pwgu.03b", 0x8b95497a, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pwgu.04b", 0x29eb5661, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pwgu.05b", 0xa54e9e44, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pwg.06", 0x87a60ce8, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"pwg.07", 0xf7b148df, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"pwg.08", 0xcc62823e, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"pwg.09a", 0x4c26baee, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"pwg.10", 0x07c4fb28, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_armwaru_gfx[] = {
    {"pwg.13m", 0xae8fe08e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pwg.15m", 0xdb560f58, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pwg.17m", 0xbc475b94, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pwg.19m", 0x07439ff7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"pwg.14m", 0xc3f9ba63, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"pwg.16m", 0x815b0e7b, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"pwg.18m", 0x0109c71b, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"pwg.20m", 0xeb75ffbe, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_armwaru_audiocpu[] = {
    {"pwg.01", 0x18a5c0e4, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pwg.01", 0x18a5c0e4, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pwg.02", 0xc9dfffa6, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_armwaru_qsound[] = {
    {"pwg.11m", 0xa78f7433, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pwg.12m", 0x77438ed0, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_armwaru_key[] = {
    {"armwaru.key", 0xfb9aada5, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_armwaru[] = {
    {"maincpu", 4194304, 0, chips_armwaru_maincpu, N(chips_armwaru_maincpu)},
    {"gfx", 20971520, 0, chips_armwaru_gfx, N(chips_armwaru_gfx)},
    {"audiocpu", 327680, 0, chips_armwaru_audiocpu, N(chips_armwaru_audiocpu)},
    {"qsound", 4194304, 0, chips_armwaru_qsound, N(chips_armwaru_qsound)},
    {"key", 32, 0, chips_armwaru_key, N(chips_armwaru_key)},
};
static const Cps2Load chips_armwaru1_maincpu[] = {
    {"pwgu.03a", 0x73d397b1, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pwgu.04a", 0x1f1de215, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pwgu.05a", 0x835fbe73, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pwg.06", 0x87a60ce8, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"pwg.07", 0xf7b148df, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"pwg.08", 0xcc62823e, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"pwg.09", 0xddc85ca6, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"pwg.10", 0x07c4fb28, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_armwaru1_gfx[] = {
    {"pwg.13m", 0xae8fe08e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pwg.15m", 0xdb560f58, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pwg.17m", 0xbc475b94, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pwg.19m", 0x07439ff7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"pwg.14m", 0xc3f9ba63, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"pwg.16m", 0x815b0e7b, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"pwg.18m", 0x0109c71b, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"pwg.20m", 0xeb75ffbe, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_armwaru1_audiocpu[] = {
    {"pwg.01", 0x18a5c0e4, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pwg.01", 0x18a5c0e4, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pwg.02", 0xc9dfffa6, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_armwaru1_qsound[] = {
    {"pwg.11m", 0xa78f7433, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pwg.12m", 0x77438ed0, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_armwaru1_key[] = {
    {"armwaru.key", 0xfb9aada5, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_armwaru1[] = {
    {"maincpu", 4194304, 0, chips_armwaru1_maincpu, N(chips_armwaru1_maincpu)},
    {"gfx", 20971520, 0, chips_armwaru1_gfx, N(chips_armwaru1_gfx)},
    {"audiocpu", 327680, 0, chips_armwaru1_audiocpu, N(chips_armwaru1_audiocpu)},
    {"qsound", 4194304, 0, chips_armwaru1_qsound, N(chips_armwaru1_qsound)},
    {"key", 32, 0, chips_armwaru1_key, N(chips_armwaru1_key)},
};
static const Cps2Load chips_armwarb_maincpu[] = {
    {"pwgb.03b", 0xd0161e14, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pwgb.04b", 0x7fb39864, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pwgb.05b", 0x52a1c12c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pwg.06", 0x87a60ce8, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"pwg.07", 0xf7b148df, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"pwg.08", 0xcc62823e, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"pwg.09a", 0x4c26baee, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"pwg.10", 0x07c4fb28, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_armwarb_gfx[] = {
    {"pwg.13m", 0xae8fe08e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pwg.15m", 0xdb560f58, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pwg.17m", 0xbc475b94, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pwg.19m", 0x07439ff7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"pwg.14m", 0xc3f9ba63, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"pwg.16m", 0x815b0e7b, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"pwg.18m", 0x0109c71b, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"pwg.20m", 0xeb75ffbe, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_armwarb_audiocpu[] = {
    {"pwg.01", 0x18a5c0e4, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pwg.01", 0x18a5c0e4, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pwg.02", 0xc9dfffa6, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_armwarb_qsound[] = {
    {"pwg.11m", 0xa78f7433, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pwg.12m", 0x77438ed0, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_armwarb_key[] = {
    {"armwarb.key", 0xeeb97bdb, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_armwarb[] = {
    {"maincpu", 4194304, 0, chips_armwarb_maincpu, N(chips_armwarb_maincpu)},
    {"gfx", 20971520, 0, chips_armwarb_gfx, N(chips_armwarb_gfx)},
    {"audiocpu", 327680, 0, chips_armwarb_audiocpu, N(chips_armwarb_audiocpu)},
    {"qsound", 4194304, 0, chips_armwarb_qsound, N(chips_armwarb_qsound)},
    {"key", 32, 0, chips_armwarb_key, N(chips_armwarb_key)},
};
static const Cps2Load chips_pgear_maincpu[] = {
    {"pwgj.03a", 0xc79c0c02, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pwgj.04a", 0x167c6ed8, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pwgj.05a", 0xa63fb400, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pwg.06", 0x87a60ce8, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"pwg.07", 0xf7b148df, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"pwg.08", 0xcc62823e, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"pwg.09a", 0x4c26baee, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"pwg.10", 0x07c4fb28, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_pgear_gfx[] = {
    {"pwg.13m", 0xae8fe08e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pwg.15m", 0xdb560f58, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pwg.17m", 0xbc475b94, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pwg.19m", 0x07439ff7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"pwg.14m", 0xc3f9ba63, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"pwg.16m", 0x815b0e7b, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"pwg.18m", 0x0109c71b, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"pwg.20m", 0xeb75ffbe, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_pgear_audiocpu[] = {
    {"pwg.01", 0x18a5c0e4, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pwg.01", 0x18a5c0e4, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pwg.02", 0xc9dfffa6, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_pgear_qsound[] = {
    {"pwg.11m", 0xa78f7433, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pwg.12m", 0x77438ed0, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_pgear_key[] = {
    {"pgear.key", 0xc576d6fd, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_pgear[] = {
    {"maincpu", 4194304, 0, chips_pgear_maincpu, N(chips_pgear_maincpu)},
    {"gfx", 20971520, 0, chips_pgear_gfx, N(chips_pgear_gfx)},
    {"audiocpu", 327680, 0, chips_pgear_audiocpu, N(chips_pgear_audiocpu)},
    {"qsound", 4194304, 0, chips_pgear_qsound, N(chips_pgear_qsound)},
    {"key", 32, 0, chips_pgear_key, N(chips_pgear_key)},
};
static const Cps2Load chips_pgearr1_maincpu[] = {
    {"pwgj.03", 0xf264e74b, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pwgj.04", 0x23a84983, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pwgj.05", 0xbef58c62, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pwg.06", 0x87a60ce8, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"pwg.07", 0xf7b148df, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"pwg.08", 0xcc62823e, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"pwg.09", 0xddc85ca6, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"pwg.10", 0x07c4fb28, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_pgearr1_gfx[] = {
    {"pwg.13m", 0xae8fe08e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pwg.15m", 0xdb560f58, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pwg.17m", 0xbc475b94, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pwg.19m", 0x07439ff7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"pwg.14m", 0xc3f9ba63, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"pwg.16m", 0x815b0e7b, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"pwg.18m", 0x0109c71b, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"pwg.20m", 0xeb75ffbe, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_pgearr1_audiocpu[] = {
    {"pwg.01", 0x18a5c0e4, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pwg.01", 0x18a5c0e4, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pwg.02", 0xc9dfffa6, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_pgearr1_qsound[] = {
    {"pwg.11m", 0xa78f7433, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pwg.12m", 0x77438ed0, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_pgearr1_key[] = {
    {"pgear.key", 0xc576d6fd, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_pgearr1[] = {
    {"maincpu", 4194304, 0, chips_pgearr1_maincpu, N(chips_pgearr1_maincpu)},
    {"gfx", 20971520, 0, chips_pgearr1_gfx, N(chips_pgearr1_gfx)},
    {"audiocpu", 327680, 0, chips_pgearr1_audiocpu, N(chips_pgearr1_audiocpu)},
    {"qsound", 4194304, 0, chips_pgearr1_qsound, N(chips_pgearr1_qsound)},
    {"key", 32, 0, chips_pgearr1_key, N(chips_pgearr1_key)},
};
static const Cps2Load chips_armwara_maincpu[] = {
    {"pwga.03b", 0x347743e1, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pwga.04b", 0x42dbfb2e, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pwga.05b", 0x835fbe73, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pwg.06", 0x87a60ce8, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"pwg.07", 0xf7b148df, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"pwg.08", 0xcc62823e, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"pwg.09a", 0x4c26baee, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"pwg.10", 0x07c4fb28, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_armwara_gfx[] = {
    {"pwg.13m", 0xae8fe08e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pwg.15m", 0xdb560f58, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pwg.17m", 0xbc475b94, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pwg.19m", 0x07439ff7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"pwg.14m", 0xc3f9ba63, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"pwg.16m", 0x815b0e7b, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"pwg.18m", 0x0109c71b, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"pwg.20m", 0xeb75ffbe, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_armwara_audiocpu[] = {
    {"pwg.01", 0x18a5c0e4, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pwg.01", 0x18a5c0e4, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pwg.02", 0xc9dfffa6, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_armwara_qsound[] = {
    {"pwg.11m", 0xa78f7433, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pwg.12m", 0x77438ed0, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_armwara_key[] = {
    {"armwara.key", 0x525439c0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_armwara[] = {
    {"maincpu", 4194304, 0, chips_armwara_maincpu, N(chips_armwara_maincpu)},
    {"gfx", 20971520, 0, chips_armwara_gfx, N(chips_armwara_gfx)},
    {"audiocpu", 327680, 0, chips_armwara_audiocpu, N(chips_armwara_audiocpu)},
    {"qsound", 4194304, 0, chips_armwara_qsound, N(chips_armwara_qsound)},
    {"key", 32, 0, chips_armwara_key, N(chips_armwara_key)},
};
static const Cps2Load chips_armwarar1_maincpu[] = {
    {"pwga.03a", 0x8d474ab1, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pwga.04a", 0x81b5aec7, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pwga.05a", 0x2618e819, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pwg.06", 0x87a60ce8, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"pwg.07", 0xf7b148df, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"pwg.08", 0xcc62823e, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"pwg.09", 0xddc85ca6, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"pwg.10", 0x07c4fb28, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_armwarar1_gfx[] = {
    {"pwg.13m", 0xae8fe08e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pwg.15m", 0xdb560f58, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pwg.17m", 0xbc475b94, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pwg.19m", 0x07439ff7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"pwg.14m", 0xc3f9ba63, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"pwg.16m", 0x815b0e7b, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"pwg.18m", 0x0109c71b, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"pwg.20m", 0xeb75ffbe, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_armwarar1_audiocpu[] = {
    {"pwg.01", 0x18a5c0e4, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pwg.01", 0x18a5c0e4, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pwg.02", 0xc9dfffa6, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_armwarar1_qsound[] = {
    {"pwg.11m", 0xa78f7433, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pwg.12m", 0x77438ed0, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_armwarar1_key[] = {
    {"armwara.key", 0x525439c0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_armwarar1[] = {
    {"maincpu", 4194304, 0, chips_armwarar1_maincpu, N(chips_armwarar1_maincpu)},
    {"gfx", 20971520, 0, chips_armwarar1_gfx, N(chips_armwarar1_gfx)},
    {"audiocpu", 327680, 0, chips_armwarar1_audiocpu, N(chips_armwarar1_audiocpu)},
    {"qsound", 4194304, 0, chips_armwarar1_qsound, N(chips_armwarar1_qsound)},
    {"key", 32, 0, chips_armwarar1_key, N(chips_armwarar1_key)},
};
static const Cps2Load chips_xmcota_maincpu[] = {
    {"xmne.03f", 0x5a726d13, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xmne.04f", 0x06a83f3a, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xmne.05b", 0x87b0ed0f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xmn.06a", 0x1b86a328, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xmn.07a", 0x2c142a44, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xmn.08a", 0xf712d44f, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xmn.09a", 0x9241cae8, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"xmne.10b", 0xcb36b0a4, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmcota_gfx[] = {
    {"xmn.13m", 0xbf4df073, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xmn.15m", 0x4d7e4cef, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xmn.17m", 0x513eea17, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xmn.19m", 0xd23897fc, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xmn.14m", 0x778237b7, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xmn.16m", 0x67b36948, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xmn.18m", 0x015a7c4c, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xmn.20m", 0x9dde2758, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmcota_audiocpu[] = {
    {"xmn.01a", 0x40f479ea, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xmn.01a", 0x40f479ea, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xmn.02a", 0x39d9b5ad, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmcota_qsound[] = {
    {"xmn.11m", 0xc848a6bc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xmn.12m", 0x729c188f, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmcota_key[] = {
    {"xmcota.key", 0x6665bbfb, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmcota[] = {
    {"maincpu", 4194304, 0, chips_xmcota_maincpu, N(chips_xmcota_maincpu)},
    {"gfx", 33554432, 0, chips_xmcota_gfx, N(chips_xmcota_gfx)},
    {"audiocpu", 327680, 0, chips_xmcota_audiocpu, N(chips_xmcota_audiocpu)},
    {"qsound", 4194304, 0, chips_xmcota_qsound, N(chips_xmcota_qsound)},
    {"key", 32, 0, chips_xmcota_key, N(chips_xmcota_key)},
};
static const Cps2Load chips_xmcotar1_maincpu[] = {
    {"xmne.03e", 0xa9a09b09, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xmne.04e", 0x52fa2106, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xmn.05a", 0xac0d7759, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xmn.06a", 0x1b86a328, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xmn.07a", 0x2c142a44, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xmn.08a", 0xf712d44f, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xmn.09a", 0x9241cae8, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"xmn.10a", 0x53c0eab9, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotar1_gfx[] = {
    {"xmn.13m", 0xbf4df073, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xmn.15m", 0x4d7e4cef, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xmn.17m", 0x513eea17, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xmn.19m", 0xd23897fc, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xmn.14m", 0x778237b7, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xmn.16m", 0x67b36948, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xmn.18m", 0x015a7c4c, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xmn.20m", 0x9dde2758, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmcotar1_audiocpu[] = {
    {"xmn.01a", 0x40f479ea, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xmn.01a", 0x40f479ea, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xmn.02a", 0x39d9b5ad, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmcotar1_qsound[] = {
    {"xmn.11m", 0xc848a6bc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xmn.12m", 0x729c188f, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotar1_key[] = {
    {"xmcota.key", 0x6665bbfb, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmcotar1[] = {
    {"maincpu", 4194304, 0, chips_xmcotar1_maincpu, N(chips_xmcotar1_maincpu)},
    {"gfx", 33554432, 0, chips_xmcotar1_gfx, N(chips_xmcotar1_gfx)},
    {"audiocpu", 327680, 0, chips_xmcotar1_audiocpu, N(chips_xmcotar1_audiocpu)},
    {"qsound", 4194304, 0, chips_xmcotar1_qsound, N(chips_xmcotar1_qsound)},
    {"key", 32, 0, chips_xmcotar1_key, N(chips_xmcotar1_key)},
};
static const Cps2Load chips_xmcotau_maincpu[] = {
    {"xmnu.03e", 0x0bafeb0e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xmnu.04e", 0xc29bdae3, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xmn.05a", 0xac0d7759, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xmn.06a", 0x1b86a328, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xmn.07a", 0x2c142a44, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xmn.08a", 0xf712d44f, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xmn.09a", 0x9241cae8, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"xmn.10a", 0x53c0eab9, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotau_gfx[] = {
    {"xmn.13m", 0xbf4df073, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xmn.15m", 0x4d7e4cef, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xmn.17m", 0x513eea17, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xmn.19m", 0xd23897fc, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xmn.14m", 0x778237b7, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xmn.16m", 0x67b36948, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xmn.18m", 0x015a7c4c, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xmn.20m", 0x9dde2758, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmcotau_audiocpu[] = {
    {"xmn.01a", 0x40f479ea, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xmn.01a", 0x40f479ea, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xmn.02a", 0x39d9b5ad, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmcotau_qsound[] = {
    {"xmn.11m", 0xc848a6bc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xmn.12m", 0x729c188f, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotau_key[] = {
    {"xmcotau.key", 0x623d3357, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmcotau[] = {
    {"maincpu", 4194304, 0, chips_xmcotau_maincpu, N(chips_xmcotau_maincpu)},
    {"gfx", 33554432, 0, chips_xmcotau_gfx, N(chips_xmcotau_gfx)},
    {"audiocpu", 327680, 0, chips_xmcotau_audiocpu, N(chips_xmcotau_audiocpu)},
    {"qsound", 4194304, 0, chips_xmcotau_qsound, N(chips_xmcotau_qsound)},
    {"key", 32, 0, chips_xmcotau_key, N(chips_xmcotau_key)},
};
static const Cps2Load chips_xmcotab_maincpu[] = {
    {"xmnb.03c", 0xab48bcb0, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xmnb.04c", 0x8d8fcbb1, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xmne.05b", 0x87b0ed0f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xmn.06a", 0x1b86a328, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xmn.07a", 0x2c142a44, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xmn.08a", 0xf712d44f, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xmn.09a", 0x9241cae8, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"xmne.10b", 0xcb36b0a4, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotab_gfx[] = {
    {"xmn.13m", 0xbf4df073, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xmn.15m", 0x4d7e4cef, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xmn.17m", 0x513eea17, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xmn.19m", 0xd23897fc, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xmn.14m", 0x778237b7, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xmn.16m", 0x67b36948, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xmn.18m", 0x015a7c4c, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xmn.20m", 0x9dde2758, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmcotab_audiocpu[] = {
    {"xmn.01a", 0x40f479ea, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xmn.01a", 0x40f479ea, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xmn.02a", 0x39d9b5ad, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmcotab_qsound[] = {
    {"xmn.11m", 0xc848a6bc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xmn.12m", 0x729c188f, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotab_key[] = {
    {"xmcotab.key", 0xbb70f10f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmcotab[] = {
    {"maincpu", 4194304, 0, chips_xmcotab_maincpu, N(chips_xmcotab_maincpu)},
    {"gfx", 33554432, 0, chips_xmcotab_gfx, N(chips_xmcotab_gfx)},
    {"audiocpu", 327680, 0, chips_xmcotab_audiocpu, N(chips_xmcotab_audiocpu)},
    {"qsound", 4194304, 0, chips_xmcotab_qsound, N(chips_xmcotab_qsound)},
    {"key", 32, 0, chips_xmcotab_key, N(chips_xmcotab_key)},
};
static const Cps2Load chips_xmcotah_maincpu[] = {
    {"xmnh.03f", 0xe4b85a90, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xmnh.04f", 0x7dfe1406, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xmnh.05b", 0x87b0ed0f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xmn.06a", 0x1b86a328, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xmn.07a", 0x2c142a44, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xmn.08a", 0xf712d44f, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xmn.09a", 0x9241cae8, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"xmnh.10b", 0xcb36b0a4, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotah_gfx[] = {
    {"xmn.13m", 0xbf4df073, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xmn.15m", 0x4d7e4cef, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xmn.17m", 0x513eea17, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xmn.19m", 0xd23897fc, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xmn.14m", 0x778237b7, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xmn.16m", 0x67b36948, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xmn.18m", 0x015a7c4c, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xmn.20m", 0x9dde2758, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmcotah_audiocpu[] = {
    {"xmn.01a", 0x40f479ea, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xmn.01a", 0x40f479ea, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xmn.02a", 0x39d9b5ad, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmcotah_qsound[] = {
    {"xmn.11m", 0xc848a6bc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xmn.12m", 0x729c188f, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotah_key[] = {
    {"xmcotah.key", 0xc9a45a5a, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmcotah[] = {
    {"maincpu", 4194304, 0, chips_xmcotah_maincpu, N(chips_xmcotah_maincpu)},
    {"gfx", 33554432, 0, chips_xmcotah_gfx, N(chips_xmcotah_gfx)},
    {"audiocpu", 327680, 0, chips_xmcotah_audiocpu, N(chips_xmcotah_audiocpu)},
    {"qsound", 4194304, 0, chips_xmcotah_qsound, N(chips_xmcotah_qsound)},
    {"key", 32, 0, chips_xmcotah_key, N(chips_xmcotah_key)},
};
static const Cps2Load chips_xmcotahr1_maincpu[] = {
    {"xmnh.03d", 0x63b0a84f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xmnh.04d", 0xb1b9b727, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xmn.05a", 0xac0d7759, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xmn.06a", 0x1b86a328, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xmn.07a", 0x2c142a44, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xmn.08a", 0xf712d44f, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xmn.09a", 0x9241cae8, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"xmn.10a", 0x53c0eab9, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotahr1_gfx[] = {
    {"xmn.13m", 0xbf4df073, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xmn.15m", 0x4d7e4cef, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xmn.17m", 0x513eea17, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xmn.19m", 0xd23897fc, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xmn.14m", 0x778237b7, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xmn.16m", 0x67b36948, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xmn.18m", 0x015a7c4c, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xmn.20m", 0x9dde2758, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmcotahr1_audiocpu[] = {
    {"xmn.01a", 0x40f479ea, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xmn.01a", 0x40f479ea, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xmn.02a", 0x39d9b5ad, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmcotahr1_qsound[] = {
    {"xmn.11m", 0xc848a6bc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xmn.12m", 0x729c188f, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotahr1_key[] = {
    {"xmcotah.key", 0xc9a45a5a, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmcotahr1[] = {
    {"maincpu", 4194304, 0, chips_xmcotahr1_maincpu, N(chips_xmcotahr1_maincpu)},
    {"gfx", 33554432, 0, chips_xmcotahr1_gfx, N(chips_xmcotahr1_gfx)},
    {"audiocpu", 327680, 0, chips_xmcotahr1_audiocpu, N(chips_xmcotahr1_audiocpu)},
    {"qsound", 4194304, 0, chips_xmcotahr1_qsound, N(chips_xmcotahr1_qsound)},
    {"key", 32, 0, chips_xmcotahr1_key, N(chips_xmcotahr1_key)},
};
static const Cps2Load chips_xmcotaj_maincpu[] = {
    {"xmnj.03e", 0x0df29f5f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xmnj.04e", 0x4a65833b, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xmn.05a", 0xac0d7759, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xmn.06a", 0x1b86a328, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xmn.07a", 0x2c142a44, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xmn.08a", 0xf712d44f, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xmn.09a", 0x9241cae8, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"xmn.10a", 0x53c0eab9, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotaj_gfx[] = {
    {"xmn.13m", 0xbf4df073, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xmn.15m", 0x4d7e4cef, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xmn.17m", 0x513eea17, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xmn.19m", 0xd23897fc, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xmn.14m", 0x778237b7, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xmn.16m", 0x67b36948, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xmn.18m", 0x015a7c4c, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xmn.20m", 0x9dde2758, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmcotaj_audiocpu[] = {
    {"xmn.01a", 0x40f479ea, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xmn.01a", 0x40f479ea, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xmn.02a", 0x39d9b5ad, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmcotaj_qsound[] = {
    {"xmn.11m", 0xc848a6bc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xmn.12m", 0x729c188f, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotaj_key[] = {
    {"xmcotaj.key", 0xd278b4ac, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmcotaj[] = {
    {"maincpu", 4194304, 0, chips_xmcotaj_maincpu, N(chips_xmcotaj_maincpu)},
    {"gfx", 33554432, 0, chips_xmcotaj_gfx, N(chips_xmcotaj_gfx)},
    {"audiocpu", 327680, 0, chips_xmcotaj_audiocpu, N(chips_xmcotaj_audiocpu)},
    {"qsound", 4194304, 0, chips_xmcotaj_qsound, N(chips_xmcotaj_qsound)},
    {"key", 32, 0, chips_xmcotaj_key, N(chips_xmcotaj_key)},
};
static const Cps2Load chips_xmcotaj1_maincpu[] = {
    {"xmnj.03d", 0x79086d62, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xmnj.04d", 0x38eed613, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xmn.05", 0xc3ed62a2, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xmn.06", 0xf03c52e1, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xmn.07", 0x325626b1, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xmn.08", 0x7194ea10, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xmn.09", 0xae946df3, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"xmn.10", 0x32a6be1d, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotaj1_gfx[] = {
    {"xmn.13m", 0xbf4df073, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xmn.15m", 0x4d7e4cef, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xmn.17m", 0x513eea17, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xmn.19m", 0xd23897fc, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xmn.14m", 0x778237b7, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xmn.16m", 0x67b36948, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xmn.18m", 0x015a7c4c, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xmn.20m", 0x9dde2758, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmcotaj1_audiocpu[] = {
    {"xmn.01a", 0x40f479ea, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xmn.01a", 0x40f479ea, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xmn.02a", 0x39d9b5ad, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmcotaj1_qsound[] = {
    {"xmn.11m", 0xc848a6bc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xmn.12m", 0x729c188f, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotaj1_key[] = {
    {"xmcotaj.key", 0xd278b4ac, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmcotaj1[] = {
    {"maincpu", 4194304, 0, chips_xmcotaj1_maincpu, N(chips_xmcotaj1_maincpu)},
    {"gfx", 33554432, 0, chips_xmcotaj1_gfx, N(chips_xmcotaj1_gfx)},
    {"audiocpu", 327680, 0, chips_xmcotaj1_audiocpu, N(chips_xmcotaj1_audiocpu)},
    {"qsound", 4194304, 0, chips_xmcotaj1_qsound, N(chips_xmcotaj1_qsound)},
    {"key", 32, 0, chips_xmcotaj1_key, N(chips_xmcotaj1_key)},
};
static const Cps2Load chips_xmcotaj2_maincpu[] = {
    {"xmnj.03b", 0xc8175fb3, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xmnj.04b", 0x54b3fba3, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xmn.05", 0xc3ed62a2, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xmn.06", 0xf03c52e1, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xmn.07", 0x325626b1, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xmn.08", 0x7194ea10, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xmn.09", 0xae946df3, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"xmn.10", 0x32a6be1d, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotaj2_gfx[] = {
    {"xmn.13m", 0xbf4df073, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xmn.15m", 0x4d7e4cef, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xmn.17m", 0x513eea17, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xmn.19m", 0xd23897fc, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xmn.14m", 0x778237b7, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xmn.16m", 0x67b36948, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xmn.18m", 0x015a7c4c, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xmn.20m", 0x9dde2758, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmcotaj2_audiocpu[] = {
    {"xmn.01a", 0x40f479ea, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xmn.01a", 0x40f479ea, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xmn.02a", 0x39d9b5ad, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmcotaj2_qsound[] = {
    {"xmn.11m", 0xc848a6bc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xmn.12m", 0x729c188f, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotaj2_key[] = {
    {"xmcotaj.key", 0xd278b4ac, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmcotaj2[] = {
    {"maincpu", 4194304, 0, chips_xmcotaj2_maincpu, N(chips_xmcotaj2_maincpu)},
    {"gfx", 33554432, 0, chips_xmcotaj2_gfx, N(chips_xmcotaj2_gfx)},
    {"audiocpu", 327680, 0, chips_xmcotaj2_audiocpu, N(chips_xmcotaj2_audiocpu)},
    {"qsound", 4194304, 0, chips_xmcotaj2_qsound, N(chips_xmcotaj2_qsound)},
    {"key", 32, 0, chips_xmcotaj2_key, N(chips_xmcotaj2_key)},
};
static const Cps2Load chips_xmcotaj3_maincpu[] = {
    {"xmnj.03a", 0x00761611, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xmnj.04a", 0x614d3f60, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xmn.05", 0xc3ed62a2, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xmn.06", 0xf03c52e1, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xmn.07", 0x325626b1, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xmn.08", 0x7194ea10, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xmn.09", 0xae946df3, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"xmn.10", 0x32a6be1d, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotaj3_gfx[] = {
    {"xmn.13m", 0xbf4df073, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xmn.15m", 0x4d7e4cef, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xmn.17m", 0x513eea17, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xmn.19m", 0xd23897fc, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xmn.14m", 0x778237b7, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xmn.16m", 0x67b36948, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xmn.18m", 0x015a7c4c, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xmn.20m", 0x9dde2758, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmcotaj3_audiocpu[] = {
    {"xmn.01a", 0x40f479ea, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xmn.01a", 0x40f479ea, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xmn.02a", 0x39d9b5ad, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmcotaj3_qsound[] = {
    {"xmn.11m", 0xc848a6bc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xmn.12m", 0x729c188f, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotaj3_key[] = {
    {"xmcotaj.key", 0xd278b4ac, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmcotaj3[] = {
    {"maincpu", 4194304, 0, chips_xmcotaj3_maincpu, N(chips_xmcotaj3_maincpu)},
    {"gfx", 33554432, 0, chips_xmcotaj3_gfx, N(chips_xmcotaj3_gfx)},
    {"audiocpu", 327680, 0, chips_xmcotaj3_audiocpu, N(chips_xmcotaj3_audiocpu)},
    {"qsound", 4194304, 0, chips_xmcotaj3_qsound, N(chips_xmcotaj3_qsound)},
    {"key", 32, 0, chips_xmcotaj3_key, N(chips_xmcotaj3_key)},
};
static const Cps2Load chips_xmcotajr_maincpu[] = {
    {"xmno.03a", 0x7ab19acf, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xmno.04a", 0x7615dd21, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xmno.05a", 0x0303d672, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xmno.06a", 0x332839a5, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xmno.07", 0x6255e8d5, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xmno.08", 0xb8ebe77c, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xmno.09", 0x5440d950, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"xmno.10a", 0xb8296966, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotajr_gfx[] = {
    {"xmn.13m", 0xbf4df073, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xmn.15m", 0x4d7e4cef, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xmn.17m", 0x513eea17, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xmn.19m", 0xd23897fc, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xmn.14m", 0x778237b7, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xmn.16m", 0x67b36948, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xmn.18m", 0x015a7c4c, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xmn.20m", 0x9dde2758, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmcotajr_audiocpu[] = {
    {"xmn.01", 0x7178336e, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xmn.01", 0x7178336e, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xmn.02", 0x0ec58501, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmcotajr_qsound[] = {
    {"xmn.11m", 0xc848a6bc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xmn.12m", 0x729c188f, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotajr_key[] = {
    {"xmcotaj.key", 0xd278b4ac, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmcotajr[] = {
    {"maincpu", 4194304, 0, chips_xmcotajr_maincpu, N(chips_xmcotajr_maincpu)},
    {"gfx", 33554432, 0, chips_xmcotajr_gfx, N(chips_xmcotajr_gfx)},
    {"audiocpu", 327680, 0, chips_xmcotajr_audiocpu, N(chips_xmcotajr_audiocpu)},
    {"qsound", 4194304, 0, chips_xmcotajr_qsound, N(chips_xmcotajr_qsound)},
    {"key", 32, 0, chips_xmcotajr_key, N(chips_xmcotajr_key)},
};
static const Cps2Load chips_xmcotaa_maincpu[] = {
    {"xmna.03e", 0xf1ade6e7, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xmna.04e", 0xb5a8843d, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xmn.05a", 0xac0d7759, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xmn.06a", 0x1b86a328, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xmn.07a", 0x2c142a44, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xmn.08a", 0xf712d44f, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xmn.09a", 0x9241cae8, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"xmn.10a", 0x53c0eab9, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotaa_gfx[] = {
    {"xmn.13m", 0xbf4df073, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xmn.15m", 0x4d7e4cef, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xmn.17m", 0x513eea17, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xmn.19m", 0xd23897fc, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xmn.14m", 0x778237b7, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xmn.16m", 0x67b36948, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xmn.18m", 0x015a7c4c, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xmn.20m", 0x9dde2758, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmcotaa_audiocpu[] = {
    {"xmn.01a", 0x40f479ea, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xmn.01a", 0x40f479ea, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xmn.02a", 0x39d9b5ad, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmcotaa_qsound[] = {
    {"xmn.11m", 0xc848a6bc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xmn.12m", 0x729c188f, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotaa_key[] = {
    {"xmcotaa.key", 0x3fdd2d42, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmcotaa[] = {
    {"maincpu", 4194304, 0, chips_xmcotaa_maincpu, N(chips_xmcotaa_maincpu)},
    {"gfx", 33554432, 0, chips_xmcotaa_gfx, N(chips_xmcotaa_gfx)},
    {"audiocpu", 327680, 0, chips_xmcotaa_audiocpu, N(chips_xmcotaa_audiocpu)},
    {"qsound", 4194304, 0, chips_xmcotaa_qsound, N(chips_xmcotaa_qsound)},
    {"key", 32, 0, chips_xmcotaa_key, N(chips_xmcotaa_key)},
};
static const Cps2Load chips_xmcotaar1_maincpu[] = {
    {"xmna.03b", 0x2280d03f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xmna.04b", 0xebbbf11e, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xmn.05", 0xc3ed62a2, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xmn.06", 0xf03c52e1, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xmn.07", 0x325626b1, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xmn.08", 0x7194ea10, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xmn.09", 0xae946df3, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"xmn.10", 0x32a6be1d, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotaar1_gfx[] = {
    {"xmn.13m", 0xbf4df073, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xmn.15m", 0x4d7e4cef, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xmn.17m", 0x513eea17, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xmn.19m", 0xd23897fc, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xmn.14m", 0x778237b7, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xmn.16m", 0x67b36948, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xmn.18m", 0x015a7c4c, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xmn.20m", 0x9dde2758, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmcotaar1_audiocpu[] = {
    {"xmn.01a", 0x40f479ea, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xmn.01a", 0x40f479ea, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xmn.02a", 0x39d9b5ad, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmcotaar1_qsound[] = {
    {"xmn.11m", 0xc848a6bc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xmn.12m", 0x729c188f, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotaar1_key[] = {
    {"xmcotaa.key", 0x3fdd2d42, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmcotaar1[] = {
    {"maincpu", 4194304, 0, chips_xmcotaar1_maincpu, N(chips_xmcotaar1_maincpu)},
    {"gfx", 33554432, 0, chips_xmcotaar1_gfx, N(chips_xmcotaar1_gfx)},
    {"audiocpu", 327680, 0, chips_xmcotaar1_audiocpu, N(chips_xmcotaar1_audiocpu)},
    {"qsound", 4194304, 0, chips_xmcotaar1_qsound, N(chips_xmcotaar1_qsound)},
    {"key", 32, 0, chips_xmcotaar1_key, N(chips_xmcotaar1_key)},
};
static const Cps2Load chips_xmcotaar2_maincpu[] = {
    {"xmna.03a", 0x7df8b27e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xmna.04a", 0xb44e30a7, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xmn.05", 0xc3ed62a2, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xmn.06", 0xf03c52e1, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xmn.07", 0x325626b1, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xmn.08", 0x7194ea10, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xmn.09", 0xae946df3, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"xmn.10", 0x32a6be1d, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotaar2_gfx[] = {
    {"xmn.13m", 0xbf4df073, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xmn.15m", 0x4d7e4cef, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xmn.17m", 0x513eea17, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xmn.19m", 0xd23897fc, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xmn.14m", 0x778237b7, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xmn.16m", 0x67b36948, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xmn.18m", 0x015a7c4c, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xmn.20m", 0x9dde2758, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmcotaar2_audiocpu[] = {
    {"xmn.01a", 0x40f479ea, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xmn.01a", 0x40f479ea, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xmn.02a", 0x39d9b5ad, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmcotaar2_qsound[] = {
    {"xmn.11m", 0xc848a6bc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xmn.12m", 0x729c188f, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotaar2_key[] = {
    {"xmcotaa.key", 0x3fdd2d42, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmcotaar2[] = {
    {"maincpu", 4194304, 0, chips_xmcotaar2_maincpu, N(chips_xmcotaar2_maincpu)},
    {"gfx", 33554432, 0, chips_xmcotaar2_gfx, N(chips_xmcotaar2_gfx)},
    {"audiocpu", 327680, 0, chips_xmcotaar2_audiocpu, N(chips_xmcotaar2_audiocpu)},
    {"qsound", 4194304, 0, chips_xmcotaar2_qsound, N(chips_xmcotaar2_qsound)},
    {"key", 32, 0, chips_xmcotaar2_key, N(chips_xmcotaar2_key)},
};
static const Cps2Load chips_nwarr_maincpu[] = {
    {"vphe.03f", 0xa922c44f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vphe.04c", 0x7312d890, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vphe.05d", 0xcde8b506, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vphe.06c", 0xbe99e7d0, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vphe.07b", 0x69e0e60c, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vphe.08b", 0xd95a3849, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vphe.09b", 0x9882561c, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vphe.10b", 0x976fa62f, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_nwarr_gfx[] = {
    {"vph.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vph.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vph.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vph.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vph.14m", 0x7a0e1add, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vph.16m", 0x2f41ca75, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vph.18m", 0x64498eed, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vph.20m", 0x17f2433f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_nwarr_audiocpu[] = {
    {"vph.01", 0x5045dcac, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vph.01", 0x5045dcac, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vph.02", 0x86b60e59, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_nwarr_qsound[] = {
    {"vph.11m", 0xe1837d33, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vph.12m", 0xfbd3cd90, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_nwarr_key[] = {
    {"nwarr.key", 0x618a13ca, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_nwarr[] = {
    {"maincpu", 4194304, 0, chips_nwarr_maincpu, N(chips_nwarr_maincpu)},
    {"gfx", 33554432, 0, chips_nwarr_gfx, N(chips_nwarr_gfx)},
    {"audiocpu", 327680, 0, chips_nwarr_audiocpu, N(chips_nwarr_audiocpu)},
    {"qsound", 4194304, 0, chips_nwarr_qsound, N(chips_nwarr_qsound)},
    {"key", 32, 0, chips_nwarr_key, N(chips_nwarr_key)},
};
static const Cps2Load chips_nwarru_maincpu[] = {
    {"vphu.03f", 0x85d6a359, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vphu.04c", 0xcb7fce77, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vphu.05e", 0xe08f2bba, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vphu.06c", 0x08c04cdb, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vphu.07b", 0xb5a5ab19, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vphu.08b", 0x51bb20fb, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vphu.09b", 0x41a64205, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vphu.10b", 0x2b1d43ae, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_nwarru_gfx[] = {
    {"vph.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vph.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vph.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vph.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vph.14m", 0x7a0e1add, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vph.16m", 0x2f41ca75, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vph.18m", 0x64498eed, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vph.20m", 0x17f2433f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_nwarru_audiocpu[] = {
    {"vph.01", 0x5045dcac, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vph.01", 0x5045dcac, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vph.02", 0x86b60e59, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_nwarru_qsound[] = {
    {"vph.11m", 0xe1837d33, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vph.12m", 0xfbd3cd90, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_nwarru_key[] = {
    {"nwarru.key", 0x1c593f9b, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_nwarru[] = {
    {"maincpu", 4194304, 0, chips_nwarru_maincpu, N(chips_nwarru_maincpu)},
    {"gfx", 33554432, 0, chips_nwarru_gfx, N(chips_nwarru_gfx)},
    {"audiocpu", 327680, 0, chips_nwarru_audiocpu, N(chips_nwarru_audiocpu)},
    {"qsound", 4194304, 0, chips_nwarru_qsound, N(chips_nwarru_qsound)},
    {"key", 32, 0, chips_nwarru_key, N(chips_nwarru_key)},
};
static const Cps2Load chips_nwarrh_maincpu[] = {
    {"vphh.03d", 0x6029c7be, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vphh.04a", 0xd26625ee, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vphh.05c", 0x73ee0b8a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vphh.06a", 0xa5b3a50a, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vphh.07", 0x5fc2bdc1, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vphh.08", 0xe65588d9, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vphh.09", 0xa2ce6d63, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vphh.10", 0xe2f4f4b9, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_nwarrh_gfx[] = {
    {"vph.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vph.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vph.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vph.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vph.14m", 0x7a0e1add, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vph.16m", 0x2f41ca75, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vph.18m", 0x64498eed, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vph.20m", 0x17f2433f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_nwarrh_audiocpu[] = {
    {"vph.01", 0x5045dcac, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vph.01", 0x5045dcac, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vph.02", 0x86b60e59, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_nwarrh_qsound[] = {
    {"vph.11m", 0xe1837d33, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vph.12m", 0xfbd3cd90, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_nwarrh_key[] = {
    {"nwarrh.key", 0x5fb16b23, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_nwarrh[] = {
    {"maincpu", 4194304, 0, chips_nwarrh_maincpu, N(chips_nwarrh_maincpu)},
    {"gfx", 33554432, 0, chips_nwarrh_gfx, N(chips_nwarrh_gfx)},
    {"audiocpu", 327680, 0, chips_nwarrh_audiocpu, N(chips_nwarrh_audiocpu)},
    {"qsound", 4194304, 0, chips_nwarrh_qsound, N(chips_nwarrh_qsound)},
    {"key", 32, 0, chips_nwarrh_key, N(chips_nwarrh_key)},
};
static const Cps2Load chips_nwarrb_maincpu[] = {
    {"vphb.03d", 0x3a426d3f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vphb.04a", 0x51c4bb2f, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vphb.05c", 0xac44d997, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vphb.06a", 0x5072a5fe, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vphb.07", 0x9b355192, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vphb.08", 0x42220f84, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vphb.09", 0x029e015d, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vphb.10", 0x37b3ce37, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_nwarrb_gfx[] = {
    {"vph.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vph.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vph.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vph.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vph.14m", 0x7a0e1add, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vph.16m", 0x2f41ca75, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vph.18m", 0x64498eed, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vph.20m", 0x17f2433f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_nwarrb_audiocpu[] = {
    {"vph.01", 0x5045dcac, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vph.01", 0x5045dcac, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vph.02", 0x86b60e59, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_nwarrb_qsound[] = {
    {"vph.11m", 0xe1837d33, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vph.12m", 0xfbd3cd90, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_nwarrb_key[] = {
    {"nwarrb.key", 0x4ffc0a54, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_nwarrb[] = {
    {"maincpu", 4194304, 0, chips_nwarrb_maincpu, N(chips_nwarrb_maincpu)},
    {"gfx", 33554432, 0, chips_nwarrb_gfx, N(chips_nwarrb_gfx)},
    {"audiocpu", 327680, 0, chips_nwarrb_audiocpu, N(chips_nwarrb_audiocpu)},
    {"qsound", 4194304, 0, chips_nwarrb_qsound, N(chips_nwarrb_qsound)},
    {"key", 32, 0, chips_nwarrb_key, N(chips_nwarrb_key)},
};
static const Cps2Load chips_nwarra_maincpu[] = {
    {"vpha.03b", 0x0a70cdd6, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vpha.04b", 0x70ce62e4, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vpha.05b", 0x5692a03f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vpha.06b", 0xb810fe66, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vpha.07b", 0x1be264f3, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vpha.08b", 0x86f1ed52, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vpha.09b", 0x7e96bd0a, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vpha.10b", 0x58bce2fd, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_nwarra_gfx[] = {
    {"vph.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vph.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vph.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vph.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vph.14m", 0x7a0e1add, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vph.16m", 0x2f41ca75, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vph.18m", 0x64498eed, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vph.20m", 0x17f2433f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_nwarra_audiocpu[] = {
    {"vph.01", 0x5045dcac, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vph.01", 0x5045dcac, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vph.02", 0x86b60e59, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_nwarra_qsound[] = {
    {"vph.11m", 0xe1837d33, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vph.12m", 0xfbd3cd90, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_nwarra_key[] = {
    {"nwarra.key", 0x9bafff67, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_nwarra[] = {
    {"maincpu", 4194304, 0, chips_nwarra_maincpu, N(chips_nwarra_maincpu)},
    {"gfx", 33554432, 0, chips_nwarra_gfx, N(chips_nwarra_gfx)},
    {"audiocpu", 327680, 0, chips_nwarra_audiocpu, N(chips_nwarra_audiocpu)},
    {"qsound", 4194304, 0, chips_nwarra_qsound, N(chips_nwarra_qsound)},
    {"key", 32, 0, chips_nwarra_key, N(chips_nwarra_key)},
};
static const Cps2Load chips_vhuntj_maincpu[] = {
    {"vphj.03f", 0x3de2e333, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vphj.04c", 0xc95cf304, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vphj.05d", 0x50de5ddd, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vphj.06c", 0xac3bd3d5, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vphj.07b", 0x0761309f, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vphj.08b", 0x5a5c2bf5, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vphj.09b", 0x823d6d99, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vphj.10b", 0x32c7d8f0, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vhuntj_gfx[] = {
    {"vph.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vph.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vph.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vph.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vph.14m", 0x7a0e1add, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vph.16m", 0x2f41ca75, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vph.18m", 0x64498eed, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vph.20m", 0x17f2433f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vhuntj_audiocpu[] = {
    {"vph.01", 0x5045dcac, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vph.01", 0x5045dcac, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vph.02", 0x86b60e59, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vhuntj_qsound[] = {
    {"vph.11m", 0xe1837d33, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vph.12m", 0xfbd3cd90, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_vhuntj_key[] = {
    {"vhuntj.key", 0x72854f68, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vhuntj[] = {
    {"maincpu", 4194304, 0, chips_vhuntj_maincpu, N(chips_vhuntj_maincpu)},
    {"gfx", 33554432, 0, chips_vhuntj_gfx, N(chips_vhuntj_gfx)},
    {"audiocpu", 327680, 0, chips_vhuntj_audiocpu, N(chips_vhuntj_audiocpu)},
    {"qsound", 4194304, 0, chips_vhuntj_qsound, N(chips_vhuntj_qsound)},
    {"key", 32, 0, chips_vhuntj_key, N(chips_vhuntj_key)},
};
static const Cps2Load chips_vhuntjr1s_maincpu[] = {
    {"vphjstop.03b", 0x9c4e6191, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vphj.04c", 0xc95cf304, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vphj.05d", 0x50de5ddd, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vphj.06c", 0xac3bd3d5, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vphj.07b", 0x0761309f, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vphj.08b", 0x5a5c2bf5, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vphj.09b", 0x823d6d99, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vphj.10b", 0x32c7d8f0, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vhuntjr1s_gfx[] = {
    {"vph.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vph.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vph.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vph.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vph.14m", 0x7a0e1add, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vph.16m", 0x2f41ca75, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vph.18m", 0x64498eed, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vph.20m", 0x17f2433f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vhuntjr1s_audiocpu[] = {
    {"vph.01", 0x5045dcac, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vph.01", 0x5045dcac, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vph.02", 0x86b60e59, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vhuntjr1s_qsound[] = {
    {"vph.11m", 0xe1837d33, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vph.12m", 0xfbd3cd90, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_vhuntjr1s_key[] = {
    {"vhuntj.key", 0x72854f68, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vhuntjr1s[] = {
    {"maincpu", 4194304, 0, chips_vhuntjr1s_maincpu, N(chips_vhuntjr1s_maincpu)},
    {"gfx", 33554432, 0, chips_vhuntjr1s_gfx, N(chips_vhuntjr1s_gfx)},
    {"audiocpu", 327680, 0, chips_vhuntjr1s_audiocpu, N(chips_vhuntjr1s_audiocpu)},
    {"qsound", 4194304, 0, chips_vhuntjr1s_qsound, N(chips_vhuntjr1s_qsound)},
    {"key", 32, 0, chips_vhuntjr1s_key, N(chips_vhuntjr1s_key)},
};
static const Cps2Load chips_vhuntjr1_maincpu[] = {
    {"vphj.03c", 0x606b682a, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vphj.04b", 0xa3b40393, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vphj.05b", 0xfccd5558, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vphj.06b", 0x07e10a73, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vphj.07b", 0x0761309f, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vphj.08b", 0x5a5c2bf5, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vphj.09b", 0x823d6d99, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vphj.10b", 0x32c7d8f0, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vhuntjr1_gfx[] = {
    {"vph.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vph.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vph.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vph.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vph.14m", 0x7a0e1add, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vph.16m", 0x2f41ca75, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vph.18m", 0x64498eed, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vph.20m", 0x17f2433f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vhuntjr1_audiocpu[] = {
    {"vph.01", 0x5045dcac, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vph.01", 0x5045dcac, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vph.02", 0x86b60e59, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vhuntjr1_qsound[] = {
    {"vph.11m", 0xe1837d33, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vph.12m", 0xfbd3cd90, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_vhuntjr1_key[] = {
    {"vhuntj.key", 0x72854f68, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vhuntjr1[] = {
    {"maincpu", 4194304, 0, chips_vhuntjr1_maincpu, N(chips_vhuntjr1_maincpu)},
    {"gfx", 33554432, 0, chips_vhuntjr1_gfx, N(chips_vhuntjr1_gfx)},
    {"audiocpu", 327680, 0, chips_vhuntjr1_audiocpu, N(chips_vhuntjr1_audiocpu)},
    {"qsound", 4194304, 0, chips_vhuntjr1_qsound, N(chips_vhuntjr1_qsound)},
    {"key", 32, 0, chips_vhuntjr1_key, N(chips_vhuntjr1_key)},
};
static const Cps2Load chips_vhuntjr2_maincpu[] = {
    {"vphj.03b", 0x679c3fa9, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vphj.04a", 0xeb6e71e4, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vphj.05a", 0xeaf634ea, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vphj.06a", 0xb70cc6be, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vphj.07a", 0x46ab907d, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vphj.08a", 0x1c00355e, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vphj.09a", 0x026e6f82, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vphj.10a", 0xaadfb3ea, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vhuntjr2_gfx[] = {
    {"vph.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vph.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vph.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vph.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vph.14m", 0x7a0e1add, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vph.16m", 0x2f41ca75, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vph.18m", 0x64498eed, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vph.20m", 0x17f2433f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vhuntjr2_audiocpu[] = {
    {"vph.01", 0x5045dcac, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vph.01", 0x5045dcac, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vph.02", 0x86b60e59, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vhuntjr2_qsound[] = {
    {"vph.11m", 0xe1837d33, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vph.12m", 0xfbd3cd90, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_vhuntjr2_key[] = {
    {"vhuntj.key", 0x72854f68, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vhuntjr2[] = {
    {"maincpu", 4194304, 0, chips_vhuntjr2_maincpu, N(chips_vhuntjr2_maincpu)},
    {"gfx", 33554432, 0, chips_vhuntjr2_gfx, N(chips_vhuntjr2_gfx)},
    {"audiocpu", 327680, 0, chips_vhuntjr2_audiocpu, N(chips_vhuntjr2_audiocpu)},
    {"qsound", 4194304, 0, chips_vhuntjr2_qsound, N(chips_vhuntjr2_qsound)},
    {"key", 32, 0, chips_vhuntjr2_key, N(chips_vhuntjr2_key)},
};
static const Cps2Load chips_cybots_maincpu[] = {
    {"cybe.03", 0x234381cd, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"cybe.04", 0x80691061, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"cyb.05", 0xec40408e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"cyb.06", 0x1ad0bed2, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"cyb.07", 0x6245a39a, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"cyb.08", 0x4b48e223, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"cyb.09", 0xe15238f6, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"cyb.10", 0x75f4003b, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_cybots_gfx[] = {
    {"cyb.13m", 0xf0dce192, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"cyb.15m", 0x187aa39c, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"cyb.17m", 0x8a0e4b12, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"cyb.19m", 0x34b62612, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"cyb.14m", 0xc1537957, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"cyb.16m", 0x15349e86, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"cyb.18m", 0xd83e977d, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"cyb.20m", 0x77cdad5c, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_cybots_audiocpu[] = {
    {"cyb.01", 0x9c0fb079, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"cyb.01", 0x9c0fb079, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"cyb.02", 0x51cb0c4e, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_cybots_qsound[] = {
    {"cyb.11m", 0x362ccab2, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"cyb.12m", 0x7066e9cc, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_cybots_key[] = {
    {"cybots.key", 0x9bbcbef3, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_cybots[] = {
    {"maincpu", 4194304, 0, chips_cybots_maincpu, N(chips_cybots_maincpu)},
    {"gfx", 33554432, 0, chips_cybots_gfx, N(chips_cybots_gfx)},
    {"audiocpu", 327680, 0, chips_cybots_audiocpu, N(chips_cybots_audiocpu)},
    {"qsound", 4194304, 0, chips_cybots_qsound, N(chips_cybots_qsound)},
    {"key", 32, 0, chips_cybots_key, N(chips_cybots_key)},
};
static const Cps2Load chips_cybotsu_maincpu[] = {
    {"cybu.03", 0xdb4da8f4, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"cybu.04", 0x1eec68ac, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"cyb.05", 0xec40408e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"cyb.06", 0x1ad0bed2, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"cyb.07", 0x6245a39a, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"cyb.08", 0x4b48e223, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"cyb.09", 0xe15238f6, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"cyb.10", 0x75f4003b, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_cybotsu_gfx[] = {
    {"cyb.13m", 0xf0dce192, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"cyb.15m", 0x187aa39c, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"cyb.17m", 0x8a0e4b12, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"cyb.19m", 0x34b62612, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"cyb.14m", 0xc1537957, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"cyb.16m", 0x15349e86, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"cyb.18m", 0xd83e977d, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"cyb.20m", 0x77cdad5c, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_cybotsu_audiocpu[] = {
    {"cyb.01", 0x9c0fb079, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"cyb.01", 0x9c0fb079, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"cyb.02", 0x51cb0c4e, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_cybotsu_qsound[] = {
    {"cyb.11m", 0x362ccab2, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"cyb.12m", 0x7066e9cc, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_cybotsu_key[] = {
    {"cybotsu.key", 0x7a09403c, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_cybotsu[] = {
    {"maincpu", 4194304, 0, chips_cybotsu_maincpu, N(chips_cybotsu_maincpu)},
    {"gfx", 33554432, 0, chips_cybotsu_gfx, N(chips_cybotsu_gfx)},
    {"audiocpu", 327680, 0, chips_cybotsu_audiocpu, N(chips_cybotsu_audiocpu)},
    {"qsound", 4194304, 0, chips_cybotsu_qsound, N(chips_cybotsu_qsound)},
    {"key", 32, 0, chips_cybotsu_key, N(chips_cybotsu_key)},
};
static const Cps2Load chips_cybotsj_maincpu[] = {
    {"cybj.03", 0x6096eada, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"cybj.04", 0x7b0ffaa9, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"cyb.05", 0xec40408e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"cyb.06", 0x1ad0bed2, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"cyb.07", 0x6245a39a, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"cyb.08", 0x4b48e223, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"cyb.09", 0xe15238f6, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"cyb.10", 0x75f4003b, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_cybotsj_gfx[] = {
    {"cyb.13m", 0xf0dce192, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"cyb.15m", 0x187aa39c, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"cyb.17m", 0x8a0e4b12, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"cyb.19m", 0x34b62612, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"cyb.14m", 0xc1537957, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"cyb.16m", 0x15349e86, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"cyb.18m", 0xd83e977d, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"cyb.20m", 0x77cdad5c, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_cybotsj_audiocpu[] = {
    {"cyb.01", 0x9c0fb079, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"cyb.01", 0x9c0fb079, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"cyb.02", 0x51cb0c4e, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_cybotsj_qsound[] = {
    {"cyb.11m", 0x362ccab2, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"cyb.12m", 0x7066e9cc, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_cybotsj_key[] = {
    {"cybotsj.key", 0xd4d560b7, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_cybotsj[] = {
    {"maincpu", 4194304, 0, chips_cybotsj_maincpu, N(chips_cybotsj_maincpu)},
    {"gfx", 33554432, 0, chips_cybotsj_gfx, N(chips_cybotsj_gfx)},
    {"audiocpu", 327680, 0, chips_cybotsj_audiocpu, N(chips_cybotsj_audiocpu)},
    {"qsound", 4194304, 0, chips_cybotsj_qsound, N(chips_cybotsj_qsound)},
    {"key", 32, 0, chips_cybotsj_key, N(chips_cybotsj_key)},
};
static const Cps2Load chips_sfa_maincpu[] = {
    {"sfze.03d", 0xebf2054d, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfz.04b", 0x8b73b0e5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfz.05a", 0x0810544d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfz.06", 0x806e8f38, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfa_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"sfz.14m", 0x90fefdb3, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"sfz.16m", 0x5354c948, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"sfz.18m", 0x41a1e790, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"sfz.20m", 0xa549df98, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_sfa_audiocpu[] = {
    {"sfz.01", 0xffffec7d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfz.01", 0xffffec7d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfz.02", 0x45f46a08, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfa_qsound[] = {
    {"sfz.11m", 0xc4b093cd, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfz.12m", 0x8bdbc4b4, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfa_key[] = {
    {"sfa.key", 0x7c095631, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfa[] = {
    {"maincpu", 4194304, 0, chips_sfa_maincpu, N(chips_sfa_maincpu)},
    {"gfx", 16777216, 0, chips_sfa_gfx, N(chips_sfa_gfx)},
    {"audiocpu", 327680, 0, chips_sfa_audiocpu, N(chips_sfa_audiocpu)},
    {"qsound", 4194304, 0, chips_sfa_qsound, N(chips_sfa_qsound)},
    {"key", 32, 0, chips_sfa_key, N(chips_sfa_key)},
};
static const Cps2Load chips_sfar1_maincpu[] = {
    {"sfze.03c", 0xa1b69dd7, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfze.04b", 0xbb90acd5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfz.05a", 0x0810544d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfz.06", 0x806e8f38, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfar1_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"sfz.14m", 0x90fefdb3, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"sfz.16m", 0x5354c948, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"sfz.18m", 0x41a1e790, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"sfz.20m", 0xa549df98, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_sfar1_audiocpu[] = {
    {"sfz.01", 0xffffec7d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfz.01", 0xffffec7d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfz.02", 0x45f46a08, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfar1_qsound[] = {
    {"sfz.11m", 0xc4b093cd, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfz.12m", 0x8bdbc4b4, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfar1_key[] = {
    {"sfa.key", 0x7c095631, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfar1[] = {
    {"maincpu", 4194304, 0, chips_sfar1_maincpu, N(chips_sfar1_maincpu)},
    {"gfx", 16777216, 0, chips_sfar1_gfx, N(chips_sfar1_gfx)},
    {"audiocpu", 327680, 0, chips_sfar1_audiocpu, N(chips_sfar1_audiocpu)},
    {"qsound", 4194304, 0, chips_sfar1_qsound, N(chips_sfar1_qsound)},
    {"key", 32, 0, chips_sfar1_key, N(chips_sfar1_key)},
};
static const Cps2Load chips_sfar2_maincpu[] = {
    {"sfze.03b", 0x2bf5708e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfz.04a", 0x5f99e9a5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfz.05a", 0x0810544d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfz.06", 0x806e8f38, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfar2_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"sfz.14m", 0x90fefdb3, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"sfz.16m", 0x5354c948, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"sfz.18m", 0x41a1e790, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"sfz.20m", 0xa549df98, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_sfar2_audiocpu[] = {
    {"sfz.01", 0xffffec7d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfz.01", 0xffffec7d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfz.02", 0x45f46a08, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfar2_qsound[] = {
    {"sfz.11m", 0xc4b093cd, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfz.12m", 0x8bdbc4b4, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfar2_key[] = {
    {"sfa.key", 0x7c095631, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfar2[] = {
    {"maincpu", 4194304, 0, chips_sfar2_maincpu, N(chips_sfar2_maincpu)},
    {"gfx", 16777216, 0, chips_sfar2_gfx, N(chips_sfar2_gfx)},
    {"audiocpu", 327680, 0, chips_sfar2_audiocpu, N(chips_sfar2_audiocpu)},
    {"qsound", 4194304, 0, chips_sfar2_qsound, N(chips_sfar2_qsound)},
    {"key", 32, 0, chips_sfar2_key, N(chips_sfar2_key)},
};
static const Cps2Load chips_sfar3_maincpu[] = {
    {"sfze.03a", 0xfdbcd434, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfz.04", 0x0c436d30, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfz.05", 0x1f363612, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfz.06", 0x806e8f38, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfar3_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"sfz.14m", 0x90fefdb3, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"sfz.16m", 0x5354c948, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"sfz.18m", 0x41a1e790, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"sfz.20m", 0xa549df98, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_sfar3_audiocpu[] = {
    {"sfz.01", 0xffffec7d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfz.01", 0xffffec7d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfz.02", 0x45f46a08, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfar3_qsound[] = {
    {"sfz.11m", 0xc4b093cd, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfz.12m", 0x8bdbc4b4, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfar3_key[] = {
    {"sfa.key", 0x7c095631, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfar3[] = {
    {"maincpu", 4194304, 0, chips_sfar3_maincpu, N(chips_sfar3_maincpu)},
    {"gfx", 16777216, 0, chips_sfar3_gfx, N(chips_sfar3_gfx)},
    {"audiocpu", 327680, 0, chips_sfar3_audiocpu, N(chips_sfar3_audiocpu)},
    {"qsound", 4194304, 0, chips_sfar3_qsound, N(chips_sfar3_qsound)},
    {"key", 32, 0, chips_sfar3_key, N(chips_sfar3_key)},
};
static const Cps2Load chips_sfau_maincpu[] = {
    {"sfzu.03a", 0x49fc7db9, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfz.04a", 0x5f99e9a5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfz.05a", 0x0810544d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfz.06", 0x806e8f38, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfau_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"sfz.14m", 0x90fefdb3, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"sfz.16m", 0x5354c948, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"sfz.18m", 0x41a1e790, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"sfz.20m", 0xa549df98, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_sfau_audiocpu[] = {
    {"sfz.01", 0xffffec7d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfz.01", 0xffffec7d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfz.02", 0x45f46a08, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfau_qsound[] = {
    {"sfz.11m", 0xc4b093cd, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfz.12m", 0x8bdbc4b4, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfau_key[] = {
    {"sfau.key", 0x1dd0998d, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfau[] = {
    {"maincpu", 4194304, 0, chips_sfau_maincpu, N(chips_sfau_maincpu)},
    {"gfx", 16777216, 0, chips_sfau_gfx, N(chips_sfau_gfx)},
    {"audiocpu", 327680, 0, chips_sfau_audiocpu, N(chips_sfau_audiocpu)},
    {"qsound", 4194304, 0, chips_sfau_qsound, N(chips_sfau_qsound)},
    {"key", 32, 0, chips_sfau_key, N(chips_sfau_key)},
};
static const Cps2Load chips_sfza_maincpu[] = {
    {"sfza.03b", 0xca91bed9, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfz.04a", 0x5f99e9a5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfz.05a", 0x0810544d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfz.06", 0x806e8f38, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfza_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"sfz.14m", 0x90fefdb3, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"sfz.16m", 0x5354c948, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"sfz.18m", 0x41a1e790, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"sfz.20m", 0xa549df98, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_sfza_audiocpu[] = {
    {"sfz.01", 0xffffec7d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfz.01", 0xffffec7d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfz.02", 0x45f46a08, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfza_qsound[] = {
    {"sfz.11m", 0xc4b093cd, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfz.12m", 0x8bdbc4b4, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfza_key[] = {
    {"sfza.key", 0x2aa6ac63, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfza[] = {
    {"maincpu", 4194304, 0, chips_sfza_maincpu, N(chips_sfza_maincpu)},
    {"gfx", 16777216, 0, chips_sfza_gfx, N(chips_sfza_gfx)},
    {"audiocpu", 327680, 0, chips_sfza_audiocpu, N(chips_sfza_audiocpu)},
    {"qsound", 4194304, 0, chips_sfza_qsound, N(chips_sfza_qsound)},
    {"key", 32, 0, chips_sfza_key, N(chips_sfza_key)},
};
static const Cps2Load chips_sfzar1_maincpu[] = {
    {"sfza.03a", 0xf38d8c8d, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfz.04", 0x0c436d30, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfz.05", 0x1f363612, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfz.06", 0x806e8f38, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfzar1_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"sfz.14m", 0x90fefdb3, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"sfz.16m", 0x5354c948, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"sfz.18m", 0x41a1e790, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"sfz.20m", 0xa549df98, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_sfzar1_audiocpu[] = {
    {"sfz.01", 0xffffec7d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfz.01", 0xffffec7d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfz.02", 0x45f46a08, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfzar1_qsound[] = {
    {"sfz.11m", 0xc4b093cd, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfz.12m", 0x8bdbc4b4, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfzar1_key[] = {
    {"sfza.key", 0x2aa6ac63, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfzar1[] = {
    {"maincpu", 4194304, 0, chips_sfzar1_maincpu, N(chips_sfzar1_maincpu)},
    {"gfx", 16777216, 0, chips_sfzar1_gfx, N(chips_sfzar1_gfx)},
    {"audiocpu", 327680, 0, chips_sfzar1_audiocpu, N(chips_sfzar1_audiocpu)},
    {"qsound", 4194304, 0, chips_sfzar1_qsound, N(chips_sfzar1_qsound)},
    {"key", 32, 0, chips_sfzar1_key, N(chips_sfzar1_key)},
};
static const Cps2Load chips_sfzj_maincpu[] = {
    {"sfzj.03c", 0xf5444120, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfz.04b", 0x8b73b0e5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfz.05a", 0x0810544d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfz.06", 0x806e8f38, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfzj_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"sfz.14m", 0x90fefdb3, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"sfz.16m", 0x5354c948, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"sfz.18m", 0x41a1e790, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"sfz.20m", 0xa549df98, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_sfzj_audiocpu[] = {
    {"sfz.01", 0xffffec7d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfz.01", 0xffffec7d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfz.02", 0x45f46a08, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfzj_qsound[] = {
    {"sfz.11m", 0xc4b093cd, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfz.12m", 0x8bdbc4b4, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfzj_key[] = {
    {"sfzj.key", 0x355d85b8, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfzj[] = {
    {"maincpu", 4194304, 0, chips_sfzj_maincpu, N(chips_sfzj_maincpu)},
    {"gfx", 16777216, 0, chips_sfzj_gfx, N(chips_sfzj_gfx)},
    {"audiocpu", 327680, 0, chips_sfzj_audiocpu, N(chips_sfzj_audiocpu)},
    {"qsound", 4194304, 0, chips_sfzj_qsound, N(chips_sfzj_qsound)},
    {"key", 32, 0, chips_sfzj_key, N(chips_sfzj_key)},
};
static const Cps2Load chips_sfzjr1_maincpu[] = {
    {"sfzj.03b", 0x844220c2, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfz.04a", 0x5f99e9a5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfz.05a", 0x0810544d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfz.06", 0x806e8f38, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfzjr1_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"sfz.14m", 0x90fefdb3, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"sfz.16m", 0x5354c948, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"sfz.18m", 0x41a1e790, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"sfz.20m", 0xa549df98, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_sfzjr1_audiocpu[] = {
    {"sfz.01", 0xffffec7d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfz.01", 0xffffec7d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfz.02", 0x45f46a08, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfzjr1_qsound[] = {
    {"sfz.11m", 0xc4b093cd, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfz.12m", 0x8bdbc4b4, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfzjr1_key[] = {
    {"sfzj.key", 0x355d85b8, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfzjr1[] = {
    {"maincpu", 4194304, 0, chips_sfzjr1_maincpu, N(chips_sfzjr1_maincpu)},
    {"gfx", 16777216, 0, chips_sfzjr1_gfx, N(chips_sfzjr1_gfx)},
    {"audiocpu", 327680, 0, chips_sfzjr1_audiocpu, N(chips_sfzjr1_audiocpu)},
    {"qsound", 4194304, 0, chips_sfzjr1_qsound, N(chips_sfzjr1_qsound)},
    {"key", 32, 0, chips_sfzjr1_key, N(chips_sfzjr1_key)},
};
static const Cps2Load chips_sfzjr2_maincpu[] = {
    {"sfzj.03a", 0x3cfce93c, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfz.04", 0x0c436d30, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfz.05", 0x1f363612, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfz.06", 0x806e8f38, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfzjr2_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"sfz.14m", 0x90fefdb3, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"sfz.16m", 0x5354c948, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"sfz.18m", 0x41a1e790, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"sfz.20m", 0xa549df98, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_sfzjr2_audiocpu[] = {
    {"sfz.01", 0xffffec7d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfz.01", 0xffffec7d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfz.02", 0x45f46a08, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfzjr2_qsound[] = {
    {"sfz.11m", 0xc4b093cd, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfz.12m", 0x8bdbc4b4, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfzjr2_key[] = {
    {"sfzj.key", 0x355d85b8, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfzjr2[] = {
    {"maincpu", 4194304, 0, chips_sfzjr2_maincpu, N(chips_sfzjr2_maincpu)},
    {"gfx", 16777216, 0, chips_sfzjr2_gfx, N(chips_sfzjr2_gfx)},
    {"audiocpu", 327680, 0, chips_sfzjr2_audiocpu, N(chips_sfzjr2_audiocpu)},
    {"qsound", 4194304, 0, chips_sfzjr2_qsound, N(chips_sfzjr2_qsound)},
    {"key", 32, 0, chips_sfzjr2_key, N(chips_sfzjr2_key)},
};
static const Cps2Load chips_sfzh_maincpu[] = {
    {"sfzh.03d", 0x6e08cbe0, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfz.04c", 0xbb90acd5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfz.05c", 0x0810544d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfz.06", 0x806e8f38, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfzh_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"sfz.14m", 0x90fefdb3, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"sfz.16m", 0x5354c948, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"sfz.18m", 0x41a1e790, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"sfz.20m", 0xa549df98, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_sfzh_audiocpu[] = {
    {"sfz.01", 0xffffec7d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfz.01", 0xffffec7d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfz.02", 0x45f46a08, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfzh_qsound[] = {
    {"sfz.11m", 0xc4b093cd, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfz.12m", 0x8bdbc4b4, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfzh_key[] = {
    {"sfzh.key", 0x4763446f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfzh[] = {
    {"maincpu", 4194304, 0, chips_sfzh_maincpu, N(chips_sfzh_maincpu)},
    {"gfx", 16777216, 0, chips_sfzh_gfx, N(chips_sfzh_gfx)},
    {"audiocpu", 327680, 0, chips_sfzh_audiocpu, N(chips_sfzh_audiocpu)},
    {"qsound", 4194304, 0, chips_sfzh_qsound, N(chips_sfzh_qsound)},
    {"key", 32, 0, chips_sfzh_key, N(chips_sfzh_key)},
};
static const Cps2Load chips_sfzhr1_maincpu[] = {
    {"sfzh.03c", 0xbce635aa, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfz.04a", 0x5f99e9a5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfz.05a", 0x0810544d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfz.06", 0x806e8f38, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfzhr1_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"sfz.14m", 0x90fefdb3, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"sfz.16m", 0x5354c948, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"sfz.18m", 0x41a1e790, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"sfz.20m", 0xa549df98, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_sfzhr1_audiocpu[] = {
    {"sfz.01", 0xffffec7d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfz.01", 0xffffec7d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfz.02", 0x45f46a08, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfzhr1_qsound[] = {
    {"sfz.11m", 0xc4b093cd, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfz.12m", 0x8bdbc4b4, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfzhr1_key[] = {
    {"sfzh.key", 0x4763446f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfzhr1[] = {
    {"maincpu", 4194304, 0, chips_sfzhr1_maincpu, N(chips_sfzhr1_maincpu)},
    {"gfx", 16777216, 0, chips_sfzhr1_gfx, N(chips_sfzhr1_gfx)},
    {"audiocpu", 327680, 0, chips_sfzhr1_audiocpu, N(chips_sfzhr1_audiocpu)},
    {"qsound", 4194304, 0, chips_sfzhr1_qsound, N(chips_sfzhr1_qsound)},
    {"key", 32, 0, chips_sfzhr1_key, N(chips_sfzhr1_key)},
};
static const Cps2Load chips_sfzb_maincpu[] = {
    {"sfzb.03g", 0x348862d4, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfzb.04e", 0x8d9b2480, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfz.05a", 0x0810544d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfz.06", 0x806e8f38, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfzb_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"sfz.14m", 0x90fefdb3, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"sfz.16m", 0x5354c948, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"sfz.18m", 0x41a1e790, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"sfz.20m", 0xa549df98, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_sfzb_audiocpu[] = {
    {"sfz.01", 0xffffec7d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfz.01", 0xffffec7d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfz.02", 0x45f46a08, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfzb_qsound[] = {
    {"sfz.11m", 0xc4b093cd, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfz.12m", 0x8bdbc4b4, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfzb_key[] = {
    {"sfzb.key", 0xb0570359, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfzb[] = {
    {"maincpu", 4194304, 0, chips_sfzb_maincpu, N(chips_sfzb_maincpu)},
    {"gfx", 16777216, 0, chips_sfzb_gfx, N(chips_sfzb_gfx)},
    {"audiocpu", 327680, 0, chips_sfzb_audiocpu, N(chips_sfzb_audiocpu)},
    {"qsound", 4194304, 0, chips_sfzb_qsound, N(chips_sfzb_qsound)},
    {"key", 32, 0, chips_sfzb_key, N(chips_sfzb_key)},
};
static const Cps2Load chips_sfzbr1_maincpu[] = {
    {"sfzb.03e", 0xecba89a3, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfz.04b", 0x8b73b0e5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfz.05a", 0x0810544d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfz.06", 0x806e8f38, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfzbr1_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"sfz.14m", 0x90fefdb3, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"sfz.16m", 0x5354c948, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"sfz.18m", 0x41a1e790, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"sfz.20m", 0xa549df98, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_sfzbr1_audiocpu[] = {
    {"sfz.01", 0xffffec7d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfz.01", 0xffffec7d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfz.02", 0x45f46a08, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfzbr1_qsound[] = {
    {"sfz.11m", 0xc4b093cd, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfz.12m", 0x8bdbc4b4, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfzbr1_key[] = {
    {"sfzb.key", 0xb0570359, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfzbr1[] = {
    {"maincpu", 4194304, 0, chips_sfzbr1_maincpu, N(chips_sfzbr1_maincpu)},
    {"gfx", 16777216, 0, chips_sfzbr1_gfx, N(chips_sfzbr1_gfx)},
    {"audiocpu", 327680, 0, chips_sfzbr1_audiocpu, N(chips_sfzbr1_audiocpu)},
    {"qsound", 4194304, 0, chips_sfzbr1_qsound, N(chips_sfzbr1_qsound)},
    {"key", 32, 0, chips_sfzbr1_key, N(chips_sfzbr1_key)},
};
static const Cps2Load chips_mmancp2u_maincpu[] = {
    {"rcmu.03b", 0xc39f037f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"rcmu.04b", 0xcd6f5e99, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"rcm.05b", 0x4376ea95, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mmancp2u_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"rcm.73", 0x774c6e04, 524288, 0, 8388608, 524288, CPS2_WORD64},
    {"rcm.63", 0xacad7c62, 524288, 0, 8388610, 524288, CPS2_WORD64},
    {"rcm.83", 0x6af30499, 524288, 0, 8388612, 524288, CPS2_WORD64},
    {"rcm.93", 0x7a5a5166, 524288, 0, 8388614, 524288, CPS2_WORD64},
    {"rcm.74", 0x004ec725, 524288, 0, 10485760, 524288, CPS2_WORD64},
    {"rcm.64", 0x65c0464e, 524288, 0, 10485762, 524288, CPS2_WORD64},
    {"rcm.84", 0xfb3097cc, 524288, 0, 10485764, 524288, CPS2_WORD64},
    {"rcm.94", 0x2e16557a, 524288, 0, 10485766, 524288, CPS2_WORD64},
    {"rcm.75", 0x70a73f99, 524288, 0, 12582912, 524288, CPS2_WORD64},
    {"rcm.65", 0xecedad3d, 524288, 0, 12582914, 524288, CPS2_WORD64},
    {"rcm.85", 0x3d6186d8, 524288, 0, 12582916, 524288, CPS2_WORD64},
    {"rcm.95", 0x8c7700f1, 524288, 0, 12582918, 524288, CPS2_WORD64},
    {"rcm.76", 0x89a889ad, 524288, 0, 14680064, 524288, CPS2_WORD64},
    {"rcm.66", 0x1300eb7b, 524288, 0, 14680066, 524288, CPS2_WORD64},
    {"rcm.86", 0x6d974ebd, 524288, 0, 14680068, 524288, CPS2_WORD64},
    {"rcm.96", 0x7da4cd24, 524288, 0, 14680070, 524288, CPS2_WORD64},
};
static const Cps2Load chips_mmancp2u_audiocpu[] = {
    {"rcm.01", 0xd60cf8a3, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"rcm.01", 0xd60cf8a3, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_mmancp2u_qsound[] = {
    {"rcm.51", 0xb6d07080, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"rcm.52", 0xdfddc493, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"rcm.53", 0x6062ae3a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"rcm.54", 0x08c6f3bf, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"rcm.55", 0xf97dfccc, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"rcm.56", 0xade475bc, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"rcm.57", 0x075effb3, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"rcm.58", 0xf6c1f87b, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mmancp2u_key[] = {
    {"mmancp2u.key", 0x17ca6659, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mmancp2u[] = {
    {"maincpu", 4194304, 0, chips_mmancp2u_maincpu, N(chips_mmancp2u_maincpu)},
    {"gfx", 16777216, 0, chips_mmancp2u_gfx, N(chips_mmancp2u_gfx)},
    {"audiocpu", 327680, 0, chips_mmancp2u_audiocpu, N(chips_mmancp2u_audiocpu)},
    {"qsound", 4194304, 0, chips_mmancp2u_qsound, N(chips_mmancp2u_qsound)},
    {"key", 32, 0, chips_mmancp2u_key, N(chips_mmancp2u_key)},
};
static const Cps2Load chips_mmancp2ur1_maincpu[] = {
    {"rcmu.03a", 0xc6b75320, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"rcmu.04a", 0x47880111, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"rcmu.05a", 0x4376ea95, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mmancp2ur1_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"rcm.73", 0x774c6e04, 524288, 0, 8388608, 524288, CPS2_WORD64},
    {"rcm.63", 0xacad7c62, 524288, 0, 8388610, 524288, CPS2_WORD64},
    {"rcm.83", 0x6af30499, 524288, 0, 8388612, 524288, CPS2_WORD64},
    {"rcm.93", 0x7a5a5166, 524288, 0, 8388614, 524288, CPS2_WORD64},
    {"rcm.74", 0x004ec725, 524288, 0, 10485760, 524288, CPS2_WORD64},
    {"rcm.64", 0x65c0464e, 524288, 0, 10485762, 524288, CPS2_WORD64},
    {"rcm.84", 0xfb3097cc, 524288, 0, 10485764, 524288, CPS2_WORD64},
    {"rcm.94", 0x2e16557a, 524288, 0, 10485766, 524288, CPS2_WORD64},
    {"rcm.75", 0x70a73f99, 524288, 0, 12582912, 524288, CPS2_WORD64},
    {"rcm.65", 0xecedad3d, 524288, 0, 12582914, 524288, CPS2_WORD64},
    {"rcm.85", 0x3d6186d8, 524288, 0, 12582916, 524288, CPS2_WORD64},
    {"rcm.95", 0x8c7700f1, 524288, 0, 12582918, 524288, CPS2_WORD64},
    {"rcm.76", 0x89a889ad, 524288, 0, 14680064, 524288, CPS2_WORD64},
    {"rcm.66", 0x1300eb7b, 524288, 0, 14680066, 524288, CPS2_WORD64},
    {"rcm.86", 0x6d974ebd, 524288, 0, 14680068, 524288, CPS2_WORD64},
    {"rcm.96", 0x7da4cd24, 524288, 0, 14680070, 524288, CPS2_WORD64},
};
static const Cps2Load chips_mmancp2ur1_audiocpu[] = {
    {"rcm.01", 0xd60cf8a3, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"rcm.01", 0xd60cf8a3, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_mmancp2ur1_qsound[] = {
    {"rcm.51", 0xb6d07080, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"rcm.52", 0xdfddc493, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"rcm.53", 0x6062ae3a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"rcm.54", 0x08c6f3bf, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"rcm.55", 0xf97dfccc, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"rcm.56", 0xade475bc, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"rcm.57", 0x075effb3, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"rcm.58", 0xf6c1f87b, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mmancp2ur1_key[] = {
    {"mmancp2u.key", 0x17ca6659, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mmancp2ur1[] = {
    {"maincpu", 4194304, 0, chips_mmancp2ur1_maincpu, N(chips_mmancp2ur1_maincpu)},
    {"gfx", 16777216, 0, chips_mmancp2ur1_gfx, N(chips_mmancp2ur1_gfx)},
    {"audiocpu", 327680, 0, chips_mmancp2ur1_audiocpu, N(chips_mmancp2ur1_audiocpu)},
    {"qsound", 4194304, 0, chips_mmancp2ur1_qsound, N(chips_mmancp2ur1_qsound)},
    {"key", 32, 0, chips_mmancp2ur1_key, N(chips_mmancp2ur1_key)},
};
static const Cps2Load chips_mmancp2ur2_maincpu[] = {
    {"rcmu.03", 0x3cfdb1bb, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"rcmu.04", 0x169bf5e8, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"rcmu.05", 0x4376ea95, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mmancp2ur2_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"rcm.73", 0x774c6e04, 524288, 0, 8388608, 524288, CPS2_WORD64},
    {"rcm.63", 0xacad7c62, 524288, 0, 8388610, 524288, CPS2_WORD64},
    {"rcm.83", 0x6af30499, 524288, 0, 8388612, 524288, CPS2_WORD64},
    {"rcm.93", 0x7a5a5166, 524288, 0, 8388614, 524288, CPS2_WORD64},
    {"rcm.74", 0x004ec725, 524288, 0, 10485760, 524288, CPS2_WORD64},
    {"rcm.64", 0x65c0464e, 524288, 0, 10485762, 524288, CPS2_WORD64},
    {"rcm.84", 0xfb3097cc, 524288, 0, 10485764, 524288, CPS2_WORD64},
    {"rcm.94", 0x2e16557a, 524288, 0, 10485766, 524288, CPS2_WORD64},
    {"rcm.75", 0x70a73f99, 524288, 0, 12582912, 524288, CPS2_WORD64},
    {"rcm.65", 0xecedad3d, 524288, 0, 12582914, 524288, CPS2_WORD64},
    {"rcm.85", 0x3d6186d8, 524288, 0, 12582916, 524288, CPS2_WORD64},
    {"rcm.95", 0x8c7700f1, 524288, 0, 12582918, 524288, CPS2_WORD64},
    {"rcm.76", 0x89a889ad, 524288, 0, 14680064, 524288, CPS2_WORD64},
    {"rcm.66", 0x1300eb7b, 524288, 0, 14680066, 524288, CPS2_WORD64},
    {"rcm.86", 0x6d974ebd, 524288, 0, 14680068, 524288, CPS2_WORD64},
    {"rcm.96", 0x7da4cd24, 524288, 0, 14680070, 524288, CPS2_WORD64},
};
static const Cps2Load chips_mmancp2ur2_audiocpu[] = {
    {"rcm.01", 0xd60cf8a3, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"rcm.01", 0xd60cf8a3, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_mmancp2ur2_qsound[] = {
    {"rcm.51", 0xb6d07080, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"rcm.52", 0xdfddc493, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"rcm.53", 0x6062ae3a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"rcm.54", 0x08c6f3bf, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"rcm.55", 0xf97dfccc, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"rcm.56", 0xade475bc, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"rcm.57", 0x075effb3, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"rcm.58", 0xf6c1f87b, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mmancp2ur2_key[] = {
    {"mmancp2u.key", 0x17ca6659, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mmancp2ur2[] = {
    {"maincpu", 4194304, 0, chips_mmancp2ur2_maincpu, N(chips_mmancp2ur2_maincpu)},
    {"gfx", 16777216, 0, chips_mmancp2ur2_gfx, N(chips_mmancp2ur2_gfx)},
    {"audiocpu", 327680, 0, chips_mmancp2ur2_audiocpu, N(chips_mmancp2ur2_audiocpu)},
    {"qsound", 4194304, 0, chips_mmancp2ur2_qsound, N(chips_mmancp2ur2_qsound)},
    {"key", 32, 0, chips_mmancp2ur2_key, N(chips_mmancp2ur2_key)},
};
static const Cps2Load chips_rmancp2j_maincpu[] = {
    {"rcmj.03a", 0x30559f60, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"rcmj.04a", 0x5efc9366, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"rcm.05a", 0x517ccde2, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_rmancp2j_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"rcm.73", 0x774c6e04, 524288, 0, 8388608, 524288, CPS2_WORD64},
    {"rcm.63", 0xacad7c62, 524288, 0, 8388610, 524288, CPS2_WORD64},
    {"rcm.83", 0x6af30499, 524288, 0, 8388612, 524288, CPS2_WORD64},
    {"rcm.93", 0x7a5a5166, 524288, 0, 8388614, 524288, CPS2_WORD64},
    {"rcm.74", 0x004ec725, 524288, 0, 10485760, 524288, CPS2_WORD64},
    {"rcm.64", 0x65c0464e, 524288, 0, 10485762, 524288, CPS2_WORD64},
    {"rcm.84", 0xfb3097cc, 524288, 0, 10485764, 524288, CPS2_WORD64},
    {"rcm.94", 0x2e16557a, 524288, 0, 10485766, 524288, CPS2_WORD64},
    {"rcm.75", 0x70a73f99, 524288, 0, 12582912, 524288, CPS2_WORD64},
    {"rcm.65", 0xecedad3d, 524288, 0, 12582914, 524288, CPS2_WORD64},
    {"rcm.85", 0x3d6186d8, 524288, 0, 12582916, 524288, CPS2_WORD64},
    {"rcm.95", 0x8c7700f1, 524288, 0, 12582918, 524288, CPS2_WORD64},
    {"rcm.76", 0x89a889ad, 524288, 0, 14680064, 524288, CPS2_WORD64},
    {"rcm.66", 0x1300eb7b, 524288, 0, 14680066, 524288, CPS2_WORD64},
    {"rcm.86", 0x6d974ebd, 524288, 0, 14680068, 524288, CPS2_WORD64},
    {"rcm.96", 0x7da4cd24, 524288, 0, 14680070, 524288, CPS2_WORD64},
};
static const Cps2Load chips_rmancp2j_audiocpu[] = {
    {"rcm.01", 0xd60cf8a3, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"rcm.01", 0xd60cf8a3, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_rmancp2j_qsound[] = {
    {"rcm.51", 0xb6d07080, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"rcm.52", 0xdfddc493, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"rcm.53", 0x6062ae3a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"rcm.54", 0x08c6f3bf, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"rcm.55", 0xf97dfccc, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"rcm.56", 0xade475bc, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"rcm.57", 0x075effb3, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"rcm.58", 0xf6c1f87b, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_rmancp2j_key[] = {
    {"rmancp2j.key", 0x17309a70, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_rmancp2j[] = {
    {"maincpu", 4194304, 0, chips_rmancp2j_maincpu, N(chips_rmancp2j_maincpu)},
    {"gfx", 16777216, 0, chips_rmancp2j_gfx, N(chips_rmancp2j_gfx)},
    {"audiocpu", 327680, 0, chips_rmancp2j_audiocpu, N(chips_rmancp2j_audiocpu)},
    {"qsound", 4194304, 0, chips_rmancp2j_qsound, N(chips_rmancp2j_qsound)},
    {"key", 32, 0, chips_rmancp2j_key, N(chips_rmancp2j_key)},
};
static const Cps2Load chips_msh_maincpu[] = {
    {"mshe.03e", 0xbd951414, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mshe.04e", 0x19dd42f2, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"msh.05", 0x6a091b9e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"msh.06b", 0x803e3fa4, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"msh.07a", 0xc45f8e27, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"msh.08a", 0x9ca6f12c, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"msh.09a", 0x82ec27af, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"msh.10b", 0x8d931196, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_msh_gfx[] = {
    {"msh.13m", 0x09d14566, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"msh.15m", 0xee962057, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"msh.17m", 0x604ece14, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"msh.19m", 0x94a731e8, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"msh.14m", 0x4197973e, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"msh.16m", 0x438da4a0, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"msh.18m", 0x4db92d94, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"msh.20m", 0xa2b0c6c0, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_msh_audiocpu[] = {
    {"msh.01", 0xc976e6f9, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"msh.01", 0xc976e6f9, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"msh.02", 0xce67d0d9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_msh_qsound[] = {
    {"msh.11m", 0x37ac6d30, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"msh.12m", 0xde092570, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_msh_key[] = {
    {"msh.key", 0xb494368e, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_msh[] = {
    {"maincpu", 4194304, 0, chips_msh_maincpu, N(chips_msh_maincpu)},
    {"gfx", 33554432, 0, chips_msh_gfx, N(chips_msh_gfx)},
    {"audiocpu", 327680, 0, chips_msh_audiocpu, N(chips_msh_audiocpu)},
    {"qsound", 4194304, 0, chips_msh_qsound, N(chips_msh_qsound)},
    {"key", 32, 0, chips_msh_key, N(chips_msh_key)},
};
static const Cps2Load chips_mshu_maincpu[] = {
    {"mshu.03", 0xd2805bdd, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mshu.04", 0x743f96ff, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"msh.05", 0x6a091b9e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"msh.06b", 0x803e3fa4, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"msh.07a", 0xc45f8e27, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"msh.08a", 0x9ca6f12c, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"msh.09a", 0x82ec27af, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"msh.10b", 0x8d931196, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshu_gfx[] = {
    {"msh.13m", 0x09d14566, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"msh.15m", 0xee962057, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"msh.17m", 0x604ece14, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"msh.19m", 0x94a731e8, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"msh.14m", 0x4197973e, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"msh.16m", 0x438da4a0, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"msh.18m", 0x4db92d94, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"msh.20m", 0xa2b0c6c0, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshu_audiocpu[] = {
    {"msh.01", 0xc976e6f9, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"msh.01", 0xc976e6f9, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"msh.02", 0xce67d0d9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshu_qsound[] = {
    {"msh.11m", 0x37ac6d30, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"msh.12m", 0xde092570, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_mshu_key[] = {
    {"mshu.key", 0x745c1bee, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshu[] = {
    {"maincpu", 4194304, 0, chips_mshu_maincpu, N(chips_mshu_maincpu)},
    {"gfx", 33554432, 0, chips_mshu_gfx, N(chips_mshu_gfx)},
    {"audiocpu", 327680, 0, chips_mshu_audiocpu, N(chips_mshu_audiocpu)},
    {"qsound", 4194304, 0, chips_mshu_qsound, N(chips_mshu_qsound)},
    {"key", 32, 0, chips_mshu_key, N(chips_mshu_key)},
};
static const Cps2Load chips_mshj_maincpu[] = {
    {"mshj.03g", 0x261f4091, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mshj.04g", 0x61d791c6, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"msh.05a", 0xf37539e6, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"msh.06b", 0x803e3fa4, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"msh.07a", 0xc45f8e27, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"msh.08a", 0x9ca6f12c, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"msh.09a", 0x82ec27af, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"msh.10b", 0x8d931196, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshj_gfx[] = {
    {"msh.13m", 0x09d14566, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"msh.15m", 0xee962057, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"msh.17m", 0x604ece14, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"msh.19m", 0x94a731e8, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"msh.14m", 0x4197973e, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"msh.16m", 0x438da4a0, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"msh.18m", 0x4db92d94, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"msh.20m", 0xa2b0c6c0, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshj_audiocpu[] = {
    {"msh.01", 0xc976e6f9, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"msh.01", 0xc976e6f9, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"msh.02", 0xce67d0d9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshj_qsound[] = {
    {"msh.11m", 0x37ac6d30, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"msh.12m", 0xde092570, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_mshj_key[] = {
    {"mshj.key", 0x888761ac, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshj[] = {
    {"maincpu", 4194304, 0, chips_mshj_maincpu, N(chips_mshj_maincpu)},
    {"gfx", 33554432, 0, chips_mshj_gfx, N(chips_mshj_gfx)},
    {"audiocpu", 327680, 0, chips_mshj_audiocpu, N(chips_mshj_audiocpu)},
    {"qsound", 4194304, 0, chips_mshj_qsound, N(chips_mshj_qsound)},
    {"key", 32, 0, chips_mshj_key, N(chips_mshj_key)},
};
static const Cps2Load chips_mshjr1_maincpu[] = {
    {"mshj.03f", 0xff172fd2, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mshj.04f", 0xebbb205a, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"msh.05", 0x6a091b9e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"msh.06b", 0x803e3fa4, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"msh.07a", 0xc45f8e27, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"msh.08a", 0x9ca6f12c, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"msh.09a", 0x82ec27af, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"msh.10b", 0x8d931196, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshjr1_gfx[] = {
    {"msh.13m", 0x09d14566, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"msh.15m", 0xee962057, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"msh.17m", 0x604ece14, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"msh.19m", 0x94a731e8, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"msh.14m", 0x4197973e, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"msh.16m", 0x438da4a0, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"msh.18m", 0x4db92d94, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"msh.20m", 0xa2b0c6c0, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshjr1_audiocpu[] = {
    {"msh.01", 0xc976e6f9, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"msh.01", 0xc976e6f9, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"msh.02", 0xce67d0d9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshjr1_qsound[] = {
    {"msh.11m", 0x37ac6d30, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"msh.12m", 0xde092570, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_mshjr1_key[] = {
    {"mshj.key", 0x888761ac, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshjr1[] = {
    {"maincpu", 4194304, 0, chips_mshjr1_maincpu, N(chips_mshjr1_maincpu)},
    {"gfx", 33554432, 0, chips_mshjr1_gfx, N(chips_mshjr1_gfx)},
    {"audiocpu", 327680, 0, chips_mshjr1_audiocpu, N(chips_mshjr1_audiocpu)},
    {"qsound", 4194304, 0, chips_mshjr1_qsound, N(chips_mshjr1_qsound)},
    {"key", 32, 0, chips_mshjr1_key, N(chips_mshjr1_key)},
};
static const Cps2Load chips_msha_maincpu[] = {
    {"msha.03e", 0xec84ec44, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"msha.04e", 0x098b8503, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"msh.05", 0x6a091b9e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"msh.06b", 0x803e3fa4, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"msh.07a", 0xc45f8e27, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"msh.08a", 0x9ca6f12c, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"msh.09a", 0x82ec27af, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"msh.10b", 0x8d931196, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_msha_gfx[] = {
    {"msh.13m", 0x09d14566, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"msh.15m", 0xee962057, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"msh.17m", 0x604ece14, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"msh.19m", 0x94a731e8, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"msh.14m", 0x4197973e, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"msh.16m", 0x438da4a0, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"msh.18m", 0x4db92d94, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"msh.20m", 0xa2b0c6c0, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_msha_audiocpu[] = {
    {"msh.01", 0xc976e6f9, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"msh.01", 0xc976e6f9, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"msh.02", 0xce67d0d9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_msha_qsound[] = {
    {"msh.11m", 0x37ac6d30, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"msh.12m", 0xde092570, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_msha_key[] = {
    {"msha.key", 0x00f3f2ca, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_msha[] = {
    {"maincpu", 4194304, 0, chips_msha_maincpu, N(chips_msha_maincpu)},
    {"gfx", 33554432, 0, chips_msha_gfx, N(chips_msha_gfx)},
    {"audiocpu", 327680, 0, chips_msha_audiocpu, N(chips_msha_audiocpu)},
    {"qsound", 4194304, 0, chips_msha_qsound, N(chips_msha_qsound)},
    {"key", 32, 0, chips_msha_key, N(chips_msha_key)},
};
static const Cps2Load chips_mshh_maincpu[] = {
    {"mshh.03c", 0x8d84b0fa, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mshh.04c", 0xd638f601, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"msh.05a", 0xf37539e6, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"msh.06b", 0x803e3fa4, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"msh.07a", 0xc45f8e27, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"msh.08a", 0x9ca6f12c, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"msh.09a", 0x82ec27af, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"msh.10b", 0x8d931196, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshh_gfx[] = {
    {"msh.13m", 0x09d14566, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"msh.15m", 0xee962057, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"msh.17m", 0x604ece14, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"msh.19m", 0x94a731e8, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"msh.14m", 0x4197973e, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"msh.16m", 0x438da4a0, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"msh.18m", 0x4db92d94, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"msh.20m", 0xa2b0c6c0, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshh_audiocpu[] = {
    {"msh.01", 0xc976e6f9, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"msh.01", 0xc976e6f9, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"msh.02", 0xce67d0d9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshh_qsound[] = {
    {"msh.11m", 0x37ac6d30, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"msh.12m", 0xde092570, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_mshh_key[] = {
    {"mshh.key", 0x5dddf5e7, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshh[] = {
    {"maincpu", 4194304, 0, chips_mshh_maincpu, N(chips_mshh_maincpu)},
    {"gfx", 33554432, 0, chips_mshh_gfx, N(chips_mshh_gfx)},
    {"audiocpu", 327680, 0, chips_mshh_audiocpu, N(chips_mshh_audiocpu)},
    {"qsound", 4194304, 0, chips_mshh_qsound, N(chips_mshh_qsound)},
    {"key", 32, 0, chips_mshh_key, N(chips_mshh_key)},
};
static const Cps2Load chips_mshb_maincpu[] = {
    {"mshb.03c", 0x19697f74, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mshb.04c", 0x95317a6f, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"msh.05a", 0xf37539e6, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"msh.06b", 0x803e3fa4, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"msh.07a", 0xc45f8e27, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"msh.08a", 0x9ca6f12c, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"msh.09a", 0x82ec27af, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"msh.10b", 0x8d931196, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshb_gfx[] = {
    {"msh.13m", 0x09d14566, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"msh.15m", 0xee962057, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"msh.17m", 0x604ece14, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"msh.19m", 0x94a731e8, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"msh.14m", 0x4197973e, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"msh.16m", 0x438da4a0, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"msh.18m", 0x4db92d94, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"msh.20m", 0xa2b0c6c0, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshb_audiocpu[] = {
    {"msh.01", 0xc976e6f9, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"msh.01", 0xc976e6f9, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"msh.02", 0xce67d0d9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshb_qsound[] = {
    {"msh.11m", 0x37ac6d30, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"msh.12m", 0xde092570, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_mshb_key[] = {
    {"mshb.key", 0x92196837, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshb[] = {
    {"maincpu", 4194304, 0, chips_mshb_maincpu, N(chips_mshb_maincpu)},
    {"gfx", 33554432, 0, chips_mshb_gfx, N(chips_mshb_gfx)},
    {"audiocpu", 327680, 0, chips_mshb_audiocpu, N(chips_mshb_audiocpu)},
    {"qsound", 4194304, 0, chips_mshb_qsound, N(chips_mshb_qsound)},
    {"key", 32, 0, chips_mshb_key, N(chips_mshb_key)},
};
static const Cps2Load chips_mshbr1_maincpu[] = {
    {"mshb.03b", 0xeb16165b, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mshb.04b", 0x94fb3c97, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"msh.05", 0x6a091b9e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"msh.06b", 0x803e3fa4, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"msh.07a", 0xc45f8e27, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"msh.08a", 0x9ca6f12c, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"msh.09a", 0x82ec27af, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"msh.10b", 0x8d931196, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshbr1_gfx[] = {
    {"msh.13m", 0x09d14566, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"msh.15m", 0xee962057, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"msh.17m", 0x604ece14, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"msh.19m", 0x94a731e8, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"msh.14m", 0x4197973e, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"msh.16m", 0x438da4a0, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"msh.18m", 0x4db92d94, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"msh.20m", 0xa2b0c6c0, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshbr1_audiocpu[] = {
    {"msh.01", 0xc976e6f9, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"msh.01", 0xc976e6f9, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"msh.02", 0xce67d0d9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshbr1_qsound[] = {
    {"msh.11m", 0x37ac6d30, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"msh.12m", 0xde092570, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_mshbr1_key[] = {
    {"mshb.key", 0x92196837, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshbr1[] = {
    {"maincpu", 4194304, 0, chips_mshbr1_maincpu, N(chips_mshbr1_maincpu)},
    {"gfx", 33554432, 0, chips_mshbr1_gfx, N(chips_mshbr1_gfx)},
    {"audiocpu", 327680, 0, chips_mshbr1_audiocpu, N(chips_mshbr1_audiocpu)},
    {"qsound", 4194304, 0, chips_mshbr1_qsound, N(chips_mshbr1_qsound)},
    {"key", 32, 0, chips_mshbr1_key, N(chips_mshbr1_key)},
};
static const Cps2Load chips_19xx_maincpu[] = {
    {"19xe.03b", 0x9bf9d9b1, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"19xe.04b", 0x9aa46476, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"19xe.05b", 0xa04a2c5e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"19xe.06b", 0xf0a81c33, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"19x.07", 0x61c0296c, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_19xx_gfx[] = {
    {"19x.13m", 0x427aeb18, 524288, 0, 0, 524288, CPS2_WORD64},
    {"19x.15m", 0x63bdbf54, 524288, 0, 2, 524288, CPS2_WORD64},
    {"19x.17m", 0x2dfe18b5, 524288, 0, 4, 524288, CPS2_WORD64},
    {"19x.19m", 0xcbef9579, 524288, 0, 6, 524288, CPS2_WORD64},
    {"19x.14m", 0xe916967c, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"19x.16m", 0x6e75f3db, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"19x.18m", 0x2213e798, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"19x.20m", 0xab9d5b96, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_19xx_audiocpu[] = {
    {"19x.01", 0xef55195e, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"19x.01", 0xef55195e, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_19xx_qsound[] = {
    {"19x.11m", 0xd38beef3, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"19x.12m", 0xd47c96e2, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_19xx_key[] = {
    {"19xx.key", 0x6f5d6406, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_19xx[] = {
    {"maincpu", 4194304, 0, chips_19xx_maincpu, N(chips_19xx_maincpu)},
    {"gfx", 16777216, 0, chips_19xx_gfx, N(chips_19xx_gfx)},
    {"audiocpu", 327680, 0, chips_19xx_audiocpu, N(chips_19xx_audiocpu)},
    {"qsound", 4194304, 0, chips_19xx_qsound, N(chips_19xx_qsound)},
    {"key", 32, 0, chips_19xx_key, N(chips_19xx_key)},
};
static const Cps2Load chips_19xxu_maincpu[] = {
    {"19xu.03", 0x05955268, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"19xu.04", 0x3111ab7f, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"19xu.05", 0x38df4a63, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"19xu.06", 0x5c7e60d3, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"19x.07", 0x61c0296c, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_19xxu_gfx[] = {
    {"19x.13m", 0x427aeb18, 524288, 0, 0, 524288, CPS2_WORD64},
    {"19x.15m", 0x63bdbf54, 524288, 0, 2, 524288, CPS2_WORD64},
    {"19x.17m", 0x2dfe18b5, 524288, 0, 4, 524288, CPS2_WORD64},
    {"19x.19m", 0xcbef9579, 524288, 0, 6, 524288, CPS2_WORD64},
    {"19x.14m", 0xe916967c, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"19x.16m", 0x6e75f3db, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"19x.18m", 0x2213e798, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"19x.20m", 0xab9d5b96, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_19xxu_audiocpu[] = {
    {"19x.01", 0xef55195e, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"19x.01", 0xef55195e, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_19xxu_qsound[] = {
    {"19x.11m", 0xd38beef3, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"19x.12m", 0xd47c96e2, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_19xxu_key[] = {
    {"19xxu.key", 0x77e67ba1, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_19xxu[] = {
    {"maincpu", 4194304, 0, chips_19xxu_maincpu, N(chips_19xxu_maincpu)},
    {"gfx", 16777216, 0, chips_19xxu_gfx, N(chips_19xxu_gfx)},
    {"audiocpu", 327680, 0, chips_19xxu_audiocpu, N(chips_19xxu_audiocpu)},
    {"qsound", 4194304, 0, chips_19xxu_qsound, N(chips_19xxu_qsound)},
    {"key", 32, 0, chips_19xxu_key, N(chips_19xxu_key)},
};
static const Cps2Load chips_19xxa_maincpu[] = {
    {"09xa.03b", 0x2e994897, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"09xa.04b", 0x6364d001, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"09xa.05b", 0x00c1949b, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"09xa.06b", 0x363c1f6e, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"19xa.07", 0x61c0296c, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_19xxa_gfx[] = {
    {"19x.13m", 0x427aeb18, 524288, 0, 0, 524288, CPS2_WORD64},
    {"19x.15m", 0x63bdbf54, 524288, 0, 2, 524288, CPS2_WORD64},
    {"19x.17m", 0x2dfe18b5, 524288, 0, 4, 524288, CPS2_WORD64},
    {"19x.19m", 0xcbef9579, 524288, 0, 6, 524288, CPS2_WORD64},
    {"19x.14m", 0xe916967c, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"19x.16m", 0x6e75f3db, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"19x.18m", 0x2213e798, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"19x.20m", 0xab9d5b96, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_19xxa_audiocpu[] = {
    {"19x.01", 0xef55195e, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"19x.01", 0xef55195e, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_19xxa_qsound[] = {
    {"19x.11m", 0xd38beef3, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"19x.12m", 0xd47c96e2, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_19xxa_key[] = {
    {"19xxa.key", 0x2cd32eb9, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_19xxa[] = {
    {"maincpu", 4194304, 0, chips_19xxa_maincpu, N(chips_19xxa_maincpu)},
    {"gfx", 16777216, 0, chips_19xxa_gfx, N(chips_19xxa_gfx)},
    {"audiocpu", 327680, 0, chips_19xxa_audiocpu, N(chips_19xxa_audiocpu)},
    {"qsound", 4194304, 0, chips_19xxa_qsound, N(chips_19xxa_qsound)},
    {"key", 32, 0, chips_19xxa_key, N(chips_19xxa_key)},
};
static const Cps2Load chips_19xxar1_maincpu[] = {
    {"19xa.03", 0x0c20fd50, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"19xa.04", 0x1fc37508, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"19xa.05", 0x6c9cc4ed, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"19xa.06", 0xca5b9f76, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"19x.07", 0x61c0296c, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_19xxar1_gfx[] = {
    {"19x.13m", 0x427aeb18, 524288, 0, 0, 524288, CPS2_WORD64},
    {"19x.15m", 0x63bdbf54, 524288, 0, 2, 524288, CPS2_WORD64},
    {"19x.17m", 0x2dfe18b5, 524288, 0, 4, 524288, CPS2_WORD64},
    {"19x.19m", 0xcbef9579, 524288, 0, 6, 524288, CPS2_WORD64},
    {"19x.14m", 0xe916967c, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"19x.16m", 0x6e75f3db, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"19x.18m", 0x2213e798, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"19x.20m", 0xab9d5b96, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_19xxar1_audiocpu[] = {
    {"19x.01", 0xef55195e, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"19x.01", 0xef55195e, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_19xxar1_qsound[] = {
    {"19x.11m", 0xd38beef3, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"19x.12m", 0xd47c96e2, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_19xxar1_key[] = {
    {"19xxa.key", 0x2cd32eb9, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_19xxar1[] = {
    {"maincpu", 4194304, 0, chips_19xxar1_maincpu, N(chips_19xxar1_maincpu)},
    {"gfx", 16777216, 0, chips_19xxar1_gfx, N(chips_19xxar1_gfx)},
    {"audiocpu", 327680, 0, chips_19xxar1_audiocpu, N(chips_19xxar1_audiocpu)},
    {"qsound", 4194304, 0, chips_19xxar1_qsound, N(chips_19xxar1_qsound)},
    {"key", 32, 0, chips_19xxar1_key, N(chips_19xxar1_key)},
};
static const Cps2Load chips_19xxj_maincpu[] = {
    {"19xj-03b.6a", 0xbcad93dd, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"19xj-04b.7a", 0x931882a1, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"19xj-05b.8a", 0xe7eeddc4, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"19xj-06b.9a", 0xf27cd6b8, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"19xj-07.6d", 0x61c0296c, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_19xxj_gfx[] = {
    {"19x-69.4j", 0x427aeb18, 524288, 0, 0, 524288, CPS2_WORD64},
    {"19x-59.4d", 0x63bdbf54, 524288, 0, 2, 524288, CPS2_WORD64},
    {"19x-79.4m", 0x2dfe18b5, 524288, 0, 4, 524288, CPS2_WORD64},
    {"19x-89.4p", 0xcbef9579, 524288, 0, 6, 524288, CPS2_WORD64},
    {"19x-73.8j", 0x8e81f595, 524288, 0, 8388608, 524288, CPS2_WORD64},
    {"19x-74.9j", 0x6d7ad22e, 524288, 0, 10485760, 524288, CPS2_WORD64},
    {"19x-75.10j", 0xcb1a1b6a, 524288, 0, 12582912, 524288, CPS2_WORD64},
    {"19x-76.11j", 0x26fc2b08, 524288, 0, 14680064, 524288, CPS2_WORD64},
    {"19x-63.8d", 0x6f8b045e, 524288, 0, 8388610, 524288, CPS2_WORD64},
    {"19x-64.9d", 0xccd5725a, 524288, 0, 10485762, 524288, CPS2_WORD64},
    {"19x-65.10d", 0x6cf6db35, 524288, 0, 12582914, 524288, CPS2_WORD64},
    {"19x-66.11d", 0x16115dd3, 524288, 0, 14680066, 524288, CPS2_WORD64},
    {"19x-83.8m", 0xc11f88c1, 524288, 0, 8388612, 524288, CPS2_WORD64},
    {"19x-84.9m", 0x68cc9cd8, 524288, 0, 10485764, 524288, CPS2_WORD64},
    {"19x-85.10m", 0xf213666b, 524288, 0, 12582916, 524288, CPS2_WORD64},
    {"19x-86.11m", 0x574e0473, 524288, 0, 14680068, 524288, CPS2_WORD64},
    {"19x-93.8p", 0x9fad3c55, 524288, 0, 8388614, 524288, CPS2_WORD64},
    {"19x-94.9p", 0xe10e252c, 524288, 0, 10485766, 524288, CPS2_WORD64},
    {"19x-95.10p", 0x2b86fa67, 524288, 0, 12582918, 524288, CPS2_WORD64},
    {"19x-96.11p", 0xae6eb692, 524288, 0, 14680070, 524288, CPS2_WORD64},
};
static const Cps2Load chips_19xxj_audiocpu[] = {
    {"19x-01.1a", 0xef55195e, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"19x-01.1a", 0xef55195e, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_19xxj_qsound[] = {
    {"19x-51.6a", 0xe9cd7780, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"19x-52.7a", 0xb27b91a8, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"19x-53.8a", 0x2e563ee2, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"19x-54.9a", 0xf47c1f24, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"19x-55.10a", 0x0b1af6e0, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"19x-56.11a", 0xdfa8819f, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"19x-57.12a", 0x229ba777, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"19x-58.13a", 0xc7dceba4, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_19xxj_key[] = {
    {"19xxj.key", 0x9aafa71a, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_19xxj[] = {
    {"maincpu", 4194304, 0, chips_19xxj_maincpu, N(chips_19xxj_maincpu)},
    {"gfx", 16777216, 0, chips_19xxj_gfx, N(chips_19xxj_gfx)},
    {"audiocpu", 327680, 0, chips_19xxj_audiocpu, N(chips_19xxj_audiocpu)},
    {"qsound", 4194304, 0, chips_19xxj_qsound, N(chips_19xxj_qsound)},
    {"key", 32, 0, chips_19xxj_key, N(chips_19xxj_key)},
};
static const Cps2Load chips_19xxjr1_maincpu[] = {
    {"19xj.03a", 0xed08bdd1, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"19xj.04a", 0xfb8e3f29, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"19xj.05a", 0xaa508ac4, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"19xj.06a", 0xff2d785b, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"19x.07", 0x61c0296c, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_19xxjr1_gfx[] = {
    {"19x.13m", 0x427aeb18, 524288, 0, 0, 524288, CPS2_WORD64},
    {"19x.15m", 0x63bdbf54, 524288, 0, 2, 524288, CPS2_WORD64},
    {"19x.17m", 0x2dfe18b5, 524288, 0, 4, 524288, CPS2_WORD64},
    {"19x.19m", 0xcbef9579, 524288, 0, 6, 524288, CPS2_WORD64},
    {"19x.14m", 0xe916967c, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"19x.16m", 0x6e75f3db, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"19x.18m", 0x2213e798, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"19x.20m", 0xab9d5b96, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_19xxjr1_audiocpu[] = {
    {"19x.01", 0xef55195e, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"19x.01", 0xef55195e, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_19xxjr1_qsound[] = {
    {"19x.11m", 0xd38beef3, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"19x.12m", 0xd47c96e2, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_19xxjr1_key[] = {
    {"19xxj.key", 0x9aafa71a, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_19xxjr1[] = {
    {"maincpu", 4194304, 0, chips_19xxjr1_maincpu, N(chips_19xxjr1_maincpu)},
    {"gfx", 16777216, 0, chips_19xxjr1_gfx, N(chips_19xxjr1_gfx)},
    {"audiocpu", 327680, 0, chips_19xxjr1_audiocpu, N(chips_19xxjr1_audiocpu)},
    {"qsound", 4194304, 0, chips_19xxjr1_qsound, N(chips_19xxjr1_qsound)},
    {"key", 32, 0, chips_19xxjr1_key, N(chips_19xxjr1_key)},
};
static const Cps2Load chips_19xxjr2_maincpu[] = {
    {"19xj.03", 0x26a381ed, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"19xj.04", 0x30100cca, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"19xj.05", 0xde67e938, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"19xj.06", 0x39f9a409, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"19x.07", 0x61c0296c, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_19xxjr2_gfx[] = {
    {"19x.13m", 0x427aeb18, 524288, 0, 0, 524288, CPS2_WORD64},
    {"19x.15m", 0x63bdbf54, 524288, 0, 2, 524288, CPS2_WORD64},
    {"19x.17m", 0x2dfe18b5, 524288, 0, 4, 524288, CPS2_WORD64},
    {"19x.19m", 0xcbef9579, 524288, 0, 6, 524288, CPS2_WORD64},
    {"19x.14m", 0xe916967c, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"19x.16m", 0x6e75f3db, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"19x.18m", 0x2213e798, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"19x.20m", 0xab9d5b96, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_19xxjr2_audiocpu[] = {
    {"19x.01", 0xef55195e, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"19x.01", 0xef55195e, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_19xxjr2_qsound[] = {
    {"19x.11m", 0xd38beef3, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"19x.12m", 0xd47c96e2, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_19xxjr2_key[] = {
    {"19xxj.key", 0x9aafa71a, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_19xxjr2[] = {
    {"maincpu", 4194304, 0, chips_19xxjr2_maincpu, N(chips_19xxjr2_maincpu)},
    {"gfx", 16777216, 0, chips_19xxjr2_gfx, N(chips_19xxjr2_gfx)},
    {"audiocpu", 327680, 0, chips_19xxjr2_audiocpu, N(chips_19xxjr2_audiocpu)},
    {"qsound", 4194304, 0, chips_19xxjr2_qsound, N(chips_19xxjr2_qsound)},
    {"key", 32, 0, chips_19xxjr2_key, N(chips_19xxjr2_key)},
};
static const Cps2Load chips_19xxh_maincpu[] = {
    {"19xh.03a", 0x357be2ac, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"19xh.04a", 0xbb13ea3b, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"19xh.05a", 0xcbd76601, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"19xh.06a", 0xb362de8b, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"19x.07", 0x61c0296c, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_19xxh_gfx[] = {
    {"19x.13m", 0x427aeb18, 524288, 0, 0, 524288, CPS2_WORD64},
    {"19x.15m", 0x63bdbf54, 524288, 0, 2, 524288, CPS2_WORD64},
    {"19x.17m", 0x2dfe18b5, 524288, 0, 4, 524288, CPS2_WORD64},
    {"19x.19m", 0xcbef9579, 524288, 0, 6, 524288, CPS2_WORD64},
    {"19x.14m", 0xe916967c, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"19x.16m", 0x6e75f3db, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"19x.18m", 0x2213e798, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"19x.20m", 0xab9d5b96, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_19xxh_audiocpu[] = {
    {"19x.01", 0xef55195e, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"19x.01", 0xef55195e, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_19xxh_qsound[] = {
    {"19x.11m", 0xd38beef3, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"19x.12m", 0xd47c96e2, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_19xxh_key[] = {
    {"19xxh.key", 0x215cf208, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_19xxh[] = {
    {"maincpu", 4194304, 0, chips_19xxh_maincpu, N(chips_19xxh_maincpu)},
    {"gfx", 16777216, 0, chips_19xxh_gfx, N(chips_19xxh_gfx)},
    {"audiocpu", 327680, 0, chips_19xxh_audiocpu, N(chips_19xxh_audiocpu)},
    {"qsound", 4194304, 0, chips_19xxh_qsound, N(chips_19xxh_qsound)},
    {"key", 32, 0, chips_19xxh_key, N(chips_19xxh_key)},
};
static const Cps2Load chips_19xxb_maincpu[] = {
    {"19xb.03a", 0x341bdf4a, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"19xb.04a", 0xdff8069e, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"19xb.05a", 0xa47a92a8, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"19xb.06a", 0xc52df10d, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"19x.07", 0x61c0296c, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_19xxb_gfx[] = {
    {"19x.13m", 0x427aeb18, 524288, 0, 0, 524288, CPS2_WORD64},
    {"19x.15m", 0x63bdbf54, 524288, 0, 2, 524288, CPS2_WORD64},
    {"19x.17m", 0x2dfe18b5, 524288, 0, 4, 524288, CPS2_WORD64},
    {"19x.19m", 0xcbef9579, 524288, 0, 6, 524288, CPS2_WORD64},
    {"19x.14m", 0xe916967c, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"19x.16m", 0x6e75f3db, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"19x.18m", 0x2213e798, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"19x.20m", 0xab9d5b96, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_19xxb_audiocpu[] = {
    {"19x.01", 0xef55195e, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"19x.01", 0xef55195e, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_19xxb_qsound[] = {
    {"19x.11m", 0xd38beef3, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"19x.12m", 0xd47c96e2, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_19xxb_key[] = {
    {"19xxb.key", 0x4200e334, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_19xxb[] = {
    {"maincpu", 4194304, 0, chips_19xxb_maincpu, N(chips_19xxb_maincpu)},
    {"gfx", 16777216, 0, chips_19xxb_gfx, N(chips_19xxb_gfx)},
    {"audiocpu", 327680, 0, chips_19xxb_audiocpu, N(chips_19xxb_audiocpu)},
    {"qsound", 4194304, 0, chips_19xxb_qsound, N(chips_19xxb_qsound)},
    {"key", 32, 0, chips_19xxb_key, N(chips_19xxb_key)},
};
static const Cps2Load chips_ddsom_maincpu[] = {
    {"dd2e.03e", 0x449361af, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dd2e.04e", 0x5b7052b6, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dd2e.05e", 0x788d5f60, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dd2e.06e", 0xe0807e1e, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dd2e.07", 0xbb777a02, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"dd2e.08", 0x30970890, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"dd2e.09", 0x99e2194d, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"dd2e.10", 0xe198805e, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddsom_gfx[] = {
    {"dd2.13m", 0xa46b4e6e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"dd2.15m", 0xd5fc50fc, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"dd2.17m", 0x837c0867, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"dd2.19m", 0xbb0ec21c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"dd2.14m", 0x6d824ce2, 2097152, 0, 16777216, 2097152, CPS2_WORD64},
    {"dd2.16m", 0x79682ae5, 2097152, 0, 16777218, 2097152, CPS2_WORD64},
    {"dd2.18m", 0xacddd149, 2097152, 0, 16777220, 2097152, CPS2_WORD64},
    {"dd2.20m", 0x117fb0c0, 2097152, 0, 16777222, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_ddsom_audiocpu[] = {
    {"dd2.01", 0x99d657e5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dd2.01", 0x99d657e5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"dd2.02", 0x117a3824, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ddsom_qsound[] = {
    {"dd2.11m", 0x98d0c325, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dd2.12m", 0x5ea2e7fa, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddsom_key[] = {
    {"ddsom.key", 0x541e425d, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddsom[] = {
    {"maincpu", 4194304, 0, chips_ddsom_maincpu, N(chips_ddsom_maincpu)},
    {"gfx", 25165824, 0, chips_ddsom_gfx, N(chips_ddsom_gfx)},
    {"audiocpu", 327680, 0, chips_ddsom_audiocpu, N(chips_ddsom_audiocpu)},
    {"qsound", 4194304, 0, chips_ddsom_qsound, N(chips_ddsom_qsound)},
    {"key", 32, 0, chips_ddsom_key, N(chips_ddsom_key)},
};
static const Cps2Load chips_ddsomr1_maincpu[] = {
    {"dd2e.03d", 0x6c084ab5, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dd2e.04d", 0x9b94a947, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dd2e.05d", 0x5d6a63c6, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dd2e.06d", 0x31bde8ee, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dd2e.07", 0xbb777a02, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"dd2e.08", 0x30970890, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"dd2e.09", 0x99e2194d, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"dd2e.10", 0xe198805e, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomr1_gfx[] = {
    {"dd2.13m", 0xa46b4e6e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"dd2.15m", 0xd5fc50fc, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"dd2.17m", 0x837c0867, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"dd2.19m", 0xbb0ec21c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"dd2.14m", 0x6d824ce2, 2097152, 0, 16777216, 2097152, CPS2_WORD64},
    {"dd2.16m", 0x79682ae5, 2097152, 0, 16777218, 2097152, CPS2_WORD64},
    {"dd2.18m", 0xacddd149, 2097152, 0, 16777220, 2097152, CPS2_WORD64},
    {"dd2.20m", 0x117fb0c0, 2097152, 0, 16777222, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_ddsomr1_audiocpu[] = {
    {"dd2.01", 0x99d657e5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dd2.01", 0x99d657e5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"dd2.02", 0x117a3824, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ddsomr1_qsound[] = {
    {"dd2.11m", 0x98d0c325, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dd2.12m", 0x5ea2e7fa, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomr1_key[] = {
    {"ddsom.key", 0x541e425d, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddsomr1[] = {
    {"maincpu", 4194304, 0, chips_ddsomr1_maincpu, N(chips_ddsomr1_maincpu)},
    {"gfx", 25165824, 0, chips_ddsomr1_gfx, N(chips_ddsomr1_gfx)},
    {"audiocpu", 327680, 0, chips_ddsomr1_audiocpu, N(chips_ddsomr1_audiocpu)},
    {"qsound", 4194304, 0, chips_ddsomr1_qsound, N(chips_ddsomr1_qsound)},
    {"key", 32, 0, chips_ddsomr1_key, N(chips_ddsomr1_key)},
};
static const Cps2Load chips_ddsomr2_maincpu[] = {
    {"dd2e.03b", 0xcd2deb66, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dd2e.04b", 0xbfee43cc, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dd2e.05b", 0x049ab19d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dd2e.06b", 0x3994fb8b, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dd2e.07", 0xbb777a02, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"dd2e.08", 0x30970890, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"dd2e.09", 0x99e2194d, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"dd2e.10", 0xe198805e, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomr2_gfx[] = {
    {"dd2.13m", 0xa46b4e6e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"dd2.15m", 0xd5fc50fc, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"dd2.17m", 0x837c0867, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"dd2.19m", 0xbb0ec21c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"dd2.14m", 0x6d824ce2, 2097152, 0, 16777216, 2097152, CPS2_WORD64},
    {"dd2.16m", 0x79682ae5, 2097152, 0, 16777218, 2097152, CPS2_WORD64},
    {"dd2.18m", 0xacddd149, 2097152, 0, 16777220, 2097152, CPS2_WORD64},
    {"dd2.20m", 0x117fb0c0, 2097152, 0, 16777222, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_ddsomr2_audiocpu[] = {
    {"dd2.01", 0x99d657e5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dd2.01", 0x99d657e5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"dd2.02", 0x117a3824, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ddsomr2_qsound[] = {
    {"dd2.11m", 0x98d0c325, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dd2.12m", 0x5ea2e7fa, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomr2_key[] = {
    {"ddsom.key", 0x541e425d, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddsomr2[] = {
    {"maincpu", 4194304, 0, chips_ddsomr2_maincpu, N(chips_ddsomr2_maincpu)},
    {"gfx", 25165824, 0, chips_ddsomr2_gfx, N(chips_ddsomr2_gfx)},
    {"audiocpu", 327680, 0, chips_ddsomr2_audiocpu, N(chips_ddsomr2_audiocpu)},
    {"qsound", 4194304, 0, chips_ddsomr2_qsound, N(chips_ddsomr2_qsound)},
    {"key", 32, 0, chips_ddsomr2_key, N(chips_ddsomr2_key)},
};
static const Cps2Load chips_ddsomr3_maincpu[] = {
    {"dd2e.03a", 0x6de67678, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dd2e.04a", 0x0e45739a, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dd2e.05a", 0x3dce8025, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dd2e.06a", 0x51bafbef, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dd2e.07", 0xbb777a02, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"dd2e.08", 0x30970890, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"dd2e.09", 0x99e2194d, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"dd2e.10", 0xe198805e, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomr3_gfx[] = {
    {"dd2.13m", 0xa46b4e6e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"dd2.15m", 0xd5fc50fc, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"dd2.17m", 0x837c0867, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"dd2.19m", 0xbb0ec21c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"dd2.14m", 0x6d824ce2, 2097152, 0, 16777216, 2097152, CPS2_WORD64},
    {"dd2.16m", 0x79682ae5, 2097152, 0, 16777218, 2097152, CPS2_WORD64},
    {"dd2.18m", 0xacddd149, 2097152, 0, 16777220, 2097152, CPS2_WORD64},
    {"dd2.20m", 0x117fb0c0, 2097152, 0, 16777222, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_ddsomr3_audiocpu[] = {
    {"dd2.01", 0x99d657e5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dd2.01", 0x99d657e5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"dd2.02", 0x117a3824, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ddsomr3_qsound[] = {
    {"dd2.11m", 0x98d0c325, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dd2.12m", 0x5ea2e7fa, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomr3_key[] = {
    {"ddsom.key", 0x541e425d, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddsomr3[] = {
    {"maincpu", 4194304, 0, chips_ddsomr3_maincpu, N(chips_ddsomr3_maincpu)},
    {"gfx", 25165824, 0, chips_ddsomr3_gfx, N(chips_ddsomr3_gfx)},
    {"audiocpu", 327680, 0, chips_ddsomr3_audiocpu, N(chips_ddsomr3_audiocpu)},
    {"qsound", 4194304, 0, chips_ddsomr3_qsound, N(chips_ddsomr3_qsound)},
    {"key", 32, 0, chips_ddsomr3_key, N(chips_ddsomr3_key)},
};
static const Cps2Load chips_ddsomu_maincpu[] = {
    {"dd2u.03g", 0xfb089b39, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dd2u.04g", 0xcd432b73, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dd2.05g", 0x5eb1991c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dd2.06g", 0xc26b5e55, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dd2.07", 0x909a0b8b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"dd2.08", 0xe53c4d01, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"dd2.09", 0x5f86279f, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"dd2.10", 0xad954c26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomu_gfx[] = {
    {"dd2.13m", 0xa46b4e6e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"dd2.15m", 0xd5fc50fc, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"dd2.17m", 0x837c0867, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"dd2.19m", 0xbb0ec21c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"dd2.14m", 0x6d824ce2, 2097152, 0, 16777216, 2097152, CPS2_WORD64},
    {"dd2.16m", 0x79682ae5, 2097152, 0, 16777218, 2097152, CPS2_WORD64},
    {"dd2.18m", 0xacddd149, 2097152, 0, 16777220, 2097152, CPS2_WORD64},
    {"dd2.20m", 0x117fb0c0, 2097152, 0, 16777222, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_ddsomu_audiocpu[] = {
    {"dd2.01", 0x99d657e5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dd2.01", 0x99d657e5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"dd2.02", 0x117a3824, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ddsomu_qsound[] = {
    {"dd2.11m", 0x98d0c325, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dd2.12m", 0x5ea2e7fa, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomu_key[] = {
    {"ddsomu.key", 0x09ae0f7c, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddsomu[] = {
    {"maincpu", 4194304, 0, chips_ddsomu_maincpu, N(chips_ddsomu_maincpu)},
    {"gfx", 25165824, 0, chips_ddsomu_gfx, N(chips_ddsomu_gfx)},
    {"audiocpu", 327680, 0, chips_ddsomu_audiocpu, N(chips_ddsomu_audiocpu)},
    {"qsound", 4194304, 0, chips_ddsomu_qsound, N(chips_ddsomu_qsound)},
    {"key", 32, 0, chips_ddsomu_key, N(chips_ddsomu_key)},
};
static const Cps2Load chips_ddsomur1_maincpu[] = {
    {"dd2u.03d", 0x0f700d84, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dd2u.04d", 0xb99eb254, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dd2.05d", 0xb23061f3, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dd2.06d", 0x8bf1d8ce, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dd2.07", 0x909a0b8b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"dd2.08", 0xe53c4d01, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"dd2.09", 0x5f86279f, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"dd2.10", 0xad954c26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomur1_gfx[] = {
    {"dd2.13m", 0xa46b4e6e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"dd2.15m", 0xd5fc50fc, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"dd2.17m", 0x837c0867, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"dd2.19m", 0xbb0ec21c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"dd2.14m", 0x6d824ce2, 2097152, 0, 16777216, 2097152, CPS2_WORD64},
    {"dd2.16m", 0x79682ae5, 2097152, 0, 16777218, 2097152, CPS2_WORD64},
    {"dd2.18m", 0xacddd149, 2097152, 0, 16777220, 2097152, CPS2_WORD64},
    {"dd2.20m", 0x117fb0c0, 2097152, 0, 16777222, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_ddsomur1_audiocpu[] = {
    {"dd2.01", 0x99d657e5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dd2.01", 0x99d657e5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"dd2.02", 0x117a3824, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ddsomur1_qsound[] = {
    {"dd2.11m", 0x98d0c325, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dd2.12m", 0x5ea2e7fa, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomur1_key[] = {
    {"ddsomu.key", 0x09ae0f7c, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddsomur1[] = {
    {"maincpu", 4194304, 0, chips_ddsomur1_maincpu, N(chips_ddsomur1_maincpu)},
    {"gfx", 25165824, 0, chips_ddsomur1_gfx, N(chips_ddsomur1_gfx)},
    {"audiocpu", 327680, 0, chips_ddsomur1_audiocpu, N(chips_ddsomur1_audiocpu)},
    {"qsound", 4194304, 0, chips_ddsomur1_qsound, N(chips_ddsomur1_qsound)},
    {"key", 32, 0, chips_ddsomur1_key, N(chips_ddsomur1_key)},
};
static const Cps2Load chips_ddsomj_maincpu[] = {
    {"dd2j.03g", 0xe6c8c985, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dd2j.04g", 0x8386c0bd, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dd2.05g", 0x5eb1991c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dd2.06g", 0xc26b5e55, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dd2.07", 0x909a0b8b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"dd2.08", 0xe53c4d01, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"dd2.09", 0x5f86279f, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"dd2.10", 0xad954c26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomj_gfx[] = {
    {"dd2.13m", 0xa46b4e6e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"dd2.15m", 0xd5fc50fc, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"dd2.17m", 0x837c0867, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"dd2.19m", 0xbb0ec21c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"dd2.14m", 0x6d824ce2, 2097152, 0, 16777216, 2097152, CPS2_WORD64},
    {"dd2.16m", 0x79682ae5, 2097152, 0, 16777218, 2097152, CPS2_WORD64},
    {"dd2.18m", 0xacddd149, 2097152, 0, 16777220, 2097152, CPS2_WORD64},
    {"dd2.20m", 0x117fb0c0, 2097152, 0, 16777222, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_ddsomj_audiocpu[] = {
    {"dd2.01", 0x99d657e5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dd2.01", 0x99d657e5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"dd2.02", 0x117a3824, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ddsomj_qsound[] = {
    {"dd2.11m", 0x98d0c325, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dd2.12m", 0x5ea2e7fa, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomj_key[] = {
    {"ddsomj.key", 0xd8dadb22, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddsomj[] = {
    {"maincpu", 4194304, 0, chips_ddsomj_maincpu, N(chips_ddsomj_maincpu)},
    {"gfx", 25165824, 0, chips_ddsomj_gfx, N(chips_ddsomj_gfx)},
    {"audiocpu", 327680, 0, chips_ddsomj_audiocpu, N(chips_ddsomj_audiocpu)},
    {"qsound", 4194304, 0, chips_ddsomj_qsound, N(chips_ddsomj_qsound)},
    {"key", 32, 0, chips_ddsomj_key, N(chips_ddsomj_key)},
};
static const Cps2Load chips_ddsomjr1_maincpu[] = {
    {"dd2j.03e", 0xb2fd4a24, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dd2j.04e", 0x3a68c310, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dd2.05e", 0xaa56f42f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dd2.06e", 0x2f8cd040, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dd2.07", 0x909a0b8b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"dd2.08", 0xe53c4d01, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"dd2.09", 0x5f86279f, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"dd2.10", 0xad954c26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomjr1_gfx[] = {
    {"dd2.13m", 0xa46b4e6e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"dd2.15m", 0xd5fc50fc, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"dd2.17m", 0x837c0867, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"dd2.19m", 0xbb0ec21c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"dd2.14m", 0x6d824ce2, 2097152, 0, 16777216, 2097152, CPS2_WORD64},
    {"dd2.16m", 0x79682ae5, 2097152, 0, 16777218, 2097152, CPS2_WORD64},
    {"dd2.18m", 0xacddd149, 2097152, 0, 16777220, 2097152, CPS2_WORD64},
    {"dd2.20m", 0x117fb0c0, 2097152, 0, 16777222, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_ddsomjr1_audiocpu[] = {
    {"dd2.01", 0x99d657e5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dd2.01", 0x99d657e5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"dd2.02", 0x117a3824, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ddsomjr1_qsound[] = {
    {"dd2.11m", 0x98d0c325, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dd2.12m", 0x5ea2e7fa, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomjr1_key[] = {
    {"ddsomj.key", 0xd8dadb22, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddsomjr1[] = {
    {"maincpu", 4194304, 0, chips_ddsomjr1_maincpu, N(chips_ddsomjr1_maincpu)},
    {"gfx", 25165824, 0, chips_ddsomjr1_gfx, N(chips_ddsomjr1_gfx)},
    {"audiocpu", 327680, 0, chips_ddsomjr1_audiocpu, N(chips_ddsomjr1_audiocpu)},
    {"qsound", 4194304, 0, chips_ddsomjr1_qsound, N(chips_ddsomjr1_qsound)},
    {"key", 32, 0, chips_ddsomjr1_key, N(chips_ddsomjr1_key)},
};
static const Cps2Load chips_ddsomjr2_maincpu[] = {
    {"dd2j.03b", 0x965d74e5, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dd2j.04b", 0x958eb8f3, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dd2.05b", 0xd38571ca, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dd2.06b", 0x6d5a3bbb, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dd2.07", 0x909a0b8b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"dd2.08", 0xe53c4d01, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"dd2.09", 0x5f86279f, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"dd2.10", 0xad954c26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomjr2_gfx[] = {
    {"dd2.13m", 0xa46b4e6e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"dd2.15m", 0xd5fc50fc, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"dd2.17m", 0x837c0867, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"dd2.19m", 0xbb0ec21c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"dd2.14m", 0x6d824ce2, 2097152, 0, 16777216, 2097152, CPS2_WORD64},
    {"dd2.16m", 0x79682ae5, 2097152, 0, 16777218, 2097152, CPS2_WORD64},
    {"dd2.18m", 0xacddd149, 2097152, 0, 16777220, 2097152, CPS2_WORD64},
    {"dd2.20m", 0x117fb0c0, 2097152, 0, 16777222, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_ddsomjr2_audiocpu[] = {
    {"dd2.01", 0x99d657e5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dd2.01", 0x99d657e5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"dd2.02", 0x117a3824, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ddsomjr2_qsound[] = {
    {"dd2.11m", 0x98d0c325, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dd2.12m", 0x5ea2e7fa, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomjr2_key[] = {
    {"ddsomj.key", 0xd8dadb22, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddsomjr2[] = {
    {"maincpu", 4194304, 0, chips_ddsomjr2_maincpu, N(chips_ddsomjr2_maincpu)},
    {"gfx", 25165824, 0, chips_ddsomjr2_gfx, N(chips_ddsomjr2_gfx)},
    {"audiocpu", 327680, 0, chips_ddsomjr2_audiocpu, N(chips_ddsomjr2_audiocpu)},
    {"qsound", 4194304, 0, chips_ddsomjr2_qsound, N(chips_ddsomjr2_qsound)},
    {"key", 32, 0, chips_ddsomjr2_key, N(chips_ddsomjr2_key)},
};
static const Cps2Load chips_ddsoma_maincpu[] = {
    {"dd2a.03g", 0x0b4fec22, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dd2a.04g", 0x055b7019, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dd2.05g", 0x5eb1991c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dd2.06g", 0xc26b5e55, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dd2.07", 0x909a0b8b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"dd2.08", 0xe53c4d01, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"dd2.09", 0x5f86279f, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"dd2.10", 0xad954c26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddsoma_gfx[] = {
    {"dd2.13m", 0xa46b4e6e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"dd2.15m", 0xd5fc50fc, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"dd2.17m", 0x837c0867, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"dd2.19m", 0xbb0ec21c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"dd2.14m", 0x6d824ce2, 2097152, 0, 16777216, 2097152, CPS2_WORD64},
    {"dd2.16m", 0x79682ae5, 2097152, 0, 16777218, 2097152, CPS2_WORD64},
    {"dd2.18m", 0xacddd149, 2097152, 0, 16777220, 2097152, CPS2_WORD64},
    {"dd2.20m", 0x117fb0c0, 2097152, 0, 16777222, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_ddsoma_audiocpu[] = {
    {"dd2.01", 0x99d657e5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dd2.01", 0x99d657e5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"dd2.02", 0x117a3824, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ddsoma_qsound[] = {
    {"dd2.11m", 0x98d0c325, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dd2.12m", 0x5ea2e7fa, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddsoma_key[] = {
    {"ddsoma.key", 0x8c3cc560, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddsoma[] = {
    {"maincpu", 4194304, 0, chips_ddsoma_maincpu, N(chips_ddsoma_maincpu)},
    {"gfx", 25165824, 0, chips_ddsoma_gfx, N(chips_ddsoma_gfx)},
    {"audiocpu", 327680, 0, chips_ddsoma_audiocpu, N(chips_ddsoma_audiocpu)},
    {"qsound", 4194304, 0, chips_ddsoma_qsound, N(chips_ddsoma_qsound)},
    {"key", 32, 0, chips_ddsoma_key, N(chips_ddsoma_key)},
};
static const Cps2Load chips_ddsomar1_maincpu[] = {
    {"dd2a.03c", 0x17162039, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dd2a.04c", 0x950bec38, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dd2a.05c", 0xfa298eba, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dd2a.06c", 0x28f75b35, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dd2.07", 0x909a0b8b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"dd2.08", 0xe53c4d01, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"dd2.09", 0x5f86279f, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"dd2.10", 0xad954c26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomar1_gfx[] = {
    {"dd2.13m", 0xa46b4e6e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"dd2.15m", 0xd5fc50fc, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"dd2.17m", 0x837c0867, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"dd2.19m", 0xbb0ec21c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"dd2.14m", 0x6d824ce2, 2097152, 0, 16777216, 2097152, CPS2_WORD64},
    {"dd2.16m", 0x79682ae5, 2097152, 0, 16777218, 2097152, CPS2_WORD64},
    {"dd2.18m", 0xacddd149, 2097152, 0, 16777220, 2097152, CPS2_WORD64},
    {"dd2.20m", 0x117fb0c0, 2097152, 0, 16777222, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_ddsomar1_audiocpu[] = {
    {"dd2.01", 0x99d657e5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dd2.01", 0x99d657e5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"dd2.02", 0x117a3824, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ddsomar1_qsound[] = {
    {"dd2.11m", 0x98d0c325, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dd2.12m", 0x5ea2e7fa, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomar1_key[] = {
    {"ddsoma.key", 0x8c3cc560, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddsomar1[] = {
    {"maincpu", 4194304, 0, chips_ddsomar1_maincpu, N(chips_ddsomar1_maincpu)},
    {"gfx", 25165824, 0, chips_ddsomar1_gfx, N(chips_ddsomar1_gfx)},
    {"audiocpu", 327680, 0, chips_ddsomar1_audiocpu, N(chips_ddsomar1_audiocpu)},
    {"qsound", 4194304, 0, chips_ddsomar1_qsound, N(chips_ddsomar1_qsound)},
    {"key", 32, 0, chips_ddsomar1_key, N(chips_ddsomar1_key)},
};
static const Cps2Load chips_ddsomh_maincpu[] = {
    {"dd2h.03a", 0xe472c9f3, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dd2h.04a", 0x315a7706, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dd2h.05a", 0x9b2534eb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dd2h.06a", 0x3b21ba59, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dd2h.07a", 0xfce2558d, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"dd2e.08", 0x30970890, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"dd2e.09", 0x99e2194d, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"dd2e.10", 0xe198805e, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomh_gfx[] = {
    {"dd2.13m", 0xa46b4e6e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"dd2.15m", 0xd5fc50fc, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"dd2.17m", 0x837c0867, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"dd2.19m", 0xbb0ec21c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"dd2.14m", 0x6d824ce2, 2097152, 0, 16777216, 2097152, CPS2_WORD64},
    {"dd2.16m", 0x79682ae5, 2097152, 0, 16777218, 2097152, CPS2_WORD64},
    {"dd2.18m", 0xacddd149, 2097152, 0, 16777220, 2097152, CPS2_WORD64},
    {"dd2.20m", 0x117fb0c0, 2097152, 0, 16777222, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_ddsomh_audiocpu[] = {
    {"dd2.01", 0x99d657e5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dd2.01", 0x99d657e5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"dd2.02", 0x117a3824, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ddsomh_qsound[] = {
    {"dd2.11m", 0x98d0c325, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dd2.12m", 0x5ea2e7fa, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomh_key[] = {
    {"ddsomh.key", 0xcaf6b540, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddsomh[] = {
    {"maincpu", 4194304, 0, chips_ddsomh_maincpu, N(chips_ddsomh_maincpu)},
    {"gfx", 25165824, 0, chips_ddsomh_gfx, N(chips_ddsomh_gfx)},
    {"audiocpu", 327680, 0, chips_ddsomh_audiocpu, N(chips_ddsomh_audiocpu)},
    {"qsound", 4194304, 0, chips_ddsomh_qsound, N(chips_ddsomh_qsound)},
    {"key", 32, 0, chips_ddsomh_key, N(chips_ddsomh_key)},
};
static const Cps2Load chips_ddsomb_maincpu[] = {
    {"dd2b.03a", 0xe8ce7fbb, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dd2b.04a", 0x6b679664, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dd2b.05a", 0x9b2534eb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dd2b.06a", 0x3b21ba59, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dd2b.07", 0xfce2558d, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"dd2e.08", 0x30970890, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"dd2e.09", 0x99e2194d, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"dd2e.10", 0xe198805e, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomb_gfx[] = {
    {"dd2.13m", 0xa46b4e6e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"dd2.15m", 0xd5fc50fc, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"dd2.17m", 0x837c0867, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"dd2.19m", 0xbb0ec21c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"dd2.14m", 0x6d824ce2, 2097152, 0, 16777216, 2097152, CPS2_WORD64},
    {"dd2.16m", 0x79682ae5, 2097152, 0, 16777218, 2097152, CPS2_WORD64},
    {"dd2.18m", 0xacddd149, 2097152, 0, 16777220, 2097152, CPS2_WORD64},
    {"dd2.20m", 0x117fb0c0, 2097152, 0, 16777222, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_ddsomb_audiocpu[] = {
    {"dd2.01", 0x99d657e5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dd2.01", 0x99d657e5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"dd2.02", 0x117a3824, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ddsomb_qsound[] = {
    {"dd2.11m", 0x98d0c325, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dd2.12m", 0x5ea2e7fa, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomb_key[] = {
    {"ddsomb.key", 0x00b4cc49, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddsomb[] = {
    {"maincpu", 4194304, 0, chips_ddsomb_maincpu, N(chips_ddsomb_maincpu)},
    {"gfx", 25165824, 0, chips_ddsomb_gfx, N(chips_ddsomb_gfx)},
    {"audiocpu", 327680, 0, chips_ddsomb_audiocpu, N(chips_ddsomb_audiocpu)},
    {"qsound", 4194304, 0, chips_ddsomb_qsound, N(chips_ddsomb_qsound)},
    {"key", 32, 0, chips_ddsomb_key, N(chips_ddsomb_key)},
};
static const Cps2Load chips_sfa2_maincpu[] = {
    {"sz2e.03", 0x1061e6bb, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz2e.04", 0x22d17b26, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz2.05", 0x4b442a7c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz2.06", 0x5b1d49c0, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz2.07", 0x8e184246, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz2.08", 0x0fe8585d, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfa2_gfx[] = {
    {"sz2.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz2.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz2.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz2.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz2.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sz2.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sz2.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sz2.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfa2_audiocpu[] = {
    {"sz2.01a", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz2.01a", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz2.02a", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfa2_qsound[] = {
    {"sz2.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sz2.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfa2_key[] = {
    {"sfa2.key", 0x1578dcb0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfa2[] = {
    {"maincpu", 4194304, 0, chips_sfa2_maincpu, N(chips_sfa2_maincpu)},
    {"gfx", 20971520, 0, chips_sfa2_gfx, N(chips_sfa2_gfx)},
    {"audiocpu", 327680, 0, chips_sfa2_audiocpu, N(chips_sfa2_audiocpu)},
    {"qsound", 4194304, 0, chips_sfa2_qsound, N(chips_sfa2_qsound)},
    {"key", 32, 0, chips_sfa2_key, N(chips_sfa2_key)},
};
static const Cps2Load chips_sfa2u_maincpu[] = {
    {"sz2u.03a", 0xd03e504f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz2u.04a", 0xfae0e9c3, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz2u.05a", 0xd02dd758, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz2u.06", 0xc5c8eb63, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz2u.07", 0x5de01cc5, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz2u.08", 0xbea11d56, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfa2u_gfx[] = {
    {"sz2.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz2.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz2.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz2.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz2.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sz2.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sz2.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sz2.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfa2u_audiocpu[] = {
    {"sz2.01a", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz2.01a", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz2.02a", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfa2u_qsound[] = {
    {"sz2.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sz2.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfa2u_key[] = {
    {"sfa2u.key", 0x4a8d91ef, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfa2u[] = {
    {"maincpu", 4194304, 0, chips_sfa2u_maincpu, N(chips_sfa2u_maincpu)},
    {"gfx", 20971520, 0, chips_sfa2u_gfx, N(chips_sfa2u_gfx)},
    {"audiocpu", 327680, 0, chips_sfa2u_audiocpu, N(chips_sfa2u_audiocpu)},
    {"qsound", 4194304, 0, chips_sfa2u_qsound, N(chips_sfa2u_qsound)},
    {"key", 32, 0, chips_sfa2u_key, N(chips_sfa2u_key)},
};
static const Cps2Load chips_sfa2ur1_maincpu[] = {
    {"sz2u.03", 0x84a09006, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz2u.04", 0xac46e5ed, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz2u.05", 0x6c0c79d3, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz2u.06", 0xc5c8eb63, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz2u.07", 0x5de01cc5, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz2u.08", 0xbea11d56, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfa2ur1_gfx[] = {
    {"sz2.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz2.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz2.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz2.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz2.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sz2.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sz2.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sz2.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfa2ur1_audiocpu[] = {
    {"sz2.01a", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz2.01a", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz2.02a", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfa2ur1_qsound[] = {
    {"sz2.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sz2.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfa2ur1_key[] = {
    {"sfa2u.key", 0x4a8d91ef, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfa2ur1[] = {
    {"maincpu", 4194304, 0, chips_sfa2ur1_maincpu, N(chips_sfa2ur1_maincpu)},
    {"gfx", 20971520, 0, chips_sfa2ur1_gfx, N(chips_sfa2ur1_gfx)},
    {"audiocpu", 327680, 0, chips_sfa2ur1_audiocpu, N(chips_sfa2ur1_audiocpu)},
    {"qsound", 4194304, 0, chips_sfa2ur1_qsound, N(chips_sfa2ur1_qsound)},
    {"key", 32, 0, chips_sfa2ur1_key, N(chips_sfa2ur1_key)},
};
static const Cps2Load chips_sfz2j_maincpu[] = {
    {"sz2j.03b", 0x3e1e2e85, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz2j.04b", 0xf53d6c45, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz2j.05b", 0xdd224156, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz2j.06b", 0xa45a75a6, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz2j.07b", 0x6352f038, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz2j.08b", 0x92b66e01, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2j_gfx[] = {
    {"sz2.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz2.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz2.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz2.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz2.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sz2.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sz2.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sz2.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfz2j_audiocpu[] = {
    {"sz2.01a", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz2.01a", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz2.02a", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz2j_qsound[] = {
    {"sz2.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sz2.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2j_key[] = {
    {"sfz2j.key", 0x455bd098, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz2j[] = {
    {"maincpu", 4194304, 0, chips_sfz2j_maincpu, N(chips_sfz2j_maincpu)},
    {"gfx", 20971520, 0, chips_sfz2j_gfx, N(chips_sfz2j_gfx)},
    {"audiocpu", 327680, 0, chips_sfz2j_audiocpu, N(chips_sfz2j_audiocpu)},
    {"qsound", 4194304, 0, chips_sfz2j_qsound, N(chips_sfz2j_qsound)},
    {"key", 32, 0, chips_sfz2j_key, N(chips_sfz2j_key)},
};
static const Cps2Load chips_sfz2jr1_maincpu[] = {
    {"sz2j.03a", 0x97461e28, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz2j.04a", 0xae4851a9, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz2.05a", 0x98e8e992, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz2.06", 0x5b1d49c0, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz2j.07a", 0xd910b2a2, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz2.08", 0x0fe8585d, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2jr1_gfx[] = {
    {"sz2.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz2.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz2.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz2.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz2.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sz2.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sz2.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sz2.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfz2jr1_audiocpu[] = {
    {"sz2.01a", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz2.01a", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz2.02a", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz2jr1_qsound[] = {
    {"sz2.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sz2.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2jr1_key[] = {
    {"sfz2j.key", 0x455bd098, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz2jr1[] = {
    {"maincpu", 4194304, 0, chips_sfz2jr1_maincpu, N(chips_sfz2jr1_maincpu)},
    {"gfx", 20971520, 0, chips_sfz2jr1_gfx, N(chips_sfz2jr1_gfx)},
    {"audiocpu", 327680, 0, chips_sfz2jr1_audiocpu, N(chips_sfz2jr1_audiocpu)},
    {"qsound", 4194304, 0, chips_sfz2jr1_qsound, N(chips_sfz2jr1_qsound)},
    {"key", 32, 0, chips_sfz2jr1_key, N(chips_sfz2jr1_key)},
};
static const Cps2Load chips_sfz2a_maincpu[] = {
    {"sz2a.03a", 0x30d2099f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz2a.04a", 0x1cc94db1, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz2.05a", 0x98e8e992, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz2.06", 0x5b1d49c0, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz2a.07a", 0x0aed2494, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz2.08", 0x0fe8585d, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2a_gfx[] = {
    {"sz2.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz2.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz2.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz2.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz2.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sz2.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sz2.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sz2.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfz2a_audiocpu[] = {
    {"sz2.01a", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz2.01a", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz2.02a", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz2a_qsound[] = {
    {"sz2.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sz2.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2a_key[] = {
    {"sfz2a.key", 0x777b7358, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz2a[] = {
    {"maincpu", 4194304, 0, chips_sfz2a_maincpu, N(chips_sfz2a_maincpu)},
    {"gfx", 20971520, 0, chips_sfz2a_gfx, N(chips_sfz2a_gfx)},
    {"audiocpu", 327680, 0, chips_sfz2a_audiocpu, N(chips_sfz2a_audiocpu)},
    {"qsound", 4194304, 0, chips_sfz2a_qsound, N(chips_sfz2a_qsound)},
    {"key", 32, 0, chips_sfz2a_key, N(chips_sfz2a_key)},
};
static const Cps2Load chips_sfz2b_maincpu[] = {
    {"sz2b.03b", 0x1ac12812, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz2b.04b", 0xe4ffaf68, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz2b.05a", 0xdd224156, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz2b.06a", 0xa45a75a6, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz2b.07a", 0x7d19d5ec, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz2b.08", 0x92b66e01, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2b_gfx[] = {
    {"sz2.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz2.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz2.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz2.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz2.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sz2.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sz2.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sz2.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfz2b_audiocpu[] = {
    {"sz2.01a", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz2.01a", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz2.02a", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz2b_qsound[] = {
    {"sz2.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sz2.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2b_key[] = {
    {"sfz2b.key", 0x35b1df07, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz2b[] = {
    {"maincpu", 4194304, 0, chips_sfz2b_maincpu, N(chips_sfz2b_maincpu)},
    {"gfx", 20971520, 0, chips_sfz2b_gfx, N(chips_sfz2b_gfx)},
    {"audiocpu", 327680, 0, chips_sfz2b_audiocpu, N(chips_sfz2b_audiocpu)},
    {"qsound", 4194304, 0, chips_sfz2b_qsound, N(chips_sfz2b_qsound)},
    {"key", 32, 0, chips_sfz2b_key, N(chips_sfz2b_key)},
};
static const Cps2Load chips_sfz2br1_maincpu[] = {
    {"sz2b.03", 0xe6ce530b, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz2b.04", 0x1605a0cb, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz2.05", 0x4b442a7c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz2.06", 0x5b1d49c0, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz2b.07", 0x947e8ac6, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz2b.08", 0x92b66e01, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2br1_gfx[] = {
    {"sz2.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz2.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz2.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz2.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz2.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sz2.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sz2.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sz2.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfz2br1_audiocpu[] = {
    {"sz2.01a", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz2.01a", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz2.02a", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz2br1_qsound[] = {
    {"sz2.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sz2.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2br1_key[] = {
    {"sfz2b.key", 0x35b1df07, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz2br1[] = {
    {"maincpu", 4194304, 0, chips_sfz2br1_maincpu, N(chips_sfz2br1_maincpu)},
    {"gfx", 20971520, 0, chips_sfz2br1_gfx, N(chips_sfz2br1_gfx)},
    {"audiocpu", 327680, 0, chips_sfz2br1_audiocpu, N(chips_sfz2br1_audiocpu)},
    {"qsound", 4194304, 0, chips_sfz2br1_qsound, N(chips_sfz2br1_qsound)},
    {"key", 32, 0, chips_sfz2br1_key, N(chips_sfz2br1_key)},
};
static const Cps2Load chips_sfz2h_maincpu[] = {
    {"sz2h.03", 0xbfeddf5b, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz2h.04", 0xea5009fb, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz2.05", 0x4b442a7c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz2.06", 0x5b1d49c0, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz2h.07", 0x947e8ac6, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz2h.08", 0x92b66e01, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2h_gfx[] = {
    {"sz2.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz2.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz2.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz2.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz2.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sz2.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sz2.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sz2.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfz2h_audiocpu[] = {
    {"sz2.01a", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz2.01a", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz2.02a", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz2h_qsound[] = {
    {"sz2.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sz2.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2h_key[] = {
    {"sfz2h.key", 0x2719ea16, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz2h[] = {
    {"maincpu", 4194304, 0, chips_sfz2h_maincpu, N(chips_sfz2h_maincpu)},
    {"gfx", 20971520, 0, chips_sfz2h_gfx, N(chips_sfz2h_gfx)},
    {"audiocpu", 327680, 0, chips_sfz2h_audiocpu, N(chips_sfz2h_audiocpu)},
    {"qsound", 4194304, 0, chips_sfz2h_qsound, N(chips_sfz2h_qsound)},
    {"key", 32, 0, chips_sfz2h_key, N(chips_sfz2h_key)},
};
static const Cps2Load chips_sfz2n_maincpu[] = {
    {"sz2n.03", 0x58924741, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz2n.04", 0x592a17c5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz2.05", 0x4b442a7c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz2.06", 0x5b1d49c0, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz2.07", 0x8e184246, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz2.08", 0x0fe8585d, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2n_gfx[] = {
    {"sz2.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz2.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz2.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz2.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz2.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sz2.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sz2.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sz2.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfz2n_audiocpu[] = {
    {"sz2.01a", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz2.01a", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz2.02a", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz2n_qsound[] = {
    {"sz2.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sz2.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2n_key[] = {
    {"sfz2n.key", 0xd1cc49d5, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz2n[] = {
    {"maincpu", 4194304, 0, chips_sfz2n_maincpu, N(chips_sfz2n_maincpu)},
    {"gfx", 20971520, 0, chips_sfz2n_gfx, N(chips_sfz2n_gfx)},
    {"audiocpu", 327680, 0, chips_sfz2n_audiocpu, N(chips_sfz2n_audiocpu)},
    {"qsound", 4194304, 0, chips_sfz2n_qsound, N(chips_sfz2n_qsound)},
    {"key", 32, 0, chips_sfz2n_key, N(chips_sfz2n_key)},
};
static const Cps2Load chips_sfz2al_maincpu[] = {
    {"szaa.03", 0x88e7023e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"szaa.04", 0xae8ec36e, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"szaa.05", 0xf053a55e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"szaa.06", 0xcfc0e7a8, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"szaa.07", 0x5feb8b20, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"szaa.08", 0x6eb6d412, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2al_gfx[] = {
    {"sza.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sza.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sza.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sza.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sza.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sza.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sza.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sza.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfz2al_audiocpu[] = {
    {"sza.01", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sza.01", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sza.02", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz2al_qsound[] = {
    {"sza.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sza.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2al_key[] = {
    {"sfz2al.key", 0x2904963e, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz2al[] = {
    {"maincpu", 4194304, 0, chips_sfz2al_maincpu, N(chips_sfz2al_maincpu)},
    {"gfx", 20971520, 0, chips_sfz2al_gfx, N(chips_sfz2al_gfx)},
    {"audiocpu", 327680, 0, chips_sfz2al_audiocpu, N(chips_sfz2al_audiocpu)},
    {"qsound", 4194304, 0, chips_sfz2al_qsound, N(chips_sfz2al_qsound)},
    {"key", 32, 0, chips_sfz2al_key, N(chips_sfz2al_key)},
};
static const Cps2Load chips_sfz2alr1_maincpu[] = {
    {"szaa.03a", 0x9f67c585, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"szaa.04a", 0x5a447a54, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"szaa.05a", 0xf053a55e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"szaa.06a", 0xcfc0e7a8, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"szaa.07a", 0x5feb8b20, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"szaa.08a", 0x6eb6d412, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2alr1_gfx[] = {
    {"sz2.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz2.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz2.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz2.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz2.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sz2.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sz2.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sz2.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfz2alr1_audiocpu[] = {
    {"sza.01", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sza.01", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sza.02", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz2alr1_qsound[] = {
    {"sza.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sza.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2alr1_key[] = {
    {"sfz2al.key", 0x2904963e, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz2alr1[] = {
    {"maincpu", 4194304, 0, chips_sfz2alr1_maincpu, N(chips_sfz2alr1_maincpu)},
    {"gfx", 20971520, 0, chips_sfz2alr1_gfx, N(chips_sfz2alr1_gfx)},
    {"audiocpu", 327680, 0, chips_sfz2alr1_audiocpu, N(chips_sfz2alr1_audiocpu)},
    {"qsound", 4194304, 0, chips_sfz2alr1_qsound, N(chips_sfz2alr1_qsound)},
    {"key", 32, 0, chips_sfz2alr1_key, N(chips_sfz2alr1_key)},
};
static const Cps2Load chips_sfz2alj_maincpu[] = {
    {"szaj.03a", 0xa3802fe3, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"szaj.04a", 0xe7ca87c7, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"szaj.05a", 0xc88ebf88, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"szaj.06a", 0x35ed5b7a, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"szaj.07a", 0x975dcb3e, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"szaj.08a", 0xdc73f2d7, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2alj_gfx[] = {
    {"sza.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sza.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sza.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sza.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sza.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sza.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sza.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sza.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfz2alj_audiocpu[] = {
    {"sza.01", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sza.01", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sza.02", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz2alj_qsound[] = {
    {"sza.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sza.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2alj_key[] = {
    {"sfz2alj.key", 0x4c42320f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz2alj[] = {
    {"maincpu", 4194304, 0, chips_sfz2alj_maincpu, N(chips_sfz2alj_maincpu)},
    {"gfx", 20971520, 0, chips_sfz2alj_gfx, N(chips_sfz2alj_gfx)},
    {"audiocpu", 327680, 0, chips_sfz2alj_audiocpu, N(chips_sfz2alj_audiocpu)},
    {"qsound", 4194304, 0, chips_sfz2alj_qsound, N(chips_sfz2alj_qsound)},
    {"key", 32, 0, chips_sfz2alj_key, N(chips_sfz2alj_key)},
};
static const Cps2Load chips_sfz2alh_maincpu[] = {
    {"szah.03", 0x06f93d1d, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"szah.04", 0xe62ee914, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"szah.05", 0x2b7f4b20, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sza.06", 0x0abda2fc, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sza.07", 0xe9430762, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sza.08", 0xb65711a9, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2alh_gfx[] = {
    {"sza.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sza.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sza.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sza.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sza.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sza.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sza.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sza.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfz2alh_audiocpu[] = {
    {"sza.01", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sza.01", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sza.02", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz2alh_qsound[] = {
    {"sza.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sza.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2alh_key[] = {
    {"sfz2alh.key", 0xf320f655, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz2alh[] = {
    {"maincpu", 4194304, 0, chips_sfz2alh_maincpu, N(chips_sfz2alh_maincpu)},
    {"gfx", 20971520, 0, chips_sfz2alh_gfx, N(chips_sfz2alh_gfx)},
    {"audiocpu", 327680, 0, chips_sfz2alh_audiocpu, N(chips_sfz2alh_audiocpu)},
    {"qsound", 4194304, 0, chips_sfz2alh_qsound, N(chips_sfz2alh_qsound)},
    {"key", 32, 0, chips_sfz2alh_key, N(chips_sfz2alh_key)},
};
static const Cps2Load chips_sfz2alb_maincpu[] = {
    {"szab.03", 0xcb436eca, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"szab.04", 0x14534bea, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"szab.05", 0x7fb10658, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sza.06", 0x0abda2fc, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sza.07", 0xe9430762, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sza.08", 0xb65711a9, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2alb_gfx[] = {
    {"sza.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sza.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sza.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sza.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sza.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sza.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sza.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sza.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfz2alb_audiocpu[] = {
    {"sza.01", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sza.01", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sza.02", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz2alb_qsound[] = {
    {"sza.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sza.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2alb_key[] = {
    {"sfz2alb.key", 0xc8b3ac73, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz2alb[] = {
    {"maincpu", 4194304, 0, chips_sfz2alb_maincpu, N(chips_sfz2alb_maincpu)},
    {"gfx", 20971520, 0, chips_sfz2alb_gfx, N(chips_sfz2alb_gfx)},
    {"audiocpu", 327680, 0, chips_sfz2alb_audiocpu, N(chips_sfz2alb_audiocpu)},
    {"qsound", 4194304, 0, chips_sfz2alb_qsound, N(chips_sfz2alb_qsound)},
    {"key", 32, 0, chips_sfz2alb_key, N(chips_sfz2alb_key)},
};
static const Cps2Load chips_spf2t_maincpu[] = {
    {"pzfe.03", 0x2af51954, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pzf.04", 0xb80649e2, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_spf2t_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"pzf.14m", 0x2d4881cb, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"pzf.16m", 0x4b0fd1be, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"pzf.18m", 0xe43aac33, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"pzf.20m", 0x7f536ff1, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_spf2t_audiocpu[] = {
    {"pzf.01", 0x600fb2a3, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pzf.01", 0x600fb2a3, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pzf.02", 0x496076e0, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_spf2t_qsound[] = {
    {"pzf.11m", 0x78442743, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pzf.12m", 0x399d2c7b, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_spf2t_key[] = {
    {"spf2t.key", 0x4c4dc7e3, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_spf2t[] = {
    {"maincpu", 4194304, 0, chips_spf2t_maincpu, N(chips_spf2t_maincpu)},
    {"gfx", 12582912, 0, chips_spf2t_gfx, N(chips_spf2t_gfx)},
    {"audiocpu", 327680, 0, chips_spf2t_audiocpu, N(chips_spf2t_audiocpu)},
    {"qsound", 4194304, 0, chips_spf2t_qsound, N(chips_spf2t_qsound)},
    {"key", 32, 0, chips_spf2t_key, N(chips_spf2t_key)},
};
static const Cps2Load chips_spf2tu_maincpu[] = {
    {"pzfu.03a", 0x346e62ef, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pzf.04", 0xb80649e2, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_spf2tu_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"pzf.14m", 0x2d4881cb, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"pzf.16m", 0x4b0fd1be, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"pzf.18m", 0xe43aac33, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"pzf.20m", 0x7f536ff1, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_spf2tu_audiocpu[] = {
    {"pzf.01", 0x600fb2a3, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pzf.01", 0x600fb2a3, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pzf.02", 0x496076e0, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_spf2tu_qsound[] = {
    {"pzf.11m", 0x78442743, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pzf.12m", 0x399d2c7b, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_spf2tu_key[] = {
    {"spf2tu.key", 0x5d7b15e8, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_spf2tu[] = {
    {"maincpu", 4194304, 0, chips_spf2tu_maincpu, N(chips_spf2tu_maincpu)},
    {"gfx", 12582912, 0, chips_spf2tu_gfx, N(chips_spf2tu_gfx)},
    {"audiocpu", 327680, 0, chips_spf2tu_audiocpu, N(chips_spf2tu_audiocpu)},
    {"qsound", 4194304, 0, chips_spf2tu_qsound, N(chips_spf2tu_qsound)},
    {"key", 32, 0, chips_spf2tu_key, N(chips_spf2tu_key)},
};
static const Cps2Load chips_spf2xj_maincpu[] = {
    {"pzfj.03a", 0x2070554a, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pzf.04", 0xb80649e2, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_spf2xj_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"pzf.14m", 0x2d4881cb, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"pzf.16m", 0x4b0fd1be, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"pzf.18m", 0xe43aac33, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"pzf.20m", 0x7f536ff1, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_spf2xj_audiocpu[] = {
    {"pzf.01", 0x600fb2a3, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pzf.01", 0x600fb2a3, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pzf.02", 0x496076e0, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_spf2xj_qsound[] = {
    {"pzf.11m", 0x78442743, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pzf.12m", 0x399d2c7b, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_spf2xj_key[] = {
    {"spf2xj.key", 0xdc39fd34, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_spf2xj[] = {
    {"maincpu", 4194304, 0, chips_spf2xj_maincpu, N(chips_spf2xj_maincpu)},
    {"gfx", 12582912, 0, chips_spf2xj_gfx, N(chips_spf2xj_gfx)},
    {"audiocpu", 327680, 0, chips_spf2xj_audiocpu, N(chips_spf2xj_audiocpu)},
    {"qsound", 4194304, 0, chips_spf2xj_qsound, N(chips_spf2xj_qsound)},
    {"key", 32, 0, chips_spf2xj_key, N(chips_spf2xj_key)},
};
static const Cps2Load chips_spf2ta_maincpu[] = {
    {"pzfa.03", 0x3cecfa78, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pzf.04", 0xb80649e2, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_spf2ta_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"pzf.14m", 0x2d4881cb, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"pzf.16m", 0x4b0fd1be, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"pzf.18m", 0xe43aac33, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"pzf.20m", 0x7f536ff1, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_spf2ta_audiocpu[] = {
    {"pzf.01", 0x600fb2a3, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pzf.01", 0x600fb2a3, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pzf.02", 0x496076e0, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_spf2ta_qsound[] = {
    {"pzf.11m", 0x78442743, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pzf.12m", 0x399d2c7b, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_spf2ta_key[] = {
    {"spf2ta.key", 0x61e93a18, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_spf2ta[] = {
    {"maincpu", 4194304, 0, chips_spf2ta_maincpu, N(chips_spf2ta_maincpu)},
    {"gfx", 12582912, 0, chips_spf2ta_gfx, N(chips_spf2ta_gfx)},
    {"audiocpu", 327680, 0, chips_spf2ta_audiocpu, N(chips_spf2ta_audiocpu)},
    {"qsound", 4194304, 0, chips_spf2ta_qsound, N(chips_spf2ta_qsound)},
    {"key", 32, 0, chips_spf2ta_key, N(chips_spf2ta_key)},
};
static const Cps2Load chips_spf2th_maincpu[] = {
    {"pzfh.03", 0x20510f2d, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pzf.04", 0xb80649e2, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_spf2th_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"pzf.14m", 0x2d4881cb, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"pzf.16m", 0x4b0fd1be, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"pzf.18m", 0xe43aac33, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"pzf.20m", 0x7f536ff1, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_spf2th_audiocpu[] = {
    {"pzf.01", 0x600fb2a3, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pzf.01", 0x600fb2a3, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pzf.02", 0x496076e0, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_spf2th_qsound[] = {
    {"pzf.11m", 0x78442743, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pzf.12m", 0x399d2c7b, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_spf2th_key[] = {
    {"spf2th.key", 0x292db449, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_spf2th[] = {
    {"maincpu", 4194304, 0, chips_spf2th_maincpu, N(chips_spf2th_maincpu)},
    {"gfx", 12582912, 0, chips_spf2th_gfx, N(chips_spf2th_gfx)},
    {"audiocpu", 327680, 0, chips_spf2th_audiocpu, N(chips_spf2th_audiocpu)},
    {"qsound", 4194304, 0, chips_spf2th_qsound, N(chips_spf2th_qsound)},
    {"key", 32, 0, chips_spf2th_key, N(chips_spf2th_key)},
};
static const Cps2Load chips_megaman2_maincpu[] = {
    {"rm2u.03", 0x8ffc2cd1, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"rm2u.04", 0xbb30083a, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"rm2.05", 0x02ee9efc, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_megaman2_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"rm2.14m", 0x9b1f00b4, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"rm2.16m", 0xc2bb0c24, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"rm2.18m", 0x12257251, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"rm2.20m", 0xf9b6e786, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_megaman2_audiocpu[] = {
    {"rm2.01a", 0xd18e7859, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"rm2.01a", 0xd18e7859, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"rm2.02", 0xc463ece0, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_megaman2_qsound[] = {
    {"rm2.11m", 0x2106174d, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"rm2.12m", 0x546c1636, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_megaman2_key[] = {
    {"megaman2.key", 0x6828ed6d, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_megaman2[] = {
    {"maincpu", 4194304, 0, chips_megaman2_maincpu, N(chips_megaman2_maincpu)},
    {"gfx", 16777216, 0, chips_megaman2_gfx, N(chips_megaman2_gfx)},
    {"audiocpu", 327680, 0, chips_megaman2_audiocpu, N(chips_megaman2_audiocpu)},
    {"qsound", 4194304, 0, chips_megaman2_qsound, N(chips_megaman2_qsound)},
    {"key", 32, 0, chips_megaman2_key, N(chips_megaman2_key)},
};
static const Cps2Load chips_megaman2a_maincpu[] = {
    {"rm2a.03", 0x2b330ca7, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"rm2a.04", 0x8b47942b, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"rm2.05", 0x02ee9efc, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_megaman2a_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"rm2.14m", 0x9b1f00b4, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"rm2.16m", 0xc2bb0c24, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"rm2.18m", 0x12257251, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"rm2.20m", 0xf9b6e786, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_megaman2a_audiocpu[] = {
    {"rm2.01a", 0xd18e7859, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"rm2.01a", 0xd18e7859, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"rm2.02", 0xc463ece0, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_megaman2a_qsound[] = {
    {"rm2.11m", 0x2106174d, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"rm2.12m", 0x546c1636, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_megaman2a_key[] = {
    {"megaman2a.key", 0xd6e8dcd7, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_megaman2a[] = {
    {"maincpu", 4194304, 0, chips_megaman2a_maincpu, N(chips_megaman2a_maincpu)},
    {"gfx", 16777216, 0, chips_megaman2a_gfx, N(chips_megaman2a_gfx)},
    {"audiocpu", 327680, 0, chips_megaman2a_audiocpu, N(chips_megaman2a_audiocpu)},
    {"qsound", 4194304, 0, chips_megaman2a_qsound, N(chips_megaman2a_qsound)},
    {"key", 32, 0, chips_megaman2a_key, N(chips_megaman2a_key)},
};
static const Cps2Load chips_rockman2j_maincpu[] = {
    {"rm2j.03", 0xdbaa1437, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"rm2j.04", 0xcf5ba612, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"rm2.05", 0x02ee9efc, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_rockman2j_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"rm2.14m", 0x9b1f00b4, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"rm2.16m", 0xc2bb0c24, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"rm2.18m", 0x12257251, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"rm2.20m", 0xf9b6e786, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_rockman2j_audiocpu[] = {
    {"rm2.01a", 0xd18e7859, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"rm2.01a", 0xd18e7859, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"rm2.02", 0xc463ece0, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_rockman2j_qsound[] = {
    {"rm2.11m", 0x2106174d, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"rm2.12m", 0x546c1636, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_rockman2j_key[] = {
    {"rockman2j.key", 0xc590187a, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_rockman2j[] = {
    {"maincpu", 4194304, 0, chips_rockman2j_maincpu, N(chips_rockman2j_maincpu)},
    {"gfx", 16777216, 0, chips_rockman2j_gfx, N(chips_rockman2j_gfx)},
    {"audiocpu", 327680, 0, chips_rockman2j_audiocpu, N(chips_rockman2j_audiocpu)},
    {"qsound", 4194304, 0, chips_rockman2j_qsound, N(chips_rockman2j_qsound)},
    {"key", 32, 0, chips_rockman2j_key, N(chips_rockman2j_key)},
};
static const Cps2Load chips_megaman2h_maincpu[] = {
    {"rm2h.03", 0xbb180378, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"rm2h.04", 0x205ffcd6, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"rm2.05", 0x02ee9efc, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_megaman2h_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"rm2.14m", 0x9b1f00b4, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"rm2.16m", 0xc2bb0c24, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"rm2.18m", 0x12257251, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"rm2.20m", 0xf9b6e786, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_megaman2h_audiocpu[] = {
    {"rm2.01a", 0xd18e7859, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"rm2.01a", 0xd18e7859, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"rm2.02", 0xc463ece0, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_megaman2h_qsound[] = {
    {"rm2.11m", 0x2106174d, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"rm2.12m", 0x546c1636, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_megaman2h_key[] = {
    {"megaman2h.key", 0x99cb8d19, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_megaman2h[] = {
    {"maincpu", 4194304, 0, chips_megaman2h_maincpu, N(chips_megaman2h_maincpu)},
    {"gfx", 16777216, 0, chips_megaman2h_gfx, N(chips_megaman2h_gfx)},
    {"audiocpu", 327680, 0, chips_megaman2h_audiocpu, N(chips_megaman2h_audiocpu)},
    {"qsound", 4194304, 0, chips_megaman2h_qsound, N(chips_megaman2h_qsound)},
    {"key", 32, 0, chips_megaman2h_key, N(chips_megaman2h_key)},
};
static const Cps2Load chips_qndream_maincpu[] = {
    {"tqzj.03a", 0x7acf3e30, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"tqzj.04", 0xf1044a87, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"tqzj.05", 0x4105ba0e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"tqzj.06", 0xc371e8a5, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_qndream_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"tqz.14m", 0x98af88a2, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"tqz.16m", 0xdf82d491, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"tqz.18m", 0x42f132ff, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"tqz.20m", 0xb2e128a3, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_qndream_audiocpu[] = {
    {"tqz.01", 0xe9ce9d0a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"tqz.01", 0xe9ce9d0a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_qndream_qsound[] = {
    {"tqz.11m", 0x78e7884f, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"tqz.12m", 0x2e049b13, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_qndream_key[] = {
    {"qndream.key", 0x97eee4ff, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_qndream[] = {
    {"maincpu", 4194304, 0, chips_qndream_maincpu, N(chips_qndream_maincpu)},
    {"gfx", 16777216, 0, chips_qndream_gfx, N(chips_qndream_gfx)},
    {"audiocpu", 327680, 0, chips_qndream_audiocpu, N(chips_qndream_audiocpu)},
    {"qsound", 4194304, 0, chips_qndream_qsound, N(chips_qndream_qsound)},
    {"key", 32, 0, chips_qndream_key, N(chips_qndream_key)},
};
static const Cps2Load chips_xmvsf_maincpu[] = {
    {"xvse.03f", 0xdb06413f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvse.04f", 0xef015aef, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsf_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsf_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsf_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsf_key[] = {
    {"xmvsf.key", 0xd5c07311, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsf[] = {
    {"maincpu", 4194304, 0, chips_xmvsf_maincpu, N(chips_xmvsf_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsf_gfx, N(chips_xmvsf_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsf_audiocpu, N(chips_xmvsf_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsf_qsound, N(chips_xmvsf_qsound)},
    {"key", 32, 0, chips_xmvsf_key, N(chips_xmvsf_key)},
};
static const Cps2Load chips_xmvsfr1_maincpu[] = {
    {"xvse.03d", 0x5ae5bd3b, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvse.04d", 0x5eb9c02e, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfr1_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfr1_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfr1_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfr1_key[] = {
    {"xmvsf.key", 0xd5c07311, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfr1[] = {
    {"maincpu", 4194304, 0, chips_xmvsfr1_maincpu, N(chips_xmvsfr1_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsfr1_gfx, N(chips_xmvsfr1_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfr1_audiocpu, N(chips_xmvsfr1_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfr1_qsound, N(chips_xmvsfr1_qsound)},
    {"key", 32, 0, chips_xmvsfr1_key, N(chips_xmvsfr1_key)},
};
static const Cps2Load chips_xmvsfu_maincpu[] = {
    {"xvsu.03k", 0x8739ef61, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvsu.04k", 0xe11d35c1, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfu_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfu_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfu_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfu_key[] = {
    {"xmvsfu.key", 0xeca13458, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfu[] = {
    {"maincpu", 4194304, 0, chips_xmvsfu_maincpu, N(chips_xmvsfu_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsfu_gfx, N(chips_xmvsfu_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfu_audiocpu, N(chips_xmvsfu_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfu_qsound, N(chips_xmvsfu_qsound)},
    {"key", 32, 0, chips_xmvsfu_key, N(chips_xmvsfu_key)},
};
static const Cps2Load chips_xmvsfur1_maincpu[] = {
    {"xvsu.03i", 0x5481155a, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvsu.04i", 0x1e236388, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfur1_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfur1_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfur1_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfur1_key[] = {
    {"xmvsfu.key", 0xeca13458, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfur1[] = {
    {"maincpu", 4194304, 0, chips_xmvsfur1_maincpu, N(chips_xmvsfur1_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsfur1_gfx, N(chips_xmvsfur1_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfur1_audiocpu, N(chips_xmvsfur1_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfur1_qsound, N(chips_xmvsfur1_qsound)},
    {"key", 32, 0, chips_xmvsfur1_key, N(chips_xmvsfur1_key)},
};
static const Cps2Load chips_xmvsfur2_maincpu[] = {
    {"xvsu.03d", 0xbd8b152f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvsu.04d", 0x7c7d1da3, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfur2_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfur2_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfur2_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfur2_key[] = {
    {"xmvsfu.key", 0xeca13458, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfur2[] = {
    {"maincpu", 4194304, 0, chips_xmvsfur2_maincpu, N(chips_xmvsfur2_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsfur2_gfx, N(chips_xmvsfur2_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfur2_audiocpu, N(chips_xmvsfur2_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfur2_qsound, N(chips_xmvsfur2_qsound)},
    {"key", 32, 0, chips_xmvsfur2_key, N(chips_xmvsfur2_key)},
};
static const Cps2Load chips_xmvsfj_maincpu[] = {
    {"xvsj.03m", 0xe2944372, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvsj.04m", 0xc20b8524, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfj_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfj_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfj_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfj_key[] = {
    {"xmvsfj.key", 0x87576cda, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfj[] = {
    {"maincpu", 4194304, 0, chips_xmvsfj_maincpu, N(chips_xmvsfj_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsfj_gfx, N(chips_xmvsfj_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfj_audiocpu, N(chips_xmvsfj_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfj_qsound, N(chips_xmvsfj_qsound)},
    {"key", 32, 0, chips_xmvsfj_key, N(chips_xmvsfj_key)},
};
static const Cps2Load chips_xmvsfjr1_maincpu[] = {
    {"xvsj.03k", 0x2a167526, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvsj.04k", 0xd993436b, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfjr1_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfjr1_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfjr1_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfjr1_key[] = {
    {"xmvsfj.key", 0x87576cda, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfjr1[] = {
    {"maincpu", 4194304, 0, chips_xmvsfjr1_maincpu, N(chips_xmvsfjr1_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsfjr1_gfx, N(chips_xmvsfjr1_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfjr1_audiocpu, N(chips_xmvsfjr1_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfjr1_qsound, N(chips_xmvsfjr1_qsound)},
    {"key", 32, 0, chips_xmvsfjr1_key, N(chips_xmvsfjr1_key)},
};
static const Cps2Load chips_xmvsfjr2_maincpu[] = {
    {"xvsj.03i", 0xef24da96, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvsj.04i", 0x70a59b35, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfjr2_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfjr2_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfjr2_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfjr2_key[] = {
    {"xmvsfj.key", 0x87576cda, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfjr2[] = {
    {"maincpu", 4194304, 0, chips_xmvsfjr2_maincpu, N(chips_xmvsfjr2_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsfjr2_gfx, N(chips_xmvsfjr2_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfjr2_audiocpu, N(chips_xmvsfjr2_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfjr2_qsound, N(chips_xmvsfjr2_qsound)},
    {"key", 32, 0, chips_xmvsfjr2_key, N(chips_xmvsfjr2_key)},
};
static const Cps2Load chips_xmvsfjr3_maincpu[] = {
    {"xvsj.03d", 0xbeb81de9, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvsj.04d", 0x23d11271, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfjr3_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfjr3_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfjr3_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfjr3_key[] = {
    {"xmvsfj.key", 0x87576cda, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfjr3[] = {
    {"maincpu", 4194304, 0, chips_xmvsfjr3_maincpu, N(chips_xmvsfjr3_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsfjr3_gfx, N(chips_xmvsfjr3_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfjr3_audiocpu, N(chips_xmvsfjr3_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfjr3_qsound, N(chips_xmvsfjr3_qsound)},
    {"key", 32, 0, chips_xmvsfjr3_key, N(chips_xmvsfjr3_key)},
};
static const Cps2Load chips_xmvsfjr4_maincpu[] = {
    {"xvsj.03c", 0x180656a1, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvsj.04c", 0x5832811c, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05", 0x030e0e1e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06", 0x5d04a8ff, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfjr4_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfjr4_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfjr4_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfjr4_key[] = {
    {"xmvsfj.key", 0x87576cda, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfjr4[] = {
    {"maincpu", 4194304, 0, chips_xmvsfjr4_maincpu, N(chips_xmvsfjr4_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsfjr4_gfx, N(chips_xmvsfjr4_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfjr4_audiocpu, N(chips_xmvsfjr4_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfjr4_qsound, N(chips_xmvsfjr4_qsound)},
    {"key", 32, 0, chips_xmvsfjr4_key, N(chips_xmvsfjr4_key)},
};
static const Cps2Load chips_xmvsfa_maincpu[] = {
    {"xvsa.03k", 0xd0cca7a8, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvsa.04k", 0x8c8e76fd, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfa_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfa_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfa_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfa_key[] = {
    {"xmvsfa.key", 0x44941468, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfa[] = {
    {"maincpu", 4194304, 0, chips_xmvsfa_maincpu, N(chips_xmvsfa_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsfa_gfx, N(chips_xmvsfa_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfa_audiocpu, N(chips_xmvsfa_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfa_qsound, N(chips_xmvsfa_qsound)},
    {"key", 32, 0, chips_xmvsfa_key, N(chips_xmvsfa_key)},
};
static const Cps2Load chips_xmvsfar1_maincpu[] = {
    {"xvsa.03", 0x520054df, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvsa.04", 0x13086e55, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfar1_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfar1_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfar1_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfar1_key[] = {
    {"xmvsfa.key", 0x44941468, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfar1[] = {
    {"maincpu", 4194304, 0, chips_xmvsfar1_maincpu, N(chips_xmvsfar1_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsfar1_gfx, N(chips_xmvsfar1_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfar1_audiocpu, N(chips_xmvsfar1_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfar1_qsound, N(chips_xmvsfar1_qsound)},
    {"key", 32, 0, chips_xmvsfar1_key, N(chips_xmvsfar1_key)},
};
static const Cps2Load chips_xmvsfar2_maincpu[] = {
    {"xvsa.03e", 0x9bdde21c, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvsa.04e", 0x33300edf, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfar2_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfar2_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfar2_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfar2_key[] = {
    {"xmvsfa.key", 0x44941468, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfar2[] = {
    {"maincpu", 4194304, 0, chips_xmvsfar2_maincpu, N(chips_xmvsfar2_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsfar2_gfx, N(chips_xmvsfar2_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfar2_audiocpu, N(chips_xmvsfar2_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfar2_qsound, N(chips_xmvsfar2_qsound)},
    {"key", 32, 0, chips_xmvsfar2_key, N(chips_xmvsfar2_key)},
};
static const Cps2Load chips_xmvsfar3_maincpu[] = {
    {"xvsa.03d", 0x2b164fd7, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvsa.04d", 0x2d32f039, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfar3_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfar3_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvsa.02", 0x19272e4c, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfar3_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfar3_key[] = {
    {"xmvsfa.key", 0x44941468, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfar3[] = {
    {"maincpu", 4194304, 0, chips_xmvsfar3_maincpu, N(chips_xmvsfar3_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsfar3_gfx, N(chips_xmvsfar3_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfar3_audiocpu, N(chips_xmvsfar3_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfar3_qsound, N(chips_xmvsfar3_qsound)},
    {"key", 32, 0, chips_xmvsfar3_key, N(chips_xmvsfar3_key)},
};
static const Cps2Load chips_xmvsfh_maincpu[] = {
    {"xvsh.03a", 0xd4fffb04, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvsh.04a", 0x1b4ea638, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfh_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfh_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfh_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfh_key[] = {
    {"xmvsfh.key", 0xf632a36b, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfh[] = {
    {"maincpu", 4194304, 0, chips_xmvsfh_maincpu, N(chips_xmvsfh_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsfh_gfx, N(chips_xmvsfh_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfh_audiocpu, N(chips_xmvsfh_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfh_qsound, N(chips_xmvsfh_qsound)},
    {"key", 32, 0, chips_xmvsfh_key, N(chips_xmvsfh_key)},
};
static const Cps2Load chips_xmvsfb_maincpu[] = {
    {"xvsb.03h", 0x05baccca, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvsb.04h", 0xe350c755, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfb_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfb_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfb_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfb_key[] = {
    {"xmvsfb.key", 0xf0384798, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfb[] = {
    {"maincpu", 4194304, 0, chips_xmvsfb_maincpu, N(chips_xmvsfb_maincpu)},
    {"gfx", 33554432, 0, chips_xmvsfb_gfx, N(chips_xmvsfb_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfb_audiocpu, N(chips_xmvsfb_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfb_qsound, N(chips_xmvsfb_qsound)},
    {"key", 32, 0, chips_xmvsfb_key, N(chips_xmvsfb_key)},
};
static const Cps2Load chips_batcir_maincpu[] = {
    {"btce.03", 0xbc60484b, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"btce.04", 0x457d55f6, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"btce.05", 0xe86560d7, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"btce.06", 0xf778e61b, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"btc.07", 0x7322d5db, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"btc.08", 0x6aac85ab, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"btc.09", 0x1203db08, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_batcir_gfx[] = {
    {"btc.13m", 0xdc705bad, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"btc.15m", 0xe5779a3c, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"btc.17m", 0xb33f4112, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"btc.19m", 0xa6fcdb7e, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_batcir_audiocpu[] = {
    {"btc.01", 0x1e194310, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"btc.01", 0x1e194310, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"btc.02", 0x01aeb8e6, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_batcir_qsound[] = {
    {"btc.11m", 0xc27f2229, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"btc.12m", 0x418a2e33, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_batcir_key[] = {
    {"batcir.key", 0xe316ae67, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_batcir[] = {
    {"maincpu", 4194304, 0, chips_batcir_maincpu, N(chips_batcir_maincpu)},
    {"gfx", 16777216, 0, chips_batcir_gfx, N(chips_batcir_gfx)},
    {"audiocpu", 327680, 0, chips_batcir_audiocpu, N(chips_batcir_audiocpu)},
    {"qsound", 4194304, 0, chips_batcir_qsound, N(chips_batcir_qsound)},
    {"key", 32, 0, chips_batcir_key, N(chips_batcir_key)},
};
static const Cps2Load chips_batcira_maincpu[] = {
    {"btca.03", 0x1ad20d87, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"btca.04", 0x2b3f4dbe, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"btca.05", 0x8238a3d9, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"btca.06", 0x446c7c02, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"btc.07", 0x7322d5db, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"btc.08", 0x6aac85ab, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"btc.09", 0x1203db08, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_batcira_gfx[] = {
    {"btc.13m", 0xdc705bad, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"btc.15m", 0xe5779a3c, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"btc.17m", 0xb33f4112, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"btc.19m", 0xa6fcdb7e, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_batcira_audiocpu[] = {
    {"btc.01", 0x1e194310, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"btc.01", 0x1e194310, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"btc.02", 0x01aeb8e6, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_batcira_qsound[] = {
    {"btc.11m", 0xc27f2229, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"btc.12m", 0x418a2e33, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_batcira_key[] = {
    {"batcira.key", 0x384500f3, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_batcira[] = {
    {"maincpu", 4194304, 0, chips_batcira_maincpu, N(chips_batcira_maincpu)},
    {"gfx", 16777216, 0, chips_batcira_gfx, N(chips_batcira_gfx)},
    {"audiocpu", 327680, 0, chips_batcira_audiocpu, N(chips_batcira_audiocpu)},
    {"qsound", 4194304, 0, chips_batcira_qsound, N(chips_batcira_qsound)},
    {"key", 32, 0, chips_batcira_key, N(chips_batcira_key)},
};
static const Cps2Load chips_batcirj_maincpu[] = {
    {"btcj.03", 0x6b7e168d, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"btcj.04", 0x46ba3467, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"btcj.05", 0x0e23a859, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"btcj.06", 0xa853b59c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"btc.07", 0x7322d5db, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"btc.08", 0x6aac85ab, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"btc.09", 0x1203db08, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_batcirj_gfx[] = {
    {"btc.13m", 0xdc705bad, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"btc.15m", 0xe5779a3c, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"btc.17m", 0xb33f4112, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"btc.19m", 0xa6fcdb7e, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_batcirj_audiocpu[] = {
    {"btc.01", 0x1e194310, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"btc.01", 0x1e194310, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"btc.02", 0x01aeb8e6, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_batcirj_qsound[] = {
    {"btc.11m", 0xc27f2229, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"btc.12m", 0x418a2e33, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_batcirj_key[] = {
    {"batcirj.key", 0x9f9fb965, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_batcirj[] = {
    {"maincpu", 4194304, 0, chips_batcirj_maincpu, N(chips_batcirj_maincpu)},
    {"gfx", 16777216, 0, chips_batcirj_gfx, N(chips_batcirj_gfx)},
    {"audiocpu", 327680, 0, chips_batcirj_audiocpu, N(chips_batcirj_audiocpu)},
    {"qsound", 4194304, 0, chips_batcirj_qsound, N(chips_batcirj_qsound)},
    {"key", 32, 0, chips_batcirj_key, N(chips_batcirj_key)},
};
static const Cps2Load chips_vsav_maincpu[] = {
    {"vm3e.03d", 0xf5962a8c, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vm3e.04d", 0x21b40ea2, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vm3.05a", 0x4118e00f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vm3.06a", 0x2f4fd3a9, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vm3.07b", 0xcbda91b8, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vm3.08a", 0x6ca47259, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vm3.09b", 0xf4a339e3, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vm3.10b", 0xfffbb5b8, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vsav_gfx[] = {
    {"vm3.13m", 0xfd8a11eb, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vm3.15m", 0xdd1e7d4e, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vm3.17m", 0x6b89445e, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vm3.19m", 0x3830fdc7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vm3.14m", 0xc1a28e6c, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vm3.16m", 0x194a7304, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vm3.18m", 0xdf9a9f47, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vm3.20m", 0xc22fc3d9, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vsav_audiocpu[] = {
    {"vm3.01", 0xf778769b, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vm3.01", 0xf778769b, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vm3.02", 0xcc09faa1, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vsav_qsound[] = {
    {"vm3.11m", 0xe80e956e, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"vm3.12m", 0x9cd71557, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_vsav_key[] = {
    {"vsav.key", 0xa6e3b164, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vsav[] = {
    {"maincpu", 4194304, 0, chips_vsav_maincpu, N(chips_vsav_maincpu)},
    {"gfx", 33554432, 0, chips_vsav_gfx, N(chips_vsav_gfx)},
    {"audiocpu", 327680, 0, chips_vsav_audiocpu, N(chips_vsav_audiocpu)},
    {"qsound", 8388608, 0, chips_vsav_qsound, N(chips_vsav_qsound)},
    {"key", 32, 0, chips_vsav_key, N(chips_vsav_key)},
};
static const Cps2Load chips_vsavu_maincpu[] = {
    {"vm3u.03d", 0x1f295274, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vm3u.04d", 0xc46adf81, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vm3.05a", 0x4118e00f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vm3.06a", 0x2f4fd3a9, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vm3.07b", 0xcbda91b8, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vm3.08a", 0x6ca47259, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vm3.09b", 0xf4a339e3, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vm3.10b", 0xfffbb5b8, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vsavu_gfx[] = {
    {"vm3.13m", 0xfd8a11eb, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vm3.15m", 0xdd1e7d4e, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vm3.17m", 0x6b89445e, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vm3.19m", 0x3830fdc7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vm3.14m", 0xc1a28e6c, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vm3.16m", 0x194a7304, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vm3.18m", 0xdf9a9f47, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vm3.20m", 0xc22fc3d9, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vsavu_audiocpu[] = {
    {"vm3.01", 0xf778769b, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vm3.01", 0xf778769b, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vm3.02", 0xcc09faa1, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vsavu_qsound[] = {
    {"vm3.11m", 0xe80e956e, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"vm3.12m", 0x9cd71557, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_vsavu_key[] = {
    {"vsavu.key", 0xff21b9d7, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vsavu[] = {
    {"maincpu", 4194304, 0, chips_vsavu_maincpu, N(chips_vsavu_maincpu)},
    {"gfx", 33554432, 0, chips_vsavu_gfx, N(chips_vsavu_gfx)},
    {"audiocpu", 327680, 0, chips_vsavu_audiocpu, N(chips_vsavu_audiocpu)},
    {"qsound", 8388608, 0, chips_vsavu_qsound, N(chips_vsavu_qsound)},
    {"key", 32, 0, chips_vsavu_key, N(chips_vsavu_key)},
};
static const Cps2Load chips_vsavj_maincpu[] = {
    {"vm3j.03d", 0x2a2e74a4, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vm3j.04d", 0x1c2427bc, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vm3j.05a", 0x95ce88d5, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vm3j.06b", 0x2c4297e0, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vm3j.07b", 0xa38aaae7, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vm3j.08a", 0x5773e5c9, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vm3j.09b", 0xd064f8b9, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vm3j.10b", 0x434518e9, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vsavj_gfx[] = {
    {"vm3.13m", 0xfd8a11eb, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vm3.15m", 0xdd1e7d4e, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vm3.17m", 0x6b89445e, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vm3.19m", 0x3830fdc7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vm3.14m", 0xc1a28e6c, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vm3.16m", 0x194a7304, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vm3.18m", 0xdf9a9f47, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vm3.20m", 0xc22fc3d9, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vsavj_audiocpu[] = {
    {"vm3.01", 0xf778769b, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vm3.01", 0xf778769b, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vm3.02", 0xcc09faa1, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vsavj_qsound[] = {
    {"vm3.11m", 0xe80e956e, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"vm3.12m", 0x9cd71557, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_vsavj_key[] = {
    {"vsavj.key", 0x36d28ab8, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vsavj[] = {
    {"maincpu", 4194304, 0, chips_vsavj_maincpu, N(chips_vsavj_maincpu)},
    {"gfx", 33554432, 0, chips_vsavj_gfx, N(chips_vsavj_gfx)},
    {"audiocpu", 327680, 0, chips_vsavj_audiocpu, N(chips_vsavj_audiocpu)},
    {"qsound", 8388608, 0, chips_vsavj_qsound, N(chips_vsavj_qsound)},
    {"key", 32, 0, chips_vsavj_key, N(chips_vsavj_key)},
};
static const Cps2Load chips_vsava_maincpu[] = {
    {"vm3a.03d", 0x44c1198f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vm3a.04d", 0x2218b781, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vm3.05a", 0x4118e00f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vm3.06a", 0x2f4fd3a9, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vm3.07b", 0xcbda91b8, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vm3.08a", 0x6ca47259, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vm3.09b", 0xf4a339e3, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vm3.10b", 0xfffbb5b8, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vsava_gfx[] = {
    {"vm3.13m", 0xfd8a11eb, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vm3.15m", 0xdd1e7d4e, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vm3.17m", 0x6b89445e, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vm3.19m", 0x3830fdc7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vm3.14m", 0xc1a28e6c, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vm3.16m", 0x194a7304, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vm3.18m", 0xdf9a9f47, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vm3.20m", 0xc22fc3d9, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vsava_audiocpu[] = {
    {"vm3.01", 0xf778769b, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vm3.01", 0xf778769b, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vm3.02", 0xcc09faa1, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vsava_qsound[] = {
    {"vm3.11m", 0xe80e956e, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"vm3.12m", 0x9cd71557, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_vsava_key[] = {
    {"vsava.key", 0x8a3520f4, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vsava[] = {
    {"maincpu", 4194304, 0, chips_vsava_maincpu, N(chips_vsava_maincpu)},
    {"gfx", 33554432, 0, chips_vsava_gfx, N(chips_vsava_gfx)},
    {"audiocpu", 327680, 0, chips_vsava_audiocpu, N(chips_vsava_audiocpu)},
    {"qsound", 8388608, 0, chips_vsava_qsound, N(chips_vsava_qsound)},
    {"key", 32, 0, chips_vsava_key, N(chips_vsava_key)},
};
static const Cps2Load chips_vsavh_maincpu[] = {
    {"vm3h.03a", 0x7cc62df8, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vm3h.04d", 0xd716f3b5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vm3.05a", 0x4118e00f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vm3.06a", 0x2f4fd3a9, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vm3.07b", 0xcbda91b8, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vm3.08a", 0x6ca47259, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vm3.09b", 0xf4a339e3, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vm3.10b", 0xfffbb5b8, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vsavh_gfx[] = {
    {"vm3.13m", 0xfd8a11eb, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vm3.15m", 0xdd1e7d4e, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vm3.17m", 0x6b89445e, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vm3.19m", 0x3830fdc7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vm3.14m", 0xc1a28e6c, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vm3.16m", 0x194a7304, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vm3.18m", 0xdf9a9f47, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vm3.20m", 0xc22fc3d9, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vsavh_audiocpu[] = {
    {"vm3.01", 0xf778769b, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vm3.01", 0xf778769b, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vm3.02", 0xcc09faa1, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vsavh_qsound[] = {
    {"vm3.11m", 0xe80e956e, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"vm3.12m", 0x9cd71557, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_vsavh_key[] = {
    {"vsavh.key", 0xa7dd6409, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vsavh[] = {
    {"maincpu", 4194304, 0, chips_vsavh_maincpu, N(chips_vsavh_maincpu)},
    {"gfx", 33554432, 0, chips_vsavh_gfx, N(chips_vsavh_gfx)},
    {"audiocpu", 327680, 0, chips_vsavh_audiocpu, N(chips_vsavh_audiocpu)},
    {"qsound", 8388608, 0, chips_vsavh_qsound, N(chips_vsavh_qsound)},
    {"key", 32, 0, chips_vsavh_key, N(chips_vsavh_key)},
};
static const Cps2Load chips_vsavb_maincpu[] = {
    {"vm3b.03d", 0x22ffba4b, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vm3b.04d", 0x88624909, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vm3.05a", 0x4118e00f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vm3.06a", 0x2f4fd3a9, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vm3.07b", 0xcbda91b8, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vm3.08a", 0x6ca47259, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vm3.09b", 0xf4a339e3, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vm3.10b", 0xfffbb5b8, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vsavb_gfx[] = {
    {"vm3.13m", 0xfd8a11eb, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vm3.15m", 0xdd1e7d4e, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vm3.17m", 0x6b89445e, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vm3.19m", 0x3830fdc7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vm3.14m", 0xc1a28e6c, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vm3.16m", 0x194a7304, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vm3.18m", 0xdf9a9f47, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vm3.20m", 0xc22fc3d9, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vsavb_audiocpu[] = {
    {"vm3.01", 0xf778769b, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vm3.01", 0xf778769b, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vm3.02", 0xcc09faa1, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vsavb_qsound[] = {
    {"vm3.11m", 0xe80e956e, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"vm3.12m", 0x9cd71557, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_vsavb_key[] = {
    {"vsavb.key", 0x5274e635, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vsavb[] = {
    {"maincpu", 4194304, 0, chips_vsavb_maincpu, N(chips_vsavb_maincpu)},
    {"gfx", 33554432, 0, chips_vsavb_gfx, N(chips_vsavb_gfx)},
    {"audiocpu", 327680, 0, chips_vsavb_audiocpu, N(chips_vsavb_audiocpu)},
    {"qsound", 8388608, 0, chips_vsavb_qsound, N(chips_vsavb_qsound)},
    {"key", 32, 0, chips_vsavb_key, N(chips_vsavb_key)},
};
static const Cps2Load chips_mshvsf_maincpu[] = {
    {"mvse.03f", 0xb72dc199, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvse.04f", 0x6ef799f9, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvs.05a", 0x1a5de0cb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvs.06a", 0x959f3030, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvs.07b", 0x7f915bdb, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvs.08a", 0xc2813884, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvs.09b", 0x3ba08818, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvs.10b", 0xcf0dba98, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsf_gfx[] = {
    {"mvs.13m", 0x29b05fd9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvs.15m", 0xfaddccf1, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvs.17m", 0x97aaf4c7, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvs.19m", 0xcb70e915, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvs.14m", 0xb3b1972d, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvs.16m", 0x08aadb5d, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvs.18m", 0xc1228b35, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvs.20m", 0x366cc6c2, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshvsf_audiocpu[] = {
    {"mvs.01", 0x68252324, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvs.01", 0x68252324, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvs.02", 0xb34e773d, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshvsf_qsound[] = {
    {"mvs.11m", 0x86219770, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvs.12m", 0xf2fd7f68, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsf_key[] = {
    {"mshvsf.key", 0x64660867, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshvsf[] = {
    {"maincpu", 4194304, 0, chips_mshvsf_maincpu, N(chips_mshvsf_maincpu)},
    {"gfx", 33554432, 0, chips_mshvsf_gfx, N(chips_mshvsf_gfx)},
    {"audiocpu", 327680, 0, chips_mshvsf_audiocpu, N(chips_mshvsf_audiocpu)},
    {"qsound", 8388608, 0, chips_mshvsf_qsound, N(chips_mshvsf_qsound)},
    {"key", 32, 0, chips_mshvsf_key, N(chips_mshvsf_key)},
};
static const Cps2Load chips_mshvsfu_maincpu[] = {
    {"mvsu.03g", 0x0664ab15, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvsu.04g", 0x97e060ee, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvs.05d", 0x921fc542, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvs.06a", 0x959f3030, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvs.07b", 0x7f915bdb, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvs.08a", 0xc2813884, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvs.09b", 0x3ba08818, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvs.10b", 0xcf0dba98, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfu_gfx[] = {
    {"mvs.13m", 0x29b05fd9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvs.15m", 0xfaddccf1, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvs.17m", 0x97aaf4c7, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvs.19m", 0xcb70e915, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvs.14m", 0xb3b1972d, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvs.16m", 0x08aadb5d, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvs.18m", 0xc1228b35, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvs.20m", 0x366cc6c2, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshvsfu_audiocpu[] = {
    {"mvs.01", 0x68252324, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvs.01", 0x68252324, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvs.02", 0xb34e773d, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshvsfu_qsound[] = {
    {"mvs.11m", 0x86219770, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvs.12m", 0xf2fd7f68, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfu_key[] = {
    {"mshvsfu.key", 0x4c04797b, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshvsfu[] = {
    {"maincpu", 4194304, 0, chips_mshvsfu_maincpu, N(chips_mshvsfu_maincpu)},
    {"gfx", 33554432, 0, chips_mshvsfu_gfx, N(chips_mshvsfu_gfx)},
    {"audiocpu", 327680, 0, chips_mshvsfu_audiocpu, N(chips_mshvsfu_audiocpu)},
    {"qsound", 8388608, 0, chips_mshvsfu_qsound, N(chips_mshvsfu_qsound)},
    {"key", 32, 0, chips_mshvsfu_key, N(chips_mshvsfu_key)},
};
static const Cps2Load chips_mshvsfu1_maincpu[] = {
    {"mvsu.03d", 0xae60a66a, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvsu.04d", 0x91f67d8a, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvs.05a", 0x1a5de0cb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvs.06a", 0x959f3030, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvs.07b", 0x7f915bdb, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvs.08a", 0xc2813884, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvs.09b", 0x3ba08818, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvs.10b", 0xcf0dba98, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfu1_gfx[] = {
    {"mvs.13m", 0x29b05fd9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvs.15m", 0xfaddccf1, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvs.17m", 0x97aaf4c7, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvs.19m", 0xcb70e915, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvs.14m", 0xb3b1972d, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvs.16m", 0x08aadb5d, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvs.18m", 0xc1228b35, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvs.20m", 0x366cc6c2, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshvsfu1_audiocpu[] = {
    {"mvs.01", 0x68252324, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvs.01", 0x68252324, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvs.02", 0xb34e773d, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshvsfu1_qsound[] = {
    {"mvs.11m", 0x86219770, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvs.12m", 0xf2fd7f68, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfu1_key[] = {
    {"mshvsfu.key", 0x4c04797b, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshvsfu1[] = {
    {"maincpu", 4194304, 0, chips_mshvsfu1_maincpu, N(chips_mshvsfu1_maincpu)},
    {"gfx", 33554432, 0, chips_mshvsfu1_gfx, N(chips_mshvsfu1_gfx)},
    {"audiocpu", 327680, 0, chips_mshvsfu1_audiocpu, N(chips_mshvsfu1_audiocpu)},
    {"qsound", 8388608, 0, chips_mshvsfu1_qsound, N(chips_mshvsfu1_qsound)},
    {"key", 32, 0, chips_mshvsfu1_key, N(chips_mshvsfu1_key)},
};
static const Cps2Load chips_mshvsfj_maincpu[] = {
    {"mvsj.03i", 0xd8cbb691, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvsj.04i", 0x32741ace, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvs.05h", 0x77870dc3, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvs.06a", 0x959f3030, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvs.07b", 0x7f915bdb, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvs.08a", 0xc2813884, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvs.09b", 0x3ba08818, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvs.10b", 0xcf0dba98, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfj_gfx[] = {
    {"mvs.13m", 0x29b05fd9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvs.15m", 0xfaddccf1, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvs.17m", 0x97aaf4c7, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvs.19m", 0xcb70e915, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvs.14m", 0xb3b1972d, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvs.16m", 0x08aadb5d, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvs.18m", 0xc1228b35, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvs.20m", 0x366cc6c2, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshvsfj_audiocpu[] = {
    {"mvs.01", 0x68252324, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvs.01", 0x68252324, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvs.02", 0xb34e773d, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshvsfj_qsound[] = {
    {"mvs.11m", 0x86219770, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvs.12m", 0xf2fd7f68, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfj_key[] = {
    {"mshvsfj.key", 0x565eeebb, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshvsfj[] = {
    {"maincpu", 4194304, 0, chips_mshvsfj_maincpu, N(chips_mshvsfj_maincpu)},
    {"gfx", 33554432, 0, chips_mshvsfj_gfx, N(chips_mshvsfj_gfx)},
    {"audiocpu", 327680, 0, chips_mshvsfj_audiocpu, N(chips_mshvsfj_audiocpu)},
    {"qsound", 8388608, 0, chips_mshvsfj_qsound, N(chips_mshvsfj_qsound)},
    {"key", 32, 0, chips_mshvsfj_key, N(chips_mshvsfj_key)},
};
static const Cps2Load chips_mshvsfj1_maincpu[] = {
    {"mvsj.03h", 0xfbe2115f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvsj.04h", 0xb528a367, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvs.05g", 0x9515a245, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvs.06a", 0x959f3030, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvs.07b", 0x7f915bdb, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvs.08a", 0xc2813884, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvs.09b", 0x3ba08818, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvs.10b", 0xcf0dba98, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfj1_gfx[] = {
    {"mvs.13m", 0x29b05fd9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvs.15m", 0xfaddccf1, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvs.17m", 0x97aaf4c7, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvs.19m", 0xcb70e915, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvs.14m", 0xb3b1972d, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvs.16m", 0x08aadb5d, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvs.18m", 0xc1228b35, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvs.20m", 0x366cc6c2, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshvsfj1_audiocpu[] = {
    {"mvs.01", 0x68252324, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvs.01", 0x68252324, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvs.02", 0xb34e773d, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshvsfj1_qsound[] = {
    {"mvs.11m", 0x86219770, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvs.12m", 0xf2fd7f68, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfj1_key[] = {
    {"mshvsfj.key", 0x565eeebb, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshvsfj1[] = {
    {"maincpu", 4194304, 0, chips_mshvsfj1_maincpu, N(chips_mshvsfj1_maincpu)},
    {"gfx", 33554432, 0, chips_mshvsfj1_gfx, N(chips_mshvsfj1_gfx)},
    {"audiocpu", 327680, 0, chips_mshvsfj1_audiocpu, N(chips_mshvsfj1_audiocpu)},
    {"qsound", 8388608, 0, chips_mshvsfj1_qsound, N(chips_mshvsfj1_qsound)},
    {"key", 32, 0, chips_mshvsfj1_key, N(chips_mshvsfj1_key)},
};
static const Cps2Load chips_mshvsfj2_maincpu[] = {
    {"mvsj.03g", 0xfdfa7e26, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvsj.04g", 0xc921825f, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvs.05a", 0x1a5de0cb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvs.06a", 0x959f3030, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvs.07b", 0x7f915bdb, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvs.08a", 0xc2813884, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvs.09b", 0x3ba08818, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvs.10b", 0xcf0dba98, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfj2_gfx[] = {
    {"mvs.13m", 0x29b05fd9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvs.15m", 0xfaddccf1, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvs.17m", 0x97aaf4c7, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvs.19m", 0xcb70e915, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvs.14m", 0xb3b1972d, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvs.16m", 0x08aadb5d, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvs.18m", 0xc1228b35, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvs.20m", 0x366cc6c2, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshvsfj2_audiocpu[] = {
    {"mvs.01", 0x68252324, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvs.01", 0x68252324, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvs.02", 0xb34e773d, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshvsfj2_qsound[] = {
    {"mvs.11m", 0x86219770, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvs.12m", 0xf2fd7f68, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfj2_key[] = {
    {"mshvsfj.key", 0x565eeebb, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshvsfj2[] = {
    {"maincpu", 4194304, 0, chips_mshvsfj2_maincpu, N(chips_mshvsfj2_maincpu)},
    {"gfx", 33554432, 0, chips_mshvsfj2_gfx, N(chips_mshvsfj2_gfx)},
    {"audiocpu", 327680, 0, chips_mshvsfj2_audiocpu, N(chips_mshvsfj2_audiocpu)},
    {"qsound", 8388608, 0, chips_mshvsfj2_qsound, N(chips_mshvsfj2_qsound)},
    {"key", 32, 0, chips_mshvsfj2_key, N(chips_mshvsfj2_key)},
};
static const Cps2Load chips_mshvsfh_maincpu[] = {
    {"mvsh.03f", 0x4f60f41e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvsh.04f", 0xdc08ec12, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvs.05a", 0x1a5de0cb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvs.06a", 0x959f3030, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvs.07b", 0x7f915bdb, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvs.08a", 0xc2813884, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvs.09b", 0x3ba08818, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvs.10b", 0xcf0dba98, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfh_gfx[] = {
    {"mvs.13m", 0x29b05fd9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvs.15m", 0xfaddccf1, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvs.17m", 0x97aaf4c7, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvs.19m", 0xcb70e915, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvs.14m", 0xb3b1972d, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvs.16m", 0x08aadb5d, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvs.18m", 0xc1228b35, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvs.20m", 0x366cc6c2, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshvsfh_audiocpu[] = {
    {"mvs.01", 0x68252324, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvs.01", 0x68252324, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvs.02", 0xb34e773d, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshvsfh_qsound[] = {
    {"mvs.11m", 0x86219770, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvs.12m", 0xf2fd7f68, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfh_key[] = {
    {"mshvsfh.key", 0xb93d576f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshvsfh[] = {
    {"maincpu", 4194304, 0, chips_mshvsfh_maincpu, N(chips_mshvsfh_maincpu)},
    {"gfx", 33554432, 0, chips_mshvsfh_gfx, N(chips_mshvsfh_gfx)},
    {"audiocpu", 327680, 0, chips_mshvsfh_audiocpu, N(chips_mshvsfh_audiocpu)},
    {"qsound", 8388608, 0, chips_mshvsfh_qsound, N(chips_mshvsfh_qsound)},
    {"key", 32, 0, chips_mshvsfh_key, N(chips_mshvsfh_key)},
};
static const Cps2Load chips_mshvsfa_maincpu[] = {
    {"mvsa.03f", 0x5b863716, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvsa.04f", 0x4886e65f, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvs.05a", 0x1a5de0cb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvs.06a", 0x959f3030, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvs.07b", 0x7f915bdb, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvs.08a", 0xc2813884, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvs.09b", 0x3ba08818, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvs.10b", 0xcf0dba98, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfa_gfx[] = {
    {"mvs.13m", 0x29b05fd9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvs.15m", 0xfaddccf1, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvs.17m", 0x97aaf4c7, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvs.19m", 0xcb70e915, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvs.14m", 0xb3b1972d, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvs.16m", 0x08aadb5d, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvs.18m", 0xc1228b35, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvs.20m", 0x366cc6c2, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshvsfa_audiocpu[] = {
    {"mvs.01", 0x68252324, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvs.01", 0x68252324, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvs.02", 0xb34e773d, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshvsfa_qsound[] = {
    {"mvs.11m", 0x86219770, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvs.12m", 0xf2fd7f68, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfa_key[] = {
    {"mshvsfa.key", 0x6810a3af, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshvsfa[] = {
    {"maincpu", 4194304, 0, chips_mshvsfa_maincpu, N(chips_mshvsfa_maincpu)},
    {"gfx", 33554432, 0, chips_mshvsfa_gfx, N(chips_mshvsfa_gfx)},
    {"audiocpu", 327680, 0, chips_mshvsfa_audiocpu, N(chips_mshvsfa_audiocpu)},
    {"qsound", 8388608, 0, chips_mshvsfa_qsound, N(chips_mshvsfa_qsound)},
    {"key", 32, 0, chips_mshvsfa_key, N(chips_mshvsfa_key)},
};
static const Cps2Load chips_mshvsfa1_maincpu[] = {
    {"mvsa.03", 0x92ef1933, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvsa.04", 0x4b24373c, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvs.05", 0xac180c1c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvs.06a", 0x959f3030, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvs.07b", 0x7f915bdb, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvs.08a", 0xc2813884, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvs.09b", 0x3ba08818, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvs.10b", 0xcf0dba98, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfa1_gfx[] = {
    {"mvs.13m", 0x29b05fd9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvs.15m", 0xfaddccf1, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvs.17m", 0x97aaf4c7, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvs.19m", 0xcb70e915, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvs.14m", 0xb3b1972d, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvs.16m", 0x08aadb5d, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvs.18m", 0xc1228b35, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvs.20m", 0x366cc6c2, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshvsfa1_audiocpu[] = {
    {"mvs.01", 0x68252324, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvs.01", 0x68252324, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvs.02", 0xb34e773d, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshvsfa1_qsound[] = {
    {"mvs.11m", 0x86219770, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvs.12m", 0xf2fd7f68, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfa1_key[] = {
    {"mshvsfa.key", 0x6810a3af, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshvsfa1[] = {
    {"maincpu", 4194304, 0, chips_mshvsfa1_maincpu, N(chips_mshvsfa1_maincpu)},
    {"gfx", 33554432, 0, chips_mshvsfa1_gfx, N(chips_mshvsfa1_gfx)},
    {"audiocpu", 327680, 0, chips_mshvsfa1_audiocpu, N(chips_mshvsfa1_audiocpu)},
    {"qsound", 8388608, 0, chips_mshvsfa1_qsound, N(chips_mshvsfa1_qsound)},
    {"key", 32, 0, chips_mshvsfa1_key, N(chips_mshvsfa1_key)},
};
static const Cps2Load chips_mshvsfb_maincpu[] = {
    {"mvsb.03g", 0x143895ef, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvsb.04g", 0xdd8a886c, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvs.05d", 0x921fc542, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvs.06a", 0x959f3030, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvs.07b", 0x7f915bdb, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvs.08a", 0xc2813884, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvs.09b", 0x3ba08818, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvs.10b", 0xcf0dba98, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfb_gfx[] = {
    {"mvs.13m", 0x29b05fd9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvs.15m", 0xfaddccf1, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvs.17m", 0x97aaf4c7, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvs.19m", 0xcb70e915, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvs.14m", 0xb3b1972d, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvs.16m", 0x08aadb5d, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvs.18m", 0xc1228b35, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvs.20m", 0x366cc6c2, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshvsfb_audiocpu[] = {
    {"mvs.01", 0x68252324, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvs.01", 0x68252324, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvs.02", 0xb34e773d, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshvsfb_qsound[] = {
    {"mvs.11m", 0x86219770, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvs.12m", 0xf2fd7f68, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfb_key[] = {
    {"mshvsfb.key", 0x3f5bb6e4, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshvsfb[] = {
    {"maincpu", 4194304, 0, chips_mshvsfb_maincpu, N(chips_mshvsfb_maincpu)},
    {"gfx", 33554432, 0, chips_mshvsfb_gfx, N(chips_mshvsfb_gfx)},
    {"audiocpu", 327680, 0, chips_mshvsfb_audiocpu, N(chips_mshvsfb_audiocpu)},
    {"qsound", 8388608, 0, chips_mshvsfb_qsound, N(chips_mshvsfb_qsound)},
    {"key", 32, 0, chips_mshvsfb_key, N(chips_mshvsfb_key)},
};
static const Cps2Load chips_mshvsfb1_maincpu[] = {
    {"mvsb.03f", 0x9c4bb950, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvsb.04f", 0xd3320d13, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvs.05a", 0x1a5de0cb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvs.06a", 0x959f3030, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvs.07b", 0x7f915bdb, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvs.08a", 0xc2813884, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvs.09b", 0x3ba08818, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvs.10b", 0xcf0dba98, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfb1_gfx[] = {
    {"mvs.13m", 0x29b05fd9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvs.15m", 0xfaddccf1, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvs.17m", 0x97aaf4c7, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvs.19m", 0xcb70e915, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvs.14m", 0xb3b1972d, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvs.16m", 0x08aadb5d, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvs.18m", 0xc1228b35, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvs.20m", 0x366cc6c2, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshvsfb1_audiocpu[] = {
    {"mvs.01", 0x68252324, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvs.01", 0x68252324, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvs.02", 0xb34e773d, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshvsfb1_qsound[] = {
    {"mvs.11m", 0x86219770, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvs.12m", 0xf2fd7f68, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfb1_key[] = {
    {"mshvsfb.key", 0x3f5bb6e4, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshvsfb1[] = {
    {"maincpu", 4194304, 0, chips_mshvsfb1_maincpu, N(chips_mshvsfb1_maincpu)},
    {"gfx", 33554432, 0, chips_mshvsfb1_gfx, N(chips_mshvsfb1_gfx)},
    {"audiocpu", 327680, 0, chips_mshvsfb1_audiocpu, N(chips_mshvsfb1_audiocpu)},
    {"qsound", 8388608, 0, chips_mshvsfb1_qsound, N(chips_mshvsfb1_qsound)},
    {"key", 32, 0, chips_mshvsfb1_key, N(chips_mshvsfb1_key)},
};
static const Cps2Load chips_csclub_maincpu[] = {
    {"csce.03a", 0x824082be, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"csce.04a", 0x74e6a4fe, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"csce.05a", 0x8ae0df19, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"csce.06a", 0x51f2f0d3, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"csce.07a", 0x003968fd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_csclub_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"csc.73", 0x335f07c3, 524288, 0, 8388608, 524288, CPS2_WORD64},
    {"csc.74", 0xab215357, 524288, 0, 10485760, 524288, CPS2_WORD64},
    {"csc.75", 0xa2367381, 524288, 0, 12582912, 524288, CPS2_WORD64},
    {"csc.76", 0x728aac1f, 524288, 0, 14680064, 524288, CPS2_WORD64},
    {"csc.63", 0x3711b8ca, 524288, 0, 8388610, 524288, CPS2_WORD64},
    {"csc.64", 0x828a06d8, 524288, 0, 10485762, 524288, CPS2_WORD64},
    {"csc.65", 0x86ee4569, 524288, 0, 12582914, 524288, CPS2_WORD64},
    {"csc.66", 0xc24f577f, 524288, 0, 14680066, 524288, CPS2_WORD64},
    {"csc.83", 0x0750d12a, 524288, 0, 8388612, 524288, CPS2_WORD64},
    {"csc.84", 0x90a92f39, 524288, 0, 10485764, 524288, CPS2_WORD64},
    {"csc.85", 0xd08ab012, 524288, 0, 12582916, 524288, CPS2_WORD64},
    {"csc.86", 0x41652583, 524288, 0, 14680068, 524288, CPS2_WORD64},
    {"csc.93", 0xa756c7f7, 524288, 0, 8388614, 524288, CPS2_WORD64},
    {"csc.94", 0xfb7ccc73, 524288, 0, 10485766, 524288, CPS2_WORD64},
    {"csc.95", 0x4d014297, 524288, 0, 12582918, 524288, CPS2_WORD64},
    {"csc.96", 0x6754b1ef, 524288, 0, 14680070, 524288, CPS2_WORD64},
};
static const Cps2Load chips_csclub_audiocpu[] = {
    {"csc.01", 0xee162111, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"csc.01", 0xee162111, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_csclub_qsound[] = {
    {"csc.51", 0x5a52afd5, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"csc.52", 0x1408a811, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"csc.53", 0x4fb9f57c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"csc.54", 0x9a8f40ec, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"csc.55", 0x91529a91, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"csc.56", 0x9a345334, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"csc.57", 0xaedc27f2, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"csc.58", 0x2300b7b3, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_csclub_key[] = {
    {"csclub.key", 0x903907d7, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_csclub[] = {
    {"maincpu", 4194304, 0, chips_csclub_maincpu, N(chips_csclub_maincpu)},
    {"gfx", 16777216, 0, chips_csclub_gfx, N(chips_csclub_gfx)},
    {"audiocpu", 327680, 0, chips_csclub_audiocpu, N(chips_csclub_audiocpu)},
    {"qsound", 4194304, 0, chips_csclub_qsound, N(chips_csclub_qsound)},
    {"key", 32, 0, chips_csclub_key, N(chips_csclub_key)},
};
static const Cps2Load chips_csclub1_maincpu[] = {
    {"csce.03", 0xf2c852ef, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"csce.04", 0x1184530f, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"csce.05", 0x804e2b6b, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"csce.06", 0x09277cb9, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"csc.07", 0x01b05caa, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_csclub1_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"csc.14m", 0xe8904afa, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"csc.16m", 0xc98c8079, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"csc.18m", 0xc030df5a, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"csc.20m", 0xb4e55863, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_csclub1_audiocpu[] = {
    {"csc.01", 0xee162111, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"csc.01", 0xee162111, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_csclub1_qsound[] = {
    {"csc.11m", 0xa027b827, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"csc.12m", 0xcb7f6e55, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_csclub1_key[] = {
    {"csclub.key", 0x903907d7, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_csclub1[] = {
    {"maincpu", 4194304, 0, chips_csclub1_maincpu, N(chips_csclub1_maincpu)},
    {"gfx", 16777216, 0, chips_csclub1_gfx, N(chips_csclub1_gfx)},
    {"audiocpu", 327680, 0, chips_csclub1_audiocpu, N(chips_csclub1_audiocpu)},
    {"qsound", 4194304, 0, chips_csclub1_qsound, N(chips_csclub1_qsound)},
    {"key", 32, 0, chips_csclub1_key, N(chips_csclub1_key)},
};
static const Cps2Load chips_cscluba_maincpu[] = {
    {"csca.03", 0xb6acd708, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"csca.04", 0xd44ae35f, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"csca.05", 0x8da76aec, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"csca.06", 0xa1b7b1ee, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"csc.07", 0x01b05caa, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_cscluba_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"csc.14m", 0xe8904afa, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"csc.16m", 0xc98c8079, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"csc.18m", 0xc030df5a, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"csc.20m", 0xb4e55863, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_cscluba_audiocpu[] = {
    {"csc.01", 0xee162111, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"csc.01", 0xee162111, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_cscluba_qsound[] = {
    {"csc.11m", 0xa027b827, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"csc.12m", 0xcb7f6e55, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_cscluba_key[] = {
    {"cscluba.key", 0x591908dc, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_cscluba[] = {
    {"maincpu", 4194304, 0, chips_cscluba_maincpu, N(chips_cscluba_maincpu)},
    {"gfx", 16777216, 0, chips_cscluba_gfx, N(chips_cscluba_gfx)},
    {"audiocpu", 327680, 0, chips_cscluba_audiocpu, N(chips_cscluba_audiocpu)},
    {"qsound", 4194304, 0, chips_cscluba_qsound, N(chips_cscluba_qsound)},
    {"key", 32, 0, chips_cscluba_key, N(chips_cscluba_key)},
};
static const Cps2Load chips_csclubj_maincpu[] = {
    {"cscj.03", 0xec4ddaa2, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"cscj.04", 0x60c632bb, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"cscj.05", 0xad042003, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"cscj.06", 0x169e4d40, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"csc.07", 0x01b05caa, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_csclubj_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"csc.14m", 0xe8904afa, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"csc.16m", 0xc98c8079, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"csc.18m", 0xc030df5a, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"csc.20m", 0xb4e55863, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_csclubj_audiocpu[] = {
    {"csc.01", 0xee162111, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"csc.01", 0xee162111, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_csclubj_qsound[] = {
    {"csc.11m", 0xa027b827, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"csc.12m", 0xcb7f6e55, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_csclubj_key[] = {
    {"csclubj.key", 0x519a04db, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_csclubj[] = {
    {"maincpu", 4194304, 0, chips_csclubj_maincpu, N(chips_csclubj_maincpu)},
    {"gfx", 16777216, 0, chips_csclubj_gfx, N(chips_csclubj_gfx)},
    {"audiocpu", 327680, 0, chips_csclubj_audiocpu, N(chips_csclubj_audiocpu)},
    {"qsound", 4194304, 0, chips_csclubj_qsound, N(chips_csclubj_qsound)},
    {"key", 32, 0, chips_csclubj_key, N(chips_csclubj_key)},
};
static const Cps2Load chips_csclubjy_maincpu[] = {
    {"cscj.03", 0xec4ddaa2, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"cscj.04", 0x60c632bb, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"cscj.05", 0xad042003, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"cscj.06", 0x169e4d40, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"csc.07", 0x01b05caa, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_csclubjy_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"csc.73", 0x335f07c3, 524288, 0, 8388608, 524288, CPS2_WORD64},
    {"csc.74", 0xab215357, 524288, 0, 10485760, 524288, CPS2_WORD64},
    {"csc.75", 0xa2367381, 524288, 0, 12582912, 524288, CPS2_WORD64},
    {"csc.76", 0x728aac1f, 524288, 0, 14680064, 524288, CPS2_WORD64},
    {"csc.63", 0x3711b8ca, 524288, 0, 8388610, 524288, CPS2_WORD64},
    {"csc.64", 0x828a06d8, 524288, 0, 10485762, 524288, CPS2_WORD64},
    {"csc.65", 0x86ee4569, 524288, 0, 12582914, 524288, CPS2_WORD64},
    {"csc.66", 0xc24f577f, 524288, 0, 14680066, 524288, CPS2_WORD64},
    {"csc.83", 0x0750d12a, 524288, 0, 8388612, 524288, CPS2_WORD64},
    {"csc.84", 0x90a92f39, 524288, 0, 10485764, 524288, CPS2_WORD64},
    {"csc.85", 0xd08ab012, 524288, 0, 12582916, 524288, CPS2_WORD64},
    {"csc.86", 0x41652583, 524288, 0, 14680068, 524288, CPS2_WORD64},
    {"csc.93", 0xa756c7f7, 524288, 0, 8388614, 524288, CPS2_WORD64},
    {"csc.94", 0xfb7ccc73, 524288, 0, 10485766, 524288, CPS2_WORD64},
    {"csc.95", 0x4d014297, 524288, 0, 12582918, 524288, CPS2_WORD64},
    {"csc.96", 0x6754b1ef, 524288, 0, 14680070, 524288, CPS2_WORD64},
};
static const Cps2Load chips_csclubjy_audiocpu[] = {
    {"csc.01", 0xee162111, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"csc.01", 0xee162111, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_csclubjy_qsound[] = {
    {"csc.51", 0x5a52afd5, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"csc.52", 0x1408a811, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"csc.53", 0x4fb9f57c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"csc.54", 0x9a8f40ec, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"csc.55", 0x91529a91, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"csc.56", 0x9a345334, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"csc.57", 0xaedc27f2, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"csc.58", 0x2300b7b3, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_csclubjy_key[] = {
    {"csclubj.key", 0x519a04db, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_csclubjy[] = {
    {"maincpu", 4194304, 0, chips_csclubjy_maincpu, N(chips_csclubjy_maincpu)},
    {"gfx", 16777216, 0, chips_csclubjy_gfx, N(chips_csclubjy_gfx)},
    {"audiocpu", 327680, 0, chips_csclubjy_audiocpu, N(chips_csclubjy_audiocpu)},
    {"qsound", 4194304, 0, chips_csclubjy_qsound, N(chips_csclubjy_qsound)},
    {"key", 32, 0, chips_csclubjy_key, N(chips_csclubjy_key)},
};
static const Cps2Load chips_csclubh_maincpu[] = {
    {"csch.03", 0x0dd7e46d, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"csch.04", 0x486e8143, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"csch.05", 0x9e509dfb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"csch.06", 0x817ba313, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"csc.07", 0x01b05caa, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_csclubh_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"csc.14m", 0xe8904afa, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"csc.16m", 0xc98c8079, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"csc.18m", 0xc030df5a, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"csc.20m", 0xb4e55863, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_csclubh_audiocpu[] = {
    {"csc.01", 0xee162111, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"csc.01", 0xee162111, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_csclubh_qsound[] = {
    {"csc.11m", 0xa027b827, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"csc.12m", 0xcb7f6e55, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_csclubh_key[] = {
    {"csclubh.key", 0xb0adc39e, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_csclubh[] = {
    {"maincpu", 4194304, 0, chips_csclubh_maincpu, N(chips_csclubh_maincpu)},
    {"gfx", 16777216, 0, chips_csclubh_gfx, N(chips_csclubh_gfx)},
    {"audiocpu", 327680, 0, chips_csclubh_audiocpu, N(chips_csclubh_audiocpu)},
    {"qsound", 4194304, 0, chips_csclubh_qsound, N(chips_csclubh_qsound)},
    {"key", 32, 0, chips_csclubh_key, N(chips_csclubh_key)},
};
static const Cps2Load chips_sgemf_maincpu[] = {
    {"pcfu.03", 0xac2e8566, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pcf.04", 0xf4314c96, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pcf.05", 0x215655f6, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pcf.06", 0xea6f13ea, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"pcf.07", 0x5ac6d5ea, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sgemf_gfx[] = {
    {"pcf.13m", 0x22d72ab9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pcf.15m", 0x16a4813c, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pcf.17m", 0x1097e035, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pcf.19m", 0xd362d874, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"pcf.14m", 0x0383897c, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"pcf.16m", 0x76f91084, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"pcf.18m", 0x756c3754, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"pcf.20m", 0x9ec9277d, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sgemf_audiocpu[] = {
    {"pcf.01", 0x254e5f33, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pcf.01", 0x254e5f33, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pcf.02", 0x6902f4f9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sgemf_qsound[] = {
    {"pcf.11m", 0xa5dea005, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"pcf.12m", 0x4ce235fe, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sgemf_key[] = {
    {"sgemf.key", 0x3d604021, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sgemf[] = {
    {"maincpu", 4194304, 0, chips_sgemf_maincpu, N(chips_sgemf_maincpu)},
    {"gfx", 20971520, 0, chips_sgemf_gfx, N(chips_sgemf_gfx)},
    {"audiocpu", 327680, 0, chips_sgemf_audiocpu, N(chips_sgemf_audiocpu)},
    {"qsound", 8388608, 0, chips_sgemf_qsound, N(chips_sgemf_qsound)},
    {"key", 32, 0, chips_sgemf_key, N(chips_sgemf_key)},
};
static const Cps2Load chips_pfghtj_maincpu[] = {
    {"pcfj.03", 0x681da43e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pcf.04", 0xf4314c96, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pcf.05", 0x215655f6, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pcf.06", 0xea6f13ea, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"pcf.07", 0x5ac6d5ea, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_pfghtj_gfx[] = {
    {"pcf.13m", 0x22d72ab9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pcf.15m", 0x16a4813c, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pcf.17m", 0x1097e035, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pcf.19m", 0xd362d874, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"pcf.14m", 0x0383897c, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"pcf.16m", 0x76f91084, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"pcf.18m", 0x756c3754, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"pcf.20m", 0x9ec9277d, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_pfghtj_audiocpu[] = {
    {"pcf.01", 0x254e5f33, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pcf.01", 0x254e5f33, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pcf.02", 0x6902f4f9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_pfghtj_qsound[] = {
    {"pcf.11m", 0xa5dea005, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"pcf.12m", 0x4ce235fe, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_pfghtj_key[] = {
    {"pfghtj.key", 0x62297638, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_pfghtj[] = {
    {"maincpu", 4194304, 0, chips_pfghtj_maincpu, N(chips_pfghtj_maincpu)},
    {"gfx", 20971520, 0, chips_pfghtj_gfx, N(chips_pfghtj_gfx)},
    {"audiocpu", 327680, 0, chips_pfghtj_audiocpu, N(chips_pfghtj_audiocpu)},
    {"qsound", 8388608, 0, chips_pfghtj_qsound, N(chips_pfghtj_qsound)},
    {"key", 32, 0, chips_pfghtj_key, N(chips_pfghtj_key)},
};
static const Cps2Load chips_sgemfa_maincpu[] = {
    {"pcfa.03", 0xe17c089a, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pcf.04", 0xf4314c96, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pcf.05", 0x215655f6, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pcf.06", 0xea6f13ea, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"pcf.07", 0x5ac6d5ea, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sgemfa_gfx[] = {
    {"pcf.13m", 0x22d72ab9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pcf.15m", 0x16a4813c, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pcf.17m", 0x1097e035, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pcf.19m", 0xd362d874, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"pcf.14m", 0x0383897c, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"pcf.16m", 0x76f91084, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"pcf.18m", 0x756c3754, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"pcf.20m", 0x9ec9277d, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sgemfa_audiocpu[] = {
    {"pcf.01", 0x254e5f33, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pcf.01", 0x254e5f33, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pcf.02", 0x6902f4f9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sgemfa_qsound[] = {
    {"pcf.11m", 0xa5dea005, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"pcf.12m", 0x4ce235fe, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sgemfa_key[] = {
    {"sgemfa.key", 0xdd513738, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sgemfa[] = {
    {"maincpu", 4194304, 0, chips_sgemfa_maincpu, N(chips_sgemfa_maincpu)},
    {"gfx", 20971520, 0, chips_sgemfa_gfx, N(chips_sgemfa_gfx)},
    {"audiocpu", 327680, 0, chips_sgemfa_audiocpu, N(chips_sgemfa_audiocpu)},
    {"qsound", 8388608, 0, chips_sgemfa_qsound, N(chips_sgemfa_qsound)},
    {"key", 32, 0, chips_sgemfa_key, N(chips_sgemfa_key)},
};
static const Cps2Load chips_sgemfh_maincpu[] = {
    {"pcfh.03", 0xe9103347, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pcf.04", 0xf4314c96, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pcf.05", 0x215655f6, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pcf.06", 0xea6f13ea, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"pcf.07", 0x5ac6d5ea, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sgemfh_gfx[] = {
    {"pcf.13m", 0x22d72ab9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pcf.15m", 0x16a4813c, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pcf.17m", 0x1097e035, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pcf.19m", 0xd362d874, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"pcf.14m", 0x0383897c, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"pcf.16m", 0x76f91084, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"pcf.18m", 0x756c3754, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"pcf.20m", 0x9ec9277d, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sgemfh_audiocpu[] = {
    {"pcf.01", 0x254e5f33, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pcf.01", 0x254e5f33, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pcf.02", 0x6902f4f9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sgemfh_qsound[] = {
    {"pcf.11m", 0xa5dea005, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"pcf.12m", 0x4ce235fe, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sgemfh_key[] = {
    {"sgemfh.key", 0xf97f4b7d, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sgemfh[] = {
    {"maincpu", 4194304, 0, chips_sgemfh_maincpu, N(chips_sgemfh_maincpu)},
    {"gfx", 20971520, 0, chips_sgemfh_gfx, N(chips_sgemfh_gfx)},
    {"audiocpu", 327680, 0, chips_sgemfh_audiocpu, N(chips_sgemfh_audiocpu)},
    {"qsound", 8388608, 0, chips_sgemfh_qsound, N(chips_sgemfh_qsound)},
    {"key", 32, 0, chips_sgemfh_key, N(chips_sgemfh_key)},
};
static const Cps2Load chips_vhunt2_maincpu[] = {
    {"vh2j.03a", 0x9ae8f186, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vh2j.04a", 0xe2fabf53, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vh2j.05", 0xde34f624, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vh2j.06", 0x6a3b9897, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vh2j.07", 0xb021c029, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vh2j.08", 0xac873dff, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vh2j.09", 0xeaefce9c, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vh2j.10", 0x11730952, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vhunt2_gfx[] = {
    {"vh2.13m", 0x3b02ddaa, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vh2.15m", 0x4e40de66, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vh2.17m", 0xb31d00c9, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vh2.19m", 0x149be3ab, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vh2.14m", 0xcd09bd63, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vh2.16m", 0xe0182c15, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vh2.18m", 0x778dc4f6, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vh2.20m", 0x605d9d1d, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vhunt2_audiocpu[] = {
    {"vh2.01", 0x67b9f779, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vh2.01", 0x67b9f779, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vh2.02", 0xaaf15fcb, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vhunt2_qsound[] = {
    {"vh2.11m", 0x38922efd, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"vh2.12m", 0x6e2430af, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_vhunt2_key[] = {
    {"vhunt2.key", 0x61306b20, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vhunt2[] = {
    {"maincpu", 4194304, 0, chips_vhunt2_maincpu, N(chips_vhunt2_maincpu)},
    {"gfx", 33554432, 0, chips_vhunt2_gfx, N(chips_vhunt2_gfx)},
    {"audiocpu", 327680, 0, chips_vhunt2_audiocpu, N(chips_vhunt2_audiocpu)},
    {"qsound", 8388608, 0, chips_vhunt2_qsound, N(chips_vhunt2_qsound)},
    {"key", 32, 0, chips_vhunt2_key, N(chips_vhunt2_key)},
};
static const Cps2Load chips_vhunt2r1_maincpu[] = {
    {"vh2j.03", 0x1a5feb13, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vh2j.04", 0x434611a5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vh2j.05", 0xde34f624, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vh2j.06", 0x6a3b9897, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vh2j.07", 0xb021c029, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vh2j.08", 0xac873dff, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vh2j.09", 0xeaefce9c, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vh2j.10", 0x11730952, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vhunt2r1_gfx[] = {
    {"vh2.13m", 0x3b02ddaa, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vh2.15m", 0x4e40de66, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vh2.17m", 0xb31d00c9, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vh2.19m", 0x149be3ab, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vh2.14m", 0xcd09bd63, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vh2.16m", 0xe0182c15, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vh2.18m", 0x778dc4f6, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vh2.20m", 0x605d9d1d, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vhunt2r1_audiocpu[] = {
    {"vh2.01", 0x67b9f779, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vh2.01", 0x67b9f779, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vh2.02", 0xaaf15fcb, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vhunt2r1_qsound[] = {
    {"vh2.11m", 0x38922efd, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"vh2.12m", 0x6e2430af, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_vhunt2r1_key[] = {
    {"vhunt2.key", 0x61306b20, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vhunt2r1[] = {
    {"maincpu", 4194304, 0, chips_vhunt2r1_maincpu, N(chips_vhunt2r1_maincpu)},
    {"gfx", 33554432, 0, chips_vhunt2r1_gfx, N(chips_vhunt2r1_gfx)},
    {"audiocpu", 327680, 0, chips_vhunt2r1_audiocpu, N(chips_vhunt2r1_audiocpu)},
    {"qsound", 8388608, 0, chips_vhunt2r1_qsound, N(chips_vhunt2r1_qsound)},
    {"key", 32, 0, chips_vhunt2r1_key, N(chips_vhunt2r1_key)},
};
static const Cps2Load chips_vsav2_maincpu[] = {
    {"vs2j.03", 0x89fd86b4, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vs2j.04", 0x107c091b, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vs2j.05", 0x61979638, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vs2j.06", 0xf37c5bc2, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vs2j.07", 0x8f885809, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vs2j.08", 0x2018c120, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vs2j.09", 0xfac3c217, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vs2j.10", 0xeb490213, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vsav2_gfx[] = {
    {"vs2.13m", 0x5c852f52, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vs2.15m", 0xa20f58af, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vs2.17m", 0x39db59ad, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vs2.19m", 0x00c763a7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vs2.14m", 0xcd09bd63, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vs2.16m", 0xe0182c15, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vs2.18m", 0x778dc4f6, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vs2.20m", 0x605d9d1d, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vsav2_audiocpu[] = {
    {"vs2.01", 0x35190139, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vs2.01", 0x35190139, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vs2.02", 0xc32dba09, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vsav2_qsound[] = {
    {"vs2.11m", 0xd67e47b7, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"vs2.12m", 0x6d020a14, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_vsav2_key[] = {
    {"vsav2.key", 0x289028ce, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vsav2[] = {
    {"maincpu", 4194304, 0, chips_vsav2_maincpu, N(chips_vsav2_maincpu)},
    {"gfx", 33554432, 0, chips_vsav2_gfx, N(chips_vsav2_gfx)},
    {"audiocpu", 327680, 0, chips_vsav2_audiocpu, N(chips_vsav2_audiocpu)},
    {"qsound", 8388608, 0, chips_vsav2_qsound, N(chips_vsav2_qsound)},
    {"key", 32, 0, chips_vsav2_key, N(chips_vsav2_key)},
};
static const Cps2Load chips_mvsc_maincpu[] = {
    {"mvce.03a", 0x824e4a90, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvce.04a", 0x436c5a4e, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvc.05a", 0x2d8c8e86, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvc.06a", 0x8528e1f5, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvc.07", 0xc3baa32b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvc.08", 0xbc002fcd, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvc.09", 0xc67b26df, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvc.10", 0x0fdd1e26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mvsc_gfx[] = {
    {"mvc.13m", 0xfa5f74bc, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvc.15m", 0x71938a8f, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvc.17m", 0x92741d07, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvc.19m", 0xbcb72fc6, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvc.14m", 0x7f1df4e4, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvc.16m", 0x90bd3203, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvc.18m", 0x67aaf727, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvc.20m", 0x8b0bade8, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mvsc_audiocpu[] = {
    {"mvc.01", 0x41629e95, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvc.01", 0x41629e95, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvc.02", 0x963abf6b, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mvsc_qsound[] = {
    {"mvc.11m", 0x850fe663, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvc.12m", 0x7ccb1896, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mvsc_key[] = {
    {"mvsc.key", 0x7e101e09, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mvsc[] = {
    {"maincpu", 4194304, 0, chips_mvsc_maincpu, N(chips_mvsc_maincpu)},
    {"gfx", 33554432, 0, chips_mvsc_gfx, N(chips_mvsc_gfx)},
    {"audiocpu", 327680, 0, chips_mvsc_audiocpu, N(chips_mvsc_audiocpu)},
    {"qsound", 8388608, 0, chips_mvsc_qsound, N(chips_mvsc_qsound)},
    {"key", 32, 0, chips_mvsc_key, N(chips_mvsc_key)},
};
static const Cps2Load chips_mvscr1_maincpu[] = {
    {"mvce.03", 0xe0633fc0, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvce.04", 0xa450a251, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvc.05", 0x7db71ce9, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvc.06", 0x4b0b6d3e, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvc.07", 0xc3baa32b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvc.08", 0xbc002fcd, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvc.09", 0xc67b26df, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvc.10", 0x0fdd1e26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mvscr1_gfx[] = {
    {"mvc.13m", 0xfa5f74bc, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvc.15m", 0x71938a8f, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvc.17m", 0x92741d07, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvc.19m", 0xbcb72fc6, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvc.14m", 0x7f1df4e4, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvc.16m", 0x90bd3203, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvc.18m", 0x67aaf727, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvc.20m", 0x8b0bade8, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mvscr1_audiocpu[] = {
    {"mvc.01", 0x41629e95, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvc.01", 0x41629e95, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvc.02", 0x963abf6b, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mvscr1_qsound[] = {
    {"mvc.11m", 0x850fe663, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvc.12m", 0x7ccb1896, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mvscr1_key[] = {
    {"mvsc.key", 0x7e101e09, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mvscr1[] = {
    {"maincpu", 4194304, 0, chips_mvscr1_maincpu, N(chips_mvscr1_maincpu)},
    {"gfx", 33554432, 0, chips_mvscr1_gfx, N(chips_mvscr1_gfx)},
    {"audiocpu", 327680, 0, chips_mvscr1_audiocpu, N(chips_mvscr1_audiocpu)},
    {"qsound", 8388608, 0, chips_mvscr1_qsound, N(chips_mvscr1_qsound)},
    {"key", 32, 0, chips_mvscr1_key, N(chips_mvscr1_key)},
};
static const Cps2Load chips_mvscu_maincpu[] = {
    {"mvcu.03d", 0xc6007557, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvcu.04d", 0x724b2b20, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvc.05a", 0x2d8c8e86, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvc.06a", 0x8528e1f5, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvc.07", 0xc3baa32b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvc.08", 0xbc002fcd, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvc.09", 0xc67b26df, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvc.10", 0x0fdd1e26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mvscu_gfx[] = {
    {"mvc.13m", 0xfa5f74bc, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvc.15m", 0x71938a8f, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvc.17m", 0x92741d07, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvc.19m", 0xbcb72fc6, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvc.14m", 0x7f1df4e4, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvc.16m", 0x90bd3203, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvc.18m", 0x67aaf727, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvc.20m", 0x8b0bade8, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mvscu_audiocpu[] = {
    {"mvc.01", 0x41629e95, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvc.01", 0x41629e95, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvc.02", 0x963abf6b, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mvscu_qsound[] = {
    {"mvc.11m", 0x850fe663, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvc.12m", 0x7ccb1896, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mvscu_key[] = {
    {"mvscu.key", 0xa83db333, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mvscu[] = {
    {"maincpu", 4194304, 0, chips_mvscu_maincpu, N(chips_mvscu_maincpu)},
    {"gfx", 33554432, 0, chips_mvscu_gfx, N(chips_mvscu_gfx)},
    {"audiocpu", 327680, 0, chips_mvscu_audiocpu, N(chips_mvscu_audiocpu)},
    {"qsound", 8388608, 0, chips_mvscu_qsound, N(chips_mvscu_qsound)},
    {"key", 32, 0, chips_mvscu_key, N(chips_mvscu_key)},
};
static const Cps2Load chips_mvscur1_maincpu[] = {
    {"mvcu.03", 0x13f2be57, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvcu.04", 0x5e9b380d, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvcu.05", 0x12f321be, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvcu.06", 0x2f1524bc, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvcu.07", 0x5fdecadb, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvc.08", 0xbc002fcd, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvc.09", 0xc67b26df, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvcu.10", 0x4f36cd63, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mvscur1_gfx[] = {
    {"mvc.13m", 0xfa5f74bc, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvc.15m", 0x71938a8f, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvc.17m", 0x92741d07, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvc.19m", 0xbcb72fc6, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvc.14m", 0x7f1df4e4, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvc.16m", 0x90bd3203, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvc.18m", 0x67aaf727, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvc.20m", 0x8b0bade8, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mvscur1_audiocpu[] = {
    {"mvc.01", 0x41629e95, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvc.01", 0x41629e95, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvc.02", 0x963abf6b, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mvscur1_qsound[] = {
    {"mvc.11m", 0x850fe663, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvc.12m", 0x7ccb1896, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mvscur1_key[] = {
    {"mvscu.key", 0xa83db333, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mvscur1[] = {
    {"maincpu", 4194304, 0, chips_mvscur1_maincpu, N(chips_mvscur1_maincpu)},
    {"gfx", 33554432, 0, chips_mvscur1_gfx, N(chips_mvscur1_gfx)},
    {"audiocpu", 327680, 0, chips_mvscur1_audiocpu, N(chips_mvscur1_audiocpu)},
    {"qsound", 8388608, 0, chips_mvscur1_qsound, N(chips_mvscur1_qsound)},
    {"key", 32, 0, chips_mvscur1_key, N(chips_mvscur1_key)},
};
static const Cps2Load chips_mvscj_maincpu[] = {
    {"mvcj.03a", 0x3df18879, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvcj.04a", 0x07d212e8, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvc.05a", 0x2d8c8e86, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvc.06a", 0x8528e1f5, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvc.07", 0xc3baa32b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvc.08", 0xbc002fcd, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvc.09", 0xc67b26df, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvc.10", 0x0fdd1e26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mvscj_gfx[] = {
    {"mvc.13m", 0xfa5f74bc, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvc.15m", 0x71938a8f, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvc.17m", 0x92741d07, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvc.19m", 0xbcb72fc6, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvc.14m", 0x7f1df4e4, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvc.16m", 0x90bd3203, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvc.18m", 0x67aaf727, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvc.20m", 0x8b0bade8, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mvscj_audiocpu[] = {
    {"mvc.01", 0x41629e95, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvc.01", 0x41629e95, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvc.02", 0x963abf6b, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mvscj_qsound[] = {
    {"mvc.11m", 0x850fe663, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvc.12m", 0x7ccb1896, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mvscj_key[] = {
    {"mvscj.key", 0x9dedbcaf, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mvscj[] = {
    {"maincpu", 4194304, 0, chips_mvscj_maincpu, N(chips_mvscj_maincpu)},
    {"gfx", 33554432, 0, chips_mvscj_gfx, N(chips_mvscj_gfx)},
    {"audiocpu", 327680, 0, chips_mvscj_audiocpu, N(chips_mvscj_audiocpu)},
    {"qsound", 8388608, 0, chips_mvscj_qsound, N(chips_mvscj_qsound)},
    {"key", 32, 0, chips_mvscj_key, N(chips_mvscj_key)},
};
static const Cps2Load chips_mvscjr1_maincpu[] = {
    {"mvcj.03", 0x2164213f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvcj.04", 0xc905c86f, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvc.05", 0x7db71ce9, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvc.06", 0x4b0b6d3e, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvc.07", 0xc3baa32b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvc.08", 0xbc002fcd, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvc.09", 0xc67b26df, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvc.10", 0x0fdd1e26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mvscjr1_gfx[] = {
    {"mvc.13m", 0xfa5f74bc, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvc.15m", 0x71938a8f, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvc.17m", 0x92741d07, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvc.19m", 0xbcb72fc6, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvc.14m", 0x7f1df4e4, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvc.16m", 0x90bd3203, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvc.18m", 0x67aaf727, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvc.20m", 0x8b0bade8, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mvscjr1_audiocpu[] = {
    {"mvc.01", 0x41629e95, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvc.01", 0x41629e95, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvc.02", 0x963abf6b, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mvscjr1_qsound[] = {
    {"mvc.11m", 0x850fe663, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvc.12m", 0x7ccb1896, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mvscjr1_key[] = {
    {"mvscj.key", 0x9dedbcaf, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mvscjr1[] = {
    {"maincpu", 4194304, 0, chips_mvscjr1_maincpu, N(chips_mvscjr1_maincpu)},
    {"gfx", 33554432, 0, chips_mvscjr1_gfx, N(chips_mvscjr1_gfx)},
    {"audiocpu", 327680, 0, chips_mvscjr1_audiocpu, N(chips_mvscjr1_audiocpu)},
    {"qsound", 8388608, 0, chips_mvscjr1_qsound, N(chips_mvscjr1_qsound)},
    {"key", 32, 0, chips_mvscjr1_key, N(chips_mvscjr1_key)},
};
static const Cps2Load chips_mvscjsing_maincpu[] = {
    {"mvc_ja.simm1", 0x6a2ef7c2, 2097152, 0, 0, 2097152, CPS2_BYTE16},
    {"mvc_ja.simm3", 0x699d09ad, 2097152, 0, 1, 2097152, CPS2_BYTE16},
};
static const Cps2Load chips_mvscjsing_gfx[] = {
    {"mvc64-13m.13", 0x8428ce69, 8388608, 0, 0, 8388608, CPS2_WORD64},
    {"mvc64-15m.15", 0x2e0028f4, 8388608, 0, 2, 8388608, CPS2_WORD64},
    {"mvc64-17m.17", 0x308ca826, 8388608, 0, 4, 8388608, CPS2_WORD64},
    {"mvc64-19m.19", 0x10699fe1, 8388608, 0, 6, 8388608, CPS2_WORD64},
};
static const Cps2Load chips_mvscjsing_audiocpu[] = {
    {"mvc.01", 0x41629e95, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvc.01", 0x41629e95, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvc.02", 0x963abf6b, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mvscjsing_qsound[] = {
    {"mvc64-11m.11", 0x5d8819e0, 8388608, 0, 0, 8388608, CPS2_SWAP16},
};
static const Cps2Load chips_mvscjsing_key[] = {
    {"mvscj.key", 0x9dedbcaf, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mvscjsing[] = {
    {"maincpu", 4194304, 0, chips_mvscjsing_maincpu, N(chips_mvscjsing_maincpu)},
    {"gfx", 33554432, 0, chips_mvscjsing_gfx, N(chips_mvscjsing_gfx)},
    {"audiocpu", 327680, 0, chips_mvscjsing_audiocpu, N(chips_mvscjsing_audiocpu)},
    {"qsound", 8388608, 0, chips_mvscjsing_qsound, N(chips_mvscjsing_qsound)},
    {"key", 32, 0, chips_mvscjsing_key, N(chips_mvscjsing_key)},
};
static const Cps2Load chips_mvsca_maincpu[] = {
    {"mvca.03a", 0x2ff4ae25, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvca.04a", 0xf28427ef, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvc.05a", 0x2d8c8e86, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvc.06a", 0x8528e1f5, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvc.07", 0xc3baa32b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvc.08", 0xbc002fcd, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvc.09", 0xc67b26df, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvc.10", 0x0fdd1e26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mvsca_gfx[] = {
    {"mvc.13m", 0xfa5f74bc, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvc.15m", 0x71938a8f, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvc.17m", 0x92741d07, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvc.19m", 0xbcb72fc6, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvc.14m", 0x7f1df4e4, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvc.16m", 0x90bd3203, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvc.18m", 0x67aaf727, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvc.20m", 0x8b0bade8, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mvsca_audiocpu[] = {
    {"mvc.01", 0x41629e95, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvc.01", 0x41629e95, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvc.02", 0x963abf6b, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mvsca_qsound[] = {
    {"mvc.11m", 0x850fe663, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvc.12m", 0x7ccb1896, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mvsca_key[] = {
    {"mvsca.key", 0x31edaee8, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mvsca[] = {
    {"maincpu", 4194304, 0, chips_mvsca_maincpu, N(chips_mvsca_maincpu)},
    {"gfx", 33554432, 0, chips_mvsca_gfx, N(chips_mvsca_gfx)},
    {"audiocpu", 327680, 0, chips_mvsca_audiocpu, N(chips_mvsca_audiocpu)},
    {"qsound", 8388608, 0, chips_mvsca_qsound, N(chips_mvsca_qsound)},
    {"key", 32, 0, chips_mvsca_key, N(chips_mvsca_key)},
};
static const Cps2Load chips_mvscar1_maincpu[] = {
    {"mvca.03", 0xfe5fa7b9, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvca.04", 0x082b701c, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvc.05", 0x7db71ce9, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvc.06", 0x4b0b6d3e, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvc.07", 0xc3baa32b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvc.08", 0xbc002fcd, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvc.09", 0xc67b26df, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvc.10", 0x0fdd1e26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mvscar1_gfx[] = {
    {"mvc.13m", 0xfa5f74bc, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvc.15m", 0x71938a8f, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvc.17m", 0x92741d07, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvc.19m", 0xbcb72fc6, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvc.14m", 0x7f1df4e4, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvc.16m", 0x90bd3203, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvc.18m", 0x67aaf727, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvc.20m", 0x8b0bade8, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mvscar1_audiocpu[] = {
    {"mvc.01", 0x41629e95, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvc.01", 0x41629e95, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvc.02", 0x963abf6b, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mvscar1_qsound[] = {
    {"mvc.11m", 0x850fe663, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvc.12m", 0x7ccb1896, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mvscar1_key[] = {
    {"mvsca.key", 0x31edaee8, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mvscar1[] = {
    {"maincpu", 4194304, 0, chips_mvscar1_maincpu, N(chips_mvscar1_maincpu)},
    {"gfx", 33554432, 0, chips_mvscar1_gfx, N(chips_mvscar1_gfx)},
    {"audiocpu", 327680, 0, chips_mvscar1_audiocpu, N(chips_mvscar1_audiocpu)},
    {"qsound", 8388608, 0, chips_mvscar1_qsound, N(chips_mvscar1_qsound)},
    {"key", 32, 0, chips_mvscar1_key, N(chips_mvscar1_key)},
};
static const Cps2Load chips_mvsch_maincpu[] = {
    {"mvch.03", 0x6a0ec9f7, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvch.04", 0x00f03fa4, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvc.05a", 0x2d8c8e86, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvc.06a", 0x8528e1f5, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvc.07", 0xc3baa32b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvc.08", 0xbc002fcd, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvc.09", 0xc67b26df, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvc.10", 0x0fdd1e26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mvsch_gfx[] = {
    {"mvc.13m", 0xfa5f74bc, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvc.15m", 0x71938a8f, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvc.17m", 0x92741d07, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvc.19m", 0xbcb72fc6, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvc.14m", 0x7f1df4e4, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvc.16m", 0x90bd3203, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvc.18m", 0x67aaf727, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvc.20m", 0x8b0bade8, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mvsch_audiocpu[] = {
    {"mvc.01", 0x41629e95, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvc.01", 0x41629e95, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvc.02", 0x963abf6b, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mvsch_qsound[] = {
    {"mvc.11m", 0x850fe663, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvc.12m", 0x7ccb1896, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mvsch_key[] = {
    {"mvsch.key", 0xdd647c0d, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mvsch[] = {
    {"maincpu", 4194304, 0, chips_mvsch_maincpu, N(chips_mvsch_maincpu)},
    {"gfx", 33554432, 0, chips_mvsch_gfx, N(chips_mvsch_gfx)},
    {"audiocpu", 327680, 0, chips_mvsch_audiocpu, N(chips_mvsch_audiocpu)},
    {"qsound", 8388608, 0, chips_mvsch_qsound, N(chips_mvsch_qsound)},
    {"key", 32, 0, chips_mvsch_key, N(chips_mvsch_key)},
};
static const Cps2Load chips_mvscb_maincpu[] = {
    {"mvcb.03a", 0x7155953b, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvcb.04a", 0xfb117d0e, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvc.05a", 0x2d8c8e86, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvc.06a", 0x8528e1f5, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvc.07", 0xc3baa32b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvc.08", 0xbc002fcd, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvc.09", 0xc67b26df, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvc.10", 0x0fdd1e26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mvscb_gfx[] = {
    {"mvc.13m", 0xfa5f74bc, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvc.15m", 0x71938a8f, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvc.17m", 0x92741d07, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvc.19m", 0xbcb72fc6, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvc.14m", 0x7f1df4e4, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvc.16m", 0x90bd3203, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvc.18m", 0x67aaf727, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvc.20m", 0x8b0bade8, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mvscb_audiocpu[] = {
    {"mvc.01", 0x41629e95, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvc.01", 0x41629e95, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvc.02", 0x963abf6b, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mvscb_qsound[] = {
    {"mvc.11m", 0x850fe663, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvc.12m", 0x7ccb1896, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mvscb_key[] = {
    {"mvscb.key", 0xd74a7a3d, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mvscb[] = {
    {"maincpu", 4194304, 0, chips_mvscb_maincpu, N(chips_mvscb_maincpu)},
    {"gfx", 33554432, 0, chips_mvscb_gfx, N(chips_mvscb_gfx)},
    {"audiocpu", 327680, 0, chips_mvscb_audiocpu, N(chips_mvscb_audiocpu)},
    {"qsound", 8388608, 0, chips_mvscb_qsound, N(chips_mvscb_qsound)},
    {"key", 32, 0, chips_mvscb_key, N(chips_mvscb_key)},
};
static const Cps2Load chips_sfa3_maincpu[] = {
    {"sz3e.03c", 0x9762b206, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz3e.04c", 0x5ad3f721, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz3.05c", 0x57fd0a40, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz3.06c", 0xf6305f8b, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz3.07c", 0x6eab0f6f, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz3.08c", 0x910c4a3b, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sz3.09c", 0xb29e5199, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"sz3.10b", 0xdeb2ff52, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3_gfx[] = {
    {"sz3.13m", 0x0f7a60d9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz3.15m", 0x8e933741, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz3.17m", 0xd6e98147, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz3.19m", 0xf31a728a, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz3.14m", 0x5ff98297, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"sz3.16m", 0x52b5bdee, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"sz3.18m", 0x40631ed5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"sz3.20m", 0x763409b4, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_sfa3_audiocpu[] = {
    {"sz3.01", 0xde810084, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz3.01", 0xde810084, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz3.02", 0x72445dc4, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfa3_qsound[] = {
    {"sz3.11m", 0x1c89eed1, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"sz3.12m", 0xf392b13a, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3_key[] = {
    {"sfa3.key", 0x54fa39c6, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfa3[] = {
    {"maincpu", 4194304, 0, chips_sfa3_maincpu, N(chips_sfa3_maincpu)},
    {"gfx", 33554432, 0, chips_sfa3_gfx, N(chips_sfa3_gfx)},
    {"audiocpu", 327680, 0, chips_sfa3_audiocpu, N(chips_sfa3_audiocpu)},
    {"qsound", 8388608, 0, chips_sfa3_qsound, N(chips_sfa3_qsound)},
    {"key", 32, 0, chips_sfa3_key, N(chips_sfa3_key)},
};
static const Cps2Load chips_sfa3u_maincpu[] = {
    {"sz3u.03c", 0xe007da2e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz3u.04c", 0x5f78f0e7, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz3.05c", 0x57fd0a40, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz3.06c", 0xf6305f8b, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz3.07c", 0x6eab0f6f, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz3.08c", 0x910c4a3b, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sz3.09c", 0xb29e5199, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"sz3.10b", 0xdeb2ff52, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3u_gfx[] = {
    {"sz3.13m", 0x0f7a60d9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz3.15m", 0x8e933741, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz3.17m", 0xd6e98147, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz3.19m", 0xf31a728a, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz3.14m", 0x5ff98297, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"sz3.16m", 0x52b5bdee, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"sz3.18m", 0x40631ed5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"sz3.20m", 0x763409b4, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_sfa3u_audiocpu[] = {
    {"sz3.01", 0xde810084, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz3.01", 0xde810084, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz3.02", 0x72445dc4, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfa3u_qsound[] = {
    {"sz3.11m", 0x1c89eed1, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"sz3.12m", 0xf392b13a, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3u_key[] = {
    {"sfa3u.key", 0x4a8f98c1, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfa3u[] = {
    {"maincpu", 4194304, 0, chips_sfa3u_maincpu, N(chips_sfa3u_maincpu)},
    {"gfx", 33554432, 0, chips_sfa3u_gfx, N(chips_sfa3u_gfx)},
    {"audiocpu", 327680, 0, chips_sfa3u_audiocpu, N(chips_sfa3u_audiocpu)},
    {"qsound", 8388608, 0, chips_sfa3u_qsound, N(chips_sfa3u_qsound)},
    {"key", 32, 0, chips_sfa3u_key, N(chips_sfa3u_key)},
};
static const Cps2Load chips_sfa3ur1_maincpu[] = {
    {"sz3u.03", 0xb5984a19, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz3u.04", 0x7e8158ba, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz3.05", 0x9b21518a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz3.06", 0xe7a6c3a7, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz3.07", 0xec4c0cfd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz3.08", 0x5c7e7240, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sz3.09", 0xc5589553, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"sz3.10", 0xa9717252, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3ur1_gfx[] = {
    {"sz3.13m", 0x0f7a60d9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz3.15m", 0x8e933741, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz3.17m", 0xd6e98147, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz3.19m", 0xf31a728a, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz3.14m", 0x5ff98297, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"sz3.16m", 0x52b5bdee, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"sz3.18m", 0x40631ed5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"sz3.20m", 0x763409b4, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_sfa3ur1_audiocpu[] = {
    {"sz3.01", 0xde810084, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz3.01", 0xde810084, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz3.02", 0x72445dc4, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfa3ur1_qsound[] = {
    {"sz3.11m", 0x1c89eed1, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"sz3.12m", 0xf392b13a, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3ur1_key[] = {
    {"sfa3u.key", 0x4a8f98c1, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfa3ur1[] = {
    {"maincpu", 4194304, 0, chips_sfa3ur1_maincpu, N(chips_sfa3ur1_maincpu)},
    {"gfx", 33554432, 0, chips_sfa3ur1_gfx, N(chips_sfa3ur1_gfx)},
    {"audiocpu", 327680, 0, chips_sfa3ur1_audiocpu, N(chips_sfa3ur1_audiocpu)},
    {"qsound", 8388608, 0, chips_sfa3ur1_qsound, N(chips_sfa3ur1_qsound)},
    {"key", 32, 0, chips_sfa3ur1_key, N(chips_sfa3ur1_key)},
};
static const Cps2Load chips_sfa3us_maincpu[] = {
    {"sz3-usam_03.6a", 0x14319e29, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz3-usam_04.7a", 0x65fbc272, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz3-usam_05.8a", 0xe93c47d1, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz3-usam_06.9a", 0x1bf09de3, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz3-usam_07.6d", 0xf6296d96, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz3-usam_08.7d", 0x1f4008ff, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sz3-usam_09.8d", 0x822fc451, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"sz3-usam_10.9d", 0x92713468, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3us_gfx[] = {
    {"sz3.13m", 0x0f7a60d9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz3.15m", 0x8e933741, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz3.17m", 0xd6e98147, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz3.19m", 0xf31a728a, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz3.14m", 0x5ff98297, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"sz3.16m", 0x52b5bdee, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"sz3.18m", 0x40631ed5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"sz3.20m", 0x763409b4, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_sfa3us_audiocpu[] = {
    {"sz3-usam_01.1a", 0xc180947d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz3-usam_01.1a", 0xc180947d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz3-usam_02.2a", 0x9ebc280f, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfa3us_qsound[] = {
    {"sz3.11m", 0x1c89eed1, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"sz3.12m", 0xf392b13a, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3us_key[] = {
    {"sfa3u.key", 0x4a8f98c1, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfa3us[] = {
    {"maincpu", 4194304, 0, chips_sfa3us_maincpu, N(chips_sfa3us_maincpu)},
    {"gfx", 33554432, 0, chips_sfa3us_gfx, N(chips_sfa3us_gfx)},
    {"audiocpu", 327680, 0, chips_sfa3us_audiocpu, N(chips_sfa3us_audiocpu)},
    {"qsound", 8388608, 0, chips_sfa3us_qsound, N(chips_sfa3us_qsound)},
    {"key", 32, 0, chips_sfa3us_key, N(chips_sfa3us_key)},
};
static const Cps2Load chips_sfa3h_maincpu[] = {
    {"sz3h.03c", 0xb3b563a3, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz3h.04c", 0x47891fec, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz3.05c", 0x57fd0a40, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz3.06c", 0xf6305f8b, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz3.07c", 0x6eab0f6f, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz3.08c", 0x910c4a3b, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sz3.09c", 0xb29e5199, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"sz3.10b", 0xdeb2ff52, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3h_gfx[] = {
    {"sz3.13m", 0x0f7a60d9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz3.15m", 0x8e933741, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz3.17m", 0xd6e98147, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz3.19m", 0xf31a728a, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz3.14m", 0x5ff98297, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"sz3.16m", 0x52b5bdee, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"sz3.18m", 0x40631ed5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"sz3.20m", 0x763409b4, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_sfa3h_audiocpu[] = {
    {"sz3.01", 0xde810084, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz3.01", 0xde810084, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz3.02", 0x72445dc4, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfa3h_qsound[] = {
    {"sz3.11m", 0x1c89eed1, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"sz3.12m", 0xf392b13a, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3h_key[] = {
    {"sfa3h.key", 0x1b34998c, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfa3h[] = {
    {"maincpu", 4194304, 0, chips_sfa3h_maincpu, N(chips_sfa3h_maincpu)},
    {"gfx", 33554432, 0, chips_sfa3h_gfx, N(chips_sfa3h_gfx)},
    {"audiocpu", 327680, 0, chips_sfa3h_audiocpu, N(chips_sfa3h_audiocpu)},
    {"qsound", 8388608, 0, chips_sfa3h_qsound, N(chips_sfa3h_qsound)},
    {"key", 32, 0, chips_sfa3h_key, N(chips_sfa3h_key)},
};
static const Cps2Load chips_sfa3hr1_maincpu[] = {
    {"sz3h.03", 0x4b16cb3e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz3h.04", 0x88ad2e6a, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz3.05", 0x9b21518a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz3.06", 0xe7a6c3a7, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz3.07", 0xec4c0cfd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz3.08", 0x5c7e7240, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sz3.09", 0xc5589553, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"sz3.10", 0xa9717252, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3hr1_gfx[] = {
    {"sz3.13m", 0x0f7a60d9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz3.15m", 0x8e933741, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz3.17m", 0xd6e98147, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz3.19m", 0xf31a728a, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz3.14m", 0x5ff98297, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"sz3.16m", 0x52b5bdee, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"sz3.18m", 0x40631ed5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"sz3.20m", 0x763409b4, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_sfa3hr1_audiocpu[] = {
    {"sz3.01", 0xde810084, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz3.01", 0xde810084, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz3.02", 0x72445dc4, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfa3hr1_qsound[] = {
    {"sz3.11m", 0x1c89eed1, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"sz3.12m", 0xf392b13a, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3hr1_key[] = {
    {"sfa3h.key", 0x1b34998c, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfa3hr1[] = {
    {"maincpu", 4194304, 0, chips_sfa3hr1_maincpu, N(chips_sfa3hr1_maincpu)},
    {"gfx", 33554432, 0, chips_sfa3hr1_gfx, N(chips_sfa3hr1_gfx)},
    {"audiocpu", 327680, 0, chips_sfa3hr1_audiocpu, N(chips_sfa3hr1_audiocpu)},
    {"qsound", 8388608, 0, chips_sfa3hr1_qsound, N(chips_sfa3hr1_qsound)},
    {"key", 32, 0, chips_sfa3hr1_key, N(chips_sfa3hr1_key)},
};
static const Cps2Load chips_sfa3b_maincpu[] = {
    {"sz3b.03", 0x046c9b4d, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz3b.04", 0xda211919, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz3.05", 0x9b21518a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz3.06", 0xe7a6c3a7, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz3.07", 0xec4c0cfd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz3.08", 0x5c7e7240, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sz3.09", 0xc5589553, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"sz3.10", 0xa9717252, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3b_gfx[] = {
    {"sz3.13m", 0x0f7a60d9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz3.15m", 0x8e933741, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz3.17m", 0xd6e98147, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz3.19m", 0xf31a728a, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz3.14m", 0x5ff98297, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"sz3.16m", 0x52b5bdee, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"sz3.18m", 0x40631ed5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"sz3.20m", 0x763409b4, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_sfa3b_audiocpu[] = {
    {"sz3.01", 0xde810084, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz3.01", 0xde810084, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz3.02", 0x72445dc4, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfa3b_qsound[] = {
    {"sz3.11m", 0x1c89eed1, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"sz3.12m", 0xf392b13a, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3b_key[] = {
    {"sfa3b.key", 0x2d0a1351, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfa3b[] = {
    {"maincpu", 4194304, 0, chips_sfa3b_maincpu, N(chips_sfa3b_maincpu)},
    {"gfx", 33554432, 0, chips_sfa3b_gfx, N(chips_sfa3b_gfx)},
    {"audiocpu", 327680, 0, chips_sfa3b_audiocpu, N(chips_sfa3b_audiocpu)},
    {"qsound", 8388608, 0, chips_sfa3b_qsound, N(chips_sfa3b_qsound)},
    {"key", 32, 0, chips_sfa3b_key, N(chips_sfa3b_key)},
};
static const Cps2Load chips_sfz3j_maincpu[] = {
    {"sz3j.03c", 0xcadf4a51, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz3j.04c", 0xfcb31228, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz3.05c", 0x57fd0a40, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz3.06c", 0xf6305f8b, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz3.07c", 0x6eab0f6f, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz3.08c", 0x910c4a3b, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sz3.09c", 0xb29e5199, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"sz3.10b", 0xdeb2ff52, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz3j_gfx[] = {
    {"sz3.13m", 0x0f7a60d9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz3.15m", 0x8e933741, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz3.17m", 0xd6e98147, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz3.19m", 0xf31a728a, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz3.14m", 0x5ff98297, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"sz3.16m", 0x52b5bdee, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"sz3.18m", 0x40631ed5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"sz3.20m", 0x763409b4, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_sfz3j_audiocpu[] = {
    {"sz3.01", 0xde810084, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz3.01", 0xde810084, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz3.02", 0x72445dc4, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz3j_qsound[] = {
    {"sz3.11m", 0x1c89eed1, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"sz3.12m", 0xf392b13a, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sfz3j_key[] = {
    {"sfz3j.key", 0xd30cca8d, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz3j[] = {
    {"maincpu", 4194304, 0, chips_sfz3j_maincpu, N(chips_sfz3j_maincpu)},
    {"gfx", 33554432, 0, chips_sfz3j_gfx, N(chips_sfz3j_gfx)},
    {"audiocpu", 327680, 0, chips_sfz3j_audiocpu, N(chips_sfz3j_audiocpu)},
    {"qsound", 8388608, 0, chips_sfz3j_qsound, N(chips_sfz3j_qsound)},
    {"key", 32, 0, chips_sfz3j_key, N(chips_sfz3j_key)},
};
static const Cps2Load chips_sfz3jr1_maincpu[] = {
    {"sz3j.03a", 0x6ee0beae, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz3j.04a", 0xa6e2978d, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz3.05a", 0x05964b7d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz3.06a", 0x78ce2179, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz3.07a", 0x398bf52f, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz3.08a", 0x866d0588, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sz3.09a", 0x2180892c, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"sz3.10", 0xa9717252, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz3jr1_gfx[] = {
    {"sz3.13m", 0x0f7a60d9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz3.15m", 0x8e933741, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz3.17m", 0xd6e98147, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz3.19m", 0xf31a728a, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz3.14m", 0x5ff98297, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"sz3.16m", 0x52b5bdee, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"sz3.18m", 0x40631ed5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"sz3.20m", 0x763409b4, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_sfz3jr1_audiocpu[] = {
    {"sz3.01", 0xde810084, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz3.01", 0xde810084, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz3.02", 0x72445dc4, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz3jr1_qsound[] = {
    {"sz3.11m", 0x1c89eed1, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"sz3.12m", 0xf392b13a, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sfz3jr1_key[] = {
    {"sfz3j.key", 0xd30cca8d, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz3jr1[] = {
    {"maincpu", 4194304, 0, chips_sfz3jr1_maincpu, N(chips_sfz3jr1_maincpu)},
    {"gfx", 33554432, 0, chips_sfz3jr1_gfx, N(chips_sfz3jr1_gfx)},
    {"audiocpu", 327680, 0, chips_sfz3jr1_audiocpu, N(chips_sfz3jr1_audiocpu)},
    {"qsound", 8388608, 0, chips_sfz3jr1_qsound, N(chips_sfz3jr1_qsound)},
    {"key", 32, 0, chips_sfz3jr1_key, N(chips_sfz3jr1_key)},
};
static const Cps2Load chips_sfz3jr2_maincpu[] = {
    {"sz3j.03", 0xf7cb4b13, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz3j.04", 0x0846c29d, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz3.05", 0x9b21518a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz3.06", 0xe7a6c3a7, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz3.07", 0xec4c0cfd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz3.08", 0x5c7e7240, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sz3.09", 0xc5589553, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"sz3.10", 0xa9717252, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz3jr2_gfx[] = {
    {"sz3.13m", 0x0f7a60d9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz3.15m", 0x8e933741, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz3.17m", 0xd6e98147, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz3.19m", 0xf31a728a, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz3.14m", 0x5ff98297, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"sz3.16m", 0x52b5bdee, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"sz3.18m", 0x40631ed5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"sz3.20m", 0x763409b4, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_sfz3jr2_audiocpu[] = {
    {"sz3.01", 0xde810084, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz3.01", 0xde810084, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz3.02", 0x72445dc4, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz3jr2_qsound[] = {
    {"sz3.11m", 0x1c89eed1, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"sz3.12m", 0xf392b13a, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sfz3jr2_key[] = {
    {"sfz3j.key", 0xd30cca8d, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz3jr2[] = {
    {"maincpu", 4194304, 0, chips_sfz3jr2_maincpu, N(chips_sfz3jr2_maincpu)},
    {"gfx", 33554432, 0, chips_sfz3jr2_gfx, N(chips_sfz3jr2_gfx)},
    {"audiocpu", 327680, 0, chips_sfz3jr2_audiocpu, N(chips_sfz3jr2_audiocpu)},
    {"qsound", 8388608, 0, chips_sfz3jr2_qsound, N(chips_sfz3jr2_qsound)},
    {"key", 32, 0, chips_sfz3jr2_key, N(chips_sfz3jr2_key)},
};
static const Cps2Load chips_sfz3a_maincpu[] = {
    {"sz3a.03d", 0xd7e140d6, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz3a.04d", 0xe06869a2, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz3.05c", 0x57fd0a40, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz3.06c", 0xf6305f8b, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz3.07c", 0x6eab0f6f, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz3.08c", 0x910c4a3b, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sz3.09c", 0xb29e5199, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"sz3.10b", 0xdeb2ff52, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz3a_gfx[] = {
    {"sz3.13m", 0x0f7a60d9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz3.15m", 0x8e933741, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz3.17m", 0xd6e98147, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz3.19m", 0xf31a728a, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz3.14m", 0x5ff98297, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"sz3.16m", 0x52b5bdee, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"sz3.18m", 0x40631ed5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"sz3.20m", 0x763409b4, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_sfz3a_audiocpu[] = {
    {"sz3.01", 0xde810084, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz3.01", 0xde810084, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz3.02", 0x72445dc4, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz3a_qsound[] = {
    {"sz3.11m", 0x1c89eed1, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"sz3.12m", 0xf392b13a, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sfz3a_key[] = {
    {"sfz3a.key", 0x09045d61, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz3a[] = {
    {"maincpu", 4194304, 0, chips_sfz3a_maincpu, N(chips_sfz3a_maincpu)},
    {"gfx", 33554432, 0, chips_sfz3a_gfx, N(chips_sfz3a_gfx)},
    {"audiocpu", 327680, 0, chips_sfz3a_audiocpu, N(chips_sfz3a_audiocpu)},
    {"qsound", 8388608, 0, chips_sfz3a_qsound, N(chips_sfz3a_qsound)},
    {"key", 32, 0, chips_sfz3a_key, N(chips_sfz3a_key)},
};
static const Cps2Load chips_sfz3ar1_maincpu[] = {
    {"sz3a.03a", 0x29c681fd, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz3a.04", 0x9ddd1484, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz3.05", 0x9b21518a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz3.06", 0xe7a6c3a7, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz3.07", 0xec4c0cfd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz3.08", 0x5c7e7240, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sz3.09", 0xc5589553, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"sz3.10", 0xa9717252, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz3ar1_gfx[] = {
    {"sz3.13m", 0x0f7a60d9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz3.15m", 0x8e933741, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz3.17m", 0xd6e98147, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz3.19m", 0xf31a728a, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz3.14m", 0x5ff98297, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"sz3.16m", 0x52b5bdee, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"sz3.18m", 0x40631ed5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"sz3.20m", 0x763409b4, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_sfz3ar1_audiocpu[] = {
    {"sz3.01", 0xde810084, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz3.01", 0xde810084, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz3.02", 0x72445dc4, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz3ar1_qsound[] = {
    {"sz3.11m", 0x1c89eed1, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"sz3.12m", 0xf392b13a, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sfz3ar1_key[] = {
    {"sfz3a.key", 0x09045d61, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz3ar1[] = {
    {"maincpu", 4194304, 0, chips_sfz3ar1_maincpu, N(chips_sfz3ar1_maincpu)},
    {"gfx", 33554432, 0, chips_sfz3ar1_gfx, N(chips_sfz3ar1_gfx)},
    {"audiocpu", 327680, 0, chips_sfz3ar1_audiocpu, N(chips_sfz3ar1_audiocpu)},
    {"qsound", 8388608, 0, chips_sfz3ar1_qsound, N(chips_sfz3ar1_qsound)},
    {"key", 32, 0, chips_sfz3ar1_key, N(chips_sfz3ar1_key)},
};
static const Cps2Load chips_jyangoku_maincpu[] = {
    {"majj.03", 0x4614a3b2, 524288, 0, 0, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_jyangoku_gfx[] = {
    {"maj1_d.simm1", 0xba0fe27b, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"maj1_c.simm1", 0x2cd141bf, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"maj1_b.simm1", 0xe29e4c26, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"maj1_a.simm1", 0x7f68b88a, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"maj3_d.simm3", 0x3aaeb90b, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"maj3_c.simm3", 0x97894cea, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"maj3_b.simm3", 0xec737d9d, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"maj3_a.simm3", 0xc23b6f22, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_jyangoku_audiocpu[] = {
    {"maj.01", 0x1fe8c213, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"maj.01", 0x1fe8c213, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_jyangoku_qsound[] = {
    {"maj5_a.simm5", 0x5ad9ee53, 2097152, 0, 0, 2097152, CPS2_BYTE16},
    {"maj5_b.simm5", 0xefb3dbfb, 2097152, 0, 1, 2097152, CPS2_BYTE16},
};
static const Cps2Load chips_jyangoku_key[] = {
    {"jyangoku.key", 0x95b0a560, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_jyangoku[] = {
    {"maincpu", 4194304, 0, chips_jyangoku_maincpu, N(chips_jyangoku_maincpu)},
    {"gfx", 16777216, 0, chips_jyangoku_gfx, N(chips_jyangoku_gfx)},
    {"audiocpu", 327680, 0, chips_jyangoku_audiocpu, N(chips_jyangoku_audiocpu)},
    {"qsound", 4194304, 0, chips_jyangoku_qsound, N(chips_jyangoku_qsound)},
    {"key", 32, 0, chips_jyangoku_key, N(chips_jyangoku_key)},
};
static const Cps2Load chips_hsf2_maincpu[] = {
    {"hs2u.03", 0xb308151e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"hs2u.04", 0x327aa49c, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"hs2.05", 0xdde34a35, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"hs2.06", 0xf4e56dda, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"hs2.07", 0xee4420fc, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"hs2.08", 0xc9441533, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"hs2.09", 0x3fc638a8, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"hs2.10", 0x20d0f9e4, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_hsf2_gfx[] = {
    {"hs2.13m", 0xa6ecab17, 8388608, 0, 0, 8388608, CPS2_WORD64},
    {"hs2.15m", 0x10a0ae4d, 8388608, 0, 2, 8388608, CPS2_WORD64},
    {"hs2.17m", 0xadfa7726, 8388608, 0, 4, 8388608, CPS2_WORD64},
    {"hs2.19m", 0xbb3ae322, 8388608, 0, 6, 8388608, CPS2_WORD64},
};
static const Cps2Load chips_hsf2_audiocpu[] = {
    {"hs2.01", 0xc1a13786, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"hs2.01", 0xc1a13786, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"hs2.02", 0x2d8794aa, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_hsf2_qsound[] = {
    {"hs2.11m", 0x0e15c359, 8388608, 0, 0, 8388608, CPS2_SWAP16},
};
static const Cps2Load chips_hsf2_key[] = {
    {"hsf2.key", 0xfc9b18c9, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_hsf2[] = {
    {"maincpu", 4194304, 0, chips_hsf2_maincpu, N(chips_hsf2_maincpu)},
    {"gfx", 33554432, 0, chips_hsf2_gfx, N(chips_hsf2_gfx)},
    {"audiocpu", 327680, 0, chips_hsf2_audiocpu, N(chips_hsf2_audiocpu)},
    {"qsound", 8388608, 0, chips_hsf2_qsound, N(chips_hsf2_qsound)},
    {"key", 32, 0, chips_hsf2_key, N(chips_hsf2_key)},
};
static const Cps2Load chips_hsf2a_maincpu[] = {
    {"hs2a.03", 0xd50a17e0, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"hs2a.04", 0xa27f42de, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"hs2.05", 0xdde34a35, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"hs2.06", 0xf4e56dda, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"hs2.07", 0xee4420fc, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"hs2.08", 0xc9441533, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"hs2.09", 0x3fc638a8, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"hs2.10", 0x20d0f9e4, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_hsf2a_gfx[] = {
    {"hs2.13m", 0xa6ecab17, 8388608, 0, 0, 8388608, CPS2_WORD64},
    {"hs2.15m", 0x10a0ae4d, 8388608, 0, 2, 8388608, CPS2_WORD64},
    {"hs2.17m", 0xadfa7726, 8388608, 0, 4, 8388608, CPS2_WORD64},
    {"hs2.19m", 0xbb3ae322, 8388608, 0, 6, 8388608, CPS2_WORD64},
};
static const Cps2Load chips_hsf2a_audiocpu[] = {
    {"hs2.01", 0xc1a13786, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"hs2.01", 0xc1a13786, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"hs2.02", 0x2d8794aa, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_hsf2a_qsound[] = {
    {"hs2.11m", 0x0e15c359, 8388608, 0, 0, 8388608, CPS2_SWAP16},
};
static const Cps2Load chips_hsf2a_key[] = {
    {"hsf2a.key", 0x2cd9eb99, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_hsf2a[] = {
    {"maincpu", 4194304, 0, chips_hsf2a_maincpu, N(chips_hsf2a_maincpu)},
    {"gfx", 33554432, 0, chips_hsf2a_gfx, N(chips_hsf2a_gfx)},
    {"audiocpu", 327680, 0, chips_hsf2a_audiocpu, N(chips_hsf2a_audiocpu)},
    {"qsound", 8388608, 0, chips_hsf2a_qsound, N(chips_hsf2a_qsound)},
    {"key", 32, 0, chips_hsf2a_key, N(chips_hsf2a_key)},
};
static const Cps2Load chips_hsf2j_maincpu[] = {
    {"hs2j.03c", 0x6efe661f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"hs2j.04b", 0x93f2500a, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"hs2j.05", 0xdde34a35, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"hs2j.06", 0xf4e56dda, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"hs2j.07", 0xee4420fc, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"hs2j.08", 0xc9441533, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"hs2j.09", 0x3fc638a8, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"hs2j.10", 0x20d0f9e4, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_hsf2j_gfx[] = {
    {"hs2.13m", 0xa6ecab17, 8388608, 0, 0, 8388608, CPS2_WORD64},
    {"hs2.15m", 0x10a0ae4d, 8388608, 0, 2, 8388608, CPS2_WORD64},
    {"hs2.17m", 0xadfa7726, 8388608, 0, 4, 8388608, CPS2_WORD64},
    {"hs2.19m", 0xbb3ae322, 8388608, 0, 6, 8388608, CPS2_WORD64},
};
static const Cps2Load chips_hsf2j_audiocpu[] = {
    {"hs2.01", 0xc1a13786, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"hs2.01", 0xc1a13786, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"hs2.02", 0x2d8794aa, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_hsf2j_qsound[] = {
    {"hs2.11m", 0x0e15c359, 8388608, 0, 0, 8388608, CPS2_SWAP16},
};
static const Cps2Load chips_hsf2j_key[] = {
    {"hsf2j.key", 0x19455a93, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_hsf2j[] = {
    {"maincpu", 4194304, 0, chips_hsf2j_maincpu, N(chips_hsf2j_maincpu)},
    {"gfx", 33554432, 0, chips_hsf2j_gfx, N(chips_hsf2j_gfx)},
    {"audiocpu", 327680, 0, chips_hsf2j_audiocpu, N(chips_hsf2j_audiocpu)},
    {"qsound", 8388608, 0, chips_hsf2j_qsound, N(chips_hsf2j_qsound)},
    {"key", 32, 0, chips_hsf2j_key, N(chips_hsf2j_key)},
};
static const Cps2Load chips_hsf2j1_maincpu[] = {
    {"hs2j.03a", 0x76c7d980, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"hs2j.04a", 0x3d1f5d9b, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"hs2.05", 0xdde34a35, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"hs2.06", 0xf4e56dda, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"hs2.07", 0xee4420fc, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"hs2.08", 0xc9441533, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"hs2.09", 0x3fc638a8, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"hs2.10", 0x20d0f9e4, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_hsf2j1_gfx[] = {
    {"hs2.13m", 0xa6ecab17, 8388608, 0, 0, 8388608, CPS2_WORD64},
    {"hs2.15m", 0x10a0ae4d, 8388608, 0, 2, 8388608, CPS2_WORD64},
    {"hs2.17m", 0xadfa7726, 8388608, 0, 4, 8388608, CPS2_WORD64},
    {"hs2.19m", 0xbb3ae322, 8388608, 0, 6, 8388608, CPS2_WORD64},
};
static const Cps2Load chips_hsf2j1_audiocpu[] = {
    {"hs2.01", 0xc1a13786, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"hs2.01", 0xc1a13786, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"hs2.02", 0x2d8794aa, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_hsf2j1_qsound[] = {
    {"hs2.11m", 0x0e15c359, 8388608, 0, 0, 8388608, CPS2_SWAP16},
};
static const Cps2Load chips_hsf2j1_key[] = {
    {"hsf2j.key", 0x19455a93, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_hsf2j1[] = {
    {"maincpu", 4194304, 0, chips_hsf2j1_maincpu, N(chips_hsf2j1_maincpu)},
    {"gfx", 33554432, 0, chips_hsf2j1_gfx, N(chips_hsf2j1_gfx)},
    {"audiocpu", 327680, 0, chips_hsf2j1_audiocpu, N(chips_hsf2j1_audiocpu)},
    {"qsound", 8388608, 0, chips_hsf2j1_qsound, N(chips_hsf2j1_qsound)},
    {"key", 32, 0, chips_hsf2j1_key, N(chips_hsf2j1_key)},
};
static const Cps2Load chips_hsf2j2_maincpu[] = {
    {"hs2j.03", 0x00738f73, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"hs2j.04", 0x40072c4a, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"hs2.05", 0xdde34a35, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"hs2.06", 0xf4e56dda, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"hs2.07", 0xee4420fc, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"hs2.08", 0xc9441533, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"hs2.09", 0x3fc638a8, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"hs2.10", 0x20d0f9e4, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_hsf2j2_gfx[] = {
    {"hs2.13m", 0xa6ecab17, 8388608, 0, 0, 8388608, CPS2_WORD64},
    {"hs2.15m", 0x10a0ae4d, 8388608, 0, 2, 8388608, CPS2_WORD64},
    {"hs2.17m", 0xadfa7726, 8388608, 0, 4, 8388608, CPS2_WORD64},
    {"hs2.19m", 0xbb3ae322, 8388608, 0, 6, 8388608, CPS2_WORD64},
};
static const Cps2Load chips_hsf2j2_audiocpu[] = {
    {"hs2.01", 0xc1a13786, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"hs2.01", 0xc1a13786, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"hs2.02", 0x2d8794aa, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_hsf2j2_qsound[] = {
    {"hs2.11m", 0x0e15c359, 8388608, 0, 0, 8388608, CPS2_SWAP16},
};
static const Cps2Load chips_hsf2j2_key[] = {
    {"hsf2j.key", 0x19455a93, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_hsf2j2[] = {
    {"maincpu", 4194304, 0, chips_hsf2j2_maincpu, N(chips_hsf2j2_maincpu)},
    {"gfx", 33554432, 0, chips_hsf2j2_gfx, N(chips_hsf2j2_gfx)},
    {"audiocpu", 327680, 0, chips_hsf2j2_audiocpu, N(chips_hsf2j2_audiocpu)},
    {"qsound", 8388608, 0, chips_hsf2j2_qsound, N(chips_hsf2j2_qsound)},
    {"key", 32, 0, chips_hsf2j2_key, N(chips_hsf2j2_key)},
};
static const Cps2Load chips_gigawing_maincpu[] = {
    {"ggwu.03", 0xac725eb2, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ggwu.04", 0x392f4118, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ggw.05", 0x3239d642, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_gigawing_gfx[] = {
    {"ggw.13m", 0x105530a4, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"ggw.15m", 0x9e774ab9, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"ggw.17m", 0x466e0ba4, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"ggw.19m", 0x840c8dea, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_gigawing_audiocpu[] = {
    {"ggw.01", 0x4c6351d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ggw.01", 0x4c6351d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_gigawing_qsound[] = {
    {"ggw.11m", 0xe172acf5, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"ggw.12m", 0x4bee4e8f, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_gigawing_key[] = {
    {"gigawing.key", 0x5076c26b, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_gigawing[] = {
    {"maincpu", 4194304, 0, chips_gigawing_maincpu, N(chips_gigawing_maincpu)},
    {"gfx", 16777216, 0, chips_gigawing_gfx, N(chips_gigawing_gfx)},
    {"audiocpu", 327680, 0, chips_gigawing_audiocpu, N(chips_gigawing_audiocpu)},
    {"qsound", 8388608, 0, chips_gigawing_qsound, N(chips_gigawing_qsound)},
    {"key", 32, 0, chips_gigawing_key, N(chips_gigawing_key)},
};
static const Cps2Load chips_gigawingj_maincpu[] = {
    {"ggwj.03a", 0xfdd23b91, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ggwj.04a", 0x8c6e093c, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ggwj.05a", 0x43811454, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_gigawingj_gfx[] = {
    {"ggw.13m", 0x105530a4, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"ggw.15m", 0x9e774ab9, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"ggw.17m", 0x466e0ba4, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"ggw.19m", 0x840c8dea, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_gigawingj_audiocpu[] = {
    {"ggw.01", 0x4c6351d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ggw.01", 0x4c6351d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_gigawingj_qsound[] = {
    {"ggw.11m", 0xe172acf5, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"ggw.12m", 0x4bee4e8f, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_gigawingj_key[] = {
    {"gigawingj.key", 0x8121a25e, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_gigawingj[] = {
    {"maincpu", 4194304, 0, chips_gigawingj_maincpu, N(chips_gigawingj_maincpu)},
    {"gfx", 16777216, 0, chips_gigawingj_gfx, N(chips_gigawingj_gfx)},
    {"audiocpu", 327680, 0, chips_gigawingj_audiocpu, N(chips_gigawingj_audiocpu)},
    {"qsound", 8388608, 0, chips_gigawingj_qsound, N(chips_gigawingj_qsound)},
    {"key", 32, 0, chips_gigawingj_key, N(chips_gigawingj_key)},
};
static const Cps2Load chips_gigawinga_maincpu[] = {
    {"ggwa.03a", 0x116f8837, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ggwa.04a", 0xe6e3f0c4, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ggwa.05a", 0x465e8ac9, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_gigawinga_gfx[] = {
    {"ggw.13m", 0x105530a4, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"ggw.15m", 0x9e774ab9, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"ggw.17m", 0x466e0ba4, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"ggw.19m", 0x840c8dea, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_gigawinga_audiocpu[] = {
    {"ggw.01", 0x4c6351d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ggw.01", 0x4c6351d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_gigawinga_qsound[] = {
    {"ggw.11m", 0xe172acf5, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"ggw.12m", 0x4bee4e8f, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_gigawinga_key[] = {
    {"gigawinga.key", 0x7401627e, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_gigawinga[] = {
    {"maincpu", 4194304, 0, chips_gigawinga_maincpu, N(chips_gigawinga_maincpu)},
    {"gfx", 16777216, 0, chips_gigawinga_gfx, N(chips_gigawinga_gfx)},
    {"audiocpu", 327680, 0, chips_gigawinga_audiocpu, N(chips_gigawinga_audiocpu)},
    {"qsound", 8388608, 0, chips_gigawinga_qsound, N(chips_gigawinga_qsound)},
    {"key", 32, 0, chips_gigawinga_key, N(chips_gigawinga_key)},
};
static const Cps2Load chips_gigawingh_maincpu[] = {
    {"ggwh.03a", 0xb9ee36eb, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ggwh.04a", 0x72e548fe, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ggw.05", 0x3239d642, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_gigawingh_gfx[] = {
    {"ggw.13m", 0x105530a4, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"ggw.15m", 0x9e774ab9, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"ggw.17m", 0x466e0ba4, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"ggw.19m", 0x840c8dea, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_gigawingh_audiocpu[] = {
    {"ggw.01", 0x4c6351d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ggw.01", 0x4c6351d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_gigawingh_qsound[] = {
    {"ggw.11m", 0xe172acf5, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"ggw.12m", 0x4bee4e8f, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_gigawingh_key[] = {
    {"gigawingh.key", 0x43198223, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_gigawingh[] = {
    {"maincpu", 4194304, 0, chips_gigawingh_maincpu, N(chips_gigawingh_maincpu)},
    {"gfx", 16777216, 0, chips_gigawingh_gfx, N(chips_gigawingh_gfx)},
    {"audiocpu", 327680, 0, chips_gigawingh_audiocpu, N(chips_gigawingh_audiocpu)},
    {"qsound", 8388608, 0, chips_gigawingh_qsound, N(chips_gigawingh_qsound)},
    {"key", 32, 0, chips_gigawingh_key, N(chips_gigawingh_key)},
};
static const Cps2Load chips_gigawingb_maincpu[] = {
    {"ggwb.03", 0xa1f8a448, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ggwb.04", 0x6a423e76, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ggw.05", 0x3239d642, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_gigawingb_gfx[] = {
    {"ggw.13m", 0x105530a4, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"ggw.15m", 0x9e774ab9, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"ggw.17m", 0x466e0ba4, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"ggw.19m", 0x840c8dea, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_gigawingb_audiocpu[] = {
    {"ggw.01", 0x4c6351d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ggw.01", 0x4c6351d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_gigawingb_qsound[] = {
    {"ggw.11m", 0xe172acf5, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"ggw.12m", 0x4bee4e8f, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_gigawingb_key[] = {
    {"gigawingb.key", 0x5e7805fa, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_gigawingb[] = {
    {"maincpu", 4194304, 0, chips_gigawingb_maincpu, N(chips_gigawingb_maincpu)},
    {"gfx", 16777216, 0, chips_gigawingb_gfx, N(chips_gigawingb_gfx)},
    {"audiocpu", 327680, 0, chips_gigawingb_audiocpu, N(chips_gigawingb_audiocpu)},
    {"qsound", 8388608, 0, chips_gigawingb_qsound, N(chips_gigawingb_qsound)},
    {"key", 32, 0, chips_gigawingb_key, N(chips_gigawingb_key)},
};
static const Cps2Load chips_mmatrix_maincpu[] = {
    {"mmxu.03", 0xab65b599, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mmxu.04", 0x0135fc6c, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mmxu.05", 0xf1fd2b84, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mmatrix_gfx[] = {
    {"mmx.13m", 0x04748718, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mmx.15m", 0x38074f44, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mmx.17m", 0xe4635e35, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mmx.19m", 0x4400a3f2, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mmx.14m", 0xd52bf491, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mmx.16m", 0x23f70780, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mmx.18m", 0x2562c9d5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mmx.20m", 0x583a9687, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mmatrix_audiocpu[] = {
    {"mmx.01", 0xc57e8171, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mmx.01", 0xc57e8171, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_mmatrix_qsound[] = {
    {"mmx.11m", 0x4180b39f, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mmx.12m", 0x95e22a59, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mmatrix_key[] = {
    {"mmatrix.key", 0x8ed66bc4, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mmatrix[] = {
    {"maincpu", 4194304, 0, chips_mmatrix_maincpu, N(chips_mmatrix_maincpu)},
    {"gfx", 33554432, 0, chips_mmatrix_gfx, N(chips_mmatrix_gfx)},
    {"audiocpu", 327680, 0, chips_mmatrix_audiocpu, N(chips_mmatrix_audiocpu)},
    {"qsound", 8388608, 0, chips_mmatrix_qsound, N(chips_mmatrix_qsound)},
    {"key", 32, 0, chips_mmatrix_key, N(chips_mmatrix_key)},
};
static const Cps2Load chips_mmatrixa_maincpu[] = {
    {"mmxa.03", 0x1d670ed7, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mmxa.04", 0x43be66d2, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mmxa.05", 0x9bfe3082, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mmatrixa_gfx[] = {
    {"mmx.13m", 0x04748718, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mmx.15m", 0x38074f44, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mmx.17m", 0xe4635e35, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mmx.19m", 0x4400a3f2, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mmx.14m", 0xd52bf491, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mmx.16m", 0x23f70780, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mmx.18m", 0x2562c9d5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mmx.20m", 0x583a9687, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mmatrixa_audiocpu[] = {
    {"mmx.01", 0xc57e8171, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mmx.01", 0xc57e8171, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_mmatrixa_qsound[] = {
    {"mmx.11m", 0x4180b39f, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mmx.12m", 0x95e22a59, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mmatrixa_key[] = {
    {"mmatrixa.key", 0xf6a944b4, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mmatrixa[] = {
    {"maincpu", 4194304, 0, chips_mmatrixa_maincpu, N(chips_mmatrixa_maincpu)},
    {"gfx", 33554432, 0, chips_mmatrixa_gfx, N(chips_mmatrixa_gfx)},
    {"audiocpu", 327680, 0, chips_mmatrixa_audiocpu, N(chips_mmatrixa_audiocpu)},
    {"qsound", 8388608, 0, chips_mmatrixa_qsound, N(chips_mmatrixa_qsound)},
    {"key", 32, 0, chips_mmatrixa_key, N(chips_mmatrixa_key)},
};
static const Cps2Load chips_mmatrixj_maincpu[] = {
    {"mmxj.03", 0x1d5de213, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mmxj.04", 0xd943a339, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mmxj.05", 0x0c8b4abb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mmatrixj_gfx[] = {
    {"mmx.13m", 0x04748718, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mmx.15m", 0x38074f44, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mmx.17m", 0xe4635e35, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mmx.19m", 0x4400a3f2, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mmx.14m", 0xd52bf491, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mmx.16m", 0x23f70780, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mmx.18m", 0x2562c9d5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mmx.20m", 0x583a9687, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mmatrixj_audiocpu[] = {
    {"mmx.01", 0xc57e8171, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mmx.01", 0xc57e8171, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_mmatrixj_qsound[] = {
    {"mmx.11m", 0x4180b39f, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mmx.12m", 0x95e22a59, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mmatrixj_key[] = {
    {"mmatrixj.key", 0x3b50d889, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mmatrixj[] = {
    {"maincpu", 4194304, 0, chips_mmatrixj_maincpu, N(chips_mmatrixj_maincpu)},
    {"gfx", 33554432, 0, chips_mmatrixj_gfx, N(chips_mmatrixj_gfx)},
    {"audiocpu", 327680, 0, chips_mmatrixj_audiocpu, N(chips_mmatrixj_audiocpu)},
    {"qsound", 8388608, 0, chips_mmatrixj_qsound, N(chips_mmatrixj_qsound)},
    {"key", 32, 0, chips_mmatrixj_key, N(chips_mmatrixj_key)},
};
static const Cps2Load chips_mpang_maincpu[] = {
    {"mpne.03c", 0xfe16fc9f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mpne.04c", 0x2cc5ec22, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mpang_gfx[] = {
    {"mpn-simm.01c", 0x388db66b, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"mpn-simm.01d", 0xaff1b494, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"mpn-simm.01a", 0xa9c4857b, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"mpn-simm.01b", 0xf759df22, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"mpn-simm.03c", 0xdec6b720, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"mpn-simm.03d", 0xf8774c18, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"mpn-simm.03a", 0xc2aea4ec, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"mpn-simm.03b", 0x84d6dc33, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_mpang_audiocpu[] = {
    {"mpn.01", 0x90c7adb6, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mpn.01", 0x90c7adb6, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_mpang_qsound[] = {
    {"mpn-simm.05a", 0x318a2e21, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"mpn-simm.05b", 0x5462f4e8, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_mpang_key[] = {
    {"mpang.key", 0x95354b0f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mpang[] = {
    {"maincpu", 4194304, 0, chips_mpang_maincpu, N(chips_mpang_maincpu)},
    {"gfx", 16777216, 0, chips_mpang_gfx, N(chips_mpang_gfx)},
    {"audiocpu", 327680, 0, chips_mpang_audiocpu, N(chips_mpang_audiocpu)},
    {"qsound", 4194304, 0, chips_mpang_qsound, N(chips_mpang_qsound)},
    {"key", 32, 0, chips_mpang_key, N(chips_mpang_key)},
};
static const Cps2Load chips_mpangr1_maincpu[] = {
    {"mpne.03b", 0x6ef0f9b2, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mpne.04b", 0x30a468bb, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mpangr1_gfx[] = {
    {"mpn-simm.01c", 0x388db66b, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"mpn-simm.01d", 0xaff1b494, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"mpn-simm.01a", 0xa9c4857b, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"mpn-simm.01b", 0xf759df22, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"mpn-simm.03c", 0xdec6b720, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"mpn-simm.03d", 0xf8774c18, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"mpn-simm.03a", 0xc2aea4ec, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"mpn-simm.03b", 0x84d6dc33, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_mpangr1_audiocpu[] = {
    {"mpn.01", 0x90c7adb6, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mpn.01", 0x90c7adb6, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_mpangr1_qsound[] = {
    {"mpn-simm.05a", 0x318a2e21, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"mpn-simm.05b", 0x5462f4e8, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_mpangr1_key[] = {
    {"mpang.key", 0x95354b0f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mpangr1[] = {
    {"maincpu", 4194304, 0, chips_mpangr1_maincpu, N(chips_mpangr1_maincpu)},
    {"gfx", 16777216, 0, chips_mpangr1_gfx, N(chips_mpangr1_gfx)},
    {"audiocpu", 327680, 0, chips_mpangr1_audiocpu, N(chips_mpangr1_audiocpu)},
    {"qsound", 4194304, 0, chips_mpangr1_qsound, N(chips_mpangr1_qsound)},
    {"key", 32, 0, chips_mpangr1_key, N(chips_mpangr1_key)},
};
static const Cps2Load chips_mpangu_maincpu[] = {
    {"mpnu.03", 0x6e7ed03c, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mpnu.04", 0xde079131, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mpangu_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"mpn.13m", 0xc5f123dc, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"mpn.15m", 0x8e033265, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"mpn.17m", 0xcfcd73d2, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"mpn.19m", 0x2db1ffbc, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_mpangu_audiocpu[] = {
    {"mpn.01", 0x90c7adb6, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mpn.01", 0x90c7adb6, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_mpangu_qsound[] = {
    {"mpn.q1", 0xd21c1f5a, 1048576, 0, 0, 1048576, CPS2_LINEAR},
    {"mpn.q2", 0xd22090b1, 1048576, 0, 1048576, 1048576, CPS2_LINEAR},
    {"mpn.q3", 0x60aa5ef2, 1048576, 0, 2097152, 1048576, CPS2_LINEAR},
    {"mpn.q4", 0x3a67d203, 1048576, 0, 3145728, 1048576, CPS2_LINEAR},
};
static const Cps2Load chips_mpangu_key[] = {
    {"mpang.key", 0x95354b0f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mpangu[] = {
    {"maincpu", 4194304, 0, chips_mpangu_maincpu, N(chips_mpangu_maincpu)},
    {"gfx", 16777216, 0, chips_mpangu_gfx, N(chips_mpangu_gfx)},
    {"audiocpu", 327680, 0, chips_mpangu_audiocpu, N(chips_mpangu_audiocpu)},
    {"qsound", 4194304, 0, chips_mpangu_qsound, N(chips_mpangu_qsound)},
    {"key", 32, 0, chips_mpangu_key, N(chips_mpangu_key)},
};
static const Cps2Load chips_mpangj_maincpu[] = {
    {"mpnj.03a", 0xbf597b1c, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mpnj.04a", 0xf4a3ab0f, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mpangj_gfx[] = {
    {"mpn-simm.01c", 0x388db66b, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"mpn-simm.01d", 0xaff1b494, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"mpn-simm.01a", 0xa9c4857b, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"mpn-simm.01b", 0xf759df22, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"mpn-simm.03c", 0xdec6b720, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"mpn-simm.03d", 0xf8774c18, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"mpn-simm.03a", 0xc2aea4ec, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"mpn-simm.03b", 0x84d6dc33, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_mpangj_audiocpu[] = {
    {"mpn.01", 0x90c7adb6, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mpn.01", 0x90c7adb6, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_mpangj_qsound[] = {
    {"mpn-simm.05a", 0x318a2e21, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"mpn-simm.05b", 0x5462f4e8, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_mpangj_key[] = {
    {"mpang.key", 0x95354b0f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mpangj[] = {
    {"maincpu", 4194304, 0, chips_mpangj_maincpu, N(chips_mpangj_maincpu)},
    {"gfx", 16777216, 0, chips_mpangj_gfx, N(chips_mpangj_gfx)},
    {"audiocpu", 327680, 0, chips_mpangj_audiocpu, N(chips_mpangj_audiocpu)},
    {"qsound", 4194304, 0, chips_mpangj_qsound, N(chips_mpangj_qsound)},
    {"key", 32, 0, chips_mpangj_key, N(chips_mpangj_key)},
};
static const Cps2Load chips_mpanga_maincpu[] = {
    {"mpn_03a.6a", 0xb05ebc34, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mpn_04a.7a", 0x8e4814b4, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mpanga_gfx[] = {
    {"mpn-simm.01c", 0x388db66b, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"mpn-simm.01d", 0xaff1b494, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"mpn-simm.01a", 0xa9c4857b, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"mpn-simm.01b", 0xf759df22, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"mpn-simm.03c", 0xdec6b720, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"mpn-simm.03d", 0xf8774c18, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"mpn-simm.03a", 0xc2aea4ec, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"mpn-simm.03b", 0x84d6dc33, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_mpanga_audiocpu[] = {
    {"mpn.01", 0x90c7adb6, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mpn.01", 0x90c7adb6, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_mpanga_qsound[] = {
    {"mpn-simm.05a", 0x318a2e21, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"mpn-simm.05b", 0x5462f4e8, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_mpanga_key[] = {
    {"mpang.key", 0x95354b0f, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mpanga[] = {
    {"maincpu", 4194304, 0, chips_mpanga_maincpu, N(chips_mpanga_maincpu)},
    {"gfx", 16777216, 0, chips_mpanga_gfx, N(chips_mpanga_gfx)},
    {"audiocpu", 327680, 0, chips_mpanga_audiocpu, N(chips_mpanga_audiocpu)},
    {"qsound", 4194304, 0, chips_mpanga_qsound, N(chips_mpanga_qsound)},
    {"key", 32, 0, chips_mpanga_key, N(chips_mpanga_key)},
};
static const Cps2Load chips_pzloop2_maincpu[] = {
    {"pl2e.03", 0x3b1285b2, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pl2e.04", 0x40a2d647, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pl2e.05", 0x0f11d818, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pl2e.06", 0x86fbbdf4, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_pzloop2_gfx[] = {
    {"pl2-simm.01c", 0x137b13a7, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"pl2-simm.01d", 0xa2db1507, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"pl2-simm.01a", 0x7e80ff8e, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"pl2-simm.01b", 0xcd93e6ed, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"pl2-simm.03c", 0x0f52bbca, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"pl2-simm.03d", 0xa62712c3, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"pl2-simm.03a", 0xb60c9f8e, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"pl2-simm.03b", 0x83fef284, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_pzloop2_audiocpu[] = {
    {"pl2.01", 0x35697569, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pl2.01", 0x35697569, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_pzloop2_qsound[] = {
    {"pl2-simm.05a", 0x85d8fbe8, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pl2-simm.05b", 0x1ed62584, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_pzloop2_key[] = {
    {"pzloop2.key", 0xae13be78, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_pzloop2[] = {
    {"maincpu", 4194304, 0, chips_pzloop2_maincpu, N(chips_pzloop2_maincpu)},
    {"gfx", 16777216, 0, chips_pzloop2_gfx, N(chips_pzloop2_gfx)},
    {"audiocpu", 327680, 0, chips_pzloop2_audiocpu, N(chips_pzloop2_audiocpu)},
    {"qsound", 4194304, 0, chips_pzloop2_qsound, N(chips_pzloop2_qsound)},
    {"key", 32, 0, chips_pzloop2_key, N(chips_pzloop2_key)},
};
static const Cps2Load chips_pzloop2j_maincpu[] = {
    {"pl2j.03c", 0x3b76b806, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pl2j.04c", 0x8878a42a, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pl2j.05c", 0x51081ea4, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pl2j.06c", 0x51c68494, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_pzloop2j_gfx[] = {
    {"pl2-simm.01c", 0x137b13a7, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"pl2-simm.01d", 0xa2db1507, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"pl2-simm.01a", 0x7e80ff8e, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"pl2-simm.01b", 0xcd93e6ed, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"pl2-simm.03c", 0x0f52bbca, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"pl2-simm.03d", 0xa62712c3, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"pl2-simm.03a", 0xb60c9f8e, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"pl2-simm.03b", 0x83fef284, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_pzloop2j_audiocpu[] = {
    {"pl2.01", 0x35697569, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pl2.01", 0x35697569, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_pzloop2j_qsound[] = {
    {"pl2-simm.05a", 0x85d8fbe8, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pl2-simm.05b", 0x1ed62584, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_pzloop2j_key[] = {
    {"pzloop2.key", 0xae13be78, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_pzloop2j[] = {
    {"maincpu", 4194304, 0, chips_pzloop2j_maincpu, N(chips_pzloop2j_maincpu)},
    {"gfx", 16777216, 0, chips_pzloop2j_gfx, N(chips_pzloop2j_gfx)},
    {"audiocpu", 327680, 0, chips_pzloop2j_audiocpu, N(chips_pzloop2j_audiocpu)},
    {"qsound", 4194304, 0, chips_pzloop2j_qsound, N(chips_pzloop2j_qsound)},
    {"key", 32, 0, chips_pzloop2j_key, N(chips_pzloop2j_key)},
};
static const Cps2Load chips_pzloop2jr1_maincpu[] = {
    {"pl2j.03a", 0x0a751bd0, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pl2j.04a", 0xc3f72afe, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pl2j.05a", 0x6ea9dbfc, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pl2j.06a", 0x0f14848d, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_pzloop2jr1_gfx[] = {
    {"pl2-simm.01c", 0x137b13a7, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"pl2-simm.01d", 0xa2db1507, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"pl2-simm.01a", 0x7e80ff8e, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"pl2-simm.01b", 0xcd93e6ed, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"pl2-simm.03c", 0x0f52bbca, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"pl2-simm.03d", 0xa62712c3, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"pl2-simm.03a", 0xb60c9f8e, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"pl2-simm.03b", 0x83fef284, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_pzloop2jr1_audiocpu[] = {
    {"pl2.01", 0x35697569, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pl2.01", 0x35697569, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_pzloop2jr1_qsound[] = {
    {"pl2-simm.05a", 0x85d8fbe8, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pl2-simm.05b", 0x1ed62584, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_pzloop2jr1_key[] = {
    {"pzloop2.key", 0xae13be78, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_pzloop2jr1[] = {
    {"maincpu", 4194304, 0, chips_pzloop2jr1_maincpu, N(chips_pzloop2jr1_maincpu)},
    {"gfx", 16777216, 0, chips_pzloop2jr1_gfx, N(chips_pzloop2jr1_gfx)},
    {"audiocpu", 327680, 0, chips_pzloop2jr1_audiocpu, N(chips_pzloop2jr1_audiocpu)},
    {"qsound", 4194304, 0, chips_pzloop2jr1_qsound, N(chips_pzloop2jr1_qsound)},
    {"key", 32, 0, chips_pzloop2jr1_key, N(chips_pzloop2jr1_key)},
};
static const Cps2Load chips_pzloop2jp_maincpu[] = {
    {"pl2j_03.bin", 0xe9f904c3, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pl2j_04.bin", 0x61c7c18f, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pl2j_05.bin", 0xee6da97c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pl2j_06.bin", 0x97e1c3ac, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_pzloop2jp_gfx[] = {
    {"pl2-13m.bin", 0x5f3b5f91, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"pl2-15m.bin", 0x3702f309, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"pl2-17m.bin", 0x62d3fce9, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"pl2-19m.bin", 0x6dcbd8ce, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"pl2-14m.bin", 0x2e22e71a, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"pl2-16m.bin", 0x38090022, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"pl2-18m.bin", 0x33afdd44, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"pl2-20m.bin", 0xd4ae0278, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_pzloop2jp_audiocpu[] = {
    {"pl2_01.bin", 0x35697569, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pl2_01.bin", 0x35697569, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_pzloop2jp_qsound[] = {
    {"pl2-11m.bin", 0x85d8fbe8, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pl2-12m.bin", 0x1ed62584, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_pzloop2jp_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_pzloop2jp[] = {
    {"maincpu", 4194304, 0, chips_pzloop2jp_maincpu, N(chips_pzloop2jp_maincpu)},
    {"gfx", 16777216, 0, chips_pzloop2jp_gfx, N(chips_pzloop2jp_gfx)},
    {"audiocpu", 327680, 0, chips_pzloop2jp_audiocpu, N(chips_pzloop2jp_audiocpu)},
    {"qsound", 4194304, 0, chips_pzloop2jp_qsound, N(chips_pzloop2jp_qsound)},
    {"key", 32, 0, chips_pzloop2jp_key, N(chips_pzloop2jp_key)},
};
static const Cps2Load chips_choko_maincpu[] = {
    {"tkoj.03", 0x11f5452f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"tkoj.04", 0x68655378, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_choko_gfx[] = {
    {"tkoj1_d.simm1", 0x6933377d, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"tkoj1_c.simm1", 0x7f668950, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"tkoj1_b.simm1", 0xcfb68ca9, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"tkoj1_a.simm1", 0x437e21c5, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"tkoj3_d.simm3", 0xa9e32b57, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"tkoj3_c.simm3", 0xb7ab9338, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"tkoj3_b.simm3", 0x4d3f919a, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"tkoj3_a.simm3", 0xcfef17ab, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_choko_audiocpu[] = {
    {"tko.01", 0x6eda50c2, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"tko.01", 0x6eda50c2, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_choko_qsound[] = {
    {"tkoj5_a.simm5", 0xab45d509, 2097152, 0, 0, 2097152, CPS2_BYTE16},
    {"tkoj5_b.simm5", 0xfa905c3d, 2097152, 0, 1, 2097152, CPS2_BYTE16},
};
static const Cps2Load chips_choko_key[] = {
    {"choko.key", 0x08505e8b, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_choko[] = {
    {"maincpu", 4194304, 255, chips_choko_maincpu, N(chips_choko_maincpu)},
    {"gfx", 16777216, 0, chips_choko_gfx, N(chips_choko_gfx)},
    {"audiocpu", 327680, 0, chips_choko_audiocpu, N(chips_choko_audiocpu)},
    {"qsound", 4194304, 0, chips_choko_qsound, N(chips_choko_qsound)},
    {"key", 32, 0, chips_choko_key, N(chips_choko_key)},
};
static const Cps2Load chips_chokop_maincpu[] = {
    {"tkojp_03.bin", 0x4d857f39, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"tkojp_04.bin", 0x137afb29, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_chokop_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"tko_14.bin", 0x336e8aa2, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"tko_16.bin", 0xe8429b54, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"tko_18.bin", 0x62092fbd, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"tko_20.bin", 0xb468a666, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_chokop_audiocpu[] = {
    {"tko_01.bin", 0x6eda50c2, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"tko_01.bin", 0x6eda50c2, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_chokop_qsound[] = {
    {"tko_11.bin", 0xca7179b1, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"tko_12.bin", 0x83a4e635, 1048576, 0, 2097152, 1048576, CPS2_SWAP16},
};
static const Cps2Load chips_chokop_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_chokop[] = {
    {"maincpu", 4194304, 0, chips_chokop_maincpu, N(chips_chokop_maincpu)},
    {"gfx", 16777216, 0, chips_chokop_gfx, N(chips_chokop_gfx)},
    {"audiocpu", 327680, 0, chips_chokop_audiocpu, N(chips_chokop_audiocpu)},
    {"qsound", 3145728, 0, chips_chokop_qsound, N(chips_chokop_qsound)},
    {"key", 32, 0, chips_chokop_key, N(chips_chokop_key)},
};
static const Cps2Load chips_dimahoo_maincpu[] = {
    {"gmde.03", 0x968fcecd, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"gmd.04", 0x37485567, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"gmd.05", 0xda269ffb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"gmd.06", 0x55b483c9, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_dimahoo_gfx[] = {
    {"gmd.13m", 0x80dd19f0, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"gmd.15m", 0xdfd93a78, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"gmd.17m", 0x16356520, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"gmd.19m", 0xdfc33031, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_dimahoo_audiocpu[] = {
    {"gmd.01", 0x3f9bc985, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"gmd.01", 0x3f9bc985, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"gmd.02", 0x3fd39dde, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_dimahoo_qsound[] = {
    {"gmd.11m", 0x06a65542, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"gmd.12m", 0x50bc7a31, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_dimahoo_key[] = {
    {"dimahoo.key", 0x7d6d2db9, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_dimahoo[] = {
    {"maincpu", 4194304, 0, chips_dimahoo_maincpu, N(chips_dimahoo_maincpu)},
    {"gfx", 16777216, 0, chips_dimahoo_gfx, N(chips_dimahoo_gfx)},
    {"audiocpu", 327680, 0, chips_dimahoo_audiocpu, N(chips_dimahoo_audiocpu)},
    {"qsound", 8388608, 0, chips_dimahoo_qsound, N(chips_dimahoo_qsound)},
    {"key", 32, 0, chips_dimahoo_key, N(chips_dimahoo_key)},
};
static const Cps2Load chips_dimahoou_maincpu[] = {
    {"gmdu.03", 0x43bcb15f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"gmd.04", 0x37485567, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"gmd.05", 0xda269ffb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"gmd.06", 0x55b483c9, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_dimahoou_gfx[] = {
    {"gmd.13m", 0x80dd19f0, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"gmd.15m", 0xdfd93a78, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"gmd.17m", 0x16356520, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"gmd.19m", 0xdfc33031, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_dimahoou_audiocpu[] = {
    {"gmd.01", 0x3f9bc985, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"gmd.01", 0x3f9bc985, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"gmd.02", 0x3fd39dde, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_dimahoou_qsound[] = {
    {"gmd.11m", 0x06a65542, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"gmd.12m", 0x50bc7a31, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_dimahoou_key[] = {
    {"dimahoou.key", 0x8254d7ab, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_dimahoou[] = {
    {"maincpu", 4194304, 0, chips_dimahoou_maincpu, N(chips_dimahoou_maincpu)},
    {"gfx", 16777216, 0, chips_dimahoou_gfx, N(chips_dimahoou_gfx)},
    {"audiocpu", 327680, 0, chips_dimahoou_audiocpu, N(chips_dimahoou_audiocpu)},
    {"qsound", 8388608, 0, chips_dimahoou_qsound, N(chips_dimahoou_qsound)},
    {"key", 32, 0, chips_dimahoou_key, N(chips_dimahoou_key)},
};
static const Cps2Load chips_gmahou_maincpu[] = {
    {"gmdj.03", 0xcd6979e3, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"gmd.04", 0x37485567, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"gmd.05", 0xda269ffb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"gmd.06", 0x55b483c9, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_gmahou_gfx[] = {
    {"gmd.13m", 0x80dd19f0, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"gmd.15m", 0xdfd93a78, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"gmd.17m", 0x16356520, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"gmd.19m", 0xdfc33031, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_gmahou_audiocpu[] = {
    {"gmd.01", 0x3f9bc985, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"gmd.01", 0x3f9bc985, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"gmd.02", 0x3fd39dde, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_gmahou_qsound[] = {
    {"gmd.11m", 0x06a65542, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"gmd.12m", 0x50bc7a31, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_gmahou_key[] = {
    {"gmahou.key", 0x76a5e659, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_gmahou[] = {
    {"maincpu", 4194304, 0, chips_gmahou_maincpu, N(chips_gmahou_maincpu)},
    {"gfx", 16777216, 0, chips_gmahou_gfx, N(chips_gmahou_gfx)},
    {"audiocpu", 327680, 0, chips_gmahou_audiocpu, N(chips_gmahou_audiocpu)},
    {"qsound", 8388608, 0, chips_gmahou_qsound, N(chips_gmahou_qsound)},
    {"key", 32, 0, chips_gmahou_key, N(chips_gmahou_key)},
};
static const Cps2Load chips_1944_maincpu[] = {
    {"nffe.03", 0x7544b926, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"nffe.04", 0xdba1c66e, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"nffe.05", 0xd78d31d3, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_1944_gfx[] = {
    {"nff.13m", 0xc9fca741, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"nff.15m", 0xf809d898, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"nff.17m", 0x15ba4507, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"nff.19m", 0x3dd41b8c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"nff.14m", 0x3fe3a54b, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"nff.16m", 0x565cd231, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"nff.18m", 0x63ca5988, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"nff.20m", 0x21eb8f3b, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_1944_audiocpu[] = {
    {"nff.01", 0xd2e44318, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"nff.01", 0xd2e44318, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_1944_qsound[] = {
    {"nff.11m", 0x243e4e05, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"nff.12m", 0x4fcf1600, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_1944_key[] = {
    {"1944.key", 0x5f22140e, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_1944[] = {
    {"maincpu", 4194304, 0, chips_1944_maincpu, N(chips_1944_maincpu)},
    {"gfx", 20971520, 0, chips_1944_gfx, N(chips_1944_gfx)},
    {"audiocpu", 327680, 0, chips_1944_audiocpu, N(chips_1944_audiocpu)},
    {"qsound", 8388608, 0, chips_1944_qsound, N(chips_1944_qsound)},
    {"key", 32, 0, chips_1944_key, N(chips_1944_key)},
};
static const Cps2Load chips_1944j_maincpu[] = {
    {"nffj.03", 0x247521ef, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"nffj.04", 0xdba1c66e, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"nffj.05", 0x7f20c2ef, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_1944j_gfx[] = {
    {"nff.13m", 0xc9fca741, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"nff.15m", 0xf809d898, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"nff.17m", 0x15ba4507, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"nff.19m", 0x3dd41b8c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"nff.14m", 0x3fe3a54b, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"nff.16m", 0x565cd231, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"nff.18m", 0x63ca5988, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"nff.20m", 0x21eb8f3b, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_1944j_audiocpu[] = {
    {"nff.01", 0xd2e44318, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"nff.01", 0xd2e44318, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_1944j_qsound[] = {
    {"nff.11m", 0x243e4e05, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"nff.12m", 0x4fcf1600, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_1944j_key[] = {
    {"1944j.key", 0x210202aa, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_1944j[] = {
    {"maincpu", 4194304, 0, chips_1944j_maincpu, N(chips_1944j_maincpu)},
    {"gfx", 20971520, 0, chips_1944j_gfx, N(chips_1944j_gfx)},
    {"audiocpu", 327680, 0, chips_1944j_audiocpu, N(chips_1944j_audiocpu)},
    {"qsound", 8388608, 0, chips_1944j_qsound, N(chips_1944j_qsound)},
    {"key", 32, 0, chips_1944j_key, N(chips_1944j_key)},
};
static const Cps2Load chips_1944u_maincpu[] = {
    {"nffu.03", 0x9693cf8f, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"nff.04", 0xdba1c66e, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"nffu.05", 0xea813eb7, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_1944u_gfx[] = {
    {"nff.13m", 0xc9fca741, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"nff.15m", 0xf809d898, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"nff.17m", 0x15ba4507, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"nff.19m", 0x3dd41b8c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"nff.14m", 0x3fe3a54b, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"nff.16m", 0x565cd231, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"nff.18m", 0x63ca5988, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"nff.20m", 0x21eb8f3b, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_1944u_audiocpu[] = {
    {"nff.01", 0xd2e44318, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"nff.01", 0xd2e44318, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_1944u_qsound[] = {
    {"nff.11m", 0x243e4e05, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"nff.12m", 0x4fcf1600, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_1944u_key[] = {
    {"1944u.key", 0x61734f5b, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_1944u[] = {
    {"maincpu", 4194304, 0, chips_1944u_maincpu, N(chips_1944u_maincpu)},
    {"gfx", 20971520, 0, chips_1944u_gfx, N(chips_1944u_gfx)},
    {"audiocpu", 327680, 0, chips_1944u_audiocpu, N(chips_1944u_audiocpu)},
    {"qsound", 8388608, 0, chips_1944u_qsound, N(chips_1944u_qsound)},
    {"key", 32, 0, chips_1944u_key, N(chips_1944u_key)},
};
static const Cps2Load chips_progear_maincpu[] = {
    {"pgae.03", 0x8577bc86, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pgae.04", 0xd850da04, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_progear_gfx[] = {
    {"pga-simm.01c", 0x452f98b0, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"pga-simm.01d", 0x9e672092, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"pga-simm.01a", 0xae9ddafe, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"pga-simm.01b", 0x94d72d94, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"pga-simm.03c", 0x48a1886d, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"pga-simm.03d", 0x172d7e37, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"pga-simm.03a", 0x9ee33d98, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"pga-simm.03b", 0x848dee32, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_progear_audiocpu[] = {
    {"pga.01", 0xbdbfa992, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pga.01", 0xbdbfa992, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_progear_qsound[] = {
    {"pga-simm.05a", 0xc0aac80c, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pga-simm.05b", 0x37a65d86, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
    {"pga-simm.06a", 0xd3f1e934, 2097152, 0, 4194304, 2097152, CPS2_SWAP16},
    {"pga-simm.06b", 0x8b39489a, 2097152, 0, 6291456, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_progear_key[] = {
    {"progear.key", 0xeee6b2a8, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_progear[] = {
    {"maincpu", 4194304, 0, chips_progear_maincpu, N(chips_progear_maincpu)},
    {"gfx", 16777216, 0, chips_progear_gfx, N(chips_progear_gfx)},
    {"audiocpu", 327680, 0, chips_progear_audiocpu, N(chips_progear_audiocpu)},
    {"qsound", 8388608, 0, chips_progear_qsound, N(chips_progear_qsound)},
    {"key", 32, 0, chips_progear_key, N(chips_progear_key)},
};
static const Cps2Load chips_progearu_maincpu[] = {
    {"pgau.03", 0x343a783e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pgau.04", 0x16208d79, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_progearu_gfx[] = {
    {"pga-simm.01c", 0x452f98b0, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"pga-simm.01d", 0x9e672092, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"pga-simm.01a", 0xae9ddafe, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"pga-simm.01b", 0x94d72d94, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"pga-simm.03c", 0x48a1886d, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"pga-simm.03d", 0x172d7e37, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"pga-simm.03a", 0x9ee33d98, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"pga-simm.03b", 0x848dee32, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_progearu_audiocpu[] = {
    {"pga.01", 0xbdbfa992, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pga.01", 0xbdbfa992, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_progearu_qsound[] = {
    {"pga-simm.05a", 0xc0aac80c, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pga-simm.05b", 0x37a65d86, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
    {"pga-simm.06a", 0xd3f1e934, 2097152, 0, 4194304, 2097152, CPS2_SWAP16},
    {"pga-simm.06b", 0x8b39489a, 2097152, 0, 6291456, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_progearu_key[] = {
    {"progearu.key", 0x46736b17, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_progearu[] = {
    {"maincpu", 4194304, 0, chips_progearu_maincpu, N(chips_progearu_maincpu)},
    {"gfx", 16777216, 0, chips_progearu_gfx, N(chips_progearu_gfx)},
    {"audiocpu", 327680, 0, chips_progearu_audiocpu, N(chips_progearu_audiocpu)},
    {"qsound", 8388608, 0, chips_progearu_qsound, N(chips_progearu_qsound)},
    {"key", 32, 0, chips_progearu_key, N(chips_progearu_key)},
};
static const Cps2Load chips_progearj_maincpu[] = {
    {"pgaj.03", 0x06dbba54, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pgaj.04", 0xa1f1f1bc, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_progearj_gfx[] = {
    {"pga-simm.01c", 0x452f98b0, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"pga-simm.01d", 0x9e672092, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"pga-simm.01a", 0xae9ddafe, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"pga-simm.01b", 0x94d72d94, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"pga-simm.03c", 0x48a1886d, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"pga-simm.03d", 0x172d7e37, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"pga-simm.03a", 0x9ee33d98, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"pga-simm.03b", 0x848dee32, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_progearj_audiocpu[] = {
    {"pga.01", 0xbdbfa992, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pga.01", 0xbdbfa992, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_progearj_qsound[] = {
    {"pga-simm.05a", 0xc0aac80c, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pga-simm.05b", 0x37a65d86, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
    {"pga-simm.06a", 0xd3f1e934, 2097152, 0, 4194304, 2097152, CPS2_SWAP16},
    {"pga-simm.06b", 0x8b39489a, 2097152, 0, 6291456, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_progearj_key[] = {
    {"progearj.key", 0xd8d515e5, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_progearj[] = {
    {"maincpu", 4194304, 0, chips_progearj_maincpu, N(chips_progearj_maincpu)},
    {"gfx", 16777216, 0, chips_progearj_gfx, N(chips_progearj_gfx)},
    {"audiocpu", 327680, 0, chips_progearj_audiocpu, N(chips_progearj_audiocpu)},
    {"qsound", 8388608, 0, chips_progearj_qsound, N(chips_progearj_qsound)},
    {"key", 32, 0, chips_progearj_key, N(chips_progearj_key)},
};
static const Cps2Load chips_progeara_maincpu[] = {
    {"pgaa.03", 0x25e6e2ce, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pgaa.04", 0x8104307e, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_progeara_gfx[] = {
    {"pga-simm.01c", 0x452f98b0, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"pga-simm.01d", 0x9e672092, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"pga-simm.01a", 0xae9ddafe, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"pga-simm.01b", 0x94d72d94, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"pga-simm.03c", 0x48a1886d, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"pga-simm.03d", 0x172d7e37, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"pga-simm.03a", 0x9ee33d98, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"pga-simm.03b", 0x848dee32, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_progeara_audiocpu[] = {
    {"pga.01", 0xbdbfa992, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pga.01", 0xbdbfa992, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_progeara_qsound[] = {
    {"pga-simm.05a", 0xc0aac80c, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pga-simm.05b", 0x37a65d86, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
    {"pga-simm.06a", 0xd3f1e934, 2097152, 0, 4194304, 2097152, CPS2_SWAP16},
    {"pga-simm.06b", 0x8b39489a, 2097152, 0, 6291456, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_progeara_key[] = {
    {"progeara.key", 0x30a0fab6, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_progeara[] = {
    {"maincpu", 4194304, 0, chips_progeara_maincpu, N(chips_progeara_maincpu)},
    {"gfx", 16777216, 0, chips_progeara_gfx, N(chips_progeara_gfx)},
    {"audiocpu", 327680, 0, chips_progeara_audiocpu, N(chips_progeara_audiocpu)},
    {"qsound", 8388608, 0, chips_progeara_qsound, N(chips_progeara_qsound)},
    {"key", 32, 0, chips_progeara_key, N(chips_progeara_key)},
};
static const Cps2Load chips_ddtodd_maincpu[] = {
    {"daded.03c", 0x843330f4, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"daded.04c", 0x306f14fc, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"daded.05c", 0x8c6b8328, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dad.06a", 0x6225495a, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dadd.07a", 0x0f0df6cc, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodd_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_ddtodd_gfx[] = {
    {"dad.13m", 0xda3cb7d6, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"dad.15m", 0x92b63172, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"dad.17m", 0xb98757f5, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"dad.19m", 0x8121ce46, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"dad.14m", 0x837e6f3f, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"dad.16m", 0xf0916bdb, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"dad.18m", 0xcef393ef, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"dad.20m", 0x8953fe9e, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ddtodd_audiocpu[] = {
    {"dad.01", 0x3f5e2424, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dad.01", 0x3f5e2424, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ddtodd_qsound[] = {
    {"dad.11m", 0x0c499b67, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dad.12m", 0x2f0b5a4e, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddtodd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddtodd[] = {
    {"maincpu", 4194304, 0, chips_ddtodd_maincpu, N(chips_ddtodd_maincpu)},
    {"user1", 4194304, 0, chips_ddtodd_user1, N(chips_ddtodd_user1)},
    {"gfx", 12582912, 0, chips_ddtodd_gfx, N(chips_ddtodd_gfx)},
    {"audiocpu", 327680, 0, chips_ddtodd_audiocpu, N(chips_ddtodd_audiocpu)},
    {"qsound", 4194304, 0, chips_ddtodd_qsound, N(chips_ddtodd_qsound)},
    {"key", 32, 0, chips_ddtodd_key, N(chips_ddtodd_key)},
};
static const Cps2Load chips_ecofghtrd_maincpu[] = {
    {"ueced.03", 0xac725d2b, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ueced.04", 0xf800138d, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ueced.05", 0xeb6a12f2, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ueced.06", 0x8380ec9a, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ecofghtrd_gfx[] = {
    {"uec.13m", 0xdcaf1436, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"uec.15m", 0x2807df41, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"uec.17m", 0x8a708d02, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"uec.19m", 0xde7be0ef, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"uec.14m", 0x1a003558, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"uec.16m", 0x4ff8a6f9, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"uec.18m", 0xb167ae12, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"uec.20m", 0x1064bdc2, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ecofghtrd_audiocpu[] = {
    {"uec.01", 0xc235bd15, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"uec.01", 0xc235bd15, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ecofghtrd_qsound[] = {
    {"uec.11m", 0x81b25d39, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"uec.12m", 0x27729e52, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ecofghtrd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ecofghtrd[] = {
    {"maincpu", 4194304, 0, chips_ecofghtrd_maincpu, N(chips_ecofghtrd_maincpu)},
    {"gfx", 12582912, 0, chips_ecofghtrd_gfx, N(chips_ecofghtrd_gfx)},
    {"audiocpu", 327680, 0, chips_ecofghtrd_audiocpu, N(chips_ecofghtrd_audiocpu)},
    {"qsound", 4194304, 0, chips_ecofghtrd_qsound, N(chips_ecofghtrd_qsound)},
    {"key", 32, 0, chips_ecofghtrd_key, N(chips_ecofghtrd_key)},
};
static const Cps2Load chips_ssf2ud_maincpu[] = {
    {"ssfud.03a", 0xfad5daf8, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfud.04a", 0x0d31af65, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfud.05", 0x75c651ef, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfud.06", 0x85c3ec00, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfud.07", 0x247e2504, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2ud_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2ud_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2ud_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2ud_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2ud[] = {
    {"maincpu", 4194304, 0, chips_ssf2ud_maincpu, N(chips_ssf2ud_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2ud_gfx, N(chips_ssf2ud_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2ud_audiocpu, N(chips_ssf2ud_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2ud_qsound, N(chips_ssf2ud_qsound)},
    {"key", 32, 0, chips_ssf2ud_key, N(chips_ssf2ud_key)},
};
static const Cps2Load chips_ssf2tbd_maincpu[] = {
    {"ssfed.3tc", 0x5d86caf8, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ssfed.4tc", 0xf6e1f98d, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ssfed.5t", 0x75c651ef, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"ssfed.6tb", 0x9adac7d7, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"ssfed.7t", 0x84f54db3, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2tbd_gfx[] = {
    {"ssf.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"ssf.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"ssf.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"ssf.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"ssf.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"ssf.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"ssf.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"ssf.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2tbd_audiocpu[] = {
    {"ssf.01", 0xeb247e8c, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ssf.01", 0xeb247e8c, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tbd_qsound[] = {
    {"ssf.q01", 0xa6f9da5c, 524288, 0, 0, 524288, CPS2_LINEAR},
    {"ssf.q02", 0x8c66ae26, 524288, 0, 524288, 524288, CPS2_LINEAR},
    {"ssf.q03", 0x695cc2ca, 524288, 0, 1048576, 524288, CPS2_LINEAR},
    {"ssf.q04", 0x9d9ebe32, 524288, 0, 1572864, 524288, CPS2_LINEAR},
    {"ssf.q05", 0x4770e7b7, 524288, 0, 2097152, 524288, CPS2_LINEAR},
    {"ssf.q06", 0x4e79c951, 524288, 0, 2621440, 524288, CPS2_LINEAR},
    {"ssf.q07", 0xcdd14313, 524288, 0, 3145728, 524288, CPS2_LINEAR},
    {"ssf.q08", 0x6f5a088c, 524288, 0, 3670016, 524288, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tbd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2tbd[] = {
    {"maincpu", 4194304, 0, chips_ssf2tbd_maincpu, N(chips_ssf2tbd_maincpu)},
    {"gfx", 12582912, 0, chips_ssf2tbd_gfx, N(chips_ssf2tbd_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2tbd_audiocpu, N(chips_ssf2tbd_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2tbd_qsound, N(chips_ssf2tbd_qsound)},
    {"key", 32, 0, chips_ssf2tbd_key, N(chips_ssf2tbd_key)},
};
static const Cps2Load chips_armwar1d_maincpu[] = {
    {"pwged.03b", 0x496bd483, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pwged.04b", 0x9bd6a38f, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pwged.05a", 0x4c11d30f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pwg.06", 0x87a60ce8, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"pwg.07", 0xf7b148df, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"pwg.08", 0xcc62823e, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"pwg.09", 0xddc85ca6, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"pwg.10", 0x07c4fb28, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_armwar1d_gfx[] = {
    {"pwg.13m", 0xae8fe08e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pwg.15m", 0xdb560f58, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pwg.17m", 0xbc475b94, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pwg.19m", 0x07439ff7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"pwg.14m", 0xc3f9ba63, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"pwg.16m", 0x815b0e7b, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"pwg.18m", 0x0109c71b, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"pwg.20m", 0xeb75ffbe, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_armwar1d_audiocpu[] = {
    {"pwg.01", 0x18a5c0e4, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pwg.01", 0x18a5c0e4, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pwg.02", 0xc9dfffa6, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_armwar1d_qsound[] = {
    {"pwg.11m", 0xa78f7433, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pwg.12m", 0x77438ed0, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_armwar1d_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_armwar1d[] = {
    {"maincpu", 4194304, 0, chips_armwar1d_maincpu, N(chips_armwar1d_maincpu)},
    {"gfx", 20971520, 0, chips_armwar1d_gfx, N(chips_armwar1d_gfx)},
    {"audiocpu", 327680, 0, chips_armwar1d_audiocpu, N(chips_armwar1d_audiocpu)},
    {"qsound", 4194304, 0, chips_armwar1d_qsound, N(chips_armwar1d_qsound)},
    {"key", 32, 0, chips_armwar1d_key, N(chips_armwar1d_key)},
};
static const Cps2Load chips_avspd_maincpu[] = {
    {"avped.03d", 0x66aa8aad, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"avped.04d", 0x579306c2, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"avp.05d", 0xfbfb5d7a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"avpd.06", 0x63094539, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_avspd_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_avspd_gfx[] = {
    {"avp.13m", 0x8f8b5ae4, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"avp.15m", 0xb00280df, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"avp.17m", 0x94403195, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"avp.19m", 0xe1981245, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"avp.14m", 0x39933b1e, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"avp.16m", 0x85412860, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"avp.18m", 0x2e2beb06, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"avp.20m", 0xe4798d1a, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_avspd_audiocpu[] = {
    {"avp.01", 0x2d3b4220, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"avp.01", 0x2d3b4220, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_avspd_qsound[] = {
    {"avp.11m", 0x83499817, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"avp.12m", 0xf4110d49, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_avspd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_avspd[] = {
    {"maincpu", 4194304, 0, chips_avspd_maincpu, N(chips_avspd_maincpu)},
    {"user1", 4194304, 0, chips_avspd_user1, N(chips_avspd_user1)},
    {"gfx", 16777216, 0, chips_avspd_gfx, N(chips_avspd_gfx)},
    {"audiocpu", 327680, 0, chips_avspd_audiocpu, N(chips_avspd_audiocpu)},
    {"qsound", 4194304, 0, chips_avspd_qsound, N(chips_avspd_qsound)},
    {"key", 32, 0, chips_avspd_key, N(chips_avspd_key)},
};
static const Cps2Load chips_dstlku1d_maincpu[] = {
    {"vamud.03a", 0x47b7a680, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vamud.04a", 0x3b7a4939, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vamu.05a", 0x673ed50a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vamu.06a", 0xf2377be7, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vamu.07a", 0xd8f498c4, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vamu.08a", 0xe6a8a1a0, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vamud.09a", 0x8b333a19, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vamu.10a", 0xc1a3d9be, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_dstlku1d_gfx[] = {
    {"vam.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vam.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vam.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vam.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vam.14m", 0xbd87243c, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"vam.16m", 0xafec855f, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"vam.18m", 0x3a033625, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"vam.20m", 0x2bff6a89, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_dstlku1d_audiocpu[] = {
    {"vam.01", 0x64b685d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vam.01", 0x64b685d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vam.02", 0xcf7c97c7, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_dstlku1d_qsound[] = {
    {"vam.11m", 0x4a39deb2, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vam.12m", 0x1a3e5c03, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_dstlku1d_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_dstlku1d[] = {
    {"maincpu", 4194304, 0, chips_dstlku1d_maincpu, N(chips_dstlku1d_maincpu)},
    {"gfx", 20971520, 0, chips_dstlku1d_gfx, N(chips_dstlku1d_gfx)},
    {"audiocpu", 327680, 0, chips_dstlku1d_audiocpu, N(chips_dstlku1d_audiocpu)},
    {"qsound", 4194304, 0, chips_dstlku1d_qsound, N(chips_dstlku1d_qsound)},
    {"key", 32, 0, chips_dstlku1d_key, N(chips_dstlku1d_key)},
};
static const Cps2Load chips_ringdstd_maincpu[] = {
    {"smbed.03b", 0xf6fba4cd, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"smbed.04b", 0x193bc493, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"smbed.05b", 0x168cccbb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"smbed.06b", 0x04673262, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"smb.07", 0xb9a11577, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"smb.08", 0xf931b76b, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ringdstd_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_ringdstd_gfx[] = {
    {"smb.13m", 0xd9b2d1de, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"smb.15m", 0x9a766d92, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"smb.17m", 0x51800f0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"smb.19m", 0x35757e96, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"smb.14m", 0xe5bfd0e7, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"smb.16m", 0xc56c0866, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"smb.18m", 0x4ded3910, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"smb.20m", 0x26ea1ec5, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
    {"smb.21m", 0x0a08c5fc, 524288, 0, 16777216, 524288, CPS2_WORD64},
    {"smb.23m", 0x0911b6c4, 524288, 0, 16777218, 524288, CPS2_WORD64},
    {"smb.25m", 0x82d6c4ec, 524288, 0, 16777220, 524288, CPS2_WORD64},
    {"smb.27m", 0x9b48678b, 524288, 0, 16777222, 524288, CPS2_WORD64},
};
static const Cps2Load chips_ringdstd_audiocpu[] = {
    {"smb.01", 0x0abc229a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"smb.01", 0x0abc229a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"smb.02", 0xd051679a, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ringdstd_qsound[] = {
    {"smb.11m", 0xc56935f9, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"smb.12m", 0x955b0782, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ringdstd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ringdstd[] = {
    {"maincpu", 4194304, 0, chips_ringdstd_maincpu, N(chips_ringdstd_maincpu)},
    {"user1", 4194304, 0, chips_ringdstd_user1, N(chips_ringdstd_user1)},
    {"gfx", 18874368, 0, chips_ringdstd_gfx, N(chips_ringdstd_gfx)},
    {"audiocpu", 327680, 0, chips_ringdstd_audiocpu, N(chips_ringdstd_audiocpu)},
    {"qsound", 4194304, 0, chips_ringdstd_qsound, N(chips_ringdstd_qsound)},
    {"key", 32, 0, chips_ringdstd_key, N(chips_ringdstd_key)},
};
static const Cps2Load chips_ssf2tad_maincpu[] = {
    {"sfxad.03c", 0xe3c92ece, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfxad.04a", 0x9bf3bb2e, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfxad.05", 0xc63358d0, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfxad.06a", 0xccb29808, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sfxad.07", 0x61f94982, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sfxad.08", 0xd399c36c, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sfxad.09", 0x436784ae, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2tad_gfx[] = {
    {"sfx.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"sfx.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"sfx.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"sfx.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"sfx.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"sfx.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"sfx.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"sfx.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
    {"sfx.21m", 0xe32854af, 1048576, 0, 12582912, 1048576, CPS2_WORD64},
    {"sfx.23m", 0x760f2927, 1048576, 0, 12582914, 1048576, CPS2_WORD64},
    {"sfx.25m", 0x1ee90208, 1048576, 0, 12582916, 1048576, CPS2_WORD64},
    {"sfx.27m", 0xf814400f, 1048576, 0, 12582918, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2tad_audiocpu[] = {
    {"sfx.01", 0xb47b8835, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfx.01", 0xb47b8835, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfx.02", 0x0022633f, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2tad_qsound[] = {
    {"sfx.11m", 0x9bdbd476, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfx.12m", 0xa05e3aab, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2tad_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2tad[] = {
    {"maincpu", 4194304, 0, chips_ssf2tad_maincpu, N(chips_ssf2tad_maincpu)},
    {"gfx", 16777216, 0, chips_ssf2tad_gfx, N(chips_ssf2tad_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2tad_audiocpu, N(chips_ssf2tad_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2tad_qsound, N(chips_ssf2tad_qsound)},
    {"key", 32, 0, chips_ssf2tad_key, N(chips_ssf2tad_key)},
};
static const Cps2Load chips_ssf2xjr1d_maincpu[] = {
    {"sfxjd.03c", 0x316de996, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfxjd.04a", 0x9bf3bb2e, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfxjd.05", 0xc63358d0, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfxjd.06a", 0xccb29808, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sfxjd.07", 0x61f94982, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sfxjd.08", 0xd399c36c, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sfxd.09", 0x0b3a6196, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2xjr1d_gfx[] = {
    {"sfx.13m", 0xcf94d275, 2097152, 0, 0, 2097152, CPS2_WORD64},
    {"sfx.15m", 0x5eb703af, 2097152, 0, 2, 2097152, CPS2_WORD64},
    {"sfx.17m", 0xffa60e0f, 2097152, 0, 4, 2097152, CPS2_WORD64},
    {"sfx.19m", 0x34e825c5, 2097152, 0, 6, 2097152, CPS2_WORD64},
    {"sfx.14m", 0xb7cc32e7, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"sfx.16m", 0x8376ad18, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"sfx.18m", 0xf5b1b336, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"sfx.20m", 0x459d5c6b, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
    {"sfx.21m", 0xe32854af, 1048576, 0, 12582912, 1048576, CPS2_WORD64},
    {"sfx.23m", 0x760f2927, 1048576, 0, 12582914, 1048576, CPS2_WORD64},
    {"sfx.25m", 0x1ee90208, 1048576, 0, 12582916, 1048576, CPS2_WORD64},
    {"sfx.27m", 0xf814400f, 1048576, 0, 12582918, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_ssf2xjr1d_audiocpu[] = {
    {"sfx.01", 0xb47b8835, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfx.01", 0xb47b8835, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfx.02", 0x0022633f, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ssf2xjr1d_qsound[] = {
    {"sfx.11m", 0x9bdbd476, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfx.12m", 0xa05e3aab, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ssf2xjr1d_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ssf2xjr1d[] = {
    {"maincpu", 4194304, 0, chips_ssf2xjr1d_maincpu, N(chips_ssf2xjr1d_maincpu)},
    {"gfx", 16777216, 0, chips_ssf2xjr1d_gfx, N(chips_ssf2xjr1d_gfx)},
    {"audiocpu", 327680, 0, chips_ssf2xjr1d_audiocpu, N(chips_ssf2xjr1d_audiocpu)},
    {"qsound", 4194304, 0, chips_ssf2xjr1d_qsound, N(chips_ssf2xjr1d_qsound)},
    {"key", 32, 0, chips_ssf2xjr1d_key, N(chips_ssf2xjr1d_key)},
};
static const Cps2Load chips_xmcotar1d_maincpu[] = {
    {"xmned.03e", 0xbef56003, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xmned.04e", 0xb1a21fa6, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xmn.05a", 0xac0d7759, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xmn.06a", 0x1b86a328, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xmn.07a", 0x2c142a44, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xmn.08a", 0xf712d44f, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xmn.09a", 0x9241cae8, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"xmn.10a", 0x53c0eab9, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotar1d_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_xmcotar1d_gfx[] = {
    {"xmn.13m", 0xbf4df073, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xmn.15m", 0x4d7e4cef, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xmn.17m", 0x513eea17, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xmn.19m", 0xd23897fc, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xmn.14m", 0x778237b7, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xmn.16m", 0x67b36948, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xmn.18m", 0x015a7c4c, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xmn.20m", 0x9dde2758, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmcotar1d_audiocpu[] = {
    {"xmn.01a", 0x40f479ea, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xmn.01a", 0x40f479ea, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xmn.02a", 0x39d9b5ad, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmcotar1d_qsound[] = {
    {"xmn.11m", 0xc848a6bc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xmn.12m", 0x729c188f, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmcotar1d_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmcotar1d[] = {
    {"maincpu", 4194304, 0, chips_xmcotar1d_maincpu, N(chips_xmcotar1d_maincpu)},
    {"user1", 4194304, 0, chips_xmcotar1d_user1, N(chips_xmcotar1d_user1)},
    {"gfx", 33554432, 0, chips_xmcotar1d_gfx, N(chips_xmcotar1d_gfx)},
    {"audiocpu", 327680, 0, chips_xmcotar1d_audiocpu, N(chips_xmcotar1d_audiocpu)},
    {"qsound", 4194304, 0, chips_xmcotar1d_qsound, N(chips_xmcotar1d_qsound)},
    {"key", 32, 0, chips_xmcotar1d_key, N(chips_xmcotar1d_key)},
};
static const Cps2Load chips_mshud_maincpu[] = {
    {"mshud.03", 0xc1d8c4c6, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mshud.04", 0xe73dda16, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mshud.05", 0x3b493e84, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"msh.06b", 0x803e3fa4, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"msh.07a", 0xc45f8e27, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"msh.08a", 0x9ca6f12c, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"msh.09a", 0x82ec27af, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"msh.10b", 0x8d931196, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshud_gfx[] = {
    {"msh.13m", 0x09d14566, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"msh.15m", 0xee962057, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"msh.17m", 0x604ece14, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"msh.19m", 0x94a731e8, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"msh.14m", 0x4197973e, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"msh.16m", 0x438da4a0, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"msh.18m", 0x4db92d94, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"msh.20m", 0xa2b0c6c0, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshud_audiocpu[] = {
    {"msh.01", 0xc976e6f9, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"msh.01", 0xc976e6f9, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"msh.02", 0xce67d0d9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshud_qsound[] = {
    {"msh.11m", 0x37ac6d30, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"msh.12m", 0xde092570, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_mshud_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshud[] = {
    {"maincpu", 4194304, 0, chips_mshud_maincpu, N(chips_mshud_maincpu)},
    {"gfx", 33554432, 0, chips_mshud_gfx, N(chips_mshud_gfx)},
    {"audiocpu", 327680, 0, chips_mshud_audiocpu, N(chips_mshud_audiocpu)},
    {"qsound", 4194304, 0, chips_mshud_qsound, N(chips_mshud_qsound)},
    {"key", 32, 0, chips_mshud_key, N(chips_mshud_key)},
};
static const Cps2Load chips_cybotsud_maincpu[] = {
    {"cybu_d.03", 0xee7560fb, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"cybu_d.04", 0x7e7425a0, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"cyb.05", 0xec40408e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"cyb.06", 0x1ad0bed2, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"cyb.07", 0x6245a39a, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"cyb.08", 0x4b48e223, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"cyb.09", 0xe15238f6, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"cyb.10", 0x75f4003b, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_cybotsud_gfx[] = {
    {"cyb.13m", 0xf0dce192, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"cyb.15m", 0x187aa39c, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"cyb.17m", 0x8a0e4b12, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"cyb.19m", 0x34b62612, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"cyb.14m", 0xc1537957, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"cyb.16m", 0x15349e86, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"cyb.18m", 0xd83e977d, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"cyb.20m", 0x77cdad5c, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_cybotsud_audiocpu[] = {
    {"cyb.01", 0x9c0fb079, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"cyb.01", 0x9c0fb079, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"cyb.02", 0x51cb0c4e, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_cybotsud_qsound[] = {
    {"cyb.11m", 0x362ccab2, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"cyb.12m", 0x7066e9cc, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_cybotsud_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_cybotsud[] = {
    {"maincpu", 4194304, 0, chips_cybotsud_maincpu, N(chips_cybotsud_maincpu)},
    {"gfx", 33554432, 0, chips_cybotsud_gfx, N(chips_cybotsud_gfx)},
    {"audiocpu", 327680, 0, chips_cybotsud_audiocpu, N(chips_cybotsud_audiocpu)},
    {"qsound", 4194304, 0, chips_cybotsud_qsound, N(chips_cybotsud_qsound)},
    {"key", 32, 0, chips_cybotsud_key, N(chips_cybotsud_key)},
};
static const Cps2Load chips_cybotsjd_maincpu[] = {
    {"cybj_d.03", 0x9eb34071, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"cybj_d.04", 0xcf223cd7, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"cyb.05", 0xec40408e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"cyb.06", 0x1ad0bed2, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"cyb.07", 0x6245a39a, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"cyb.08", 0x4b48e223, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"cyb.09", 0xe15238f6, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"cyb.10", 0x75f4003b, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_cybotsjd_gfx[] = {
    {"cyb.13m", 0xf0dce192, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"cyb.15m", 0x187aa39c, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"cyb.17m", 0x8a0e4b12, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"cyb.19m", 0x34b62612, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"cyb.14m", 0xc1537957, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"cyb.16m", 0x15349e86, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"cyb.18m", 0xd83e977d, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"cyb.20m", 0x77cdad5c, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_cybotsjd_audiocpu[] = {
    {"cyb.01", 0x9c0fb079, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"cyb.01", 0x9c0fb079, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"cyb.02", 0x51cb0c4e, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_cybotsjd_qsound[] = {
    {"cyb.11m", 0x362ccab2, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"cyb.12m", 0x7066e9cc, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_cybotsjd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_cybotsjd[] = {
    {"maincpu", 4194304, 0, chips_cybotsjd_maincpu, N(chips_cybotsjd_maincpu)},
    {"gfx", 33554432, 0, chips_cybotsjd_gfx, N(chips_cybotsjd_gfx)},
    {"audiocpu", 327680, 0, chips_cybotsjd_audiocpu, N(chips_cybotsjd_audiocpu)},
    {"qsound", 4194304, 0, chips_cybotsjd_qsound, N(chips_cybotsjd_qsound)},
    {"key", 32, 0, chips_cybotsjd_key, N(chips_cybotsjd_key)},
};
static const Cps2Load chips_nwarrud_maincpu[] = {
    {"vphud.03f", 0x20d4d5a8, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vphud.04c", 0x61be9b42, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vphud.05e", 0x1ba906d8, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vphu.06c", 0x08c04cdb, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vphu.07b", 0xb5a5ab19, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vphu.08b", 0x51bb20fb, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vphu.09b", 0x41a64205, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vphud.10b", 0x9619adad, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_nwarrud_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_nwarrud_gfx[] = {
    {"vph.13m", 0xc51baf99, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vph.15m", 0x3ce83c77, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vph.17m", 0x4f2408e0, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vph.19m", 0x9ff60250, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vph.14m", 0x7a0e1add, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vph.16m", 0x2f41ca75, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vph.18m", 0x64498eed, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vph.20m", 0x17f2433f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_nwarrud_audiocpu[] = {
    {"vph.01", 0x5045dcac, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vph.01", 0x5045dcac, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vph.02", 0x86b60e59, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_nwarrud_qsound[] = {
    {"vph.11m", 0xe1837d33, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"vph.12m", 0xfbd3cd90, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_nwarrud_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_nwarrud[] = {
    {"maincpu", 4194304, 0, chips_nwarrud_maincpu, N(chips_nwarrud_maincpu)},
    {"user1", 4194304, 0, chips_nwarrud_user1, N(chips_nwarrud_user1)},
    {"gfx", 33554432, 0, chips_nwarrud_gfx, N(chips_nwarrud_gfx)},
    {"audiocpu", 327680, 0, chips_nwarrud_audiocpu, N(chips_nwarrud_audiocpu)},
    {"qsound", 4194304, 0, chips_nwarrud_qsound, N(chips_nwarrud_qsound)},
    {"key", 32, 0, chips_nwarrud_key, N(chips_nwarrud_key)},
};
static const Cps2Load chips_sfad_maincpu[] = {
    {"sfzed.03d", 0xa1a54827, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sfz.04b", 0x8b73b0e5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sfz.05a", 0x0810544d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sfz.06", 0x806e8f38, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfad_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_sfad_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"sfz.14m", 0x90fefdb3, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"sfz.16m", 0x5354c948, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"sfz.18m", 0x41a1e790, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"sfz.20m", 0xa549df98, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_sfad_audiocpu[] = {
    {"sfz.01", 0xffffec7d, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sfz.01", 0xffffec7d, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sfz.02", 0x45f46a08, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfad_qsound[] = {
    {"sfz.11m", 0xc4b093cd, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sfz.12m", 0x8bdbc4b4, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfad_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfad[] = {
    {"maincpu", 4194304, 0, chips_sfad_maincpu, N(chips_sfad_maincpu)},
    {"user1", 4194304, 0, chips_sfad_user1, N(chips_sfad_user1)},
    {"gfx", 16777216, 0, chips_sfad_gfx, N(chips_sfad_gfx)},
    {"audiocpu", 327680, 0, chips_sfad_audiocpu, N(chips_sfad_audiocpu)},
    {"qsound", 4194304, 0, chips_sfad_qsound, N(chips_sfad_qsound)},
    {"key", 32, 0, chips_sfad_key, N(chips_sfad_key)},
};
static const Cps2Load chips_19xxd_maincpu[] = {
    {"19xud.03", 0xf81b60e5, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"19xud.04", 0xcc44638c, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"19xud.05", 0x33a168de, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"19xud.06", 0xe0111282, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"19x.07", 0x61c0296c, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_19xxd_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_19xxd_gfx[] = {
    {"19x.13m", 0x427aeb18, 524288, 0, 0, 524288, CPS2_WORD64},
    {"19x.15m", 0x63bdbf54, 524288, 0, 2, 524288, CPS2_WORD64},
    {"19x.17m", 0x2dfe18b5, 524288, 0, 4, 524288, CPS2_WORD64},
    {"19x.19m", 0xcbef9579, 524288, 0, 6, 524288, CPS2_WORD64},
    {"19x.14m", 0xe916967c, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"19x.16m", 0x6e75f3db, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"19x.18m", 0x2213e798, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"19x.20m", 0xab9d5b96, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_19xxd_audiocpu[] = {
    {"19x.01", 0xef55195e, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"19x.01", 0xef55195e, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_19xxd_qsound[] = {
    {"19x.11m", 0xd38beef3, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"19x.12m", 0xd47c96e2, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_19xxd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_19xxd[] = {
    {"maincpu", 4194304, 0, chips_19xxd_maincpu, N(chips_19xxd_maincpu)},
    {"user1", 4194304, 0, chips_19xxd_user1, N(chips_19xxd_user1)},
    {"gfx", 16777216, 0, chips_19xxd_gfx, N(chips_19xxd_gfx)},
    {"audiocpu", 327680, 0, chips_19xxd_audiocpu, N(chips_19xxd_audiocpu)},
    {"qsound", 4194304, 0, chips_19xxd_qsound, N(chips_19xxd_qsound)},
    {"key", 32, 0, chips_19xxd_key, N(chips_19xxd_key)},
};
static const Cps2Load chips_ddsomud_maincpu[] = {
    {"dd2ud.03g", 0x816f695a, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"dd2ud.04g", 0x7cc81c6b, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"dd2.05g", 0x5eb1991c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"dd2.06g", 0xc26b5e55, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"dd2.07", 0x909a0b8b, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"dd2.08", 0xe53c4d01, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"dd2.09", 0x5f86279f, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"dd2d.10", 0x0c172f8f, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomud_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_ddsomud_gfx[] = {
    {"dd2.13m", 0xa46b4e6e, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"dd2.15m", 0xd5fc50fc, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"dd2.17m", 0x837c0867, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"dd2.19m", 0xbb0ec21c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"dd2.14m", 0x6d824ce2, 2097152, 0, 16777216, 2097152, CPS2_WORD64},
    {"dd2.16m", 0x79682ae5, 2097152, 0, 16777218, 2097152, CPS2_WORD64},
    {"dd2.18m", 0xacddd149, 2097152, 0, 16777220, 2097152, CPS2_WORD64},
    {"dd2.20m", 0x117fb0c0, 2097152, 0, 16777222, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_ddsomud_audiocpu[] = {
    {"dd2.01", 0x99d657e5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"dd2.01", 0x99d657e5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"dd2.02", 0x117a3824, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_ddsomud_qsound[] = {
    {"dd2.11m", 0x98d0c325, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"dd2.12m", 0x5ea2e7fa, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_ddsomud_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_ddsomud[] = {
    {"maincpu", 4194304, 0, chips_ddsomud_maincpu, N(chips_ddsomud_maincpu)},
    {"user1", 4194304, 0, chips_ddsomud_user1, N(chips_ddsomud_user1)},
    {"gfx", 25165824, 0, chips_ddsomud_gfx, N(chips_ddsomud_gfx)},
    {"audiocpu", 327680, 0, chips_ddsomud_audiocpu, N(chips_ddsomud_audiocpu)},
    {"qsound", 4194304, 0, chips_ddsomud_qsound, N(chips_ddsomud_qsound)},
    {"key", 32, 0, chips_ddsomud_key, N(chips_ddsomud_key)},
};
static const Cps2Load chips_gigaman2_maincpu[] = {
    {"sys_rom1.bin", 0x2eaa5e10, 4194304, 0, 0, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_gigaman2_mcu[] = {
    {"89c4051.bin", 0x0, 65536, 0, 0, 65536, CPS2_UNDUMPED},
};
static const Cps2Load chips_gigaman2_gfx[] = {
    {"cg_rom1.bin", 0xed55a641, 8388608, 0, 0, 4194304, CPS2_LINEAR},
    {"cg_rom2.bin", 0x63918c05, 8388608, 0, 4194304, 4194304, CPS2_LINEAR},
};
static const Cps2Load chips_gigaman2_oki[] = {
    {"pcm_rom1.bin", 0x41a854ab, 8388608, 0, 0, 8388608, CPS2_LINEAR},
};
static const Cps2Region regions_gigaman2[] = {
    {"maincpu", 4194304, 0, chips_gigaman2_maincpu, N(chips_gigaman2_maincpu)},
    {"mcu", 65536, 0, chips_gigaman2_mcu, N(chips_gigaman2_mcu)},
    {"gfx", 8388608, 0, chips_gigaman2_gfx, N(chips_gigaman2_gfx)},
    {"oki", 8388608, 0, chips_gigaman2_oki, N(chips_gigaman2_oki)},
};
static const Cps2Load chips_megamn2d_maincpu[] = {
    {"rm2ud.03", 0xd3635f25, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"rm2ud.04", 0x768a1705, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"rm2.05", 0x02ee9efc, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_megamn2d_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_megamn2d_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"rm2.14m", 0x9b1f00b4, 2097152, 0, 8388608, 2097152, CPS2_WORD64},
    {"rm2.16m", 0xc2bb0c24, 2097152, 0, 8388610, 2097152, CPS2_WORD64},
    {"rm2.18m", 0x12257251, 2097152, 0, 8388612, 2097152, CPS2_WORD64},
    {"rm2.20m", 0xf9b6e786, 2097152, 0, 8388614, 2097152, CPS2_WORD64},
};
static const Cps2Load chips_megamn2d_audiocpu[] = {
    {"rm2.01a", 0xd18e7859, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"rm2.01a", 0xd18e7859, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"rm2.02", 0xc463ece0, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_megamn2d_qsound[] = {
    {"rm2.11m", 0x2106174d, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"rm2.12m", 0x546c1636, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_megamn2d_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_megamn2d[] = {
    {"maincpu", 4194304, 0, chips_megamn2d_maincpu, N(chips_megamn2d_maincpu)},
    {"user1", 4194304, 0, chips_megamn2d_user1, N(chips_megamn2d_user1)},
    {"gfx", 16777216, 0, chips_megamn2d_gfx, N(chips_megamn2d_gfx)},
    {"audiocpu", 327680, 0, chips_megamn2d_audiocpu, N(chips_megamn2d_audiocpu)},
    {"qsound", 4194304, 0, chips_megamn2d_qsound, N(chips_megamn2d_qsound)},
    {"key", 32, 0, chips_megamn2d_key, N(chips_megamn2d_key)},
};
static const Cps2Load chips_sfz2ad_maincpu[] = {
    {"sz2ad.03a", 0x017f8fab, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz2ad.04a", 0xf50e5ea2, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz2.05a", 0x98e8e992, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz2.06", 0x5b1d49c0, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz2a.07a", 0x0aed2494, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz2.08", 0x0fe8585d, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2ad_gfx[] = {
    {"sz2.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz2.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz2.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz2.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz2.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sz2.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sz2.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sz2.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfz2ad_audiocpu[] = {
    {"sz2.01a", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz2.01a", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz2.02a", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz2ad_qsound[] = {
    {"sz2.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sz2.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2ad_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz2ad[] = {
    {"maincpu", 4194304, 0, chips_sfz2ad_maincpu, N(chips_sfz2ad_maincpu)},
    {"gfx", 20971520, 0, chips_sfz2ad_gfx, N(chips_sfz2ad_gfx)},
    {"audiocpu", 327680, 0, chips_sfz2ad_audiocpu, N(chips_sfz2ad_audiocpu)},
    {"qsound", 4194304, 0, chips_sfz2ad_qsound, N(chips_sfz2ad_qsound)},
    {"key", 32, 0, chips_sfz2ad_key, N(chips_sfz2ad_key)},
};
static const Cps2Load chips_sfz2jd_maincpu[] = {
    {"sz2j_d.03a", 0xb7325df8, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz2j_d.04a", 0xa1022a3e, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz2.05a", 0x98e8e992, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz2.06", 0x5b1d49c0, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz2j.07a", 0xd910b2a2, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz2.08", 0x0fe8585d, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2jd_gfx[] = {
    {"sz2.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz2.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz2.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz2.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz2.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sz2.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sz2.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sz2.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfz2jd_audiocpu[] = {
    {"sz2.01a", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz2.01a", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz2.02a", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz2jd_qsound[] = {
    {"sz2.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sz2.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2jd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz2jd[] = {
    {"maincpu", 4194304, 0, chips_sfz2jd_maincpu, N(chips_sfz2jd_maincpu)},
    {"gfx", 20971520, 0, chips_sfz2jd_gfx, N(chips_sfz2jd_gfx)},
    {"audiocpu", 327680, 0, chips_sfz2jd_audiocpu, N(chips_sfz2jd_audiocpu)},
    {"qsound", 4194304, 0, chips_sfz2jd_qsound, N(chips_sfz2jd_qsound)},
    {"key", 32, 0, chips_sfz2jd_key, N(chips_sfz2jd_key)},
};
static const Cps2Load chips_spf2td_maincpu[] = {
    {"pzfu_d.03a", 0x7836b903, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pzf.04", 0xb80649e2, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_spf2td_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_spf2td_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"pzf.14m", 0x2d4881cb, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"pzf.16m", 0x4b0fd1be, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"pzf.18m", 0xe43aac33, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"pzf.20m", 0x7f536ff1, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_spf2td_audiocpu[] = {
    {"pzf.01", 0x600fb2a3, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pzf.01", 0x600fb2a3, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pzf.02", 0x496076e0, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_spf2td_qsound[] = {
    {"pzf.11m", 0x78442743, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pzf.12m", 0x399d2c7b, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_spf2td_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_spf2td[] = {
    {"maincpu", 4194304, 0, chips_spf2td_maincpu, N(chips_spf2td_maincpu)},
    {"user1", 4194304, 0, chips_spf2td_user1, N(chips_spf2td_user1)},
    {"gfx", 12582912, 0, chips_spf2td_gfx, N(chips_spf2td_gfx)},
    {"audiocpu", 327680, 0, chips_spf2td_audiocpu, N(chips_spf2td_audiocpu)},
    {"qsound", 4194304, 0, chips_spf2td_qsound, N(chips_spf2td_qsound)},
    {"key", 32, 0, chips_spf2td_key, N(chips_spf2td_key)},
};
static const Cps2Load chips_spf2xjd_maincpu[] = {
    {"pzfjd.03a", 0x5e85ed08, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pzf.04", 0xb80649e2, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_spf2xjd_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_spf2xjd_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"pzf.14m", 0x2d4881cb, 1048576, 0, 8388608, 1048576, CPS2_WORD64},
    {"pzf.16m", 0x4b0fd1be, 1048576, 0, 8388610, 1048576, CPS2_WORD64},
    {"pzf.18m", 0xe43aac33, 1048576, 0, 8388612, 1048576, CPS2_WORD64},
    {"pzf.20m", 0x7f536ff1, 1048576, 0, 8388614, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_spf2xjd_audiocpu[] = {
    {"pzf.01", 0x600fb2a3, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pzf.01", 0x600fb2a3, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pzf.02", 0x496076e0, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_spf2xjd_qsound[] = {
    {"pzf.11m", 0x78442743, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pzf.12m", 0x399d2c7b, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_spf2xjd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_spf2xjd[] = {
    {"maincpu", 4194304, 0, chips_spf2xjd_maincpu, N(chips_spf2xjd_maincpu)},
    {"user1", 4194304, 0, chips_spf2xjd_user1, N(chips_spf2xjd_user1)},
    {"gfx", 12582912, 0, chips_spf2xjd_gfx, N(chips_spf2xjd_gfx)},
    {"audiocpu", 327680, 0, chips_spf2xjd_audiocpu, N(chips_spf2xjd_audiocpu)},
    {"qsound", 4194304, 0, chips_spf2xjd_qsound, N(chips_spf2xjd_qsound)},
    {"key", 32, 0, chips_spf2xjd_key, N(chips_spf2xjd_key)},
};
static const Cps2Load chips_sfz2ald_maincpu[] = {
    {"szaad.03", 0x89f9483b, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"szaad.04", 0xaef27ae5, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"szaa.05", 0xf053a55e, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"szaa.06", 0xcfc0e7a8, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"szaa.07", 0x5feb8b20, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"szaa.08", 0x6eb6d412, 524288, 0, 2621440, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2ald_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_sfz2ald_gfx[] = {
    {"sz2.13m", 0x4d1f1f22, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz2.15m", 0x19cea680, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz2.17m", 0xe01b4588, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz2.19m", 0x0feeda64, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz2.14m", 0x0560c6aa, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"sz2.16m", 0xae940f87, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"sz2.18m", 0x4bc3c8bc, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"sz2.20m", 0x39e674c0, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sfz2ald_audiocpu[] = {
    {"sz2.01a", 0x1bc323cf, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz2.01a", 0x1bc323cf, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz2.02a", 0xba6a5013, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz2ald_qsound[] = {
    {"sz2.11m", 0xaa47a601, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"sz2.12m", 0x2237bc53, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_sfz2ald_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz2ald[] = {
    {"maincpu", 4194304, 0, chips_sfz2ald_maincpu, N(chips_sfz2ald_maincpu)},
    {"user1", 4194304, 0, chips_sfz2ald_user1, N(chips_sfz2ald_user1)},
    {"gfx", 20971520, 0, chips_sfz2ald_gfx, N(chips_sfz2ald_gfx)},
    {"audiocpu", 327680, 0, chips_sfz2ald_audiocpu, N(chips_sfz2ald_audiocpu)},
    {"qsound", 4194304, 0, chips_sfz2ald_qsound, N(chips_sfz2ald_qsound)},
    {"key", 32, 0, chips_sfz2ald_key, N(chips_sfz2ald_key)},
};
static const Cps2Load chips_xmvsfu1d_maincpu[] = {
    {"xvsud.03h", 0x4e2e76b7, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"xvsud.04h", 0x290c61a7, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"xvs.05a", 0x7db6025d, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"xvs.06a", 0xe8e2c75c, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"xvs.07", 0x08f0abed, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"xvs.08", 0x81929675, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"xvs.09", 0x9641f36b, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfu1d_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_xmvsfu1d_gfx[] = {
    {"xvs.13m", 0xf6684efd, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"xvs.15m", 0x29109221, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"xvs.17m", 0x92db3474, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"xvs.19m", 0x3733473c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"xvs.14m", 0xbcac2e41, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"xvs.16m", 0xea04a272, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"xvs.18m", 0xb0def86a, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"xvs.20m", 0x4b40ff9f, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_xmvsfu1d_audiocpu[] = {
    {"xvs.01", 0x3999e93a, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"xvs.01", 0x3999e93a, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"xvs.02", 0x101bdee9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_xmvsfu1d_qsound[] = {
    {"xvs.11m", 0x9cadcdbc, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"xvs.12m", 0x7b11e460, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_xmvsfu1d_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_xmvsfu1d[] = {
    {"maincpu", 4194304, 0, chips_xmvsfu1d_maincpu, N(chips_xmvsfu1d_maincpu)},
    {"user1", 4194304, 0, chips_xmvsfu1d_user1, N(chips_xmvsfu1d_user1)},
    {"gfx", 33554432, 0, chips_xmvsfu1d_gfx, N(chips_xmvsfu1d_gfx)},
    {"audiocpu", 327680, 0, chips_xmvsfu1d_audiocpu, N(chips_xmvsfu1d_audiocpu)},
    {"qsound", 4194304, 0, chips_xmvsfu1d_qsound, N(chips_xmvsfu1d_qsound)},
    {"key", 32, 0, chips_xmvsfu1d_key, N(chips_xmvsfu1d_key)},
};
static const Cps2Load chips_batcird_maincpu[] = {
    {"btced.03", 0x0737db6d, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"btced.04", 0xef1a8823, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"btced.05", 0x20bdbb14, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"btced.06", 0xb4d8f5bc, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"btc.07", 0x7322d5db, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"btc.08", 0x6aac85ab, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"btc.09", 0x1203db08, 524288, 0, 3145728, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_batcird_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_batcird_gfx[] = {
    {"btc.13m", 0xdc705bad, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"btc.15m", 0xe5779a3c, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"btc.17m", 0xb33f4112, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"btc.19m", 0xa6fcdb7e, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_batcird_audiocpu[] = {
    {"btc.01", 0x1e194310, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"btc.01", 0x1e194310, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"btc.02", 0x01aeb8e6, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_batcird_qsound[] = {
    {"btc.11m", 0xc27f2229, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"btc.12m", 0x418a2e33, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_batcird_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_batcird[] = {
    {"maincpu", 4194304, 0, chips_batcird_maincpu, N(chips_batcird_maincpu)},
    {"user1", 4194304, 0, chips_batcird_user1, N(chips_batcird_user1)},
    {"gfx", 16777216, 0, chips_batcird_gfx, N(chips_batcird_gfx)},
    {"audiocpu", 327680, 0, chips_batcird_audiocpu, N(chips_batcird_audiocpu)},
    {"qsound", 4194304, 0, chips_batcird_qsound, N(chips_batcird_qsound)},
    {"key", 32, 0, chips_batcird_key, N(chips_batcird_key)},
};
static const Cps2Load chips_csclub1d_maincpu[] = {
    {"csce_d.03", 0x5aedc6e6, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"csce_d.04", 0xa3d9aa25, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"csce_d.05", 0x0915c9d1, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"csce_d.06", 0x09c77d99, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"csc_d.07", 0x77478e25, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_csclub1d_gfx[] = {
    {NULL, 0, 0, 0, 0, 8388608, CPS2_FILL},
    {"csc.73", 0x335f07c3, 524288, 0, 8388608, 524288, CPS2_WORD64},
    {"csc.74", 0xab215357, 524288, 0, 10485760, 524288, CPS2_WORD64},
    {"csc.75", 0xa2367381, 524288, 0, 12582912, 524288, CPS2_WORD64},
    {"csc.76", 0x728aac1f, 524288, 0, 14680064, 524288, CPS2_WORD64},
    {"csc.63", 0x3711b8ca, 524288, 0, 8388610, 524288, CPS2_WORD64},
    {"csc.64", 0x828a06d8, 524288, 0, 10485762, 524288, CPS2_WORD64},
    {"csc.65", 0x86ee4569, 524288, 0, 12582914, 524288, CPS2_WORD64},
    {"csc.66", 0xc24f577f, 524288, 0, 14680066, 524288, CPS2_WORD64},
    {"csc.83", 0x0750d12a, 524288, 0, 8388612, 524288, CPS2_WORD64},
    {"csc.84", 0x90a92f39, 524288, 0, 10485764, 524288, CPS2_WORD64},
    {"csc.85", 0xd08ab012, 524288, 0, 12582916, 524288, CPS2_WORD64},
    {"csc.86", 0x41652583, 524288, 0, 14680068, 524288, CPS2_WORD64},
    {"csc.93", 0xa756c7f7, 524288, 0, 8388614, 524288, CPS2_WORD64},
    {"csc.94", 0xfb7ccc73, 524288, 0, 10485766, 524288, CPS2_WORD64},
    {"csc.95", 0x4d014297, 524288, 0, 12582918, 524288, CPS2_WORD64},
    {"csc.96", 0x6754b1ef, 524288, 0, 14680070, 524288, CPS2_WORD64},
};
static const Cps2Load chips_csclub1d_audiocpu[] = {
    {"csc.01", 0xee162111, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"csc.01", 0xee162111, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_csclub1d_qsound[] = {
    {"csc.51", 0x5a52afd5, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"csc.52", 0x1408a811, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"csc.53", 0x4fb9f57c, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"csc.54", 0x9a8f40ec, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"csc.55", 0x91529a91, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"csc.56", 0x9a345334, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"csc.57", 0xaedc27f2, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"csc.58", 0x2300b7b3, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_csclub1d_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_csclub1d[] = {
    {"maincpu", 4194304, 0, chips_csclub1d_maincpu, N(chips_csclub1d_maincpu)},
    {"gfx", 16777216, 0, chips_csclub1d_gfx, N(chips_csclub1d_gfx)},
    {"audiocpu", 327680, 0, chips_csclub1d_audiocpu, N(chips_csclub1d_audiocpu)},
    {"qsound", 4194304, 0, chips_csclub1d_qsound, N(chips_csclub1d_qsound)},
    {"key", 32, 0, chips_csclub1d_key, N(chips_csclub1d_key)},
};
static const Cps2Load chips_mshvsfu1d_maincpu[] = {
    {"mvsu_d.03d", 0x1c88bee3, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvsu_d.04d", 0x1e8b2535, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvs_d.05a", 0x373856fb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvs.06a", 0x959f3030, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvs.07b", 0x7f915bdb, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvs.08a", 0xc2813884, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvs.09b", 0x3ba08818, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvs.10b", 0xcf0dba98, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfu1d_gfx[] = {
    {"mvs.13m", 0x29b05fd9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvs.15m", 0xfaddccf1, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvs.17m", 0x97aaf4c7, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvs.19m", 0xcb70e915, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvs.14m", 0xb3b1972d, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvs.16m", 0x08aadb5d, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvs.18m", 0xc1228b35, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvs.20m", 0x366cc6c2, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mshvsfu1d_audiocpu[] = {
    {"mvs.01", 0x68252324, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvs.01", 0x68252324, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvs.02", 0xb34e773d, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mshvsfu1d_qsound[] = {
    {"mvs.11m", 0x86219770, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvs.12m", 0xf2fd7f68, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mshvsfu1d_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mshvsfu1d[] = {
    {"maincpu", 4194304, 0, chips_mshvsfu1d_maincpu, N(chips_mshvsfu1d_maincpu)},
    {"gfx", 33554432, 0, chips_mshvsfu1d_gfx, N(chips_mshvsfu1d_gfx)},
    {"audiocpu", 327680, 0, chips_mshvsfu1d_audiocpu, N(chips_mshvsfu1d_audiocpu)},
    {"qsound", 8388608, 0, chips_mshvsfu1d_qsound, N(chips_mshvsfu1d_qsound)},
    {"key", 32, 0, chips_mshvsfu1d_key, N(chips_mshvsfu1d_key)},
};
static const Cps2Load chips_sgemfd_maincpu[] = {
    {"pcfud.03", 0x8b83674a, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pcfd.04", 0xb58f1d03, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pcf.05", 0x215655f6, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pcf.06", 0xea6f13ea, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"pcf.07", 0x5ac6d5ea, 524288, 0, 2097152, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sgemfd_gfx[] = {
    {"pcf.13m", 0x22d72ab9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pcf.15m", 0x16a4813c, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pcf.17m", 0x1097e035, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pcf.19m", 0xd362d874, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"pcf.14m", 0x0383897c, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"pcf.16m", 0x76f91084, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"pcf.18m", 0x756c3754, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"pcf.20m", 0x9ec9277d, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_sgemfd_audiocpu[] = {
    {"pcf.01", 0x254e5f33, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pcf.01", 0x254e5f33, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"pcf.02", 0x6902f4f9, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sgemfd_qsound[] = {
    {"pcf.11m", 0xa5dea005, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"pcf.12m", 0x4ce235fe, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sgemfd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sgemfd[] = {
    {"maincpu", 4194304, 0, chips_sgemfd_maincpu, N(chips_sgemfd_maincpu)},
    {"gfx", 20971520, 0, chips_sgemfd_gfx, N(chips_sgemfd_gfx)},
    {"audiocpu", 327680, 0, chips_sgemfd_audiocpu, N(chips_sgemfd_audiocpu)},
    {"qsound", 8388608, 0, chips_sgemfd_qsound, N(chips_sgemfd_qsound)},
    {"key", 32, 0, chips_sgemfd_key, N(chips_sgemfd_key)},
};
static const Cps2Load chips_vsavd_maincpu[] = {
    {"vm3ed.03d", 0x97d805e3, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vm3ed.04d", 0x5e07fdce, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vm3.05a", 0x4118e00f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vm3.06a", 0x2f4fd3a9, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vm3.07b", 0xcbda91b8, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vm3.08a", 0x6ca47259, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vm3.09b", 0xf4a339e3, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vm3.10b", 0xfffbb5b8, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vsavd_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_vsavd_gfx[] = {
    {"vm3.13m", 0xfd8a11eb, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vm3.15m", 0xdd1e7d4e, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vm3.17m", 0x6b89445e, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vm3.19m", 0x3830fdc7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vm3.14m", 0xc1a28e6c, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vm3.16m", 0x194a7304, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vm3.18m", 0xdf9a9f47, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vm3.20m", 0xc22fc3d9, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vsavd_audiocpu[] = {
    {"vm3.01", 0xf778769b, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vm3.01", 0xf778769b, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vm3.02", 0xcc09faa1, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vsavd_qsound[] = {
    {"vm3.11m", 0xe80e956e, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"vm3.12m", 0x9cd71557, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_vsavd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vsavd[] = {
    {"maincpu", 4194304, 0, chips_vsavd_maincpu, N(chips_vsavd_maincpu)},
    {"user1", 4194304, 0, chips_vsavd_user1, N(chips_vsavd_user1)},
    {"gfx", 33554432, 0, chips_vsavd_gfx, N(chips_vsavd_gfx)},
    {"audiocpu", 327680, 0, chips_vsavd_audiocpu, N(chips_vsavd_audiocpu)},
    {"qsound", 8388608, 0, chips_vsavd_qsound, N(chips_vsavd_qsound)},
    {"key", 32, 0, chips_vsavd_key, N(chips_vsavd_key)},
};
static const Cps2Load chips_vhunt2d_maincpu[] = {
    {"vh2j_d.03a", 0x696e0157, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vh2j_d.04a", 0xced9bba3, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vh2j.05", 0xde34f624, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vh2j.06", 0x6a3b9897, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vh2j.07", 0xb021c029, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vh2j.08", 0xac873dff, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vh2j.09", 0xeaefce9c, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vh2j.10", 0x11730952, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vhunt2d_gfx[] = {
    {"vh2.13m", 0x3b02ddaa, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vh2.15m", 0x4e40de66, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vh2.17m", 0xb31d00c9, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vh2.19m", 0x149be3ab, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vh2.14m", 0xcd09bd63, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vh2.16m", 0xe0182c15, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vh2.18m", 0x778dc4f6, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vh2.20m", 0x605d9d1d, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vhunt2d_audiocpu[] = {
    {"vh2.01", 0x67b9f779, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vh2.01", 0x67b9f779, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vh2.02", 0xaaf15fcb, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vhunt2d_qsound[] = {
    {"vh2.11m", 0x38922efd, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"vh2.12m", 0x6e2430af, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_vhunt2d_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vhunt2d[] = {
    {"maincpu", 4194304, 0, chips_vhunt2d_maincpu, N(chips_vhunt2d_maincpu)},
    {"gfx", 33554432, 0, chips_vhunt2d_gfx, N(chips_vhunt2d_gfx)},
    {"audiocpu", 327680, 0, chips_vhunt2d_audiocpu, N(chips_vhunt2d_audiocpu)},
    {"qsound", 8388608, 0, chips_vhunt2d_qsound, N(chips_vhunt2d_qsound)},
    {"key", 32, 0, chips_vhunt2d_key, N(chips_vhunt2d_key)},
};
static const Cps2Load chips_vsav2d_maincpu[] = {
    {"vs2j_d.03", 0x50865f7b, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"vs2j_d.04", 0xc3bff0e3, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"vs2j.05", 0x61979638, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"vs2j.06", 0xf37c5bc2, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"vs2j.07", 0x8f885809, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"vs2j.08", 0x2018c120, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"vs2j.09", 0xfac3c217, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"vs2j.10", 0xeb490213, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_vsav2d_gfx[] = {
    {"vs2.13m", 0x5c852f52, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"vs2.15m", 0xa20f58af, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"vs2.17m", 0x39db59ad, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"vs2.19m", 0x00c763a7, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"vs2.14m", 0xcd09bd63, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"vs2.16m", 0xe0182c15, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"vs2.18m", 0x778dc4f6, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"vs2.20m", 0x605d9d1d, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_vsav2d_audiocpu[] = {
    {"vs2.01", 0x35190139, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"vs2.01", 0x35190139, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"vs2.02", 0xc32dba09, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_vsav2d_qsound[] = {
    {"vs2.11m", 0xd67e47b7, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"vs2.12m", 0x6d020a14, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_vsav2d_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_vsav2d[] = {
    {"maincpu", 4194304, 0, chips_vsav2d_maincpu, N(chips_vsav2d_maincpu)},
    {"gfx", 33554432, 0, chips_vsav2d_gfx, N(chips_vsav2d_gfx)},
    {"audiocpu", 327680, 0, chips_vsav2d_audiocpu, N(chips_vsav2d_audiocpu)},
    {"qsound", 8388608, 0, chips_vsav2d_qsound, N(chips_vsav2d_qsound)},
    {"key", 32, 0, chips_vsav2d_key, N(chips_vsav2d_key)},
};
static const Cps2Load chips_mvscud_maincpu[] = {
    {"mvcud.03d", 0x75cde3e5, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mvcud.04d", 0xb32ea484, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mvc.05a", 0x2d8c8e86, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"mvc.06a", 0x8528e1f5, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"mvcd.07", 0x205293e9, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"mvc.08", 0xbc002fcd, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"mvc.09", 0xc67b26df, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"mvc.10", 0x0fdd1e26, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mvscud_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_mvscud_gfx[] = {
    {"mvc.13m", 0xfa5f74bc, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mvc.15m", 0x71938a8f, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mvc.17m", 0x92741d07, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mvc.19m", 0xbcb72fc6, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mvc.14m", 0x7f1df4e4, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mvc.16m", 0x90bd3203, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mvc.18m", 0x67aaf727, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mvc.20m", 0x8b0bade8, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mvscud_audiocpu[] = {
    {"mvc.01", 0x41629e95, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mvc.01", 0x41629e95, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"mvc.02", 0x963abf6b, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_mvscud_qsound[] = {
    {"mvc.11m", 0x850fe663, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mvc.12m", 0x7ccb1896, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mvscud_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mvscud[] = {
    {"maincpu", 4194304, 0, chips_mvscud_maincpu, N(chips_mvscud_maincpu)},
    {"user1", 4194304, 0, chips_mvscud_user1, N(chips_mvscud_user1)},
    {"gfx", 33554432, 0, chips_mvscud_gfx, N(chips_mvscud_gfx)},
    {"audiocpu", 327680, 0, chips_mvscud_audiocpu, N(chips_mvscud_audiocpu)},
    {"qsound", 8388608, 0, chips_mvscud_qsound, N(chips_mvscud_qsound)},
    {"key", 32, 0, chips_mvscud_key, N(chips_mvscud_key)},
};
static const Cps2Load chips_sfa3ud_maincpu[] = {
    {"sz3ud.03c", 0x6db8add7, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz3ud.04c", 0xd9c65a26, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz3.05c", 0x57fd0a40, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz3.06c", 0xf6305f8b, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz3.07c", 0x6eab0f6f, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz3.08c", 0x910c4a3b, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sz3.09c", 0xb29e5199, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"sz3.10b", 0xdeb2ff52, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3ud_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_sfa3ud_gfx[] = {
    {"sz3.13m", 0x0f7a60d9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz3.15m", 0x8e933741, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz3.17m", 0xd6e98147, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz3.19m", 0xf31a728a, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz3.14m", 0x5ff98297, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"sz3.16m", 0x52b5bdee, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"sz3.18m", 0x40631ed5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"sz3.20m", 0x763409b4, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_sfa3ud_audiocpu[] = {
    {"sz3.01", 0xde810084, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz3.01", 0xde810084, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz3.02", 0x72445dc4, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfa3ud_qsound[] = {
    {"sz3.11m", 0x1c89eed1, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"sz3.12m", 0xf392b13a, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sfa3ud_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfa3ud[] = {
    {"maincpu", 4194304, 0, chips_sfa3ud_maincpu, N(chips_sfa3ud_maincpu)},
    {"user1", 4194304, 0, chips_sfa3ud_user1, N(chips_sfa3ud_user1)},
    {"gfx", 33554432, 0, chips_sfa3ud_gfx, N(chips_sfa3ud_gfx)},
    {"audiocpu", 327680, 0, chips_sfa3ud_audiocpu, N(chips_sfa3ud_audiocpu)},
    {"qsound", 8388608, 0, chips_sfa3ud_qsound, N(chips_sfa3ud_qsound)},
    {"key", 32, 0, chips_sfa3ud_key, N(chips_sfa3ud_key)},
};
static const Cps2Load chips_sfz3jr2d_maincpu[] = {
    {"sz3j_d.03", 0xb0436151, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"sz3j_d.04", 0x642d8170, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"sz3.05", 0x9b21518a, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"sz3.06", 0xe7a6c3a7, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"sz3.07", 0xec4c0cfd, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"sz3.08", 0x5c7e7240, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"sz3.09", 0xc5589553, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"sz3.10", 0xa9717252, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_sfz3jr2d_gfx[] = {
    {"sz3.13m", 0x0f7a60d9, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"sz3.15m", 0x8e933741, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"sz3.17m", 0xd6e98147, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"sz3.19m", 0xf31a728a, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"sz3.14m", 0x5ff98297, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"sz3.16m", 0x52b5bdee, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"sz3.18m", 0x40631ed5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"sz3.20m", 0x763409b4, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_sfz3jr2d_audiocpu[] = {
    {"sz3.01", 0xde810084, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"sz3.01", 0xde810084, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"sz3.02", 0x72445dc4, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_sfz3jr2d_qsound[] = {
    {"sz3.11m", 0x1c89eed1, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"sz3.12m", 0xf392b13a, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_sfz3jr2d_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_sfz3jr2d[] = {
    {"maincpu", 4194304, 0, chips_sfz3jr2d_maincpu, N(chips_sfz3jr2d_maincpu)},
    {"gfx", 33554432, 0, chips_sfz3jr2d_gfx, N(chips_sfz3jr2d_gfx)},
    {"audiocpu", 327680, 0, chips_sfz3jr2d_audiocpu, N(chips_sfz3jr2d_audiocpu)},
    {"qsound", 8388608, 0, chips_sfz3jr2d_qsound, N(chips_sfz3jr2d_qsound)},
    {"key", 32, 0, chips_sfz3jr2d_key, N(chips_sfz3jr2d_key)},
};
static const Cps2Load chips_gigawingd_maincpu[] = {
    {"ggwu_d.03", 0xdde92dfa, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ggwu_d.04", 0xe0509ae2, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ggw_d.05", 0x722d0042, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_gigawingd_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_gigawingd_gfx[] = {
    {"ggw.13m", 0x105530a4, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"ggw.15m", 0x9e774ab9, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"ggw.17m", 0x466e0ba4, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"ggw.19m", 0x840c8dea, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_gigawingd_audiocpu[] = {
    {"ggw.01", 0x4c6351d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ggw.01", 0x4c6351d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_gigawingd_qsound[] = {
    {"ggw.11m", 0xe172acf5, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"ggw.12m", 0x4bee4e8f, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_gigawingd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_gigawingd[] = {
    {"maincpu", 4194304, 0, chips_gigawingd_maincpu, N(chips_gigawingd_maincpu)},
    {"user1", 4194304, 0, chips_gigawingd_user1, N(chips_gigawingd_user1)},
    {"gfx", 16777216, 0, chips_gigawingd_gfx, N(chips_gigawingd_gfx)},
    {"audiocpu", 327680, 0, chips_gigawingd_audiocpu, N(chips_gigawingd_audiocpu)},
    {"qsound", 8388608, 0, chips_gigawingd_qsound, N(chips_gigawingd_qsound)},
    {"key", 32, 0, chips_gigawingd_key, N(chips_gigawingd_key)},
};
static const Cps2Load chips_gigawingjd_maincpu[] = {
    {"ggwjd.03a", 0xcb1c756e, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"ggwjd.04a", 0xfa158e04, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"ggwjd.05a", 0x1c5bc4e7, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_gigawingjd_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_gigawingjd_gfx[] = {
    {"ggw.13m", 0x105530a4, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"ggw.15m", 0x9e774ab9, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"ggw.17m", 0x466e0ba4, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"ggw.19m", 0x840c8dea, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_gigawingjd_audiocpu[] = {
    {"ggw.01", 0x4c6351d5, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"ggw.01", 0x4c6351d5, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_gigawingjd_qsound[] = {
    {"ggw.11m", 0xe172acf5, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"ggw.12m", 0x4bee4e8f, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_gigawingjd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_gigawingjd[] = {
    {"maincpu", 4194304, 0, chips_gigawingjd_maincpu, N(chips_gigawingjd_maincpu)},
    {"user1", 4194304, 0, chips_gigawingjd_user1, N(chips_gigawingjd_user1)},
    {"gfx", 16777216, 0, chips_gigawingjd_gfx, N(chips_gigawingjd_gfx)},
    {"audiocpu", 327680, 0, chips_gigawingjd_audiocpu, N(chips_gigawingjd_audiocpu)},
    {"qsound", 8388608, 0, chips_gigawingjd_qsound, N(chips_gigawingjd_qsound)},
    {"key", 32, 0, chips_gigawingjd_key, N(chips_gigawingjd_key)},
};
static const Cps2Load chips_1944d_maincpu[] = {
    {"nffud.03", 0x28e8aae4, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"nff.04", 0xdba1c66e, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"nffu.05", 0xea813eb7, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_1944d_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_1944d_gfx[] = {
    {"nff.13m", 0xc9fca741, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"nff.15m", 0xf809d898, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"nff.17m", 0x15ba4507, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"nff.19m", 0x3dd41b8c, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"nff.14m", 0x3fe3a54b, 1048576, 0, 16777216, 1048576, CPS2_WORD64},
    {"nff.16m", 0x565cd231, 1048576, 0, 16777218, 1048576, CPS2_WORD64},
    {"nff.18m", 0x63ca5988, 1048576, 0, 16777220, 1048576, CPS2_WORD64},
    {"nff.20m", 0x21eb8f3b, 1048576, 0, 16777222, 1048576, CPS2_WORD64},
};
static const Cps2Load chips_1944d_audiocpu[] = {
    {"nff.01", 0xd2e44318, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"nff.01", 0xd2e44318, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_1944d_qsound[] = {
    {"nff.11m", 0x243e4e05, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"nff.12m", 0x4fcf1600, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_1944d_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_1944d[] = {
    {"maincpu", 4194304, 0, chips_1944d_maincpu, N(chips_1944d_maincpu)},
    {"user1", 4194304, 0, chips_1944d_user1, N(chips_1944d_user1)},
    {"gfx", 33554432, 0, chips_1944d_gfx, N(chips_1944d_gfx)},
    {"audiocpu", 327680, 0, chips_1944d_audiocpu, N(chips_1944d_audiocpu)},
    {"qsound", 8388608, 0, chips_1944d_qsound, N(chips_1944d_qsound)},
    {"key", 32, 0, chips_1944d_key, N(chips_1944d_key)},
};
static const Cps2Load chips_dimahoud_maincpu[] = {
    {"gmdud.03", 0x12888435, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"gmd.04", 0x37485567, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"gmd.05", 0xda269ffb, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"gmdud.06", 0xd825efda, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_dimahoud_gfx[] = {
    {"gmd.13m", 0x80dd19f0, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"gmd.15m", 0xdfd93a78, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"gmd.17m", 0x16356520, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"gmd.19m", 0xdfc33031, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_dimahoud_audiocpu[] = {
    {"gmd.01", 0x3f9bc985, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"gmd.01", 0x3f9bc985, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"gmd.02", 0x3fd39dde, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_dimahoud_qsound[] = {
    {"gmd.11m", 0x06a65542, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"gmd.12m", 0x50bc7a31, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_dimahoud_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_dimahoud[] = {
    {"maincpu", 4194304, 0, chips_dimahoud_maincpu, N(chips_dimahoud_maincpu)},
    {"gfx", 16777216, 0, chips_dimahoud_gfx, N(chips_dimahoud_gfx)},
    {"audiocpu", 327680, 0, chips_dimahoud_audiocpu, N(chips_dimahoud_audiocpu)},
    {"qsound", 8388608, 0, chips_dimahoud_qsound, N(chips_dimahoud_qsound)},
    {"key", 32, 0, chips_dimahoud_key, N(chips_dimahoud_key)},
};
static const Cps2Load chips_mmatrixd_maincpu[] = {
    {"mmxud.03", 0x36711e60, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"mmxud.04", 0x4687226f, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"mmxud.05", 0x52124398, 524288, 0, 1048576, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_mmatrixd_gfx[] = {
    {"mmx.13m", 0x04748718, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"mmx.15m", 0x38074f44, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"mmx.17m", 0xe4635e35, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"mmx.19m", 0x4400a3f2, 4194304, 0, 6, 4194304, CPS2_WORD64},
    {"mmx.14m", 0xd52bf491, 4194304, 0, 16777216, 4194304, CPS2_WORD64},
    {"mmx.16m", 0x23f70780, 4194304, 0, 16777218, 4194304, CPS2_WORD64},
    {"mmx.18m", 0x2562c9d5, 4194304, 0, 16777220, 4194304, CPS2_WORD64},
    {"mmx.20m", 0x583a9687, 4194304, 0, 16777222, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_mmatrixd_audiocpu[] = {
    {"mmx.01", 0xc57e8171, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"mmx.01", 0xc57e8171, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_mmatrixd_qsound[] = {
    {"mmx.11m", 0x4180b39f, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"mmx.12m", 0x95e22a59, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_mmatrixd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_mmatrixd[] = {
    {"maincpu", 4194304, 0, chips_mmatrixd_maincpu, N(chips_mmatrixd_maincpu)},
    {"gfx", 33554432, 0, chips_mmatrixd_gfx, N(chips_mmatrixd_gfx)},
    {"audiocpu", 327680, 0, chips_mmatrixd_audiocpu, N(chips_mmatrixd_audiocpu)},
    {"qsound", 8388608, 0, chips_mmatrixd_qsound, N(chips_mmatrixd_qsound)},
    {"key", 32, 0, chips_mmatrixd_key, N(chips_mmatrixd_key)},
};
static const Cps2Load chips_progearud_maincpu[] = {
    {"pgau_d.03", 0xba22b9c5, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pgau_d.04", 0xdf3927ef, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_progearud_gfx[] = {
    {"pga-simm.01c", 0x452f98b0, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"pga-simm.01d", 0x9e672092, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"pga-simm.01a", 0xae9ddafe, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"pga-simm.01b", 0x94d72d94, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"pga-simm.03c", 0x48a1886d, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"pga-simm.03d", 0x172d7e37, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"pga-simm.03a", 0x9ee33d98, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"pga-simm.03b", 0x848dee32, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_progearud_audiocpu[] = {
    {"pga.01", 0xbdbfa992, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pga.01", 0xbdbfa992, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_progearud_qsound[] = {
    {"pga-simm.05a", 0xc0aac80c, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pga-simm.05b", 0x37a65d86, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
    {"pga-simm.06a", 0xd3f1e934, 2097152, 0, 4194304, 2097152, CPS2_SWAP16},
    {"pga-simm.06b", 0x8b39489a, 2097152, 0, 6291456, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_progearud_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_progearud[] = {
    {"maincpu", 4194304, 0, chips_progearud_maincpu, N(chips_progearud_maincpu)},
    {"gfx", 16777216, 0, chips_progearud_gfx, N(chips_progearud_gfx)},
    {"audiocpu", 327680, 0, chips_progearud_audiocpu, N(chips_progearud_audiocpu)},
    {"qsound", 8388608, 0, chips_progearud_qsound, N(chips_progearud_qsound)},
    {"key", 32, 0, chips_progearud_key, N(chips_progearud_key)},
};
static const Cps2Load chips_progearjd_maincpu[] = {
    {"pgaj_d.03", 0x0271f3a3, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pgaj_d.04", 0xbe4b7799, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_progearjd_gfx[] = {
    {"pga-simm.01c", 0x452f98b0, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"pga-simm.01d", 0x9e672092, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"pga-simm.01a", 0xae9ddafe, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"pga-simm.01b", 0x94d72d94, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"pga-simm.03c", 0x48a1886d, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"pga-simm.03d", 0x172d7e37, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"pga-simm.03a", 0x9ee33d98, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"pga-simm.03b", 0x848dee32, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_progearjd_audiocpu[] = {
    {"pga.01", 0xbdbfa992, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pga.01", 0xbdbfa992, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_progearjd_qsound[] = {
    {"pga-simm.05a", 0xc0aac80c, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pga-simm.05b", 0x37a65d86, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
    {"pga-simm.06a", 0xd3f1e934, 2097152, 0, 4194304, 2097152, CPS2_SWAP16},
    {"pga-simm.06b", 0x8b39489a, 2097152, 0, 6291456, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_progearjd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_progearjd[] = {
    {"maincpu", 4194304, 0, chips_progearjd_maincpu, N(chips_progearjd_maincpu)},
    {"gfx", 16777216, 0, chips_progearjd_gfx, N(chips_progearjd_gfx)},
    {"audiocpu", 327680, 0, chips_progearjd_audiocpu, N(chips_progearjd_audiocpu)},
    {"qsound", 8388608, 0, chips_progearjd_qsound, N(chips_progearjd_qsound)},
    {"key", 32, 0, chips_progearjd_key, N(chips_progearjd_key)},
};
static const Cps2Load chips_progearjbl_maincpu[] = {
    {"pgaj_bl.03", 0x4fef676c, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pgaj_bl.04", 0xa069bd3b, 524288, 0, 524288, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_progearjbl_gfx[] = {
    {"pga.13m", 0x5194c198, 4194304, 0, 0, 4194304, CPS2_WORD64},
    {"pga.15m", 0xb794e83f, 4194304, 0, 2, 4194304, CPS2_WORD64},
    {"pga.17m", 0x87f22918, 4194304, 0, 4, 4194304, CPS2_WORD64},
    {"pga.19m", 0x65ffb45b, 4194304, 0, 6, 4194304, CPS2_WORD64},
};
static const Cps2Load chips_progearjbl_audiocpu[] = {
    {"pga.01", 0xbdbfa992, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pga.01", 0xbdbfa992, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_progearjbl_qsound[] = {
    {"pga.11m", 0xabdd224e, 4194304, 0, 0, 4194304, CPS2_SWAP16},
    {"pga.12m", 0xdac53406, 4194304, 0, 4194304, 4194304, CPS2_SWAP16},
};
static const Cps2Load chips_progearjbl_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_progearjbl[] = {
    {"maincpu", 4194304, 0, chips_progearjbl_maincpu, N(chips_progearjbl_maincpu)},
    {"gfx", 16777216, 0, chips_progearjbl_gfx, N(chips_progearjbl_gfx)},
    {"audiocpu", 327680, 0, chips_progearjbl_audiocpu, N(chips_progearjbl_audiocpu)},
    {"qsound", 8388608, 0, chips_progearjbl_qsound, N(chips_progearjbl_qsound)},
    {"key", 32, 0, chips_progearjbl_key, N(chips_progearjbl_key)},
};
static const Cps2Load chips_pzloop2jd_maincpu[] = {
    {"pl2j_d.03a", 0x1f5d41c9, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"pl2j_d.04a", 0x60721b73, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"pl2j_d.05a", 0x0c39799f, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"pl2j_d.06a", 0xf3974d76, 524288, 0, 1572864, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_pzloop2jd_gfx[] = {
    {"pl2-simm.01c", 0x137b13a7, 2097152, 0, 0, 2097152, CPS2_BYTE64},
    {"pl2-simm.01d", 0xa2db1507, 2097152, 0, 1, 2097152, CPS2_BYTE64},
    {"pl2-simm.01a", 0x7e80ff8e, 2097152, 0, 2, 2097152, CPS2_BYTE64},
    {"pl2-simm.01b", 0xcd93e6ed, 2097152, 0, 3, 2097152, CPS2_BYTE64},
    {"pl2-simm.03c", 0x0f52bbca, 2097152, 0, 4, 2097152, CPS2_BYTE64},
    {"pl2-simm.03d", 0xa62712c3, 2097152, 0, 5, 2097152, CPS2_BYTE64},
    {"pl2-simm.03a", 0xb60c9f8e, 2097152, 0, 6, 2097152, CPS2_BYTE64},
    {"pl2-simm.03b", 0x83fef284, 2097152, 0, 7, 2097152, CPS2_BYTE64},
};
static const Cps2Load chips_pzloop2jd_audiocpu[] = {
    {"pl2.01", 0x35697569, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"pl2.01", 0x35697569, 131072, 32768, 65536, 98304, CPS2_LINEAR},
};
static const Cps2Load chips_pzloop2jd_qsound[] = {
    {"pl2-simm.05a", 0x85d8fbe8, 2097152, 0, 0, 2097152, CPS2_SWAP16},
    {"pl2-simm.05b", 0x1ed62584, 2097152, 0, 2097152, 2097152, CPS2_SWAP16},
};
static const Cps2Load chips_pzloop2jd_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_pzloop2jd[] = {
    {"maincpu", 4194304, 0, chips_pzloop2jd_maincpu, N(chips_pzloop2jd_maincpu)},
    {"gfx", 16777216, 0, chips_pzloop2jd_gfx, N(chips_pzloop2jd_gfx)},
    {"audiocpu", 327680, 0, chips_pzloop2jd_audiocpu, N(chips_pzloop2jd_audiocpu)},
    {"qsound", 4194304, 0, chips_pzloop2jd_qsound, N(chips_pzloop2jd_qsound)},
    {"key", 32, 0, chips_pzloop2jd_key, N(chips_pzloop2jd_key)},
};
static const Cps2Load chips_hsf2d_maincpu[] = {
    {"hs2ad.03", 0x0153d371, 524288, 0, 0, 524288, CPS2_SWAP16},
    {"hs2ad.04", 0x0276b78a, 524288, 0, 524288, 524288, CPS2_SWAP16},
    {"hs2.05", 0xdde34a35, 524288, 0, 1048576, 524288, CPS2_SWAP16},
    {"hs2.06", 0xf4e56dda, 524288, 0, 1572864, 524288, CPS2_SWAP16},
    {"hs2.07", 0xee4420fc, 524288, 0, 2097152, 524288, CPS2_SWAP16},
    {"hs2.08", 0xc9441533, 524288, 0, 2621440, 524288, CPS2_SWAP16},
    {"hs2.09", 0x3fc638a8, 524288, 0, 3145728, 524288, CPS2_SWAP16},
    {"hs2.10", 0x20d0f9e4, 524288, 0, 3670016, 524288, CPS2_SWAP16},
};
static const Cps2Load chips_hsf2d_user1[] = {
    {NULL, 0, 0, 0, 0, 1048576, CPS2_FILL},
};
static const Cps2Load chips_hsf2d_gfx[] = {
    {"hs2.13m", 0xa6ecab17, 8388608, 0, 0, 8388608, CPS2_WORD64},
    {"hs2.15m", 0x10a0ae4d, 8388608, 0, 2, 8388608, CPS2_WORD64},
    {"hs2.17m", 0xadfa7726, 8388608, 0, 4, 8388608, CPS2_WORD64},
    {"hs2.19m", 0xbb3ae322, 8388608, 0, 6, 8388608, CPS2_WORD64},
};
static const Cps2Load chips_hsf2d_audiocpu[] = {
    {"hs2.01", 0xc1a13786, 131072, 0, 0, 32768, CPS2_LINEAR},
    {"hs2.01", 0xc1a13786, 131072, 32768, 65536, 98304, CPS2_LINEAR},
    {"hs2.02", 0x2d8794aa, 131072, 0, 163840, 131072, CPS2_LINEAR},
};
static const Cps2Load chips_hsf2d_qsound[] = {
    {"hs2.11m", 0x0e15c359, 8388608, 0, 0, 8388608, CPS2_SWAP16},
};
static const Cps2Load chips_hsf2d_key[] = {
    {"phoenix.key", 0x2cf772b0, 20, 0, 0, 20, CPS2_LINEAR},
};
static const Cps2Region regions_hsf2d[] = {
    {"maincpu", 4194304, 0, chips_hsf2d_maincpu, N(chips_hsf2d_maincpu)},
    {"user1", 4194304, 0, chips_hsf2d_user1, N(chips_hsf2d_user1)},
    {"gfx", 33554432, 0, chips_hsf2d_gfx, N(chips_hsf2d_gfx)},
    {"audiocpu", 327680, 0, chips_hsf2d_audiocpu, N(chips_hsf2d_audiocpu)},
    {"qsound", 8388608, 0, chips_hsf2d_qsound, N(chips_hsf2d_qsound)},
    {"key", 32, 0, chips_hsf2d_key, N(chips_hsf2d_key)},
};
const Cps2Game cps2_games[] = {
    {"ssf2", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The New Challengers (World 931005)", regions_ssf2, N(regions_ssf2)},
    {"ssf2r1", "ssf2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The New Challengers (World 930911)", regions_ssf2r1, N(regions_ssf2r1)},
    {"ssf2u", "ssf2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The New Challengers (USA 930911)", regions_ssf2u, N(regions_ssf2u)},
    {"ssf2us2", "ssf2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The New Challengers Super 2 (USA 930911)", regions_ssf2us2, N(regions_ssf2us2)},
    {"ssf2a", "ssf2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The New Challengers (Asia 931005)", regions_ssf2a, N(regions_ssf2a)},
    {"ssf2ar1", "ssf2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The New Challengers (Asia 930914)", regions_ssf2ar1, N(regions_ssf2ar1)},
    {"ssf2j", "ssf2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The New Challengers (Japan 931005)", regions_ssf2j, N(regions_ssf2j)},
    {"ssf2jr1", "ssf2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The New Challengers (Japan 930911)", regions_ssf2jr1, N(regions_ssf2jr1)},
    {"ssf2jr2", "ssf2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The New Challengers (Japan 930910)", regions_ssf2jr2, N(regions_ssf2jr2)},
    {"ssf2h", "ssf2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The New Challengers (Hispanic 930911)", regions_ssf2h, N(regions_ssf2h)},
    {"ssf2tb", "ssf2", "cps2comm", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The Tournament Battle (World 931119)", regions_ssf2tb, N(regions_ssf2tb)},
    {"ssf2tbr1", "ssf2", "cps2comm", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The Tournament Battle (World 930911)", regions_ssf2tbr1, N(regions_ssf2tbr1)},
    {"ssf2tbu", "ssf2", "cps2comm", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The Tournament Battle (USA 930911)", regions_ssf2tbu, N(regions_ssf2tbu)},
    {"ssf2tbj", "ssf2", "cps2comm", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The Tournament Battle (Japan 931005)", regions_ssf2tbj, N(regions_ssf2tbj)},
    {"ssf2tbj1", "ssf2", "cps2comm", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The Tournament Battle (Japan 930911)", regions_ssf2tbj1, N(regions_ssf2tbj1)},
    {"ssf2tba", "ssf2", "cps2comm", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The Tournament Battle (Asia 931005)", regions_ssf2tba, N(regions_ssf2tba)},
    {"ssf2tbh", "ssf2", "cps2comm", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The Tournament Battle (Hispanic 931005)", regions_ssf2tbh, N(regions_ssf2tbh)},
    {"ecofghtr", NULL, "cps2", "ecofghtr", "init_ecofghtr", "ROT0", "Eco Fighters (World 931203)", regions_ecofghtr, N(regions_ecofghtr)},
    {"ecofghtru", "ecofghtr", "cps2", "ecofghtr", "init_ecofghtr", "ROT0", "Eco Fighters (USA 940215)", regions_ecofghtru, N(regions_ecofghtru)},
    {"ecofghtru1", "ecofghtr", "cps2", "ecofghtr", "init_ecofghtr", "ROT0", "Eco Fighters (USA 931203)", regions_ecofghtru1, N(regions_ecofghtru1)},
    {"uecology", "ecofghtr", "cps2", "ecofghtr", "init_ecofghtr", "ROT0", "Ultimate Ecology (Japan 931203)", regions_uecology, N(regions_uecology)},
    {"ecofghtra", "ecofghtr", "cps2", "ecofghtr", "init_ecofghtr", "ROT0", "Eco Fighters (Asia 931203)", regions_ecofghtra, N(regions_ecofghtra)},
    {"ecofghtrh", "ecofghtr", "cps2", "ecofghtr", "init_ecofghtr", "ROT0", "Eco Fighters (Hispanic 931203)", regions_ecofghtrh, N(regions_ecofghtrh)},
    {"ddtod", NULL, "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Tower of Doom (Europe 940412)", regions_ddtod, N(regions_ddtod)},
    {"ddtodr1", "ddtod", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Tower of Doom (Europe 940113)", regions_ddtodr1, N(regions_ddtodr1)},
    {"ddtodu", "ddtod", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Tower of Doom (USA 940125)", regions_ddtodu, N(regions_ddtodu)},
    {"ddtodur1", "ddtod", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Tower of Doom (USA 940113)", regions_ddtodur1, N(regions_ddtodur1)},
    {"ddtodj", "ddtod", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Tower of Doom (Japan 940412)", regions_ddtodj, N(regions_ddtodj)},
    {"ddtodjr1", "ddtod", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Tower of Doom (Japan 940125)", regions_ddtodjr1, N(regions_ddtodjr1)},
    {"ddtodjr2", "ddtod", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Tower of Doom (Japan 940113)", regions_ddtodjr2, N(regions_ddtodjr2)},
    {"ddtoda", "ddtod", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Tower of Doom (Asia 940412)", regions_ddtoda, N(regions_ddtoda)},
    {"ddtodar1", "ddtod", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Tower of Doom (Asia 940113)", regions_ddtodar1, N(regions_ddtodar1)},
    {"ddtodh", "ddtod", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Tower of Doom (Hispanic 940412)", regions_ddtodh, N(regions_ddtodh)},
    {"ddtodhr1", "ddtod", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Tower of Doom (Hispanic 940125)", regions_ddtodhr1, N(regions_ddtodhr1)},
    {"ddtodhr2", "ddtod", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Tower of Doom (Hispanic 940113)", regions_ddtodhr2, N(regions_ddtodhr2)},
    {"ssf2t", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II Turbo (World 940223)", regions_ssf2t, N(regions_ssf2t)},
    {"ssf2ta", "ssf2t", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II Turbo (Asia 940223)", regions_ssf2ta, N(regions_ssf2ta)},
    {"ssf2th", "ssf2t", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II Turbo (Hispanic 940223)", regions_ssf2th, N(regions_ssf2th)},
    {"ssf2tu", "ssf2t", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II Turbo (USA 940323)", regions_ssf2tu, N(regions_ssf2tu)},
    {"ssf2tur1", "ssf2t", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II Turbo (USA 940223)", regions_ssf2tur1, N(regions_ssf2tur1)},
    {"ssf2xj", "ssf2t", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II X: Grand Master Challenge (Japan 940311)", regions_ssf2xj, N(regions_ssf2xj)},
    {"ssf2xjr1", "ssf2t", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II X: Grand Master Challenge (Japan 940223)", regions_ssf2xjr1, N(regions_ssf2xjr1)},
    {"ssf2xjr1r", "ssf2t", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II X: Grand Master Challenge (Japan 940223 rent version)", regions_ssf2xjr1r, N(regions_ssf2xjr1r)},
    {"avsp", NULL, "cps2", "cps2_3p3b", "init_cps2", "ROT0", "Alien vs. Predator (Europe 940520)", regions_avsp, N(regions_avsp)},
    {"avspu", "avsp", "cps2", "cps2_3p3b", "init_cps2", "ROT0", "Alien vs. Predator (USA 940520)", regions_avspu, N(regions_avspu)},
    {"avspj", "avsp", "cps2", "cps2_3p3b", "init_cps2", "ROT0", "Alien vs. Predator (Japan 940520)", regions_avspj, N(regions_avspj)},
    {"avspa", "avsp", "cps2", "cps2_3p3b", "init_cps2", "ROT0", "Alien vs. Predator (Asia 940520)", regions_avspa, N(regions_avspa)},
    {"avsph", "avsp", "cps2", "cps2_3p3b", "init_cps2", "ROT0", "Alien vs. Predator (Hispanic 940520)", regions_avsph, N(regions_avsph)},
    {"dstlk", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Darkstalkers: The Night Warriors (Europe 940705)", regions_dstlk, N(regions_dstlk)},
    {"dstlku", "dstlk", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Darkstalkers: The Night Warriors (USA 940818)", regions_dstlku, N(regions_dstlku)},
    {"dstlkur1", "dstlk", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Darkstalkers: The Night Warriors (USA 940705)", regions_dstlkur1, N(regions_dstlkur1)},
    {"dstlka", "dstlk", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Darkstalkers: The Night Warriors (Asia 940705)", regions_dstlka, N(regions_dstlka)},
    {"dstlkh", "dstlk", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Darkstalkers: The Night Warriors (Hispanic 940818)", regions_dstlkh, N(regions_dstlkh)},
    {"dstlkb", "dstlk", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Darkstalkers: The Night Warriors (Brazil 940818)", regions_dstlkb, N(regions_dstlkb)},
    {"vampj", "dstlk", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire: The Night Warriors (Japan 940705)", regions_vampj, N(regions_vampj)},
    {"vampja", "dstlk", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire: The Night Warriors (Japan 940705 alt)", regions_vampja, N(regions_vampja)},
    {"vampjr1", "dstlk", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire: The Night Warriors (Japan 940630)", regions_vampjr1, N(regions_vampjr1)},
    {"ringdest", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Ring of Destruction: Slammasters II (Europe 940902)", regions_ringdest, N(regions_ringdest)},
    {"ringdesta", "ringdest", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Ring of Destruction: Slammasters II (Asia 940831)", regions_ringdesta, N(regions_ringdesta)},
    {"ringdesth", "ringdest", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Ring of Destruction: Slammasters II (Hispanic 940902)", regions_ringdesth, N(regions_ringdesth)},
    {"ringdestb", "ringdest", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Ring of Destruction: Slammasters II (Brazil 940902)", regions_ringdestb, N(regions_ringdestb)},
    {"smbomb", "ringdest", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Muscle Bomber: The International Blowout (Japan 940831)", regions_smbomb, N(regions_smbomb)},
    {"smbombr1", "ringdest", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Muscle Bomber: The International Blowout (Japan 940808)", regions_smbombr1, N(regions_smbombr1)},
    {"armwar", NULL, "cps2", "cps2_3p3b", "init_cps2", "ROT0", "Armored Warriors (Europe 941024)", regions_armwar, N(regions_armwar)},
    {"armwarr1", "armwar", "cps2", "cps2_3p3b", "init_cps2", "ROT0", "Armored Warriors (Europe 941011)", regions_armwarr1, N(regions_armwarr1)},
    {"armwaru", "armwar", "cps2", "cps2_3p3b", "init_cps2", "ROT0", "Armored Warriors (USA 941024)", regions_armwaru, N(regions_armwaru)},
    {"armwaru1", "armwar", "cps2", "cps2_3p3b", "init_cps2", "ROT0", "Armored Warriors (USA 940920)", regions_armwaru1, N(regions_armwaru1)},
    {"armwarb", "armwar", "cps2", "cps2_3p3b", "init_cps2", "ROT0", "Armored Warriors (Brazil 941024)", regions_armwarb, N(regions_armwarb)},
    {"pgear", "armwar", "cps2", "cps2_3p3b", "init_cps2", "ROT0", "Powered Gear: Strategic Variant Armor Equipment (Japan 941024)", regions_pgear, N(regions_pgear)},
    {"pgearr1", "armwar", "cps2", "cps2_3p3b", "init_cps2", "ROT0", "Powered Gear: Strategic Variant Armor Equipment (Japan 940916)", regions_pgearr1, N(regions_pgearr1)},
    {"armwara", "armwar", "cps2", "cps2_3p3b", "init_cps2", "ROT0", "Armored Warriors (Asia 941024)", regions_armwara, N(regions_armwara)},
    {"armwarar1", "armwar", "cps2", "cps2_3p3b", "init_cps2", "ROT0", "Armored Warriors (Asia 940920)", regions_armwarar1, N(regions_armwarar1)},
    {"xmcota", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men: Children of the Atom (Europe 950331)", regions_xmcota, N(regions_xmcota)},
    {"xmcotar1", "xmcota", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men: Children of the Atom (Europe 950105)", regions_xmcotar1, N(regions_xmcotar1)},
    {"xmcotau", "xmcota", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men: Children of the Atom (USA 950105)", regions_xmcotau, N(regions_xmcotau)},
    {"xmcotab", "xmcota", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men: Children of the Atom (Brazil 950331)", regions_xmcotab, N(regions_xmcotab)},
    {"xmcotah", "xmcota", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men: Children of the Atom (Hispanic 950331)", regions_xmcotah, N(regions_xmcotah)},
    {"xmcotahr1", "xmcota", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men: Children of the Atom (Hispanic 950105)", regions_xmcotahr1, N(regions_xmcotahr1)},
    {"xmcotaj", "xmcota", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men: Children of the Atom (Japan 950105)", regions_xmcotaj, N(regions_xmcotaj)},
    {"xmcotaj1", "xmcota", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men: Children of the Atom (Japan 941222)", regions_xmcotaj1, N(regions_xmcotaj1)},
    {"xmcotaj2", "xmcota", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men: Children of the Atom (Japan 941219)", regions_xmcotaj2, N(regions_xmcotaj2)},
    {"xmcotaj3", "xmcota", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men: Children of the Atom (Japan 941217)", regions_xmcotaj3, N(regions_xmcotaj3)},
    {"xmcotajr", "xmcota", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men: Children of the Atom (Japan 941208 rent version)", regions_xmcotajr, N(regions_xmcotajr)},
    {"xmcotaa", "xmcota", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men: Children of the Atom (Asia 950105)", regions_xmcotaa, N(regions_xmcotaa)},
    {"xmcotaar1", "xmcota", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men: Children of the Atom (Asia 941219)", regions_xmcotaar1, N(regions_xmcotaar1)},
    {"xmcotaar2", "xmcota", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men: Children of the Atom (Asia 941217)", regions_xmcotaar2, N(regions_xmcotaar2)},
    {"nwarr", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Night Warriors: Darkstalkers' Revenge (Europe 950316)", regions_nwarr, N(regions_nwarr)},
    {"nwarru", "nwarr", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Night Warriors: Darkstalkers' Revenge (USA 950406)", regions_nwarru, N(regions_nwarru)},
    {"nwarrh", "nwarr", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Night Warriors: Darkstalkers' Revenge (Hispanic 950403)", regions_nwarrh, N(regions_nwarrh)},
    {"nwarrb", "nwarr", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Night Warriors: Darkstalkers' Revenge (Brazil 950403)", regions_nwarrb, N(regions_nwarrb)},
    {"nwarra", "nwarr", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Night Warriors: Darkstalkers' Revenge (Asia 950302)", regions_nwarra, N(regions_nwarra)},
    {"vhuntj", "nwarr", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Hunter: Darkstalkers' Revenge (Japan 950316)", regions_vhuntj, N(regions_vhuntj)},
    {"vhuntjr1s", "nwarr", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Hunter: Darkstalkers' Revenge (Japan 950307 stop version)", regions_vhuntjr1s, N(regions_vhuntjr1s)},
    {"vhuntjr1", "nwarr", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Hunter: Darkstalkers' Revenge (Japan 950307)", regions_vhuntjr1, N(regions_vhuntjr1)},
    {"vhuntjr2", "nwarr", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Hunter: Darkstalkers' Revenge (Japan 950302)", regions_vhuntjr2, N(regions_vhuntjr2)},
    {"cybots", NULL, "cps2", "cybots", "init_cps2", "ROT0", "Cyberbots: Fullmetal Madness (Europe 950424)", regions_cybots, N(regions_cybots)},
    {"cybotsu", "cybots", "cps2", "cybots", "init_cps2", "ROT0", "Cyberbots: Fullmetal Madness (USA 950424)", regions_cybotsu, N(regions_cybotsu)},
    {"cybotsj", "cybots", "cps2", "cybots", "init_cps2", "ROT0", "Cyberbots: Fullmetal Madness (Japan 950420)", regions_cybotsj, N(regions_cybotsj)},
    {"sfa", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Alpha: Warriors' Dreams (Europe 950727)", regions_sfa, N(regions_sfa)},
    {"sfar1", "sfa", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Alpha: Warriors' Dreams (Europe 950718)", regions_sfar1, N(regions_sfar1)},
    {"sfar2", "sfa", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Alpha: Warriors' Dreams (Europe 950627)", regions_sfar2, N(regions_sfar2)},
    {"sfar3", "sfa", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Alpha: Warriors' Dreams (Europe 950605)", regions_sfar3, N(regions_sfar3)},
    {"sfau", "sfa", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Alpha: Warriors' Dreams (USA 950627)", regions_sfau, N(regions_sfau)},
    {"sfza", "sfa", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero (Asia 950627)", regions_sfza, N(regions_sfza)},
    {"sfzar1", "sfa", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero (Asia 950605)", regions_sfzar1, N(regions_sfzar1)},
    {"sfzj", "sfa", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero (Japan 950727)", regions_sfzj, N(regions_sfzj)},
    {"sfzjr1", "sfa", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero (Japan 950627)", regions_sfzjr1, N(regions_sfzjr1)},
    {"sfzjr2", "sfa", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero (Japan 950605)", regions_sfzjr2, N(regions_sfzjr2)},
    {"sfzh", "sfa", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero (Hispanic 950718)", regions_sfzh, N(regions_sfzh)},
    {"sfzhr1", "sfa", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero (Hispanic 950627)", regions_sfzhr1, N(regions_sfzhr1)},
    {"sfzb", "sfa", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero (Brazil 951109)", regions_sfzb, N(regions_sfzb)},
    {"sfzbr1", "sfa", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero (Brazil 950727)", regions_sfzbr1, N(regions_sfzbr1)},
    {"mmancp2u", "megaman", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Mega Man: The Power Battle (CPS2, USA 951006, SAMPLE Version)", regions_mmancp2u, N(regions_mmancp2u)},
    {"mmancp2ur1", "megaman", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Mega Man: The Power Battle (CPS2, USA 950926, SAMPLE Version)", regions_mmancp2ur1, N(regions_mmancp2ur1)},
    {"mmancp2ur2", "megaman", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Mega Man: The Power Battle (CPS2, USA 950925, SAMPLE Version)", regions_mmancp2ur2, N(regions_mmancp2ur2)},
    {"rmancp2j", "megaman", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Rockman: The Power Battle (CPS2, Japan 950922)", regions_rmancp2j, N(regions_rmancp2j)},
    {"msh", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes (Europe 951024)", regions_msh, N(regions_msh)},
    {"mshu", "msh", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes (USA 951024)", regions_mshu, N(regions_mshu)},
    {"mshj", "msh", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes (Japan 951117)", regions_mshj, N(regions_mshj)},
    {"mshjr1", "msh", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes (Japan 951024)", regions_mshjr1, N(regions_mshjr1)},
    {"msha", "msh", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes (Asia 951024)", regions_msha, N(regions_msha)},
    {"mshh", "msh", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes (Hispanic 951117)", regions_mshh, N(regions_mshh)},
    {"mshb", "msh", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes (Brazil 951117)", regions_mshb, N(regions_mshb)},
    {"mshbr1", "msh", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes (Brazil 951024)", regions_mshbr1, N(regions_mshbr1)},
    {"19xx", NULL, "cps2", "cps2_2p2b", "init_cps2", "ROT270", "19XX: The War Against Destiny (Europe 960104)", regions_19xx, N(regions_19xx)},
    {"19xxu", "19xx", "cps2", "cps2_2p2b", "init_cps2", "ROT270", "19XX: The War Against Destiny (USA 951207)", regions_19xxu, N(regions_19xxu)},
    {"19xxa", "19xx", "cps2", "cps2_2p2b", "init_cps2", "ROT270", "19XX: The War Against Destiny (Asia 960104)", regions_19xxa, N(regions_19xxa)},
    {"19xxar1", "19xx", "cps2", "cps2_2p2b", "init_cps2", "ROT270", "19XX: The War Against Destiny (Asia 951207)", regions_19xxar1, N(regions_19xxar1)},
    {"19xxj", "19xx", "cps2", "cps2_2p2b", "init_cps2", "ROT270", "19XX: The War Against Destiny (Japan 960104, yellow case)", regions_19xxj, N(regions_19xxj)},
    {"19xxjr1", "19xx", "cps2", "cps2_2p2b", "init_cps2", "ROT270", "19XX: The War Against Destiny (Japan 951225)", regions_19xxjr1, N(regions_19xxjr1)},
    {"19xxjr2", "19xx", "cps2", "cps2_2p2b", "init_cps2", "ROT270", "19XX: The War Against Destiny (Japan 951207)", regions_19xxjr2, N(regions_19xxjr2)},
    {"19xxh", "19xx", "cps2", "cps2_2p2b", "init_cps2", "ROT270", "19XX: The War Against Destiny (Hispanic 951218)", regions_19xxh, N(regions_19xxh)},
    {"19xxb", "19xx", "cps2", "cps2_2p2b", "init_cps2", "ROT270", "19XX: The War Against Destiny (Brazil 951218)", regions_19xxb, N(regions_19xxb)},
    {"ddsom", NULL, "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Shadow over Mystara (Europe 960619)", regions_ddsom, N(regions_ddsom)},
    {"ddsomr1", "ddsom", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Shadow over Mystara (Europe 960223)", regions_ddsomr1, N(regions_ddsomr1)},
    {"ddsomr2", "ddsom", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Shadow over Mystara (Europe 960209)", regions_ddsomr2, N(regions_ddsomr2)},
    {"ddsomr3", "ddsom", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Shadow over Mystara (Europe 960208)", regions_ddsomr3, N(regions_ddsomr3)},
    {"ddsomu", "ddsom", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Shadow over Mystara (USA 960619)", regions_ddsomu, N(regions_ddsomu)},
    {"ddsomur1", "ddsom", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Shadow over Mystara (USA 960209)", regions_ddsomur1, N(regions_ddsomur1)},
    {"ddsomj", "ddsom", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Shadow over Mystara (Japan 960619)", regions_ddsomj, N(regions_ddsomj)},
    {"ddsomjr1", "ddsom", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Shadow over Mystara (Japan 960223)", regions_ddsomjr1, N(regions_ddsomjr1)},
    {"ddsomjr2", "ddsom", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Shadow over Mystara (Japan 960206)", regions_ddsomjr2, N(regions_ddsomjr2)},
    {"ddsoma", "ddsom", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Shadow over Mystara (Asia 960619)", regions_ddsoma, N(regions_ddsoma)},
    {"ddsomar1", "ddsom", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Shadow over Mystara (Asia 960208)", regions_ddsomar1, N(regions_ddsomar1)},
    {"ddsomh", "ddsom", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Shadow over Mystara (Hispanic 960223)", regions_ddsomh, N(regions_ddsomh)},
    {"ddsomb", "ddsom", "cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Shadow over Mystara (Brazil 960223)", regions_ddsomb, N(regions_ddsomb)},
    {"sfa2", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Alpha 2 (Europe 960229)", regions_sfa2, N(regions_sfa2)},
    {"sfa2u", "sfa2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Alpha 2 (USA 960430)", regions_sfa2u, N(regions_sfa2u)},
    {"sfa2ur1", "sfa2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Alpha 2 (USA 960306)", regions_sfa2ur1, N(regions_sfa2ur1)},
    {"sfz2j", "sfa2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 2 (Japan 960430)", regions_sfz2j, N(regions_sfz2j)},
    {"sfz2jr1", "sfa2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 2 (Japan 960227)", regions_sfz2jr1, N(regions_sfz2jr1)},
    {"sfz2a", "sfa2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 2 (Asia 960227)", regions_sfz2a, N(regions_sfz2a)},
    {"sfz2b", "sfa2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 2 (Brazil 960531)", regions_sfz2b, N(regions_sfz2b)},
    {"sfz2br1", "sfa2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 2 (Brazil 960304)", regions_sfz2br1, N(regions_sfz2br1)},
    {"sfz2h", "sfa2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 2 (Hispanic 960304)", regions_sfz2h, N(regions_sfz2h)},
    {"sfz2n", "sfa2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 2 (Oceania 960229)", regions_sfz2n, N(regions_sfz2n)},
    {"sfz2al", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 2 Alpha (Asia 960826)", regions_sfz2al, N(regions_sfz2al)},
    {"sfz2alr1", "sfz2al", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 2 Alpha (Asia 960805)", regions_sfz2alr1, N(regions_sfz2alr1)},
    {"sfz2alj", "sfz2al", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 2 Alpha (Japan 960805)", regions_sfz2alj, N(regions_sfz2alj)},
    {"sfz2alh", "sfz2al", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 2 Alpha (Hispanic 960813)", regions_sfz2alh, N(regions_sfz2alh)},
    {"sfz2alb", "sfz2al", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 2 Alpha (Brazil 960813)", regions_sfz2alb, N(regions_sfz2alb)},
    {"spf2t", NULL, "cps2", "cps2_2p2b", "init_cps2", "ROT0", "Super Puzzle Fighter II Turbo (Europe 960529)", regions_spf2t, N(regions_spf2t)},
    {"spf2tu", "spf2t", "cps2", "cps2_2p2b", "init_cps2", "ROT0", "Super Puzzle Fighter II Turbo (USA 960620)", regions_spf2tu, N(regions_spf2tu)},
    {"spf2xj", "spf2t", "cps2", "cps2_2p2b", "init_cps2", "ROT0", "Super Puzzle Fighter II X (Japan 960531)", regions_spf2xj, N(regions_spf2xj)},
    {"spf2ta", "spf2t", "cps2", "cps2_2p2b", "init_cps2", "ROT0", "Super Puzzle Fighter II Turbo (Asia 960529)", regions_spf2ta, N(regions_spf2ta)},
    {"spf2th", "spf2t", "cps2", "cps2_2p2b", "init_cps2", "ROT0", "Super Puzzle Fighter II Turbo (Hispanic 960531)", regions_spf2th, N(regions_spf2th)},
    {"megaman2", NULL, "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Mega Man 2: The Power Fighters (USA 960708)", regions_megaman2, N(regions_megaman2)},
    {"megaman2a", "megaman2", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Mega Man 2: The Power Fighters (Asia 960708)", regions_megaman2a, N(regions_megaman2a)},
    {"rockman2j", "megaman2", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Rockman 2: The Power Fighters (Japan 960708)", regions_rockman2j, N(regions_rockman2j)},
    {"megaman2h", "megaman2", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Mega Man 2: The Power Fighters (Hispanic 960712)", regions_megaman2h, N(regions_megaman2h)},
    {"qndream", NULL, "cps2", "qndream", "init_cps2", "ROT0", "Quiz Nanairo Dreams: Nijiirochou no Kiseki (Japan 960826)", regions_qndream, N(regions_qndream)},
    {"xmvsf", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (Europe 961004)", regions_xmvsf, N(regions_xmvsf)},
    {"xmvsfr1", "xmvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (Europe 960910)", regions_xmvsfr1, N(regions_xmvsfr1)},
    {"xmvsfu", "xmvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (USA 961023)", regions_xmvsfu, N(regions_xmvsfu)},
    {"xmvsfur1", "xmvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (USA 961004)", regions_xmvsfur1, N(regions_xmvsfur1)},
    {"xmvsfur2", "xmvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (USA 960910)", regions_xmvsfur2, N(regions_xmvsfur2)},
    {"xmvsfj", "xmvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (Japan 970113)", regions_xmvsfj, N(regions_xmvsfj)},
    {"xmvsfjr1", "xmvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (Japan 961023)", regions_xmvsfjr1, N(regions_xmvsfjr1)},
    {"xmvsfjr2", "xmvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (Japan 961004)", regions_xmvsfjr2, N(regions_xmvsfjr2)},
    {"xmvsfjr3", "xmvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (Japan 960910)", regions_xmvsfjr3, N(regions_xmvsfjr3)},
    {"xmvsfjr4", "xmvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (Japan 960909)", regions_xmvsfjr4, N(regions_xmvsfjr4)},
    {"xmvsfa", "xmvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (Asia 961023)", regions_xmvsfa, N(regions_xmvsfa)},
    {"xmvsfar1", "xmvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (Asia 961004)", regions_xmvsfar1, N(regions_xmvsfar1)},
    {"xmvsfar2", "xmvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (Asia 960919)", regions_xmvsfar2, N(regions_xmvsfar2)},
    {"xmvsfar3", "xmvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (Asia 960910)", regions_xmvsfar3, N(regions_xmvsfar3)},
    {"xmvsfh", "xmvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (Hispanic 961004)", regions_xmvsfh, N(regions_xmvsfh)},
    {"xmvsfb", "xmvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (Brazil 961023)", regions_xmvsfb, N(regions_xmvsfb)},
    {"batcir", NULL, "cps2", "cps2_4p2b", "init_cps2", "ROT0", "Battle Circuit (Europe 970319)", regions_batcir, N(regions_batcir)},
    {"batcira", "batcir", "cps2", "cps2_4p2b", "init_cps2", "ROT0", "Battle Circuit (Asia 970319)", regions_batcira, N(regions_batcira)},
    {"batcirj", "batcir", "cps2", "cps2_4p2b", "init_cps2", "ROT0", "Battle Circuit (Japan 970319)", regions_batcirj, N(regions_batcirj)},
    {"vsav", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Savior: The Lord of Vampire (Europe 970519)", regions_vsav, N(regions_vsav)},
    {"vsavu", "vsav", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Savior: The Lord of Vampire (USA 970519)", regions_vsavu, N(regions_vsavu)},
    {"vsavj", "vsav", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Savior: The Lord of Vampire (Japan 970519)", regions_vsavj, N(regions_vsavj)},
    {"vsava", "vsav", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Savior: The Lord of Vampire (Asia 970519)", regions_vsava, N(regions_vsava)},
    {"vsavh", "vsav", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Savior: The Lord of Vampire (Hispanic 970519)", regions_vsavh, N(regions_vsavh)},
    {"vsavb", "vsav", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Savior: The Lord of Vampire (Brazil 970519)", regions_vsavb, N(regions_vsavb)},
    {"mshvsf", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes Vs. Street Fighter (Europe 970625)", regions_mshvsf, N(regions_mshvsf)},
    {"mshvsfu", "mshvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes Vs. Street Fighter (USA 970827)", regions_mshvsfu, N(regions_mshvsfu)},
    {"mshvsfu1", "mshvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes Vs. Street Fighter (USA 970625)", regions_mshvsfu1, N(regions_mshvsfu1)},
    {"mshvsfj", "mshvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes Vs. Street Fighter (Japan 970707)", regions_mshvsfj, N(regions_mshvsfj)},
    {"mshvsfj1", "mshvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes Vs. Street Fighter (Japan 970702)", regions_mshvsfj1, N(regions_mshvsfj1)},
    {"mshvsfj2", "mshvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes Vs. Street Fighter (Japan 970625)", regions_mshvsfj2, N(regions_mshvsfj2)},
    {"mshvsfh", "mshvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes Vs. Street Fighter (Hispanic 970625)", regions_mshvsfh, N(regions_mshvsfh)},
    {"mshvsfa", "mshvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes Vs. Street Fighter (Asia 970625)", regions_mshvsfa, N(regions_mshvsfa)},
    {"mshvsfa1", "mshvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes Vs. Street Fighter (Asia 970620)", regions_mshvsfa1, N(regions_mshvsfa1)},
    {"mshvsfb", "mshvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes Vs. Street Fighter (Brazil 970827)", regions_mshvsfb, N(regions_mshvsfb)},
    {"mshvsfb1", "mshvsf", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes Vs. Street Fighter (Brazil 970625)", regions_mshvsfb1, N(regions_mshvsfb1)},
    {"csclub", NULL, "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Capcom Sports Club (Europe 971017)", regions_csclub, N(regions_csclub)},
    {"csclub1", "csclub", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Capcom Sports Club (Europe 970722)", regions_csclub1, N(regions_csclub1)},
    {"cscluba", "csclub", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Capcom Sports Club (Asia 970722)", regions_cscluba, N(regions_cscluba)},
    {"csclubj", "csclub", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Capcom Sports Club (Japan 970722)", regions_csclubj, N(regions_csclubj)},
    {"csclubjy", "csclub", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Capcom Sports Club (Japan 970722, yellow case)", regions_csclubjy, N(regions_csclubjy)},
    {"csclubh", "csclub", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Capcom Sports Club (Hispanic 970722)", regions_csclubh, N(regions_csclubh)},
    {"sgemf", NULL, "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Super Gem Fighter: Mini Mix (USA 970904)", regions_sgemf, N(regions_sgemf)},
    {"pfghtj", "sgemf", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Pocket Fighter (Japan 970904)", regions_pfghtj, N(regions_pfghtj)},
    {"sgemfa", "sgemf", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Super Gem Fighter: Mini Mix (Asia 970904)", regions_sgemfa, N(regions_sgemfa)},
    {"sgemfh", "sgemf", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Super Gem Fighter: Mini Mix (Hispanic 970904)", regions_sgemfh, N(regions_sgemfh)},
    {"vhunt2", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Hunter 2: Darkstalkers Revenge (Japan 970929)", regions_vhunt2, N(regions_vhunt2)},
    {"vhunt2r1", "vhunt2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Hunter 2: Darkstalkers Revenge (Japan 970913)", regions_vhunt2r1, N(regions_vhunt2r1)},
    {"vsav2", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Savior 2: The Lord of Vampire (Japan 970913)", regions_vsav2, N(regions_vsav2)},
    {"mvsc", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Vs. Capcom: Clash of Super Heroes (Europe 980123)", regions_mvsc, N(regions_mvsc)},
    {"mvscr1", "mvsc", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Vs. Capcom: Clash of Super Heroes (Europe 980112)", regions_mvscr1, N(regions_mvscr1)},
    {"mvscu", "mvsc", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Vs. Capcom: Clash of Super Heroes (USA 980123)", regions_mvscu, N(regions_mvscu)},
    {"mvscur1", "mvsc", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Vs. Capcom: Clash of Super Heroes (USA 971222)", regions_mvscur1, N(regions_mvscur1)},
    {"mvscj", "mvsc", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Vs. Capcom: Clash of Super Heroes (Japan 980123)", regions_mvscj, N(regions_mvscj)},
    {"mvscjr1", "mvsc", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Vs. Capcom: Clash of Super Heroes (Japan 980112)", regions_mvscjr1, N(regions_mvscjr1)},
    {"mvscjsing", "mvsc", "cps2", "cps2_2p6b", "init_singbrd", "ROT0", "Marvel Vs. Capcom: Clash of Super Heroes (Japan 980123) (Single PCB)", regions_mvscjsing, N(regions_mvscjsing)},
    {"mvsca", "mvsc", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Vs. Capcom: Clash of Super Heroes (Asia 980123)", regions_mvsca, N(regions_mvsca)},
    {"mvscar1", "mvsc", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Vs. Capcom: Clash of Super Heroes (Asia 980112)", regions_mvscar1, N(regions_mvscar1)},
    {"mvsch", "mvsc", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Vs. Capcom: Clash of Super Heroes (Hispanic 980123)", regions_mvsch, N(regions_mvsch)},
    {"mvscb", "mvsc", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Vs. Capcom: Clash of Super Heroes (Brazil 980123)", regions_mvscb, N(regions_mvscb)},
    {"sfa3", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Alpha 3 (Europe 980904)", regions_sfa3, N(regions_sfa3)},
    {"sfa3u", "sfa3", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Alpha 3 (USA 980904)", regions_sfa3u, N(regions_sfa3u)},
    {"sfa3ur1", "sfa3", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Alpha 3 (USA 980629)", regions_sfa3ur1, N(regions_sfa3ur1)},
    {"sfa3us", "sfa3", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Alpha 3 (USA 980616, SAMPLE Version)", regions_sfa3us, N(regions_sfa3us)},
    {"sfa3h", "sfa3", "cps2", "cps2_2p6bt", "init_cps2", "ROT0", "Street Fighter Alpha 3 (Hispanic 980904)", regions_sfa3h, N(regions_sfa3h)},
    {"sfa3hr1", "sfa3", "cps2", "cps2_2p6bt", "init_cps2", "ROT0", "Street Fighter Alpha 3 (Hispanic 980629)", regions_sfa3hr1, N(regions_sfa3hr1)},
    {"sfa3b", "sfa3", "cps2", "cps2_2p6bt", "init_cps2", "ROT0", "Street Fighter Alpha 3 (Brazil 980629)", regions_sfa3b, N(regions_sfa3b)},
    {"sfz3j", "sfa3", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 3 (Japan 980904)", regions_sfz3j, N(regions_sfz3j)},
    {"sfz3jr1", "sfa3", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 3 (Japan 980727)", regions_sfz3jr1, N(regions_sfz3jr1)},
    {"sfz3jr2", "sfa3", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 3 (Japan 980629)", regions_sfz3jr2, N(regions_sfz3jr2)},
    {"sfz3a", "sfa3", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 3 (Asia 980904)", regions_sfz3a, N(regions_sfz3a)},
    {"sfz3ar1", "sfa3", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 3 (Asia 980701)", regions_sfz3ar1, N(regions_sfz3ar1)},
    {"jyangoku", NULL, "cps2", "cps2_1p2b", "init_cps2", "ROT0", "Jyangokushi: Haoh no Saihai (Japan 990527)", regions_jyangoku, N(regions_jyangoku)},
    {"hsf2", NULL, "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Hyper Street Fighter II: The Anniversary Edition (USA 040202)", regions_hsf2, N(regions_hsf2)},
    {"hsf2a", "hsf2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Hyper Street Fighter II: The Anniversary Edition (Asia 040202)", regions_hsf2a, N(regions_hsf2a)},
    {"hsf2j", "hsf2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Hyper Street Fighter II: The Anniversary Edition (Japan 040202)", regions_hsf2j, N(regions_hsf2j)},
    {"hsf2j1", "hsf2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Hyper Street Fighter II: The Anniversary Edition (Japan 040123)", regions_hsf2j1, N(regions_hsf2j1)},
    {"hsf2j2", "hsf2", "cps2", "cps2_2p6b", "init_cps2", "ROT0", "Hyper Street Fighter II: The Anniversary Edition (Japan 031222)", regions_hsf2j2, N(regions_hsf2j2)},
    {"gigawing", NULL, "cps2", "cps2_2p2b", "init_cps2", "ROT0", "Giga Wing (USA 990222)", regions_gigawing, N(regions_gigawing)},
    {"gigawingj", "gigawing", "cps2", "cps2_2p2b", "init_cps2", "ROT0", "Giga Wing (Japan 990223)", regions_gigawingj, N(regions_gigawingj)},
    {"gigawinga", "gigawing", "cps2", "cps2_2p2b", "init_cps2", "ROT0", "Giga Wing (Asia 990222)", regions_gigawinga, N(regions_gigawinga)},
    {"gigawingh", "gigawing", "cps2", "cps2_2p2b", "init_cps2", "ROT0", "Giga Wing (Hispanic 990222)", regions_gigawingh, N(regions_gigawingh)},
    {"gigawingb", "gigawing", "cps2", "cps2_2p2b", "init_cps2", "ROT0", "Giga Wing (Brazil 990222)", regions_gigawingb, N(regions_gigawingb)},
    {"mmatrix", NULL, "cps2", "cps2_2p1b", "init_cps2", "ROT0", "Mars Matrix: Hyper Solid Shooting (USA 000412)", regions_mmatrix, N(regions_mmatrix)},
    {"mmatrixa", "mmatrix", "cps2", "cps2_2p1b", "init_cps2", "ROT0", "Mars Matrix: Hyper Solid Shooting (Asia 000412)", regions_mmatrixa, N(regions_mmatrixa)},
    {"mmatrixj", "mmatrix", "cps2", "cps2_2p1b", "init_cps2", "ROT0", "Mars Matrix: Hyper Solid Shooting (Japan 000412)", regions_mmatrixj, N(regions_mmatrixj)},
    {"mpang", NULL, "cps2", "cps2_2p1b", "init_cps2", "ROT0", "Mighty! Pang (Europe 001010)", regions_mpang, N(regions_mpang)},
    {"mpangr1", "mpang", "cps2", "cps2_2p1b", "init_cps2", "ROT0", "Mighty! Pang (Europe 000925)", regions_mpangr1, N(regions_mpangr1)},
    {"mpangu", "mpang", "cps2", "cps2_2p1b", "init_cps2", "ROT0", "Mighty! Pang (USA 001010)", regions_mpangu, N(regions_mpangu)},
    {"mpangj", "mpang", "cps2", "cps2_2p1b", "init_cps2", "ROT0", "Mighty! Pang (Japan 001011)", regions_mpangj, N(regions_mpangj)},
    {"mpanga", "mpang", "cps2", "cps2_2p1b", "init_cps2", "ROT0", "Mighty! Pang (Asia 001010)", regions_mpanga, N(regions_mpanga)},
    {"pzloop2", NULL, "cps2", "pzloop2", "init_pzloop2", "ROT0", "Puzz Loop 2 (Europe 010302)", regions_pzloop2, N(regions_pzloop2)},
    {"pzloop2j", "pzloop2", "cps2", "pzloop2", "init_pzloop2", "ROT0", "Puzz Loop 2 (Japan 010226)", regions_pzloop2j, N(regions_pzloop2j)},
    {"pzloop2jr1", "pzloop2", "cps2", "pzloop2", "init_pzloop2", "ROT0", "Puzz Loop 2 (Japan 010205)", regions_pzloop2jr1, N(regions_pzloop2jr1)},
    {"pzloop2jp", "pzloop2", "dead_cps2", "pzloop2", "init_pzloop2", "ROT0", "Puzz Loop 2 (Japan 010201 Publicity)", regions_pzloop2jp, N(regions_pzloop2jp)},
    {"choko", NULL, "cps2", "choko", "init_cps2", "ROT0", "Janpai Puzzle Choukou (Japan 010820)", regions_choko, N(regions_choko)},
    {"chokop", "choko", "dead_cps2", "choko", "init_cps2", "ROT0", "Janpai Puzzle Choukou (Japan 010820 Publicity)", regions_chokop, N(regions_chokop)},
    {"dimahoo", NULL, "cps2", "cps2_2p3b", "init_cps2", "ROT270", "Dimahoo (Europe 000121)", regions_dimahoo, N(regions_dimahoo)},
    {"dimahoou", "dimahoo", "cps2", "cps2_2p3b", "init_cps2", "ROT270", "Dimahoo (USA 000121)", regions_dimahoou, N(regions_dimahoou)},
    {"gmahou", "dimahoo", "cps2", "cps2_2p3b", "init_cps2", "ROT270", "Great Mahou Daisakusen (Japan 000121)", regions_gmahou, N(regions_gmahou)},
    {"1944", NULL, "cps2", "cps2_2p2b", "init_cps2", "ROT0", "1944: The Loop Master (Europe 000620)", regions_1944, N(regions_1944)},
    {"1944j", "1944", "cps2", "cps2_2p2b", "init_cps2", "ROT0", "1944: The Loop Master (Japan 000620)", regions_1944j, N(regions_1944j)},
    {"1944u", "1944", "cps2", "cps2_2p2b", "init_cps2", "ROT0", "1944: The Loop Master (USA 000620)", regions_1944u, N(regions_1944u)},
    {"progear", NULL, "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Progear (Europe 010117)", regions_progear, N(regions_progear)},
    {"progearu", "progear", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Progear (USA 010117)", regions_progearu, N(regions_progearu)},
    {"progearj", "progear", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Progear no Arashi (Japan 010117)", regions_progearj, N(regions_progearj)},
    {"progeara", "progear", "cps2", "cps2_2p3b", "init_cps2", "ROT0", "Progear (Asia 010117)", regions_progeara, N(regions_progeara)},
    {"ddtodd", "ddtod", "dead_cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Tower of Doom (Europe 940412 Phoenix Edition) (bootleg)", regions_ddtodd, N(regions_ddtodd)},
    {"ecofghtrd", "ecofghtr", "dead_cps2", "ecofghtr", "init_ecofghtr", "ROT0", "Eco Fighters (World 931203 Phoenix Edition) (bootleg)", regions_ecofghtrd, N(regions_ecofghtrd)},
    {"ssf2ud", "ssf2", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The New Challengers (USA 930911 Phoenix Edition) (bootleg)", regions_ssf2ud, N(regions_ssf2ud)},
    {"ssf2tbd", "ssf2", "dead_cps2comm", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II: The Tournament Battle (World 931119 Phoenix Edition) (bootleg)", regions_ssf2tbd, N(regions_ssf2tbd)},
    {"armwar1d", "armwar", "dead_cps2", "cps2_3p3b", "init_cps2", "ROT0", "Armored Warriors (Europe 941011 Phoenix Edition) (bootleg)", regions_armwar1d, N(regions_armwar1d)},
    {"avspd", "avsp", "dead_cps2", "cps2_3p3b", "init_cps2", "ROT0", "Alien vs. Predator (Europe 940520 Phoenix Edition) (bootleg)", regions_avspd, N(regions_avspd)},
    {"dstlku1d", "dstlk", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Darkstalkers: The Night Warriors (USA 940705 Phoenix Edition) (bootleg)", regions_dstlku1d, N(regions_dstlku1d)},
    {"ringdstd", "ringdest", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Ring of Destruction: Slammasters II (Europe 940902 Phoenix Edition) (bootleg)", regions_ringdstd, N(regions_ringdstd)},
    {"ssf2tad", "ssf2t", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II Turbo (Asia 940223 Phoenix Edition) (bootleg)", regions_ssf2tad, N(regions_ssf2tad)},
    {"ssf2xjr1d", "ssf2t", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Super Street Fighter II X: Grand Master Challenge (Japan 940223 Phoenix Edition) (bootleg)", regions_ssf2xjr1d, N(regions_ssf2xjr1d)},
    {"xmcotar1d", "xmcota", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men: Children of the Atom (Europe 950105 Phoenix Edition) (bootleg)", regions_xmcotar1d, N(regions_xmcotar1d)},
    {"mshud", "msh", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes (USA 951024 Phoenix Edition) (bootleg)", regions_mshud, N(regions_mshud)},
    {"cybotsud", "cybots", "dead_cps2", "cybots", "init_cps2", "ROT0", "Cyberbots: Fullmetal Madness (USA 950424 Phoenix Edition) (bootleg)", regions_cybotsud, N(regions_cybotsud)},
    {"cybotsjd", "cybots", "dead_cps2", "cybots", "init_cps2", "ROT0", "Cyberbots: Fullmetal Madness (Japan 950424) (decrypted bootleg)", regions_cybotsjd, N(regions_cybotsjd)},
    {"nwarrud", "nwarr", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Night Warriors: Darkstalkers' Revenge (USA 950406 Phoenix Edition) (bootleg)", regions_nwarrud, N(regions_nwarrud)},
    {"sfad", "sfa", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Alpha: Warriors' Dreams (Europe 950727 Phoenix Edition) (bootleg)", regions_sfad, N(regions_sfad)},
    {"19xxd", "19xx", "dead_cps2", "cps2_2p2b", "init_cps2", "ROT270", "19XX: The War Against Destiny (USA 951207 Phoenix Edition) (bootleg)", regions_19xxd, N(regions_19xxd)},
    {"ddsomud", "ddsom", "dead_cps2", "cps2_4p4b", "init_cps2", "ROT0", "Dungeons & Dragons: Shadow over Mystara (USA 960619 Phoenix Edition) (bootleg)", regions_ddsomud, N(regions_ddsomud)},
    {"gigaman2", "megaman2", "gigaman2", "cps2_2p3b", "init_gigaman2", "ROT0", "Giga Man 2: The Power Fighters (bootleg of Mega Man 2: The Power Fighters)", regions_gigaman2, N(regions_gigaman2)},
    {"megamn2d", "megaman2", "dead_cps2", "cps2_2p3b", "init_cps2", "ROT0", "Mega Man 2: The Power Fighters (USA 960708 Phoenix Edition) (bootleg)", regions_megamn2d, N(regions_megamn2d)},
    {"sfz2ad", "sfa2", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 2 (Asia 960227 Phoenix Edition) (bootleg)", regions_sfz2ad, N(regions_sfz2ad)},
    {"sfz2jd", "sfa2", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 2 (Japan 960227 Phoenix Edition) (bootleg)", regions_sfz2jd, N(regions_sfz2jd)},
    {"spf2td", "spf2t", "dead_cps2", "cps2_2p2b", "init_cps2", "ROT0", "Super Puzzle Fighter II Turbo (USA 960620 Phoenix Edition) (bootleg)", regions_spf2td, N(regions_spf2td)},
    {"spf2xjd", "spf2t", "dead_cps2", "cps2_2p2b", "init_cps2", "ROT0", "Super Puzzle Fighter II X (Japan 960531 Phoenix Edition) (bootleg)", regions_spf2xjd, N(regions_spf2xjd)},
    {"sfz2ald", "sfz2al", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 2 Alpha (Asia 960826 Phoenix Edition) (bootleg)", regions_sfz2ald, N(regions_sfz2ald)},
    {"xmvsfu1d", "xmvsf", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "X-Men Vs. Street Fighter (USA 961004 Phoenix Edition) (bootleg)", regions_xmvsfu1d, N(regions_xmvsfu1d)},
    {"batcird", "batcir", "dead_cps2", "cps2_4p2b", "init_cps2", "ROT0", "Battle Circuit (Europe 970319 Phoenix Edition) (bootleg)", regions_batcird, N(regions_batcird)},
    {"csclub1d", "csclub", "dead_cps2", "cps2_2p3b", "init_cps2", "ROT0", "Capcom Sports Club (Europe 970722 Phoenix Edition) (bootleg)", regions_csclub1d, N(regions_csclub1d)},
    {"mshvsfu1d", "mshvsf", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Super Heroes Vs. Street Fighter (USA 970625 Phoenix Edition) (bootleg)", regions_mshvsfu1d, N(regions_mshvsfu1d)},
    {"sgemfd", "sgemf", "dead_cps2", "cps2_2p3b", "init_cps2", "ROT0", "Super Gem Fighter: Mini Mix (USA 970904 Phoenix Edition) (bootleg)", regions_sgemfd, N(regions_sgemfd)},
    {"vsavd", "vsav", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Savior: The Lord of Vampire (Europe 970519 Phoenix Edition) (bootleg)", regions_vsavd, N(regions_vsavd)},
    {"vhunt2d", "vhunt2", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Hunter 2: Darkstalkers Revenge (Japan 970913 Phoenix Edition) (bootleg)", regions_vhunt2d, N(regions_vhunt2d)},
    {"vsav2d", "vsav2", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Vampire Savior 2: The Lord of Vampire (Japan 970913 Phoenix Edition) (bootleg)", regions_vsav2d, N(regions_vsav2d)},
    {"mvscud", "mvsc", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Marvel Vs. Capcom: Clash of Super Heroes (USA 980123 Phoenix Edition) (bootleg)", regions_mvscud, N(regions_mvscud)},
    {"sfa3ud", "sfa3", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Alpha 3 (USA 980904 Phoenix Edition) (bootleg)", regions_sfa3ud, N(regions_sfa3ud)},
    {"sfz3jr2d", "sfa3", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Street Fighter Zero 3 (Japan 980629 Phoenix Edition) (bootleg)", regions_sfz3jr2d, N(regions_sfz3jr2d)},
    {"gigawingd", "gigawing", "dead_cps2", "cps2_2p2b", "init_cps2", "ROT0", "Giga Wing (USA 990222 Phoenix Edition) (bootleg)", regions_gigawingd, N(regions_gigawingd)},
    {"gigawingjd", "gigawing", "dead_cps2", "cps2_2p2b", "init_cps2", "ROT0", "Giga Wing (Japan 990223 Phoenix Edition) (bootleg)", regions_gigawingjd, N(regions_gigawingjd)},
    {"1944d", "1944", "dead_cps2", "cps2_2p2b", "init_cps2", "ROT0", "1944: The Loop Master (USA 000620 Phoenix Edition) (bootleg)", regions_1944d, N(regions_1944d)},
    {"dimahoud", "dimahoo", "dead_cps2", "cps2_2p3b", "init_cps2", "ROT270", "Dimahoo (USA 000121 Phoenix Edition) (bootleg)", regions_dimahoud, N(regions_dimahoud)},
    {"mmatrixd", "mmatrix", "dead_cps2", "cps2_2p1b", "init_cps2", "ROT0", "Mars Matrix: Hyper Solid Shooting (USA 000412 Phoenix Edition) (bootleg)", regions_mmatrixd, N(regions_mmatrixd)},
    {"progearud", "progear", "dead_cps2", "cps2_2p3b", "init_cps2", "ROT0", "Progear (USA 010117 Phoenix Edition) (bootleg)", regions_progearud, N(regions_progearud)},
    {"progearjd", "progear", "dead_cps2", "cps2_2p3b", "init_cps2", "ROT0", "Progear no Arashi (Japan 010117 Phoenix Edition) (bootleg)", regions_progearjd, N(regions_progearjd)},
    {"progearjbl", "progear", "dead_cps2", "cps2_2p3b", "init_cps2", "ROT0", "Progear no Arashi (Japan 010117) (decrypted bootleg)", regions_progearjbl, N(regions_progearjbl)},
    {"pzloop2jd", "pzloop2", "dead_cps2", "pzloop2", "init_pzloop2", "ROT0", "Puzz Loop 2 (Japan 010226 Phoenix Edition) (bootleg)", regions_pzloop2jd, N(regions_pzloop2jd)},
    {"hsf2d", "hsf2", "dead_cps2", "cps2_2p6b", "init_cps2", "ROT0", "Hyper Street Fighter II: The Anniversary Edition (Asia 040202 Phoenix Edition) (bootleg)", regions_hsf2d, N(regions_hsf2d)},
};
const size_t cps2_game_count = N(cps2_games);
