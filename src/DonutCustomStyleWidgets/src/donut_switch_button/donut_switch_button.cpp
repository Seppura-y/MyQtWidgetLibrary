#include "donut_switch_button.h"
#include "donut_switch_button_p.h"

#include "donut_style.h"
#include "donut_style_painter.h"

#include <QStylePainter>
#include <QStyleOption>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QApplication>
#include <QPainterPath>
#include <QFontMetrics>

DonutSwitchButton::DonutSwitchButton(QWidget* parent)
    : QAbstractButton(parent), d_ptr_(new DonutSwitchButtonPrivate)
{
    d_ptr_->q_ptr_ = this;
    d_ptr_->init();
    setStyle(new DonutStyle);

    // Connect animation
    connect(d_ptr_->animation_, &QPropertyAnimation::valueChanged,
        this, &DonutSwitchButton::onAnimationValueChanged);
    connect(d_ptr_->animation_, &QPropertyAnimation::finished,
        this, &DonutSwitchButton::onAnimationFinished);
}

DonutSwitchButton::~DonutSwitchButton()
{
    delete d_ptr_;
}

// Basic properties
bool DonutSwitchButton::isChecked() const
{
    return d_ptr_->is_checked_;
}

int DonutSwitchButton::animationDuration() const
{
    return d_ptr_->animation_duration_;
}

// Color properties
QColor DonutSwitchButton::onColor() const { return d_ptr_->on_color_; }
QColor DonutSwitchButton::offColor() const { return d_ptr_->off_color_; }
QColor DonutSwitchButton::knobColor() const { return d_ptr_->knob_color_; }
QColor DonutSwitchButton::disabledColor() const { return d_ptr_->disabled_color_; }
QColor DonutSwitchButton::onTextColor() const { return d_ptr_->on_text_color_; }
QColor DonutSwitchButton::offTextColor() const { return d_ptr_->off_text_color_; }
QColor DonutSwitchButton::knobTextColor() const { return d_ptr_->knob_text_color_; }
QColor DonutSwitchButton::borderColor() const { return d_ptr_->border_color_; }

// Shape properties
DonutSwitchButton::KnobShape DonutSwitchButton::knobShape() const { return d_ptr_->knob_shape_; }
DonutSwitchButton::TrackShape DonutSwitchButton::trackShape() const { return d_ptr_->track_shape_; }
int DonutSwitchButton::borderWidth() const { return d_ptr_->border_width_; }
int DonutSwitchButton::trackRadius() const { return d_ptr_->track_radius_; }
int DonutSwitchButton::knobRadius() const { return d_ptr_->knob_radius_; }

// Text properties
QString DonutSwitchButton::onText() const { return d_ptr_->on_text_; }
QString DonutSwitchButton::offText() const { return d_ptr_->off_text_; }
QString DonutSwitchButton::knobText() const { return d_ptr_->knob_text_; }
bool DonutSwitchButton::showText() const { return d_ptr_->show_text_; }
bool DonutSwitchButton::showKnobText() const { return d_ptr_->show_knob_text_; }
QFont DonutSwitchButton::textFont() const { return d_ptr_->text_font_; }
QFont DonutSwitchButton::knobTextFont() const { return d_ptr_->knob_text_font_; }

// Layout properties
int DonutSwitchButton::trackMargin() const { return d_ptr_->track_margin_; }
int DonutSwitchButton::knobMargin() const { return d_ptr_->knob_margin_; }

// Setters
void DonutSwitchButton::setChecked(bool checked)
{
    if (d_ptr_->is_checked_ == checked)
        return;

    d_ptr_->is_checked_ = checked;
    d_ptr_->startAnimation(checked);

    emit toggled(checked);
    update();
}

void DonutSwitchButton::setAnimationDuration(int duration)
{
    d_ptr_->animation_duration_ = duration;
    d_ptr_->animation_->setDuration(duration);
}

// Color setters
void DonutSwitchButton::setOnColor(const QColor& color) { d_ptr_->on_color_ = color; update(); }
void DonutSwitchButton::setOffColor(const QColor& color) { d_ptr_->off_color_ = color; update(); }
void DonutSwitchButton::setKnobColor(const QColor& color) { d_ptr_->knob_color_ = color; update(); }
void DonutSwitchButton::setDisabledColor(const QColor& color) { d_ptr_->disabled_color_ = color; update(); }
void DonutSwitchButton::setOnTextColor(const QColor& color) { d_ptr_->on_text_color_ = color; update(); }
void DonutSwitchButton::setOffTextColor(const QColor& color) { d_ptr_->off_text_color_ = color; update(); }
void DonutSwitchButton::setKnobTextColor(const QColor& color) { d_ptr_->knob_text_color_ = color; update(); }
void DonutSwitchButton::setBorderColor(const QColor& color) { d_ptr_->border_color_ = color; update(); }

// Shape setters
void DonutSwitchButton::setKnobShape(KnobShape shape) { d_ptr_->knob_shape_ = shape; update(); }
void DonutSwitchButton::setTrackShape(TrackShape shape) { d_ptr_->track_shape_ = shape; update(); }
void DonutSwitchButton::setBorderWidth(int width) { d_ptr_->border_width_ = width; update(); }
void DonutSwitchButton::setTrackRadius(int radius) { d_ptr_->track_radius_ = radius; update(); }
void DonutSwitchButton::setKnobRadius(int radius) { d_ptr_->knob_radius_ = radius; update(); }

// Text setters
void DonutSwitchButton::setOnText(const QString& text) { d_ptr_->on_text_ = text; update(); }
void DonutSwitchButton::setOffText(const QString& text) { d_ptr_->off_text_ = text; update(); }
void DonutSwitchButton::setKnobText(const QString& text) { d_ptr_->knob_text_ = text; update(); }
void DonutSwitchButton::setShowText(bool show) { d_ptr_->show_text_ = show; update(); }
void DonutSwitchButton::setShowKnobText(bool show) { d_ptr_->show_knob_text_ = show; update(); }
void DonutSwitchButton::setTextFont(const QFont& font) { d_ptr_->text_font_ = font; update(); }
void DonutSwitchButton::setKnobTextFont(const QFont& font) { d_ptr_->knob_text_font_ = font; update(); }

// Layout setters
void DonutSwitchButton::setTrackMargin(int margin) { d_ptr_->track_margin_ = margin; d_ptr_->updateLayout(); update(); }
void DonutSwitchButton::setKnobMargin(int margin) { d_ptr_->knob_margin_ = margin; d_ptr_->updateLayout(); update(); }

void DonutSwitchButton::toggle()
{
    setChecked(!isChecked());
}

QSize DonutSwitchButton::sizeHint() const
{
    return QSize(80, 40);
}

QSize DonutSwitchButton::minimumSizeHint() const
{
    return QSize(50, 25);
}

void DonutSwitchButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

        QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Colors based on state
    QColor trackColor;
    QColor knobColor = d_ptr_->knob_color_;

    if (!isEnabled()) {
        trackColor = d_ptr_->disabled_color_;
        knobColor = knobColor.darker(150);
    }
    else {
        // Interpolate between off and on colors based on animation position
        qreal ratio = d_ptr_->knob_position_;
        trackColor = QColor(
            d_ptr_->off_color_.red() + ratio * (d_ptr_->on_color_.red() - d_ptr_->off_color_.red()),
            d_ptr_->off_color_.green() + ratio * (d_ptr_->on_color_.green() - d_ptr_->off_color_.green()),
            d_ptr_->off_color_.blue() + ratio * (d_ptr_->on_color_.blue() - d_ptr_->off_color_.blue())
        );
    }

    // Add hover effect
    if (d_ptr_->is_hovered_ && isEnabled()) {
        trackColor = trackColor.lighter(110);
    }

    // Draw track
    QRectF trackRect = d_ptr_->trackRect();
    drawTrack(painter, trackRect, trackColor);

    // Draw knob
    QRectF knobRect = d_ptr_->knobRect();

    // Add shadow effect
    QRectF shadowRect = knobRect.adjusted(1, 1, 1, 1);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 50));

    if (d_ptr_->knob_shape_ == CircleKnob) {
        painter.drawEllipse(shadowRect);
    }
    else {
        painter.drawRoundedRect(shadowRect, d_ptr_->knob_radius_, d_ptr_->knob_radius_);
    }

    // Draw knob
    drawKnob(painter, knobRect, knobColor);

    // Add highlight effect when pressed
    if (d_ptr_->is_pressed_) {
        painter.setBrush(QColor(255, 255, 255, 50));
        painter.setPen(Qt::NoPen);
        drawKnob(painter, knobRect, QColor(255, 255, 255, 50));
    }

    // Draw text
    drawText(painter);
}

void DonutSwitchButton::drawTrack(QPainter& painter, const QRectF& rect, const QColor& color)
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);

    switch (d_ptr_->track_shape_) {
    case RoundedTrack:
        painter.drawRoundedRect(rect, d_ptr_->track_radius_ > 0 ? d_ptr_->track_radius_ : rect.height() / 2,
            d_ptr_->track_radius_ > 0 ? d_ptr_->track_radius_ : rect.height() / 2);
        break;
    case RectangleTrack:
        painter.drawRect(rect);
        break;
    case EllipseTrack:
        painter.drawEllipse(rect);
        break;
    case CustomTrack:
        // Can be extended for custom shapes
        painter.drawRoundedRect(rect, d_ptr_->track_radius_, d_ptr_->track_radius_);
        break;
    }

    // Draw border
    if (d_ptr_->border_width_ > 0) {
        painter.setPen(QPen(d_ptr_->border_color_, d_ptr_->border_width_));
        painter.setBrush(Qt::NoBrush);

        switch (d_ptr_->track_shape_) {
        case RoundedTrack:
            painter.drawRoundedRect(rect, d_ptr_->track_radius_ > 0 ? d_ptr_->track_radius_ : rect.height() / 2,
                d_ptr_->track_radius_ > 0 ? d_ptr_->track_radius_ : rect.height() / 2);
            break;
        case RectangleTrack:
            painter.drawRect(rect);
            break;
        case EllipseTrack:
            painter.drawEllipse(rect);
            break;
        case CustomTrack:
            painter.drawRoundedRect(rect, d_ptr_->track_radius_, d_ptr_->track_radius_);
            break;
        }
    }
}

void DonutSwitchButton::drawKnob(QPainter& painter, const QRectF& rect, const QColor& color)
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);

    switch (d_ptr_->knob_shape_) {
    case CircleKnob:
        painter.drawEllipse(rect);
        break;
    case RoundedRectKnob:
        painter.drawRoundedRect(rect, d_ptr_->knob_radius_, d_ptr_->knob_radius_);
        break;
    case SquareKnob:
        painter.drawRect(rect);
        break;
    case DiamondKnob: {
        QPainterPath path;
        QPointF center = rect.center();
        qreal halfWidth = rect.width() / 2;
        qreal halfHeight = rect.height() / 2;
        path.moveTo(center.x(), center.y() - halfHeight);
        path.lineTo(center.x() + halfWidth, center.y());
        path.lineTo(center.x(), center.y() + halfHeight);
        path.lineTo(center.x() - halfWidth, center.y());
        path.closeSubpath();
        painter.drawPath(path);
        break;
    }
    case CustomKnob:
        // Can be extended for custom shapes
        painter.drawRoundedRect(rect, d_ptr_->knob_radius_, d_ptr_->knob_radius_);
        break;
    }

    // Draw knob border
    if (d_ptr_->border_width_ > 0) {
        painter.setPen(QPen(d_ptr_->border_color_.darker(120), 1));
        painter.setBrush(Qt::NoBrush);

        switch (d_ptr_->knob_shape_) {
        case CircleKnob:
            painter.drawEllipse(rect);
            break;
        case RoundedRectKnob:
            painter.drawRoundedRect(rect, d_ptr_->knob_radius_, d_ptr_->knob_radius_);
            break;
        case SquareKnob:
            painter.drawRect(rect);
            break;
        case DiamondKnob: {
            QPainterPath path;
            QPointF center = rect.center();
            qreal halfWidth = rect.width() / 2;
            qreal halfHeight = rect.height() / 2;
            path.moveTo(center.x(), center.y() - halfHeight);
            path.lineTo(center.x() + halfWidth, center.y());
            path.lineTo(center.x(), center.y() + halfHeight);
            path.lineTo(center.x() - halfWidth, center.y());
            path.closeSubpath();
            painter.drawPath(path);
            break;
        }
        case CustomKnob:
            painter.drawRoundedRect(rect, d_ptr_->knob_radius_, d_ptr_->knob_radius_);
            break;
        }
    }
}

void DonutSwitchButton::drawText(QPainter& painter)
{
    if (!d_ptr_->show_text_ && !d_ptr_->show_knob_text_)
        return;

    painter.setRenderHint(QPainter::TextAntialiasing);

    // Draw track text
    if (d_ptr_->show_text_) {
        painter.setFont(d_ptr_->text_font_);

        // On text (right side)
        if (!d_ptr_->on_text_.isEmpty()) {
            QRectF onRect = d_ptr_->onTextRect();
            painter.setPen(d_ptr_->on_text_color_);
            painter.drawText(onRect, Qt::AlignCenter, d_ptr_->on_text_);
        }

        // Off text (left side)
        if (!d_ptr_->off_text_.isEmpty()) {
            QRectF offRect = d_ptr_->offTextRect();
            painter.setPen(d_ptr_->off_text_color_);
            painter.drawText(offRect, Qt::AlignCenter, d_ptr_->off_text_);
        }
    }

    // Draw knob text
    if (d_ptr_->show_knob_text_ && !d_ptr_->knob_text_.isEmpty()) {
        painter.setFont(d_ptr_->knob_text_font_);
        painter.setPen(d_ptr_->knob_text_color_);
        QRectF knobRect = d_ptr_->knobRect();
        painter.drawText(knobRect, Qt::AlignCenter, d_ptr_->knob_text_);
    }
}

void DonutSwitchButton::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        d_ptr_->is_pressed_ = true;
        update();
    }
    QAbstractButton::mousePressEvent(event);
}

void DonutSwitchButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && d_ptr_->is_pressed_) {
        d_ptr_->is_pressed_ = false;

        if (rect().contains(event->pos())) {
            toggle();
            emit clicked(isChecked());
        }
        update();
    }
    QAbstractButton::mouseReleaseEvent(event);
}

void DonutSwitchButton::resizeEvent(QResizeEvent* event)
{
    QAbstractButton::resizeEvent(event);
    d_ptr_->updateLayout();
}

void DonutSwitchButton::enterEvent(QEvent* event)
{
    d_ptr_->is_hovered_ = true;
    update();
    QAbstractButton::enterEvent(event);
}

void DonutSwitchButton::leaveEvent(QEvent* event)
{
    d_ptr_->is_hovered_ = false;
    update();
    QAbstractButton::leaveEvent(event);
}

void DonutSwitchButton::onAnimationValueChanged()
{
    update();
}

void DonutSwitchButton::onAnimationFinished()
{
    update();
}

void DonutSwitchButton::initStyleOption(QStyleOptionButton* opt) const
{
    if (!opt)
        return;

    opt->init(this);
    opt->initFrom(this);

    if (isChecked())
        opt->state |= QStyle::State_On;
    else
        opt->state |= QStyle::State_Off;
}

void DonutSwitchButton::updateKnobPosition()
{
    d_ptr_->updateLayout();
    update();
}

// DonutSwitchButtonPrivate implementation

DonutSwitchButtonPrivate::DonutSwitchButtonPrivate()
    : is_checked_(false)
    , is_pressed_(false)
    , is_hovered_(false)
    , animation_(nullptr)
    , knob_position_(0.0)
    , animation_duration_(200)
    , track_margin_(2)
    , knob_margin_(2)
{
}

DonutSwitchButtonPrivate::~DonutSwitchButtonPrivate()
{
}

void DonutSwitchButtonPrivate::init()
{
    q_ptr_->setObjectName("DonutSwitchButton");
    q_ptr_->setCheckable(true);
    q_ptr_->setAttribute(Qt::WA_Hover, true);

    // Setup colors
    on_color_ = QColor(0, 150, 250);      // Blue
    off_color_ = QColor(180, 180, 180);   // Gray
    knob_color_ = QColor(255, 255, 255);  // White
    disabled_color_ = QColor(200, 200, 200); // Light gray
    on_text_color_ = QColor(255, 255, 255);  // White
    off_text_color_ = QColor(100, 100, 100); // Dark gray
    knob_text_color_ = QColor(100, 100, 100); // Dark gray
    border_color_ = QColor(150, 150, 150);   // Gray

    // Setup shapes
    knob_shape_ = DonutSwitchButton::CircleKnob;
    track_shape_ = DonutSwitchButton::RoundedTrack;
    border_width_ = 0;
    track_radius_ = -1; // Auto
    knob_radius_ = 4;

    // Setup text
    on_text_ = "ON";
    off_text_ = "OFF";
    knob_text_ = "";
    show_text_ = false;
    show_knob_text_ = false;
    text_font_ = q_ptr_->font();
    text_font_.setPixelSize(10);
    knob_text_font_ = q_ptr_->font();
    knob_text_font_.setPixelSize(8);

    // Setup animation
    animation_ = new QPropertyAnimation(this, "knobPosition");
    animation_->setDuration(animation_duration_);
    animation_->setEasingCurve(QEasingCurve::OutCubic);

    updateLayout();
}

void DonutSwitchButtonPrivate::updateLayout()
{
    if (!q_ptr_)
        return;

    QRectF widgetRect = q_ptr_->rect();

    // Calculate track rectangle (smaller than widget to leave margin)
    track_rect_ = widgetRect.adjusted(track_margin_, track_margin_,
        -track_margin_, -track_margin_);

    // Knob size is slightly smaller than track height
    knob_size_ = track_rect_.height() - (knob_margin_ * 2);
}

void DonutSwitchButtonPrivate::startAnimation(bool checked)
{
    animation_->stop();

    qreal startValue = knob_position_;
    qreal endValue = checked ? 1.0 : 0.0;

    animation_->setStartValue(startValue);
    animation_->setEndValue(endValue);
    animation_->start();
}

void DonutSwitchButtonPrivate::setKnobPosition(qreal position)
{
    knob_position_ = qBound(0.0, position, 1.0);
}

QRectF DonutSwitchButtonPrivate::trackRect() const
{
    return track_rect_;
}

QRectF DonutSwitchButtonPrivate::knobRect() const
{
    return knobRectAtPosition(knob_position_);
}

QRectF DonutSwitchButtonPrivate::knobRectAtPosition(qreal position) const
{
    QRectF track = trackRect();  // 修复：正确调用函数

    qreal knobRadius = knob_size_ / 2.0;
    qreal trackPadding = knob_margin_;

    qreal minX = track.left() + trackPadding + knobRadius;
    qreal maxX = track.right() - trackPadding - knobRadius;

    qreal knobX = minX + position * (maxX - minX);
    qreal knobY = track.center().y();

    return QRectF(knobX - knobRadius, knobY - knobRadius, knob_size_, knob_size_);
}

QRectF DonutSwitchButtonPrivate::onTextRect() const
{
    QRectF track = trackRect();  // 修复：正确调用函数
    QRectF knob = knobRect();    // 修复：正确调用函数

    return QRectF(knob.right(), track.top(),
        track.right() - knob.right(), track.height());
}

QRectF DonutSwitchButtonPrivate::offTextRect() const
{
    QRectF track = trackRect();  // 修复：正确调用函数
    QRectF knob = knobRect();    // 修复：正确调用函数

    return QRectF(track.left(), track.top(),
        knob.left() - track.left(), track.height());
}

#include "donut_switch_button.moc"