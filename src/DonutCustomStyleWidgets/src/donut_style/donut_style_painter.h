#ifndef DONUT_STYLE_PAINTER_H
#define DONUT_STYLE_PAINTER_H


#include "donut_style.h"
#include "donut_style_helper.h"

#include <QPainter>

class DonutStylePainter : public QPainter
{
public:
    DonutStylePainter();
    DonutStylePainter(QWidget* w);
    ~DonutStylePainter() {}

    void drawPrimitive(DonutStyle::PrimitiveElement pe, const QStyleOption* opt);
    void drawPrimitive(QStyle::PrimitiveElement pe, const QStyleOption* opt);
    void drawControl(DonutStyle::ControlElement element, const QStyleOption* opt);
    void drawControl(QStyle::ControlElement element, const QStyleOption* opt);

private:
    QWidget* widget_;
    QStyle* q_style_;
    DonutStyleHelper style_helper_;
};



#endif