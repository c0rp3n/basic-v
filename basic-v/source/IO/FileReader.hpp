#pragma once

#include <string>
#include <vector>

#include "../../../Libs/mio/single_include/mio/mio.hpp"

namespace bv
{
    namespace IO
    {
        static class FileReader
        {
        public:
            static std::vector<std::string> ReadLines(std::string filepath)
            {
                std::vector<std::string> lines;
                std::string data;
                {
                    mio::mmap_source mmap(filepath);
                    data = std::string(mmap.data);
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
