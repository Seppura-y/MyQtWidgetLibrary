#include "donut_custom_slider.h"

#include "donut_style.h"

#include <QMouseEvent>
#include <QStyleOption>
#include <QStylePainter>
#include <QDebug>


DonutCustomSlider::DonutCustomSlider(QWidget* parent)
    : QSlider(parent)
{
    this->setMouseTracking(true);
    this->setStyle(new DonutStyle);
}

DonutCustomSlider::~DonutCustomSlider()
{
}

void DonutCustomSlider::mousePressEvent(QMouseEvent* ev)
{
    QSlider::mousePressEvent(ev);

    is_pressed_ = true;
    double pos = 0;

    if (this->orientation() == Qt::Horizontal)
    {
        pos = ev->pos().x() / (double)width();
    }
    else if (this->orientation() == Qt::Vertical)
    {
        pos = ((double)height() - ev->pos().y()) / (double)height();
    }

    this->setValue(pos * (this->maximum() - this->minimum()) + this->minimum());

    emit sigCustomSliderValueChanged(this->value());
}

void DonutCustomSlider::mouseReleaseEvent(QMouseEvent* ev)
{
    QSlider::mouseReleaseEvent(ev);

    is_pressed_ = false;
    emit sigCustomSliderValueChanged(this->value());
}

void DonutCustomSlider::mouseMoveEvent(QMouseEvent* ev)
{
	QSlider::mouseMoveEvent(ev);
	update();
    cur_mouse_pos_ = ev->pos();

    if (is_pressed_)
    {
        double pos = 0;

        if (this->orientation() == Qt::Horizontal)
        {
            pos = ev->pos().x() / (double)width();
        }
        else if (this->orientation() == Qt::Vertical)
        {
            pos = ((double)height() - ev->pos().y()) / (double)height();
        }

        this->setValue(pos * (this->maximum() - this->minimum()) + this->minimum());

        emit sigCustomSliderValueChanged(this->value());
    }
    
    //qDebug() << "DonutCustomSlider mouse move";
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