#include <QThread>

// ���캯���������̣߳�run�����������߳�
class Thread1 : public QThread
{
public:
	Thread1();

	void run() override;
};