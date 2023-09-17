#ifndef PAINTER_WIDGET_H
#define PAINTER_WIDGET_H

#include <QWidget>
#include "draw_type.h"

class PainterWidget : public QWidget
{
    Q_OBJECT

public:
    PainterWidget(QWidget* p = nullptr);
    ~PainterWidget() {}

    void setDrawType(DRAW_TYPE type);

private:
    void paintEvent(QPaintEvent* event) override;

private:
    void drawPoint();
    void drawMultipoints();
    void drawLine();
    void drawArc();
    void drawRect();
    void drawRoundrect();
    void drawChord();
    void drawEllipse();
    void drawPolygon();
    void drawPolyline();
    void drawConvexPloygon();
    void drawLines();
    void drawPath();
    void drawPie();
    void drawImage();
    void drawPixmap();
    void drawText();
    void drawErase();
    void drawFillpath();
    void drawFillrect();

private:
    DRAW_TYPE draw_type_;

    int width_ = 0;
    int height_ = 0;
};


#endif