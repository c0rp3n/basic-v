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
        static bool GetNextNode
        (
            std::vector<bv::PNode>* nodes,
            std::vector<int64_t>* parents,
            std::vector<bool>* visited,
            int64_t* currentNode
        )
        {
            if (*currentNode < 0)
            {
                return false;
            }

            for (auto& child : nodes->at(*currentNode).branches)
            {
                if (!(visited->at(child)))
                {
                    parents->push_back(*currentNode);
                    visited->at(child) = true;
                    *currentNode = child;
                    return true;
                }
            }

            *currentNode = parents->at(*currentNode);
            return GetNextNode(nodes, parents, visited, currentNode);
        }

    public:
		static void Parse(std::vector<bv::Token>* tokens, std::vector<bv::PNode>* nodes)
		{
            std::vector<int64_t> parents;
            std::vector<bool> visited(nodes->size());
            std::fill<std::vector<bool>::iterator, bool>(visited.begin(), visited.end(), false);

			std::vector<std::string> text;
			std::vector<std::string> data;
			std::vector<std::string> rodata;

            size_t savedRegisterCount = 0;
            const size_t savedRegisters = 10;
            std::map<std::string, size_t> idRegisters;

            size_t floatCount = 0;
            size_t stringCount = 0;

			std::map<std::string, bv::Lexeme> idTypes;

            int64_t nodeIndex = 0;
            parents.push_back(-1);
			while (GetNextNode(nodes, &parents, &visited, &nodeIndex))
			{
                bv::PNode* node = &nodes->at(nodeIndex);
                bv::Token* token = &tokens->at(node->datum);

                // Declaration
                if (token->token == bv::Lexeme::Dim) // dim
                {
                    std::string id;
                    std::string type;
                    std::string value;

                    // Get assignment
                    if (GetNextNode(nodes, &parents, &visited, &nodeIndex))
                    {
                        node = &nodes->at(nodeIndex);
                        token = &tokens->at(node->datum);
                    }

                    // Get Identifier
                    if (GetNextNode(nodes, &parents, &visited, &nodeIndex))
                    {
                        node = &nodes->at(nodeIndex);
                        token = &tokens->at(node->datum);

                        id = token->value;
                    }

                    // Get Value
                    if (GetNextNode(nodes, &parents, &visited, &nodeIndex))
                    {
                        node = &nodes->at(nodeIndex);
                        token = &tokens->at(node->datum);

                        if (token->token == bv::Lexeme::Int)
                        {
                            type = bv::Asm::data_int_word;
                            value = token->value;

                            idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::Int));
                        }
                        else if (token->token == bv::Lexeme::Real)
                        {
                            type = bv::Asm::data_real;
                            value = token->value;

                            idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::Real));
                        }
                        else if (token->token == bv::Lexeme::String)
                        {
                            type = bv::Asm::data_string;
                            value = "\"" + token->value + "\"";

                            idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::String));
                        }
                        else if (token->token == bv::Lexeme::Input)
                        {
                            // cry
                        }
                    }

                    data.push_back(TAB + id + ": " + type + " " + value + "\n");
                }

                else if (token->token == bv::Lexeme::Data) // data
                {
                    std::string id;
                    std::string type;
                    std::string value;

                    // Get assignment
                    if (GetNextNode(nodes, &parents, &visited, &nodeIndex))
                    {
                        node = &nodes->at(nodeIndex);
                        token = &tokens->at(node->datum);
                    }

                    // Get Identifier
                    if (GetNextNode(nodes, &parents, &visited, &nodeIndex))
                    {
                        node = &nodes->at(nodeIndex);
                        token = &tokens->at(node->datum);

                        id = token->value;
                    }

                    // Get Value
                    if (GetNextNode(nodes, &parents, &visited, &nodeIndex))
                    {
                        node = &nodes->at(nodeIndex);
                        token = &tokens->at(node->datum);

                        if (token->token == bv::Lexeme::Int)
                        {
                            type = bv::Asm::data_int_word;
                            value = token->value;

                            idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::Int));
                        }
                        else if (token->token == bv::Lexeme::Real)
                        {
                            type = bv::Asm::data_real;
                            value = token->value;

                            idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::Real));
                        }
                        else if (token->token == bv::Lexeme::String)
                        {
                            type = bv::Asm::data_string;
                            value = "\"" + token->value + "\"";

                            idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::String));
                        }
                    }

                    rodata.push_back(TAB + id + ": " + type + " " + value + "\n");
                }

                // Assignment
                else if (token->token == bv::Lexeme::Assign)
                {
                    bv::Lexeme type;

                    std::string id;
                    std::string valueRegister = bv::Asm::Register::Temp0;

                    // Get Id
                    if (GetNextNode(nodes, &parents, &visited, &nodeIndex))
                    {
                        node = &nodes->at(nodeIndex);
                        token = &tokens->at(node->datum);

                        type = idTypes[token->value];
                    }

                    // Get Value
                    if (GetNextNode(nodes, &parents, &visited, &nodeIndex))
                    {
                        node = &nodes->at(nodeIndex);
                        token = &tokens->at(node->datum);

                        if (token->token == bv::Lexeme::Addition)
                        {
                            std::string instruction;
                            std::string rhs;

                            // Lhs
                            if (GetNextNode(nodes, &parents, &visited, &nodeIndex))
                            {
                                node = &nodes->at(nodeIndex);
                                token = &tokens->at(node->datum);

                                if (token->token == bv::Lexeme::Identifier)
                                {
                                    text.push_back
                                    (
                                        TAB +
                                        fmt::format
                                        (
                                            bv::Asm::Instruction::LoadAddress,
                                            bv::Asm::Register::Temp0,
                                            token->value
                                        )
                                    );
                                }
                                else if (token->token == bv::Lexeme::Integer)
                                {
                                    text.push_back
                                    (
                                        TAB +
                                        fmt::format
                                        (
                                            bv::Asm::Instruction::LoadInstant,
                                            bv::Asm::Register::Temp0,
                                            token->value
                                        )
                                    );
                                }
                            }

                            // Rhs
                            if (GetNextNode(nodes, &parents, &visited, &nodeIndex))
                            {
                                node = &nodes->at(nodeIndex);
                                token = &tokens->at(node->datum);

                                if (token->token == bv::Lexeme::Identifier)
                                {
                                    text.push_back
                                    (
                                        TAB +
                                        fmt::format
                                        (
                                            bv::Asm::Instruction::LoadAddress,
                                            bv::Asm::Register::Temp1,
                                            token->value
                                        )
                                    );

                                    instruction = bv::Asm::Instruction::Add;
                                    rhs = bv::Asm::Register::Temp1;
                                }
                                else if (token->token == bv::Lexeme::Integer)
                                {
                                    instruction = bv::Asm::Instruction::AddI;
                                    rhs = token->value;
                                }
                            }

                            text.push_back
                            (
                                TAB +
                                fmt::format
                                (
                                    instruction,
                                    bv::Asm::Register::Temp0,
                                    bv::Asm::Register::Temp0,
                                    rhs
                                )
                            );
                        }
                        else if (token->token == bv::Lexeme::Input)
                        {
                            text.push_back(TAB + bv::Asm::Enviroment::ReadInt);
                            valueRegister = bv::Asm::Register::Arg0;
                        }
                        else
                        {
                            if (token->token != type)
                            {
                                // throw
                                return;
                            }
                            else
                            {
                                if (token->token == bv::Lexeme::Identifier)
                                {
                                    text.push_back
                                    (
                                        TAB +
                                        fmt::format
                                        (
                                            bv::Asm::Instruction::LoadAddress,
                                            bv::Asm::Register::Temp0,
                                            token->value
                                        )
                                    );
                                }
                                else if (token->token == bv::Lexeme::Integer)
                                {
                                    text.push_back
                                    (
                                        TAB +
                                        fmt::format
                                        (
                                            bv::Asm::Instruction::LoadInstant,
                                            bv::Asm::Register::Temp0,
                                            token->value
                                        ) +
                                        "\n"
                                    );
                                }
                            }
                        }
                    }

                    text.push_back
                    (
                        TAB +
                        fmt::format
                        (
                            bv::Asm::Instruction::StoreWord,

                        )
                    );
                }

                // Print
                else if (token->token == bv::Lexeme::Print)
                {
                    if (GetNextNode(nodes, &parents, &visited, &nodeIndex))
                    {
                        node = &nodes->at(nodeIndex);
                        token = &tokens->at(node->datum);

                        if (token->token == bv::Lexeme::Identifier)
                        {
                            bv::Lexeme type = idTypes[token->value];
                            if (type == bv::Lexeme::Integer)
                            {
                                // Enviroment Code
                                text.push_back(TAB + bv::Asm::Enviroment::PrintInt);
                            }
                            else if (type == bv::Lexeme::Real)
                            {
                                text.push_back(TAB + bv::Asm::Enviroment::PrintFloat);
                            }
                            else if (type == bv::Lexeme::String)
                            {
                                text.push_back(TAB + bv::Asm::Enviroment::PrintString);
                            }

                            // Load data to a1
                            text.push_back
                            (
                                TAB +
                                fmt::format
                                (
                                    bv::Asm::Instruction::LoadAddress,
                                    bv::Asm::Register::Arg1,
                                    token->value
                                )
                            );
                            text.push_back(bv::Asm::Enviroment::Call);
                        }
                        else if (token->token == bv::Lexeme::Int)
                        {
                            // Enviroment Code
                            text.push_back(TAB + bv::Asm::Enviroment::PrintInt);
                            // Load data to a1
                            text.push_back
                            (
                                TAB +
                                fmt::format
                                (
                                    bv::Asm::Instruction::LoadInstant,
                                    bv::Asm::Register::Arg1,
                                    token->value
                                )
                            );
                            text.push_back(bv::Asm::Enviroment::Call);
                        }
                        else if (token->token == bv::Lexeme::Real)
                        {
                            // Enviroment Code
                            text.push_back(TAB + bv::Asm::Enviroment::PrintFloat);
                            // Load data to a1
                            std::string id = "_float_" + floatCount++;
                            text.push_back
                            (
                                TAB +
                                fmt::format
                                (
                                    bv::Asm::Instruction::FloatLoadWord,
                                    bv::Asm::Register::FloatArg0,
                                    id,
                                    bv::Asm::Register::Temp0
                                )
                            );
                            rodata.push_back(TAB + id + ": " + bv::Asm::DataTypes::real + " " + token->value + "\n");
                            text.push_back(bv::Asm::Enviroment::Call);
                        }
                        else if (token->token == bv::Lexeme::String)
                        {
                            std::string id = "_string_" + stringCount++;

                            // Enviroment Code
                            text.push_back(TAB + bv::Asm::Enviroment::PrintString);
                            // Load data to a1
                            text.push_back
                            (
                                TAB +
                                fmt::format
                                (
                                    bv::Asm::Instruction::LoadAddress,
                                    bv::Asm::Register::Arg1,
                                    id
                                )
                            );

                            rodata.push_back(TAB + id + ": " + bv::Asm::DataTypes::string + " " + token->value + "\n");
                            text.push_back(bv::Asm::Enviroment::Call);
                        }
                    }
                }

                // Control / Flow
				else if (token->token == bv::Lexeme::If) // if
				{

				}
			}

            int help = 1;
		}
	};
}
