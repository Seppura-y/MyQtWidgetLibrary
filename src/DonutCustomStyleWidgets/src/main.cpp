#include <QtWidgets/QApplication>
#include "round_widget.h"
#include "donut_custom_slider.h"
#include "donut_switch_button.h"
#include "donut_double_slider.h"
#include "donut_timeline.h"
#include "donut_custom_timeline.h"
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

    //QxtSpanSlider span_slider(Qt::Horizontal, &w);
    //span_slider.setGeometry(20, 200, 500, 20);
    //span_slider.setHandleMovementMode(QxtSpanSlider::NoOverlapping);
    //span_slider.show();


    //DonutDoubleSlider span_slider(Qt::Horizontal, &w);
    //span_slider.setGeometry(20, 200, 500, 20);
    //span_slider.setHandleMovementMode(DonutDoubleSlider::NoOverlapping);
    //span_slider.show();

    DonutTimeline timeline(Qt::Horizontal, &w);
    timeline.setGeometry(20, 200, 500, 50);
    //timeline.setFixedHeight(50);
    timeline.setTickPosition(QSlider::TicksBothSides);
    timeline.setMaximum(800);
    timeline.setTickInterval(800 / 80);
    //timeline.setHandleMovementMode(DonutTimeline::FreeMovement);
    timeline.setHandleMovementMode(DonutTimeline::NoOverlapping);
    timeline.setUpperPosition(100);
    timeline.show();

    DonutCustomTimeline custom_timeline(&w);
    custom_timeline.setMaximum(800);
    custom_timeline.setTickInterval(800 / 80);
    custom_timeline.setOrientation(Qt::Horizontal);
    custom_timeline.setGeometry(20, 300, 600, 50);
    custom_timeline.show();

    return a.exec();
}