#include "render_widget.h"
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QStyleOption>
#include <QPainter>
#include <QPushButton>

#include <string>

RenderWidget::RenderWidget(QWidget* parent) : QWidget(parent)
{
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
	this->setStyleSheet("RenderWdiget{background-color: black;}");

	//render_manager_.reset(new VlcManager());
	render_manager_ = new VlcManager();

	int ret = render_manager_->initVLC();

	switch (ret)
	{
	case -1:
		QMessageBox::information(this, "error", "create vlc instance failed");
		exit(EXIT_FAILURE);
		break;

	case -2:
		QMessageBox::information(this, "error", "create vlc media player failed");
		exit(EXIT_FAILURE);
		break;
	}

	QObject::connect(render_manager_, &VlcManager::sigUpdateTotalDuration, [=](QTime time)
		{
			emit this->sigUpdateTotalDuration(time);
		});

	QObject::connect(render_manager_, &VlcManager::sigUpdateTimePos, [=](QTime value)
		{
			emit this->sigUpdateCurrentTimePos(value);
		});

	QObject::connect(render_manager_, &VlcManager::sigUpdateSoundVolume, [=](int value)
		{
			emit this->sigUpdateCurrentSoundVolume(value);
		});

	QObject::connect(render_manager_, &VlcManager::sigMediaEndReached, [=]()
		{
			emit this->sigRenderMediaEndReached();
		});


	//QObject::connect(render_manager_.get(), &VlcManager::sigUpdateTotalDuration, [=](QTime time)
	//	{
	//		emit this->sigUpdateTotalDuration(time);
	//	});

	//QObject::connect(render_manager_.get(), &VlcManager::sigUpdateTimePos, [=](QTime time)
	//	{
	//		emit this->sigUpdateCurrentTimePos(time);
	//	});

	//QObject::connect(render_manager_.get(), &VlcManager::sigUpdateSoundVolume, [=](QTime time)
	//	{
	//		emit this->sigUpdateTotalDuration(time);
	//	});
}

RenderWidget::~RenderWidget()
{

}

void RenderWidget::openMediaFile(QString file_path)
{
	QString path = QDir::toNativeSeparators(file_path);
	if (render_manager_->openMediaFile(path, (void*)(this->winId())) != 0)
	{
		QMessageBox::information(this, "warnning", "open file failed");
	}
	emit sigOpenMediaFileSuccess();
}

void RenderWidget::setMediaPause(bool pause)
{
	if (pause)
	{
		render_manager_->setPause();
	}
	else
	{
		render_manager_->setPlaying();
	}
}

void RenderWidget::setSeekPos(double value)
{
	render_manager_->setTimePos(value);
}

void RenderWidget::setSoundVolume(int value)
{
	render_manager_->setSoundVolume(value);
}

void RenderWidget::setMediaStop()
{
	render_manager_->setStop();
}

//void RenderWidget::onOpenMediaFile(QString file_path)
//{
//
//}

void RenderWidget::mousePressEvent(QMouseEvent* ev)
{
	qDebug() << "render widget mouse pressed";
	return QWidget::mousePressEvent(ev);
}

void RenderWidget::paintEvent(QPaintEvent* ev)
{

	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

	QWidget::paintEvent(ev);
}