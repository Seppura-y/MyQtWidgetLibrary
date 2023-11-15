#ifndef DONUT_STYLE_PAINTER_H
#define DONUT_STYLE_PAINTER_H


#include "donut_style.h"

#include <QPainter>

class DonutStylePainter : public QPainter
{
public:
    DonutStylePainter();
    DonutStylePainter(QWidget* w);
    ~DonutStylePainter();

    void drawPrimitive(DonutStyle::PrimitiveElement pe, const QStyleOption* opt);
    void drawControl(DonutStyle::ControlElement element, const QStyleOption* opt);
    void drawComplexControl(DonutStyle::ComplexControl cc, const QStyleOption* opt);


private:
    QWidget* widget_;
    DonutStyle* donut_style_;
};



#endif