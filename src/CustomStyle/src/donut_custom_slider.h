#ifndef DONUT_CUSTOM_SLIDER_H
#define DONUT_CUSTOM_SLIDER_H


#include <QSlider>

class DonutCustomSlider : public QSlider
{
	Q_OBJECT

public:
	DonutCustomSlider(QWidget* parent = nullptr);
	~DonutCustomSlider();

protected:
	void mouseMoveEvent(QMouseEvent* ev) override;
	void paintEvent(QPaintEvent* ev) override;
private:
	QPoint cur_mouse_pos_;
};


#endif