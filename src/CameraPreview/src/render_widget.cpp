#include "render_widget.h"
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QStyleOption>
#include <QPainter>
#include <QPushButton>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QScreen>
#include <QGuiApplication>
#include <QApplication>

#include <Windows.h>

#include <string>
#include <iostream>

//static HHOOK hHook = NULL;
//static bool is_fullscreen = false;
//LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
//	switch (wParam)
//	{
//
//		case WM_LBUTTONDBLCLK:
//		{
//			qDebug() << "left double click";
//			is_fullscreen = !is_fullscreen;
//		}
//	}
//	return CallNextHookEx(hHook, nCode, wParam, lParam);
//}

BOOL CALLBACK EnumVLC(HWND hwnd, LPARAM lParam)
{
	TCHAR szTitle[1024];
	int len = GetWindowText(hwnd, szTitle, 1024);

	if (len > 0)
	{
		EnableWindow(hwnd, FALSE);
		KillTimer(NULL, 1);
	}
	return TRUE;
}

void CALLBACK TimeProc(HWND hwnd, UINT msg, UINT_PTR id, DWORD time)
{
	HWND wnd = FindWindowEx(NULL, NULL, NULL, "MediaManager");
	if(wnd)
	{
		EnumChildWindows(wnd, EnumVLC, NULL);
	}
}

RenderWidget::RenderWidget(QWidget* parent) : QWidget(parent)
{
	this->setWindowTitle("RenderWidget");
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
	this->setStyleSheet("RenderWdiget{background-color: black;}");


	this->setMouseTracking(true);
	QObject::connect(&timer_mouse_hide_, &QTimer::timeout, this, &RenderWidget::onMouseHideTimeout);
	timer_mouse_hide_.start(1000);
}

RenderWidget::RenderWidget(int row, int colum, int width, int height, QWidget* parent)
{
	this->setWindowTitle("RenderWidget");
	//setAttribute(Qt::WA_TranslucentBackground);
	//setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
	this->setStyleSheet("RenderWdiget{background-color: rgb(60,60,60);}");
	this->setAcceptDrops(true);

	colum_ = colum;
	row_ = row;
	width_ = width;
	height_ = height;
	is_selected_ = false;
	is_covered_ = false;
	is_first_point_ = false;

	block_row_ = -1;
	block_colum_ = -1;

}

RenderWidget::~RenderWidget()
{

}

void RenderWidget::openMediaFile(QString file_path)
{
	if (!render_manager_)
	{
		initVlcManager();
	}
	QString path = QDir::toNativeSeparators(file_path);
	if (render_manager_->openMediaFile(path, (void*)(this->winId())) != 0)
	{
		QMessageBox::information(this, "warnning", "open file failed");
	}
	emit sigOpenMediaFileSuccess();
	//SetTimer(NULL, 1, 300, TimeProc);
}

void RenderWidget::setMediaPause(bool pause)
{
	if (!render_manager_) return;
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
	if (!render_manager_) return;
	render_manager_->setTimePos(value);
}

void RenderWidget::setSoundVolume(int value)
{
	if (!render_manager_) return;
	render_manager_->setSoundVolume(value);
}

void RenderWidget::setMediaStop()
{
	if (render_manager_)
	{
		render_manager_->setStop();
		delete render_manager_;
		render_manager_ = nullptr;
	}
}

void RenderWidget::onRefreshUi()
{
	if (is_selected_)
	{
		if (is_first_point_)
		{
			this->setStyleSheet("background-color:rgb(255,255,127)");
		}
		else
		{
			this->setStyleSheet("background-color:rgb(255,255,255)");
		}

	}
	else
	{
		this->setStyleSheet("background-color:rgb(60,60,60)");
		this->setStyleSheet("background-color:green");
	}
}

void RenderWidget::paintEvent(QPaintEvent* ev)
{

	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

	QWidget::paintEvent(ev);
}

void RenderWidget::mouseMoveEvent(QMouseEvent* ev)
{
	//this->setCursor(QCursor(Qt::ArrowCursor));
	QWidget::mouseMoveEvent(ev);
}

void RenderWidget::mousePressEvent(QMouseEvent* ev)
{
	if (ev->button() == Qt::LeftButton)
	{
		qDebug() << "left button clicked";
		if (is_selected_)
		{
			is_selected_ = false;
			emit sigSelected(row_, colum_);
		}
		else
		{
			is_selected_ = true;
			//this->refresh();
			emit sigSelected(row_, colum_);
		}
	}
}

void RenderWidget::initVlcManager()
{
	render_manager_ = new VlcManager();

	//hHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);
	//if (hHook == NULL)
	//{
	//	qDebug() << "hook failed";
	//}

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

//void RenderWidget::mouseDoubleClickEvent(QMouseEvent* ev)
//{
//	qDebug() << "render widget double click";
//	QWidget::mouseDoubleClickEvent(ev);
//}

void RenderWidget::onMouseHideTimeout()
{
	//this->setCursor(QCursor(Qt::BlankCursor));
}

//
//bool RenderWidget::nativeEventFilter(const QByteArray& eventType, void* message, long* result)
//{
//	if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG") {
//		MSG* pMsg = reinterpret_cast<MSG*>(message);
//		std::cout << "msg id = " << pMsg->message << std::endl;
//		if (pMsg->message == 32) 
//		{
//			if (is_fullscreen_)
//			{
//				is_fullscreen_ = false;
//				//emit sigShowFullscreen(false);
//			}
//			else
//			{
//				is_fullscreen_ = true;
//				//emit sigShowFullscreen(true);
//			}
//			return false;
//		}
//	}
//			//return QAbstractNativeEventFilter::nativeEventFilter(eventType, message, result);
//
//	return false;
//}