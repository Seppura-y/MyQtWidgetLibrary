#include <QThread>

class Thread1 : public QThread
{
public:
	Thread1();

	void run() override;
};