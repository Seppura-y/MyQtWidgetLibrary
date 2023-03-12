#include "media_manager.h"
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
#include "media_manager_gui_class.h"
#include "menu_bar.h"
#include "camera_menu.h"
#include "mybutton.h"
#include "panel_widget.h"

//#pragma comment(lib,"Dwmapi.lib")
//#pragma comment (lib, "user32.lib")

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lParam)    ((int)(short)LOWORD(lParam))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lParam)    ((int)(short)HIWORD(lParam))
#endif

using namespace std;
MediaManager::MediaManager(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.statusBar->close();
    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet(ConfigHelper::GetQssString(":/MediaManager/res/css/media_manager.css"));

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

    //installEventFilter(title_);
}

void MediaManager::mousePressEvent(QMouseEvent* ev)
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

void MediaManager::mouseMoveEvent(QMouseEvent* ev)
{
    //if (ui.title_wid->geometry().contains(mouse_drag_point_) && left_bt_pressed_)
    //{
    //    this->move(ev->globalPos() - mouse_drag_point_);
    //}
    //else
    //{
    //    return QMainWindow::mouseMoveEvent(ev);
    //}
    return QMainWindow::mouseMoveEvent(ev);
}

void MediaManager::mouseReleaseEvent(QMouseEvent* ev)
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

bool MediaManager::nativeEvent(const QByteArray& eventType, void* message, long* result)
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

LRESULT MediaManager::calculateBorder(const QPoint& pt)
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

    QRect rectTopRight(cx - borderSize, 0, borderSize, borderSize);
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

    QRect rectBottomLeft(0, cy - borderSize, borderSize, borderSize);
    if (rectBottomLeft.contains(pt)) {
        return HTBOTTOMLEFT;
    }

    QRect rectBottomRight(cx - borderSize, cy - borderSize, borderSize, borderSize);
    if (rectBottomRight.contains(pt)) {
        return HTBOTTOMRIGHT;
    }

    QRect rectBottom(borderSize, cy - borderSize, cx - borderSize * 2, borderSize);
    if (rectBottom.contains(pt)) {
        return HTBOTTOM;
    }

    return HTCLIENT;
}

void MediaManager::initTitle()
{
    title_ = MediaGUIClass.getTitle();

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

void MediaManager::createMenuBar()
{
    menu_bar_ = new MenuBar(title_);
    menu_bar_->addMenu("asdf");
    menu_bar_->addMenu("sdfsdf");
    menu_bar_->addMenu("sdfw");
    menu_bar_->addMenu("gn");
}


void MediaManager::initCameraMenu()
{
    cam_menu_ = MediaGUIClass.getCameraMenu();
    cam_menu_ = new CameraMenu();

    //QObject::connect(cam_menu_, &CameraMenu::sigProcessScreenCapture, this, [this] {qDebug() << "manager"; this->hide(); });

    QPalette palette;
    QWidget* wid = new QWidget;
    MyButton* pb = new MyButton;
    QHBoxLayout* layout = new QHBoxLayout;
    QHBoxLayout* layout2 = new QHBoxLayout;

    pb->setMaximumSize(15, 35);
    wid->setMaximumSize(35, 1000);
    wid->setMinimumWidth(15);

    palette.setColor(QPalette::Background, QColor(0, 255, 0, 50));
    wid->setAutoFillBackground(true);
    wid->setPalette(palette);

    layout2->setContentsMargins(0, 0, 0, 0);
    layout2->setMargin(0);
    layout2->addWidget(pb);
    layout2->setSpacing(0);
    wid->setLayout(layout2);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setMargin(0);
    layout->addWidget(cam_menu_);
    layout->addWidget(wid);
    layout->setSpacing(0);
    //ui.menu_wid->setLayout(layout);

    QHBoxLayout* layout3 = new QHBoxLayout;
    QWidget* w = new QWidget;
    w->setAutoFillBackground(true);
    w->setPalette(palette);
    layout3->addWidget(w);
    ui.main_wid->setLayout(layout3);

    //MediaGUIClass.setCameraMenu(cam_menu_);
}

void MediaManager::initMainWidget()
{
    cam_menu_ = MediaGUIClass.getCameraMenu();
    cam_menu_ = new CameraMenu();
    cam_menu_->setMaximumWidth(230);
    QObject::connect(cam_menu_, &CameraMenu::sigProcessScreenCapture, this, [this] { this->hide(); });
    QObject::connect(cam_menu_, &CameraMenu::sigProcessScreenCaptureFinished, this, [this] {qDebug() << "man fin"; this->show(); });

    menu_extend_bt_ = new QPushButton;
    menu_extend_bt_->setMaximumSize(8, 90);
    menu_extend_bt_->setStyleSheet(ConfigHelper::GetQssString(":/MediaManager/res/css/mybutton.css"));

    //int id = QFontDatabase::addApplicationFont(":/MediaManager/res/Font Awesome 6 Pro-Light-300.otf");
    int id = QFontDatabase::addApplicationFont(":/MediaManager/res/Font Awesome 6 Duotone-Solid-900.otf");
    //int id = QFontDatabase::addApplicationFont(":/MediaManager/res/Font Awesome 6 Pro-Solid-900.otf");
    if (id < 0)
        qWarning() << "FontAwesome cannot be loaded !";

    QFont font;
    QString family = QFontDatabase::applicationFontFamilies(id).first();
    font.setFamily(family);

    font.setPixelSize(12);
    font.setPointSize(12);
    menu_extend_bt_->setFont(font);
    menu_extend_bt_->setText(QChar(0xf32e));

    QHBoxLayout* layout2 = new QHBoxLayout;
    layout2->setContentsMargins(0, 0, 0, 0);
    layout2->setMargin(0);
    layout2->addWidget(menu_extend_bt_);
    layout2->setSpacing(0);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0, 255, 0, 0));

    QWidget* wid = new QWidget;
    wid->setMaximumSize(8, 10000);
    wid->setMinimumWidth(8);
    wid->setAutoFillBackground(true);
    wid->setPalette(palette);
    wid->setLayout(layout2);

    palette.setColor(QPalette::Background, QColor(0, 255, 0, 50));

    //QWidget* w = new QWidget;
    //w->setAutoFillBackground(true);
    //w->setPalette(palette);

    panel_widget_ = new PanelWidget;
    //panel_widget_->setAutoFillBackground(true);
    //panel_widget_->setPalette(palette);

    main_wid_layout_->setContentsMargins(0, 0, 0, 5);
    main_wid_layout_->setMargin(0);
    main_wid_layout_->setSpacing(0);
    main_wid_layout_->addWidget(cam_menu_);
    main_wid_layout_->addWidget(wid);
    //main_wid_layout_->addWidget(w);
    main_wid_layout_->addWidget(panel_widget_);

    ui.main_wid->setLayout(main_wid_layout_);

    connect(menu_extend_bt_, &QPushButton::clicked, this, 
        [this] 
        {
            if (is_cam_menu_extend_)
            {
                is_cam_menu_extend_ = false;
                this->cam_menu_->hide();
                menu_extend_bt_->setText(QChar(0xf330));
            }
            else
            {
                is_cam_menu_extend_ = true;
                this->cam_menu_->show();
                menu_extend_bt_->setText(QChar(0xf32e));
            }
        }
    );
}
