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
class QPushButton;

class Multi_Array_Table : public QMainWindow
{
    Q_OBJECT
    public:
        explicit Multi_Array_Table(QWidget *parent = 0);
        void setupMultiArrayTable(std::vector<std::vector<std::string>>& inputData, std::vector<std::string>& headers);
        void setupMenus();
        void setupActions();
        void handleOpenCsvFile();
        void setupModel(std::string& filePath);
        void setupFilterSignals();
        void destroyFilterLabels();
        void saveFilteredSnapShot();
    private:
        QStandardItemModel* sourceModel;
        CustomProxyModel* filterModel;
        QTableView* tableView;
        QAction* actOpenFile;
        QMenu* fileMenu;
        QHBoxLayout* filterLayout;
        QPushButton* btnResetFilters;
        std::vector<std::vector<std::string>> multiArrayData;
        std::vector<std::string> headers;
    public slots:
        void clearFilters();
};

#endif // CSV_WINDOW_H
