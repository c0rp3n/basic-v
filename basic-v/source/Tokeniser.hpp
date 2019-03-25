#include <string>
#include <vector>

#include "Types/Lexeme.hpp"
#include "Types/Token.hpp"

class Tokeniser
{
private:
	std::string::iterator iter;

public:
	std::vector<bv::Token> tokens;

	void TokeniseLine(std::string line, int lineNumber)
	{
		iter = line.begin();
		char character;

		while (iter < line.end())
		{
			character = *iter;
			int position = iter - line.begin();
			iter++;

			//If a keywors or an identifier...
			if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || (character == '_'))
			{
				std::string value(1, character);
				while (iter != line.end() && ((*iter >= 'a' && *iter <= 'z') || (*iter >= 'A' && *iter <= 'Z') || (*iter >= '0' && *iter <= '9') || (*iter == '_')))
				{
					value.append(1, *iter++);
				}

				// Look up whether or not the value matched predefined keywords.
				// If so, add the keyword to the token vector
				// If not, it is a custom identifier (see else)
				if (value == "false")
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::False));
				}
				else if (value == "true")
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::True));
				}
				else if (value == "if")
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::If));
				}
				else if (value == "then")
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Then));
				}
				else if (value == "case")
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Case));
				}
				else if (value == "of")
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Of));
				}
				else if (value == "when")
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::When));
				}
				else if (value == "otherwise")
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Otherwise));
				}
				else if (value == "for")
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::For));
				}
				else if (value == "to")
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::To));
				}
				else if (value == "next")
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Next));
				}
				else if (value == "repeat")
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Repeat));
				}
				else if (value == "until")
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Until));
				}
				else if (value == "while")
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::While));
				}
				else if (value == "endwhile")
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::EndWhile));
				}
				else if (value == "end")
				{
					//If the keyword 'end' matches, look ahead another keyword to see if we need to match 'end if' or 'end case'

					std::string::iterator tempIter = iter;
					std::string value2 = "";
					if (*tempIter++ == ' ')
					{
						while (tempIter != line.end() && ((*tempIter >= 'a' && *tempIter <= 'z') || (*tempIter >= 'A' && *tempIter <= 'Z')))
						{
							value2.append(1, *tempIter++);
						}
					}

					if (value2 == "if")
					{
						iter = tempIter;
						tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::EndIf));
					}
					else if (value2 == "case")
					{
						iter = tempIter;
						tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::EndCase));
					}
					else
					{
						tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::End));
					}
				}
				else
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Identifier, value));
				}


			}

			//If an integer or a real number...
			else if ((character >= '0' && character <= '9') || (character == '-' && *iter >= '0' && *iter <= '9'))
			{
				std::string value(1, character);

				while (iter != line.end() && *iter >= '0' && *iter <= '9' || (iter != line.end() && *iter == '.' && *(iter + 1) >= '0' && *(iter + 1) <= '9'))
				{
					value.append(1, *iter++);
				}

				//If the number contains a '.', it's a real. Otherwise, an integer.
				if (value.find('.') != std::string::npos)
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Real, value));
				}
				else
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Integer, value));
				}
			}

			//If a string literal...
			else if (character == '"')
			{
				std::string value(1, *iter++);
				while (iter != line.end() && *iter != '"')
				{
					value.append(1, *iter++);
				}
				iter++;
				tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::String, value));
			}

			//If '=' or '=='...
			else if (character == '=')
			{
				if (iter != line.end() && *iter++ == '=')
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Equal));
				}
				else
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Assign));
				}
			}

			//If '+'...
			else if (character == '+')
			{
				tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Addition));
			}

			//If '-'...
			else if (character == '-')
			{
				tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Subtraction));
			}

			//If '*'...
			else if (character == '*')
			{
				tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Multiply));
			}

			//If '/'...
			else if (character == '/')
			{
				tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Divide));
			}

			//If '<', '<>', or '<='...
			else if (character == '<')
			{
				if (iter != line.end() && *iter == '>')
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::NotEqual));
				}
				else if (iter != line.end() && *iter == '=')
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::LessThanOrEqual));
				}
				else
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::LessThan));
				}
				iter++;
			}

			//If '>' or '>='
			else if (character == '>')
			{
				if (iter != line.end() && *iter++ == '=')
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::GreaterThanOrEqual));
				}
				else
				{
					tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::GreaterThan));
				}
			}

			//If '!'
			else if (character == '!')
			{
				tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Not));
			}

			//If '('...
			else if (character == '(')
			{
				tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::OpenBracket));
			}

			//If ')'...
			else if (character == ')')
			{
				tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::CloseBracket));
			}

			//If ':'...
			else if (character == ':')
			{
				tokens.push_back(bv::Token(lineNumber, position, bv::Lexeme::Colon));
			}
		}
	}
};