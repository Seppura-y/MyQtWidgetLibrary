#include "thread2.h"

#include <QThread>
#include <QDebug>

Thread2::Thread2()
{
    qDebug() << "Thread2 constructor thread id : " << QThread::currentThreadId();
    setAutoDelete(true);
}

Thread2::~Thread2()
{
    qDebug() << "Thread2 desturctor";
}

void Thread2::run()
{
    qDebug() << "Thread2 run thread id : " << QThread::currentThreadId();
}
