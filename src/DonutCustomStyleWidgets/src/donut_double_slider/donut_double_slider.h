#ifndef DONUT_DOUBLE_SLIDER_H
#define DONUT_DOUBLE_SLIDER_H

#include <QSlider>

class DonutDoubleSliderPrivate;
class DonutDoubleSlider : public QSlider
{
	Q_OBJECT

public:
    explicit DonutDoubleSlider(QWidget* parent = nullptr);
    explicit DonutDoubleSlider(Qt::Orientation orientation, QWidget* parent = nullptr);
    ~DonutDoubleSlider();
public:
    enum HandleMovementMode
    {
        FreeMovement,
        NoCrossing,
        NoOverlapping
    };

    enum SpanHandle
    {
        NoHandle,
        LowerHandle,
        UpperHandle
    };
protected:

private:


};

#endif