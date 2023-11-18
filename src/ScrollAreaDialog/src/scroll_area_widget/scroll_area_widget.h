#ifndef SCROLL_AREA_WIDGET_H
#define SCROLL_AREA_WIDGET_H

#include <vector>

#include <QScrollArea>
#include <QListWidget>
#include <QStringList>

class ScrollAreaItemBase;
class ScrollAreaWidget : public QWidget
{
	Q_OBJECT

public:
	ScrollAreaWidget(QWidget* parent = nullptr);

private slots:
	void onListItemClicked(QListWidgetItem* item);
	void onScrollValueChanged(int value);

private:
	QListWidget* list_wid_ = nullptr;
	QScrollArea* scroll_area_ = nullptr;

	QStringList menu_str_list_;

	ScrollAreaItemBase* setting_widget_1_ = nullptr;
	ScrollAreaItemBase* setting_widget_2_ = nullptr;
	ScrollAreaItemBase* setting_widget_3_ = nullptr;
	ScrollAreaItemBase* setting_widget_4_ = nullptr;
	ScrollAreaItemBase* setting_widget_5_ = nullptr;
	ScrollAreaItemBase* setting_widget_6_ = nullptr;

	std::vector<QWidget*> setting_widgets_;

};


#endif