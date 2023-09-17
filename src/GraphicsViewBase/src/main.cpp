#include <QtWidgets/QApplication>

#include "main_wid.h"

#include <QDebug>

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    MainWid w;
    w.show();

    return a.exec();
}