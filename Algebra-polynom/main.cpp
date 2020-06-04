#include "mainwindow.h"

#include <QMetaType>
#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<QVector<QString>>();

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Algebra Polynom");
    w.setWindowIcon(QIcon(":/icon/icon.ico"));
    w.show();
    return a.exec();
}
