#ifndef CSV_WINDOW_H
#define CSV_WINDOW_H

#include <QMainWindow>

class CustomProxyModel;
class QLineEdit;
class QRegExp;
class QStandardItemModel;
class QTableView;
class QAction;
class QMenuBar;
class QHBoxLayout;

class Csv_Window : public QMainWindow
{
    Q_OBJECT
    public:
        explicit Csv_Window(QWidget *parent = 0);
        void setupMultiArrayTable(std::vector<std::vector<std::string>>& inputData, std::vector<std::string>& headers);
        void setupMenus();
        void setupActions();
        void handleOpenCsvFile();
        void setupModel(std::string& filePath);
        void setupFilterSignals();
        void clearFilterLabels();
    private:
        QStandardItemModel* sourceModel;
        CustomProxyModel* filterModel;
        QTableView* tableView;
        QAction* actOpenFile;
        QMenu* fileMenu;
        QHBoxLayout* filterLayout;
        std::vector<std::vector<std::string>> multiArrayData;
        std::vector<std::string> headers;
};

#endif // CSV_WINDOW_H
