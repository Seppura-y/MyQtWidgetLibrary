#include "donut_style_painter.h"

#include "donut_style_helper.h"
#include <QWidget>
#include <QStyleOption>
void DonutStylePainter::drawPrimitive(QStyle::PrimitiveElement pe, const QStyleOption* opt)
{
    q_style_->drawPrimitive(pe, opt, this, widget_);
}

DonutStylePainter::DonutStylePainter()
    : QPainter()
{
    widget_ = nullptr;
    //style_helper_ = nullptr;
}

DonutStylePainter::DonutStylePainter(QWidget* w)
{
    widget_ = w;
    q_style_ = w->style();
    style_helper_.setStyle(q_style_);
    QPainter::begin(w);
}

void DonutStylePainter::drawPrimitive(DonutStyle::PrimitiveElement pe, const QStyleOption* opt)
{
    style_helper_.drawPrimitive(pe, opt, this, widget_);
}

void DonutStylePainter::drawControl(QStyle::ControlElement element, const QStyleOption* opt)
{
    q_style_->drawControl(element, opt, this, widget_);
}

void DonutStylePainter::drawControl(DonutStyle::ControlElement element, const QStyleOption* opt)
{
    style_helper_.drawControl(element, opt, this, widget_);
}

void DonutStylePainter::drawComplexControl(QStyle::ComplexControl cc, const QStyleOption* opt)
{
    const QStyleOptionComplex* option = qstyleoption_cast<const QStyleOptionComplex*>(opt);
    q_style_->drawComplexControl(cc, option, this, widget_);
}

void DonutStylePainter::drawComplexControl(DonutStyle::ComplexControl cc, const QStyleOption* opt)
{
    const QStyleOptionComplex* option = qstyleoption_cast<const QStyleOptionComplex*>(opt);
    style_helper_.drawComplexControl(cc, option, this, widget_);
}