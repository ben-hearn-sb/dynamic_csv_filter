#include "file_utils.h"
#include <sstream>
#include <QtCore/QTextStream>
#include <windows.h>
namespace fs = boost::filesystem;

// Constructs a multi-vector out of a csv file
void file_utils::constructCsvFileVector(std::string filePath, std::vector<std::vector<std::string>>& lineData, std::vector<std::string>& headers)
{
    std::ifstream file(filePath); // declare file stream
    std::string line;
    std::string splitLine;
    int numOfColumns = 0;
    int numOfLines= 0;
    int currentColNum = 0;
    std::regex rgx("\"([^\"]*)\"");

    // Run through each line of the CSV file and split at the newline separator
    while (std::getline(file, line, '\r'))
    {
        numOfColumns = 0;
        ++numOfLines;

        const char *mystart = line.c_str();
        bool instring{ false };
        for (const char* p = mystart; *p; p++)
        {
            if (*p == '"') // toggle flag if we're btw double quote
            {
                instring = !instring;
            }
            else if (*p == ',' && !instring)
            {
                ++numOfColumns;
                if (numOfLines == 1)
                {
                    // On each field delimiter "," we add a new column indicating a new field
                    // Only needs doing once
                    lineData.resize(numOfColumns);
                }

                if (numOfLines == 1)
                {
                    // Only push back first line of fields to headers
                    headers.push_back(std::string(mystart, p - mystart));
                }
                else
                {
                    lineData[numOfColumns - 1].push_back(std::string(mystart, p - mystart)); // If comma is outside double quote keep the field
                }
                mystart = p + 1;
            }
        }
    }
}

// List files in a single layered directory
std::vector<std::string> file_utils::listFilesInDir(std::string & inputPath)
{
    std::vector<std::string> file_paths = std::vector<std::string>();

    if (!inputPath.empty())
    {
        fs::path apk_path(inputPath);
        fs::recursive_directory_iterator end;

        for (fs::recursive_directory_iterator i(apk_path); i != end; ++i)
        {
            const fs::path cp = (*i);
            file_paths.push_back(cp.string());
        }
    }
    return file_paths;
}

std::string file_utils::getFileName(const std::string& inputPath)
{
    fs::path p(inputPath);
    return p.stem().string();
}

std::string file_utils::getFileExt(const std::string & inputPath)
{
    fs::path p(inputPath);
    return p.filename().extension().string();
}
