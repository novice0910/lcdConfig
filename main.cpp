#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //解决显示中文问题

    MainWindow w;
    w.show();

    return a.exec();
}
