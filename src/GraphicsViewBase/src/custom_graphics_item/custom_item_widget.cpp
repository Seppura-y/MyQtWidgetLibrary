#include "custom_item_widget.h"

#include "custom_rect_item.h"

#include <QGraphicsView>

CustomItemWidget::CustomItemWidget(QWidget* parent)
{
	this->resize(1280, 720);

	view_ = new QGraphicsView(this);
	view_->setGeometry(3, 3, this->width() - 6, this->height() - 6);
	view_->show();

	QRect rect = view_->rect();
	scene_ = new QGraphicsScene(rect);

	view_->setScene(scene_);

	CustomRectItem* rect_item = new CustomRectItem();
	scene_->addItem(rect_item);
}

CustomItemWidget::~CustomItemWidget()
{
}
