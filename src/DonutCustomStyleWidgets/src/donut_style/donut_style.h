#ifndef DONUT_STYLE_H
#define DONUT_STYLE_H

#include <QCommonStyle>
#include <QPainter>

class DonutStyle : public QCommonStyle
{
    Q_OBJECT //connect qobject_cast

public:
    //这里新增加的枚举，是属于 MyStyle:: , 而非 QStyle:: 范围
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

public:
    DonutStyle();

    // QStyle interface
public:

    //static 函数，供 StyleHelper 调用 [用来绘画自增加的控件枚举]
    static void drawPrimitive(const QStyle* style, DonutStyle::PrimitiveElement pe, const QStyleOption* opt, QPainter* p, const QWidget* w = nullptr);
    static void drawControl(const QStyle* style, DonutStyle::ControlElement element, const QStyleOption* opt, QPainter* p, const QWidget* w);

    static QRect subElementRect(const QStyle* style, DonutStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget);
    static int pixelMetric(const QStyle* style, DonutStyle::PixelMetric metric, const QStyleOption* option, const QWidget* widget);

    //自定义的枚举类型 , 只能够在此内联函数里面调用
    //[主要用来绘画 自定义新增 的控件枚举 --> 实际调用在 下面的 virtual 里面绘画]
    inline void drawPrimitive(DonutStyle::PrimitiveElement pe, const QStyleOption* opt, QPainter* p, const QWidget* w = nullptr) const;
    void drawControl(DonutStyle::ControlElement element, const QStyleOption* opt, QPainter* p, const QWidget* w) const;

    inline QRect subElementRect(DonutStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget) const;
    inline int pixelMetric(DonutStyle::PixelMetric metric, const QStyleOption* option, const QWidget* widget) const;

    //这里的快捷方式创建的枚举,都是不带QStyle:: ; 但是快捷方式的定义是带是QStyle:: , 此处声明的地方必须加上 QStyle:: /*后面改写更复杂的得写上DonutStyle:: 因添加自定义的枚举*/
    //这里 override 的虚函数，只能够调用旧有的  QStyle:: 的函数
    //[主要用来绘画 Qt 、 自定义新增 的控件枚举]
    virtual void drawPrimitive(QStyle::PrimitiveElement pe, const QStyleOption* opt, QPainter* p, const QWidget* w) const override;
    virtual void drawControl(QStyle::ControlElement element, const QStyleOption* opt, QPainter* p, const QWidget* w) const override;
    virtual void drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex* opt, QPainter* p, const QWidget* widget) const override;

    virtual int pixelMetric(QStyle::PixelMetric metric, const QStyleOption* option, const QWidget* widget) const override;
    virtual int styleHint(QStyle::StyleHint stylehint, const QStyleOption* opt, const QWidget* widget, QStyleHintReturn* returnData) const override;

    virtual QRect subElementRect(QStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget) const override;
    virtual QRect subControlRect(QStyle::ComplexControl cc, const QStyleOptionComplex* opt, SubControl sc, const QWidget* widget = nullptr) const override;
    virtual QSize sizeFromContents(QStyle::ContentsType ct, const QStyleOption* opt, const QSize& contentsSize, const QWidget* w) const override;
    virtual QStyle::SubControl hitTestComplexControl(ComplexControl cc,const QStyleOptionComplex* opt, const QPoint& point, const QWidget* widget = nullptr) const override;
    virtual void polish(QWidget* widget) override;
    virtual void unpolish(QWidget* widget) override;

    // 使用声明
    // 在子类中引入这些函数，以便子类可以使用基类的实现
    // 重实现,使得父类的多个同名 函数 (不同参数) 任然可以在本类里面使用
    //using QCommonStyle::polish;
    //using QCommonStyle::unpolish;
    //using QCommonStyle::drawPrimitive;
    //using QCommonStyle::drawControl;
    //using QCommonStyle::subElementRect;
    //using QCommonStyle::drawComplexControl;
    //using QCommonStyle::subControlRect;
    //using QCommonStyle::pixelMetric;
    //using QCommonStyle::sizeFromContents;
    //using QCommonStyle::styleHint;
};

#endif