#include "donut_timeline.h"
#include "donut_timeline_p.h"
#include "donut_style.h"
#include "donut_style_painter.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QStylePainter>
#include <QStyleOptionSlider>
#include <QStylePainter>

DonutTimelineStyleOption::DonutTimelineStyleOption()
	: QStyleOptionSlider()
{

}

DonutTimelinePrivate::DonutTimelinePrivate() :
    lower_(0),
    upper_(0),
    lower_pos_(0),
    upper_pos_(0),
    offset_(0),
    position_(0),
    last_pressed_(DonutTimeline::NoHandle),
    main_control_(DonutTimeline::LowerHandle),
    lower_pressed_(QStyle::SC_None),
    upper_pressed_(QStyle::SC_None),
    movement_(DonutTimeline::FreeMovement),
    first_movement_(false),
    block_tracking_(false)
{
}

void DonutTimelinePrivate::initStyleOption(QStyleOptionSlider* option, DonutTimeline::SpanHandle handle) const
{
    const DonutTimeline* p = q_ptr_;
    p->initStyleOption(option);
    option->sliderPosition = (handle == DonutTimeline::LowerHandle ? lower_pos_ : upper_pos_);
    option->sliderValue = (handle == DonutTimeline::LowerHandle ? lower_ : upper_);
}





int DonutTimelinePrivate::pixelPosToRangeValue(int pos) const
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

void DonutTimelinePrivate::handleMousePress(const QPoint& pos, QStyle::SubControl& control, int value, DonutTimeline::SpanHandle handle)
{
    QStyleOptionSlider opt;
    initStyleOption(&opt, handle);

    DonutTimeline* p = q_ptr_;
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

QRect DonutTimelinePrivate::getSpan(QPainter* painter, const QRect& rect) const
{
    DonutTimelineStyleOption options;
    initStyleOption(&options);

    const QSlider* p = q_ptr_;
    // area
    QRect groove = p->style()->subControlRect(QStyle::CC_Slider, &options, QStyle::SC_SliderGroove, p);

    return rect.intersected(groove);
}

void DonutTimelinePrivate::triggerAction(QAbstractSlider::SliderAction action, bool main)
{
    int value = 0;
    bool no = false;
    bool up = false;
    const int min = q_ptr_->minimum();
    const int max = q_ptr_->maximum();
    const DonutTimeline::SpanHandle altControl = (main_control_ == DonutTimeline::LowerHandle ? DonutTimeline::UpperHandle : DonutTimeline::LowerHandle);

    block_tracking_ = true;

    switch (action)
    {
    case QAbstractSlider::SliderSingleStepAdd:
        if ((main && main_control_ == DonutTimeline::UpperHandle) || (!main && altControl == DonutTimeline::UpperHandle))
        {
            value = qBound(min, upper_ + q_ptr_->singleStep(), max);
            up = true;
            break;
        }
        value = qBound(min, lower_ + q_ptr_->singleStep(), max);
        break;
    case QAbstractSlider::SliderSingleStepSub:
        if ((main && main_control_ == DonutTimeline::UpperHandle) || (!main && altControl == DonutTimeline::UpperHandle))
        {
            value = qBound(min, upper_ - q_ptr_->singleStep(), max);
            up = true;
            break;
        }
        value = qBound(min, lower_ - q_ptr_->singleStep(), max);
        break;
    case QAbstractSlider::SliderToMinimum:
        value = min;
        if ((main && main_control_ == DonutTimeline::UpperHandle) || (!main && altControl == DonutTimeline::UpperHandle))
            up = true;
        break;
    case QAbstractSlider::SliderToMaximum:
        value = max;
        if ((main && main_control_ == DonutTimeline::UpperHandle) || (!main && altControl == DonutTimeline::UpperHandle))
            up = true;
        break;
    case QAbstractSlider::SliderMove:
        if ((main && main_control_ == DonutTimeline::UpperHandle) || (!main && altControl == DonutTimeline::UpperHandle))
            up = true;
    case QAbstractSlider::SliderNoAction:
        no = true;
        break;
    default:
        qWarning("DonutTimelinePrivate::triggerAction: Unknown action");
        break;
    }

    if (!no && !up)
    {
        if (movement_ == DonutTimeline::NoCrossing)
            value = qMin(value, upper_);
        else if (movement_ == DonutTimeline::NoOverlapping)
            value = qMin(value, upper_ - 1);

        if (movement_ == DonutTimeline::FreeMovement && value > upper_)
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
        if (movement_ == DonutTimeline::NoCrossing)
            value = qMax(value, lower_);
        else if (movement_ == DonutTimeline::NoOverlapping)
            value = qMax(value, lower_ + 1);

        if (movement_ == DonutTimeline::FreeMovement && value < lower_)
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

void DonutTimelinePrivate::swapControls()
{
    qSwap(lower_, upper_);
    qSwap(lower_pressed_, upper_pressed_);
    last_pressed_ = (last_pressed_ == DonutTimeline::LowerHandle ? DonutTimeline::UpperHandle : DonutTimeline::LowerHandle);
    main_control_ = (main_control_ == DonutTimeline::LowerHandle ? DonutTimeline::UpperHandle : DonutTimeline::LowerHandle);
}

void DonutTimelinePrivate::updateRange(int min, int max)
{
    Q_UNUSED(min);
    Q_UNUSED(max);
    // setSpan() takes care of keeping span in range
    q_ptr_->setSpan(lower_, upper_);
}

void DonutTimelinePrivate::movePressedHandle()
{
    switch (last_pressed_)
    {
    case DonutTimeline::LowerHandle:
        if (lower_pos_ != lower_)
        {
            bool main = (main_control_ == DonutTimeline::LowerHandle);
            triggerAction(QAbstractSlider::SliderMove, main);
        }
        break;
    case DonutTimeline::UpperHandle:
        if (upper_pos_ != upper_)
        {
            bool main = (main_control_ == DonutTimeline::UpperHandle);
            triggerAction(QAbstractSlider::SliderMove, main);
        }
        break;
    default:
        break;
    }
}


DonutTimeline::DonutTimeline(QWidget* parent) : QSlider(parent), d_ptr_(new DonutTimelinePrivate())
{
    d_ptr_->q_ptr_ = this;
    connect(this, SIGNAL(rangeChanged(int, int)), d_ptr_, SLOT(updateRange(int, int)));
    connect(this, SIGNAL(sliderReleased()), d_ptr_, SLOT(movePressedHandle()));

    this->setStyle(new DonutStyle);
    setMouseTracking(true);
}

DonutTimeline::DonutTimeline(Qt::Orientation orientation, QWidget* parent) : QSlider(orientation, parent), d_ptr_(new DonutTimelinePrivate())
{
    d_ptr_->q_ptr_ = this;
    connect(this, SIGNAL(rangeChanged(int, int)), d_ptr_, SLOT(updateRange(int, int)));
    connect(this, SIGNAL(sliderReleased()), d_ptr_, SLOT(movePressedHandle()));

    this->setStyle(new DonutStyle);
    setMouseTracking(true);
}

DonutTimeline::~DonutTimeline()
{
}

DonutTimeline::HandleMovementMode DonutTimeline::handleMovementMode() const
{
    return d_ptr_->movement_;
}

void DonutTimeline::setHandleMovementMode(DonutTimeline::HandleMovementMode mode)
{
    d_ptr_->movement_ = mode;
}

int DonutTimeline::lowerValue() const
{
    return qMin(d_ptr_->lower_, d_ptr_->upper_);
}

void DonutTimeline::setLowerValue(int lower)
{
    setSpan(lower, d_ptr_->upper_);
}

int DonutTimeline::upperValue() const
{
    return qMax(d_ptr_->lower_, d_ptr_->upper_);
}

void DonutTimeline::setUpperValue(int upper)
{
    setSpan(d_ptr_->lower_, upper);
}

void DonutTimeline::setSpan(int lower, int upper)
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


int DonutTimeline::lowerPosition() const
{
    return d_ptr_->lower_pos_;
}

void DonutTimeline::setLowerPosition(int lower)
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
            bool main = (d_ptr_->main_control_ == DonutTimeline::LowerHandle);
            d_ptr_->triggerAction(SliderMove, main);
        }
    }
}


int DonutTimeline::upperPosition() const
{
    return d_ptr_->upper_pos_;
}

void DonutTimeline::setUpperPosition(int upper)
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
            bool main = (d_ptr_->main_control_ == DonutTimeline::UpperHandle);
            d_ptr_->triggerAction(SliderMove, main);
        }
    }
}


void DonutTimeline::keyPressEvent(QKeyEvent* event)
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
        main = (d_ptr_->main_control_ == DonutTimeline::LowerHandle);
        action = SliderToMinimum;
        break;
    case Qt::Key_End:
        main = (d_ptr_->main_control_ == DonutTimeline::UpperHandle);
        action = SliderToMaximum;
        break;
    default:
        event->ignore();
        break;
    }

    if (action)
        d_ptr_->triggerAction(action, main);
}

void DonutTimeline::mousePressEvent(QMouseEvent* event)
{
    if (minimum() == maximum() || (event->buttons() ^ event->button()))
    {
        event->ignore();
        return;
    }

    d_ptr_->handleMousePress(event->pos(), d_ptr_->upper_pressed_, d_ptr_->upper_, DonutTimeline::UpperHandle);

    if (d_ptr_->upper_pressed_ != QStyle::SC_SliderHandle)
        d_ptr_->handleMousePress(event->pos(), d_ptr_->lower_pressed_, d_ptr_->lower_, DonutTimeline::LowerHandle);

    d_ptr_->first_movement_ = true;
    event->accept();
}

void DonutTimeline::mouseMoveEvent(QMouseEvent* event)
{
    d_ptr_->lower_hovered_ = false;
    d_ptr_->upper_hovered_ = false;
    d_ptr_->hovered_handle_ = DonutTimeline::NoHandle;

    if (d_ptr_->lower_rect_.contains(event->pos()))
    {
        d_ptr_->lower_hovered_ = true;
        d_ptr_->hovered_handle_ = DonutTimeline::LowerHandle;
    }

    if (d_ptr_->upper_rect_.contains(event->pos()))
    {
        d_ptr_->upper_hovered_ = true;
        d_ptr_->hovered_handle_ = DonutTimeline::UpperHandle;
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

void DonutTimeline::mouseReleaseEvent(QMouseEvent* event)
{
    QSlider::mouseReleaseEvent(event);
    setSliderDown(false);
    d_ptr_->lower_pressed_ = QStyle::SC_None;
    d_ptr_->upper_pressed_ = QStyle::SC_None;
    d_ptr_->hovered_handle_ = DonutTimeline::NoHandle;
    d_ptr_->lower_hovered_ = false;
    d_ptr_->upper_hovered_ = false;
    update();
}


void DonutTimeline::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    DonutStylePainter painter(this);

    DonutTimelineStyleOption opt;
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
    QRect spanRect;
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
    case DonutTimeline::LowerHandle:
        opt.activeSubControls = (QStyle::SubControl)DonutStyle::SC_LowerHandle;
        opt.state |= QStyle::State_Sunken;
    case DonutTimeline::UpperHandle:
        opt.activeSubControls = (QStyle::SubControl)DonutStyle::SC_UpperHandle;
        opt.state |= QStyle::State_Sunken;
    }

    switch (d_ptr_->hovered_handle_)
    {
    case DonutTimeline::LowerHandle:
        opt.lower_hovered_ = true;
        break;
    case DonutTimeline::UpperHandle:
        opt.upper_hovered_ = true;
        break;
    default:
        opt.lower_hovered_ = false;
        opt.upper_hovered_ = false;
        break;
    }

    painter.drawComplexControl(DonutStyle::CC_DoubleSlider, &opt);
}