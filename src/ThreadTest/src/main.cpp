#include <QtWidgets/QApplication>
#include "round_widget.h"

#include "thread1.h"
#include "move_to_thread_widget.h"

#include <QDebug>

void test()
{
    qDebug() << "test thread id : " << QThread::currentThreadId();
    Thread1 t;
    t.start();  // 退出此函数线程对象会直接销毁，导致崩溃
                // 需要在事件循环内等待线程结束？
}

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    qDebug() << "Main thread id : " << QThread::currentThreadId();

    //RoundWidget w;
    MoveToThreadWidget w;
    w.show();

    Thread1 thread;
    thread.start();

    //test();

    return a.exec();
}