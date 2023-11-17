#include "scroll_area_widget.h"
#include <QHBoxLayout>

#include "config_helper.h"

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

	QHBoxLayout* h_layout = new QHBoxLayout(this);
	h_layout->addWidget(list_wid_);
	h_layout->addWidget(scroll_area_);

    this->setStyleSheet(ConfigHelper::getInstance()->getQssString(":resources/res/css/scroll_area_widget.css"));
}
