#ifndef DONUT_DOUBLE_SLIDER_P_H
#define DONUT_DOUBLE_SLIDER_P_H

#include <QStyle>
#include <QObject>
#include "donut_double_slider.h"

QT_FORWARD_DECLARE_CLASS(QStylePainter)
QT_FORWARD_DECLARE_CLASS(QStyleOptionSlider)

class DonutDoubleSliderPrivate : public QObject
{
	Q_OBJECT

public:
	DonutDoubleSliderPrivate();

public:
	int lower_value_;
	int upper_value_;
	int lower_pos_;
	int upper_pos_;
private:

	DonutDoubleSlider* q_ptr_;
	friend class DonutDoubleSlider;
};
#endif