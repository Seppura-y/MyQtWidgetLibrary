#ifndef MAIN_WID_H
#define MAIN_WID_H

#include <QWidget>
#include <QPushButton>

class MainWid : public QWidget
{
	Q_OBJECT
public:
	MainWid(QWidget* parent = nullptr);
	~MainWid();

public slots:
	void onDialogShow();

private:
	QPushButton* pb_dialog_show_ = nullptr;

};

#endif