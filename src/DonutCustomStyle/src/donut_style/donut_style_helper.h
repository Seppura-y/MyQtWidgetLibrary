#ifndef DONUT_STYLE_HELPER_H
#define DONUT_STYLE_HELPER_H

#include "donut_style.h"

#include <QStyle>

class DonutStyleHelper
{
public:
    DonutStyleHelper(const QStyle* style = nullptr);

    void setStyle(const QStyle* style);

    const QStyle* qStyle() const;
    const DonutStyle* myStyle() const;

    void drawPrimitive(DonutStyle::PrimitiveElement pe, const QStyleOption* opt, QPainter* p, const QWidget* w = nullptr) const;
    void drawControl(DonutStyle::ControlElement element, const QStyleOption* opt, QPainter* p, const QWidget* w) const;
    QRect subElementRect(DonutStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget) const;
    int pixelMetric(DonutStyle::PixelMetric metric, const QStyleOption* option, const QWidget* widget) const;

    void drawComplexControl(DonutStyle::ComplexControl cc, const QStyleOptionComplex* opt, QPainter* p, const QWidget* w) const;
private:
    const QStyle* q_style_;
    const DonutStyle* donut_style_;
};

#endif