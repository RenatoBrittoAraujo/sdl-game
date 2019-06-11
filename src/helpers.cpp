#include "helpers.hpp"

#include <string>
#include <fstream>

bool fileExists(const std::string & path)
{
    std::ifstream file;
    file.open(path);
    return file.good();
}