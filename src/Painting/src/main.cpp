#include <QtWidgets/QApplication>
#include "round_widget.h"
#include "item_select_widget.h"

#include <QDebug>

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    //RoundWidget w;
    ItemSelectWidget w;
    w.show();

    return a.exec();
}