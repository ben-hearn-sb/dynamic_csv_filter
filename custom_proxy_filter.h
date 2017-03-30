#ifndef CUSTOM_PROXY_FILTER_H
#define CUSTOM_PROXY_FILTER_H

#include <QSortFilterProxyModel>

class QRegExp;
class QLineEdit;

class CustomProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    public:
        explicit CustomProxyModel(QObject* parent=0);
        std::vector<QRegExp> regVec;
        // Struct that will contain our line edit and regular expression
        struct filterInfo
        {
            QLineEdit* filterEdit;
            QRegExp myRegExp;
        };
        std::vector<filterInfo> filters;
        // setupFilterPatterns();

    public slots:
        void setFilter(const QString& regExp);

    protected:
        bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // CUSTOM_PROXY_FILTER_H
