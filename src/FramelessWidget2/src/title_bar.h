#ifndef TITLE_BAR_H
#define TITLE_BAR_H

#include <QWidget>

class QPushButton;
class QLabel;

class TitleBar : public QWidget
{
	Q_OBJECT

public:
	TitleBar(QWidget* p = nullptr);
	~TitleBar();

private:
	void initUI();

private:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;

private slots:
	void onClicked();

signals:
	void sigClose();

private:
	QLabel* lab_logo_;
	QLabel* lab_title_;

	QPushButton* pb_set_;
	QPushButton* pb_min_;
	QPushButton* pb_max_;
	QPushButton* pb_close_;

};

#endif