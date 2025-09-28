#ifndef DONUT_STYLE_H
#define DONUT_STYLE_H

#include <QCommonStyle>
#include <QPainter>

class DonutStyle : public QCommonStyle
{
    Q_OBJECT

public:

    enum ControlElement {
        CE_SwitchButton = QStyle::CE_CustomBase + 1,                   //switchButton �ؼ�
        CE_CustomBase = QStyle::CE_CustomBase + 0xf00000
    };

    enum SubElement {
        SE_SwitchButtonGroove = QStyle::SE_CustomBase + 1,             //���۾��δ�С
        SE_SwitchButtonHandle,                                         //������δ�С
        SE_CustomBase = QStyle::SE_CustomBase + 0xf00000
    };

    enum PixelMetric {
        PM_SwitchButtonHandleWidth = QStyle::PM_CustomBase + 1,        //switch Handle width
        PM_SwithcButtonHandleHeight,                                   //switch Handle height
        PM_CustomBase = QStyle::PM_CustomBase + 0xf00000
    };

    enum PrimitiveElement {
        PE_SwitchButtonGroove = QStyle::PE_CustomBase + 1,             //����
        PE_SwitchButtonHandle,                                         //����
        PE_CustomBase = QStyle::PE_CustomBase + 0xf00000
    };

    enum ComplexControl {
        CC_DoubleSlider = QStyle::CC_CustomBase + 1,
        CC_DountTimeline = QStyle::CC_CustomBase + 2,
        CC_UniversalSlider = QStyle::CC_CustomBase + 3, 
        CC_CustomBase = QStyle::CC_CustomBase + 0xf00000
    };
    enum SubControls { 
        SC_TimelineBase = QStyle::SC_CustomBase + 0xf00000,
        SC_LowerHandle = SC_TimelineBase + 1,
        SC_UpperHandle = SC_TimelineBase + 2,
        SC_MiddleHandle = SC_TimelineBase + 4,
        SC_TimelineGroove = SC_TimelineBase + 8,
        SC_ConfirmButton = SC_TimelineBase + 16,  // 新增
        SC_UpTriangle = SC_TimelineBase + 32,     // 新增
        SC_DownTriangle = SC_TimelineBase + 64    // 新增
    };
public:
    DonutStyle();

public:

    void drawPrimitive(DonutStyle::PrimitiveElement pe, const QStyleOption* opt, QPainter* p, const QWidget* w = nullptr) const;
    void drawControl(DonutStyle::ControlElement element, const QStyleOption* opt, QPainter* p, const QWidget* w) const;
    
    // ת����ʵ�ʵ�������QStyle�İ汾
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