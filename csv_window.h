#ifndef CSV_WINDOW_H
#define CSV_WINDOW_H

#include <QMainWindow>

class CustomProxyModel;

class QLineEdit;
class QRegExp;
class QStandardItemModel;
class QTableView;

class Csv_Window : public QMainWindow
{
    Q_OBJECT
    public:
        explicit Csv_Window(QWidget *parent = 0);
        void setupCsvTable(std::vector<std::vector<std::string>>& inputData, std::vector<std::string>& headers);
    private:
        QStandardItemModel* sourceModel;
        CustomProxyModel* filterModel;
        QTableView* tableView;
};

#endif // CSV_WINDOW_H
