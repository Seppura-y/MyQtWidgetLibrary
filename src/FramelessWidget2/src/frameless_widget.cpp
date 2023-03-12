#include "frameless_widget.h"
#include <windows.h>
#include <windowsx.h>
#include <qt_windows.h>

FramelessWidget::FramelessWidget(QWidget* parent)
	:QWidget(parent)
{
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
	//setAttribute(Qt::WA_Hover);
}

FramelessWidget::~FramelessWidget()
{

}


bool FramelessWidget::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	MSG* param = static_cast<MSG*>(message);

	switch (param->message)
	{
	case WM_NCHITTEST:
	{
		int nX = GET_X_LPARAM(param->lParam) - this->geometry().x();
		int nY = GET_Y_LPARAM(param->lParam) - this->geometry().y();

		/*if (childAt(nX, nY) != nullptr)
			return QWidget::nativeEvent(eventType, message, result);*/

		if (nX > border_width_ && nX < this->width() - border_width_ &&
			nY > border_width_ && nY < this->height() - border_width_)
		{
			if (childAt(nX, nY) != nullptr)
				return QWidget::nativeEvent(eventType, message, result);
		}

		if ((nX > 0) && (nX < border_width_))
			*result = HTLEFT;

		if ((nX > this->width() - border_width_) && (nX < this->width()))
			*result = HTRIGHT;

		if ((nY > 0) && (nY < border_width_))
			*result = HTTOP;

		if ((nY > this->height() - border_width_) && (nY < this->height()))
			*result = HTBOTTOM;

		if ((nX > 0) && (nX < border_width_) && (nY > 0)
			&& (nY < border_width_))
			*result = HTTOPLEFT;

		if ((nX > this->width() - border_width_) && (nX < this->width())
			&& (nY > 0) && (nY < border_width_))
			*result = HTTOPRIGHT;

		if ((nX > 0) && (nX < border_width_)
			&& (nY > this->height() - border_width_) && (nY < this->height()))
			*result = HTBOTTOMLEFT;

		if ((nX > this->width() - border_width_) && (nX < this->width())
			&& (nY > this->height() - border_width_) && (nY < this->height()))
			*result = HTBOTTOMRIGHT;

		return true;
	}
	}

	return false;
}