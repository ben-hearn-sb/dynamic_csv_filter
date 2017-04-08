#ifndef FILE_UTILS_H
#define FILE_UTILS_H

//#include <fstream>
//#include <regex>
//#include <iostream>
#include <istream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
class QString;

namespace file_utils
{
    void constructCsvFileVector(std::string filePath, std::vector< std::vector<std::string> >& vec, std::vector<std::string>& headers);
    std::vector<std::string> listFilesInDir(std::string& inputPath);
    std::string getFileName(const std::string& inputPath);
    std::string getFileExt(const std::string& inputPath);
    std::string openFile();
    void saveFile(QString& inData);
    std::istream& safeGetline(std::istream& is, std::string& t);
}

#endif // FILE_UTILS_H
