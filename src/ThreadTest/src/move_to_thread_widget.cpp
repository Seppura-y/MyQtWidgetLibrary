#include "move_to_thread_widget.h"
#include <QDebug>


MoveToThreadWidget::MoveToThreadWidget(QWidget* parent)
	: QWidget(parent)
{
	qDebug() << "MoveToThreadWidget constructor thread id : " << QThread::currentThreadId();


	this->setGeometry(1500, 800, 480, 360);
	pb_start_ = new QPushButton(this);
	pb_start_->setGeometry(100, 100, 50, 30);
	pb_start_->setText("start");

	thread_ = new Thread3();

	QObject::connect(pb_start_, &QPushButton::clicked, this, &MoveToThreadWidget::onThreadStart);
	QObject::connect(this, &MoveToThreadWidget::sigThreadStart, thread_, &Thread3::func);


	this->show();
}

MoveToThreadWidget::~MoveToThreadWidget()
{
	delete pb_start_;
}

void MoveToThreadWidget::onThreadStart()
{
	emit sigThreadStart();
}