#include "file_loader.hpp"

// Include standard headers
#include <fstream>  // std::ifstream
#include <iostream> // std::cout, std::cin, std::cerr
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <string>   // std::string

namespace file
{
    std::string slurp(const std::string file_path)
    {
        // inspired by http://stackoverflow.com/questions/116038/what-is-the-best-way-to-slurp-a-file-into-a-stdstring-in-c/116220#116220
        std::cout << "Loading file " << file_path << " into memory.\n";

        std::ifstream input_stream(file_path.c_str());
        std::stringstream file_buffer;
        file_buffer << input_stream.rdbuf();
        std::string file_contents_string = file_buffer.str();
        return file_contents_string;
    }
}