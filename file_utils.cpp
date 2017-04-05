#include "file_utils.h"
#include "qt_utils.h"

#include <QtCore/QTextStream>
#include <QObject>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QIODevice>
#include <QDebug>
#include <QString>

#include <sstream>
#include <windows.h>
namespace fs = boost::filesystem;

void file_utils::constructCsvFileVector(std::string filePath, std::vector<std::vector<std::string>>& lineData, std::vector<std::string>& headers)
{
    // Constructs a multi-vector out of a csv file
    std::ifstream file(filePath); // declare file stream
    std::string line;
    int numOfColumns = 0;
    int numOfLines= 0;

    // Run through each line of the CSV file and split at the newline separator
    // TODO: Fix this to handle bth \r and \n newline terminators
    while (std::getline(file, line, '\r'))
    {
        numOfColumns = 0;
        ++numOfLines;
        const char *mystart = line.c_str();
        bool instring{ false };
        for (const char* p = mystart; *p; ++p) // Iterate through each character
        {
            if (*p == '"') // toggle flag if we're btw double quote
            {
                instring = !instring;
            }
            // We need to check for an empty string and a comma. The empty string is the last value in our mystart variable
            else if ((*p == ',' && !instring))
            {
                ++numOfColumns;
                if (numOfLines == 1)
                {
                    // On each field delimiter "," we add a new column indicating a new field
                    // Only needs doing once hence if line == 1
                    lineData.resize(numOfColumns);
                    headers.push_back(std::string(mystart, p - mystart));
                }
                else
                {
                    lineData[numOfColumns - 1].push_back(std::string(mystart, p - mystart)); // If comma is outside double quote keep the field
                }
                mystart = p + 1;
            }
        }
        // End of the mystart char array delimited by end of line instead of , so we need to account for that
        ++numOfColumns;
        if(numOfLines == 1)
        {
            lineData.resize(numOfColumns);
            headers.push_back(std::string(mystart));
        }
        else
        {
            lineData[numOfColumns - 1].push_back(std::string(mystart));
        }
    }
}

// List files in a single layered directory
std::vector<std::string> file_utils::listFilesInDir(std::string & inputPath)
{
    // Iterates a directory and lists all the files. Not currelty recursive
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
    // Gets the name of a file
    fs::path p(inputPath);
    return p.stem().string();
}

std::string file_utils::getFileExt(const std::string & inputPath)
{
    // gets the extension of a file
    fs::path p(inputPath);
    return p.filename().extension().string();
}

std::string file_utils::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, QObject::tr("Open CSV file"),
                                                    "C:/Users/Ben/Desktop/sample_csv_data",
                                                    QObject::tr("text files (*.csv *.txt)"));
    if (fileName.isEmpty())
    {
        return "";
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(NULL, QObject::tr("Unable to open file"), file.errorString());
            //const char* errorMessage = "Error biatch";
            //qt_utils::createInfoBox(QString::fromStdString("Unable to open file"), file.errorString());
            //qt_utils::createInfoBox(errorMessage, file.errorString());
            return "";
        }
        return fileName.toStdString();
    }
}
