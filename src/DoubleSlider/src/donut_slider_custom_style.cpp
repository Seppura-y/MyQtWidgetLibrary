#include "donut_slider_custom_style.h"
#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>

#include <QSpinBox>

DonutSliderCustomStyle::DonutSliderCustomStyle() : QCommonStyle()
{
}

DonutSliderCustomStyle::~DonutSliderCustomStyle()
{
}

void DonutSliderCustomStyle::drawComplexControl(ComplexControl cctrl, const QStyleOptionComplex* copt, QPainter* cpainter, const QWidget* cwgt) const
{
    QCommonStyle::drawComplexControl(cctrl, copt, cpainter, cwgt);
    if (cctrl == CC_Slider) {
        const QStyleOptionSlider* cOptionSlider = qstyleoption_cast<const QStyleOptionSlider*>(copt);

        if (cOptionSlider) {

            cpainter->save();
            //cpainter->drawEllipse(subControlRect(cctrl, copt, SC_SliderHandle));
            cpainter->fillRect(subControlRect(cctrl, copt, SC_SliderGroove), QColor(255, 128, 64, 255));
            cpainter->fillRect(subControlRect(cctrl, copt, SC_SliderHandle), QColor(128, 255, 64, 255));

            cpainter->restore();

            //cpainter->save();
            //QPainterPath path = QPainterPath();
            //QPoint center = QPoint(
            //    subControlRect(cctrl, copt, SC_SliderHandle).x() + subControlRect(cctrl, copt, SC_SliderHandle).width() / 2,
            //    subControlRect(cctrl, copt, SC_SliderHandle).y() + subControlRect(cctrl, copt, SC_SliderHandle).height() / 4
            //);
            ////QPoint center = subControlRect(cctrl, copt, SC_SliderHandle).center() + QPoint(1, 1);
            //path.addEllipse(center, 6, 6);

            //QColor handleColor = QColor(0, 0, 255); // self.config["handle.color"]  # type:QColor;
            //cpainter->setRenderHint(QPainter::Antialiasing);
            //cpainter->setBrush(handleColor);
            //cpainter->drawPath(path);
            //cpainter->restore();
        }
    }


}

QStyle::SubControl DonutSliderCustomStyle::hitTestComplexControl(ComplexControl cctrl, const QStyleOptionComplex* copt, const QPoint& cpoint, const QWidget* cwgt) const
{
    if (cctrl == CC_Slider && copt) {
        SubControl sc = SC_None;

        if (const QStyleOptionSlider* cOptionSlider = qstyleoption_cast<const QStyleOptionSlider*>(copt)) {
            QRect _tempRect = subControlRect(cctrl, cOptionSlider, SC_SliderHandle);

            if (_tempRect.isValid() && _tempRect.contains(cpoint)) {
                sc = SC_SliderHandle;
            }
            else {
                _tempRect = subControlRect(cctrl, cOptionSlider, SC_SliderGroove);

                if (_tempRect.isValid() && _tempRect.contains(cpoint)) {
                    sc = SC_SliderGroove;
                }
            }
        }

        return sc;
    }

    return QCommonStyle::hitTestComplexControl(cctrl, copt, cpoint, cwgt);
}

QRect DonutSliderCustomStyle::subControlRect(ComplexControl cctrl, const QStyleOptionComplex* copt, QStyle::SubControl subCtrl, const QWidget* cwgt) const
{
    if (cctrl == CC_Slider) {
        const QStyleOptionSlider* cOptionSlider = qstyleoption_cast<const QStyleOptionSlider*>(copt);

        QRect rectCctrl = cOptionSlider->rect; // Slider widget rectangle

        int iGrooveSize = 30;                    // Size of slider groove
        int iHandleSize = 30;                    // Size of slider groove

        switch (subCtrl) {
        case SC_SliderHandle:
        {
            int _iTempX = QStyle::sliderPositionFromValue(cOptionSlider->minimum, cOptionSlider->maximum, cOptionSlider->sliderPosition, cOptionSlider->rect.width() - iHandleSize, cOptionSlider->upsideDown);

            rectCctrl.setX(_iTempX);
            rectCctrl.setY(0);
            rectCctrl.setWidth(30);
            rectCctrl.setHeight(30);

            return rectCctrl;
        }
        case SC_SliderGroove:
        {
            rectCctrl.setWidth(rectCctrl.width());
            rectCctrl.setHeight(iGrooveSize);
            rectCctrl.setX(0);
            rectCctrl.setY(0);

            return rectCctrl;
        }
        }
    }

    return QCommonStyle::subControlRect(cctrl, copt, subCtrl, cwgt);
}

CustomStyle::CustomStyle()
    : QProxyStyle()
{

}

void CustomStyle::drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    if (element == PE_IndicatorSpinUp || element == PE_IndicatorSpinDown)
    {
        QPolygon points(3);
        int x = option->rect.x();
        int y = option->rect.y();
        int w = option->rect.width() / 2;
        int h = option->rect.height() / 2;
        x += (option->rect.width() - w) / 2;
        y += (option->rect.height() - h) / 2;

        if (element == PE_IndicatorSpinUp)
        {
            points[0] = QPoint(x, y + h);
            points[1] = QPoint(x + w, y + h);
            points[2] = QPoint(x + w / 2, y);
        }
        else // PE_SpinBoxDown
        {
            points[0] = QPoint(x, y);
            points[1] = QPoint(x + w, y);
            points[2] = QPoint(x + w / 2, y + h);
        }

        if (option->state & State_Enabled)
        {
            painter->setPen(option->palette.mid().color());
            painter->setBrush(option->palette.buttonText());
        }
        else
        {
            painter->setPen(option->palette.buttonText().color());
            painter->setBrush(option->palette.mid());
        }
        painter->drawPolygon(points);
    }
    else
    {
        QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
    //QProxyStyle::drawPrimitive(element, option, painter, widget);

}

CustomSpinBox::CustomSpinBox(QWidget* parent)
{
    auto style = new CustomStyle();
    this->setStyle(style);
    //setStyle(style);
}
