#include "RecursiveDescent.hpp"

#include <iostream>

void bv::Parser::RecursiveDescent::Parse(std::vector<Token>* tokens)
{
	tokenIterator = tokens->begin();
	program();
}

bool bv::Parser::RecursiveDescent::accept(bv::Lexeme l)
{
	if (tokenIterator->token == l) {
		tokenIterator++;
		return true;
	}
	return false;
}

bool bv::Parser::RecursiveDescent::expect(bv::Lexeme l)
{
	if (accept(l))
		return true;
	error("expect: unexpected symbol");
	return false;
}

void bv::Parser::RecursiveDescent::factor()
{
	if (accept(bv::Lexeme::Identifier) || accept(bv::Lexeme::Real) || accept(bv::Lexeme::Integer))
	{
		;
	}
	else if (accept(bv::Lexeme::OpenBracket))
	{
		expression();
		expect(bv::Lexeme::CloseBracket);
	}
	else {
		error("factor: syntax error");
		tokenIterator++;
	}
}

void bv::Parser::RecursiveDescent::term()
{
	factor();
	while (tokenIterator->token == bv::Lexeme::Multiply || tokenIterator->token == bv::Lexeme::Divide)
	{
		tokenIterator++;
		factor();
	}
}

void bv::Parser::RecursiveDescent::expression()
{
	if (accept(bv::Lexeme::Addition) || accept(bv::Lexeme::Subtraction))
	{
		;
	}
	term();
	while (accept(bv::Lexeme::Addition) || accept(bv::Lexeme::Subtraction))
	{
		term();
	}
}

void bv::Parser::RecursiveDescent::condition()
{
	if (accept(bv::Lexeme::Not))
	{
		factor();
	}
	else
	{
		expression();
		if (accept(bv::Lexeme::Equal) || accept(bv::Lexeme::NotEqual) || accept(bv::Lexeme::LessThan) || accept(bv::Lexeme::LessThanOrEqual) || accept(bv::Lexeme::GreaterThan) || accept(bv::Lexeme::GreaterThanOrEqual))
		{
			expression();
		}
		else
		{
			error("condition: invalid operator");
		}
	}
}

void bv::Parser::RecursiveDescent::statement()
{
	if (accept(bv::Lexeme::Identifier))
	{
		expect(bv::Lexeme::Assign);
		if (!accept(bv::Lexeme::String))
		{
			expression();
		}
	}
	else if (accept(bv::Lexeme::If))
	{
		condition();
		expect(bv::Lexeme::Then);
		if (accept(bv::Lexeme::NewLine))
		{
			block();
			expect(bv::Lexeme::End);
			expect(bv::Lexeme::If);
		}
		else
		{
			statement();
		}
		
	}
	else if (accept(bv::Lexeme::Case))
	{
		expect(bv::Lexeme::Identifier);
		expect(bv::Lexeme::Of);
		expect(bv::Lexeme::NewLine);
		while (accept(bv::Lexeme::When))
		{
			if (accept(bv::Lexeme::Integer) || accept(bv::Lexeme::Real) || accept(bv::Lexeme::String))
			{
				expect(bv::Lexeme::Colon);
				block();
			}
			else
			{
				error("Statement: No data given to When statement");
			}
		}
		if (accept(bv::Lexeme::Otherwise))
		{
			expect(bv::Lexeme::Colon);
			block();
		}
		expect(bv::Lexeme::End);
		expect(bv::Lexeme::Case);
	}
	else if (accept(bv::Lexeme::For))
	{
		expect(bv::Lexeme::Identifier);
		expect(bv::Lexeme::Assign);
		if (accept(bv::Lexeme::Identifier) || accept(bv::Lexeme::Integer))
		{
			expect(bv::Lexeme::To);
			if(accept(bv::Lexeme::Identifier) || accept(bv::Lexeme::Integer))
			{
				if (accept(bv::Lexeme::NewLine))
				{
					block();
					expect(bv::Lexeme::Next);
					expect(bv::Lexeme::Identifier);
				}
				else
				{
					statement();
				}
			}
			else
			{
				error("Invalid range end for FOR loop...");
			}
		}
		else
		{
			error("Invalid range beginning for FOR loop...");
		}
	}
	else if (accept(bv::Lexeme::While))
	{
		condition();
		expect(bv::Lexeme::Do);
		if (accept(bv::Lexeme::NewLine))
		{
			block();
			expect(bv::Lexeme::End);
			expect(bv::Lexeme::While);
		}
		else
		{
			statement();
		}
	}
	else
	{
		error("Statement: Syntax Error");
	}
}

void bv::Parser::RecursiveDescent::block()
{
	do
	{
		if (accept(bv::Lexeme::Data))
		{

			do
			{
				expect(bv::Lexeme::Identifier);
				expect(bv::Lexeme::Assign);
				if (accept(bv::Lexeme::Identifier) || accept(bv::Lexeme::Integer))
				{
					;
				}
				else
				{
					error("Invalid data type...");
				}
			} while (accept(bv::Lexeme::Comma));
		}
		else if (accept(bv::Lexeme::Dim))
		{
			do
			{
				expect(bv::Lexeme::Identifier);
				if (accept(bv::Lexeme::Assign))
				{
					if (accept(bv::Lexeme::Identifier) || accept(bv::Lexeme::Integer))
					{
						;
					}
					else
					{
						error("Invalid data type...");
					}
				}
			} while (accept(bv::Lexeme::Comma));
		}
		else
		{
			statement();
		}
	} while (accept(bv::Lexeme::NewLine));
}

void bv::Parser::RecursiveDescent::program()
{
	while (accept(bv::Lexeme::Def))
	{
		expect(bv::Lexeme::Sub);
		expect(bv::Lexeme::Identifier);
		expect(bv::Lexeme::OpenBracket);
		if (accept(bv::Lexeme::Identifier))
		{
			while (accept(bv::Lexeme::Comma))
			{
				expect(bv::Lexeme::Identifier);
			}
		}
		expect(bv::Lexeme::CloseBracket);
		expect(bv::Lexeme::NewLine);
	}
	block();
	while (accept(bv::Lexeme::Sub))
	{
		expect(bv::Lexeme::Identifier);
		expect(bv::Lexeme::OpenBracket);
		if (accept(bv::Lexeme::Identifier))
		{
			while (accept(bv::Lexeme::Comma))
			{
				expect(bv::Lexeme::Identifier);
			}
		}
		expect(bv::Lexeme::CloseBracket);
		expect(bv::Lexeme::NewLine);
		block();
		expect(bv::Lexeme::End);
		expect(bv::Lexeme::Sub);
		expect(bv::Lexeme::NewLine);
	}
}

void bv::Parser::RecursiveDescent::error(std::string s)
{
	std::cout << s;
}