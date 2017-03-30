#ifndef CSV_WINDOW_H
#define CSV_WINDOW_H

#include <QMainWindow>

class QLineEdit;
class QRegExp;

class Csv_Window : public QMainWindow
{
    Q_OBJECT
    public:
        explicit Csv_Window(QWidget *parent = 0);

        //void setupCsvTable(std::vector<std::vector<std::string>>& inputData, std::vector<std::string>& headers);
        //void setupDummyFilters(std::vector<filterInfo>& inputVec);
};

#endif // CSV_WINDOW_H
