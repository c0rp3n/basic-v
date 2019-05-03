#include "CodeGenerator.hpp"

using namespace bv::Compiler;

bool CodeGenerator::GetNextNode
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
    return CodeGenerator::GetNextNode(nodes, parents, visited, currentNode);
}

bool CodeGenerator::GetNextNodeTillHome
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
    return CodeGenerator::GetNextNodeTillHome(nodes, parents, visited, currentNode, home);
}

void CodeGenerator::Parse(std::vector<bv::Token>* tokens, std::vector<bv::PNode>* nodes, std::string filepath = "help-me-for-fucks-sake.s")
{
    CodeGenerator::ParseData data;

    data.parents.push_back(-1);
    do
    {
        CodeGenerator::ParseTree(&data, 0);
    } while (GetNextNode(nodes, &data.parents, &data.visited, &data.nodeIndex));

    // Write assembly file (".s")
    {
        std::ofstream o(filepath, std::ios::binary);
        o << bv::Asm::Section::symbol_global << u8" " << bv::Asm::Section::main << std::endl;
        o << std::endl;
        o << bv::Asm::Section::section << u8" " + bv::Asm::Section::text << std::endl;
        o << bv::Asm::Section::main << u8":" << std::endl;

        for (auto& t : data.text)
        {
            o << t;
        }
        o << TAB << bv::Asm::Enviroment::Exit;
        o << TAB << bv::Asm::Enviroment::Call;

        o << std::endl;
        o << bv::Asm::Section::section << u8" " + bv::Asm::Section::section_data << std::endl;
        for (auto& d : data.data)
        {
            o << d;
        }

        o << std::endl;
        o << bv::Asm::Section::section << u8" " + bv::Asm::Section::section_ro_data << std::endl;
        for (auto& rd : data.rodata)
        {
            o << rd;
        }

        o.close();
    }
}

void CodeGenerator::Condition(CodeGenerator::ParseData* data, int64_t home, std::string returnSymbol)
{
    bv::PNode* node = &data->nodes->at(data->nodeIndex);
    bv::Token* token = &data->tokens->at(node->datum);

    std::string comparison;

    if (token->token == bv::Lexeme::Equal)
    {
        comparison = bv::Asm::Instruction::BranchEqual;
    }
    else if (token->token == bv::Lexeme::GreaterThan)
    {
        comparison = bv::Asm::Instruction::BranchGreaterThan;
    }

    if (GetNextNodeTillHome(data->nodes, &data->parents, &data->visited, &data->nodeIndex, home))
    {
        node = &data->nodes->at(data->nodeIndex);
        token = &data->tokens->at(node->datum);

        if (token->token == bv::Lexeme::Identifier)
        {
            data->text.push_back
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
            data->text.push_back
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

    if (GetNextNodeTillHome(data->nodes, &data->parents, &data->visited, &data->nodeIndex, home))
    {
        node = &data->nodes->at(data->nodeIndex);
        token = &data->tokens->at(node->datum);

        if (token->token == bv::Lexeme::Identifier)
        {
            data->text.push_back
            (
                TAB +
                fmt::format
                (
                    bv::Asm::Instruction::LoadAddress,
                    bv::Asm::Register::Temp1,
                    token->value
                )
            );
        }
        else if (token->token == bv::Lexeme::Integer)
        {
            data->text.push_back
            (
                TAB +
                fmt::format
                (
                    bv::Asm::Instruction::LoadInstant,
                    bv::Asm::Register::Temp1,
                    token->value
                )
            );
        }
    }

    data->text.push_back
    (
        TAB +
        fmt::format
        (
            comparison,
            bv::Asm::Register::Temp0,
            bv::Asm::Register::Temp1,
            returnSymbol
        )
    );
}

void CodeGenerator::ParseTree(CodeGenerator::ParseData* data, int64_t home)
{
    bv::PNode* node = &data->nodes->at(data->nodeIndex);
    bv::Token* token = &data->tokens->at(node->datum);

    // Declaration
    if (token->token == bv::Lexeme::Dim) // dim
    {
        std::string id;
        std::string type;
        std::string value;

        // Get assignment
        if (GetNextNode(data->nodes, &data->parents, &data->visited, &data->nodeIndex))
        {
            node = &data->nodes->at(data->nodeIndex);
            token = &data->tokens->at(node->datum);
        }

        // Get Identifier
        if (GetNextNode(data->nodes, &data->parents, &data->visited, &data->nodeIndex))
        {
            node = &data->nodes->at(data->nodeIndex);
            token = &data->tokens->at(node->datum);

            id = token->value;
        }

        // Get Value
        if (GetNextNode(data->nodes, &data->parents, &data->visited, &data->nodeIndex))
        {
            node = &data->nodes->at(data->nodeIndex);
            token = &data->tokens->at(node->datum);

            if (token->token == bv::Lexeme::Integer)
            {
                type = bv::Asm::DataTypes::int_word;
                value = token->value;

                data->idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::Integer));
            }
            else if (token->token == bv::Lexeme::Real)
            {
                type = bv::Asm::DataTypes::real;
                value = token->value;

                data->idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::Real));
            }
            else if (token->token == bv::Lexeme::String)
            {
                type = bv::Asm::DataTypes::string;
                value = "\"" + token->value + "\"";

                data->idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::String));
            }
            else if (token->token == bv::Lexeme::Input)
            {
                // cry
            }
        }

        data->data.push_back(TAB + id + ": " + type + " " + value + "\n");
    }

    else if (token->token == bv::Lexeme::Data) // data
    {
        std::string id;
        std::string type;
        std::string value;

        // Get assignment
        if (GetNextNode(data->nodes, &data->parents, &data->visited, &data->nodeIndex))
        {
            node = &data->nodes->at(data->nodeIndex);
            token = &data->tokens->at(node->datum);
        }

        // Get Identifier
        if (GetNextNode(data->nodes, &data->parents, &data->visited, &data->nodeIndex))
        {
            node = &data->nodes->at(data->nodeIndex);
            token = &data->tokens->at(node->datum);

            id = token->value;
        }

        // Get Value
        if (GetNextNode(data->nodes, &data->parents, &data->visited, &data->nodeIndex))
        {
            node = &data->nodes->at(data->nodeIndex);
            token = &data->tokens->at(node->datum);

            if (token->token == bv::Lexeme::Integer)
            {
                type = bv::Asm::DataTypes::int_word;
                value = token->value;

                data->idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::Integer));
            }
            else if (token->token == bv::Lexeme::Real)
            {
                type = bv::Asm::DataTypes::real;
                value = token->value;

                data->idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::Real));
            }
            else if (token->token == bv::Lexeme::String)
            {
                type = bv::Asm::DataTypes::string;
                value = "\"" + token->value + "\"";

                data->idTypes.insert(std::pair<std::string, bv::Lexeme>(id, bv::Lexeme::String));
            }
        }

        data->rodata.push_back(TAB + id + ": " + type + " " + value + "\n");
    }

    // Assignment
    else if (token->token == bv::Lexeme::Assign)
    {
        bv::Lexeme type;

        std::string id;
        std::string valueRegister = bv::Asm::Register::Temp0;

        // Get Id
        if (GetNextNode(data->nodes, &data->parents, &data->visited, &data->nodeIndex))
        {
            node = &data->nodes->at(data->nodeIndex);
            token = &data->tokens->at(node->datum);

            id = token->value;
            type = data->idTypes[token->value];
        }

        // Get Value
        if (GetNextNode(data->nodes, &data->parents, &data->visited, &data->nodeIndex))
        {
            node = &data->nodes->at(data->nodeIndex);
            token = &data->tokens->at(node->datum);

            if (token->token == bv::Lexeme::Addition)
            {
                std::string instruction;
                std::string rhs;

                // Lhs
                if (GetNextNode(data->nodes, &data->parents, &data->visited, &data->nodeIndex))
                {
                    node = &data->nodes->at(data->nodeIndex);
                    token = &data->tokens->at(node->datum);

                    if (token->token == bv::Lexeme::Identifier)
                    {
                        data->text.push_back
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
                        data->text.push_back
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
                if (GetNextNode(data->nodes, &data->parents, &data->visited, &data->nodeIndex))
                {
                    node = &data->nodes->at(data->nodeIndex);
                    token = &data->tokens->at(node->datum);

                    if (token->token == bv::Lexeme::Identifier)
                    {
                        data->text.push_back
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

                data->text.push_back
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
                data->text.push_back(TAB + bv::Asm::Enviroment::ReadInt);
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
                        data->text.push_back
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
                        data->text.push_back
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
                        std::string loc = u8"_float_" + data->floatCount++;
                        data->text.push_back
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
                        data->rodata.push_back(TAB + loc + u8": " + bv::Asm::DataTypes::real + u8" " + token->value + u8"\n");
                    }
                    else if (token->token == bv::Lexeme::String)
                    {
                        // Load data to a1
                        std::string loc = u8"_string_" + data->stringCount++;
                        data->text.push_back
                        (
                            TAB +
                            fmt::format
                            (
                                bv::Asm::Instruction::LoadAddress,
                                bv::Asm::Register::Temp0,
                                id
                            )
                        );

                        data->rodata.push_back(TAB + loc + u8": " + bv::Asm::DataTypes::string + u8" \"" + token->value + u8"\"\n");
                    }
                }
            }
        }

        data->text.push_back
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
        if (GetNextNode(data->nodes, &data->parents, &data->visited, &data->nodeIndex))
        {
            node = &data->nodes->at(data->nodeIndex);
            token = &data->tokens->at(node->datum);

            if (token->token == bv::Lexeme::Identifier)
            {
                bv::Lexeme type = data->idTypes[token->value];
                if (type == bv::Lexeme::Integer)
                {
                    // Enviroment Code
                    data->text.push_back(TAB + bv::Asm::Enviroment::PrintInt);
                }
                else if (type == bv::Lexeme::Real)
                {
                    data->text.push_back(TAB + bv::Asm::Enviroment::PrintFloat);
                }
                else if (type == bv::Lexeme::String)
                {
                    data->text.push_back(TAB + bv::Asm::Enviroment::PrintString);
                }

                // Load data to a1
                data->text.push_back
                (
                    TAB +
                    fmt::format
                    (
                        bv::Asm::Instruction::LoadAddress,
                        bv::Asm::Register::Arg1,
                        token->value
                    )
                );
                data->text.push_back(bv::Asm::Enviroment::Call);
            }
            else if (token->token == bv::Lexeme::Int)
            {
                // Enviroment Code
                data->text.push_back(TAB + bv::Asm::Enviroment::PrintInt);
                // Load data to a1
                data->text.push_back
                (
                    TAB +
                    fmt::format
                    (
                        bv::Asm::Instruction::LoadInstant,
                        bv::Asm::Register::Arg1,
                        token->value
                    )
                );
                data->text.push_back(bv::Asm::Enviroment::Call);
            }
            else if (token->token == bv::Lexeme::Real)
            {
                // Enviroment Code
                data->text.push_back(TAB + bv::Asm::Enviroment::PrintFloat);
                // Load data to a1
                std::string loc = u8"_float_" + data->floatCount++;
                data->text.push_back
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
                data->rodata.push_back(TAB + loc + u8": " + bv::Asm::DataTypes::real + u8" " + token->value + u8"\n");
                data->text.push_back(bv::Asm::Enviroment::Call);
            }
            else if (token->token == bv::Lexeme::String)
            {
                std::string loc = u8"_string_" + data->stringCount++;

                // Enviroment Code
                data->text.push_back(TAB + bv::Asm::Enviroment::PrintString);
                // Load data to a1
                data->text.push_back
                (
                    TAB +
                    fmt::format
                    (
                        bv::Asm::Instruction::LoadAddress,
                        bv::Asm::Register::Arg1,
                        loc
                    )
                );

                data->rodata.push_back(TAB + loc + u8": " + bv::Asm::DataTypes::string + u8" " + token->value + u8"\n");
                data->text.push_back(bv::Asm::Enviroment::Call);
            }
        }
    }

    // Control / Flow
    else if (token->token == bv::Lexeme::If) // if
    {

    }

    else if (token->token == bv::Lexeme::While)
    {
        // Add loop back point
        std::string symbol = u8"_while_" + data->whileCount++;
        data->text.push_back(symbol + ":\n");

        // Condition
        if (GetNextNode(data->nodes, &data->parents, &data->visited, &data->nodeIndex))
        {
            CodeGenerator::Condition(data, data->nodeIndex);
        }

        // Body
        if (GetNextNode(data->nodes, &data->parents, &data->visited, &data->nodeIndex))
        {
            CodeGenerator::ParseTree(data, data->nodeIndex);
        }

        // Loop back
        data->text.push_back
        (
            fmt::format
            (
                bv::Asm::Instruction::Jump,
                symbol
            )
        );
    }
}