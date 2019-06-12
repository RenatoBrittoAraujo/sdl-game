#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <string>

static bool _verbose = false;

bool fileExists(const std::string & path);

void debugPrint(const std::string message = "EMPTY MESSAGE");
void contextPrint(const std::string message = "EMPTY MESSAGE");
void errorPrint(const std::string message = "ERROR UNDEFINED");

void setVerbose(bool verbose); 

#endif