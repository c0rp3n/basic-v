#pragma once

#include <vector>

#include "Token.hpp"

namespace bv
{
    struct AsTree
    {
	public:
		struct Node;

		std::vector<Node> tree;

		AsTree()
		{
		}

		struct Node
		{
			Node* fork;
            Node* expression;
			Node* flow;

			std::vector<Token> tokens;

			Node()
			{
				this->fork = nullptr;
                this->expression = nullptr;
				this->flow = nullptr;
			}

			Node(std::vector<Token> tokens, Node* flow, Node* expression, Node* fork)
			{
				this->tokens = tokens;
				this->fork = fork;
                this->expression = expression;
				this->flow = flow;
			}
		};
    };
}
