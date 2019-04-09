#include "RecursiveDescent.hpp"

#include <iostream>

void bv::Parser::RecursiveDescent::Parse(std::vector<Token>* tokens)
{
    this->tokens = tokens;
    tokenIterator = tokens->begin();
    Program();
}

bool bv::Parser::RecursiveDescent::Accept(Lexeme l)
{
    if (tokenIterator == tokens->end())
        return false;
    if (tokenIterator->token == l) {
        AddToTree();
        tokenIterator++;
        return true;
    }
    return false;
}

bool bv::Parser::RecursiveDescent::Expect(Lexeme l)
{
    if (Accept(l))
        return true;
    Error("expect: unexpected symbol");
    return false;
}

void bv::Parser::RecursiveDescent::AddToTree()
{
    Lexeme t = tokenIterator->token;
    if (t == Lexeme::OpenBracket || t == Lexeme::CloseBracket || t == Lexeme::NewLine || t == Lexeme::Then || t == Lexeme::End || t == Lexeme::Of || t == Lexeme::Colon || t == Lexeme::Do || t == Lexeme::Next)
        return;

    std::shared_ptr<ParseTreeNode> node(new ParseTreeNode(*tokenIterator));

    //If tree is empty, make this the root node
    if (tree == nullptr)
    {
        tree = node;
    }

    else if (t == Lexeme::If || t == Lexeme::Case || (t == Lexeme::Identifier && tree->token.token == Lexeme::For))
        return;

    else if (t == Lexeme::Assign)
    {
        node->nodes.push_back(tree);
        tree = node;
    }
    else if (tree->token.token == Lexeme::Case || tree->token.token == Lexeme::When)
    {
        tree->nodes.push_back(node);
    }



    //Expression rules
    
    else if (tree->nodes.size() == 2)
    {
        node->nodes.push_back(tree);
        tree = node;
    }
    //If node has no lhs, push tree to lhs
    else if (tree->nodes.size() < 1)
    {
        node->nodes.push_back(tree);
        tree = node;
    }
    //Otherwise push to rhs of tree
    else
    {
        tree->nodes.push_back(node);
    }
}

void bv::Parser::RecursiveDescent::Factor()
{
    if (Accept(Lexeme::Identifier) || Accept(Lexeme::Real) || Accept(Lexeme::Integer))
    {
        ;
    }
    else if (Accept(Lexeme::OpenBracket))
    {
        Expression();
        Expect(Lexeme::CloseBracket);
    }
    else {
        Error("factor: syntax error");
        tokenIterator++;
    }
}

void bv::Parser::RecursiveDescent::Term()
{
    Factor();
    while (Accept(Lexeme::Multiply) || Accept(Lexeme::Divide))
    {
        Factor();
    }
}

void bv::Parser::RecursiveDescent::Expression()
{
    if (Accept(Lexeme::Addition) || Accept(Lexeme::Subtraction))
    {
        ;
    }
    Term();
    while (Accept(Lexeme::Addition) || Accept(Lexeme::Subtraction))
    {
        Term();
    }
}

void bv::Parser::RecursiveDescent::Condition()
{
    if (Accept(Lexeme::Not))
    {
        Factor();
    }
    else
    {
        Expression();
        std::shared_ptr<ParseTreeNode> lhs = tree;
        tree = nullptr;

        if (Accept(Lexeme::Equal) || Accept(Lexeme::NotEqual) || Accept(Lexeme::LessThan) || Accept(Lexeme::LessThanOrEqual) || Accept(Lexeme::GreaterThan) || Accept(Lexeme::GreaterThanOrEqual))
        {
            tree->nodes.push_back(lhs);
            std::shared_ptr<ParseTreeNode> tempTree = tree;
            tree = nullptr;
            Expression();
            tempTree->nodes.push_back(tree);
            tree = tempTree;
        }
        else
        {
            Error("condition: invalid operator");
        }
    }
}

void bv::Parser::RecursiveDescent::Statement()
{
    std::shared_ptr<ParseTreeNode> masterTree = tree;
    tree = nullptr;

    if (Accept(Lexeme::Identifier))
    {
        Expect(Lexeme::Assign);
        if (!Accept(Lexeme::String))
        {
            std::shared_ptr<ParseTreeNode> tree2 = tree;
            tree = nullptr;
            Expression();
            tree2->nodes.push_back(tree);
            tree = tree2;
        }
    }
    else if (Accept(Lexeme::If))
    {
        std::shared_ptr<ParseTreeNode> tempTree = tree;
        tree = nullptr;
        Condition();
        tempTree->nodes.push_back(tree);
        tree = nullptr;

        Expect(Lexeme::Then);
        if (Accept(Lexeme::NewLine))
        {
            
            Block();
            tempTree->nodes.push_back(tree);
            tree = tempTree;

            Expect(Lexeme::End);
            Expect(Lexeme::If);
        }
        else
        {
            Statement();
        }

        tempTree->nodes.push_back(tree);
        tree = tempTree;
        
    }
    else if (Accept(Lexeme::Case))
    {
        Expect(Lexeme::Identifier);
        Expect(Lexeme::Of);
        Expect(Lexeme::NewLine);



        std::shared_ptr<ParseTreeNode> tempTree = tree;
        tree = nullptr;

        while (Accept(Lexeme::When))
        {
            if (Accept(Lexeme::Integer) || Accept(Lexeme::Real) || Accept(Lexeme::String))
            {
                Expect(Lexeme::Colon);
                Block();
            }
            else
            {
                Error("Statement: No valid data given to When statement");
            }

            tempTree->nodes.push_back(tree);
            tree = nullptr;
        }
        if (Accept(Lexeme::Otherwise))
        {
            Expect(Lexeme::Colon);
            Block();
        }
        Expect(Lexeme::End);
        Expect(Lexeme::Case);

        tempTree->nodes.push_back(tree);
        tree = tempTree;
    }
    else if (Accept(Lexeme::For))
    {
        std::shared_ptr<ParseTreeNode> tempTree = tree;
        tree = nullptr;

        Expect(Lexeme::Identifier);
        Expect(Lexeme::Assign);
        if (Accept(Lexeme::Identifier) || Accept(Lexeme::Integer))
        {
            tempTree->nodes.push_back(tree);
            tree = nullptr;

            Expect(Lexeme::To);
            if(Accept(Lexeme::Identifier) || Accept(Lexeme::Integer))
            {
                tempTree->nodes.push_back(tree);
                tree = nullptr;

                if (Accept(Lexeme::NewLine))
                {
                    Block();
                    tempTree->nodes.push_back(tree);
                    tree = tempTree;

                    Expect(Lexeme::Next);
                    Expect(Lexeme::Identifier);
                }
                else
                {
                    Statement();
                    tempTree->nodes.push_back(tree);
                    tree = tempTree;
                }
            }
            else
            {
                Error("Invalid range end for FOR loop...");
            }
        }
        else
        {
            Error("Invalid range beginning for FOR loop...");
        }
    }
    else if (Accept(Lexeme::While))
    {
        std::shared_ptr<ParseTreeNode> tempTree = tree;
        tree = nullptr;
        Condition();
        tempTree->nodes.push_back(tree);
        tree = nullptr;

        Expect(Lexeme::Do);
        if (Accept(Lexeme::NewLine))
        {
            Block();
            Expect(Lexeme::End);
            Expect(Lexeme::While);
        }
        else
        {
            Statement();
        }
        tempTree->nodes.push_back(tree);
        tree = tempTree;

    }
    else
    {
        Error("Statement: Syntax Error");
    }

    if (masterTree != nullptr)
    {
        masterTree->nodes.push_back(tree);
        tree = masterTree;
    }
    else
    {
        masterTree = tree;
    }
}

void bv::Parser::RecursiveDescent::Block()
{
    std::shared_ptr<ParseTreeNode> masterTree = tree;
    tree = nullptr;

    std::vector<std::shared_ptr<ParseTreeNode>> blockTrees;

    do
    {
        if (Accept(Lexeme::Data))
        {
            std::shared_ptr<ParseTreeNode> tempTree = tree;
            tree = nullptr;
            do
            {
                Expect(Lexeme::Identifier);
                Expect(Lexeme::Assign);
                if (Accept(Lexeme::Identifier) || Accept(Lexeme::Integer) || Accept(Lexeme::String))
                {
                    ;
                }
                else
                {
                    Error("Invalid data type passed to data");
                }
            } while (Accept(Lexeme::Comma));
            tempTree->nodes.push_back(tree);
            tree = tempTree;
        }
        else if (Accept(Lexeme::Dim))
        {
            std::shared_ptr<ParseTreeNode> tempTree = tree;
            tree = nullptr;
            do
            {
                Expect(Lexeme::Identifier);
                if (Accept(Lexeme::Assign))
                {
                    if (Accept(Lexeme::Identifier) || Accept(Lexeme::Integer) || Accept(Lexeme::String))
                    {
                        ;
                    }
                    else
                    {
                        Error("Invalid data type passed to dim");
                    }
                }
            } while (Accept(Lexeme::Comma));
            tempTree->nodes.push_back(tree);
            tree = tempTree;
        }
        else
        {
            Statement();
        }

        std::shared_ptr<ParseTreeNode> tempTree = tree;
        tree = nullptr;
        blockTrees.push_back(tempTree);
    } while (Accept(Lexeme::NewLine));

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

    tree = masterTree;


}

void bv::Parser::RecursiveDescent::Program()
{
    //Space for function declarations here in future. For now, a program is just a block.

    Block();
}

void bv::Parser::RecursiveDescent::Error(std::string s)
{
    std::cout << s << std::endl << "Line " << (*tokenIterator).line << ", position " << (*tokenIterator).position << ".";
}