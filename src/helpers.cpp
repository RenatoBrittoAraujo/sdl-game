#include "helpers.hpp"

#include <string>
#include <fstream>
#include <unistd.h>

bool fileExists(const std::string & path)
{
    return ( access( path.c_str(), F_OK ) != -1 );
}