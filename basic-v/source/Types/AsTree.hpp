#pragma once

#include <vector>

#include "Token.hpp"

namespace bv
{
    struct AsTree
    {
        AsTree* left;
        AsTree* right;

        std::vector<Token> tokens;

        AsTree()
        {
            this->left = nullptr;
            this->right = nullptr;
        }

        AsTree(std::vector<Token> tokens)
        {
            this->tokens = tokens;
            this->left = nullptr;
            this->right = nullptr;
        }

        AsTree(std::vector<Token> tokens, AsTree* left)
        {
            this->tokens = tokens;
            this->left = left;
            this->right = nullptr;
        }

        AsTree(std::vector<Token> tokens, AsTree* left, AsTree* right)
        {
            this->tokens = tokens;
            this->left = left;
            this->right = right;
        }
    };
}
