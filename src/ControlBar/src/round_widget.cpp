#include "round_widget.h"
#include <QPainter>
#include <QStyleOption>
#include <QHBoxLayout>

#include "volume_button.h"
#include "control_bar.h"
#include "custom_slider.h"
#include "config_helper.h"

RoundWidget::RoundWidget()
{
    // to make a round widget
    // must set these properties before 
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);

    // method 2
    this->setStyleSheet("QWidget{background-color:white;border-radius:30px;}");

    resize(800, 600);

    //QHBoxLayout* pHlay = new QHBoxLayout(this);

    VolumeButton* volume_button = new VolumeButton(this);
    //volume_button->setFixedSize(28, 28);
    volume_button->move(this->width() / 2, this->height() / 2);
    //pHlay->addWidget(volume_button);

    ControlBar* bar = new ControlBar(this);
    bar->setFixedWidth(this->width() - 20);
    bar->move(20, 20);


    //CustomSlider* slider = new CustomSlider(this);
    //slider->setOrientation(Qt::Horizontal);
    //slider->setStyleSheet(ConfigHelper::GetQssString(":/resources/res/css/control_bar.css"));
    //slider->setFixedSize(400,20);
    ////slider->setFixedSize(400, 400);
    //slider->move(20, 150);

    QSlider* test_slider = new QSlider(this);
    test_slider->setOrientation(Qt::Horizontal);
#define MAX_SLIDER_VALUE 65536
    test_slider->setMaximum(MAX_SLIDER_VALUE);
    test_slider->setTickPosition(QSlider::TicksBothSides);
    test_slider->setTickInterval(1000);
    test_slider->setGeometry(50, this->height() / 2 + 50, 500, 50);
    test_slider->show();
}

RoundWidget::~RoundWidget()
{
}


// method 1 : 
//void RoundWidget::paintEvent(QPaintEvent *ev)
//{
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setBrush(QBrush(QColor(60, 60, 60)));
//    painter.setPen(Qt::transparent);
//    QRect rect = this->rect();
//    painter.drawRoundedRect(rect, 15, 15);
//}


// method 2 : 
void RoundWidget::paintEvent(QPaintEvent* ev)
{
    QStyleOption option;
    option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
    QWidget::paintEvent(ev);
}

void RoundWidget::initUI()
{
    
}
