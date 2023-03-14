#include "round_widget.h"
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>

RoundWidget::RoundWidget(QWidget* parent) : QWidget(parent)
{
    // to make a round widget
    // must set these properties before 
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);

    // method 2
    this->setStyleSheet("QWidget{background-color:gray;border-radius:30px;}");

    initUI();
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
    this->resize(1920, 1080);
    title_ = new Title(this);
    QVBoxLayout layout;
    QWidget* content_widget = new QWidget(this);
    layout.addWidget(title_);
    layout.addWidget(content_widget);

    this->setLayout(&layout);
}
