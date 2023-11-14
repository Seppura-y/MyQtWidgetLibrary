#include "round_widget.h"
#include <QPainter>
#include <QStyleOption>

#include <QDebug>
#include <QTableWidget>
#include <QProgressBar>
#include <QPushButton>
#include <QApplication>
#include <QSlider>
#include <QScrollBar>
#include <QStyleFactory>

#include <QSlider>

#include "donut_switch_button.h"
#include "donut_style.h"
#include "donut_custom_slider.h"

RoundWidget::RoundWidget(QWidget* parent) : QWidget(parent)
{
    // to make a round widget
    // must set these properties before 
    //setAttribute(Qt::WA_TranslucentBackground);
    //setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);

    //// method 2
    //this->setStyleSheet("QWidget{background-color:gray;border-radius:30px;}");

    init();
}

RoundWidget::~RoundWidget()
{
}

void RoundWidget::init()
{
    resize(1000, 600);

    //QTableWidget* table = new QTableWidget(10, 10, this);
    //table->move(10, 10);

    //QScrollBar* scrollBarH = new QScrollBar(this);
    //scrollBarH->move(300, 50);
    //scrollBarH->setRange(0, 100);
    //scrollBarH->setValue(34);
    //scrollBarH->resize(380, 20);
    //scrollBarH->setOrientation(Qt::Horizontal);

    //QScrollBar* scrollBarV = new QScrollBar(this);
    //scrollBarV->move(50, 250);
    //scrollBarV->setRange(0, 100);
    //scrollBarV->setValue(67);
    //scrollBarV->resize(20, 380);
    //scrollBarV->setOrientation(Qt::Vertical);

    //QProgressBar* progreH = new QProgressBar(this);
    //progreH->move(300, 100);
    //progreH->resize(250, 40);
    //progreH->setValue(37);
    //progreH->setOrientation(Qt::Horizontal);

    //QProgressBar* progreV = new QProgressBar(this);
    //progreV->move(100, 300);
    //progreV->resize(40, 250);
    //progreV->setValue(67);
    //progreV->setOrientation(Qt::Vertical);

    QSlider* slider = new QSlider(this);
    slider->move(600, 500);
    slider->resize(300, 50);
    slider->setOrientation(Qt::Horizontal);
    slider->show();

    DonutCustomSlider* dn_slider = new DonutCustomSlider(this);
    dn_slider->move(600, 300);
    dn_slider->resize(300, 50);
    dn_slider->setOrientation(Qt::Horizontal);
    dn_slider->show();

    //自定义的控件
    //DonutSwitchButton* switchBtn = new DonutSwitchButton(this);
    //switchBtn->resize(80, 40);
    //switchBtn->move(200, 300);

    int i = 0;
    QStringList listStyle = QStyleFactory::keys();

    //显示 and 使用当前系统支持的系统风格
    foreach(QString val, listStyle)
    {
        qDebug() << val << "  ";
        QPushButton* btn = new QPushButton(val, this);
        btn->move(this->rect().right() - 100, this->rect().top() + i++ * 40);
        connect(btn, &QPushButton::clicked, this,
            [=]() 
            {
                qApp->setStyle(val);
            }
        );
    }

    //若是自定义风格， new 为对象即可
    QPushButton* btn = new QPushButton("My Style", this);
    btn->move(this->rect().right() - 100, this->rect().top() + i++ * 40);
    connect(btn, &QPushButton::clicked, this,
        [=]()
        {
            qApp->setStyle(new DonutStyle());
        }
    );

    qApp->setStyle(new DonutStyle());
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
