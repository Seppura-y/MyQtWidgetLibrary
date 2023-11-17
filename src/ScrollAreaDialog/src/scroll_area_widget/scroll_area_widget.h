#ifndef SCROLL_AREA_WIDGET_H
#define SCROLL_AREA_WIDGET_H

#include <QScrollArea>
#include <QListWidget>
#include <QStringList>

class ScrollAreaWidget : public QWidget
{
	Q_OBJECT

public:
	ScrollAreaWidget(QWidget* parent = nullptr);

private slots:


private:
	QListWidget* list_wid_ = nullptr;
	QScrollArea* scroll_area_ = nullptr;

	QStringList menu_str_list_;
};


#endif