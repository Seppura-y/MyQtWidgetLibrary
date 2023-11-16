#ifndef DONUT_DOUBLE_SLIDER_P_H
#define DONUT_DOUBLE_SLIDER_P_H

#include <QStyle>
#include <QObject>
#include <QStyleOptionSlider>
#include <QStyleOptionComplex>
#include "donut_double_slider.h"

QT_FORWARD_DECLARE_CLASS(QStylePainter)
QT_FORWARD_DECLARE_CLASS(QStyleOptionSlider)

// DonutDoubleSlider的数据类
class DonutDoubleSliderPrivate : public QObject
{
	Q_OBJECT

public:
	DonutDoubleSliderPrivate();
	void initStyleOption(QStyleOptionSlider* option, DonutDoubleSlider::SpanHandle handle = DonutDoubleSlider::UpperHandle) const;

    int pick(const QPoint& pt) const
    {
        return q_ptr_->orientation() == Qt::Horizontal ? pt.x() : pt.y();
    }
    int pixelPosToRangeValue(int pos) const;

    // 鼠标点击事件中，分别代入 lower_pressed_ 和 upper_pressed_ 记录此次鼠标点中的是哪个SubControl
    void handleMousePress(const QPoint& pos, QStyle::SubControl& control, int value, DonutDoubleSlider::SpanHandle handle);

    QRect getSpan(QPainter* painter, const QRect& rect) const;

    void triggerAction(QAbstractSlider::SliderAction action, bool main);
    void swapControls();

    int lower_;
    int upper_;
    int lower_pos_;
    int upper_pos_;
    int offset_;
    int position_;

    // 记录最后点击的是哪个handle
    DonutDoubleSlider::SpanHandle last_pressed_;
    DonutDoubleSlider::SpanHandle main_control_;

    // 记录鼠标点中的是哪个SubControl
    QStyle::SubControl lower_pressed_;
    // 记录鼠标点中的是哪个SubControl
    QStyle::SubControl upper_pressed_;

    DonutDoubleSlider::HandleMovementMode movement_;
    bool first_movement_;
    bool block_tracking_;

    QRect lower_rect_;
    QRect upper_rect_;
    bool lower_hovered_;
    bool upper_hovered_;
    DonutDoubleSlider::SpanHandle hovered_handle_;

public Q_SLOTS:
    void updateRange(int min, int max);
    void movePressedHandle();

private:

	DonutDoubleSlider* q_ptr_;
	friend class DonutDoubleSlider;
};

class DonutDoubleSliderStyleOption : public QStyleOptionSlider
{
public:
	DonutDoubleSliderStyleOption();
	DonutDoubleSliderStyleOption(const DonutDoubleSliderStyleOption& other) : QStyleOptionSlider() { *this = other; }
	DonutDoubleSliderStyleOption& operator=(const DonutDoubleSliderStyleOption&) = default;
public:
	QRect upper_rect_;
	QRect lower_rect_;
	QRect span_rect_;

	QPoint span_start_;
	QPoint span_end_;

	int upper_position_;
	int lower_position_;

	QStyle::SubControls lower_handle_;
	QStyle::SubControls upper_handle_;

	bool lower_hovered_ = false;
	bool upper_hovered_ = false;
};
#endif