# CPS-2 verification log

| Phase | Evidence | Coverage |
| --- | --- | --- |
| P1 | MAME 0.289 opcode hashes matched for `ssf2` and `ssf2u`. The C loader assembled 323 catalog sets. Region CRCs matched the provisional loader for `ssf2`, `ssf2u`, `progear`, and `vsav2`. | [Decryptor](https://github.com/Viper-Bit/retrocast/pull/89), [loader](https://github.com/Viper-Bit/retrocast/pull/90) |
| P2 | `ssf2` and `ssf2u` reached a playable round using scripted controls. One title-sequence frame per set matched MAME 0.289 after alignment. Continuous frame comparison remains open. | [Machine and video](https://github.com/Viper-Bit/retrocast/pull/91) |
| P3 | Both sets produced stereo gameplay output. The first 756 `ssf2` QSound bus writes matched MAME 0.289. First audible output was within 5 ms. Later writes diverged and the captures used different rates. | [QSound](https://github.com/Viper-Bit/retrocast/pull/92) |
| P4 | The bounded headless probe requires changing, non-uniform video and a running 68000. | [Compatibility list](compatibility.md) |
