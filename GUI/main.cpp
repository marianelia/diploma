#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //InputFiles i;
    //i.show();
    MainWindow w;
    w.setWindowTitle("Результат");
    w.show();
    return a.exec();
}
