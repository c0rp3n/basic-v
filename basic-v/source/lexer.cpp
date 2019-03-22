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
		//If an identifier...
		if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || (character == '_')) {
			std::string value(1, character);
			while (iter != line.end() && ((*iter >= 'a' && *iter <= 'z') || (*iter >= 'A' && *iter <= 'Z') || (*iter >= '0' && *iter <= '9') || (*iter == '_'))) {
				value.append(1, *iter);
				iter++;
			}
			tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Identifier, value));
			continue;
		}

		//If an integer...
		else if (character >= '0' && character <= '9') {
			int value = character - '0';
			while (iter != line.end() && *iter >= '0' && *iter <= '9') {
				value = value * 10 + *iter++ - '0';
			}
			tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Integer, std::to_string(value)));
			continue;
		}

		//If a string literal...
		else if (character == '"') {
			std::string value(1, *iter++);
			while (iter != line.end() && *iter != '"') {
				value.append(1, *iter++);
			}
			iter++;
			tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::String, value));
			continue;
		}

		//If '=' or '=='...
		else if (character == '=')
		{
			if (iter != line.end() && *(++iter) == '=')
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Equal));
				iter++;
			}
			else
			{
				tokens.push_back(bv::Token(lineNumber, 0, bv::Lexeme::Assign));
			}
			continue;
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



