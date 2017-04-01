#include "general_utils.h"

std::vector<std::string> general_utils::extractHeaders(std::vector<std::vector<std::string>>& inputVec)
{
    // Not used but useful to keep around for reference
    std::vector<std::vector<std::string>>::iterator row;
    std::vector<std::string>::iterator col;
    std::vector<std::string> headers;
    int firstElement = 0;

    for (row = inputVec.begin(); row != inputVec.end(); ++row)
    {
        col = row->begin(); // Get the first element of the vector
        headers.push_back(*col);
    }
    return headers;
}

std::vector<const char*> general_utils::convertToConstCharVec(std::vector<std::string>& vs)
{
    std::vector<const char*> vc;
    std::transform(vs.begin(), vs.end(), std::back_inserter(vc), convertToCharStar);
    return vc;
}

const char* general_utils::convertToCharStar(const std::string & s)
{
    return s.c_str();
}
