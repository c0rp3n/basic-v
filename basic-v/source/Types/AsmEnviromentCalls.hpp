#pragma once

#include <string>

namespace bv::Asm::Enviroment
{
	const std::string Call = "ecall\n";

	const std::string PrintInt[2] = 
	{
		u8"li a0, 1\n",
		u8"li a1, {0}\n"
	};
	const std::string ReadInt = u8"li a0, 5\n";

	const std::string PrintFloat[2] = 
	{
		u8"li a0, 2\n",
		u8"flw fa0, {0}, t0\n"
	};
	const std::string ReadFloat = u8"li a0, 6\n";

	const std::string PrintChar[2] = 
	{
		u8"li a0, 11\n",
		u8"li a1, {0}\n"
	};
	const std::string ReadChar = u8"li a0, 12\n";

	const std::string PrintString[2] = 
	{
		u8"li a0, 4\n",
		u8"li a1, {0}\n"
	};
	const std::string ReadString[3] =
	{
		u8"li a0, 8\n",
		u8"li a1, {0}\n",	// buffer
		u8"li a2, {0}\n"	// length
	};

	const std::string Sbrk[2] =
	{
		u8"li a0, 9\n",
		u8"li a1, {0}\n" // number of bytes
	};

	const std::string Exit = u8"li a0, 10\n";
}