#include "general_utils.h"

std::vector<const char*> general_utils::convertToConstCharVec(std::vector<std::string>& vs)
{
    // Converts a std::string vector to a char* vector
    std::vector<const char*> vc;
    std::transform(vs.begin(), vs.end(), std::back_inserter(vc), convertToCharStar);
    return vc;
}

const char* general_utils::convertToCharStar(const std::string & s)
{
    // Necessary function for the above convertToConstCharVec to work
    return s.c_str();
}
