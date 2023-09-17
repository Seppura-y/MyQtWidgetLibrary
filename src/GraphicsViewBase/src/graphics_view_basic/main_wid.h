#ifndef MAIN_WID_H
#define MAIN_WID_H

#include "graphics_view_basic.h"

#include <QWidget>
#include <QLabel>
#include <QGraphicsScene>

class MainWid : public QWidget
{
	Q_OBJECT

public:
	MainWid(QWidget* parent = nullptr);
	~MainWid();

private:
	void initGraphicsView();

private slots:
	void onMouseMovePoint(QPoint point);
	void onMouseClickedPoint(QPoint point);

private:
	QGraphicsScene* scene_ = nullptr;
	GraphicsViewBasic* view_ = nullptr;
	QLabel* lab_scene_pos_ = nullptr;
	QLabel* lab_view_pos_ = nullptr;
	QLabel* lab_item_pos_ = nullptr;
};

#endif