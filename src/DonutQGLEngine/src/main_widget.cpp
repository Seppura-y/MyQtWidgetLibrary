#include "main_widget.h"
#include <iostream>
#include <QPushButton>
#include <QFont>
#include <QPropertyAnimation>
#include <QOpenglExtensions>
#include <QOpenglWidget>
#include <QSlider>
#include <QLabel>
#include <QScrollArea>
#include <QDebug>
#include <QPainter>
#include <QHBoxLayout>
#include <QFontDatabase>
#include <QtWinExtras/QtWin>
//#include <dwmapi.h>


#include "config_helper.h"
#include "font_icon.h"
#include "title.h"
// #include "media_manager_gui_class.h"
#include "menu_bar.h"
#include "display_widget.h"
// #include "camera_menu.h"
// #include "mybutton.h"
// #include "panel_widget.h"

//#pragma comment(lib,"Dwmapi.lib")
//#pragma comment (lib, "user32.lib")

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lParam)    ((int)(short)LOWORD(lParam))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lParam)    ((int)(short)HIWORD(lParam))
#endif

using namespace std;
MainWidget::MainWidget(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.statusBar->close();
    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet(ConfigHelper::GetQssString(":main_widget/res/css/main_widget.css"));

    HWND hwnd = reinterpret_cast<HWND>(this->winId());
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);
    SetWindowLongPtr(hwnd, GWL_STYLE, style/* | WS_MAXIMIZEBOX*/ | WS_THICKFRAME | WS_CAPTION);
    //SetWindowLongPtr(hwnd, GWL_STYLE, style | WS_THICKFRAME);

    //bool enabled = QtWin::isCompositionEnabled();
    //if (enabled) {
    //    HWND hwnd = (HWND)this->winId();
    //    DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
    //    //::SetWindowLong(hwnd, GWL_STYLE, style | WS_THICKFRAME | WS_CAPTION | WS_BORDER);
    //    SetWindowLong(hwnd, GWL_STYLE, style | WS_THICKFRAME);
    //    QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1);
    //}

    main_wid_layout_ = new QHBoxLayout;
    initTitle();
    initMainWidget();
    initDisplayWidget();
    //installEventFilter(title_);
}

void MainWidget::mousePressEvent(QMouseEvent* ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        left_bt_pressed_ = true;
        mouse_drag_point_ = ev->pos();
    }
    //else
    //{
    //    return QMainWindow::mousePressEvent(ev);
    //}
    return QMainWindow::mousePressEvent(ev);
}

void MainWidget::mouseMoveEvent(QMouseEvent* ev)
{
    if (ui.title_wid->geometry().contains(mouse_drag_point_) && left_bt_pressed_)
    {
        this->move(ev->globalPos() - mouse_drag_point_);
    }
    else
    {
        return QMainWindow::mouseMoveEvent(ev);
    }
    return QMainWindow::mouseMoveEvent(ev);
}

void MainWidget::mouseReleaseEvent(QMouseEvent* ev)
{
    if (left_bt_pressed_)
    {
        left_bt_pressed_ = false;
        if (this->geometry().topLeft() != maximized_rect_.topLeft() && this->geometry().size() == maximized_rect_.size())
        {
            maximized_flag_ = true;
            emit sigWindowNormal();
        }
        else
        {
            maximized_flag_ = false;
        }
    }
    return QMainWindow::mouseReleaseEvent(ev);
}

bool MainWidget::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
#ifdef Q_OS_WIN
    if (eventType != "windows_generic_MSG")
        return false;

    MSG* msg = static_cast<MSG*>(message);

    QWidget* widget = QWidget::find(reinterpret_cast<WId>(msg->hwnd));
    if (!widget)
        return false;

    switch (msg->message) 
    {
        case WM_NCCALCSIZE: 
        {
            *result = 0;
            return true;
        }

        case WM_NCHITTEST: 
        {
            int x = GET_X_LPARAM(msg->lParam);
            int y = GET_Y_LPARAM(msg->lParam);
            QPoint pt = mapFromGlobal(QPoint(x, y));
            *result = calculateBorder(pt);

            if (*result == HTCLIENT) 
            {
                if (title_->getPlainTitleRect().contains(pt))
                {
                    *result = HTCAPTION;
                }
            }
            return true;
        }

        case WM_GETMINMAXINFO: 
        {
            LPMINMAXINFO lpMMI = (LPMINMAXINFO)(msg->lParam);
            lpMMI->ptMinTrackSize.x = 1280;
            lpMMI->ptMinTrackSize.y = 720;

            if (::IsZoomed(msg->hwnd)) 
            {
                is_maximized_ = true;
                RECT frame = { 0, 0, 0, 0 };
                AdjustWindowRectEx(&frame, WS_OVERLAPPEDWINDOW, FALSE, 0);
                frame.left = abs(frame.left);
                frame.top = abs(frame.bottom);
                widget->setContentsMargins(frame.left, frame.top, frame.right, frame.bottom);
            }
            else 
            {
                widget->setContentsMargins(0, 0, 0, 0);
                is_maximized_ = false;
            }

            *result = ::DefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
            return true;
            break;
        }

        default:
            break;
    }

#endif
    return QWidget::nativeEvent(eventType, message, result);
}

LRESULT MainWidget::calculateBorder(const QPoint& pt)
{
    if (::IsZoomed((HWND)this->winId())) {
        return HTCLIENT;
    }
    int borderSize = 4;
    int cx = this->size().width();
    int cy = this->size().height();

    QRect rectTopLeft(0, 0, borderSize, borderSize);
    if (rectTopLeft.contains(pt)) {
        return HTTOPLEFT;
    }

    QRect rectLeft(0, borderSize, borderSize, cy - borderSize * 2);
    if (rectLeft.contains(pt)) {
        return HTLEFT;
    }

    QRect rectTopRight(cx - 2 * borderSize, 0, 2 * borderSize, 2 * borderSize);
    if (rectTopRight.contains(pt)) {
        return HTTOPRIGHT;
    }

    QRect rectRight(cx - borderSize, borderSize, borderSize, cy - borderSize * 2);
    if (rectRight.contains(pt)) {
        return HTRIGHT;
    }

    QRect rectTop(borderSize, 0, cx - borderSize * 2, borderSize);
    if (rectTop.contains(pt)) {
        return HTTOP;
    }

    QRect rectBottomLeft(0, cy - 2 * borderSize, 2 * borderSize, 2 * borderSize);
    if (rectBottomLeft.contains(pt)) {
        return HTBOTTOMLEFT;
    }

    QRect rectBottomRight(cx - 2 * borderSize, cy - 2 * borderSize, 2 * borderSize, 2 * borderSize);
    if (rectBottomRight.contains(pt)) {
        return HTBOTTOMRIGHT;
    }

    QRect rectBottom(borderSize, cy - borderSize, cx - borderSize * 2, borderSize);
    if (rectBottom.contains(pt)) {
        return HTBOTTOM;
    }

    return HTCLIENT;
}

void MainWidget::initTitle()
{
    //title_ = MediaGUIClass.getTitle();

    title_ = new Title();

    QHBoxLayout* layout = new QHBoxLayout(ui.title_wid);
    layout->addWidget(title_);
    ui.title_wid->setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    ui.title_wid->setGeometry(0, 0, this->width(), title_->height());

    connect(title_, &Title::sigCloseBtnClicked, this, [this] {
            this->close();
        });

    connect(title_, &Title::sigMaxBtnClicked, this, [this] {
            if (this->isMaximized())
            {
                this->showNormal();
                emit sigWindowNormal();
            }
            else
            {
                if (maximized_flag_ && is_maximized_init_)
                {
                    this->setGeometry(maximized_rect_);
                    this->setWindowState(Qt::WindowMaximized);
                    maximized_flag_ = false;
                }
                else
                {
                    this->showMaximized();
                }

                emit sigWindowMaximized();

                if (!is_maximized_init_)
                {
                    is_maximized_init_ = true;
                    maximized_rect_ = this->geometry();
                }
            }
        });

    connect(title_, &Title::sigMiniBtnClicked, this, [this] {
            this->showMinimized();
        });

    connect(title_, &Title::sigTitleDoubleClicked, this, [this] {
            if (this->isMaximized())
            {
                this->showNormal();
                emit sigWindowNormal();
            }
            else
            {
                if (maximized_flag_ && is_maximized_init_)
                {
                    this->setGeometry(maximized_rect_);
                    this->setWindowState(Qt::WindowMaximized);
                    maximized_flag_ = false;
                }
                else
                {
                    this->showMaximized();
                }

                emit sigWindowMaximized();

                if (!is_maximized_init_)
                {
                    is_maximized_init_ = true;
                    maximized_rect_ = this->geometry();
                }
            }
        });

    this->installEventFilter(title_);
}

void MainWidget::createMenuBar()
{
    menu_bar_ = new MenuBar(title_);
    menu_bar_->addMenu("asdf");
    menu_bar_->addMenu("sdfsdf");
    menu_bar_->addMenu("sdfw");
    menu_bar_->addMenu("gn");
}


void MainWidget::initCameraMenu()
{

}

void MainWidget::initMainWidget()
{

}

void MainWidget::initDisplayWidget()
{
    display_widget_ = new DisplayWidget();
    QHBoxLayout* main_layout = new QHBoxLayout();
    main_layout->setContentsMargins(0, 0, 0, 5);
    main_layout->addWidget(display_widget_);
    ui.main_wid->setLayout(main_layout);
}
