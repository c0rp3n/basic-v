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
            void Parse(std::vector<Token>*);

        private:
            bool Accept(Lexeme);
            bool Expect(Lexeme);
            void AddToTree();
            void Factor();
            void Term();
            void Expression();
            void Condition();
            void Statement();
            void Block();
            void Program();
            void Error(std::string);

		public:
            std::shared_ptr<ParseTreeNode> tree;
		private:
            std::vector<Token>* tokens;
            std::vector<Token>::iterator tokenIterator;
        };
    }
}
