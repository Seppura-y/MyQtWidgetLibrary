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

    // �������Ǵ��ڵĵ���λ�ã� ��Qt::Popup����
    QPoint p1 = pb_dialog_show_->mapToGlobal(QPoint(0, 0));  //��ť���Ͻ����������ľ���λ��
    QRect rect1 = pb_dialog_show_->rect();

    int x = p1.x() + rect1.width() / 2 - triangle_start_x - 20 / 2;
    int y = p1.y() + rect1.height() + 1 - 15;
    pDialog->move(x, y);

    pDialog->show();
}