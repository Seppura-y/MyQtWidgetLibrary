#include "thread1.h"

#include <QDebug>


Thread1::Thread1()
{
	qDebug() << "Thread1 constructor thread id : " << QThread::currentThreadId();

}

void Thread1::run()
{
	qDebug() << "Thread1 run thread id : " << QThread::currentThreadId();

	while (1)
	{
		qDebug() << "Thread1 run";
		QThread::msleep(500);
	}
}
