#include <QtWidgets/QApplication>
#include <QWidget>
#include "round_widget.h"
#include "scroll_area_widget.h"
int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    RoundWidget w;
    w.show();

    ScrollAreaWidget wid;
    wid.show();


    return a.exec();
}