#ifndef MOUSE_MOVE_PAINTER_WIDGET_H
#define MOUSE_MOVE_PAINTER_WIDGET_H

#include <QWidget>

class MouseMovePainterWidget : public QWidget
{
	Q_OBJECT

public:
	MouseMovePainterWidget(QWidget* parent = nullptr);
	~MouseMovePainterWidget();

    void endDraw();
    void clearCanvas();

protected:
    void paintEvent(QPaintEvent* ev) override;
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    void mouseDoubleClickEvent(QMouseEvent* ev) override;

    bool is_drawing_ = false;           //是否已经开始左键点击，同时标识是否开始进行绘制
    bool is_moving_ = false;            //是否处于绘制时的鼠标移动状态

    QVector<QPointF> point_list_;
    QPointF move_point_;    // 目前鼠标的位置
};


#endif