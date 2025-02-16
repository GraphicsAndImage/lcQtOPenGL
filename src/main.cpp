#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedWidth(800);
    w.setFixedHeight(400);
    w.showMaximized();
    return a.exec();
}
