#pragma once

#include <string>

namespace bv::Asm::Section
{
	const std::string main = u8"main";

	const uint8_t symbol_delimiter = u8':';

	const std::string symbol_global = u8".globl";
	const std::string symbol_local = u8".local";

	const std::string section = u8".section";
    const std::string text = u8".text";
	const std::string section_ro_data = u8".rodata";
	const std::string section_data = u8".data";
	const std::string section_bss = u8".bss";
}
