#include "donut_style_painter.h"

#include <QWidget>
#include <QStyleOption>

DonutStylePainter::DonutStylePainter()
    : QPainter()
{
    widget_ = nullptr;
    donut_style_ = new DonutStyle();
}

DonutStylePainter::DonutStylePainter(QWidget* w)
{
    widget_ = w;
    donut_style_ = new DonutStyle();
    QPainter::begin(w);
}
DonutStylePainter::~DonutStylePainter()
{
    if (donut_style_)
    {
        delete donut_style_;
    }
}


void DonutStylePainter::drawPrimitive(DonutStyle::PrimitiveElement pe, const QStyleOption* opt)
{
    donut_style_->drawPrimitive(pe, opt, this, widget_);
}

void DonutStylePainter::drawControl(DonutStyle::ControlElement element, const QStyleOption* opt)
{
    donut_style_->drawControl(element, opt, this, widget_);
}

void DonutStylePainter::drawComplexControl(DonutStyle::ComplexControl cc, const QStyleOption* opt)
{
    const QStyleOptionComplex* option = qstyleoption_cast<const QStyleOptionComplex*>(opt);
    donut_style_->drawComplexControl(cc, option, this, widget_);
}