#ifndef DONUT_SWITCH_BUTTON_P_H
#define DONUT_SWITCH_BUTTON_P_H

#include <QObject>
#include <QStyle>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QColor>
#include <QRectF>
#include <QFont>
#include "donut_switch_button.h"

QT_FORWARD_DECLARE_CLASS(QStylePainter)
QT_FORWARD_DECLARE_CLASS(QStyleOptionSlider)

class DonutSwitchButtonPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal knobPosition READ knobPosition WRITE setKnobPosition)

public:
    explicit DonutSwitchButtonPrivate();
    ~DonutSwitchButtonPrivate();

    void init();
    void updateLayout();
    void startAnimation(bool checked);

    // Property accessors
    qreal knobPosition() const { return knob_position_; }
    void setKnobPosition(qreal position);

    // Layout calculations
    QRectF trackRect() const;
    QRectF knobRect() const;
    QRectF knobRectAtPosition(qreal position) const;
    QRectF onTextRect() const;
    QRectF offTextRect() const;

public:
    DonutSwitchButton* q_ptr_;

    // State
    bool is_checked_;
    bool is_pressed_;
    bool is_hovered_;
    
    // Animation
    QPropertyAnimation* animation_;
    qreal knob_position_; // 0.0 = off, 1.0 = on
    int animation_duration_;
    
    // Colors
    QColor on_color_;
    QColor off_color_;
    QColor knob_color_;
    QColor disabled_color_;
    QColor on_text_color_;
    QColor off_text_color_;
    QColor knob_text_color_;
    QColor border_color_;
    
    // Shapes
    DonutSwitchButton::KnobShape knob_shape_;
    DonutSwitchButton::TrackShape track_shape_;
    int border_width_;
    int track_radius_;
    int knob_radius_;
    
    // Text
    QString on_text_;
    QString off_text_;
    QString knob_text_;
    bool show_text_;
    bool show_knob_text_;
    QFont text_font_;
    QFont knob_text_font_;
    
    // Layout
    QRectF track_rect_;
    qreal knob_size_;
    int track_margin_;
    int knob_margin_;

    friend class DonutSwitchButton;
};

#endif
