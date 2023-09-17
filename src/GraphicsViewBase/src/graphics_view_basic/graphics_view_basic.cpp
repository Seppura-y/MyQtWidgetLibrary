#include "graphics_view_basic.h"

#include <QMouseEvent>
#include <QPoint>

GraphicsViewBasic::GraphicsViewBasic(QWidget* parent)
	: QGraphicsView(parent)
{
	this->setCursor(Qt::CrossCursor);
	this->setMouseTracking(true);
	this->setDragMode(QGraphicsView::RubberBandDrag);
}

void GraphicsViewBasic::mouseMoveEvent(QMouseEvent* ev)
{
	QPoint point = ev->pos();
	emit sigMouseMovePoint(point);
	QGraphicsView::mouseMoveEvent(ev);
}

void GraphicsViewBasic::mousePressEvent(QMouseEvent* ev)
{
	if (ev->button() == Qt::LeftButton)
	{
		QPoint point = ev->pos();
		emit sigMouseClickedPoint(point);
	}

	QGraphicsView::mousePressEvent(ev);
}
