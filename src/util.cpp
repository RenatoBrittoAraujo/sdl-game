#include "util.hpp"
#include "globals.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

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

unsigned int Util::split(const std::string & text, std::vector<std::string> & strings, char ch)
{
    int pos = text.find(ch);
    int initialPos = 0;
    strings.clear();

    while(pos != std::string::npos)
    {
        strings.push_back(text.substr(initialPos, pos - initialPos + 1));
        initialPos = pos + 1;
        pos = text.find(ch, initialPos);
    }

    strings.push_back(text.substr(initialPos, std::min<int>(pos, text.size() - (initialPos + 1))));

    return strings.size();   
}


