#include <QRunnable>

class Thread2 : public QRunnable
{
public:
	Thread2();
	~Thread2();
	void run() override;
private:
};