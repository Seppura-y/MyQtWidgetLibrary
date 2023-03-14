#include "round_widget.h"
#include <QPainter>
#include <QStyleOption>
#include <QHBoxLayout>

#include "volume_button.h"


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
