#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace bv
{
	struct FunctionEntry
	{
		std::string identifier;
		std::vector<std::string> arguments;

		FunctionEntry()
		{
			this->identifier = "";
			this->arguments = std::vector<std::string>();
		}

		FunctionEntry(std::string identifier, std::vector<std::string> arguments)
		{
			this->identifier = identifier;
			this->arguments = arguments;
		}
	};
}

