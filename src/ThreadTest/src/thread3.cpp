#include "thread3.h"
#include <QDebug>

Thread3::Thread3()
{
	this->moveToThread(&thread_);
	thread_.start();

	qDebug() << "Thread3 constructor thread id : " << QThread::currentThreadId();
}

void Thread3::func()
{
	qDebug() << "Thread3 func thread id : " << QThread::currentThreadId();

	while (1)
	{
		qDebug() << "func";
		QThread::msleep(500);
	}
}
