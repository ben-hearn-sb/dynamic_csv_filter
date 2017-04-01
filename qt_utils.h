#ifndef QT_UTILS_H
#define QT_UTILS_H

class QHeaderView;
class QTableView;
class QTableWidget;
class QStringList;
class QStandardItemModel;

#include <vector>

namespace qt_utils
{
    QStringList convertToQStringList(std::vector<char*> inputVec);
    QStringList convertToQStringList(std::vector<std::string> inputVec);
    void stretchAllColumns(QTableWidget* inputTable);
    void stretchAllColumns(QTableView* inputTable);
    void resizeRowsToContents(QTableWidget* inputTable);
    void setTableHeaders(QStandardItemModel* inputModel, QStringList& headers);
}

#endif
