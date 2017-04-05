#ifndef CUSTOM_PROXY_FILTER_H
#define CUSTOM_PROXY_FILTER_H

#include <QSortFilterProxyModel>

class QRegExp;
class QLineEdit;
class QStringList;
class QStandardItemModel;

class CustomProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    public:
        explicit CustomProxyModel(QObject* parent=0);
        void setupFilters(QStringList& qHeaders);
        std::vector<int> getFilteredIndexes(QStandardItemModel* inputModel);

        // Struct that will contain our line edit and regular expression
        struct filterInfo
        {
            QLineEdit* filterEdit;
            QRegExp myRegExp;
        };
        std::vector<filterInfo> filters;

    public slots:
        void setFilter(const QString& regExp);

    protected:
        bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // CUSTOM_PROXY_FILTER_H
