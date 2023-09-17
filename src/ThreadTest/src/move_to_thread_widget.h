#include <QWidget>
#include <QPushButton>

#include "thread3.h"

class MoveToThreadWidget : public QWidget
{
	Q_OBJECT
public:
	MoveToThreadWidget(QWidget* parent = nullptr);
	~MoveToThreadWidget();
signals:
	void sigThreadStart();
public slots:
	void onThreadStart();
private:
	QPushButton* pb_start_;
	Thread3* thread_;
};