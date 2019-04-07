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
            bool accept(Lexeme);
            bool expect(Lexeme);
            void addToTree();
            void factor();
            void term();
            void expression();
            void condition();
            void statement();
            void block();
            void program();
            void error(std::string);
            std::shared_ptr<ParseTreeNode> tree;
            std::vector<Token>* tokens;
            std::vector<Token>::iterator tokenIterator;
        };
    }
}
