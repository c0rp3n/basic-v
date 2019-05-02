#include "Tokeniser.hpp"

#include <iostream>

using namespace bv::Lexer;

void bv::Lexer::Tokeniser::TokeniseLines(std::vector<std::string>::iterator start, std::vector<std::string>::iterator end, uint64_t startLine, std::vector<bv::Token>* tokens)
{
    while (start != end)
    {
        bv::Lexer::Tokeniser::TokeniseLine((*start), startLine, tokens);
        start++;
		startLine++;
    }
}

void bv::Lexer::Tokeniser::TokeniseLine(std::string line, uint64_t lineNumber, std::vector<bv::Token>* tokens)
{
    std::string::iterator iter = line.begin();
    char character;

    while (iter < line.end())
    {
        character = *iter;
        int64_t position = iter - line.begin();
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
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::False));
            }
            else if (value == "true")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::True));
            }
            else if (value == "if")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::If));
            }
            else if (value == "then")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Then));
            }
            else if (value == "case")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Case));
            }
            else if (value == "of")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Of));
            }
            else if (value == "when")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::When));
            }
            else if (value == "otherwise")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Otherwise));
            }
            else if (value == "for")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::For));
            }
            else if (value == "to")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::To));
            }
            else if (value == "next")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Next));
            }
            else if (value == "repeat")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Repeat));
            }
            else if (value == "until")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Until));
            }
            else if (value == "while")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::While));
            }
            else if (value == "do")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Do));
            }
            else if (value == "end")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::End));
            }
            else if (value == "dim")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Dim));
            }
            else if (value == "data")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Data));
            }
            else if (value == "def")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Def));
            }
            else if (value == "sub")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Sub));
            }
            else if (value == "call")
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Call));
            }
            else
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Identifier, value));
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
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Real, value));
            }
            else
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Integer, value));
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
            tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::String, value));
        }

        //If '=' or '=='...
        else if (character == '=')
        {
            if (iter != line.end() && *iter++ == '=')
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Equal));
            }
            else
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Assign));
            }
        }

        //If '+'...
        else if (character == '+')
        {
            tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Addition));
        }

        //If '-'...
        else if (character == '-')
        {
            tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Subtraction));
        }

        //If '*'...
        else if (character == '*')
        {
            tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Multiply));
        }

        //If '/'...
        else if (character == '/')
        {
            tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Divide));
        }

        //If '<', '<>', or '<='...
        else if (character == '<')
        {
            if (iter != line.end() && *iter == '>')
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::NotEqual));
            }
            else if (iter != line.end() && *iter == '=')
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::LessThanOrEqual));
            }
            else
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::LessThan));
            }
            iter++;
        }

        //If '>' or '>='
        else if (character == '>')
        {
            if (iter != line.end() && *iter++ == '=')
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::GreaterThanOrEqual));
            }
            else
            {
                tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::GreaterThan));
            }
        }

        //If '!'
        else if (character == '!')
        {
            tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Not));
        }

        //If '('...
        else if (character == '(')
        {
            tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::OpenBracket));
        }

        //If ')'...
        else if (character == ')')
        {
            tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::CloseBracket));
        }

        //If ':'...
        else if (character == ':')
        {
            tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Colon));
        }

        //If ','...
        else if (character == ',')
        {
            tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::Comma));
        }

        //If newline...
        else if (character == '\n')
        {
            tokens->push_back(bv::Token(lineNumber, position, bv::Lexeme::NewLine));
        }
    }
}
