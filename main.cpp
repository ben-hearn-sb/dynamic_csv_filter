#include "multi_array_table.h"
#include<QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Multi_Array_Table w;
    w.show();
    return a.exec();
}

#include "main.moc"
