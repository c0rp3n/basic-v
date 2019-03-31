#pragma once

#include <vector>

#include "../Types/Lexeme.hpp"
#include "../Types/Token.hpp"
#include "../Types/PTree.hpp"

namespace bv
{
	namespace Parser
	{
		class RecursiveDescent
		{
		public:
			static void Parse(std::vector<Token>*);

		private:
			static bool accept(Lexeme);
			static bool expect(Lexeme);
			static void factor();
			static void term();
			static void expression();
			static void condition();
			static void statement();
			static void block();
			static void program();
			static void error(std::string);
			static bv::PTree parseTree;
			static std::vector<Token>::iterator tokenIterator;
		};
	}
}
