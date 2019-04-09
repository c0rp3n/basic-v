#include <iostream>
#include <vector>

#include "Parser\RecursiveDescent.hpp"
#include "Types\Token.hpp"
#include "Types\Lexeme.hpp"

int main(int argc, char* argv[])
{

    std::vector<bv::Token> tokens;

    bv::Parser::RecursiveDescent parser;
    parser.Parse(&tokens);

}
