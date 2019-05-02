#pragma once

#include <string>

namespace bv::Asm::Instruction
{
    const std::string Add = "add {0}, {1}, {2}";
    const std::string AddI = "addi {0}, {1}, {2}";
    const std::string Move = "mv {0}, {1}";
    const std::string LoadAddress = "la {0}, {1}";
    const std::string LoadInstant = "li {0}, {1}";
    const std::string StoreWord = "sw {0}, {1}, {2}";
    const std::string FloatLoadWord = "flw {0}, {1}, {2}";
    const std::string FloatStoreWord = "fsw {0}, {1}, {2}";
    const std::string BranchEqual = "beq {0}, {1}, {2}";
    const std::string BranchGreaterThan = "bgt {0}, {1}, {2}";
    const std::string Jump = "j {0}";
}
