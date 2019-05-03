#include "RecursiveDescent.hpp"

#include <iostream>

void bv::Parser::RecursiveDescent::Parse(std::vector<Token>* tokens)
{
    this->tokens = tokens;
    this->tokenIterator = tokens->begin();
    this->Program();
}

bool bv::Parser::RecursiveDescent::Accept(Lexeme l)
{
    if (this->tokenIterator == this->tokens->end())
        return false;
    if (this->tokenIterator->token == l) {
        this->AddToTree();
        this->tokenIterator++;
        return true;
    }
    return false;
}

bool bv::Parser::RecursiveDescent::Expect(Lexeme l)
{
    if (this->Accept(l))
        return true;
    this->Error("expect: unexpected symbol");
    return false;
}

void bv::Parser::RecursiveDescent::AddToTree()
{
    Lexeme t = this->tokenIterator->token;
    if (t == Lexeme::OpenBracket || t == Lexeme::CloseBracket || t == Lexeme::NewLine || t == Lexeme::Then || t == Lexeme::End || t == Lexeme::Of || t == Lexeme::Colon || t == Lexeme::Do || t == Lexeme::Next)
        return;

    std::shared_ptr<ParseTreeNode> node(new ParseTreeNode(this->tokenIterator - this->tokens->begin()));

    //If tree is empty, make this the root node
    if (this->tree == nullptr)
    {
        this->tree = node;
    }

    else if (t == Lexeme::If || t == Lexeme::Case || (t == Lexeme::Identifier && this->tokens->at(tree->index).token == Lexeme::For))
        return;

    else if (t == Lexeme::Assign)
    {
        node->nodes.push_back(tree);
        this->tree = node;
    }
    else if ((*this->tokens)[tree->index].token == Lexeme::Case || this->tokens->at(tree->index).token == Lexeme::When)
    {
        this->tree->nodes.push_back(node);
    }



    //Expression rules

    else if (this->tree->nodes.size() == 2)
    {
        node->nodes.push_back(this->tree);
        this->tree = node;
    }
    //If node has no lhs, push tree to lhs
    else if (this->tree->nodes.size() < 1)
    {
        node->nodes.push_back(this->tree);
        this->tree = node;
    }
    //Otherwise push to rhs of tree
    else
    {
        this->tree->nodes.push_back(node);
    }
}

void bv::Parser::RecursiveDescent::Factor()
{
    if (this->Accept(Lexeme::Identifier) || this->Accept(Lexeme::Real) || this->Accept(Lexeme::Integer) || this->Accept(Lexeme::Input))
    {
        ;
    }
    else if (this->Accept(Lexeme::OpenBracket))
    {
        this->Expression();
        this->Expect(Lexeme::CloseBracket);
    }
    else
    {
        this->Error("factor: syntax error");
        this->tokenIterator++;
    }
}

void bv::Parser::RecursiveDescent::Term()
{
    this->Factor();
    while (this->Accept(Lexeme::Multiply) || this->Accept(Lexeme::Divide))
    {
        this->Factor();
    }
}

void bv::Parser::RecursiveDescent::Expression()
{
    if (this->Accept(Lexeme::Addition) || this->Accept(Lexeme::Subtraction))
    {
        ;
    }
    this->Term();
    while (this->Accept(Lexeme::Addition) || this->Accept(Lexeme::Subtraction))
    {
        this->Term();
    }
}

void bv::Parser::RecursiveDescent::Condition()
{
    this->Expect(Lexeme::OpenBracket);

    if (this->Accept(Lexeme::Not))
    {
        this->Factor();
    }
    else
    {
        this->Expression();
        std::shared_ptr<ParseTreeNode> lhs = this->tree;
        this->tree = nullptr;

        if (Accept(Lexeme::Equal) || Accept(Lexeme::NotEqual) || Accept(Lexeme::LessThan) || Accept(Lexeme::LessThanOrEqual) || Accept(Lexeme::GreaterThan) || Accept(Lexeme::GreaterThanOrEqual))
        {
            this->tree->nodes.push_back(lhs);
            std::shared_ptr<ParseTreeNode> tempTree = this->tree;
            this->tree = nullptr;
            this->Expression();
            tempTree->nodes.push_back(this->tree);
            this->tree = tempTree;
        }
        else
        {
            this->Error("condition: invalid operator");
        }
    }

    this->Expect(Lexeme::CloseBracket);
}

void bv::Parser::RecursiveDescent::Statement()
{
    std::shared_ptr<ParseTreeNode> masterTree = this->tree;
    this->tree = nullptr;

    if (this->Accept(Lexeme::Identifier))
    {
        this->Expect(Lexeme::Assign);
        if (!this->Accept(Lexeme::String))
        {
            std::shared_ptr<ParseTreeNode> tree2 = this->tree;
            this->tree = nullptr;
            this->Expression();
            tree2->nodes.push_back(this->tree);
            this->tree = tree2;
        }
    }
    else if (this->Accept(Lexeme::Print))
    {
        std::shared_ptr<ParseTreeNode> tempTree = this->tree;
        this->tree = nullptr;

        if (this->Accept(Lexeme::Identifier) || this->Accept(Lexeme::Integer) || this->Accept(Lexeme::Real) || this->Accept(Lexeme::String))
        {
            ;
        }
        else if (this->Accept(Lexeme::OpenBracket))
        {
            this->Expression();
            this->Expect(Lexeme::CloseBracket);
        }
        else
        {
            this->Error("Invalid value passed to PRINT");
        }
        tempTree->nodes.push_back(this->tree);
        this->tree = tempTree;
    }
    else if (this->Accept(Lexeme::If))
    {
        std::shared_ptr<ParseTreeNode> tempTree = this->tree;
        this->tree = nullptr;
        this->Condition();
        tempTree->nodes.push_back(this->tree);
        this->tree = nullptr;
        this->Statement();
        tempTree->nodes.push_back(this->tree);
        this->tree = nullptr;

        this->Expect(Lexeme::NewLine);

        while (this->Accept(Lexeme::Else))
        {
            std::shared_ptr<ParseTreeNode> elseTree = this->tree;
            tree = nullptr;

            if (this->Accept(Lexeme::If))
            {
                std::shared_ptr<ParseTreeNode> ifTree = this->tree;
                this->tree = nullptr;
                this->Condition();
                ifTree->nodes.push_back(this->tree);
                this->tree = nullptr;
                this->Statement();
                ifTree->nodes.push_back(this->tree);
                tree = ifTree;
            }
            else
            {
                this->Statement();
            }

            this->Expect(Lexeme::NewLine);

            elseTree->nodes.push_back(this->tree);
            tempTree->nodes.push_back(elseTree);
            this->tree = nullptr;
        }

        this->tree = tempTree;
    }
    else if (this->Accept(Lexeme::Case))
    {
        this->Expect(Lexeme::Identifier);
        this->Expect(Lexeme::Of);
        this->Expect(Lexeme::NewLine);



        std::shared_ptr<ParseTreeNode> tempTree = this->tree;
        this->tree = nullptr;

        while (this->Accept(Lexeme::When))
        {
            if (this->Accept(Lexeme::Integer) || this->Accept(Lexeme::Real) || this->Accept(Lexeme::String))
            {
                this->Expect(Lexeme::Colon);
                this->Block();
            }
            else
            {
                this->Error("Statement: No valid data given to When statement");
            }

            tempTree->nodes.push_back(this->tree);
            this->tree = nullptr;
        }
        if (this->Accept(Lexeme::Otherwise))
        {
            this->Expect(Lexeme::Colon);
            this->Block();
        }
        this->Expect(Lexeme::End);
        this->Expect(Lexeme::Case);

        tempTree->nodes.push_back(this->tree);
        this->tree = tempTree;
    }
    else if (this->Accept(Lexeme::For))
    {
        std::shared_ptr<ParseTreeNode> tempTree = this->tree;
        this->tree = nullptr;

        this->Expect(Lexeme::Identifier);
        this->Expect(Lexeme::Assign);
        if (this->Accept(Lexeme::Identifier) || this->Accept(Lexeme::Integer))
        {
            tempTree->nodes.push_back(this->tree);
            this->tree = nullptr;

            this->Expect(Lexeme::To);
            if (this->Accept(Lexeme::Identifier) || this->Accept(Lexeme::Integer))
            {
                tempTree->nodes.push_back(this->tree);
                this->tree = nullptr;

                if (this->Accept(Lexeme::NewLine))
                {
                    this->Block();
                    tempTree->nodes.push_back(this->tree);
                    this->tree = tempTree;

                    this->Expect(Lexeme::Next);
                    this->Expect(Lexeme::Identifier);
                }
                else
                {
                    this->Statement();
                    tempTree->nodes.push_back(this->tree);
                    this->tree = tempTree;
                }
            }
            else
            {
                this->Error("Invalid range end for FOR loop...");
            }
        }
        else
        {
            this->Error("Invalid range beginning for FOR loop...");
        }
    }
    else if (Accept(Lexeme::While))
    {
        std::shared_ptr<ParseTreeNode> tempTree = this->tree;
        this->tree = nullptr;
        this->Condition();
        tempTree->nodes.push_back(this->tree);
        this->tree = nullptr;

        this->Expect(Lexeme::Do);
        if (this->Accept(Lexeme::NewLine))
        {
            this->Block();
            tempTree->nodes.push_back(this->tree);
            tree = nullptr;
            this->Expect(Lexeme::End);
            //this->Expect(Lexeme::While);
            this->tokenIterator++;
        }
        else
        {
            this->Statement();
        }
        if (tree != nullptr)
        {
            tempTree->nodes.push_back(this->tree);
        }
        this->tree = tempTree;

    }
    else
    {
        if ((tokenIterator != tokens->end()) && (tokenIterator->token != Lexeme::NewLine && tokenIterator->token != Lexeme::End))
        {
            this->Error("Statement: Syntax Error");
        }
    }

    if (masterTree != nullptr)
    {
        masterTree->nodes.push_back(this->tree);
        this->tree = masterTree;
    }
    else
    {
        masterTree = this->tree;
    }
}

void bv::Parser::RecursiveDescent::Block()
{
    std::shared_ptr<ParseTreeNode> masterTree = this->tree;
    this->tree = nullptr;

    std::vector<std::shared_ptr<ParseTreeNode>> blockTrees;

    do
    {
        if (this->Accept(Lexeme::Data))
        {
            std::shared_ptr<ParseTreeNode> tempTree = this->tree;
            this->tree = nullptr;
            do
            {
                this->Expect(Lexeme::Identifier);
                this->Expect(Lexeme::Assign);
                if (this->Accept(Lexeme::Identifier) || this->Accept(Lexeme::Integer) || this->Accept(Lexeme::Real) || this->Accept(Lexeme::String))
                {
                    ;
                }
                else
                {
                    this->Error("Invalid data type passed to data");
                }
            } while (this->Accept(Lexeme::Comma));
            tempTree->nodes.push_back(this->tree);
            this->tree = tempTree;
        }
        else if (this->Accept(Lexeme::Dim))
        {
            std::shared_ptr<ParseTreeNode> tempTree = this->tree;
            this->tree = nullptr;
            do
            {
                this->Expect(Lexeme::Identifier);
                if (this->Accept(Lexeme::Assign))
                {
                    if (this->Accept(Lexeme::Identifier) || this->Accept(Lexeme::Integer) || this->Accept(Lexeme::Real) || this->Accept(Lexeme::String) || this->Accept(Lexeme::Input))
                    {
                        ;
                    }
                    else
                    {
                        this->Error("Invalid data type passed to dim");
                    }
                }
            } while (this->Accept(Lexeme::Comma));
            tempTree->nodes.push_back(this->tree);
            this->tree = tempTree;
        }
        else
        {
            this->Statement();
        }

        std::shared_ptr<ParseTreeNode> tempTree = this->tree;
        this->tree = nullptr;
        if (tempTree != nullptr)
        {
            blockTrees.push_back(tempTree);
        }
    } while (this->Accept(Lexeme::NewLine));

    std::shared_ptr<ParseTreeNode> wholeTree = nullptr;
    for (int i = blockTrees.size() - 1; i > -1; i--)
    {
        if (wholeTree == nullptr)
            wholeTree = blockTrees.at(i);
        else
        {
            std::shared_ptr<ParseTreeNode> temp = wholeTree;
            wholeTree = blockTrees.at(i);
            wholeTree->nodes.push_back(temp);
        }
    }

    if (masterTree == nullptr)
    {
        masterTree = wholeTree;
    }
    else
    {
        masterTree->nodes.push_back(wholeTree);
    }

    this->tree = masterTree;


}

void bv::Parser::RecursiveDescent::Program()
{
    //Space for function declarations here in future. For now, a program is just a block.

    this->Block();
}

void bv::Parser::RecursiveDescent::Error(std::string s)
{
    if (this->tokenIterator == this->tokens->end())
        return;
    std::cout << s << std::endl << "Line " << ((*this->tokenIterator).line + 1) << ", position " << (*this->tokenIterator).position << "." << std::endl;
}