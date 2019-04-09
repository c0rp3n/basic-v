#include <string>
#include <vector>

#include "../Types/Lexeme.hpp"
#include "../Types/Token.hpp"


namespace bv::Lexer
{
    class Tokeniser
    {
    public:
        static void TokeniseLines(std::vector<std::string>::iterator start, std::vector<std::string>::iterator end, int startLine, std::vector<bv::Token>* tokens);

        static void TokeniseLine(std::string line, int lineNumber, std::vector<bv::Token>* tokens);
    };
}
