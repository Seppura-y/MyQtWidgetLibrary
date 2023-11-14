#include "donut_style.h"

#include <QPainter>
#include <QStyleOption>
#include <QPainterPath>

DonutStyle::DonutStyle()
{

}


void DonutStyle::drawPrimitive(const QStyle* style, DonutStyle::PrimitiveElement pe, const QStyleOption* opt, QPainter* p, const QWidget* w)
{

}

void DonutStyle::drawControl(const QStyle* style, DonutStyle::ControlElement element, const QStyleOption* opt, QPainter* p, const QWidget* w)
{
}

void DonutStyle::drawComplexControl(const QStyle* style, DonutStyle::ComplexControl cc, const QStyleOptionComplex* opt, QPainter* p, const QWidget* w)
{
}

QRect DonutStyle::subElementRect(const QStyle* style, DonutStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget)
{
    return QRect();
}

int DonutStyle::pixelMetric(const QStyle* style, DonutStyle::PixelMetric metric, const QStyleOption* option, const QWidget* widget)
{
    return 0;
}


void DonutStyle::drawPrimitive(DonutStyle::PrimitiveElement pe, const QStyleOption* opt, QPainter* p, const QWidget* w) const
{
    proxy()->drawPrimitive(static_cast<QStyle::PrimitiveElement>(pe), opt, p, w);
}

void DonutStyle::drawControl(DonutStyle::ControlElement element, const QStyleOption* opt, QPainter* p, const QWidget* w) const
{
    proxy()->drawControl(static_cast<QStyle::ControlElement>(element), opt, p, w);
}

void DonutStyle::drawComplexControl(DonutStyle::ComplexControl cc, const QStyleOptionComplex* opt, QPainter* p, const QWidget* w) const
{
    const QStyleOptionComplex* option = qstyleoption_cast<const QStyleOptionComplex*>(opt);

    proxy()->drawComplexControl(static_cast<QStyle::ComplexControl>(cc), option, p, w);
}

QRect DonutStyle::subElementRect(DonutStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget) const
{
    return proxy()->subElementRect(static_cast<QStyle::SubElement>(subElement), option, widget);
}

int DonutStyle::pixelMetric(DonutStyle::PixelMetric metric, const QStyleOption* option, const QWidget* widget) const
{
    return proxy()->pixelMetric(static_cast<QStyle::PixelMetric>(metric), option, widget);
}

void DonutStyle::polish(QWidget* widget)
{
    QCommonStyle::polish(widget);
}

void DonutStyle::unpolish(QWidget* widget)
{
    QCommonStyle::unpolish(widget);
}

void DonutStyle::drawPrimitive(QStyle::PrimitiveElement pe, const QStyleOption* opt, QPainter* p, const QWidget* w) const
{
    switch(pe)
    {
    case PE_SwitchButtonGroove:
    {
        if (const QStyleOptionButton* switchBtn = qstyleoption_cast<const QStyleOptionButton*>(opt))
        {
            p->setPen(Qt::NoPen);
            if (switchBtn->state & State_On)
            {
                p->setBrush(QColor("orange"));
                //p->setBrush(QColor("#77d472"));
            }

            if (switchBtn->state & State_Off)
            {
                p->setPen(QPen(QColor("#e5e5e5"), 2));
                p->setBrush(QColor("#fdfefd"));
            }

            p->drawRoundedRect(switchBtn->rect.adjusted(1, 1, -1, -1), switchBtn->rect.height() / 2.0, switchBtn->rect.height() / 2.0);
        }
        break;
    }

    case PE_SwitchButtonHandle:
    {
        if (const QStyleOptionButton* switchBtn = qstyleoption_cast<const QStyleOptionButton*>(opt))
        {
            p->setPen(Qt::NoPen);
            if (switchBtn->state & State_On)
            {
                //p->setBrush(QColor("orange"));
                p->setBrush(QColor("#fefffe"));
            }

            if (switchBtn->state & State_Off)
                p->setPen(QPen(QColor("#e5e5e5"), 2));

            QRect rectHandle = switchBtn->rect.adjusted(1, 2, -1, -1);
            int r = qMin(rectHandle.width() / 2.0, rectHandle.height() / 2.0);
            p->drawEllipse(rectHandle.center(), r, r);
        }
        break;
    }
    default:
        break;
    }

    QCommonStyle::drawPrimitive(pe, opt, p, w);

    //后续分离开为模块的判断
//    if (Q_UNLIKELY(pe < QStyle::PE_CustomBase))
//    else
//        drawPrimitive(this, static_cast<DonutStyle::PrimitiveElement>(pe), opt, p, w);
}

void DonutStyle::drawControl(QStyle::ControlElement element, const QStyleOption* opt, QPainter* p, const QWidget* w) const
{
    p->setRenderHint(QPainter::Antialiasing);

    switch(element)
    {
        case CE_ScrollBarAddPage: //增加滑槽
        {
            p->fillRect(opt->rect, QColor("#bfe9ff"));
            return;
        }
        case CE_ScrollBarSubPage: //减少滑槽
        {
            p->fillRect(opt->rect, QColor("#EC6EAD"));
            return;
        }
        case CE_ScrollBarSlider: //滑块
        {
            p->fillRect(opt->rect, QColor("#A8BFFF"));
            return;
        }
        case CE_ScrollBarAddLine: //增加按钮
        {
            p->fillRect(opt->rect, QColor("#21d4fd"));
            return;
        }
        case CE_ScrollBarSubLine: //减少按钮
        {
            p->fillRect(opt->rect, QColor("#de6161"));
            return;
        }
        case CE_SwitchButton:
        {
            if (const QStyleOptionButton* switchBtn = qstyleoption_cast<const QStyleOptionButton*>(opt))
            {
                QStyleOptionButton option = *switchBtn;
                option.palette = switchBtn->palette;

                option.rect = subElementRect(SE_SwitchButtonGroove, opt, w);
                drawPrimitive(PE_SwitchButtonGroove, &option, p, w);

                option.rect = subElementRect(SE_SwitchButtonHandle, opt, w);
                drawPrimitive(PE_SwitchButtonHandle, &option, p, w);
            }
            break;
        }
        default:
            break;
    }

    return QCommonStyle::drawControl(element, opt, p, w);
}

QRect DonutStyle::subElementRect(QStyle::SubElement subElement, const QStyleOption* option, const QWidget* widget) const
{
    switch(subElement)
    {
        case SE_SwitchButtonGroove:
        {
            if (const QStyleOptionButton* switchBtn = qstyleoption_cast<const QStyleOptionButton*>(option))
                return switchBtn->rect;
            break;
        }
        case SE_SwitchButtonHandle:
        {
            if (const QStyleOptionButton* switchBtn = qstyleoption_cast<const QStyleOptionButton*>(option))
            {
                int handleWidth = pixelMetric(PM_SwitchButtonHandleWidth, option, widget);
                QRect rectHandle(0, 0, 0, 0);
                rectHandle.setHeight(switchBtn->rect.height());

                if (switchBtn->rect.width() / 2.0 <= handleWidth)
                    rectHandle.setWidth(switchBtn->rect.width() / 2.0);
                else
                    rectHandle.setWidth(handleWidth);

                if (switchBtn->state & QStyle::State_Off)
                    rectHandle.moveLeft(switchBtn->rect.left() + 5);
                if (switchBtn->state & QStyle::State_On)
                    rectHandle.moveRight(switchBtn->rect.right() - 5);

                return rectHandle;
            }
            break;
        }
        case SE_SliderFocusRect:
        {
            if (const QStyleOptionSlider* slider_opt = qstyleoption_cast<const QStyleOptionSlider*>(option))
            {
                return slider_opt->rect;
                break;
            }
        }
        default:
            break;
    }

    return QCommonStyle::subElementRect(subElement, option, widget);
}

void DonutStyle::drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex* opt, QPainter* p, const QWidget* widget) const
{
    if (cc == CC_Slider)
    {
        const QStyleOptionSlider* opt_slider = qstyleoption_cast<const QStyleOptionSlider*>(opt);
        if (opt_slider)
        {
            QRect groove_rect = subControlRect(cc, opt_slider, SC_SliderGroove);
            QRect handle_rect = subControlRect(cc, opt_slider, SC_SliderHandle);
            p->save();
            p->setRenderHint(QPainter::Antialiasing);
            p->setPen(Qt::NoPen);
            p->setBrush(QColor("lightgray"));

            p->drawRoundedRect(
                groove_rect.adjusted(1, groove_rect.height() / 4.0, -1, -groove_rect.height() / 4.0),
                groove_rect.height() / 4.0,
                groove_rect.height() / 4.0
            );

            p->setBrush(QColor("orange"));
            QRect subpage_rect = QRect(
                groove_rect.x(),
                groove_rect.y(),
                handle_rect.x() + handle_rect.width() - groove_rect.x(),
                groove_rect.height()
            );

            p->drawRoundedRect(subpage_rect.adjusted(1, subpage_rect.height() / 4.0, -1, -subpage_rect.height() / 4.0),
                subpage_rect.height() / 4.0,
                subpage_rect.height() / 4.0
            );

            QPainterPath path = QPainterPath();
            QPoint center = QPoint(
                subControlRect(cc, opt_slider, SC_SliderHandle).x() + subControlRect(cc, opt_slider, SC_SliderHandle).width() / 2,
                subControlRect(cc, opt_slider, SC_SliderHandle).y() + subControlRect(cc, opt_slider, SC_SliderHandle).height() / 2
            );

            path.addEllipse(center,
                subControlRect(cc, opt_slider, SC_SliderGroove, nullptr).height() / 2.0 - 1,
                subControlRect(cc, opt_slider, SC_SliderGroove, nullptr).height() / 2.0 - 1);


            QColor handleColor = opt->state & QStyle::State_MouseOver ? QColor("darkorange") : QColor("white");
            p->setRenderHint(QPainter::Antialiasing);
            p->setBrush(handleColor);
            p->drawPath(path);
            p->restore();
        }
    }
    QCommonStyle::drawComplexControl(cc, opt, p, widget);
}

QRect DonutStyle::subControlRect(QStyle::ComplexControl cc, const QStyleOptionComplex* opt, QStyle::SubControl sc, const QWidget* widget) const
{
    if (cc == CC_Slider)
    {
        const QStyleOptionSlider* option_slider = qstyleoption_cast<const QStyleOptionSlider*>(opt);

        QRect slider_rect = option_slider->rect; // Slider widget rectangle

        int groove_size = 30;                    // Size of slider groove
        int handle_size = 30;                    // Size of slider groove

        switch (sc)
        {
            case SC_SliderHandle:
            {
                int temp_x = QStyle::sliderPositionFromValue(
                    option_slider->minimum,
                    option_slider->maximum,
                    option_slider->sliderPosition,
                    option_slider->rect.width() - handle_size,
                    option_slider->upsideDown
                );

                slider_rect.setX(temp_x);
                slider_rect.setY(0);
                slider_rect.setWidth(30);
                slider_rect.setHeight(30);

                return slider_rect;
            }
            case SC_SliderGroove:
            {
                slider_rect.setWidth(slider_rect.width());
                slider_rect.setHeight(groove_size);
                slider_rect.setX(0);
                slider_rect.setY(0);

                return slider_rect;
            }
        }
    }
    return QCommonStyle::subControlRect(cc, opt, sc, widget);
}

int DonutStyle::pixelMetric(QStyle::PixelMetric metric, const QStyleOption* option, const QWidget* widget) const
{
    switch(metric)
    {
        case PM_SwitchButtonHandleWidth:
            return 30;
        case PM_SwithcButtonHandleHeight:
            return 12;
        default:
            break;
    }

    return QCommonStyle::pixelMetric(metric, option, widget);
}

QSize DonutStyle::sizeFromContents(QStyle::ContentsType ct, const QStyleOption* opt, const QSize& contentsSize, const QWidget* w) const
{
    return QCommonStyle::sizeFromContents(ct, opt, contentsSize, w);
}

QStyle::SubControl DonutStyle::hitTestComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex* opt, const QPoint& point, const QWidget* widget) const
{
    if (cc == CC_Slider && opt)
    {
        SubControl sc = SC_None;

        if (const QStyleOptionSlider* option_slider = qstyleoption_cast<const QStyleOptionSlider*>(opt))
        {
            QRect temp_rect = subControlRect(cc, option_slider, SC_SliderHandle);

            if (temp_rect.isValid() && temp_rect.contains(point))
            {
                sc = SC_SliderHandle;
            }
            else
            {
                temp_rect = subControlRect(cc, option_slider, SC_SliderGroove);

                if (temp_rect.isValid() && temp_rect.contains(point))
                {
                    sc = SC_SliderGroove;
                }
            }
        }

        return sc;
    }

    return QCommonStyle::hitTestComplexControl(cc, opt, point, widget);
}

int DonutStyle::styleHint(QStyle::StyleHint stylehint, const QStyleOption* opt, const QWidget* widget, QStyleHintReturn* returnData) const
{
    return QCommonStyle::styleHint(stylehint, opt, widget, returnData);
}
