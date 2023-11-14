#ifndef DONUT_STYLE_H
#define DONUT_STYLE_H

#include <QCommonStyle>
#include <QPainter>

class DonutStyle : public QCommonStyle
{
    Q_OBJECT //connect qobject_cast

public:
    //���������ӵ�ö�٣������� MyStyle:: , ���� QStyle:: ��Χ
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

public:
    DonutStyle();

    // QStyle interface
public:

    //static �������� StyleHelper ���� [�����滭�����ӵĿؼ�ö��]
    static void drawPrimitive(const QStyle* style, DonutStyle::PrimitiveElement pe, const QStyleOption* opt, QPainter* p, const QWidget* w = nullptr);
    static void drawControl(const QStyle* style, DonutStyle::ControlElement element, const QStyleOption* opt, QPainter* p, const QWidget* w);

    static QRect subElementRect(const QStyle* style, DonutStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget);
    static int pixelMetric(const QStyle* style, DonutStyle::PixelMetric metric, const QStyleOption* option, const QWidget* widget);

    //�Զ����ö������ , ֻ�ܹ��ڴ����������������
    //[��Ҫ�����滭 �Զ������� �Ŀؼ�ö�� --> ʵ�ʵ����� ����� virtual ����滭]
    inline void drawPrimitive(DonutStyle::PrimitiveElement pe, const QStyleOption* opt, QPainter* p, const QWidget* w = nullptr) const;
    void drawControl(DonutStyle::ControlElement element, const QStyleOption* opt, QPainter* p, const QWidget* w) const;

    inline QRect subElementRect(DonutStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget) const;
    inline int pixelMetric(DonutStyle::PixelMetric metric, const QStyleOption* option, const QWidget* widget) const;

    //����Ŀ�ݷ�ʽ������ö��,���ǲ���QStyle:: ; ���ǿ�ݷ�ʽ�Ķ����Ǵ���QStyle:: , �˴������ĵط�������� QStyle:: /*�����д�����ӵĵ�д��DonutStyle:: ������Զ����ö��*/
    //���� override ���麯����ֻ�ܹ����þ��е�  QStyle:: �ĺ���
    //[��Ҫ�����滭 Qt �� �Զ������� �Ŀؼ�ö��]
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

    // ʹ������
    // ��������������Щ�������Ա��������ʹ�û����ʵ��
    // ��ʵ��,ʹ�ø���Ķ��ͬ�� ���� (��ͬ����) ��Ȼ�����ڱ�������ʹ��
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