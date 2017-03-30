#ifndef GENERAL_UTILS_H
#define GENERAL_UTILS_H

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

namespace general_utils
{
    std::vector<std::string> extractHeaders(std::vector<std::vector<std::string>>& inputVec);
    std::vector<const char*> convertToConstCharVec(std::vector<std::string>& vs);
    const char* convertToCharStar(const std::string & s);

    /*template<typename Out>
    void split(const std::string &s, char delim, Out result);
    std::vector<std::string> split(const std::string &s, char delim);*/
}

#endif
