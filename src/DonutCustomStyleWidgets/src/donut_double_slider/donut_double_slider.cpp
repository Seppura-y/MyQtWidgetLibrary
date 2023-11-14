#include "donut_double_slider.h"
#include "donut_double_slider_p.h"
#include "donut_style.h"


DonutDoubleSliderStyleOption::DonutDoubleSliderStyleOption()
	: QStyleOptionSlider()
{

}


DonutDoubleSliderPrivate::DonutDoubleSliderPrivate()
{

}

void DonutDoubleSliderPrivate::initStyleOption(QStyleOptionSlider* option, DonutDoubleSlider::SpanHandle handle) const
{

}


DonutDoubleSlider::DonutDoubleSlider(QWidget* parent)
{
	setStyle(new DonutStyle);
}

DonutDoubleSlider::DonutDoubleSlider(Qt::Orientation orientation, QWidget* parent)
{
	setStyle(new DonutStyle);
}

DonutDoubleSlider::~DonutDoubleSlider()
{
}
