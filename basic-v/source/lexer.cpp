#include <iostream>
#include <string>
#include <vector>

#include "../../Libs/mio/single_include/mio/mio.hpp"

#include "IO/FileReader.hpp"

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

    std::vector<std::string> lines = bv::IO::FileReader::ReadLines(filepath);
}
