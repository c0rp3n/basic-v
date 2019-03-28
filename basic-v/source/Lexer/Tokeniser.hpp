#include <string>
#include <vector>

#include "../Types/Lexeme.hpp"
#include "../Types/Token.hpp"


namespace bv
{
    namespace Lexer
    {
        class Tokeniser
        {
        public:
            static void TokeniseLines(std::vector<std::string>* lines, int lineNumber, std::vector<bv::Token> *tokens);

            static void TokeniseLine(std::string line, int lineNumber, std::vector<bv::Token> *tokens);
        };
    }
}
