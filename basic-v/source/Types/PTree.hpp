#pragma once

#include <vector>

#include "Token.hpp"

namespace bv
{
    struct ParseTreeNode
    {
        std::vector<std::shared_ptr<ParseTreeNode>> nodes;
        Token token;

        ParseTreeNode()
        {

        }

        ParseTreeNode(Token token)
        {
            this->token = token;
        }
    };
}
