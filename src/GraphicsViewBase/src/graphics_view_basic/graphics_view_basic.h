#ifndef GRAPHICS_VIEW_BASIC_H
#define GRAPHICS_VIEW_BASIC_H

#include <QObject>
#include <QGraphicsView>

class GraphicsViewBasic : public QGraphicsView
{
	Q_OBJECT
public:
	GraphicsViewBasic(QWidget* parent = nullptr);

signals:
	void sigMouseMovePoint(QPoint point);
	void sigMouseClickedPoint(QPoint point);
protected:
	void mouseMoveEvent(QMouseEvent* ev) override;
	void mousePressEvent(QMouseEvent* ev) override;


};


#endif