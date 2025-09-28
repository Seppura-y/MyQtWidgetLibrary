#include "mouse_move_painter_widget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QStyleOption>

MouseMovePainterWidget::MouseMovePainterWidget(QWidget* parent)
    : QWidget(parent)
{
	setMouseTracking(true);

	point_list_.clear();

    this->setStyleSheet("MouseMovePainterWidget{background-color:rgba(155,155,155,155);}");
}

MouseMovePainterWidget::~MouseMovePainterWidget()
{
}

void MouseMovePainterWidget::endDraw()
{
    if (is_drawing_)
    {
        is_drawing_ = false;
        point_list_.push_back(point_list_[0]);
    }

    this->update();
}

void MouseMovePainterWidget::clearCanvas()
{
    point_list_.clear();
    this->update();
}

void MouseMovePainterWidget::paintEvent(QPaintEvent* ev)
{
    // 设置了才能使这个作为子窗口的widget的样式表生效
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QPainter painter(this);
    painter.setPen(QColor(255, 0, 0));

    QVector<QLineF> lines;

    for (int i = 0; i < point_list_.size() - 1; i++)
    {
        QLineF line(QPointF(point_list_[i].x(), point_list_[i].y()),
            QPointF(point_list_[i + 1].x(), point_list_[i + 1].y()));

        lines.push_back(line);
    }

    if (is_drawing_)
    {
        int size = point_list_.size();

        if (is_moving_ && size > 0)
        {
            QLineF line(QPointF(point_list_[point_list_.size() - 1].x(), point_list_[point_list_.size() - 1].y()),
                move_point_);

            lines.push_back(line);
        }
    }

    painter.drawLines(lines);
}

void MouseMovePainterWidget::mousePressEvent(QMouseEvent* ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        if (!is_drawing_)
        {
            point_list_.clear();
            is_drawing_ = true;
        }
    }
}

void MouseMovePainterWidget::mouseMoveEvent(QMouseEvent* ev)
{
    if (is_drawing_)
    {
        is_moving_ = true;

        move_point_ = ev->pos();

        this->update();
    }
}

void MouseMovePainterWidget::mouseReleaseEvent(QMouseEvent* ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        if (is_drawing_)
        {
            // 鼠标松开后最新的点入队列
            point_list_.push_back(QPointF(ev->x(), ev->y()));
            is_moving_ = false;
            this->update();
        }
    }
}

void MouseMovePainterWidget::mouseDoubleClickEvent(QMouseEvent* ev)
{
    endDraw();
}
