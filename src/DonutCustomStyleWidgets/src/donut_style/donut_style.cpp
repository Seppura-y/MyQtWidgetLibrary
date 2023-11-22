#include "donut_style.h"

#include "donut_double_slider_p.h"
#include "donut_timeline_p.h"

#include <QPainter>
#include <QStyleOption>
#include <QPainterPath>

DonutStyle::DonutStyle()
{

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
    proxy()->drawComplexControl(static_cast<QStyle::ComplexControl>(cc), opt, p, w);
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
        if (const QStyleOptionButton* switch_btn = qstyleoption_cast<const QStyleOptionButton*>(opt))
        {
            p->setPen(Qt::NoPen);
            if (switch_btn->state & State_On)
            {
                p->setBrush(QColor("orange"));
            }

            if (switch_btn->state & State_Off)
            {
                p->setPen(QPen(QColor("#e5e5e5"), 2));
                p->setBrush(QColor("#fdfefd"));
            }

            p->drawRoundedRect(switch_btn->rect.adjusted(1, 1, -1, -1), switch_btn->rect.height() / 2.0, switch_btn->rect.height() / 2.0);
        }
        break;
    }

    case PE_SwitchButtonHandle:
    {
        if (const QStyleOptionButton* switch_btn = qstyleoption_cast<const QStyleOptionButton*>(opt))
        {
            p->setPen(Qt::NoPen);
            if (switch_btn->state & State_On)
            {
                //p->setBrush(QColor("orange"));
                p->setBrush(QColor("#fefffe"));
            }

            if (switch_btn->state & State_Off)
                p->setPen(QPen(QColor("#e5e5e5"), 2));

            QRect handle_rect = switch_btn->rect.adjusted(1, 2, -1, -1);
            int r = qMin(handle_rect.width() / 2.0, handle_rect.height() / 2.0);
            p->drawEllipse(handle_rect.center(), r, r);
        }
        break;
    }
    default:
        break;
    }

    QCommonStyle::drawPrimitive(pe, opt, p, w);
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
            if (const QStyleOptionButton* switch_btn = qstyleoption_cast<const QStyleOptionButton*>(opt))
            {
                QStyleOptionButton option = *switch_btn;
                option.palette = switch_btn->palette;

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
            if (const QStyleOptionButton* switch_btn = qstyleoption_cast<const QStyleOptionButton*>(option))
                return switch_btn->rect;
            break;
        }
        case SE_SwitchButtonHandle:
        {
            if (const QStyleOptionButton* switch_btn = qstyleoption_cast<const QStyleOptionButton*>(option))
            {
                int handle_width = pixelMetric(PM_SwitchButtonHandleWidth, option, widget);
                QRect rect_handle(0, 0, 0, 0);
                rect_handle.setHeight(switch_btn->rect.height());

                if (switch_btn->rect.width() / 2.0 <= handle_width)
                    rect_handle.setWidth(switch_btn->rect.width() / 2.0);
                else
                    rect_handle.setWidth(handle_width);

                if (switch_btn->state & QStyle::State_Off)
                    rect_handle.moveLeft(switch_btn->rect.left() + 5);
                if (switch_btn->state & QStyle::State_On)
                    rect_handle.moveRight(switch_btn->rect.right() - 5);

                return rect_handle;
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
    if (cc == CC_DountTimeline)
    {
        const DonutTimelineStyleOption* opt_slider = qstyleoption_cast<const DonutTimelineStyleOption*>(opt);
        if (opt_slider)
        {
            QRect groove_rect = subControlRect(CC_Slider, opt_slider, SC_SliderGroove);
            QRect handle_rect = subControlRect(CC_Slider, opt_slider, SC_SliderHandle);

            p->save();
            // 清空上一次调用drawComplexControl时绘制的内容
            p->eraseRect(groove_rect);
            p->setRenderHint(QPainter::Antialiasing);
            p->setPen(Qt::NoPen);
            p->setBrush(QColor("lightgray"));

            p->drawRoundedRect(
                groove_rect.adjusted(1, groove_rect.height() / 4.0, -1, -groove_rect.height() / 4.0),
                groove_rect.height() / 4.0,
                groove_rect.height() / 4.0
            );

            p->setBrush(QColor("orange"));

            QRect spr(
                QPoint(opt_slider->span_rect_.x(), groove_rect.y()),
                QSize(opt_slider->span_rect_.width(), groove_rect.height())
            );
            p->drawRoundedRect(spr.adjusted(0, groove_rect.height() / 4.0, -1, -groove_rect.height() / 4.0),
                groove_rect.height() / 4.0,
                groove_rect.height() / 4.0
            );


            QPoint lower_center = QPoint(
                opt_slider->lower_rect_.x() + opt_slider->lower_rect_.width() / 2,
                opt_slider->lower_rect_.y() + opt_slider->lower_rect_.height() / 2
            );

            QColor handle_color = opt_slider->lower_hovered_ ? QColor("darkorange") : QColor("white");
            p->setPen(opt_slider->lower_hovered_ ? Qt::NoPen : QPen(QColor("#e5e5e5"), 1));
            p->setBrush(handle_color);
            p->setRenderHint(QPainter::Antialiasing);
            p->drawEllipse(lower_center,
                groove_rect.height() / 2 - 1,
                groove_rect.height() / 2 - 1);


            QPoint upper_center = QPoint(
                opt_slider->upper_rect_.x() + opt_slider->upper_rect_.width() / 2,
                opt_slider->upper_rect_.y() + opt_slider->upper_rect_.height() / 2
            );

            handle_color = opt_slider->upper_hovered_ ? QColor("darkorange") : QColor("white");
            p->setPen(opt_slider->upper_hovered_ ? Qt::NoPen : QPen(QColor("#e5e5e5"), 1));
            p->setRenderHint(QPainter::Antialiasing);
            p->setBrush(handle_color);
            p->drawEllipse(upper_center,
                groove_rect.height() / 2 - 1,
                groove_rect.height() / 2 - 1
            );

            QPoint middle_center = QPoint(
                opt_slider->middle_rect_.x() + opt_slider->middle_rect_.width() / 2,
                opt_slider->middle_rect_.y() + opt_slider->middle_rect_.height() / 2
            );

            handle_color = opt_slider->middle_hovered_ ? QColor("white") : QColor("darkorange");
            p->setPen(opt_slider->middle_hovered_ ? Qt::NoPen : QPen(QColor("#e5e5e5"), 1));
            p->setRenderHint(QPainter::Antialiasing);
            p->setBrush(handle_color);
            p->drawEllipse(middle_center,
                groove_rect.height() / 2 - 1,
                groove_rect.height() / 2 - 1
            );

            p->restore();
        }
        return;
    }
    else if (cc == CC_DoubleSlider)
    {
        const DonutDoubleSliderStyleOption* opt_slider = qstyleoption_cast<const DonutDoubleSliderStyleOption*>(opt);
        if (opt_slider)
        {
            QRect groove_rect = subControlRect(CC_Slider, opt_slider, SC_SliderGroove);
            QRect handle_rect = subControlRect(CC_Slider, opt_slider, SC_SliderHandle);

            p->save();
            // 清空上一次调用drawComplexControl时绘制的内容
            p->eraseRect(groove_rect);
            p->setRenderHint(QPainter::Antialiasing);
            p->setPen(Qt::NoPen);
            p->setBrush(QColor("lightgray"));

            p->drawRoundedRect(
                groove_rect.adjusted(1, groove_rect.height() / 4.0, -1, -groove_rect.height() / 4.0),
                groove_rect.height() / 4.0,
                groove_rect.height() / 4.0
            );

            p->setBrush(QColor("orange"));

            QRect spr(
                QPoint(opt_slider->span_rect_.x(), groove_rect.y()),
                QSize(opt_slider->span_rect_.width(), groove_rect.height())
            );
            p->drawRoundedRect(spr.adjusted(0, groove_rect.height() / 4.0, -1, -groove_rect.height() / 4.0),
                groove_rect.height() / 4.0,
                groove_rect.height() / 4.0
            );


            QPoint lower_center = QPoint(
                opt_slider->lower_rect_.x() + opt_slider->lower_rect_.width() / 2,
                opt_slider->lower_rect_.y() + opt_slider->lower_rect_.height() / 2
            );

            QColor handle_color = opt_slider->lower_hovered_ ? QColor("darkorange") : QColor("white");
            p->setPen(opt_slider->lower_hovered_ ? Qt::NoPen : QPen(QColor("#e5e5e5"), 1));
            p->setBrush(handle_color);
            p->setRenderHint(QPainter::Antialiasing);
            p->drawEllipse(lower_center,
                groove_rect.height() / 2 - 1,
                groove_rect.height() / 2 - 1);


            QPoint upper_center = QPoint(
                opt_slider->upper_rect_.x() + opt_slider->upper_rect_.width() / 2,
                opt_slider->upper_rect_.y() + opt_slider->upper_rect_.height() / 2
            );

            handle_color = opt_slider->upper_hovered_ ? QColor("darkorange") : QColor("white");
            p->setPen(opt_slider->upper_hovered_ ? Qt::NoPen : QPen(QColor("#e5e5e5"), 1));
            p->setRenderHint(QPainter::Antialiasing);
            p->setBrush(handle_color);
            p->drawEllipse(upper_center,
                groove_rect.height() / 2 - 1,
                groove_rect.height() / 2 - 1
            );

            p->restore();
        }
        return;
    }
    else if (cc == CC_Slider)
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

            QPoint center = QPoint(
                subControlRect(cc, opt_slider, SC_SliderHandle).x() + subControlRect(cc, opt_slider, SC_SliderHandle).width() / 2,
                subControlRect(cc, opt_slider, SC_SliderHandle).y() + subControlRect(cc, opt_slider, SC_SliderHandle).height() / 2
            );

            QColor handleColor = opt->state & QStyle::State_MouseOver ? QColor("darkorange") : QColor("white");
            p->setPen(opt->state& QStyle::State_MouseOver ? Qt::NoPen : QPen(QColor("#e5e5e5"), 1));
            p->setRenderHint(QPainter::Antialiasing);
            p->setBrush(handleColor);
            p->drawEllipse(center,
                subControlRect(cc, opt_slider, SC_SliderGroove, nullptr).height() / 2 - 1,
                subControlRect(cc, opt_slider, SC_SliderGroove, nullptr).height() / 2 - 1);



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

        int groove_size = 16;                    // Size of slider groove
        int handle_size = 16;                    // Size of slider groove

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
                slider_rect.setWidth(handle_size);
                slider_rect.setHeight(handle_size);

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
