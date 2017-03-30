#include<QStandardItemModel>
#include<QWidget>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QTableView>
#include<QList>
#include<QMainWindow>
#include<QStringList>

#include "csv_window.h"
#include "custom_proxy_filter.h"
#include "file_utils.h"
#include "qt_utils.h"

Csv_Window::Csv_Window(QWidget *parent): QMainWindow(parent)
{
    //set up GUI
    resize(500, 500);
    //std::string fileString = "C:/Users/Ben/google_drive/Avalanche/qt_task/data.csv";
    std::string fileString = "C:/Users/Ben/Desktop/sample_csv_data/Sacramentorealestatetransactions.csv";
    std::vector<std::vector<std::string>> csvData;
    std::vector<std::string> headers;
    std::vector<std::string> imageFilters;
    file_utils::constructCsvFileVector(fileString, csvData, headers);

    QWidget* w = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* hLayout = new QHBoxLayout();

    tableView = new QTableView();

    //set up models
    sourceModel     = new QStandardItemModel();
    filterModel     = new CustomProxyModel();
    filterModel->setSourceModel(sourceModel);
    tableView->setModel(filterModel);

    QStringList qHeaders = qt_utils::convertToQStringList(headers);
    filterModel->setupFilters(qHeaders);
    setupCsvTable(csvData, headers);
    qt_utils::stretchAllColumns(tableView);

    for(int i = 0; i < filterModel->filters.size(); ++i)
    {
        hLayout->addWidget(filterModel->filters[i].filterEdit);
        QObject::connect(filterModel->filters[i].filterEdit, SIGNAL(textChanged(const QString &)), filterModel, SLOT(setFilter(const QString &)));
        filterModel->filters[i].myRegExp.setCaseSensitivity(Qt::CaseInsensitive);
        filterModel->filters[i].myRegExp.setPatternSyntax(QRegExp::RegExp);
    }

    layout->addLayout(hLayout);
    layout->addWidget(tableView);
    w->setLayout(layout);
    setCentralWidget(w);
}

void Csv_Window::setupCsvTable(std::vector<std::vector<std::string>>& inputData, std::vector<std::string>& headers)
{
    // We setup our tablemodel here using the input csv multi vector
    std::vector<std::vector<std::string>>::const_iterator col;
    std::vector<std::string>::const_iterator row;
    for (col = inputData.begin(); col != inputData.end(); ++col)
    {
        QList<QStandardItem*> column;
        for (row = col->begin(); row != col->end(); ++row)
        {
            QString value = QString::fromStdString(*row).toLatin1().data();
            column.append(new QStandardItem(value));
        }
        sourceModel->appendColumn(column);
    }
    QStringList qHeaders = qt_utils::convertToQStringList(headers);
    qt_utils::setTableHeaders(sourceModel, qHeaders);
}
