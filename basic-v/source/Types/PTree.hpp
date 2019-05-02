#pragma once

#include <vector>

#include "Token.hpp"

namespace bv
{
    struct ParseTreeNode
    {
        std::vector<std::shared_ptr<ParseTreeNode>> nodes;
        size_t index;

        ParseTreeNode()
        {

        }

        ParseTreeNode(size_t index)
        {
            this->index = index;
        }
    };
}
