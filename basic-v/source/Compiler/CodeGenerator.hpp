#pragma once

#define TAB "    "

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <fmt/format.h>

#include "../Types/AsmSection.hpp"
#include "../Types/AsmDataTypes.hpp"
#include "../Types/AsmInstructions.hpp"
#include "../Types/AsmRegisters.hpp"
#include "../Types/AsmEnviromentCalls.hpp"
#include "../Types/Lexeme.hpp"
#include "../Types/Token.hpp"
#include "../Types/PNode.hpp"

namespace bv::Compiler
{
	class CodeGenerator
	{
    private:
        struct ParseData
        {
            std::vector<bv::Token>* tokens;
            std::vector<bv::PNode>* nodes;
            std::vector<int64_t> parents;
            std::vector<bool> visited;

            std::vector<std::string> text;
            std::vector<std::string> data;
            std::vector<std::string> rodata;

            size_t savedRegisterCount;
            const size_t savedRegisters = 10;
            std::map<std::string, size_t> idRegisters;

            size_t floatCount;
            size_t stringCount;

            size_t ifCount;
            size_t whileCount;

            std::map<std::string, bv::Lexeme> idTypes;

            int64_t nodeIndex;

            ParseData()
            {
                this->visited.resize(this->nodes->size());
                std::fill<std::vector<bool>::iterator, bool>(this->visited.begin(), this->visited.end(), false);

                this->savedRegisterCount = 0;
                this->floatCount = 0;
                this->stringCount = 0;
                this->ifCount = 0;
                this->whileCount = 0;
                this->nodeIndex = 0;
            }
        };

        static bool GetNextNode
        (
            std::vector<bv::PNode>* nodes,
            std::vector<int64_t>* parents,
            std::vector<bool>* visited,
            int64_t* currentNode
        );

        static bool GetNextNodeTillHome
        (
            std::vector<bv::PNode>* nodes,
            std::vector<int64_t>* parents,
            std::vector<bool>* visited,
            int64_t* currentNode,
            int64_t home
        );

        static void ParseTree(ParseData* data, int64_t home);

        static void Condition(ParseData* data, int64_t home);

    public:
        static void Parse(std::vector<bv::Token>* tokens, std::vector<bv::PNode>* nodes, std::string filepath = "help-me-for-fucks-sake.s");
	};
}
