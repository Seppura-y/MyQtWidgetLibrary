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
	void mousePressEvent(QMouseEvent* ev) override;
	void mouseReleaseEvent(QMouseEvent* ev) override;
	void mouseMoveEvent(QMouseEvent* ev) override;
	void paintEvent(QPaintEvent* ev) override;

signals:
	void sigCustomSliderValueChanged(int value);

private:
	bool is_pressed_ = false;
	QPoint cur_mouse_pos_;
};


#endif