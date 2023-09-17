#ifndef CUSTOM_ITEM_WIDGET_H
#define CUSTOM_ITEM_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsScene>

class CustomItemWidget : public QWidget
{
	Q_OBJECT

public:
	CustomItemWidget(QWidget* parent = nullptr);
	~CustomItemWidget();

private:
	QGraphicsScene* scene_ = nullptr;
	QGraphicsView* view_ = nullptr;
};

#endif