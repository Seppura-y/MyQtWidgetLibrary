#include <QtWidgets/QApplication>
#include "round_widget.h"

#include "thread1.h"
#include "move_to_thread_widget.h"

#include <QDebug>

void test()
{
    qDebug() << "test thread id : " << QThread::currentThreadId();
    Thread1 t;
    t.start();  // �˳��˺����̶߳����ֱ�����٣����±���
                // ��Ҫ���¼�ѭ���ڵȴ��߳̽�����
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