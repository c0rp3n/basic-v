#pragma once

#include <vector>

#include "Token.hpp"

namespace bv
{
    struct AsTree
    {
	public:
		struct Node;
        struct Expression;

		std::vector<Node> nodes;
        std::vector<Expression> expressions;

        std::vector<Node*> trees;

		AsTree()
		{
		}

		struct Node
		{
            Node* fork;
            Expression* expression;
			Node* flow;

			std::vector<Token> tokens;

			Node()
			{
				this->fork = nullptr;
                this->expression = nullptr;
				this->flow = nullptr;
			}

			Node(std::vector<Token> tokens, Node* flow, Node* fork, Expression* expression)
			{
				this->tokens = tokens;
				this->fork = fork;
                this->expression = expression;
				this->flow = flow;
			}
		};

        struct Expression
        {
            Expression* lhs;
            Expression* rhs;

            std::vector<Token> tokens;

            Expression()
            {
                this->lhs = nullptr;
                this->rhs = nullptr;
            }

            Expression(std::vector<Token> tokens, Expression* lhs, Expression* rhs)
            {
                this->lhs = lhs;
                this->rhs = rhs;
            }
        };
    };
}
