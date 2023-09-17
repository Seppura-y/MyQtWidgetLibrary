#include <QObject>
#include <QThread>

class Thread3 : public QObject
{
public:
	Thread3();

public slots:
	void func();

private:
	QThread thread_;
};