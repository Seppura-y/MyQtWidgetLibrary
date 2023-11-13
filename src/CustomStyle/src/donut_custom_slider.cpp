#include "donut_custom_slider.h"


#include <QMouseEvent>
#include <QStyleOption>
#include <QStylePainter>
#include <QDebug>


DonutCustomSlider::DonutCustomSlider(QWidget* parent)
    : QSlider(parent)
{
    this->setMouseTracking(true);
}

DonutCustomSlider::~DonutCustomSlider()
{
}

void DonutCustomSlider::mouseMoveEvent(QMouseEvent* ev)
{
	QSlider::mouseMoveEvent(ev);
	update();
    cur_mouse_pos_ = ev->pos();

    
    qDebug() << "DonutCustomSlider mouse move";
}

void DonutCustomSlider::paintEvent(QPaintEvent* ev)
{
	Q_UNUSED(ev);

	QStyleOptionSlider opt;
	initStyleOption(&opt);

    QRect handle_rect = style()->subControlRect(QStyle::ComplexControl::CC_Slider, &opt, QStyle::SubControl::SC_SliderHandle);
    if (handle_rect.contains(cur_mouse_pos_))
    {
        opt.state |= QStyle::State_MouseOver;
    }
    else
    {
        opt.state &= (~(QStyle::State_MouseOver));
    }

	QStylePainter painter(this);
	painter.drawComplexControl(QStyle::CC_Slider, opt);

    // 在这里可以添加额外的绘制代码，根据鼠标状态更新handle的外观
    //if (opt.subControls & QStyle::SC_SliderHandle)
    //{
        if (opt.state & QStyle::State_MouseOver)
        {
            // 鼠标停在handle上时，可以设置不同的颜色或其他效果
            painter.setBrush(Qt::red);
            painter.drawComplexControl(QStyle::CC_Slider, opt);
        }
    //}
}
