# CPS-2 opcode decryption

The C decryptor takes program words and a verified 20-byte key and writes
a separate opcode buffer. The machine can continue to read the original
program words for data accesses.

Build the standalone checker with a C compiler:

```sh
cc -std=c11 -O2 systems/cps2/runtime/decrypt_main.c systems/cps2/runtime/cps2crypt.c -o cps2-decrypt
```

The checker reads the key followed by big-endian program bytes on standard
input and writes big-endian opcode bytes to standard output.
