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

    bool is_drawing_ = false;           //�Ƿ��Ѿ���ʼ��������ͬʱ��ʶ�Ƿ�ʼ���л���
    bool is_moving_ = false;            //�Ƿ��ڻ���ʱ������ƶ�״̬

    QVector<QPointF> point_list_;
    QPointF move_point_;    // Ŀǰ����λ��
};


#endif