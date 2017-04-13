#ifndef FILE_UTILS_H
#define FILE_UTILS_H

//#include <fstream>
//#include <regex>
//#include <iostream>
#include <istream>
#include <string>
#include <vector>
class QString;

namespace file_utils
{
    void constructCsvFileVector(std::string filePath, std::vector< std::vector<std::string> >& vec, std::vector<std::string>& headers);
    std::string openFile();
    void saveFile(QString& inData);
    std::istream& safeGetline(std::istream& is, std::string& t);
}

#endif // FILE_UTILS_H
