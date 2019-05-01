#include <iostream>
#include <vector>

#include "Parser\RecursiveDescent.hpp"
#include "Types\Token.hpp"
#include "Types\Lexeme.hpp"

struct PNode
{
	std::vector<size_t> branches;
	size_t datum;

	PNode()
	{
	}

	PNode(size_t datum)
	{
		this->datum = datum;
	}
};

size_t ParseTree(std::vector<PNode>* nodes, size_t* count, bv::ParseTreeNode node);

int main(int argc, char* argv[])
{
	std::string filepath;
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == 0)
		{
			continue;
		}

		if (argv[i][0] == '-' && argv[i][1] != '-')
		{
			if (argv[i][1] == 'h')
			{
				// todo: help text stuff here
			}
			else if (argv[i][1] == 'p')
			{
				if (i + 1 < argc)
				{
					filepath = argv[++i];
				}
			}
		}
	}

	if (filepath == "")
	{
		return 0;
	}

    std::vector<bv::Token> tokens;
	bv::Token::Parse(filepath , &tokens);

    bv::Parser::RecursiveDescent parser;
    parser.Parse(&tokens);

	std::vector<PNode> nodes;
	size_t count = 0;
	size_t root = 0;
	ParseTree(&nodes, &count ,*parser.tree);

	return 0;
}

size_t ParseTree(std::vector<PNode>* nodes, size_t* count, bv::ParseTreeNode node)
{
	size_t node_index = (*count)++;
	nodes->push_back(PNode(node.index));
	std::vector<size_t> children;
	for (const auto& branch : node.nodes)
	{
		size_t cindex = ParseTree(nodes, count, *branch);
		nodes->at(node_index).branches.push_back(cindex);
	}

	return node_index;
}
