#include <QtWidgets/QApplication>
#include "frameless_widget.h"
int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    
    FramelessWidget w;
    w.show();

    return a.exec();
}