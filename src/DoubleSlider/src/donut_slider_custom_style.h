#ifndef DONUT_SLIDER_CUSTOM_STYLE_H
#define DONUT_SLIDER_CUSTOM_STYLE_H

#include <QStyle>
#include <QCommonStyle>
#include <QProxyStyle>
#include <QSpinBox>

class DonutSliderCustomStyle : public QCommonStyle
{
    Q_OBJECT
public:
    explicit DonutSliderCustomStyle();
    ~DonutSliderCustomStyle();

    virtual void drawComplexControl(ComplexControl       cctrl,
        const QStyleOptionComplex* copt,
        QPainter* cpainter,
        const QWidget* cwgt = nullptr) const;

    virtual QStyle::SubControl hitTestComplexControl(ComplexControl       cctrl,
        const QStyleOptionComplex* copt,
        const QPoint& cpoint,
        const QWidget* cwgt = nullptr) const;

    virtual QRect subControlRect(ComplexControl       cctrl,
        const QStyleOptionComplex* copt,
        QStyle::SubControl           subCtrl,
        const QWidget* cwgt = nullptr) const;
};

class CustomStyle : public QProxyStyle
{
    Q_OBJECT

public:
    CustomStyle();
    ~CustomStyle() {}

    void drawPrimitive(PrimitiveElement element, const QStyleOption* option,
        QPainter* painter, const QWidget* widget) const override;
};

class CustomSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    CustomSpinBox(QWidget* parent = nullptr);
    ~CustomSpinBox() {}



};
#endif