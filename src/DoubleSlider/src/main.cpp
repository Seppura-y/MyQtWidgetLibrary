#include <QtWidgets/QApplication>
#include "round_widget.h"
#include "double_slider.h"

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    //
    RoundWidget w;
    w.show();

    //DoubleSlider slider;
    //slider.show();

    return a.exec();
}