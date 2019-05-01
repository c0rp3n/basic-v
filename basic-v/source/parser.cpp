#include <iostream>
#include <vector>

#include "Parser\RecursiveDescent.hpp"
#include "Types\Token.hpp"
#include "Types\Lexeme.hpp"

int main(int argc, char* argv[])
{
	std::string filepath;
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
			else if (argv[i][1] == 'p')
			{
				if (i + 1 < argc)
				{
					filepath = argv[++i];
				}
			}
		}
	}

	if (filepath == "")
	{
		return 0;
	}

    std::vector<bv::Token> tokens;
	bv::Token::Parse(filepath , &tokens);

    bv::Parser::RecursiveDescent parser;
    parser.Parse(&tokens);

}
