#pragma once

#include <string>

namespace bv::Asm::Enviroment
{
    const std::string Call = "ecall\n";

    const std::string PrintInt = u8"li a0, 1\n";
    const std::string ReadInt = u8"li a0, 5\n";

    const std::string PrintFloat = u8"li a0, 2\n";
    const std::string ReadFloat = u8"li a0, 6\n";

    const std::string PrintChar = u8"li a0, 11\n";
    const std::string ReadChar = u8"li a0, 12\n";

    const std::string PrintString = u8"li a0, 4\n";
    const std::string ReadString = u8"li a0, 8\n";

    const std::string Sbrk = u8"li a0, 9\n";

    const std::string Exit = u8"li a0, 10\n";
}