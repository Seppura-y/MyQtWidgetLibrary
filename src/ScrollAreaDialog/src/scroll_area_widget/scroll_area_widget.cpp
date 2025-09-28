#include "scroll_area_widget.h"

#include "config_helper.h"
#include "scroll_area_item_base.h"

#include <QScrollBar>
#include <QHBoxLayout>
#include <string>

ScrollAreaWidget::ScrollAreaWidget(QWidget* parent)
	: QWidget(parent)
{
	setFixedSize(150 + 1000 + 30 + 15, 900);
	list_wid_ = new QListWidget(this);
	list_wid_->setFixedWidth(150);
	//list_wid_->setFrameShape(QFrame::NoFrame);
	list_wid_->setFocusPolicy(Qt::NoFocus);

	menu_str_list_ << u8"基本设置" << u8"云盘设置" << u8"下载设置" << u8"接管设置"
		<< u8"任务管理" << u8"悬浮窗口" << u8"高级设置" << u8"12" << u8"23" << u8"445" << u8"78" << u8"12.";

	list_wid_->addItems(menu_str_list_);

	scroll_area_ = new QScrollArea(this);
	scroll_area_->setFixedWidth(1000 + 30);
	scroll_area_->setFrameShape(QFrame::NoFrame);
	//scroll_area_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    this->setStyleSheet(ConfigHelper::getInstance()->getQssString(":resources/res/css/scroll_area_widget.css"));

	setting_widget_1_ = new ScrollAreaItemBase();
	setting_widgets_.push_back(setting_widget_1_);

	setting_widget_2_ = new ScrollAreaItemBase();
	setting_widgets_.push_back(setting_widget_2_);

	setting_widget_3_ = new ScrollAreaItemBase();
	setting_widgets_.push_back(setting_widget_3_);

	setting_widget_4_ = new ScrollAreaItemBase();
	setting_widgets_.push_back(setting_widget_4_);

	setting_widget_5_ = new ScrollAreaItemBase();
	setting_widgets_.push_back(setting_widget_5_);

	setting_widget_6_ = new ScrollAreaItemBase();
	setting_widgets_.push_back(setting_widget_6_);


	QWidget* widget = new QWidget();
	QVBoxLayout* v_layout = new QVBoxLayout(widget);
	for (auto wid : setting_widgets_)
	{
		v_layout->addWidget(wid);
		v_layout->addSpacing(10);
	}
	v_layout->setContentsMargins(0, 5, 0, 5);
	scroll_area_->setWidget(widget);

	QHBoxLayout* h_layout = new QHBoxLayout(this);
	h_layout->addWidget(list_wid_);
	h_layout->setSpacing(1);
	h_layout->addWidget(scroll_area_);

	QObject::connect(list_wid_, &QListWidget::itemClicked, this, &ScrollAreaWidget::onListItemClicked);
	QObject::connect(scroll_area_->verticalScrollBar(), &QScrollBar::valueChanged, this, &ScrollAreaWidget::onScrollValueChanged);
	
}

void ScrollAreaWidget::onListItemClicked(QListWidgetItem* item)
{
	is_item_clicked_ = true;
	QString item_text = item->text();
	QPoint widget_pos;
	int size = menu_str_list_.size();
	for (int i = 0; i < size; i++)
	{
		if (item_text == menu_str_list_[i])
		{
			widget_pos = setting_widgets_[i]->pos();
		}
	}
	scroll_area_->verticalScrollBar()->setValue(widget_pos.y());
}


void ScrollAreaWidget::onScrollValueChanged(int value)
{
	if (!is_item_clicked_)
	{
		int size = setting_widgets_.size();
		for (int i = 0; i < size; i++)
		{
			if (!setting_widgets_[i]->visibleRegion().isEmpty())
			{
				list_wid_->item(i)->setSelected(true);
				return;
			}
			else
			{
				list_wid_->item(i)->setSelected(false);
			}
		}
	}

	is_item_clicked_ = false;
}
