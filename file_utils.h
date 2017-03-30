#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <boost/filesystem.hpp>

namespace file_utils
{
    void constructCsvFileVector(std::string filePath, std::vector< std::vector<std::string> >& vec, std::vector<std::string>& headers);
    std::vector<std::string> listFilesInDir(std::string& inputPath);
    std::string getFileName(const std::string& inputPath);
    std::string getFileExt(const std::string& inputPath);
}

#endif // FILE_UTILS_H
