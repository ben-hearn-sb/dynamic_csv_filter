#include "csv_window.h"
#include<QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Csv_Window w;
    w.show();
    return a.exec();
}

#include "main.moc"
