#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace bv
{
    namespace IO
    {
        static class FileReader
        {
        public:
            /// <summary>
            /// Parses all of the lines in a file.
            /// </summary>
            /// <param name="filepath">Path to the file including name and extension.</param>
            /// <returns>A vector of each line in the file.</returns>
            static std::vector<std::string> ReadLines(std::string filepath)
            {
                std::vector<std::string> lines;
                std::string data;
                {
                    std::ifstream ifs(filepath);
                    data = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
                }

                std::vector<uint64_t> lineLengths;
                {
                    uint64_t lineLength = 0;
                    for (const char& value : data)
                    {
                        if (value == '\n')
                        {
                            lineLengths.push_back(lineLength);
                            lineLength = 0;
                        }
                        else
                        {
                            lineLength++;
                        }
                    }
                }

                {
                    uint64_t pointer = 0;
                    for (uint64_t& i : lineLengths)
                    {
                        const std::string line = data.substr(pointer, i);
                        lines.push_back(line);

                        pointer += i;
                    }
                }

                lineLengths.clear();

                return lines;
            }
        };
    }
}
