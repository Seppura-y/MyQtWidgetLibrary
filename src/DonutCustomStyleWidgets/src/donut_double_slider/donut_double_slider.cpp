#include "donut_double_slider.h"
#include "donut_double_slider_p.h"
#include "donut_style.h"
#include "donut_style_painter.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QStylePainter>
#include <QStyleOptionSlider>
#include <QFontMetrics>
#include <QPainter>

DonutDoubleSliderStyleOption::DonutDoubleSliderStyleOption()
    : QStyleOptionSlider()
{

}

DonutDoubleSliderPrivate::DonutDoubleSliderPrivate() :
    lower_(0),
    upper_(0),
    lower_pos_(0),
    upper_pos_(0),
    offset_(0),
    position_(0),
    last_pressed_(DonutDoubleSlider::NoHandle),
    main_control_(DonutDoubleSlider::LowerHandle),
    lower_pressed_(QStyle::SC_None),
    upper_pressed_(QStyle::SC_None),
    movement_(DonutDoubleSlider::FreeMovement),
    first_movement_(false),
    block_tracking_(false)
{
}

void DonutDoubleSliderPrivate::initStyleOption(QStyleOptionSlider* option, DonutDoubleSlider::SpanHandle handle) const
{
    const DonutDoubleSlider* p = q_ptr_;
    p->initStyleOption(option);
    option->sliderPosition = (handle == DonutDoubleSlider::LowerHandle ? lower_pos_ : upper_pos_);
    option->sliderValue = (handle == DonutDoubleSlider::LowerHandle ? lower_ : upper_);
}

int DonutDoubleSliderPrivate::pixelPosToRangeValue(int pos) const
{
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    int slider_min = 0;
    int slider_max = 0;
    int handle_length = 0;
    const QSlider* p = q_ptr_;
    const QRect groove_rect = p->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, p);
    const QRect handle_rect = p->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, p);
    if (p->orientation() == Qt::Horizontal)
    {
        handle_length = handle_rect.width();
        slider_min = groove_rect.x();
        slider_max = groove_rect.right() - handle_length + 1;
    }
    else
    {
        handle_length = handle_rect.height();
        slider_min = groove_rect.y();
        slider_max = groove_rect.bottom() - handle_length + 1;
    }
    return QStyle::sliderValueFromPosition(p->minimum(), p->maximum(), pos - slider_min,
        slider_max - slider_min, opt.upsideDown);
}

void DonutDoubleSliderPrivate::handleMousePress(const QPoint& pos, QStyle::SubControl& control, int value, DonutDoubleSlider::SpanHandle handle)
{
    QStyleOptionSlider opt;
    initStyleOption(&opt, handle);

    DonutDoubleSlider* p = q_ptr_;
    const QStyle::SubControl old_control = control;

    control = p->style()->hitTestComplexControl(QStyle::CC_Slider, &opt, pos, p);
    const QRect sr = p->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, p);
    if (control == QStyle::SC_SliderHandle)
    {
        position_ = value;
        offset_ = pick(pos - sr.topLeft());
        last_pressed_ = handle;
        p->setSliderDown(true);
        emit p->sliderPressed(handle);
    }
    if (control != old_control)
    {
        //p->update(sr);
        p->update();
    }
}

QRect DonutDoubleSliderPrivate::getSpan(QPainter* painter, const QRect& rect) const
{
    DonutDoubleSliderStyleOption options;
    initStyleOption(&options);

    const QSlider* p = q_ptr_;
    // area
    QRect groove = p->style()->subControlRect(QStyle::CC_Slider, &options, QStyle::SC_SliderGroove, p);

    return rect.intersected(groove);
}

void DonutDoubleSliderPrivate::triggerAction(QAbstractSlider::SliderAction action, bool main)
{
    int value = 0;
    bool no = false;
    bool up = false;
    const int min = q_ptr_->minimum();
    const int max = q_ptr_->maximum();
    const DonutDoubleSlider::SpanHandle altControl = (main_control_ == DonutDoubleSlider::LowerHandle ? DonutDoubleSlider::UpperHandle : DonutDoubleSlider::LowerHandle);

    block_tracking_ = true;

    switch (action)
    {
    case QAbstractSlider::SliderSingleStepAdd:
        if ((main && main_control_ == DonutDoubleSlider::UpperHandle) || (!main && altControl == DonutDoubleSlider::UpperHandle))
        {
            value = qBound(min, upper_ + q_ptr_->singleStep(), max);
            up = true;
            break;
        }
        value = qBound(min, lower_ + q_ptr_->singleStep(), max);
        break;
    case QAbstractSlider::SliderSingleStepSub:
        if ((main && main_control_ == DonutDoubleSlider::UpperHandle) || (!main && altControl == DonutDoubleSlider::UpperHandle))
        {
            value = qBound(min, upper_ - q_ptr_->singleStep(), max);
            up = true;
            break;
        }
        value = qBound(min, lower_ - q_ptr_->singleStep(), max);
        break;
    case QAbstractSlider::SliderToMinimum:
        value = min;
        if ((main && main_control_ == DonutDoubleSlider::UpperHandle) || (!main && altControl == DonutDoubleSlider::UpperHandle))
            up = true;
        break;
    case QAbstractSlider::SliderToMaximum:
        value = max;
        if ((main && main_control_ == DonutDoubleSlider::UpperHandle) || (!main && altControl == DonutDoubleSlider::UpperHandle))
            up = true;
        break;
    case QAbstractSlider::SliderMove:
        if ((main && main_control_ == DonutDoubleSlider::UpperHandle) || (!main && altControl == DonutDoubleSlider::UpperHandle))
            up = true;
    case QAbstractSlider::SliderNoAction:
        no = true;
        break;
    default:
        qWarning("DonutDoubleSliderPrivate::triggerAction: Unknown action");
        break;
    }

    if (!no && !up)
    {
        if (movement_ == DonutDoubleSlider::NoCrossing)
            value = qMin(value, upper_);
        else if (movement_ == DonutDoubleSlider::NoOverlapping)
            value = qMin(value, upper_ - 1);

        if (movement_ == DonutDoubleSlider::FreeMovement && value > upper_)
        {
            swapControls();
            q_ptr_->setUpperPosition(value);
        }
        else
        {
            q_ptr_->setLowerPosition(value);
        }
    }
    else if (!no)
    {
        if (movement_ == DonutDoubleSlider::NoCrossing)
            value = qMax(value, lower_);
        else if (movement_ == DonutDoubleSlider::NoOverlapping)
            value = qMax(value, lower_ + 1);

        if (movement_ == DonutDoubleSlider::FreeMovement && value < lower_)
        {
            swapControls();
            q_ptr_->setLowerPosition(value);
        }
        else
        {
            q_ptr_->setUpperPosition(value);
        }
    }

    block_tracking_ = false;
    q_ptr_->setLowerValue(lower_pos_);
    q_ptr_->setUpperValue(upper_pos_);
}

void DonutDoubleSliderPrivate::swapControls()
{
    qSwap(lower_, upper_);
    qSwap(lower_pressed_, upper_pressed_);
    last_pressed_ = (last_pressed_ == DonutDoubleSlider::LowerHandle ? DonutDoubleSlider::UpperHandle : DonutDoubleSlider::LowerHandle);
    main_control_ = (main_control_ == DonutDoubleSlider::LowerHandle ? DonutDoubleSlider::UpperHandle : DonutDoubleSlider::LowerHandle);
}

void DonutDoubleSliderPrivate::updateRange(int min, int max)
{
    Q_UNUSED(min);
    Q_UNUSED(max);
    // setSpan() takes care of keeping span in range
    q_ptr_->setSpan(lower_, upper_);
}

void DonutDoubleSliderPrivate::movePressedHandle()
{
    switch (last_pressed_)
    {
    case DonutDoubleSlider::LowerHandle:
        if (lower_pos_ != lower_)
        {
            bool main = (main_control_ == DonutDoubleSlider::LowerHandle);
            triggerAction(QAbstractSlider::SliderMove, main);
        }
        break;
    case DonutDoubleSlider::UpperHandle:
        if (upper_pos_ != upper_)
        {
            bool main = (main_control_ == DonutDoubleSlider::UpperHandle);
            triggerAction(QAbstractSlider::SliderMove, main);
        }
        break;
    default:
        break;
    }
}


DonutDoubleSlider::DonutDoubleSlider(QWidget* parent) : QSlider(parent), d_ptr_(new DonutDoubleSliderPrivate())
{
    d_ptr_->q_ptr_ = this;
    connect(this, SIGNAL(rangeChanged(int, int)), d_ptr_, SLOT(updateRange(int, int)));
    connect(this, SIGNAL(sliderReleased()), d_ptr_, SLOT(movePressedHandle()));

    this->setStyle(new DonutStyle);
    setMouseTracking(true);
}

DonutDoubleSlider::DonutDoubleSlider(Qt::Orientation orientation, QWidget* parent) : QSlider(orientation, parent), d_ptr_(new DonutDoubleSliderPrivate())
{
    d_ptr_->q_ptr_ = this;
    connect(this, SIGNAL(rangeChanged(int, int)), d_ptr_, SLOT(updateRange(int, int)));
    connect(this, SIGNAL(sliderReleased()), d_ptr_, SLOT(movePressedHandle()));

    this->setStyle(new DonutStyle);
    setMouseTracking(true);
}

DonutDoubleSlider::~DonutDoubleSlider()
{
}

DonutDoubleSlider::HandleMovementMode DonutDoubleSlider::handleMovementMode() const
{
    return d_ptr_->movement_;
}

void DonutDoubleSlider::setHandleMovementMode(DonutDoubleSlider::HandleMovementMode mode)
{
    d_ptr_->movement_ = mode;
}

int DonutDoubleSlider::lowerValue() const
{
    return qMin(d_ptr_->lower_, d_ptr_->upper_);
}

void DonutDoubleSlider::setLowerValue(int lower)
{
    setSpan(lower, d_ptr_->upper_);
}

int DonutDoubleSlider::upperValue() const
{
    return qMax(d_ptr_->lower_, d_ptr_->upper_);
}

void DonutDoubleSlider::setUpperValue(int upper)
{
    setSpan(d_ptr_->lower_, upper);
}

void DonutDoubleSlider::setSpan(int lower, int upper)
{
    const int low = qBound(minimum(), qMin(lower, upper), maximum());
    const int upp = qBound(minimum(), qMax(lower, upper), maximum());
    if (low != d_ptr_->lower_ || upp != d_ptr_->upper_)
    {
        if (low != d_ptr_->lower_)
        {
            d_ptr_->lower_ = low;
            d_ptr_->lower_pos_ = low;
            emit lowerValueChanged(low);
        }
        if (upp != d_ptr_->upper_)
        {
            d_ptr_->upper_ = upp;
            d_ptr_->upper_pos_ = upp;
            emit upperValueChanged(upp);
        }
        emit spanChanged(d_ptr_->lower_, d_ptr_->upper_);
        update();
    }
}


int DonutDoubleSlider::lowerPosition() const
{
    return d_ptr_->lower_pos_;
}

void DonutDoubleSlider::setLowerPosition(int lower)
{
    if (d_ptr_->lower_pos_ != lower)
    {
        d_ptr_->lower_pos_ = lower;
        if (!hasTracking())
            update();
        if (isSliderDown())
            emit lowerPositionChanged(lower);
        if (hasTracking() && !d_ptr_->block_tracking_)
        {
            bool main = (d_ptr_->main_control_ == DonutDoubleSlider::LowerHandle);
            d_ptr_->triggerAction(SliderMove, main);
        }
    }
}


int DonutDoubleSlider::upperPosition() const
{
    return d_ptr_->upper_pos_;
}

void DonutDoubleSlider::setUpperPosition(int upper)
{
    if (d_ptr_->upper_pos_ != upper)
    {
        d_ptr_->upper_pos_ = upper;
        if (!hasTracking())
            update();
        if (isSliderDown())
            emit upperPositionChanged(upper);
        if (hasTracking() && !d_ptr_->block_tracking_)
        {
            bool main = (d_ptr_->main_control_ == DonutDoubleSlider::UpperHandle);
            d_ptr_->triggerAction(SliderMove, main);
        }
    }
}


void DonutDoubleSlider::keyPressEvent(QKeyEvent* event)
{
    QSlider::keyPressEvent(event);

    bool main = true;
    SliderAction action = SliderNoAction;
    switch (event->key())
    {
    case Qt::Key_Left:
        main = (orientation() == Qt::Horizontal);
        action = !invertedAppearance() ? SliderSingleStepSub : SliderSingleStepAdd;
        break;
    case Qt::Key_Right:
        main = (orientation() == Qt::Horizontal);
        action = !invertedAppearance() ? SliderSingleStepAdd : SliderSingleStepSub;
        break;
    case Qt::Key_Up:
        main = (orientation() == Qt::Vertical);
        action = invertedControls() ? SliderSingleStepSub : SliderSingleStepAdd;
        break;
    case Qt::Key_Down:
        main = (orientation() == Qt::Vertical);
        action = invertedControls() ? SliderSingleStepAdd : SliderSingleStepSub;
        break;
    case Qt::Key_Home:
        main = (d_ptr_->main_control_ == DonutDoubleSlider::LowerHandle);
        action = SliderToMinimum;
        break;
    case Qt::Key_End:
        main = (d_ptr_->main_control_ == DonutDoubleSlider::UpperHandle);
        action = SliderToMaximum;
        break;
    default:
        event->ignore();
        break;
    }

    if (action)
        d_ptr_->triggerAction(action, main);
}

void DonutDoubleSlider::mousePressEvent(QMouseEvent* event)
{
    if (minimum() == maximum() || (event->buttons() ^ event->button()))
    {
        event->ignore();
        return;
    }

    d_ptr_->handleMousePress(event->pos(), d_ptr_->upper_pressed_, d_ptr_->upper_, DonutDoubleSlider::UpperHandle);

    if (d_ptr_->upper_pressed_ != QStyle::SC_SliderHandle)
        d_ptr_->handleMousePress(event->pos(), d_ptr_->lower_pressed_, d_ptr_->lower_, DonutDoubleSlider::LowerHandle);

    d_ptr_->first_movement_ = true;
    event->accept();
}

void DonutDoubleSlider::mouseMoveEvent(QMouseEvent* event)
{
    d_ptr_->lower_hovered_ = false;
    d_ptr_->upper_hovered_ = false;
    d_ptr_->hovered_handle_ = DonutDoubleSlider::NoHandle;

    if (d_ptr_->lower_rect_.contains(event->pos()))
    {
        d_ptr_->lower_hovered_ = true;
        d_ptr_->hovered_handle_ = DonutDoubleSlider::LowerHandle;
    }

    if (d_ptr_->upper_rect_.contains(event->pos()))
    {
        d_ptr_->upper_hovered_ = true;
        d_ptr_->hovered_handle_ = DonutDoubleSlider::UpperHandle;
    }
    this->update();

    if (d_ptr_->lower_pressed_ != QStyle::SC_SliderHandle && d_ptr_->upper_pressed_ != QStyle::SC_SliderHandle)
    {
        event->ignore();
        return;
    }

    QStyleOptionSlider opt;
    d_ptr_->initStyleOption(&opt);
    const int m = style()->pixelMetric(QStyle::PM_MaximumDragDistance, &opt, this);
    int newPosition = d_ptr_->pixelPosToRangeValue(d_ptr_->pick(event->pos()) - d_ptr_->offset_);
    if (m >= 0)
    {
        const QRect r = rect().adjusted(-m, -m, m, m);
        if (!r.contains(event->pos()))
        {
            newPosition = d_ptr_->position_;
        }
    }

    // pick the preferred handle on the first movement
    if (d_ptr_->first_movement_)
    {
        if (d_ptr_->lower_ == d_ptr_->upper_)
        {
            if (newPosition < lowerValue())
            {
                d_ptr_->swapControls();
                d_ptr_->first_movement_ = false;
            }
        }
        else
        {
            d_ptr_->first_movement_ = false;
        }
    }

    if (d_ptr_->lower_pressed_ == QStyle::SC_SliderHandle)
    {
        if (d_ptr_->movement_ == NoCrossing)
            newPosition = qMin(newPosition, upperValue());
        else if (d_ptr_->movement_ == NoOverlapping)
            newPosition = qMin(newPosition, upperValue() - 1);

        if (d_ptr_->movement_ == FreeMovement && newPosition > d_ptr_->upper_)
        {
            d_ptr_->swapControls();
            setUpperPosition(newPosition);
        }
        else
        {
            setLowerPosition(newPosition);
        }
    }
    else if (d_ptr_->upper_pressed_ == QStyle::SC_SliderHandle)
    {
        if (d_ptr_->movement_ == NoCrossing)
            newPosition = qMax(newPosition, lowerValue());
        else if (d_ptr_->movement_ == NoOverlapping)
            newPosition = qMax(newPosition, lowerValue() + 1);

        if (d_ptr_->movement_ == FreeMovement && newPosition < d_ptr_->lower_)
        {
            d_ptr_->swapControls();
            setLowerPosition(newPosition);
        }
        else
        {
            setUpperPosition(newPosition);
        }
    }
    event->accept();
}

void DonutDoubleSlider::mouseReleaseEvent(QMouseEvent* event)
{
    QSlider::mouseReleaseEvent(event);
    setSliderDown(false);
    d_ptr_->lower_pressed_ = QStyle::SC_None;
    d_ptr_->upper_pressed_ = QStyle::SC_None;
    d_ptr_->hovered_handle_ = DonutDoubleSlider::NoHandle;
    d_ptr_->lower_hovered_ = false;
    d_ptr_->upper_hovered_ = false;
    update();
}

void DonutDoubleSlider::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    // 计算滑块的像素位置
    QStyleOptionSlider opt;
    d_ptr_->initStyleOption(&opt);

    // 获取groove rect
    QRect grooveRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);

    // 计算lower handle的像素位置
    int lowerPixelPos = QStyle::sliderPositionFromValue(minimum(), maximum(),
        d_ptr_->lower_pos_,
        orientation() == Qt::Horizontal ? grooveRect.width() : grooveRect.height());

    // 计算upper handle的像素位置  
    int upperPixelPos = QStyle::sliderPositionFromValue(minimum(), maximum(),
        d_ptr_->upper_pos_,
        orientation() == Qt::Horizontal ? grooveRect.width() : grooveRect.height());

    // 首先使用DonutStylePainter绘制滑块
    {
        DonutStylePainter painter(this);
        DonutDoubleSliderStyleOption opt;
        d_ptr_->initStyleOption(&opt);

        opt.sliderValue = 0;
        opt.sliderPosition = 0;
        opt.subControls = QStyle::SC_SliderGroove | QStyle::SC_SliderTickmarks;

        // handle rects
        opt.sliderPosition = d_ptr_->lower_pos_;
        const QRect lr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
        const int lrv = d_ptr_->pick(lr.center());
        opt.sliderPosition = d_ptr_->upper_pos_;
        const QRect ur = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
        const int urv = d_ptr_->pick(ur.center());

        opt.lower_rect_ = lr;
        opt.upper_rect_ = ur;
        d_ptr_->lower_rect_ = lr;
        d_ptr_->upper_rect_ = ur;

        // span
        const int minv = qMin(lrv, urv);
        const int maxv = qMax(lrv, urv);
        const QPoint c = QRect(lr.center(), ur.center()).center();
        if (orientation() == Qt::Horizontal)
        {
            opt.span_rect_ = QRect(QPoint(minv, c.y() - 15), QPoint(maxv, c.y() + 1));
            opt.span_start_ = QPoint(minv, c.y());
            opt.span_end_ = QPoint(maxv, c.y());
        }
        else
        {
            opt.span_rect_ = QRect(QPoint(c.x() - 2, minv), QPoint(c.x() + 1, maxv));
            opt.span_start_ = QPoint(c.x(), minv);
            opt.span_end_ = QPoint(c.x(), maxv);
        }

        opt.lower_handle_ = (QStyle::SubControl)DonutStyle::SC_LowerHandle;
        switch (d_ptr_->last_pressed_)
        {
        case DonutDoubleSlider::LowerHandle:
            opt.activeSubControls = (QStyle::SubControl)DonutStyle::SC_LowerHandle;
            opt.state |= QStyle::State_Sunken;
            break;
        case DonutDoubleSlider::UpperHandle:
            opt.activeSubControls = (QStyle::SubControl)DonutStyle::SC_UpperHandle;
            opt.state |= QStyle::State_Sunken;
            break;
        }

        switch (d_ptr_->hovered_handle_)
        {
        case DonutDoubleSlider::LowerHandle:
            opt.lower_hovered_ = true;
            break;
        case DonutDoubleSlider::UpperHandle:
            opt.upper_hovered_ = true;
            break;
        default:
            opt.lower_hovered_ = false;
            opt.upper_hovered_ = false;
            break;
        }

        painter.drawComplexControl(DonutStyle::CC_DoubleSlider, &opt);
    }

    // 然后使用标准QPainter绘制值标签
    QPainter labelPainter(this);
    labelPainter.setRenderHint(QPainter::Antialiasing);

    // 设置字体和颜色
    QFont font = this->font();
    font.setPixelSize(12);
    font.setBold(true);
    labelPainter.setFont(font);

    QFontMetrics fm(font);

    // 计算实际的handle位置
    QRect actualLowerRect, actualUpperRect;

    if (orientation() == Qt::Horizontal)
    {
        // 水平滑块
        int handleWidth = 16; // 假设handle宽度
        int handleHeight = 20; // 假设handle高度
        int grooveY = grooveRect.center().y();

        actualLowerRect = QRect(grooveRect.x() + lowerPixelPos - handleWidth / 2,
            grooveY - handleHeight / 2,
            handleWidth, handleHeight);

        actualUpperRect = QRect(grooveRect.x() + upperPixelPos - handleWidth / 2,
            grooveY - handleHeight / 2,
            handleWidth, handleHeight);
    }
    else
    {
        // 垂直滑块
        int handleWidth = 20; // 假设handle宽度
        int handleHeight = 16; // 假设handle高度
        int grooveX = grooveRect.center().x();

        actualLowerRect = QRect(grooveX - handleWidth / 2,
            grooveRect.y() + lowerPixelPos - handleHeight / 2,
            handleWidth, handleHeight);

        actualUpperRect = QRect(grooveX - handleWidth / 2,
            grooveRect.y() + upperPixelPos - handleHeight / 2,
            handleWidth, handleHeight);
    }

    // 绘制lower值标签
    QString lowerText = QString::number(lowerValue());
    QRect lowerTextRect = fm.boundingRect(lowerText);

    QRect lowerLabelRect;
    if (orientation() == Qt::Horizontal)
    {
        lowerLabelRect = QRect(
            actualLowerRect.center().x() - lowerTextRect.width() / 2 - 8,
            actualLowerRect.bottom() + 5,
            lowerTextRect.width() + 16,
            lowerTextRect.height() + 10
        );
    }
    else
    {
        lowerLabelRect = QRect(
            actualLowerRect.right() + 5,
            actualLowerRect.center().y() - lowerTextRect.height() / 2 - 5,
            lowerTextRect.width() + 16,
            lowerTextRect.height() + 10
        );
    }

    // 绘制lower标签
    labelPainter.setPen(Qt::NoPen);
    labelPainter.setBrush(QBrush(QColor(50, 50, 50, 200)));
    labelPainter.drawRoundedRect(lowerLabelRect, 4, 4);

    labelPainter.setPen(QPen(QColor(255, 255, 255), 1));
    labelPainter.drawText(lowerLabelRect, Qt::AlignCenter, lowerText);

    // 绘制upper值标签
    QString upperText = QString::number(upperValue());
    QRect upperTextRect = fm.boundingRect(upperText);

    QRect upperLabelRect;
    if (orientation() == Qt::Horizontal)
    {
        upperLabelRect = QRect(
            actualUpperRect.center().x() - upperTextRect.width() / 2 - 8,
            actualUpperRect.bottom() + 5,
            upperTextRect.width() + 16,
            upperTextRect.height() + 10
        );
    }
    else
    {
        upperLabelRect = QRect(
            actualUpperRect.right() + 5,
            actualUpperRect.center().y() - upperTextRect.height() / 2 - 5,
            upperTextRect.width() + 16,
            upperTextRect.height() + 10
        );
    }

    // 绘制upper标签
    labelPainter.setPen(Qt::NoPen);
    labelPainter.setBrush(QBrush(QColor(50, 50, 50, 200)));
    labelPainter.drawRoundedRect(upperLabelRect, 4, 4);

    labelPainter.setPen(QPen(QColor(255, 255, 255), 1));
    labelPainter.drawText(upperLabelRect, Qt::AlignCenter, upperText);
}