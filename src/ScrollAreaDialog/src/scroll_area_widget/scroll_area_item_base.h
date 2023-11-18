#ifndef SCROLL_AREA_ITEM_BASE_H
#define SCROLL_AREA_ITEM_BASE_H

#include <QWidget>

class ScrollAreaItemBase : public QWidget
{
	Q_OBJECT

public:
	ScrollAreaItemBase(QWidget* parent = nullptr);
	~ScrollAreaItemBase();
protected:

private:

};

#endif