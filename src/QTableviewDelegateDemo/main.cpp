
#include "mainwindow.h"

#include <QApplication>
#include "tableview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;

    TableView t;
    t.show();
    return a.exec();
}
