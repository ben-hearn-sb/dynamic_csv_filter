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

void qt_utils::setTableHeaders(QStandardItemModel* inputModel, QStringList& headers)
{
    inputModel->setHorizontalHeaderLabels(headers);
}

void createInfoBox(const QString& message, const QString& errorString)
{
    QMessageBox::information(NULL, message, errorString);
}
