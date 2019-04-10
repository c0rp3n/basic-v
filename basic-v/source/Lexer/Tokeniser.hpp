#include <memory>
#include <string>
#include <vector>

#include "../Types/Lexeme.hpp"
#include "../Types/Token.hpp"


namespace bv::Lexer
{
    class Tokeniser
    {
    public:
        static void TokeniseLines(std::vector<std::string>::iterator start, std::vector<std::string>::iterator end, uint64_t startLine, std::shared_ptr<std::vector<bv::Token>> tokens);

        static void TokeniseLine(std::string line, uint64_t lineNumber, std::shared_ptr<std::vector<bv::Token>> tokens);
    };
}
