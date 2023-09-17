#include <QtWidgets/QApplication>

#include "main_wid.h"
#include "custom_item_widget.h"

#include <QDebug>

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    CustomItemWidget w;
    w.show();

    return a.exec();
}