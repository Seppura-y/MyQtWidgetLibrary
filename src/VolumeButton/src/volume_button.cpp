#include "volume_button.h"
#include <QMouseEvent>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <iostream>
#include <QThread>

#include "config_helper.h"

VolumeButton::VolumeButton(QWidget *parent) : QPushButton(parent)
{
	this->setFixedSize(32, 32);

	this->setStyleSheet(ConfigHelper::GetInstance()->GetQssString(":volume_button/res/css/button.css"));
}

VolumeButton::~VolumeButton()
{
}

void VolumeButton::initUi()
{
}




void VolumeButton::paintEvent(QPaintEvent* ev)
{
	QStylePainter p(this);
	QStyleOptionButton option;
	initStyleOption(&option);
	p.drawControl(QStyle::CE_PushButton, option);
}

void VolumeButton::enterEvent(QEvent* ev)
{
	if (!volume_slider_dialog_)
	{
		volume_slider_dialog_ = new VolumeSliderDialog(this);
	}
		
	QPoint button_pos = this->mapToGlobal(QPoint(0, 0));
	QRect button_rect = this->rect();
	QRect dialog_rect = volume_slider_dialog_->rect();	//rect包含标题栏，去掉标题栏后height不变

	int x = button_pos.x() + (button_rect.width() - dialog_rect.width()) / 2;
	int y = button_pos.y() - dialog_rect.height() - 5;
	volume_slider_dialog_->move(x, y);	//相对于global

	volume_slider_dialog_->show();
	timer_id_ = startTimer(250);

	connect(volume_slider_dialog_, &VolumeSliderDialog::sigSliderValueChanged, [=](int value) {
		emit sigVolumeValueChanged(value);
		});
}

void VolumeButton::mousePressEvent(QMouseEvent* ev)
{
	if (ev->button() == Qt::LeftButton)
	{
		is_mute_ = !is_mute_;
		if (is_mute_)
		{
			if (volume_slider_dialog_)
				volume_slider_dialog_->setSliderValue(0);
		}
		else
		{
			if (volume_slider_dialog_)
				volume_slider_dialog_->setSliderValue(50);
		}
	}
}

void VolumeButton::timerEvent(QTimerEvent* event)
{
	if ((volume_slider_dialog_ != nullptr) && (volume_slider_dialog_->isVisible()))
	{
		if (volume_slider_dialog_)
		{
			QPoint cursor_pos = QCursor::pos();

			QPoint button_pos = this->mapToGlobal(QPoint(0, 0));
			QRect button_rect = this->rect();

			QRect dialog_rect = volume_slider_dialog_->rect();
			QRect dialog_pos = volume_slider_dialog_->geometry();

			QRect area(
				dialog_pos.left(),
				dialog_pos.top(),
				dialog_rect.width(),
				button_pos.y() + button_rect.height() - dialog_pos.top()
			);

			if (!area.contains(cursor_pos))
			{
				volume_slider_dialog_->hide();
			}
		}
	}
	//else
	//{
	//	killTimer(timer_id_);
	//}
}
