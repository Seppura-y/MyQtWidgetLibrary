#pragma once

#include <QtWidgets/QMainWindow>
#include <QMouseEvent>
#include <QRect>
#ifdef Q_OS_WIN32
#include <Windows.h>
#endif


#include "ui_media_manager.h"

class MenuBar;
class Title;
class CameraMenu;
class PanelWidget;
class QHBoxLayout;
class QPushButton;

class MediaManager : public QMainWindow
{
    Q_OBJECT

public:
    MediaManager(QWidget *parent = Q_NULLPTR);

private:
    void mouseMoveEvent(QMouseEvent* ev) override;
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    bool nativeEvent(const QByteArray& eventType,void* message,long* result) override;

protected:
    void initTitle();
    void initMainWidget();
    void initCameraMenu();

protected slots:

private:
    void createMenuBar();
    LRESULT calculateBorder(const QPoint& pt);
signals:
    void sigWindowMaximized();
    void sigWindowNormal();
private:
    MenuBar* menu_bar_ = nullptr;
    Title* title_ = nullptr;
    CameraMenu* cam_menu_ = nullptr;
private:
    Ui::MediaManagerClass ui;

    bool left_bt_pressed_ = false;
    QPoint mouse_drag_point_;

    bool is_maximized_init_ = false;
    bool maximized_flag_ = false;
    QRect maximized_rect_;
    QRect normal_rect_;

    QHBoxLayout* main_wid_layout_ = nullptr;
    QPushButton* menu_extend_bt_ = nullptr;
    bool is_cam_menu_extend_ = true;

    PanelWidget* panel_widget_ = nullptr;

    ////////////////////////////////////////////////////////////////////
    //nativeEvent
    bool is_maximized_ = false;
    bool is_minimized_ = false;
};
