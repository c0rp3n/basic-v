#include <filesystem>
#include <iostream>
#include <vector>

#include <nlohmann/json.hpp>

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
void Serialise(std::string jsonpath, std::vector<PNode>* nodes);

int main(int argc, char* argv[])
{
	std::string filepath;
	std::string fileout;
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
            else if (argv[i][1] == 'o')
            {
                if (i + 1 < argc)
                {
                    fileout = argv[++i];
                }
            }
		}
	}

	if (filepath == "")
	{
		return 1;
	}

    std::vector<bv::Token> tokens;
	if (!bv::Token::Parse(filepath, &tokens))
	{
		// eererererereererer
		return 1;
	}

    bv::Parser::RecursiveDescent parser;
    parser.Parse(&tokens);

	std::vector<PNode> nodes;
	size_t count = 0;
	size_t root = 0;
	ParseTree(&nodes, &count ,*parser.tree);

    if (fileout != "")
    {
        Serialise(fileout, &nodes);
    }
    else
    {
        std::cout << "Error: empty output string passed." << std::endl;
    }

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

void Serialise(std::string jsonpath, std::vector<PNode>* nodes)
{
	nlohmann::json json;
	json[u8"nodes"] = {};
	for (PNode& n : *nodes)
	{
		json[u8"nodes"].push_back({
			{ u8"branches", n.branches },
			{ u8"datum", n.datum },
			});
	}

	std::ofstream o(jsonpath, std::ios::binary);
	o << std::setw(4) << json << std::endl;
	o.close();
}
