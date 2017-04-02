#include<QStandardItemModel>
#include<QWidget>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QTableView>
#include<QList>
#include<QMainWindow>
#include<QStringList>
#include<QAction>
#include<QMenu>
#include<QMenuBar>
#include<QObject>
#include<QDebug>

#include "csv_window.h"
#include "custom_proxy_filter.h"
#include "file_utils.h"
#include "qt_utils.h"

Csv_Window::Csv_Window(QWidget *parent): QMainWindow(parent)
{
    //set up GUI
    resize(500, 500);

    QWidget* w = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    filterLayout = new QHBoxLayout();

    //set up models
    tableView = new QTableView();
    sourceModel     = new QStandardItemModel();
    filterModel     = new CustomProxyModel();
    filterModel->setSourceModel(sourceModel);
    tableView->setModel(filterModel);

    layout->addLayout(filterLayout);
    layout->addWidget(tableView);
    w->setLayout(layout);
    setCentralWidget(w);
    setupActions();
    setupMenus();
}

void Csv_Window::setupActions()
{
    actOpenFile = new QAction(QObject::tr("Open File"), this);
    //actOpenFile->setShortcuts(Qt::CTRL + Qt::Key_O);
    connect(actOpenFile, &QAction::triggered, this, &Csv_Window::handleOpenCsvFile);
}

void Csv_Window::setupMenus()
{
    // Here we setup out menus
    fileMenu = new QMenu(QObject::tr("File"));
    fileMenu->addAction(actOpenFile);
    menuBar()->addMenu(fileMenu);
}

void Csv_Window::handleOpenCsvFile()
{
    std::string filePath = file_utils::openFile();
    if(filePath != "")
    {
        setupModel(filePath);
    }
}

void Csv_Window::setupMultiArrayTable(std::vector<std::vector<std::string>>& inputData, std::vector<std::string>& headers)
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
        // Here we append our columns to our source model
        sourceModel->appendColumn(column);
    }
    QStringList qHeaders = qt_utils::convertToQStringList(headers);
    qt_utils::setTableHeaders(sourceModel, qHeaders);
}

void Csv_Window::setupModel(std::string& filePath)
{
    // Clear our vectors and model of old data first
    filterModel->filters.clear();
    multiArrayData.clear();
    headers.clear();
    sourceModel->clear();
    clearFilterLabels();
    //filterModel->clear();

    // Setup our multiarry & headers
    file_utils::constructCsvFileVector(filePath, multiArrayData, headers);
    QStringList qHeaders = qt_utils::convertToQStringList(headers);
    filterModel->setupFilters(qHeaders);
    setupMultiArrayTable(multiArrayData, headers);
    qt_utils::stretchAllColumns(tableView);
    setupFilterSignals();
}

void Csv_Window::setupFilterSignals()
{
    // Setup line edit filter signals
    for(int i = 0; i < filterModel->filters.size(); ++i)
    {
        filterLayout->addWidget(filterModel->filters[i].filterEdit);
        QObject::connect(filterModel->filters[i].filterEdit, SIGNAL(textChanged(const QString &)), filterModel, SLOT(setFilter(const QString &)));
        filterModel->filters[i].myRegExp.setCaseSensitivity(Qt::CaseInsensitive);
        filterModel->filters[i].myRegExp.setPatternSyntax(QRegExp::RegExp);
    }
}

void Csv_Window::clearFilterLabels()
{
    // Iterates the filter layout and destroys the object handler and object
    for (int i = 0; i < filterLayout->count(); ++i)
    {
        QLayoutItem *child;
        while ((child = filterLayout->takeAt(i)) != 0)
        {
            delete child->widget();
            delete child;
        }
    }
}
