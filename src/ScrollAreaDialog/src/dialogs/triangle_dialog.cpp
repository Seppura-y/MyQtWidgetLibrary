#include "triangle_dialog.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QPainterPath>

#define SHADOW_WIDTH	15
#define TRIANGLE_WIDTH	15
#define TRIANGLE_HEIGHT	15
#define BORDER_RADIUS	5

TriangleDialog::TriangleDialog(int width, int height, QWidget* parent)
	: QDialog(parent), start_x_(50), triangle_width_(TRIANGLE_WIDTH), triangle_height_(TRIANGLE_HEIGHT)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);  // 设置透明窗口, 为窗口阴影和圆角做准备

    //UserInfoWidget* pUserinfoWidget = new UserInfoWidget(this);

    QVBoxLayout* pVlay = new QVBoxLayout(this);
    //pVlay->addWidget(pUserinfoWidget);

    //设置布局的四周边距
    pVlay->setContentsMargins(
        SHADOW_WIDTH,                   // left
        SHADOW_WIDTH + TRIANGLE_HEIGHT, // top
        SHADOW_WIDTH,                   // right
        SHADOW_WIDTH                    // bottom
    );

    // 设置阴影边框
    auto shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setColor(Qt::red);
    shadowEffect->setBlurRadius(SHADOW_WIDTH);
    this->setGraphicsEffect(shadowEffect);

    //设置窗口固定大小
    setFixedSize(width, height);
}


void TriangleDialog::setTrianglePosition(int start_x, int width, int height)
{
    start_x_ = start_x;
    triangle_width_ = width;
    triangle_height_ = height;
}

void TriangleDialog::paintEvent(QPaintEvent* ev)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(55, 55, 55));

    // 以下计算注意坐标原点是左上角
    QPolygon triangle_polygon;
    triangle_polygon << QPoint(start_x_, triangle_height_ + SHADOW_WIDTH);      // 左
    triangle_polygon << QPoint(start_x_ + triangle_width_ / 2, SHADOW_WIDTH);   // 中
    triangle_polygon << QPoint(start_x_ + triangle_width_, triangle_height_ + SHADOW_WIDTH);    // 右

    QPainterPath draw_path;
    draw_path.addRoundedRect(
        QRect(
            SHADOW_WIDTH,                                           // left
            SHADOW_WIDTH + triangle_height_,                        // top
            this->width() - SHADOW_WIDTH * 2,                       // width
            this->height() - SHADOW_WIDTH * 2 - triangle_height_),  // height
            BORDER_RADIUS, BORDER_RADIUS                            // 倒角
    );

    draw_path.addPolygon(triangle_polygon);

    painter.drawPath(draw_path);
}
