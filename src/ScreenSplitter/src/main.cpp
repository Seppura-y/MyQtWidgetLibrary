#include <QtWidgets/QApplication>

#include "manager.h"

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    
    Manager w;
    w.show();

    return a.exec();
}