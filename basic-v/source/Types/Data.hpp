#pragma once

#include <cstdint>
#include <string>

namespace bv
{
	struct DataEntry
	{
		enum struct Type : uint64_t
		{
			None,
			Integer,
			Real,
			String,
		};

		std::string identifier;
		Type type;
		std::string value;

		DataEntry()
		{
			this->identifier = "";
			this->type = Type::None;
			this->value = "";
		}

		DataEntry(std::string identifier, Type type, std::string value)
		{
			this->identifier = identifier;
			this->type = type;
			this->value = value;
		}
	};
}
