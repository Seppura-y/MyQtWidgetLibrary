#include <QThread>

// 构造函数属于主线程，run函数属于子线程
class Thread1 : public QThread
{
public:
	Thread1();

	void run() override;
};