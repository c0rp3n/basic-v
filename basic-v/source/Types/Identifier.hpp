#pragma once

#include <cstdint>
#include <string>

#include "Token.hpp"

namespace bv::Types
{
	struct Identifier
	{
		uint64_t line;
		uint64_t position;
		Token token;
		std::string value;
	};
}
