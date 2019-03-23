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
                // Open the File
                std::ifstream in(filepath.c_str());

                // Check if object is valid
                if (!in)
                {
                    std::cerr << "Cannot open the File : " << filepath << std::endl;
                }

                std::string str;
                // Read the next line from File untill it reaches the end.
                while (std::getline(in, str))
                {
                    // Line contains string of length > 0 then save it in vector
                    if (str.size() > 0)
                        lines.push_back(str);
                }
                //Close The File
                in.close();

                return lines;
            }
        };
    }
}
