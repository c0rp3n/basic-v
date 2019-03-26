#pragma once

#include <vector>

#include "../Types/Lexeme.hpp"
#include "../Types/Token.hpp"

namespace bv
{
	namespace Parser
	{
		class RecursiveDescent
		{
		public:
			void Parse(std::vector<Token>* tokens);

		private:

		};
	}
}
