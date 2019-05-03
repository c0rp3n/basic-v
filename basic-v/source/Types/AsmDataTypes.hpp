#pragma once

#include <string>

namespace bv::Asm::DataTypes
{
    const std::string identifier = u8".ident";

    const std::string string = u8".string";
    const std::string int8 = u8".byte";
    const std::string int16 = u8".2byte";
    const std::string int32 = u8".4byte";
    const std::string int64 = u8".8byte";
    const std::string int_word = u8".word";
    const std::string real = u8".float";

    const std::string zero = u8".zero";
}
