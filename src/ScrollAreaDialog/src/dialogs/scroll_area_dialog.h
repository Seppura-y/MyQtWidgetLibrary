#ifndef SCROLL_AREA_DIALOG_H
#define SCROLL_AREA_DIALOG_H

#include <QScrollArea>
#include <QListWidget>
#include <QStringList>

class ScrollAreaDialog : public QWidget
{
	Q_OBJECT

public:
	ScrollAreaDialog(QWidget* parent = nullptr);

private slots:


private:
	QListWidget* list_wid_ = nullptr;
	QScrollArea* scroll_area_ = nullptr;

	QStringList* menu_str_list_ = nullptr;
};


#endif