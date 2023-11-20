#include "donut_custom_timeline.h"

#include "donut_style.h"

#include <QMouseEvent>
#include <QStyleOption>
#include <QStylePainter>
#include <QDebug>


DonutCustomTimeline::DonutCustomTimeline(QWidget* parent)
    : QSlider(parent)
{
    this->setMouseTracking(true);
    //this->setStyle(new DonutStyle);
    this->setTickPosition(QSlider::TicksBothSides);
}

DonutCustomTimeline::~DonutCustomTimeline()
{
}

void DonutCustomTimeline::mousePressEvent(QMouseEvent* ev)
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

void DonutCustomTimeline::mouseReleaseEvent(QMouseEvent* ev)
{
    QSlider::mouseReleaseEvent(ev);

    is_pressed_ = false;
    emit sigCustomSliderValueChanged(this->value());
}

void DonutCustomTimeline::mouseMoveEvent(QMouseEvent* ev)
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

void DonutCustomTimeline::paintEvent(QPaintEvent* ev)
{
    QStylePainter p(this);
    QStyleOptionSlider style_options;
    initStyleOption(&style_options);

    const QRect groove_rect =
        style()->subControlRect(QStyle::CC_Slider, &style_options, QStyle::SC_SliderTickmarks, this);

    const QRect frame_rect =
        style()->subElementRect(QStyle::SubElement::SE_SliderFocusRect, &style_options, this);

    p.setPen(Qt::NoPen);
    p.setBrush(QColor("lightgray"));
    p.drawRect(frame_rect);

    const QRect handle_rect =
        style()->subControlRect(QStyle::CC_Slider, &style_options, QStyle::SC_SliderHandle, this);

    // Draw the slider (this is basically copy/pasted from QSlider::paintEvent).
    style_options.subControls = QStyle::SC_SliderGroove;
    p.drawComplexControl(QStyle::CC_Slider, style_options);

    // Draw the slider handle.
    style_options.subControls = QStyle::SC_SliderHandle;
    p.drawComplexControl(QStyle::CC_Slider, style_options);

    // Draw tick marks.
    // Do this manually because they are very badly behaved with style sheets.
    int interval = tickInterval();
    if (interval == 0)
    {
        interval = pageStep();
    }

    if (tickPosition() != NoTicks)
    {
        // This is the horizontal margin of the slider's *handle*, as defined in the stylesheet.
        //float margin = this->maximum() / 800;
        constexpr float margin = 5;

        const float handle_width = static_cast<float>(handle_rect.width());
        const float handle_half_width = handle_width / 2.0f;
        const float slider_value_range = static_cast<float>(this->maximum() - this->minimum());
        // Drawing range = control's width, minus twice the handle half width (one on each side), minus twice the margin (one on each side).
        const float drawing_range = static_cast<float>(this->width()) - handle_width - 2.0f * margin;
        const float factor = drawing_range / slider_value_range;

        for (int i = minimum(); i <= maximum(); i += interval)
        {
            // Height of the ticks' bars to draw.
            int tick_height = handle_rect.height();
            //constexpr int tick_height = 5;

            const int offset_value_space = i - minimum(); // How far from the slider's minimum value we are.
            const float offset_drawing_space = factor * static_cast<float>(offset_value_space) + handle_half_width + margin; // Where to draw in the horizontal range.
            const int x = static_cast<int>(offset_drawing_space);

            p.setPen(QColor{ 0, 0, 0, 255 });
            if (tickPosition() == TicksBothSides || tickPosition() == TicksAbove)
            {
                const int y = this->rect().top();
                p.drawLine(x, y, x, y + tick_height);
            }
            if (tickPosition() == TicksBothSides || tickPosition() == TicksBelow)
            {
                const int y = this->rect().bottom();
                p.drawLine(x, y, x, y - tick_height);
            }
        }
    }
}
