#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "IO/FileReader.hpp"
#include "Lexer/Tokeniser.hpp"



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

    std::vector<std::string> lines = bv::IO::FileReader::ReadLines(filepath);
    if (lines.size() < 1)
    {
        return 0;
    }

    std::vector<bv::Token> tokens;
    {
        std::vector<std::vector<bv::Token>> threadTokens;

        // Thread creation and consequent wait.
        {
            uint32_t threadCount = std::thread::hardware_concurrency();
            uint32_t linesPerThread = lines.size() / threadCount;
            threadTokens.reserve(threadCount);

            std::vector<std::thread> threads;
            threads.reserve(threadCount);

            for (int i = 0; i < threadCount - 1; i++)
            {
                threadTokens.push_back(std::vector<bv::Token>());
                threads.push_back(std::thread(bv::Lexer::Tokeniser::TokeniseLines, lines[i * linesPerThread], lines[(i + 1) * linesPerThread], threadTokens[i]));
            }
            threadTokens.push_back(std::vector<bv::Token>());
            threads.push_back(std::thread(bv::Lexer::Tokeniser::TokeniseLines, lines[(threadCount - 1) * linesPerThread], lines.end(), threadTokens[threadCount - 1]));

            for (std::thread &t : threads)
            {
                t.join();
            }
        }

        {
            int tokenCount = 0;
            for (std::vector<bv::Token>& v : threadTokens)
            {
                tokenCount += v.size();
            }

            tokens.reserve(tokenCount);
        }

        for (std::vector<bv::Token>& v : threadTokens)
        {
            for (bv::Token& t : v)
            {
                tokens.push_back(t);
            }
        }
    }


    return 0;
}