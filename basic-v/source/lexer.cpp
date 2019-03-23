#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "IO/FileReader.hpp"
#include "Types/Lexeme.hpp"
#include "Types/Token.hpp"

std::string::iterator iter;
std::vector<bv::Token> tokens;

void generateTokens(std::string line, int lineNumber)
{
	iter = line.begin();
	char character;

	while (iter < line.end())
	{
		character = *iter;
		iter++;



		//If a keywors or an identifier...
		if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || (character == '_')) {
			std::string value(1, character);
			while (iter != line.end() && ((*iter >= 'a' && *iter <= 'z') || (*iter >= 'A' && *iter <= 'Z') || (*iter >= '0' && *iter <= '9') || (*iter == '_'))) {
				value.append(1, *iter);
				iter++;
			}

			// Look up whether or not the value matched predefined keywords.
			// If so, add the keyword to the token vector
			// If not, it is a custom identifier (see else)
			if (value == "false")
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::False));
			}
			else if (value == "true")
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::True));
			}
			else if (value == "if")
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::If));
			}
			else if (value == "then")
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Then));
			}
			else if (value == "case")
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Case));
			}
			else if (value == "of")
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Of));
			}
			else if (value == "when")
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::When));
			}
			else if (value == "otherwise")
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Otherwise));
			}
			else if (value == "for")
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::For));
			}
			else if (value == "to")
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::To));
			}
			else if (value == "next")
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Next));
			}
			else if (value == "repeat")
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Repeat));
			}
			else if (value == "until")
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Until));
			}
			else if (value == "while")
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::While));
			}
			else if (value == "endwhile")
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::EndWhile));
			}
			else if (value == "end")
			{
				//If the keyword 'end' matches, look ahead another keyword to see if we need to match 'end if' or 'end case'

				std::string::iterator tempIter = iter;
				std::string value2 = "";
				if (*tempIter++ == ' ')
				{
					while (tempIter != line.end() && ((*tempIter >= 'a' && *tempIter <= 'z') || (*tempIter >= 'A' && *tempIter <= 'Z'))) {
						value2.append(1, *tempIter);
						tempIter++;
					}
				}

				if (value2 == "if")
				{
					iter = tempIter;
					tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::EndIf));
				}
				else if (value2 == "case")
				{
					iter = tempIter;
					tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::EndCase));
				}
				else
				{
					tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::End));
				}
			}
			else
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Identifier, value));
			}


		}

		//If an integer...
		else if ((character >= '0' && character <= '9') || (character == '-' && *iter >= '0' && *iter <= '9')) {
			int value = (character == '-') ? 0 - (character - '0') : character - '0';
			while (iter != line.end() && *iter >= '0' && *iter <= '9') {
				value = value * 10 + *iter++ - '0';
			}
			tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Integer, std::to_string(value)));
		}

		//If a string literal...
		else if (character == '"') {
			std::string value(1, *iter++);
			while (iter != line.end() && *iter != '"') {
				value.append(1, *iter++);
			}
			iter++;
			tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::String, value));
		}

		//If '=' or '=='...
		else if (character == '=')
		{
			if (iter != line.end() && *iter++ == '=')
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Equal));
			}
			else
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Assign));
			}
		}

		//If '+'...
		else if (character == '+')
		{
			tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Addition));
		}

		//If '-'...
		else if (character == '-')
		{
			tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Subtraction));
		}

		//If '*'...
		else if (character == '*')
		{
			tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Multiply));
		}

		//If '/'...
		else if (character == '/')
		{
			tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Divide));
		}

		//If '<', '<>', or '<='...
		else if (character == '<')
		{
			if (iter != line.end() && *iter == '>')
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::NotEqual));
			}
			else if (iter != line.end() && *iter == '=')
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::LessThanOrEqual));
			}
			else
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::LessThan));
			}
			iter++;
		}

		//If '>' or '>='
		else if (character == '>')
		{
			if (iter != line.end() && *iter++ == '=')
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::GreaterThanOrEqual));
			}
			else
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::GreaterThan));
			}
		}

		//If '!'
		else if (character == '!')
		{
			tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Not));
		}

		//If '('...
		else if (character == '(')
		{
			tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::OpenBracket));
		}

		//If ')'...
		else if (character == ')')
		{
			tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::CloseBracket));
		}

		//If ':'...
		else if (character == ':')
		{
			tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Colon));
		}
	}
}

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
				// help text stuff here
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

	filepath = "C:\\Users\\Sam Conran\\Programming\\C++\\basic-v\\basic-v-x64\\Debug\\example.txt";

	std::vector<std::string> lines = bv::IO::FileReader::ReadLines(filepath);
	if (lines.size() < 1)
	{
		return 0;
	}

	int lineNumber = 0;
	for (std::string line : lines)
	{
		lineNumber++;
		generateTokens(line, lineNumber);
	}

	system("pause");


	/*
	<===== Commenting out for now, just for simplicity of testing the rules =====>

	int threadCount = std::thread::hardware_concurrency();
	int linesPerThread = lines.size() / threadCount;
	std::vector<std::thread> threads;
	threads.reserve(threadCount);
	for (int i = 0; i < threadCount; i++)
	{
		threads.push_back(std::thread());
	}

	for (std::thread &t : threads)
	{
		t.join();
	}

	*/


	return 0;
}



