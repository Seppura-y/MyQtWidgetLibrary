#ifndef MAIN_WIN_H
#define MAIN_WIN_H

#include "mouse_move_painter_widget.h"

#include <QMainWindow>
#include <QMenu>

class MainWin : public QMainWindow
{
	Q_OBJECT
public:
	MainWin(QWidget* parent = nullptr);
	~MainWin();

protected:
	void contextMenuEvent(QContextMenuEvent* ev) override;
private:
	MouseMovePainterWidget* painter_widget_ = nullptr;
	QMenu* menu_;
};

#endif