#include "main_win.h"

#include <QAction>

MainWin::MainWin(QWidget* parent)
{
	this->resize(1920, 1080);
	painter_widget_ = new MouseMovePainterWidget(this);
	painter_widget_->setGeometry(0, 0, this->width(), this->height()-50);
	painter_widget_->show();

	menu_ = new QMenu(this);
	QAction* act_end = new QAction(QString::fromLocal8Bit("end draw"), this);
	act_end->setShortcut(QKeySequence("Ctrl+E"));

	QAction* act_clear = new QAction(QString::fromLocal8Bit("clear canvas"), this);
	act_end->setShortcut(QKeySequence("Ctrl+D"));

	QAction* act_exit = new QAction(QString::fromLocal8Bit("exit menu"), this);

	menu_->addAction(act_end);
	menu_->addAction(act_clear);
	menu_->addAction(act_exit);

	menu_->setStyleSheet("QMenu{font:18px;}");

	connect(act_end, &QAction::triggered, [=] {
		painter_widget_->endDraw();
	});

	connect(act_clear, &QAction::triggered, [=] {
		painter_widget_->clearCanvas();
	});
}

MainWin::~MainWin()
{
}

void MainWin::contextMenuEvent(QContextMenuEvent* ev)
{
	menu_->move(cursor().pos());
	menu_->show();
}
