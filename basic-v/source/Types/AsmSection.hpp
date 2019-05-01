#pragma once

#include <string>

namespace bv::Asm
{
	const std::string main = u8"main";

	const uint8_t symbol_delimiter = u8':';

	const std::string symbol_global = u8".globl";
	const std::string symbol_local = u8".local";

	const std::string section = u8".section";
	const std::string section_ro_data = u8".rodata";
	const std::string section_data = u8".data";
	const std::string section_bss = u8".bss";

	const std::string identifier = u8".ident";

	const std::string data_string = u8".string";
	const std::string data_int8 = u8".byte";
	const std::string data_int16 = u8".2byte";
	const std::string data_int32 = u8".4byte";
	const std::string data_int64 = u8".8byte";
	const std::string data_int_word = u8".word";
	const std::string data_real = u8".float";

	const std::string zero = u8".zero";
}
