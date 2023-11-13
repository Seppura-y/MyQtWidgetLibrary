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

    // �����������Ӷ���Ļ��ƴ��룬�������״̬����handle�����
    //if (opt.subControls & QStyle::SC_SliderHandle)
    //{
        if (opt.state & QStyle::State_MouseOver)
        {
            // ���ͣ��handle��ʱ���������ò�ͬ����ɫ������Ч��
            painter.setBrush(Qt::red);
            painter.drawComplexControl(QStyle::CC_Slider, opt);
        }
    //}
}
