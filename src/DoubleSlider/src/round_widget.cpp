#include "round_widget.h"
#include <QPainter>
#include <QStyleOption>
#include <QPainterPath>
#include <QSlider>
#include <QEvent>
#include <QMouseEvent>
#include <QSpinBox>

#include "donut_slider_custom_style.h"

RoundWidget::RoundWidget(QWidget* parent) : QWidget(parent)
{
    // to make a round widget
    // must set these properties before 
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);

    // method 2
    this->setStyleSheet("QWidget{background-color:gray;border-radius:30px;}");




    QSlider* slider = new QSlider(Qt::Horizontal, this);
    auto style = new DonutSliderStyle();
    slider->setStyle(style);
    slider->setGeometry(50, 50, 200, 50);

    slider->installEventFilter(style);
    slider->show();

    QSpinBox box;
    box.setGeometry(100, 250, 150, 50);
    box.setStyle(new CustomStyle);
    box.show();
}

RoundWidget::~RoundWidget()
{
}


// method 1 : 
//void RoundWidget::paintEvent(QPaintEvent *ev)
//{
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setBrush(QBrush(QColor(60, 60, 60)));
//    painter.setPen(Qt::transparent);
//    QRect rect = this->rect();
//    painter.drawRoundedRect(rect, 15, 15);
//}


// method 2 : 
void RoundWidget::paintEvent(QPaintEvent* ev)
{
    QStyleOption option;
    option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
    QWidget::paintEvent(ev);
}

void RoundWidget::initUI()
{
    
}

DonutSliderStyle::DonutSliderStyle(QStyle* style)
    : QProxyStyle(style)
{
    int handle_width = 4 + 4 + 6; // margin + ring-width + hollow-radius
    handle_size_ = { 2 * handle_width, 2 * handle_width }; // self.config["handle.size"]
}

bool DonutSliderStyle::eventFilter(QObject* watched, QEvent* event)
{
    //if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseMove || event->type() == QEvent::MouseButtonRelease) {
    //    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
    //    QSlider* slider = qobject_cast<QSlider*>(watched);

    //    if (slider) {
    //        QRect handleRect = subControlRect(CC_Slider, nullptr, SC_SliderHandle, slider);
    //        bool isMouseOverHandle = handleRect.contains(mouseEvent->pos());

    //        if (isMouseOverHandle && (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseMove)) {
    //            // 处理鼠标按下和移动事件
    //            int value = slider->minimum() + (slider->maximum() - slider->minimum()) * (mouseEvent->pos().x() - handleRect.left()) / handleRect.width();
    //            slider->setValue(value);
    //        }
    //    }
    //}

    // 继续传递事件
    return QProxyStyle::eventFilter(watched, event);
}

QRect DonutSliderStyle::subControlRect(ComplexControl cc, const QStyleOptionComplex* opt, SubControl sc, const QWidget* widget) const
{
    // 返回子控件所占的矩形区域
    //if (cc != QStyle::CC_Slider || opt->direction != Qt::LeftToRight || sc == QStyle::SC_SliderTickmarks)
    if (cc != QStyle::CC_Slider || (sc != QStyle::SC_SliderGroove && sc != QStyle::SC_SliderHandle))
    {
        return QProxyStyle::subControlRect(cc, opt, sc, widget);
    }
    rect_ = opt->rect;

    if (sc == QStyle::SC_SliderGroove)
    {
        int h = 6;  // self.config["groove.height"]
        QRectF grooveRect = QRectF(0, (rect_.height() - h) / 2, rect_.width(), h);
        return grooveRect.toRect();
    }
    else if (sc == QStyle::SC_SliderHandle)
    {
        const QStyleOptionSlider* sliderOpt = qstyleoption_cast<const QStyleOptionSlider*>(opt);
        if (!sliderOpt) {
            // 处理类型转换失败的情况
            return QRect();
        }

        int x = this->sliderPositionFromValue(
            sliderOpt->minimum, sliderOpt->maximum, sliderOpt->sliderPosition, rect_.width()
        );
        // 解决滑块跑出滑动条的情况
        x *= (rect_.width() - handle_size_.width()) / rect_.width();
        QRectF sliderRect = QRectF(0, 0, handle_size_.width(), handle_size_.height());
        return sliderRect.toRect();
    }


    return QRect();
}

void DonutSliderStyle::drawComplexControl(ComplexControl cc, const QStyleOptionComplex* opt, QPainter* painter, const QWidget* widget) const
{
    // 绘制子控件
    if (cc != QStyle::CC_Slider /*|| opt->direction != Qt::LeftToRight*/)
    {
        return QProxyStyle::drawComplexControl(cc, opt, painter, widget);
    }

    QRect grooveRect = this->subControlRect(cc, opt, QStyle::SC_SliderGroove, widget);
    QRect handleRect = this->subControlRect(cc, opt, QStyle::SC_SliderHandle, widget);
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);

    // 绘制滑槽
    painter->save();
    painter->translate(grooveRect.topLeft());

    // 绘制划过的部分
    int w = handleRect.x() - grooveRect.x();
    int h = 6; // self.config['groove.height'];
    painter->setBrush(QColor(255, 255, 255));    // self.config["sub-page.color"]
    painter->drawRect(0, 0, w, h);

    // 绘制未划过的部分
    int x = w + handle_size_.width();
    painter->setBrush(QColor(0, 0, 0));    // self.config["add-page.color"]
    painter->drawRect(x, 0, grooveRect.width() - w, h);
    painter->restore();

    // 绘制滑块
    int ringWidth = 4;      // self.config["handle.ring-width"];
    int hollowRadius = 6;   // self.config["handle.hollow-radius"];
    int radius = ringWidth + hollowRadius;

    QPainterPath path = QPainterPath();
    path.moveTo(0, 0);
    QPoint center = handleRect.center() + QPoint(10, 10);
    path.addEllipse(center, radius, radius);
    path.addEllipse(center, hollowRadius, hollowRadius);

    QColor handleColor = QColor(0, 0, 255); // self.config["handle.color"]  # type:QColor;
    handleColor.setAlpha(opt->activeSubControls != QStyle::SC_SliderHandle ? 255 : 153);
    painter->setBrush(handleColor);
    painter->drawPath(path);

    // 滑块按下
    const QStyleOptionSlider* sliderOpt = qstyleoption_cast<const QStyleOptionSlider*>(opt);
    if (!sliderOpt) {
        // 处理类型转换失败的情况
        return;
    }
    bool isSliderDown = sliderOpt->state & QStyle::State_Sunken;
    if (isSliderDown)
    {
        handleColor = QColor(0, 255, 0);
        handleColor.setAlpha(255);
        painter->setBrush(handleColor);
        painter->drawEllipse(handleRect);
    }

}

DonutStylePainter::DonutStylePainter(QWidget* widget)
    : QStylePainter(widget)
{

}

void DonutStylePainter::drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex& opt)
{
    
    if (opt.state & QStyle::State_Sunken)
    {
        int x;
    }
    if (cc != QStyle::CC_Slider /*|| (opt.activeSubControls) != QStyle::SC_SliderHandle*/)
    {
        //return QStylePainter::drawComplexControl(cc, opt);
        return;
    }

    // 绘制滑块
    auto handleRect = opt.rect;
    int radius = 8;

    QPainterPath path = QPainterPath();
    path.moveTo(0, 0);
    QPoint center = handleRect.center() + QPoint(1, 1);
    path.addEllipse(center, radius, radius);


    QColor handleColor = QColor(200, 0, 255); // self.config["handle.color"]  # type:QColor;
    handleColor.setAlpha(opt.activeSubControls != QStyle::SC_SliderHandle ? 255 : 153);
    this->setBrush(handleColor);
    this->drawPath(path);

    // 滑块按下
    if (opt.state & QStyle::State_Sunken)
    {
        handleColor = QColor(0, 255, 0);
        handleColor.setAlpha(255);
        this->setBrush(handleColor);
        this->drawEllipse(handleRect);
    }
    //const QStyleOptionSlider* sliderOpt = qstyleoption_cast<const QStyleOptionSlider*>(opt);
    //if (!sliderOpt) {
    //    // 处理类型转换失败的情况
    //    return;
    //}
    //bool isSliderDown = sliderOpt->state & QStyle::State_Sunken;
    //if (isSliderDown)
    //{
    //    handleColor = QColor(0, 255, 0);
    //    handleColor.setAlpha(255);
    //    painter->setBrush(handleColor);
    //    painter->drawEllipse(handleRect);
    //}
}
