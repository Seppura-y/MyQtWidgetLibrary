#include "client_thread.h"
#include <QDebug>

ClientThread::ClientThread(QObject* parent) : QThread(parent)
{
	qDebug() << "Client create Thread id : " << currentThreadId();
	//emit connectToServer();
}

void ClientThread::run()
{
	qDebug() << "Client run Thread id : " << currentThreadId();
	//emit connectToServer();
	exec();
}