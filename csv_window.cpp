#include<QSortFilterProxyModel>
#include<QtGui/QStandardItemModel>
#include<QtWidgets/QWidget>
#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QLineEdit>
#include<QtWidgets/QTableView>
#include<QtCore/QList>
#include<QMainWindow>

#include "csv_window.h"
#include "custom_proxy_filter.h"

Csv_Window::Csv_Window(QWidget *parent): QMainWindow(parent)
{
    //set up GUI
    resize(500, 500);
    QWidget* w = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* hLayout = new QHBoxLayout();
    QLineEdit* lineEditName = new QLineEdit();
    QLineEdit* lineEditYear= new QLineEdit();
    QLineEdit* lineEditNumber= new QLineEdit();
    lineEditName->setObjectName("name_edit");
    lineEditYear->setObjectName("year_edit");
    lineEditNumber->setObjectName("number_edit");

    lineEditName->setPlaceholderText("name filter");
    lineEditYear->setPlaceholderText("year filter");
    lineEditNumber->setPlaceholderText("Number Filter");
    QRegExp nameRegExp;
    QRegExp yearRegExp;
    QRegExp numRegExp;

    QTableView* tableView = new QTableView();

    //set up models
    QStandardItemModel* sourceModel = new QStandardItemModel();
    CustomProxyModel* filterModel   = new CustomProxyModel();
    filterModel->setSourceModel(sourceModel);
    tableView->setModel(filterModel);

    layout->addLayout(hLayout);
    layout->addWidget(tableView);

    filterModel->filters.push_back({lineEditName, nameRegExp});
    filterModel->filters.push_back({lineEditYear, yearRegExp});
    filterModel->filters.push_back({lineEditNumber, numRegExp});

    for(int i = 0; i < filterModel->filters.size(); ++i)
    {
        hLayout->addWidget(filterModel->filters[i].filterEdit);
        QObject::connect(filterModel->filters[i].filterEdit, SIGNAL(textChanged(const QString &)), filterModel, SLOT(setFilter(const QString &)));
        filterModel->filters[i].myRegExp.setCaseSensitivity(Qt::CaseInsensitive);
        filterModel->filters[i].myRegExp.setPatternSyntax(QRegExp::RegExp);
    }

    //fill with dummy data
    QVector<QString> names{"Danny", "Christine", "Lars", "Roberto", "Maria"};
    for(int i=0; i<100; i++)
    {
        QList<QStandardItem*> row;
        row.append(new QStandardItem(names[i%names.size()]));
        row.append(new QStandardItem(QString::number((i%9)+1980)));
        row.append(new QStandardItem(QString::number(i)));
        sourceModel->appendRow(row);
    }
    w->setLayout(layout);
    setCentralWidget(w);
}

/*
void Csv_Window::setupCsvTable(std::vector<std::vector<std::string>>& inputData, std::vector<std::string>& headers)
{
    std::vector<std::vector<std::string>>::const_iterator col;
    std::vector<std::string>::const_iterator row;
    int columnCount = 0;
    int rowCount = 0;
    for (col = inputData.begin(); col != inputData.end(); ++col)
    {
        rowCount=0;
        for (row = col->begin(); row != col->end(); ++row)
        {
            QString value = QString::fromStdString(*row).toLatin1().data();
            QStandardItem *item = new QStandardItem(value);
            csvModel->setItem(rowCount, columnCount, item);
            ++rowCount;
        }
        ++columnCount;
    }
}
*/
