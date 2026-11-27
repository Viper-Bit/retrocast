// Standalone checker: a 20-byte key followed by program bytes on stdin.
#include "cps2crypt.h"

#include <iostream>
#include <iterator>
#include <vector>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

int main()
{
#ifdef _WIN32
    _setmode(_fileno(stdin), _O_BINARY);
    _setmode(_fileno(stdout), _O_BINARY);
#endif
    const std::vector<uint8_t> input(std::istreambuf_iterator<char>(std::cin), {});
    constexpr size_t key_size = 20;
    if (input.size() <= key_size || input.size() > key_size + 0x1000000 || input.size() % 2) {
        std::cerr << "Expected a 20-byte key and an even-sized program\n";
        return 1;
    }
    std::vector<uint16_t> rom((input.size() - key_size) / 2), opcodes(rom.size());
    for (size_t i = 0; i < rom.size(); ++i)
        rom[i] = uint16_t(input[key_size + 2 * i] << 8) | input[key_size + 2 * i + 1];
    cps2_decrypt(rom.data(), opcodes.data(), int(rom.size() * 2), input.data());
    for (uint16_t word : opcodes) {
        std::cout.put(char(word >> 8));
        std::cout.put(char(word));
    }
    return !std::cout;
}
