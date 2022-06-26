#include "file.hpp"

#include <fstream>
#include <sstream>

std::string File::read_file(const std::string& path)
{
    std::ifstream file(path);
    std::stringstream buffer;

    buffer << file.rdbuf();
    return buffer.str();
}