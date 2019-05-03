#pragma once

#include <string>

namespace bv::Asm::Instruction
{
    const std::string Add = u8"add {0}, {1}, {2}\n";
    const std::string AddI = u8"addi {0}, {1}, {2}\n";
    const std::string Move = u8"mv {0}, {1}\n";
    const std::string LoadAddress = u8"la {0}, {1}\n";
    const std::string LoadInstant = u8"li {0}, {1}\n";
    const std::string StoreWord = u8"sw {0}, {1}, {2}\n";
    const std::string FloatLoadWord = u8"flw {0}, {1}, {2}\n";
    const std::string FloatStoreWord = u8"fsw {0}, {1}, {2}\n";
    const std::string BranchEqual = u8"beq {0}, {1}, {2}\n";
    const std::string BranchGreaterThan = u8"bgt {0}, {1}, {2}\n";
    const std::string BranchLessThan = u8"blt {0}, {1}, {2}\n";
    const std::string Jump = u8"j {0}\n";
}
