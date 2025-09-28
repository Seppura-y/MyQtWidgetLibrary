#include <QtWidgets/QApplication>
#include "round_widget.h"
#include "donut_custom_slider.h"
#include "donut_switch_button.h"
#include "donut_double_slider.h"
#include "donut_timeline.h"
#include "donut_custom_timeline.h"
#include "QxtSpanSlider.h"
#include "switch_test.h"

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

    switch_btn.setStyleSheet(R"(
    DonutSwitchButton {
        qproperty-onColor: rgb(34, 139, 34);
        qproperty-offColor: rgb(255, 69, 0);
        qproperty-knobColor: rgb(255, 255, 255);
        qproperty-borderColor: rgb(100, 100, 100);
        qproperty-borderWidth: 2;
        qproperty-knobShape: RoundedRectKnob;
        qproperty-trackShape: RoundedTrack;
        qproperty-onText: "开启";
        qproperty-offText: "关闭";
        qproperty-showText: true;
        qproperty-trackRadius: 10;
        qproperty-knobRadius: 5;
    }
    )");
    //switch_btn.setGeometry(20, 100, 50, 30);
    // 设置颜色
    switch_btn.setOnColor(QColor(34, 139, 34));   // 绿色
    switch_btn.setOffColor(QColor(255, 69, 0));   // 红色
    switch_btn.setKnobColor(QColor(255, 255, 255)); // 白色

    // 设置形状
    switch_btn.setKnobShape(DonutSwitchButton::RoundedRectKnob);
    switch_btn.setTrackShape(DonutSwitchButton::RoundedTrack);

    // 设置文字
    //switch_btn.setOnText(QString("OK"));
    //switch_btn.setOffText(QString("CK"));
    switch_btn.setShowText(true);

    // 设置边框
    switch_btn.setBorderWidth(2);
    switch_btn.setBorderColor(QColor(100, 100, 100));

    switch_btn.show();

    DonutDoubleSlider span_slider(Qt::Horizontal, &w);

    DonutTimeline timeline(Qt::Horizontal, &w);
    timeline.setGeometry(20, 300, 500, 46);
    timeline.setTickPosition(QSlider::TicksBothSides);
    timeline.setMaximum(800);
    timeline.setTickInterval(800 / 80);
    timeline.setHandleMovementMode(DonutTimeline::NoOverlapping);
    timeline.setUpperPosition(100);
    timeline.show();

    DonutCustomTimeline custom_timeline(&w);
    custom_timeline.setMaximum(800);
    custom_timeline.setTickInterval(800 / 80);
    custom_timeline.setOrientation(Qt::Horizontal);
    custom_timeline.setGeometry(20, 400, 600, 50);
    custom_timeline.show();

    SwitchButton bt(&w);
    bt.setGeometry(80, 100, 50, 30);
    bt.show();
    return a.exec();
}