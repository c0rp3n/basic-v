#pragma once

#define TAB "    "

#include <map>
#include <string>
#include <vector>

#include "../Types/AsmEnviromentCalls.hpp"
#include "../Types/AsmSection.hpp"
#include "../Types/Lexeme.hpp"
#include "../Types/Token.hpp"

namespace bv::Compiler
{
	class CodeGenerator
	{
		static void Parse(std::vector<void*>* tree)
		{
			std::vector<std::string> text;
			std::vector<std::string> data;
			std::vector<std::string> rodata;

			std::map<std::string, bv::Lexeme> idTypes;

			while (true)
			{
				if (true) // if
				{

				}

				if (true) // dim
				{
					std::string id;
					std::string type;
					std::string value;

					id = token.value; // next node

					if (token.token == Lexeme::Int)
					{
						type = bv::Asm::data_int_word;
						value = token.value;
					}
					else if (token.token == Lexeme::Real)
					{
						type = bv::Asm::data_real;
						value = token.value;
					}
					else if (token.token == Lexeme::String)
					{
						type = bv::Asm::data_string;
						value = "\"" + token.value + "\"";
					}

					data.push_back(TAB + id + ": " + type + " " + value + "\n");
				}

				if (true) // data
				{
					std::string id;
					std::string type;
					std::string value;

					id = token.value; // next node

					if (token.token == Lexeme::Int)
					{
						type = bv::Asm::data_int_word;
						value = token.value;
					}
					else if (token.token == Lexeme::Real)
					{
						type = bv::Asm::data_real;
						value = token.value;
					}
					else if (token.token == Lexeme::String)
					{
						type = bv::Asm::data_string;
						value = "\"" + token.value + "\"";
					}

					rodata.push_back(TAB + id + ": " + type + " " + value + "\n");
				}
			}
		}
	};
}
