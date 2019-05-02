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

        static bool GetNextNodeTillHome
        (
            std::vector<bv::PNode>* nodes,
            std::vector<int64_t>* parents,
            std::vector<bool>* visited,
            int64_t* currentNode,
            int64_t home
        )
        {
            if (*currentNode < 0 || *currentNode == home)
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
            return GetNextNodeTillHome(nodes, parents, visited, currentNode, home);
        }

    public:
		static void Parse(std::vector<bv::Token>* tokens, std::vector<bv::PNode>* nodes, std::string filepath = "help-me-for-fucks-sake.s")
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

            size_t ifCount = 0;
            size_t whileCount = 0;

			std::map<std::string, bv::Lexeme> idTypes;

            int64_t nodeIndex = 0;
            parents.push_back(-1);
			do
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

                        if (token->token == bv::Lexeme::Integer)
                        {
                            type = bv::Asm::DataTypes::int_word;
                            value = token->value;

                            idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::Integer));
                        }
                        else if (token->token == bv::Lexeme::Real)
                        {
                            type = bv::Asm::DataTypes::real;
                            value = token->value;

                            idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::Real));
                        }
                        else if (token->token == bv::Lexeme::String)
                        {
                            type = bv::Asm::DataTypes::string;
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

                        if (token->token == bv::Lexeme::Integer)
                        {
                            type = bv::Asm::DataTypes::int_word;
                            value = token->value;

                            idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::Integer));
                        }
                        else if (token->token == bv::Lexeme::Real)
                        {
                            type = bv::Asm::DataTypes::real;
                            value = token->value;

                            idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::Real));
                        }
                        else if (token->token == bv::Lexeme::String)
                        {
                            type = bv::Asm::DataTypes::string;
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

                        id = token->value;
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
                                        )
                                    );
                                }
                                else if (token->token == bv::Lexeme::Real)
                                {
                                    // Load data to a1
                                    std::string loc = u8"_float_" + floatCount++;
                                    text.push_back
                                    (
                                        TAB +
                                        fmt::format
                                        (
                                            bv::Asm::Instruction::FloatLoadWord,
                                            bv::Asm::Register::Temp0,
                                            id,
                                            bv::Asm::Register::Temp0
                                        )
                                    );
                                    rodata.push_back(TAB + loc + u8": " + bv::Asm::DataTypes::real + u8" " + token->value + u8"\n");
                                }
                                else if (token->token == bv::Lexeme::String)
                                {
                                    // Load data to a1
                                    std::string loc = u8"_string_" + stringCount++;
                                    text.push_back
                                    (
                                        TAB +
                                        fmt::format
                                        (
                                            bv::Asm::Instruction::LoadAddress,
                                            bv::Asm::Register::Temp0,
                                            id
                                        )
                                    );

                                    rodata.push_back(TAB + loc + u8": " + bv::Asm::DataTypes::string + u8" \"" + token->value + u8"\"\n");
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
                            valueRegister,
                            id,
                            bv::Asm::Register::Temp0
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
                            std::string loc = u8"_float_" + floatCount++;
                            text.push_back
                            (
                                TAB +
                                fmt::format
                                (
                                    bv::Asm::Instruction::FloatLoadWord,
                                    bv::Asm::Register::FloatArg0,
                                    loc,
                                    bv::Asm::Register::Temp0
                                )
                            );
                            rodata.push_back(TAB + loc + u8": " + bv::Asm::DataTypes::real + u8" " + token->value + u8"\n");
                            text.push_back(bv::Asm::Enviroment::Call);
                        }
                        else if (token->token == bv::Lexeme::String)
                        {
                            std::string loc = u8"_string_" + stringCount++;

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
                                    loc
                                )
                            );

                            rodata.push_back(TAB + loc + u8": " + bv::Asm::DataTypes::string + u8" " + token->value + u8"\n");
                            text.push_back(bv::Asm::Enviroment::Call);
                        }
                    }
                }

                // Control / Flow
                else if (token->token == bv::Lexeme::While)
                {
                    // Add loop back point
                    std::string symbol = u8"_while_" + whileCount++;
                    text.push_back(symbol + ":\n");

                    // Condition


                    // Body


                    // Loop back
                    text.push_back
                    (
                        fmt::format
                        (
                            bv::Asm::Instruction::Jump,
                            symbol
                        )
                    );
                }

				else if (token->token == bv::Lexeme::If) // if
				{

				}
            } while (GetNextNode(nodes, &parents, &visited, &nodeIndex));

            {
                std::ofstream o(filepath, std::ios::binary);
                o << bv::Asm::Section::symbol_global << u8" " << bv::Asm::Section::main << std::endl;
                o << std::endl;
                o << bv::Asm::Section::section << u8" " + bv::Asm::Section::text << std::endl;
                o << bv::Asm::Section::main << u8":" << std::endl;

                for (auto& t : text)
                {
                    o << t;
                }
                o << TAB << bv::Asm::Enviroment::Exit;
                o << TAB << bv::Asm::Enviroment::Call;

                o << std::endl;
                o << bv::Asm::Section::section << u8" " + bv::Asm::Section::section_data << std::endl;
                for (auto& d : data)
                {
                    o << d;
                }

                o << std::endl;
                o << bv::Asm::Section::section << u8" " + bv::Asm::Section::section_ro_data << std::endl;
                for (auto& rd : rodata)
                {
                    o << rd;
                }

                o.close();
            }
		}
	};
}
