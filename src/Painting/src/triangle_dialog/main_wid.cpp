#include "main_wid.h"

#include "triangle_dialog.h"
MainWid::MainWid(QWidget* parent)
	: QWidget(parent)
{
	this->setGeometry(1200, 500, 1280, 720);

	pb_dialog_show_ = new QPushButton(this);
	pb_dialog_show_->setGeometry(this->width() / 2 - 30, 100, 60, 30);
	pb_dialog_show_->setText("show");
	pb_dialog_show_->show();

	QObject::connect(pb_dialog_show_, &QPushButton::clicked, this, &MainWid::onDialogShow);
}

MainWid::~MainWid()
{
}

void MainWid::onDialogShow()
{
    int triangle_start_x = 60;

    TriangleDialog* pDialog = new TriangleDialog(343, 320, this);
    pDialog->setTrianglePosition(triangle_start_x, 20, 12);

    // 设置三角窗口的弹出位置， 有Qt::Popup属性
    QPoint p1 = pb_dialog_show_->mapToGlobal(QPoint(0, 0));  //按钮左上角相对于桌面的绝对位置
    QRect rect1 = pb_dialog_show_->rect();

    int x = p1.x() + rect1.width() / 2 - triangle_start_x - 20 / 2;
    int y = p1.y() + rect1.height() + 1 - 15;
    pDialog->move(x, y);

    pDialog->show();
}