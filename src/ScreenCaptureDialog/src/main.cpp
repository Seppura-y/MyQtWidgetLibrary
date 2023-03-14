#include <QtWidgets/QApplication>
#include "round_widget.h"

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    
    RoundWidget w;
    w.show();

    return a.exec();
}