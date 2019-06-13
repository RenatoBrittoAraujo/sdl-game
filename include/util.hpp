#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <string>

class Util
{
public:
    
    static const bool fileExists(const std::string & path);

    static const void debugPrint(const std::string message);
    static const void contextPrint(const std::string message);
    static const void errorPrint(const std::string message);

    static const void setVerbose(bool verbose);

};

#endif