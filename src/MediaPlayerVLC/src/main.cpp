#include <QtWidgets/QApplication>

#include "main_widget.h"

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    
    MainWidget* w = MainWidget::getInstance();
    w->show();

    return a.exec();
}