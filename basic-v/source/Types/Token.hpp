#pragma once

#include <cstdint>
#include <string>

#include "TokenType.hpp"

namespace bv
{
	struct Token
	{
		uint64_t line;
		uint64_t position;
		Lexeme token;
		std::string value;
	};
}
