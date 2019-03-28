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
			Node* left;
			Node* right;

			std::vector<Token> tokens;

			Node()
			{
				this->left = nullptr;
				this->right = nullptr;
			}

			Node(std::vector<Token> tokens)
			{
				this->tokens = tokens;
				this->left = nullptr;
				this->right = nullptr;
			}

			Node(std::vector<Token> tokens, Node* right)
			{
				this->tokens = tokens;
				this->left = left;
				this->right = nullptr;
			}

			Node(std::vector<Token> tokens, Node* right, Node* left)
			{
				this->tokens = tokens;
				this->left = left;
				this->right = right;
			}
		};
    };
}
