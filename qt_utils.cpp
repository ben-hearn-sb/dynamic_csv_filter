#include "qt_utils.h"
#include "general_utils.h"

#include <QDebug>
#include <QStringList>
#include <QTableWidget>
#include <QTableView>
#include <QHeaderView>
#include <QStringList>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QString>

QStringList qt_utils::convertToQStringList(std::vector<char*> inputVec)
{
    QVector<char*> qVec = QVector<char*>::fromStdVector(inputVec); //Convert first to QVector type
    QStringList list;
    foreach(const char* str, qVec)
    {
        list << str;
    }
    return list;
}

QStringList qt_utils::convertToQStringList(std::vector<std::string> inputVec)
{
    std::vector<const char*> constCharVec = general_utils::convertToConstCharVec(inputVec);
    QVector<const char*> qVec = QVector<const char*>::fromStdVector(constCharVec); //Convert first to QVector type
    QStringList list;
    foreach(const char* str, qVec)
    {
        list << str;
    }
    return list;
}

void qt_utils::stretchAllColumns(QTableWidget* inputTable)
{
    for (int col = 0; col < inputTable->columnCount(); ++col)
    {
        inputTable->horizontalHeader()->setSectionResizeMode(col, QHeaderView::Stretch);
    }
}

void qt_utils::stretchAllColumns(QTableView* inputTable)
{
    QAbstractItemModel* tableModel=  inputTable->model();
    //int iRows = tableModel->rowCount();
    int iCols = tableModel->columnCount();
    for (int col = 0; col < iCols; ++col)
    {
        inputTable->horizontalHeader()->setSectionResizeMode(col, QHeaderView::Stretch);
    }
}

void qt_utils::resizeRowsToContents(QTableWidget* inputTable)
{
    inputTable->resizeRowsToContents();
}

void qt_utils::createInfoBox(const QString& message, const QString& errorString)
{
    // Generic use info box
    QMessageBox::information(NULL, message, errorString);
}

QString qt_utils::collectTableInfoInStr(QStandardItemModel* inputModel)
{
    // Collects all the data from the model
    QString textData;
    int rows = inputModel->rowCount();
    int columns = inputModel->columnCount();
    //TODO: Collect the headers of the model too

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {

                textData += inputModel->data(inputModel->index(i,j)).toString();
                textData += ", ";     // for .csv file format
        }
        textData += "\n";             // (optional: for new line segmentation)
    }
    return textData;
}

QString qt_utils::collectTableInfoInStr(QStandardItemModel* inputModel, std::vector<int>& filteredIndexes)
{
    // Collects all the data from the model
    QString textData;
    int columnCount = inputModel->columnCount();
    for (std::vector<int>::iterator itRow = filteredIndexes.begin() ; itRow != filteredIndexes.end(); ++itRow)
    {
        for (int col = 0; col < columnCount; ++col)
        {
            textData += inputModel->data(inputModel->index(*itRow,col)).toString();
            if(col < columnCount-1)
            {
                textData += ", ";     // for .csv file format
            }
        }
        textData += "\n";
    }
    return textData;
}

void qt_utils::setTableHeaders(QStandardItemModel* inputModel, QStringList& headers)
{
    inputModel->setHorizontalHeaderLabels(headers);
}

QString qt_utils::getTableHeadersInStr(QStandardItemModel* inputModel)
{
    int iCols = inputModel->columnCount();
    QString headerLabels;
    for (int col = 0; col < iCols; ++col)
    {
        headerLabels += inputModel->headerData(col, Qt::Horizontal, Qt::DisplayRole).toString();
        if(col < iCols-1)
        {
            headerLabels += ", "; // For CSV data
        }
    }
    return headerLabels;
}
