#include "donut_style_helper.h"

DonutStyleHelper::DonutStyleHelper(const QStyle* style)
{
    setStyle(style);
}

void DonutStyleHelper::setStyle(const QStyle* style)
{
    q_style_ = style;
    donut_style_ = qobject_cast<const DonutStyle*>(style);
}

const QStyle* DonutStyleHelper::qStyle() const
{
    return q_style_;
}

const DonutStyle* DonutStyleHelper::myStyle() const
{
    return donut_style_;
}

void DonutStyleHelper::drawPrimitive(DonutStyle::PrimitiveElement pe, const QStyleOption* opt, QPainter* p, const QWidget* w) const
{
    donut_style_ ? donut_style_->drawPrimitive(pe, opt, p, w)
        : DonutStyle::drawPrimitive(q_style_, pe, opt, p, w);   // static
}

void DonutStyleHelper::drawControl(DonutStyle::ControlElement element, const QStyleOption* opt, QPainter* p, const QWidget* w) const
{
    donut_style_ ? donut_style_->drawControl(element, opt, p, w)
        : DonutStyle::drawControl(q_style_, element, opt, p, w);
}

QRect DonutStyleHelper::subElementRect(DonutStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget) const
{
    return donut_style_ ? donut_style_->subElementRect(subElement, option, widget)
        : DonutStyle::subElementRect(q_style_, subElement, option, widget);
}

int DonutStyleHelper::pixelMetric(DonutStyle::PixelMetric metric, const QStyleOption* option, const QWidget* widget) const
{
    return donut_style_ ? donut_style_->pixelMetric(metric, option, widget)
        : DonutStyle::pixelMetric(q_style_, metric, option, widget);
}


