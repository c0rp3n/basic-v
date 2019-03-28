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
		bool imutable;
		std::string value;

		DataEntry()
		{
			this->identifier = "";
			this->type = Type::None;
			this->imutable = true;
			this->value = "";
		}

		DataEntry(std::string identifier, Type type, bool imutable, std::string value)
		{
			this->identifier = identifier;
			this->type = type;
			this->imutable = imutable;
			this->value = value;
		}
	};
}
