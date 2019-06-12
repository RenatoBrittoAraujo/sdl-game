#include "helpers.hpp"
#include "globals.hpp"

#include <string>
#include <fstream>
#include <iostream>

bool fileExists(const std::string & path)
{
    std::ifstream file;
    file.open(path);
    return file.good();
}

void debugPrint(const std::string message)
{
    if(_verbose)
        std::cout<<"[DEBUG] "<<message<<std::endl;
}

void contextPrint(const std::string message)
{
    if(_verbose)
        std::cout<<"[CONTEXT] "<<message<<std::endl;
}

void errorPrint(const std::string message)
{
    std::cout<<"[ERROR] "<<message<<std::endl;
}

void setVerbose(bool verbose)
{
    _verbose = verbose;
}