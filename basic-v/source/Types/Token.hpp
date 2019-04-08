#pragma once

#include <cstdint>
#include <string>

#include "Lexeme.hpp"

namespace bv
{
    struct Token
    {
        uint64_t line;
        uint64_t position;
        Lexeme token;
        std::string value;

        Token()
        {
        };

        Token(uint64_t line, uint64_t position, Lexeme token, std::string value = "")
        {
            this->line = line;
            this->position = position;
            this->token = token;
            this->value = value;
        }
    };
}
