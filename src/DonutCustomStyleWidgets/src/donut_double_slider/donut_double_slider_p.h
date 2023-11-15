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

public:
	int lower_value_;
	int upper_value_;
	int lower_pos_;
	int upper_pos_;

	DonutDoubleSlider::SpanHandle last_pressed_;
	DonutDoubleSlider::SpanHandle main_control_;
	QStyle::SubControl lower_pressed_;
	QStyle::SubControl upper_pressed_;
	DonutDoubleSlider::HandleMovementMode movement_;
	bool first_movement_;
	bool block_tracking_;
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
};
#endif