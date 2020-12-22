#include "mainwindow.h"
#include <QApplication>

/** Файл сгенерирован самим QT. Здесь создается окно программы и выводится на экран. */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
