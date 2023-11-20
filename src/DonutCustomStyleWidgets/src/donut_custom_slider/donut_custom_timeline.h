#ifndef DONUT_CUSTOM_TIMELINE_H
#define DONUT_CUSTOM_TIMELINE_H


#include <QSlider>

class DonutCustomTimeline : public QSlider
{
	Q_OBJECT

public:
	DonutCustomTimeline(QWidget* parent = nullptr);
	~DonutCustomTimeline();

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