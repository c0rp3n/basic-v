#include "RecursiveDescent.hpp"

#include <iostream>

void bv::Parser::RecursiveDescent::Parse(std::vector<Token>* tokens)
{
    this->tokens = tokens;
    tokenIterator = tokens->begin();
    program();
    system("pause");
}

bool bv::Parser::RecursiveDescent::accept(Lexeme l)
{
    if (tokenIterator == tokens->end())
        return false;
    if (tokenIterator->token == l) {
        addToTree();
        tokenIterator++;
        return true;
    }
    return false;
}

bool bv::Parser::RecursiveDescent::expect(Lexeme l)
{
    if (accept(l))
        return true;
    error("expect: unexpected symbol");
    return false;
}

void bv::Parser::RecursiveDescent::addToTree()
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

void bv::Parser::RecursiveDescent::factor()
{
    if (accept(Lexeme::Identifier) || accept(Lexeme::Real) || accept(Lexeme::Integer))
    {
        ;
    }
    else if (accept(Lexeme::OpenBracket))
    {
        expression();
        expect(Lexeme::CloseBracket);
    }
    else {
        error("factor: syntax error");
        tokenIterator++;
    }
}

void bv::Parser::RecursiveDescent::term()
{
    factor();
    while (accept(Lexeme::Multiply) || accept(Lexeme::Divide))
    {
        factor();
    }
}

void bv::Parser::RecursiveDescent::expression()
{
    if (accept(Lexeme::Addition) || accept(Lexeme::Subtraction))
    {
        ;
    }
    term();
    while (accept(Lexeme::Addition) || accept(Lexeme::Subtraction))
    {
        term();
    }
}

void bv::Parser::RecursiveDescent::condition()
{
    if (accept(Lexeme::Not))
    {
        factor();
    }
    else
    {
        expression();
        std::shared_ptr<ParseTreeNode> lhs = tree;
        tree = nullptr;

        if (accept(Lexeme::Equal) || accept(Lexeme::NotEqual) || accept(Lexeme::LessThan) || accept(Lexeme::LessThanOrEqual) || accept(Lexeme::GreaterThan) || accept(Lexeme::GreaterThanOrEqual))
        {
            tree->nodes.push_back(lhs);
            std::shared_ptr<ParseTreeNode> tempTree = tree;
            tree = nullptr;
            expression();
            tempTree->nodes.push_back(tree);
            tree = tempTree;
        }
        else
        {
            error("condition: invalid operator");
        }
    }
}

void bv::Parser::RecursiveDescent::statement()
{
    std::shared_ptr<ParseTreeNode> masterTree = tree;
    tree = nullptr;

    if (accept(Lexeme::Identifier))
    {
        expect(Lexeme::Assign);
        if (!accept(Lexeme::String))
        {
            std::shared_ptr<ParseTreeNode> tree2 = tree;
            tree = nullptr;
            expression();
            tree2->nodes.push_back(tree);
            tree = tree2;
        }
    }
    else if (accept(Lexeme::If))
    {
        std::shared_ptr<ParseTreeNode> tempTree = tree;
        tree = nullptr;
        condition();
        tempTree->nodes.push_back(tree);
        tree = nullptr;

        expect(Lexeme::Then);
        if (accept(Lexeme::NewLine))
        {
            
            block();
            tempTree->nodes.push_back(tree);
            tree = tempTree;

            expect(Lexeme::End);
            expect(Lexeme::If);
        }
        else
        {
            statement();
        }

        tempTree->nodes.push_back(tree);
        tree = tempTree;
        
    }
    else if (accept(Lexeme::Case))
    {
        expect(Lexeme::Identifier);
        expect(Lexeme::Of);
        expect(Lexeme::NewLine);



        std::shared_ptr<ParseTreeNode> tempTree = tree;
        tree = nullptr;

        while (accept(Lexeme::When))
        {
            if (accept(Lexeme::Integer) || accept(Lexeme::Real) || accept(Lexeme::String))
            {
                expect(Lexeme::Colon);
                block();
            }
            else
            {
                error("Statement: No data given to When statement");
            }

            tempTree->nodes.push_back(tree);
            tree = nullptr;
        }
        if (accept(Lexeme::Otherwise))
        {
            expect(Lexeme::Colon);
            block();
        }
        expect(Lexeme::End);
        expect(Lexeme::Case);

        tempTree->nodes.push_back(tree);
        tree = tempTree;
    }
    else if (accept(Lexeme::For))
    {
        std::shared_ptr<ParseTreeNode> tempTree = tree;
        tree = nullptr;

        expect(Lexeme::Identifier);
        expect(Lexeme::Assign);
        if (accept(Lexeme::Identifier) || accept(Lexeme::Integer))
        {
            tempTree->nodes.push_back(tree);
            tree = nullptr;

            expect(Lexeme::To);
            if(accept(Lexeme::Identifier) || accept(Lexeme::Integer))
            {
                tempTree->nodes.push_back(tree);
                tree = nullptr;

                if (accept(Lexeme::NewLine))
                {
                    block();
                    tempTree->nodes.push_back(tree);
                    tree = tempTree;

                    expect(Lexeme::Next);
                    expect(Lexeme::Identifier);
                }
                else
                {
                    statement();
                    tempTree->nodes.push_back(tree);
                    tree = tempTree;
                }
            }
            else
            {
                error("Invalid range end for FOR loop...");
            }
        }
        else
        {
            error("Invalid range beginning for FOR loop...");
        }
    }
    else if (accept(Lexeme::While))
    {
        std::shared_ptr<ParseTreeNode> tempTree = tree;
        tree = nullptr;
        condition();
        tempTree->nodes.push_back(tree);
        tree = nullptr;

        expect(Lexeme::Do);
        if (accept(Lexeme::NewLine))
        {
            block();
            expect(Lexeme::End);
            expect(Lexeme::While);
        }
        else
        {
            statement();
        }
        tempTree->nodes.push_back(tree);
        tree = tempTree;

    }
    else
    {
        error("Statement: Syntax Error");
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

void bv::Parser::RecursiveDescent::block()
{
    std::shared_ptr<ParseTreeNode> masterTree = tree;
    tree = nullptr;

    std::vector<std::shared_ptr<ParseTreeNode>> blockTrees;

    do
    {
        if (accept(Lexeme::Data))
        {
            std::shared_ptr<ParseTreeNode> tempTree = tree;
            tree = nullptr;
            do
            {
                expect(Lexeme::Identifier);
                expect(Lexeme::Assign);
                if (accept(Lexeme::Identifier) || accept(Lexeme::Integer) || accept(Lexeme::String))
                {
                    ;
                }
                else
                {
                    error("Invalid data type...");
                }
            } while (accept(Lexeme::Comma));
            tempTree->nodes.push_back(tree);
            tree = tempTree;
        }
        else if (accept(Lexeme::Dim))
        {
            std::shared_ptr<ParseTreeNode> tempTree = tree;
            tree = nullptr;
            do
            {
                expect(Lexeme::Identifier);
                if (accept(Lexeme::Assign))
                {
                    if (accept(Lexeme::Identifier) || accept(Lexeme::Integer) || accept(Lexeme::String))
                    {
                        ;
                    }
                    else
                    {
                        error("Invalid data type...");
                    }
                }
            } while (accept(Lexeme::Comma));
            tempTree->nodes.push_back(tree);
            tree = tempTree;
        }
        else
        {
            statement();
        }

        std::shared_ptr<ParseTreeNode> tempTree = tree;
        tree = nullptr;
        blockTrees.push_back(tempTree);
    } while (accept(Lexeme::NewLine));

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

void bv::Parser::RecursiveDescent::program()
{
    block();
}

void bv::Parser::RecursiveDescent::error(std::string s)
{
    std::cout << s;
}