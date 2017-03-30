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

CustomProxyModel::CustomProxyModel(QObject* parent):QSortFilterProxyModel(parent)
{
}

bool CustomProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    bool contains;
    for (int i = 0; i < filters.size(); ++i)
    {
        QModelIndex qIndex  = sourceModel()->index(sourceRow, i, sourceParent);
        QString qStr        = sourceModel()->data(qIndex).toString();
        if(i == 0)
        {
            contains = qStr.contains(filters[i].myRegExp);
        }
        else
        {
            contains &= qStr.contains(filters[i].myRegExp);
        }
    }
    return contains;
}

void CustomProxyModel::setFilter(const QString& regExp)
{
    QObject* senderObj = sender();
    QString senderName = senderObj->objectName();
    //qDebug() << senderName;
    for(int i = 0; i < filters.size(); ++i)
    {
        if(filters[i].filterEdit->objectName()  == senderName)
        {
            qDebug() << "Found a match: " << senderName;
            filters[i].myRegExp.setPattern(regExp);
            invalidateFilter();
            break;
        }
    }
}

void CustomProxyModel::setupFilters(QStringList& qHeaders)
{
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
