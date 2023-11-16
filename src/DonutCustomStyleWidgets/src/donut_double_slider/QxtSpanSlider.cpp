#include "QxtSpanSlider.h"
/****************************************************************************
** Copyright (c) 2006 - 2011, the LibQxt project.
** See the Qxt AUTHORS file for a list of authors and copyright holders.
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the LibQxt project nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
** DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
** <http://libqxt.org>  <foundation@libqxt.org>
*****************************************************************************/

#include "QxtSpanSlider_p.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QStylePainter>
#include <QStyleOptionSlider>
#include <QStylePainter>

#include "round_widget.h"
#include "donut_style.h"
#include "donut_style_painter.h"
#include "donut_double_slider_p.h"
//#include "donut_slider_custom_style.h"

QxtSpanSliderPrivate::QxtSpanSliderPrivate() :
        lower_(0),
        upper_(0),
        lower_pos_(0),
        upper_pos_(0),
        offset_(0),
        position_(0),
        last_pressed_(QxtSpanSlider::NoHandle),
        main_control_(QxtSpanSlider::LowerHandle),
        lower_pressed_(QStyle::SC_None),
        upper_pressed_(QStyle::SC_None),
        movement_(QxtSpanSlider::FreeMovement),
        first_movement_(false),
        block_tracking_(false)
{
}

void QxtSpanSliderPrivate::initStyleOption(QStyleOptionSlider* option, QxtSpanSlider::SpanHandle handle) const
{
    const QxtSpanSlider* p = q_ptr;
    p->initStyleOption(option);
    option->sliderPosition = (handle == QxtSpanSlider::LowerHandle ? lower_pos_ : upper_pos_);
    option->sliderValue = (handle == QxtSpanSlider::LowerHandle ? lower_ : upper_);
}

int QxtSpanSliderPrivate::pixelPosToRangeValue(int pos) const
{
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    int slider_min = 0;
    int slider_max = 0;
    int handle_length = 0;
    const QSlider* p = q_ptr;
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

void QxtSpanSliderPrivate::handleMousePress(const QPoint& pos, QStyle::SubControl& control, int value, QxtSpanSlider::SpanHandle handle)
{
    QStyleOptionSlider opt;
    initStyleOption(&opt, handle);

    QxtSpanSlider* p = q_ptr;
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

QRect QxtSpanSliderPrivate::getSpan(QPainter* painter, const QRect& rect) const
{
    DonutDoubleSliderStyleOption options;
    initStyleOption(&options);

    const QSlider* p = q_ptr;
    // area
    QRect groove = p->style()->subControlRect(QStyle::CC_Slider, &options, QStyle::SC_SliderGroove, p);

    return rect.intersected(groove);
}

void QxtSpanSliderPrivate::triggerAction(QAbstractSlider::SliderAction action, bool main)
{
    int value = 0;
    bool no = false;
    bool up = false;
    const int min = q_ptr->minimum();
    const int max = q_ptr->maximum();
    const QxtSpanSlider::SpanHandle altControl = (main_control_ == QxtSpanSlider::LowerHandle ? QxtSpanSlider::UpperHandle : QxtSpanSlider::LowerHandle);

    block_tracking_ = true;

    switch (action)
    {
    case QAbstractSlider::SliderSingleStepAdd:
        if ((main && main_control_ == QxtSpanSlider::UpperHandle) || (!main && altControl == QxtSpanSlider::UpperHandle))
        {
            value = qBound(min, upper_ + q_ptr->singleStep(), max);
            up = true;
            break;
        }
        value = qBound(min, lower_ + q_ptr->singleStep(), max);
        break;
    case QAbstractSlider::SliderSingleStepSub:
        if ((main && main_control_ == QxtSpanSlider::UpperHandle) || (!main && altControl == QxtSpanSlider::UpperHandle))
        {
            value = qBound(min, upper_ - q_ptr->singleStep(), max);
            up = true;
            break;
        }
        value = qBound(min, lower_ - q_ptr->singleStep(), max);
        break;
    case QAbstractSlider::SliderToMinimum:
        value = min;
        if ((main && main_control_ == QxtSpanSlider::UpperHandle) || (!main && altControl == QxtSpanSlider::UpperHandle))
            up = true;
        break;
    case QAbstractSlider::SliderToMaximum:
        value = max;
        if ((main && main_control_ == QxtSpanSlider::UpperHandle) || (!main && altControl == QxtSpanSlider::UpperHandle))
            up = true;
        break;
    case QAbstractSlider::SliderMove:
        if ((main && main_control_ == QxtSpanSlider::UpperHandle) || (!main && altControl == QxtSpanSlider::UpperHandle))
            up = true;
    case QAbstractSlider::SliderNoAction:
        no = true;
        break;
    default:
        qWarning("QxtSpanSliderPrivate::triggerAction: Unknown action");
        break;
    }

    if (!no && !up)
    {
        if (movement_ == QxtSpanSlider::NoCrossing)
            value = qMin(value, upper_);
        else if (movement_ == QxtSpanSlider::NoOverlapping)
            value = qMin(value, upper_ - 1);

        if (movement_ == QxtSpanSlider::FreeMovement && value > upper_)
        {
            swapControls();
            q_ptr->setUpperPosition(value);
        }
        else
        {
            q_ptr->setLowerPosition(value);
        }
    }
    else if (!no)
    {
        if (movement_ == QxtSpanSlider::NoCrossing)
            value = qMax(value, lower_);
        else if (movement_ == QxtSpanSlider::NoOverlapping)
            value = qMax(value, lower_ + 1);

        if (movement_ == QxtSpanSlider::FreeMovement && value < lower_)
        {
            swapControls();
            q_ptr->setLowerPosition(value);
        }
        else
        {
            q_ptr->setUpperPosition(value);
        }
    }

    block_tracking_ = false;
    q_ptr->setLowerValue(lower_pos_);
    q_ptr->setUpperValue(upper_pos_);
}

void QxtSpanSliderPrivate::swapControls()
{
    qSwap(lower_, upper_);
    qSwap(lower_pressed_, upper_pressed_);
    last_pressed_ = (last_pressed_ == QxtSpanSlider::LowerHandle ? QxtSpanSlider::UpperHandle : QxtSpanSlider::LowerHandle);
    main_control_ = (main_control_ == QxtSpanSlider::LowerHandle ? QxtSpanSlider::UpperHandle : QxtSpanSlider::LowerHandle);
}

void QxtSpanSliderPrivate::updateRange(int min, int max)
{
    Q_UNUSED(min);
    Q_UNUSED(max);
    // setSpan() takes care of keeping span in range
    q_ptr->setSpan(lower_, upper_);
}

void QxtSpanSliderPrivate::movePressedHandle()
{
    switch (last_pressed_)
    {
        case QxtSpanSlider::LowerHandle:
            if (lower_pos_ != lower_)
            {
                bool main = (main_control_ == QxtSpanSlider::LowerHandle);
                triggerAction(QAbstractSlider::SliderMove, main);
            }
            break;
        case QxtSpanSlider::UpperHandle:
            if (upper_pos_ != upper_)
            {
                bool main = (main_control_ == QxtSpanSlider::UpperHandle);
                triggerAction(QAbstractSlider::SliderMove, main);
            }
            break;
        default:
            break;
    }
}

/*!
    \class QxtSpanSlider
    \inmodule QxtWidgets
    \brief The QxtSpanSlider widget is a QSlider with two handles.
    QxtSpanSlider is a slider with two handles. QxtSpanSlider is
    handy for letting user to choose an span between min/max.
    The span color is calculated based on QPalette::Highlight.
    The keys are bound according to the following table:
    \table
    \header \o Orientation    \o Key           \o Handle
    \row    \o Qt::Horizontal \o Qt::Key_Left  \o lower
    \row    \o Qt::Horizontal \o Qt::Key_Right \o lower
    \row    \o Qt::Horizontal \o Qt::Key_Up    \o upper
    \row    \o Qt::Horizontal \o Qt::Key_Down  \o upper
    \row    \o Qt::Vertical   \o Qt::Key_Up    \o lower
    \row    \o Qt::Vertical   \o Qt::Key_Down  \o lower
    \row    \o Qt::Vertical   \o Qt::Key_Left  \o upper
    \row    \o Qt::Vertical   \o Qt::Key_Right \o upper
    \endtable
    Keys are bound by the time the slider is created. A key is bound
    to same handle for the lifetime of the slider. So even if the handle
    representation might change from lower to upper, the same key binding
    remains.
    \image qxtspanslider.png "QxtSpanSlider in Plastique style."
    \bold {Note:} QxtSpanSlider inherits QSlider for implementation specific
    reasons. Adjusting any single handle specific properties like
    \list
    \o QAbstractSlider::sliderPosition
    \o QAbstractSlider::value
    \endlist
    has no effect. However, all slider specific properties like
    \list
    \o QAbstractSlider::invertedAppearance
    \o QAbstractSlider::invertedControls
    \o QAbstractSlider::minimum
    \o QAbstractSlider::maximum
    \o QAbstractSlider::orientation
    \o QAbstractSlider::pageStep
    \o QAbstractSlider::singleStep
    \o QSlider::tickInterval
    \o QSlider::tickPosition
    \endlist
    are taken into consideration.
 */

/*!
    \enum QxtSpanSlider::HandleMovementMode
    This enum describes the available handle movement modes.
    \value FreeMovement The handles can be moved freely.
    \value NoCrossing The handles cannot cross, but they can still overlap each other. The lower and upper values can be the same.
    \value NoOverlapping The handles cannot overlap each other. The lower and upper values cannot be the same.
 */

/*!
    \enum QxtSpanSlider::SpanHandle
    This enum describes the available span handles.
    \omitvalue NoHandle \omit Internal only (for now). \endomit
    \value LowerHandle The lower boundary handle.
    \value UpperHandle The upper boundary handle.
 */

/*!
    \fn QxtSpanSlider::lowerValueChanged(int lower)
    This signal is emitted whenever the \a lower value has changed.
 */

/*!
    \fn QxtSpanSlider::upperValueChanged(int upper)
    This signal is emitted whenever the \a upper value has changed.
 */

/*!
    \fn QxtSpanSlider::spanChanged(int lower, int upper)
    This signal is emitted whenever both the \a lower and the \a upper
    values have changed ie. the span has changed.
 */

/*!
    \fn QxtSpanSlider::lower_pos_itionChanged(int lower)
    This signal is emitted whenever the \a lower position has changed.
 */

/*!
    \fn QxtSpanSlider::upper_pos_itionChanged(int upper)
    This signal is emitted whenever the \a upper position has changed.
 */

/*!
    \fn QxtSpanSlider::sliderPressed(SpanHandle handle)
    This signal is emitted whenever the \a handle has been pressed.
 */

/*!
    Constructs a new QxtSpanSlider with \a parent.
 */
QxtSpanSlider::QxtSpanSlider(QWidget* parent) : QSlider(parent), d_ptr(new QxtSpanSliderPrivate())
{
    d_ptr->q_ptr = this;
    connect(this, SIGNAL(rangeChanged(int, int)), d_ptr, SLOT(updateRange(int, int)));
    connect(this, SIGNAL(sliderReleased()), d_ptr, SLOT(movePressedHandle()));

    this->setStyle(new DonutStyle);
    setMouseTracking(true);
}

/*!
    Constructs a new QxtSpanSlider with \a orientation and \a parent.
 */
QxtSpanSlider::QxtSpanSlider(Qt::Orientation orientation, QWidget* parent) : QSlider(orientation, parent), d_ptr(new QxtSpanSliderPrivate())
{
    d_ptr->q_ptr = this;
    connect(this, SIGNAL(rangeChanged(int, int)), d_ptr, SLOT(updateRange(int, int)));
    connect(this, SIGNAL(sliderReleased()), d_ptr, SLOT(movePressedHandle()));

    this->setStyle(new DonutStyle);
    setMouseTracking(true);
    //this->installEventFilter(style);
}

/*!
    Destructs the span slider.
 */
QxtSpanSlider::~QxtSpanSlider()
{
}

/*!
    \property QxtSpanSlider::handleMovementMode
    \brief the handle movement mode
 */
QxtSpanSlider::HandleMovementMode QxtSpanSlider::handleMovementMode() const
{
    return d_ptr->movement_;
}

void QxtSpanSlider::setHandleMovementMode(QxtSpanSlider::HandleMovementMode mode)
{
    d_ptr->movement_ = mode;
}

/*!
    \property QxtSpanSlider::lowerValue
    \brief the lower value of the span
 */
int QxtSpanSlider::lowerValue() const
{
    return qMin(d_ptr->lower_, d_ptr->upper_);
}

void QxtSpanSlider::setLowerValue(int lower)
{
    setSpan(lower, d_ptr->upper_);
}

/*!
    \property QxtSpanSlider::upperValue
    \brief the upper value of the span
 */
int QxtSpanSlider::upperValue() const
{
    return qMax(d_ptr->lower_, d_ptr->upper_);
}

void QxtSpanSlider::setUpperValue(int upper)
{
    setSpan(d_ptr->lower_, upper);
}

/*!
    Sets the span from \a lower to \a upper.
 */
void QxtSpanSlider::setSpan(int lower, int upper)
{
    const int low = qBound(minimum(), qMin(lower, upper), maximum());
    const int upp = qBound(minimum(), qMax(lower, upper), maximum());
    if (low != d_ptr->lower_ || upp != d_ptr->upper_)
    {
        if (low != d_ptr->lower_)
        {
            d_ptr->lower_ = low;
            d_ptr->lower_pos_ = low;
            emit lowerValueChanged(low);
        }
        if (upp != d_ptr->upper_)
        {
            d_ptr->upper_ = upp;
            d_ptr->upper_pos_ = upp;
            emit upperValueChanged(upp);
        }
        emit spanChanged(d_ptr->lower_, d_ptr->upper_);
        update();
    }
}

/*!
    \property QxtSpanSlider::lower_pos_ition
    \brief the lower position of the span
 */
int QxtSpanSlider::lowerPosition() const
{
    return d_ptr->lower_pos_;
}

void QxtSpanSlider::setLowerPosition(int lower)
{
    if (d_ptr->lower_pos_ != lower)
    {
        d_ptr->lower_pos_ = lower;
        if (!hasTracking())
            update();
        if (isSliderDown())
            emit lowerPositionChanged(lower);
        if (hasTracking() && !d_ptr->block_tracking_)
        {
            bool main = (d_ptr->main_control_ == QxtSpanSlider::LowerHandle);
            d_ptr->triggerAction(SliderMove, main);
        }
    }
}

/*!
    \property QxtSpanSlider::upper_pos_ition
    \brief the upper position of the span
 */
int QxtSpanSlider::upperPosition() const
{
    return d_ptr->upper_pos_;
}

void QxtSpanSlider::setUpperPosition(int upper)
{
    if (d_ptr->upper_pos_ != upper)
    {
        d_ptr->upper_pos_ = upper;
        if (!hasTracking())
            update();
        if (isSliderDown())
            emit upperPositionChanged(upper);
        if (hasTracking() && !d_ptr->block_tracking_)
        {
            bool main = (d_ptr->main_control_ == QxtSpanSlider::UpperHandle);
            d_ptr->triggerAction(SliderMove, main);
        }
    }
}

/*!
    \reimp
 */
void QxtSpanSlider::keyPressEvent(QKeyEvent* event)
{
    QSlider::keyPressEvent(event);

    bool main = true;
    SliderAction action = SliderNoAction;
    switch (event->key())
    {
    case Qt::Key_Left:
        main   = (orientation() == Qt::Horizontal);
        action = !invertedAppearance() ? SliderSingleStepSub : SliderSingleStepAdd;
        break;
    case Qt::Key_Right:
        main   = (orientation() == Qt::Horizontal);
        action = !invertedAppearance() ? SliderSingleStepAdd : SliderSingleStepSub;
        break;
    case Qt::Key_Up:
        main   = (orientation() == Qt::Vertical);
        action = invertedControls() ? SliderSingleStepSub : SliderSingleStepAdd;
        break;
    case Qt::Key_Down:
        main   = (orientation() == Qt::Vertical);
        action = invertedControls() ? SliderSingleStepAdd : SliderSingleStepSub;
        break;
    case Qt::Key_Home:
        main   = (d_ptr->main_control_ == QxtSpanSlider::LowerHandle);
        action = SliderToMinimum;
        break;
    case Qt::Key_End:
        main   = (d_ptr->main_control_ == QxtSpanSlider::UpperHandle);
        action = SliderToMaximum;
        break;
    default:
        event->ignore();
        break;
    }

    if (action)
        d_ptr->triggerAction(action, main);
}

/*!
    \reimp
 */
void QxtSpanSlider::mousePressEvent(QMouseEvent* event)
{
    if (minimum() == maximum() || (event->buttons() ^ event->button()))
    {
        event->ignore();
        return;
    }

    d_ptr->handleMousePress(event->pos(), d_ptr->upper_pressed_, d_ptr->upper_, QxtSpanSlider::UpperHandle);

    if (d_ptr->upper_pressed_ != QStyle::SC_SliderHandle)
        d_ptr->handleMousePress(event->pos(), d_ptr->lower_pressed_, d_ptr->lower_, QxtSpanSlider::LowerHandle);

    d_ptr->first_movement_ = true;
    event->accept();
}

/*!
    \reimp
 */
void QxtSpanSlider::mouseMoveEvent(QMouseEvent* event)
{
    d_ptr->lower_hovered_ = false;
    d_ptr->upper_hovered_ = false;
    d_ptr->hovered_handle_ = QxtSpanSlider::NoHandle;

    if (d_ptr->lower_rect_.contains(event->pos()))
    {
        d_ptr->lower_hovered_ = true;
        d_ptr->hovered_handle_ = QxtSpanSlider::LowerHandle;
    }

    if (d_ptr->upper_rect_.contains(event->pos()))
    {
        d_ptr->upper_hovered_ = true;
        d_ptr->hovered_handle_ = QxtSpanSlider::UpperHandle;
    }
    this->update();

    if (d_ptr->lower_pressed_ != QStyle::SC_SliderHandle && d_ptr->upper_pressed_ != QStyle::SC_SliderHandle)
    {
        event->ignore();
        return;
    }

    QStyleOptionSlider opt;
    d_ptr->initStyleOption(&opt);
    const int m = style()->pixelMetric(QStyle::PM_MaximumDragDistance, &opt, this);
    int newPosition = d_ptr->pixelPosToRangeValue(d_ptr->pick(event->pos()) - d_ptr->offset_);
    if (m >= 0)
    {
        const QRect r = rect().adjusted(-m, -m, m, m);
        if (!r.contains(event->pos()))
        {
            newPosition = d_ptr->position_;
        }
    }

    // pick the preferred handle on the first movement
    if (d_ptr->first_movement_)
    {
        if (d_ptr->lower_ == d_ptr->upper_)
        {
            if (newPosition < lowerValue())
            {
                d_ptr->swapControls();
                d_ptr->first_movement_ = false;
            }
        }
        else
        {
            d_ptr->first_movement_ = false;
        }
    }

    if (d_ptr->lower_pressed_ == QStyle::SC_SliderHandle)
    {
        if (d_ptr->movement_ == NoCrossing)
            newPosition = qMin(newPosition, upperValue());
        else if (d_ptr->movement_ == NoOverlapping)
            newPosition = qMin(newPosition, upperValue() - 1);

        if (d_ptr->movement_ == FreeMovement && newPosition > d_ptr->upper_)
        {
            d_ptr->swapControls();
            setUpperPosition(newPosition);
        }
        else
        {
            setLowerPosition(newPosition);
        }
    }
    else if (d_ptr->upper_pressed_ == QStyle::SC_SliderHandle)
    {
        if (d_ptr->movement_ == NoCrossing)
            newPosition = qMax(newPosition, lowerValue());
        else if (d_ptr->movement_ == NoOverlapping)
            newPosition = qMax(newPosition, lowerValue() + 1);

        if (d_ptr->movement_ == FreeMovement && newPosition < d_ptr->lower_)
        {
            d_ptr->swapControls();
            setLowerPosition(newPosition);
        }
        else
        {
            setUpperPosition(newPosition);
        }
    }
    event->accept();
}

/*!
    \reimp
 */
void QxtSpanSlider::mouseReleaseEvent(QMouseEvent* event)
{
    QSlider::mouseReleaseEvent(event);
    setSliderDown(false);
    d_ptr->lower_pressed_ = QStyle::SC_None;
    d_ptr->upper_pressed_ = QStyle::SC_None;
    d_ptr->hovered_handle_ = QxtSpanSlider::NoHandle;
    d_ptr->lower_hovered_ = false;
    d_ptr->upper_hovered_ = false;
    update();
}


void QxtSpanSlider::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    DonutStylePainter painter(this);

    DonutDoubleSliderStyleOption opt;
    d_ptr->initStyleOption(&opt);

    opt.sliderValue = 0;
    opt.sliderPosition = 0;
    opt.subControls = QStyle::SC_SliderGroove | QStyle::SC_SliderTickmarks;

    // handle rects
    opt.sliderPosition = d_ptr->lower_pos_;
    const QRect lr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    const int lrv = d_ptr->pick(lr.center());
    opt.sliderPosition = d_ptr->upper_pos_;
    const QRect ur = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    const int urv = d_ptr->pick(ur.center());

    opt.lower_rect_ = lr;
    opt.upper_rect_ = ur;
    d_ptr->lower_rect_ = lr;
    d_ptr->upper_rect_ = ur;
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
    switch (d_ptr->last_pressed_)
    {
    case QxtSpanSlider::LowerHandle:
        opt.activeSubControls = (QStyle::SubControl)DonutStyle::SC_LowerHandle;
        opt.state |= QStyle::State_Sunken;
    case QxtSpanSlider::UpperHandle:
        opt.activeSubControls = (QStyle::SubControl)DonutStyle::SC_UpperHandle;
        opt.state |= QStyle::State_Sunken;
    }

    switch (d_ptr->hovered_handle_)
    {
    case QxtSpanSlider::LowerHandle:
        opt.lower_hovered_ = true;
        break;
    case QxtSpanSlider::UpperHandle:
        opt.upper_hovered_ = true;
        break;
    default:
        opt.lower_hovered_ = false;
        opt.upper_hovered_ = false;
        break;
    }

    painter.drawComplexControl(DonutStyle::CC_DoubleSlider, &opt);
}