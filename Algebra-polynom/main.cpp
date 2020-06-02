#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Algebra Polynom");
    w.setWindowIcon(QIcon(":/icon/icon.ico"));
    w.show();
    return a.exec();
}
