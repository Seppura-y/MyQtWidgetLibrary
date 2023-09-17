#ifndef ITEM_SELECT_WIDGET_H
#define ITEM_SELECT_WIDGET_H

#include <QWidget>
#include <QTreeView>

#include <memory>

#include "painter_widget.h"

class ItemSelectWidget : public QWidget
{
	Q_OBJECT
public:
	ItemSelectWidget(QWidget* parent = nullptr);
	~ItemSelectWidget();

private:
	void treeView();

private slots:
	void onTreeViewExpand(const QModelIndex& index);

private:
	QTreeView* item_tree_ = nullptr;
	PainterWidget* painter_widget_ = nullptr;
};

#endif