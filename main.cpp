#include <QApplication>
#include <QMainWindow>
#include "plotwindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    PlotWindow w;
//    w.setWindowTitle("График");
//    w.show();
    MainWindow mw;
    mw.show();
    return a.exec();
}

