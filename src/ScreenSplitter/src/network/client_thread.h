#pragma once
#include <QThread>

class ClientThread : public QThread
{
public:
	explicit ClientThread(QObject* parent = nullptr);
	void run() override;

private:

};

