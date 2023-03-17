#include "render_widget.h"
#include <QMessageBox>
#include <QDebug>
#include <QDir>

#include <string>

RenderWidget::RenderWidget(QWidget* parent) : QWidget(parent)
{
	vlc_instance_ = libvlc_new(0, nullptr);
	if (!vlc_instance_)
	{
		QMessageBox::information(this, "Error", "Create VLC instance failed!");
		exit(EXIT_FAILURE);
	}
	else
	{
		vlc_media_player_ = libvlc_media_player_new(vlc_instance_);
		if (vlc_media_player_)
		{

		}
		else
		{
			libvlc_release(vlc_instance_);
			QMessageBox::information(this, "Error", "Create VLC media player failed!");
			exit(EXIT_FAILURE);
		}
	}
	this->setStyleSheet("RenderWdiget{background-color: black;}");
}

RenderWidget::~RenderWidget()
{
	if (vlc_media_player_)
	{
		libvlc_media_player_release(vlc_media_player_);
		vlc_media_player_ = nullptr;
	}

	if (vlc_instance_)
	{
		libvlc_release(vlc_instance_);
		vlc_instance_ = nullptr;
	}
}

void RenderWidget::openMediaFile(QString file_path)
{

	QString path = QDir::toNativeSeparators(file_path);

	// set path
	vlc_media_ = libvlc_media_new_path(vlc_instance_, path.toStdString().c_str());

	if (vlc_media_)
	{
		// parse media
		libvlc_media_parse(vlc_media_);

		// set media
		libvlc_media_player_set_media(vlc_media_player_, vlc_media_);

		// set the window's handle on which the media is played
		libvlc_media_player_set_hwnd(vlc_media_player_, (void*)(winId()));

		// release media
		libvlc_media_release(vlc_media_);
		vlc_media_ = nullptr;

		// play 
		libvlc_media_player_play(vlc_media_player_);

		emit sigOpenMediaFileSuccess();
	}
	else
	{
		if (vlc_media_player_)
		{
			libvlc_media_player_release(vlc_media_player_);
			vlc_media_player_ = nullptr;
		}

		if (vlc_instance_)
		{
			libvlc_release(vlc_instance_);
			vlc_instance_ = nullptr;
		}

		QMessageBox::information(this, "Error", "Open media file failed!");
		exit(EXIT_FAILURE);
	}

}

void RenderWidget::setMediaPause(bool status)
{
	if (!vlc_media_player_)
	{
		return;
	}
	media_pause_ = status;
	
	if (media_pause_)
	{
		if (libvlc_media_player_get_state(vlc_media_player_) == libvlc_state_t::libvlc_Playing)
		{
			libvlc_media_player_pause(vlc_media_player_);
		}
	}
	else if(!media_pause_)
	{
		if (libvlc_media_player_get_state(vlc_media_player_) == libvlc_state_t::libvlc_Paused)
		{
			libvlc_media_player_play(vlc_media_player_);
		}
	}

}

void RenderWidget::onOpenMediaFile(QString file_path)
{

}

void RenderWidget::mousePressEvent(QMouseEvent* ev)
{
	qDebug() << "render widget mouse pressed";
	return QWidget::mousePressEvent(ev);
}
