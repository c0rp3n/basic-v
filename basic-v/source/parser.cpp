#include <iostream>
#include <vector>

#include "Parser\RecursiveDescent.hpp"
#include "Types\Token.hpp"
#include "Types\Lexeme.hpp"

int main(int argc, char* argv[])
{
	/*
	std::vector<bv::Token> tokens =
	{
		bv::Token(0, 0, bv::Lexeme::Identifier, "var"),
		bv::Token(0, 0, bv::Lexeme::Assign),
		bv::Token(0, 0, bv::Lexeme::OpenBracket),
		bv::Token(0, 0, bv::Lexeme::Integer, "5"),
		bv::Token(0, 0, bv::Lexeme::Addition),
		bv::Token(0, 0, bv::Lexeme::Integer, "3"),
		bv::Token(0, 0, bv::Lexeme::CloseBracket),
		bv::Token(0, 0, bv::Lexeme::Multiply),
		bv::Token(0, 0, bv::Lexeme::Integer, "4")
	};

	std::vector<bv::Token> tokens =
	{
		bv::Token(0, 0, bv::Lexeme::If),
		bv::Token(0, 0, bv::Lexeme::Identifier, "variable"),
		bv::Token(0, 0, bv::Lexeme::NotEqual),
		bv::Token(0, 0, bv::Lexeme::Integer, "5"),
		bv::Token(0, 0, bv::Lexeme::Then),
		bv::Token(0, 0, bv::Lexeme::Identifier, "someVar"),
		bv::Token(0, 0, bv::Lexeme::Assign),
		bv::Token(0, 0, bv::Lexeme::Integer, "4")
	};
	*/

	//case var of
	//	when 0: print "Values: 0"

	std::vector<bv::Token> tokens =
	{
		bv::Token(0, 0, bv::Lexeme::Case),
		bv::Token(0, 0, bv::Lexeme::Identifier, "3"),
		bv::Token(0, 0, bv::Lexeme::Of),
		bv::Token(0, 0, bv::Lexeme::NewLine),
		bv::Token(0, 0, bv::Lexeme::When),
		bv::Token(0, 0, bv::Lexeme::Integer, "5"),
		bv::Token(0, 0, bv::Lexeme::Colon),
		bv::Token(0, 0, bv::Lexeme::Identifier, "var"),
		bv::Token(0, 0, bv::Lexeme::Assign),
		bv::Token(0, 0, bv::Lexeme::Integer, "5"),
		bv::Token(0, 0, bv::Lexeme::Otherwise),
		bv::Token(0, 0, bv::Lexeme::Colon),
		bv::Token(0, 0, bv::Lexeme::Identifier, "someVar"),
		bv::Token(0, 0, bv::Lexeme::Assign),
		bv::Token(0, 0, bv::Lexeme::Integer, "4"),
		bv::Token(0, 0, bv::Lexeme::End),
		bv::Token(0, 0, bv::Lexeme::Case)
	};

	bv::Parser::RecursiveDescent a;
	a.Parse(&tokens);
	system("pause");
}
