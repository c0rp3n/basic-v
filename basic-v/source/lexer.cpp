#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "IO/FileReader.hpp"
#include "Tokeniser.hpp"



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
                // help text stuff here
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

    Tokeniser tokeniser;

    std::vector<std::string> lines = bv::IO::FileReader::ReadLines(filepath);
    if (lines.size() < 1)
    {
        return 0;
    }

    int lineNumber = 0;
    for (std::string line : lines)
    {
        lineNumber++;
        tokeniser.TokeniseLine(line, lineNumber);
    }

    /*
    <===== Commenting out for now, just for simplicity of testing the rules =====>

    int threadCount = std::thread::hardware_concurrency();
    int linesPerThread = lines.size() / threadCount;
    std::vector<std::thread> threads;
    threads.reserve(threadCount);
    for (int i = 0; i < threadCount; i++)
    {
        threads.push_back(std::thread());
    }

    for (std::thread &t : threads)
    {
        t.join();
    }

    */


    return 0;
}