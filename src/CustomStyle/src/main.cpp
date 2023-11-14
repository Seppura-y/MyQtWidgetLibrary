#include <QtWidgets/QApplication>
#include "round_widget.h"
#include "donut_custom_slider.h"

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    
    RoundWidget w;
    w.show();

    //QWidget w;
    //w.show();

    //DonutCustomSlider slider;
    //slider.setOrientation(Qt::Horizontal);
    //slider.show();

    return a.exec();
}