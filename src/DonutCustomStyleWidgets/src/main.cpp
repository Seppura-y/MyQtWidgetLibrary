#include <QtWidgets/QApplication>
#include "round_widget.h"
#include "donut_custom_slider.h"
#include "donut_switch_button.h"
#include "QxtSpanSlider.h"

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    
    //RoundWidget w;
    //w.show();

    QWidget w;
    w.show();

    DonutCustomSlider slider(&w);
    slider.setOrientation(Qt::Horizontal);
    slider.setGeometry(20, 20, 300, 50);
    slider.show();

    DonutSwitchButton switch_btn(&w);
    switch_btn.setGeometry(20, 100, 50, 30);
    switch_btn.show();

    QxtSpanSlider span_slider(Qt::Horizontal, &w);
    span_slider.setGeometry(20, 200, 500, 20);
    span_slider.setHandleMovementMode(QxtSpanSlider::NoOverlapping);
    span_slider.show();

    return a.exec();
}