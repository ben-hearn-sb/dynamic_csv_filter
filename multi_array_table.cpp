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
#include<QPushButton>
#include<QFileDialog>

#include "multi_array_table.h"
#include "custom_proxy_filter.h"
#include "file_utils.h"
#include "qt_utils.h"

// TODO:
// Save filtered information in new file
// Destroy QRegExp as well as labels

Multi_Array_Table::Multi_Array_Table(QWidget *parent): QMainWindow(parent)
{
    //set up GUI
    resize(500, 500);

    QWidget* w = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    QVBoxLayout* filterSectionLayout = new QVBoxLayout();
    filterLayout = new QHBoxLayout();

    //set up models
    tableView = new QTableView();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // Read only cells
    sourceModel     = new QStandardItemModel();
    filterModel     = new CustomProxyModel();
    filterModel->setSourceModel(sourceModel);
    tableView->setModel(filterModel);

    btnResetFilters = new QPushButton("Clear Filters");
    //btnResetFilters->setShortcut(Qt::CTRL + Qt::Key_C);
    connect(btnResetFilters, SIGNAL(clicked()), this, SLOT(clearFilters()));

    filterSectionLayout->addWidget(btnResetFilters);
    filterSectionLayout->addLayout(filterLayout);
    layout->addLayout(filterSectionLayout);
    layout->addWidget(tableView);
    w->setLayout(layout);
    setCentralWidget(w);
    setupActions();
    setupMenus();
}

void Multi_Array_Table::setupActions()
{
    actOpenFile = new QAction(QObject::tr("Open File"), this);
    actOpenFile->setShortcut(Qt::CTRL + Qt::Key_O);
    actSaveFiltered = new QAction(QObject::tr("Save Filtered"), this);
    actSaveFiltered->setShortcut(Qt::CTRL + Qt::Key_S);

    connect(actOpenFile, &QAction::triggered, this, &Multi_Array_Table::handleOpenCsvFile);
    connect(actSaveFiltered, &QAction::triggered, this, &Multi_Array_Table::saveFilteredData);
}

void Multi_Array_Table::setupMenus()
{
    // Here we setup out menus
    fileMenu = new QMenu(QObject::tr("File"));
    fileMenu->addAction(actOpenFile);
    fileMenu->addAction(actSaveFiltered);
    menuBar()->addMenu(fileMenu);
}

void Multi_Array_Table::handleOpenCsvFile()
{
    std::string filePath = file_utils::openFile();
    if(filePath != "")
    {
        setupModel(filePath);
    }
}

void Multi_Array_Table::setupMultiArrayTable(std::vector<std::vector<std::string>>& inputData, std::vector<std::string>& headers)
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

void Multi_Array_Table::setupModel(std::string& filePath)
{
    // Clear our vectors and model of old data first
    filterModel->filters.clear();
    multiArrayData.clear();
    headers.clear();
    sourceModel->clear();
    destroyFilterLabels();
    //filterModel->clear();

    // Setup our multiarry & headers
    file_utils::constructCsvFileVector(filePath, multiArrayData, headers);
    QStringList qHeaders = qt_utils::convertToQStringList(headers);
    filterModel->setupFilters(qHeaders);
    setupMultiArrayTable(multiArrayData, headers);
    qt_utils::stretchAllColumns(tableView);
    setupFilterSignals();
}

void Multi_Array_Table::setupFilterSignals()
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

void Multi_Array_Table::destroyFilterLabels()
{
    // TODO: Destroy QRegExp as well as labels
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

void Multi_Array_Table::clearFilters()
{
    // Clears the filter labels we have saved
    for(int i = 0; i < filterModel->filters.size(); ++i)
    {
        filterModel->filters[i].filterEdit->clear();
    }
}

void Multi_Array_Table::saveFilteredData()
{
    std::vector<int> filteredIndexes = filterModel->getFilteredIndexes(sourceModel);
    QString headerLabels = qt_utils::getTableHeadersInStr(sourceModel);
    QString tableData = qt_utils::collectTableInfoInStr(sourceModel, filteredIndexes);
    QString finalData = headerLabels + "\n" + tableData;

    //QFile newFile("C:/Users/Ben/Desktop/sample_csv_data/test.csv");
    //filename = QFileDialog::getSaveFileName( ... );
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("CSV data (*.csv)"));
    QFile newFile( filename );
    //f.open( QIODevice::WriteOnly );
    // store data in f
    //f.close();
    if(newFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream out(&newFile);
        out << finalData;
        newFile.close();
        qDebug() << "Closed file";
    }
}
