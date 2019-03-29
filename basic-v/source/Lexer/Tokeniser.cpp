#include "Tokeniser.hpp"

#include <iostream>

using namespace bv::Lexer;

void bv::Lexer::Tokeniser::TokeniseLines(std::vector<std::string>::iterator start, std::vector<std::string>::iterator end, int startLine, std::vector<bv::Token>* tokens)
{
    while (start != end)
    {
        tokens->push_back(bv::Lexer::Tokeniser::TokeniseLine(&(*start), startLine));
        start++;
    }
}

bv::Token bv::Lexer::Tokeniser::TokeniseLine(std::string* line, int lineNumber)
{
    std::string::iterator iter = line->begin();
    char character;

    while (iter < line->end())
    {
        character = *iter;
        int position = iter - line->begin();
        iter++;

        //If a keywors or an identifier...
        if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || (character == '_'))
        {
            std::string value(1, character);
            while (iter != line->end() && ((*iter >= 'a' && *iter <= 'z') || (*iter >= 'A' && *iter <= 'Z') || (*iter >= '0' && *iter <= '9') || (*iter == '_')))
            {
                value.append(1, *iter++);
            }

            // Look u-p whether or not the value matched predefined keywords.
            // If so, add the keyword to the token vector
            // If not, it is a custom identifier (see else)
            if (value == "false")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::False);
            }
            else if (value == "true")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::True);
            }
            else if (value == "if")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::If);
            }
            else if (value == "then")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Then);
            }
            else if (value == "case")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Case);
            }
            else if (value == "of")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Of);
            }
            else if (value == "when")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::When);
            }
            else if (value == "otherwise")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Otherwise);
            }
            else if (value == "for")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::For);
            }
            else if (value == "to")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::To);
            }
            else if (value == "next")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Next);
            }
            else if (value == "repeat")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Repeat);
            }
            else if (value == "until")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Until);
            }
            else if (value == "while")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::While);
            }
            else if (value == "endwhile")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::EndWhile);
            }
            else if (value == "end")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::End);
            }
            else if (value == "dim")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Dim);
            }
            else if (value == "data")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Data);
            }
            else if (value == "def")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Def);
            }
            else if (value == "sub")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Sub);
            }
            else if (value == "call")
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Call);
            }
            else
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Identifier, value);
            }


        }

        //If an integer or a real number...
        else if ((character >= '0' && character <= '9') || (character == '-' && *iter >= '0' && *iter <= '9'))
        {
            std::string value(1, character);

            while (iter != line->end() && *iter >= '0' && *iter <= '9' || (iter != line->end() && *iter == '.' && *(iter + 1) >= '0' && *(iter + 1) <= '9'))
            {
                value.append(1, *iter++);
            }

            //If the number contains a '.', it's a real. Otherwise, an integer.
            if (value.find('.') != std::string::npos)
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Real, value);
            }
            else
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Integer, value);
            }
        }

        //If a string literal...
        else if (character == '"')
        {
            std::string value(1, *iter++);
            while (iter != line->end() && *iter != '"')
            {
                value.append(1, *iter++);
            }
            iter++;
            return bv::Token(lineNumber, position, bv::Lexeme::String, value);
        }

        //If '=' or '=='...
        else if (character == '=')
        {
            if (iter != line->end() && *iter++ == '=')
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Equal);
            }
            else
            {
                return bv::Token(lineNumber, position, bv::Lexeme::Assign);
            }
        }

        //If '+'...
        else if (character == '+')
        {
            return bv::Token(lineNumber, position, bv::Lexeme::Addition);
        }

        //If '-'...
        else if (character == '-')
        {
            return bv::Token(lineNumber, position, bv::Lexeme::Subtraction);
        }

        //If '*'...
        else if (character == '*')
        {
            return bv::Token(lineNumber, position, bv::Lexeme::Multiply);
        }

        //If '/'...
        else if (character == '/')
        {
            return bv::Token(lineNumber, position, bv::Lexeme::Divide);
        }

        //If '<', '<>', or '<='...
        else if (character == '<')
        {
            if (iter != line->end() && *iter == '>')
            {
                return bv::Token(lineNumber, position, bv::Lexeme::NotEqual);
            }
            else if (iter != line->end() && *iter == '=')
            {
                return bv::Token(lineNumber, position, bv::Lexeme::LessThanOrEqual);
            }
            else
            {
                return bv::Token(lineNumber, position, bv::Lexeme::LessThan);
            }
            iter++;
        }

        //If '>' or '>='
        else if (character == '>')
        {
            if (iter != line->end() && *iter++ == '=')
            {
                return bv::Token(lineNumber, position, bv::Lexeme::GreaterThanOrEqual);
            }
            else
            {
                return bv::Token(lineNumber, position, bv::Lexeme::GreaterThan);
            }
        }

        //If '!'
        else if (character == '!')
        {
            return bv::Token(lineNumber, position, bv::Lexeme::Not);
        }

        //If '('...
        else if (character == '(')
        {
            return bv::Token(lineNumber, position, bv::Lexeme::OpenBracket);
        }

        //If ')'...
        else if (character == ')')
        {
            return bv::Token(lineNumber, position, bv::Lexeme::CloseBracket);
        }

        //If ':'...
        else if (character == ':')
        {
            return bv::Token(lineNumber, position, bv::Lexeme::Colon);
        }

        //If ','...
        else if (character == ',')
        {
            return bv::Token(lineNumber, position, bv::Lexeme::Comma);
        }

        else
        {
            std::cerr << "";
        }
    }
}
