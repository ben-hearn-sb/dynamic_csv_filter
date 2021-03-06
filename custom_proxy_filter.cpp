#include "custom_proxy_filter.h"

#include<QSortFilterProxyModel>
#include<QModelIndex>
#include<QString>
#include<QRegExp>
#include<Qt>
#include<QModelIndex>
#include<QObject>
#include<QDebug>
#include<QLineEdit>
#include<QStandardItemModel>

CustomProxyModel::CustomProxyModel(QObject* parent):QSortFilterProxyModel(parent)
{
}

bool CustomProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    // Iterates each row and if the row does not contain the regExp then we return false. Default is true
    // Each row is iterates, if our QRegExp is not found in a column then the row is false
    for (int i = 0; i < filters.size(); ++i) // filters.size() represents the number of columns we have. Columns = filters
    {
        QModelIndex qIndex  = sourceModel()->index(sourceRow, i, sourceParent);
        QString qStr        = sourceModel()->data(qIndex).toString();
        if (qStr.contains(filters[i].myRegExp) == false)
        {
            return false;
        }
    }
    return true;
}

void CustomProxyModel::setFilter(const QString& regExp)
{
    // Tells the model filters
    QObject* senderObj = sender();
    QString senderName = senderObj->objectName();
    //qDebug() << senderName;
    for(int i = 0; i < filters.size(); ++i)
    {
        if(filters[i].filterEdit->objectName()  == senderName)
        {
            //qDebug() << "Found a match: " << senderName;
            filters[i].myRegExp.setPattern(regExp);
            invalidateFilter();
            break;
        }
    }
}

void CustomProxyModel::setupFilters(QStringList& qHeaders)
{
    // Sets up our filter structs dynamically based on the headers
    QStringList::const_iterator item;
    for (item = qHeaders.begin(); item != qHeaders.end(); ++item)
    {
        QLineEdit* edit = new QLineEdit();
        edit->setObjectName(*item);
        edit->setPlaceholderText(*item);
        QRegExp regExp;
        filters.push_back({edit, regExp});
    }
}

std::vector<int> CustomProxyModel::getFilteredIndexes(QStandardItemModel* inputModel)
{
    std::vector<int> visibleRows;
    //int rowCount = CustomProxyModel::rowCount();
    int rowCount = inputModel->rowCount();
    for(int i = 0; i < rowCount; ++i)
    {
        bool valid = mapFromSource(sourceModel()->index(i, 0)).isValid();
        if(valid == true)
        {
            visibleRows.push_back(i);
        }
    }
    return visibleRows;
}

