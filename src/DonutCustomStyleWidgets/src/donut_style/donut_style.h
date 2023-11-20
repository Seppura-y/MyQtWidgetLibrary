#ifndef DONUT_STYLE_H
#define DONUT_STYLE_H

#include <QCommonStyle>
#include <QPainter>

class DonutStyle : public QCommonStyle
{
    Q_OBJECT

public:

    enum ControlElement {
        CE_SwitchButton = QStyle::CE_CustomBase + 1,                   //switchButton 控件
        CE_CustomBase = QStyle::CE_CustomBase + 0xf00000
    };

    enum SubElement {
        SE_SwitchButtonGroove = QStyle::SE_CustomBase + 1,             //滑槽矩形大小
        SE_SwitchButtonHandle,                                         //滑块矩形大小
        SE_CustomBase = QStyle::SE_CustomBase + 0xf00000
    };

    enum PixelMetric {
        PM_SwitchButtonHandleWidth = QStyle::PM_CustomBase + 1,        //switch Handle width
        PM_SwithcButtonHandleHeight,                                   //switch Handle height
        PM_CustomBase = QStyle::PM_CustomBase + 0xf00000
    };

    enum PrimitiveElement {
        PE_SwitchButtonGroove = QStyle::PE_CustomBase + 1,             //滑槽
        PE_SwitchButtonHandle,                                         //滑块
        PE_CustomBase = QStyle::PE_CustomBase + 0xf00000
    };

    enum ComplexControl {
        CC_DoubleSlider = QStyle::CC_CustomBase + 1,
        CC_CustomBase = QStyle::CC_CustomBase + 0xf00000
    };
    enum SubControls { SC_LowerHandle = SC_CustomBase + 1, SC_UpperHandle = SC_CustomBase + 2 };
public:
    DonutStyle();

public:

    void drawPrimitive(DonutStyle::PrimitiveElement pe, const QStyleOption* opt, QPainter* p, const QWidget* w = nullptr) const;
    void drawControl(DonutStyle::ControlElement element, const QStyleOption* opt, QPainter* p, const QWidget* w) const;
    
    // 转发，实际调用重载QStyle的版本
    void drawComplexControl(DonutStyle::ComplexControl cc, const QStyleOptionComplex* opt, QPainter* p, const QWidget* w) const;

    int pixelMetric(DonutStyle::PixelMetric metric, const QStyleOption* option, const QWidget* widget) const;

    QRect subElementRect(DonutStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget) const;
    
    virtual void drawPrimitive(QStyle::PrimitiveElement pe, const QStyleOption* opt, QPainter* p, const QWidget* w) const override;
    virtual void drawControl(QStyle::ControlElement element, const QStyleOption* opt, QPainter* p, const QWidget* w) const override;
    virtual void drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex* opt, QPainter* p, const QWidget* widget) const override;

    virtual int pixelMetric(QStyle::PixelMetric metric, const QStyleOption* option, const QWidget* widget) const override;
    virtual int styleHint(QStyle::StyleHint stylehint, const QStyleOption* opt, const QWidget* widget, QStyleHintReturn* returnData) const override;

    virtual QRect subElementRect(QStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget) const override;
    virtual QRect subControlRect(QStyle::ComplexControl cc, const QStyleOptionComplex* opt, SubControl sc, const QWidget* widget = nullptr) const override;
    virtual QSize sizeFromContents(QStyle::ContentsType ct, const QStyleOption* opt, const QSize& contentsSize, const QWidget* w) const override;
    

    virtual QStyle::SubControl hitTestComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex* opt, const QPoint& point, const QWidget* widget = nullptr) const override;
    

    virtual void polish(QWidget* widget) override;
    virtual void unpolish(QWidget* widget) override;
};

#endif