#pragma once

#include <QtWidgets/QWidget>
#include "ui_manager.h"

#include <QScrollArea>
#include <QGridLayout>
#include <QAbstractSocket>
#include <QTcpServer>

#include "screen_scroll_area.h"
#include "screen_configuration.h"
#include "sock_client.h"
#include "sock_svr.h"
#include "client_thread.h"

class QTcpSocket;
class QPushButton;
class QFile;
class QListWidget;
class ItemListWidget;

class Manager : public QWidget
{
    Q_OBJECT

public:
    Manager(QWidget *parent = Q_NULLPTR);
    ~Manager();
    void GetRange();
    void InitGridArea();
    void InitItemList();

    void resizeEvent(QResizeEvent* ev) override;
    void timerEvent(QTimerEvent* ev) override;
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    //void closeEvent(QCloseEvent* ev) override;

public:
    QPushButton* pbOpen = nullptr;
    QPushButton* pbSend = nullptr;
    QPushButton* pbSetAddress = nullptr;

signals:
    void SetAddr(int, QString);
    void OpenFile(QString, QString);
    void SendFile();
    void ClientConnect();
    void ClientDisconnect();
public slots:
    void merging();
    void splitting();
    void clearing();
    void saving();
    void loading();
    void refreshing(int row, int colum);
    void SendLayoutFile();
    void ResetDimension();

    void AddItem();
    //void AddItem(int index);
    void SetItem();
    void SetItem(int itemType,int index);
    void DeleteItem();
    void DeleteItem(int itemType,int index);

    void AddPicItem();
    void SetPicItem(int itemType,int index);

    void SetAddress();
    void ResetSvr();
    void OpenFile();
    void StartSend();
    void GetClientStatus(bool status);
    //void ConnectToManager();
    void DisconnectToManager();

private:
    Ui::ManagerClass ui;

    ScreenConfiguration* screen_conf = nullptr;
    QWidget* content_widget_ = nullptr;
    QGridLayout* grid_layout_ = nullptr;
    ScreenScrollArea* scroll_area_ = nullptr;
    bool is_leftbutton_pressed_ = false;
    bool first_point_selected_ = false;
    bool second_point_selected_ = false;
    bool is_client_connected_ = false;

    int first_colum_ = -1;
    int first_row_ = -1;
    int second_colum_ = -1;
    int second_row_ = -1;

    int start_colum_ = -1;
    int start_row_ = -1;
    int selected_width_ = -1;
    int selected_height_ = -1;
    int end_colum_ = -1;
    int end_row_ = -1;

    bool is_need_init_ = true;
    int grid_width_ = -1;
    int grid_height_ = -1;
    int grid_colum_ = -1;
    int grid_row_ = -1;

    int controler_width_ = 5760;
    int controler_height_ = 1080;
    int controler_width_prev_ = -1;
    int controler_height_prev_ = -1;

    ItemListWidget* lwCamera = nullptr;
    ItemListWidget* lwAgent = nullptr;
    ItemListWidget* lwWeb = nullptr;
    ItemListWidget* lwPicture = nullptr;

    SockClient* sock_client_ = nullptr;
    SockSvr* sock_svr_ = nullptr;
    ClientThread client_th_;
};
