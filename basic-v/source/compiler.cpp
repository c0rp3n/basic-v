#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "Compiler/CodeGenerator.hpp"
#include "Types/Token.hpp"
#include "Types/Lexeme.hpp"
#include "Types/PNode.hpp"

int main(int argc, char* argv[])
{
    std::string tokenpath;
    std::string treepath;
    std::string outputpath;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == 0)
        {
            continue;
        }

        if (argv[i][0] == '-' && argv[i][1] != '-')
        {
            if (argv[i][1] == 'h')
            {
                // todo: help text stuff here
            }
            else if (argv[i][1] == 't')
            {
                if (i + 1 < argc)
                {
                    tokenpath = argv[++i];
                }
            }
            else if (argv[i][1] == 'p')
            {
                if (i + 1 < argc)
                {
                    treepath = argv[++i];
                }
            }
            else if (argv[i][1] == 'o')
            {
                if (i + 1 < argc)
                {
                    outputpath = argv[++i];
                }
            }
        }
    }

    std::vector<bv::Token> tokens;
    {
        if (tokenpath == "")
        {
            return 1;
        }

        if (!bv::Token::Parse(tokenpath, &tokens))
        {
            // eererererereererer
            return 1;
        }
    }

    std::vector<bv::PNode> parsetree;
    {
        if (treepath == "")
        {
            return 1;
        }

        if (!bv::PNode::Parse(treepath, &parsetree))
        {
            // eererererereererer
            return 1;
        }
    }

    bv::Compiler::CodeGenerator::Parse(&tokens, &parsetree);
}
