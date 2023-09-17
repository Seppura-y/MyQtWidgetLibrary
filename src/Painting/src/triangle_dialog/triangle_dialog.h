#ifndef TRIANGLE_DIALOG_H
#define TRIANGLE_DIALOG_H

#include <QDialog>

class TriangleDialog : public QDialog
{
	Q_OBJECT
public:
	TriangleDialog(int width, int height, QWidget* parent = nullptr);

	void setTrianglePosition(int start_x, int width, int height);

protected:
	void paintEvent(QPaintEvent* ev) override;

private:
	int start_x_;
	int triangle_width_;
	int triangle_height_;
};

#endif