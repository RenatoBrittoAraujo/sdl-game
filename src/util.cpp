#include "util.hpp"
#include "globals.hpp"

#include <string>
#include <fstream>
#include <iostream>

#include "globals.hpp"
 
const bool Util::fileExists(const std::string & path)
{
    std::ifstream file;
    file.open(path);
    return file.good();
}

const void Util::debugPrint(const std::string message)
{
    if(globals::_verbose)
        std::cout<<"[DEBUG] "<<message<<std::endl;
}

const void Util::contextPrint(const std::string message)
{
    if(globals::_verbose)
        std::cout<<"[CONTEXT] "<<message<<std::endl;
}

const void Util::errorPrint(const std::string message)
{
    std::cout<<"[ERROR] "<<message<<std::endl;
}

const void Util::setVerbose(bool verbose)
{
    globals::_verbose = verbose;
}


