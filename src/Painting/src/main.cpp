#include <QtWidgets/QApplication>
#include "round_widget.h"
#include "item_select_widget.h"

#include "mouse_move_painter_widget.h"
#include "main_win.h"

#include "main_wid.h"

#include <QDebug>

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    //RoundWidget w;
    MainWid w;
    //ItemSelectWidget w;
    w.show();

    return a.exec();
}