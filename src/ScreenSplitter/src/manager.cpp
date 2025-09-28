#include "manager.h"
#include "elwidget.h"
#include "item_listwidget.h"

#include <QScreen>
#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QFileDialog>
#include <QStringList>
#include <QtNetwork>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QValidator>
#include <QTabWidget>
//#include <QTabBar>
#include <QListWidget>
//#include <QTableWidget>
#include <QDialog>
#include <QPixMap>
#include <QRadioButton>
#include <QFile>

#define ITEM_LIST_CONFIG "./config/item_list_conf.json"
#define GRID_CONFIG "./config/grid_conf.json"
#define DIMENSION_CONFIG "./config/Manager_init.json"
#define ITEM_LIST_COUNT 4

static QPoint evpoint;

Manager::Manager(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);
    ui.pbClose->setStyleSheet("background-image:url(:D:\hsy\ffmpeg_code\src\ScreenManager\image\close.png)");
    ui.pbMin->setStyleSheet("background-image:url(:D:\hsy\ffmpeg_code\src\ScreenManager\image\min.png)");
    ui.pbMax->setStyleSheet("background-image:url(:D:\hsy\ffmpeg_code\src\ScreenManager\image\max.png)");


    QObject::connect(ui.pbClose, SIGNAL(clicked()), this, SLOT(close()));
    //QObject::connect(ui.pbMax, SIGNAL(clicked()), this, SLOT(showMaximized()));
    QObject::connect(ui.pbMin, SIGNAL(clicked()), this, SLOT(showMinimized()));

    QObject::connect(ui.pbAddItem, SIGNAL(clicked()), this, SLOT(AddItem()));
    QObject::connect(ui.pbSetItem, SIGNAL(clicked()), this, SLOT(SetItem()));
    QObject::connect(ui.pbDelItem, SIGNAL(clicked()), this, SLOT(DeleteItem()));


    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    this->resize(width - 50, height - 100);
    //this->setWindowFlag(Qt::FramelessWindowHint);
    //this->showFullScreen();

    QVBoxLayout* vbLayout = new QVBoxLayout();
    this->setLayout(vbLayout);
    vbLayout->addWidget(ui.wHead);
    vbLayout->addWidget(ui.wBody);
    vbLayout->setContentsMargins(0, 0, 0, 0);
    vbLayout->setSpacing(0);
    ui.wHead->setMaximumHeight(60);
    ui.wHead->setMinimumHeight(60);

    QVBoxLayout* vblayout2 = new QVBoxLayout();
    ui.wList->setLayout(vblayout2);
    vblayout2->addWidget(ui.wButtons);
    vblayout2->addWidget(ui.twItem);
    vblayout2->setSpacing(0);
    vblayout2->setContentsMargins(0, 0, 0, 0);
    ui.wButtons->setMaximumHeight(50);
    ui.wButtons->setMinimumHeight(50);

    QHBoxLayout* hblayout = new QHBoxLayout();
    ui.wBody->setLayout(hblayout);
    hblayout->addWidget(ui.wList);
    hblayout->addWidget(ui.wGrid);
    hblayout->setSpacing(0);
    hblayout->setContentsMargins(0, 0, 0, 0);
    ui.wList->setMaximumWidth(180);
    ui.wList->setStyleSheet("background-color: rgb(255,255,255)");

    scroll_area_ = new ScreenScrollArea(ui.wGrid);
    scroll_area_->set_merge_enable(false);
    scroll_area_->set_split_enable(false);
    QObject::connect(scroll_area_, SIGNAL(merge()), this, SLOT(merging()));
    QObject::connect(scroll_area_, SIGNAL(split()), this, SLOT(splitting()));
    QObject::connect(scroll_area_, SIGNAL(save()), this, SLOT(saving()));
    QObject::connect(scroll_area_, SIGNAL(clear()), this, SLOT(clearing()));
    QObject::connect(scroll_area_, SIGNAL(load()), this, SLOT(loading()));
    QObject::connect(scroll_area_, SIGNAL(rstsvr()), this, SLOT(ResetSvr()));
    QObject::connect(scroll_area_, SIGNAL(setaddr()), this, SLOT(SetAddress()));
    QObject::connect(scroll_area_, SIGNAL(sndfile()), this, SLOT(SendLayoutFile()));

    QVBoxLayout* vblayout3 = new QVBoxLayout();
    ui.wGrid->setLayout(vblayout3);
    vblayout3->setSpacing(1);
    vblayout3->setContentsMargins(0, 0, 0, 0);
    vblayout3->addWidget(scroll_area_);

    content_widget_ = new QWidget();
    scroll_area_->setWidget(content_widget_);

    grid_layout_ = new QGridLayout(content_widget_);
    grid_layout_->setSpacing(1);
    grid_layout_->setContentsMargins(0, 0, 0, 0);
    scroll_area_->setWidget(content_widget_);
    scroll_area_->setWidgetResizable(false);
    //int row_count = grid_layout_->rowCount();
    //int colum_count = grid_layout_->columnCount();
    //int grid_count = row_count * colum_count;
    //int count = grid_layout_->count();

    //qDebug() << "init grid_count : " << grid_count << " count : " << count;
    first_point_selected_ = false;
    second_point_selected_ = false;


    ui.twItem->tabBar()->setTabText(0, QString::fromLocal8Bit("1"));
    ui.twItem->tabBar()->setTabText(1, QString::fromLocal8Bit("2"));
    ui.twItem->tabBar()->setTabText(2, QString::fromLocal8Bit("3"));
    ui.twItem->tabBar()->setTabText(3, QString::fromLocal8Bit("4"));
    ////////////////////////////////////////////////////////////////////////////////////////////
    QVBoxLayout* vbLayout_cmr = new QVBoxLayout();
    QLabel* lbCmr = new QLabel();
    lbCmr->setText(QString::fromLocal8Bit("camera : "));
    lbCmr->setMaximumHeight(60);

    //lwCamera = new QListWidget();
    lwCamera = new ItemListWidget(0,this);
    lwCamera->setDragEnabled(true);

    vbLayout_cmr->addWidget(lbCmr);
    vbLayout_cmr->addWidget(lwCamera);
    ui.twItem->widget(0)->setLayout(vbLayout_cmr);
    ////////////////////////////////////////////////////////////////////////////////////////////
    QVBoxLayout* vbLayout_web = new QVBoxLayout();
    QLabel* lbWeb = new QLabel();
    lbWeb->setText(QString::fromLocal8Bit("web : "));
    lbWeb->setMaximumHeight(60);

    //lwWeb = new QListWidget();
    lwWeb = new ItemListWidget(1, this);
    lwWeb->setDragEnabled(true);

    vbLayout_web->addWidget(lbWeb);
    vbLayout_web->addWidget(lwWeb);
    ui.twItem->widget(1)->setLayout(vbLayout_web);
    ////////////////////////////////////////////////////////////////////////////////////////////
    QVBoxLayout* vbLayout_agent = new QVBoxLayout();
    QLabel* lbAgent = new QLabel();
    lbAgent->setText(QString::fromLocal8Bit("agent : "));
    lbAgent->setMaximumHeight(60);

    //lwAgent = new QListWidget();
    lwAgent = new ItemListWidget(2,this);
    lwAgent->setDragEnabled(true);

    vbLayout_agent->addWidget(lbAgent);
    vbLayout_agent->addWidget(lwAgent);
    ui.twItem->widget(2)->setLayout(vbLayout_agent);
    //////////////////////////////////////////////////////////////////////////////////////////////
    QVBoxLayout* vbLayout_picture = new QVBoxLayout();
    QLabel* lbPicture = new QLabel();
    lbPicture->setText(QString::fromLocal8Bit("picture : "));
    lbPicture->setMaximumHeight(60);

    //lwPicture = new QListWidget();
    lwPicture = new ItemListWidget(3,this);
    lwPicture->setDragEnabled(true);

    vbLayout_picture->addWidget(lbPicture);
    vbLayout_picture->addWidget(lwPicture);
    ui.twItem->widget(3)->setLayout(vbLayout_picture);
    ////////////////////////////////////////////////////////////////////////////////////////////
    screen_conf = ScreenConfiguration::GetInstance();
    screen_conf->InitJson();
    InitItemList();

    ////////////////////////////////////////////////////////////////////////////////////////////
    sock_svr_ = new SockSvr();
    QObject::connect(sock_svr_, SIGNAL(ResetDimen()), this, SLOT(ResetDimension()));

    sock_client_ = new SockClient();
    QObject::connect(sock_client_, SIGNAL(ClientStatus(bool)), this, SLOT(GetClientStatus(bool)));
    QObject::connect(this, SIGNAL(SetAddr(int, QString)), sock_client_, SLOT(SetAddress(int, QString)));
    QObject::connect(this, SIGNAL(OpenFile(QString, QString)), sock_client_, SLOT(SetMsgFile(QString, QString)));
    QObject::connect(this, SIGNAL(SendFile()), sock_client_, SLOT(Send()));
    QObject::connect(this, SIGNAL(ClientConnect()), sock_client_, SLOT(SockConnect()));
    QObject::connect(this, SIGNAL(ClientDisconnect()), sock_client_, SLOT(DisConn()));
    sock_client_->moveToThread(&client_th_);
    client_th_.start();

    startTimer(10);
    emit ClientConnect();
}

Manager::~Manager()
{
    client_th_.terminate();
    client_th_.wait();
}

void Manager::resizeEvent(QResizeEvent* ev)
{
    int x = this->width() - ui.wButton->width();
    int y = ui.wButton->y();
    ui.wButton->move(x, y);
}

//void Manager::closeEvent(QCloseEvent* ev)
//{
//    client_th_.quit();
//    client_th_.wait();
//}

void Manager::mousePressEvent(QMouseEvent* ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        evpoint = ev->pos();
        is_leftbutton_pressed_ = true;
    }
}

void Manager::mouseMoveEvent(QMouseEvent* ev)
{
    if (!is_leftbutton_pressed_)
    {
        return QWidget::mouseMoveEvent(ev);
    }
    if (evpoint.y() > ui.wHead->height())
    {
        return QWidget::mouseMoveEvent(ev);
    }
    this->move(ev->globalPos() - evpoint);
}

void Manager::mouseReleaseEvent(QMouseEvent* ev)
{
    is_leftbutton_pressed_ = false;
}


void Manager::InitGridArea()
{
    if ( is_need_init_ && 
        (controler_width_ != -1) && 
        (controler_height_ != -1) && 
        (  (controler_width_ != controler_width_prev_) || (controler_height_ != controler_height_prev_)  ))
    {
        for (int i = 0; i < grid_row_; i++)
        {
            for (int j = 0; j < grid_colum_; j++)
            {
                QLayoutItem* item = grid_layout_->itemAtPosition(i, j);
                if (!item)continue;
                int index = grid_layout_->indexOf(item);
                ElWidget* item_widget = (ElWidget*)grid_layout_->takeAt(index)->widget();
                if (!item_widget)continue;
                delete item_widget;
            }
        }

        int scrollbar_height = scroll_area_->get_horizontal_scrollbar_height();
        double scale = (double)(ui.wGrid->height() - scrollbar_height) / controler_height_;
        content_widget_->resize(controler_width_ * scale, controler_height_ * scale);

        grid_row_ = controler_height_ / 100;
        grid_colum_ = controler_width_ / (controler_height_ / grid_row_);

        for (int i = 0; i < grid_row_; i++)
        {
            for (int j = 0; j < grid_colum_; j++)
            {
                ElWidget* elwidget = new ElWidget(i, j);
                QObject::connect(elwidget, SIGNAL(selected(int, int)), this, SLOT(refreshing(int, int)));
                grid_layout_->addWidget(elwidget, i, j);
            }
        }

        controler_width_prev_ = controler_width_;
        controler_height_prev_ = controler_height_;
        is_need_init_ = false;
    }
}

void Manager::ResetDimension()
{
    if (!screen_conf->LoadJson(DIMENSION_CONFIG))
    {
        QMessageBox::information(nullptr, "error", QString("load %1 failed").arg(DIMENSION_CONFIG));
        return;
    }
    QJsonObject* src;
    src = screen_conf->GetObject((ScreenConfiguration::ObjType::OBJ_TYPE_DIMENSION));

    src = &(src->find(QString("Dimension")).value().toObject());
    controler_width_ = src->find(QString("controler_width")).value().toInt();
    controler_height_ = src->find(QString("controler_height")).value().toInt();
    is_need_init_ = true;
    InitGridArea();
}

void Manager::timerEvent(QTimerEvent* ev)
{
    //if (!sock_client_->isConnected)
    //{
    //    ConnectToSvr();
    //}
    if (is_need_init_)
    {
        InitGridArea();
    }
    //InitGridArea();
    //QString filename = QString("./Manager_init.json");
    //if (!screen_conf->LoadJson(filename))
    //{
    //    return;
    //}
    ////QJsonObject o = screen_conf->GetJson();
    //QJsonObject* o = screen_conf->GetObject(ScreenConfiguration::ObjType::OBJ_TYPE_DIMENSION);
    //QStringList keys = o->keys();
    //for (int i = 0; i < keys.size(); i++)
    //{
    //    auto it = o->find(keys.at(i));
    //    QJsonObject obj = it.value().toObject();

    //    controler_height_ = obj.find("controler_height").value().toInt();
    //    controler_width_ = obj.find("controler_width").value().toInt();
    //}


}
void Manager::AddItem()
{
    int index = ui.twItem->currentIndex();
    switch (index)
    {
        case 0:
        {
            SetItem(0,-1);
            break;
        }
        case 1:
        {
            SetItem(1,-1);
            break;
        }
        case 2:
        {
            SetItem(2,-1);
            break;
        }
        case 3:
        {
            SetPicItem(3,-1);
            break;
        }

    }
}

//void Manager::AddItem(int index)
//{
//    switch (index)
//    {
//        case 0:
//        {
//            SetItem(0, -1);
//            break;
//        }
//        case 1:
//        {
//            SetItem(1, -1);
//            break;
//        }
//        case 2:
//        {
//            SetItem(2, -1);
//            break;
//        }
//        case 3:
//        {
//            SetItem(3, -1);
//            break;
//        }
//    }
//}

void Manager::AddPicItem()
{
    SetPicItem(3, -1);
}



void Manager::SetItem()
{
    int type = ui.twItem->currentIndex();
    //QListWidget* curList = (QListWidget*)ui.twItem->currentWidget()->layout()->itemAt(1)->widget();
    ItemListWidget* curList = (ItemListWidget*)ui.twItem->currentWidget()->layout()->itemAt(1)->widget();
    if (curList->currentIndex().row() < 0)
    {
        QMessageBox::information(nullptr, "error", QString::fromLocal8Bit("please select a item"));
    }
    if (type == 3)
    {
        this->SetPicItem(type,curList->currentIndex().row());
    }
    else
    {
        this->SetItem(type, curList->currentIndex().row());
    }

}

void Manager::SetPicItem(int itemType, int index)
{
    QString openPicUrl = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择文件"), QString("./"), QString("Json Files (*.jpg *.png)"));
    QString openPicName = openPicUrl.right(openPicUrl.size() - openPicUrl.lastIndexOf('/') - 1);
    if (index >= 0)
    {
        ItemListWidget* lwCur = (ItemListWidget*)ui.twItem->currentWidget()->layout()->itemAt(1)->widget();
        //lwCur->itemType = itemType;
        lwCur->currentItem()->setText(openPicName);
        DeleteItem(itemType, index);
    }

    QJsonObject obj;
    obj.insert("name",openPicName);
    obj.insert("url",openPicUrl);
    obj.insert("item_type", itemType);
    screen_conf->WriteJson(openPicName, obj, (ScreenConfiguration::ObjType)itemType);
    screen_conf->SaveJson(ITEM_LIST_CONFIG, ScreenConfiguration::FileType::FILE_TYPE_ITEMLIST);
    InitItemList();

    emit OpenFile(QString::fromLocal8Bit("picture"), openPicUrl);
    emit StartSend();
}

void Manager::SetItem(int itemType,int index)
{
    //QDialog dia(this);
    //dia.resize(600, 120);

    //QFormLayout* formLayout = new QFormLayout();
    //dia.setLayout(formLayout);

    //QLineEdit leName;
    //formLayout->addRow(QString::fromLocal8Bit("name : "), &leName);

    //QLineEdit leUrl;
    //formLayout->addRow(QString::fromLocal8Bit("url"), &leUrl);

    //QLineEdit leSubUrl;
    //if (itemType == 0)
    //{
    //    formLayout->addRow(QString::fromLocal8Bit("sub_url"), &leSubUrl);
    //}

    //QPushButton pbAccept;
    //pbAccept.setText(QString::fromLocal8Bit("accept"));
    //QObject::connect(&pbAccept, SIGNAL(clicked()), &dia, SLOT(accept()));
    //formLayout->addRow(&pbAccept);

    //QJsonObject obj;
    //QString key;
    //if (index >= 0)
    //{
    //    //QString key = ((QListWidget*)ui.twItem->currentWidget()->layout()->itemAt(1)->widget())->currentItem()->text();
    //    ItemListWidget* lwCur = (ItemListWidget*)ui.twItem->currentWidget()->layout()->itemAt(1)->widget();
    //    lwCur->itemType = itemType;
    //    key = lwCur->currentItem()->text();
    //    obj = *screen_conf->GetObject((ScreenConfiguration::ObjType)itemType);

    //    if (!obj.contains(key))
    //    {
    //        qDebug() << "set item : do not have this key";
    //        return;
    //    }
    //    QJsonObject::iterator it = obj.find(key);
    //    obj = it.value().toObject();
    //    leName.setText(obj.find("name").value().toString());
    //    leUrl.setText(obj.find("url").value().toString());
    //    if (itemType == 0)
    //    {
    //        leSubUrl.setText(obj.find("SubUrl").value().toString());
    //    }
    //    DeleteItem(itemType, index);
    //}
    //
    //QJsonObject info;

    //for (;;)
    //{
    //    if (dia.exec() == QDialog::Accepted)
    //    {
    //        if (leName.text().isEmpty())
    //        {
    //            QMessageBox::information(nullptr, "error", "please set a name");
    //            continue;
    //        }

    //        if (leUrl.text().isEmpty())
    //        {
    //            QMessageBox::information(nullptr, "error", "please set a name");
    //            continue;
    //        }

    //        if (itemType == 0)
    //        {
    //            if (leSubUrl.text().isEmpty())
    //            {
    //                QMessageBox::information(nullptr, "error", "please set a name");
    //                continue;
    //            }
    //            info.insert("SubUrl", leSubUrl.text());
    //        }

    //        info.insert("name", leName.text());
    //        info.insert("url", leUrl.text());
    //        info.insert("item_type", itemType);
    //        //info.insert("item_index", index);
    //        screen_conf->WriteJson(leName.text(), info,(ScreenConfiguration::ObjType)itemType);
    //        screen_conf->SaveJson(ITEM_LIST_CONFIG,ScreenConfiguration::FileType::FILE_TYPE_ITEMLIST);
    //        InitItemList();
    //        break;
    //    }
    //    else if (dia.close())
    //    {
    //        screen_conf->WriteJson(key, obj, (ScreenConfiguration::ObjType)itemType);
    //        //QJsonDocument doc;
    //        //doc.setObject(obj);
    //        //QByteArray arr = doc.toJson();
    //        screen_conf->SaveJson(ITEM_LIST_CONFIG, ScreenConfiguration::FileType::FILE_TYPE_ITEMLIST);
    //        InitItemList();
    //        return;
    //    }
    //}

}

void Manager::DeleteItem()
{
    int type = ui.twItem->currentIndex();
    //QListWidget* curList = (QListWidget*)ui.twItem->currentWidget()->layout()->itemAt(1)->widget();
    ItemListWidget* curList = (ItemListWidget*)ui.twItem->currentWidget()->layout()->itemAt(1)->widget();
    if (curList->currentIndex().row() < 0)
    {
        QMessageBox::information(nullptr, "error", QString::fromLocal8Bit("please select a item"));
        return;
    }
    this->DeleteItem(type, curList->currentIndex().row());
}

void Manager::DeleteItem(int itemType,int index)
{
    //QString key = ((QListWidget*)ui.twItem->currentWidget()->layout()->itemAt(1)->widget())->currentItem()->text();
    QString key = ((ItemListWidget*)ui.twItem->currentWidget()->layout()->itemAt(1)->widget())->currentItem()->text();
    QJsonObject* obj = screen_conf->GetObject((ScreenConfiguration::ObjType)itemType);
    if (obj->contains(key))
    {
        //QJsonObject::iterator it = obj.find(key);
        //obj.erase(it);
        obj->take(key);
        screen_conf->SaveJson(ITEM_LIST_CONFIG, ScreenConfiguration::FileType::FILE_TYPE_ITEMLIST);
        InitItemList();
    }

}

void Manager::InitItemList()
{
    if (!screen_conf->LoadJson(ITEM_LIST_CONFIG))
    {
        QMessageBox::information(nullptr, "error", QString("load %1 failed").arg(ITEM_LIST_CONFIG));
        return;
    }
    QJsonObject* src;
    QStringList src_key;
    for (int i = 0; i < ITEM_LIST_COUNT; i++)
    {
        //QListWidget* list = (QListWidget*)ui.twItem->widget(i)->layout()->itemAt(1)->widget();
        ItemListWidget* list = (ItemListWidget*)ui.twItem->widget(i)->layout()->itemAt(1)->widget();
        list->clear();
        src = screen_conf->GetObject((ScreenConfiguration::ObjType)i);
        src_key = src->keys();
        for (auto it = src_key.begin(); it != src_key.end();it++)
        {
            QString key = *it;
            list->addItem(key);
        }
    }
}

void Manager::loading()
{
    QString filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择json配置文件"), QString("./"), QString("Json Files (*.json)"));
    if (filename.isEmpty() || !filename.contains(QString("json")))
    {
        return;
    }

    int row;
    int colum;
    int width;
    int height;
    int block_row;
    int block_colum;
    bool isCovered;

    if (!screen_conf->LoadJson(filename))
    {
        return;
    }

    clearing();

    QJsonObject o = *screen_conf->GetObject(ScreenConfiguration::ObjType::OBJ_TYPE_WIDGET);
    //QJsonObject o = screen_conf->GetJson();
    QStringList keys = o.keys();
    for (int i = 0; i < keys.size(); i++)
    {
        int item_type = -1;
        //qDebug() << "key " << i << "is " << keys.at(i);
        auto it = o.find(keys.at(i));
        QJsonObject obj = it.value().toObject();
        QStringList keyss = obj.keys();


        row = obj.find(QString("row")).value().toInt();
        colum = obj.find(QString("colum")).value().toInt();
        width = obj.find(QString("width")).value().toInt();
        height = obj.find(QString("height")).value().toInt();
        block_row = obj.find(QString("block_row")).value().toInt();
        block_colum = obj.find(QString("block_colum")).value().toInt();
        isCovered = obj.find(QString("isCovered")).value().toBool();
        item_type = obj.find(QString("item_type")).value().toInt();

        QLayoutItem* item = grid_layout_->itemAtPosition(row, colum);
        if (item == nullptr)continue;
        int index = grid_layout_->indexOf(item);
        ElWidget* wid = (ElWidget*)grid_layout_->takeAt(index)->widget();
        if (wid == nullptr)continue;
        delete wid;
        wid = new ElWidget(row, colum, width, height);
        wid->block_row = block_row;
        wid->block_colum = block_colum;
        wid->isCovered = isCovered;
        wid->item_type = item_type;
        QObject::connect(wid, SIGNAL(selected(int, int)), this, SLOT(refreshing(int, int)));
        grid_layout_->addWidget(wid, row, colum, height, width);
        if (width > 1 || height > 1)
        {
            for (int i = row; i < row + height; i++)
            {
                for (int j = colum; j < colum + width; j++)
                {
                    wid = (ElWidget*)grid_layout_->itemAtPosition(i, j)->widget();
                    wid->isCovered = true;
                    wid->block_row = row;
                    wid->block_colum = colum;
                }
            }
        }

        //switch (wid->item_type)
        //{
        //    case 0:
        //    {
        //        wid->setStyleSheet("	border-image: url(D:/hsy/ffmpeg_code/src/Manager/image/cam.png)");
        //        break;
        //    }
        //    case 1:
        //    {
        //        wid->setStyleSheet("	border-image: url(D:/hsy/ffmpeg_code/src/Manager/image/agn.png)");
        //        break;
        //    }
        //    case 2:
        //    {
        //        wid->setStyleSheet("	border-image: url(D:/hsy/ffmpeg_code/src/Manager/image/web.png)");
        //        break;
        //    }
        //    case 3:
        //    {
        //        wid->setStyleSheet("	border-image: url(D:/hsy/ffmpeg_code/src/Manager/image/pic.png)");
        //        break;
        //    }
        //    default:
        //    {
        //        break;
        //    }
        //}

    }

}


void Manager::clearing()
{
    first_point_selected_ = false;
    first_row_ = -1;
    first_colum_ = -1;

    second_point_selected_ = false;
    second_row_ = -1;
    second_colum_ = -1;

    //QJsonObject* obj = screen_conf->GetObject(ScreenConfiguration::ObjType::OBJ_TYPE_WIDGET);
    //QJsonDocument doc;
    //QStringList keys = obj->keys();

    //for (int i = 0; i < keys.size(); i++)
    //{
    //    auto it = obj->find(keys.at(i));
    //    obj->erase(it);
    //}

    //for (auto it = obj->begin(); it != obj->end(); it++)
    //{
    //    obj->take(it.key());
    //}

    //if (obj->size() > 0)
    //{
    //    auto it = obj->begin();
    //    auto it_end = obj->end();
    //    for (it; it < it_end; it++)
    //    {
    //        obj->take(it.key());
    //    }
    //}


    int index = -1;
    QLayoutItem* item;
    ElWidget* item_widget;
    for (int i = 0; i < grid_row_; i++)
    {
        for (int j = 0; j < grid_colum_; j++)
        {
            item = grid_layout_->itemAtPosition(i, j);
            if (item == nullptr)
            {
                item_widget = new ElWidget(i, j);
                QObject::connect(item_widget, SIGNAL(selected(int, int)), this, SLOT(refreshing(int, int)));
                grid_layout_->addWidget(item_widget, i, j);
            }
            index = grid_layout_->indexOf(item);
            item_widget = (ElWidget*)grid_layout_->takeAt(index)->widget();
            delete item_widget;

            item_widget = new ElWidget(i, j);
            QObject::connect(item_widget, SIGNAL(selected(int, int)), this, SLOT(refreshing(int, int)));
            grid_layout_->addWidget(item_widget, i, j);
        }
    }
}

void Manager::saving()
{
    QString filename = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("选择或创建json文件"), QString("./"), QString("Json Files (*.json)"));
    if (!filename.contains(QString(".json")))
    {
        qDebug() << QString("请选择json文件");
        return;
    }
    QJsonObject::iterator it;
    QJsonObject obj = *screen_conf->GetObject(ScreenConfiguration::ObjType::OBJ_TYPE_WIDGET);

    QStringList str = obj.keys();
    int sz = str.size();
    
    QFile file(filename);
    file.remove();

    //if (!obj.empty())
    //{
    //    for (it = obj.begin(); it != obj.end(); it++)
    //    {
    //        obj.erase(it);
    //    }
    //}
    // 
    //qDebug() << "obj count : " << obj.count();
    //if (obj.count() > 0)
    //{
    //    obj.
    //    for (it = obj.begin(); it != obj.end(); it++)
    //    {
    //        obj.erase(it);
    //        qDebug() << "obj count : " << obj.count();
    //    }
    //}


    int widget_count = 0;
    //QJsonObject obj;
    for (int i = 0; i < grid_row_; i++)
    {
        for (int j = 0; j < grid_colum_; j++)
        {
            QLayoutItem* item = grid_layout_->itemAtPosition(i, j);
            if (item == nullptr)continue;
            ElWidget* item_widget = (ElWidget*)grid_layout_->itemAtPosition(i, j)->widget();
            if (item_widget == nullptr)continue;
            if (item_widget->isCovered)
            {

            }
            else
            {
                QString str = QString("Widget_%1").arg(widget_count++);
                QJsonObject obj;
                obj.insert(QString("row"), item_widget->row);
                obj.insert(QString("colum"), item_widget->colum);
                obj.insert(QString("width"), item_widget->width);
                obj.insert(QString("height"), item_widget->height);
                obj.insert(QString("block_row"), item_widget->block_row);
                obj.insert(QString("block_colum"), item_widget->block_colum);
                obj.insert(QString("isCovered"), item_widget->isCovered);
                obj.insert(QString("name"), item_widget->name);
                obj.insert(QString("url"), item_widget->url);
                obj.insert(QString("sub_url"), item_widget->sub_url);
                obj.insert(QString("item_type"), item_widget->item_type);
                screen_conf->WriteJson(str, obj, ScreenConfiguration::ObjType::OBJ_TYPE_WIDGET);
            }
        }
    }
    screen_conf->SaveJson(filename);
    //qDebug() << "remain count : " << grid_layout_->count()<<"grid_colum"<<grid_layout_->columnCount();
}

void Manager::merging()
{
    first_point_selected_ = false;
    first_colum_ = -1;
    first_row_ = -1;
    second_point_selected_ = false;
    second_colum_ = -1;
    second_row_ = -1;

    for (int i = 0; i < grid_row_; i++)
    {
        for (int j = 0; j < grid_colum_; j++)
        {
            ElWidget* item = (ElWidget*)grid_layout_->itemAtPosition(i, j)->widget();
            if (item == nullptr)continue;
            if (item->isSelected)
            {
                item->isFirstPoint = false;
                item->isSelected = false;
                item->refresh();
            }

        }
    }

    QLayoutItem* item = grid_layout_->itemAtPosition(start_row_, start_colum_);
    int index = grid_layout_->indexOf(item);
    ElWidget* item_widget = (ElWidget*)grid_layout_->takeAt(index)->widget();
    if (item_widget)
    {
        delete item_widget;
        item_widget = nullptr;
    }

    for (int i = start_row_; i < start_row_ + selected_height_; i++)
    {
        for (int j = start_colum_; j < start_colum_ + selected_width_; j++)
        {
            if (i == start_row_ && j == start_colum_)continue;
            item = grid_layout_->itemAtPosition(i, j);
            if (!item)continue;
            item_widget = (ElWidget*)item->widget();
            if (!item_widget)continue;

            if ((item_widget->width > 1) || (item_widget->height > 1))
            {
                int index = grid_layout_->indexOf(item);
                grid_layout_->takeAt(index);
                delete item_widget;
                item_widget = new ElWidget(i, j);
                grid_layout_->addWidget(item_widget, i, j);
            }

            item_widget->isCovered = true;
            item_widget->block_row = start_row_;
            item_widget->block_colum = start_colum_;
        }
    }

    ElWidget* elwidget = new ElWidget(start_row_, start_colum_, selected_width_, selected_height_);
    QObject::connect(elwidget, SIGNAL(selected(int, int)), this, SLOT(refreshing(int, int)));
    grid_layout_->addWidget(elwidget, start_row_, start_colum_, selected_height_, selected_width_);

    scroll_area_->set_merge_enable(false);
    scroll_area_->set_split_enable(false);
}

void Manager::splitting()
{
    qDebug() << "spliting first row : " << first_row_ << "  first colum : " << first_colum_;
    //int index = -1;
    int width = -1, height = -1;
    int row = first_row_;
    int colum = first_colum_;
    QLayoutItem* item = nullptr;
    ElWidget* item_widget = nullptr;


    item = grid_layout_->itemAtPosition(row, colum);
    int index = grid_layout_->indexOf(item);
    item_widget = (ElWidget*)grid_layout_->takeAt(index)->widget();
    if (item_widget == nullptr)return;
    width = item_widget->width;
    height = item_widget->height;
    delete item_widget;

    item_widget = new ElWidget(row, colum);
    QObject::connect(item_widget, SIGNAL(selected(int, int)), this, SLOT(refreshing(int, int)));
    grid_layout_->addWidget(item_widget, row, colum);
    scroll_area_->set_merge_enable(false);
    scroll_area_->set_split_enable(false);

    for (int i = row ; i < row + height; i++)
    {
        for (int j = colum; j < colum + width; j++)
        {
            item = grid_layout_->itemAtPosition(i, j);
            //if (!item)continue;
            item_widget = (ElWidget*)item->widget();
            //if (!item_widget)continue;

            if (item_widget->isCovered)
            {
                item_widget->isCovered = false;
                item_widget->block_row = -1;
                item_widget->block_colum = -1;
            }
        }
    }

    //item = grid_layout_->itemAtPosition(row, colum);
    //int index = grid_layout_->indexOf(item);
    //item_widget = (ElWidget*)grid_layout_->takeAt(index)->widget();
    //if (item_widget == nullptr)return;
    //delete item_widget;

    //item_widget = new ElWidget(row, colum);
    //QObject::connect(item_widget, SIGNAL(selected(int, int)), this, SLOT(refreshing(int, int)));
    //grid_layout_->addWidget(item_widget, row, colum);
    //scroll_area_->set_merge_enable(false);
    //scroll_area_->set_split_enable(false);

    first_point_selected_ = false;
    first_row_ = -1;
    first_colum_ = -1;
    second_point_selected_ = false;
    second_row_ = -1;
    second_colum_ = -1;
}




void Manager::refreshing(int row, int colum)
{
    QLayoutItem* item = nullptr;
    ElWidget* item_widget = nullptr;
    if (!first_point_selected_)
    {
        scroll_area_->set_merge_enable(false);
        first_point_selected_ = true;
        first_colum_ = colum;
        first_row_ = row;
        item_widget = (ElWidget*)grid_layout_->itemAtPosition(first_row_, first_colum_)->widget();
        if (item_widget == nullptr)return;
        if ((item_widget->width > 1) || (item_widget->height > 1))
        {
            scroll_area_->set_split_enable();
        }
        if (item_widget->isSelected)
        {
            item_widget->isFirstPoint = true;
            item_widget->refresh();
        }
        return;
    }
    if (!second_point_selected_)
    {
        second_point_selected_ = true;
        scroll_area_->set_merge_enable();
        scroll_area_->set_split_enable(false);
    }
    else
    {
        for (int i = 0; i < grid_row_; i++)
        {
            for (int j = 0; j < grid_colum_; j++)
            {
                item_widget = (ElWidget*)grid_layout_->itemAtPosition(i, j)->widget();
                if (item_widget == nullptr)continue;
                if (item_widget->isSelected)
                {
                    if (item_widget->isFirstPoint)continue;
                    item_widget->isSelected = false;
                    item_widget->refresh();
                }

            }
        }
    }
    second_colum_ = colum;
    second_row_ = row;

    if (second_colum_ == first_colum_ && second_row_ == first_row_)
    {
        first_point_selected_ = false;
        second_point_selected_ = false;
        item_widget = (ElWidget*)grid_layout_->itemAtPosition(first_row_, first_colum_)->widget();
        item_widget->isFirstPoint = false;
        item_widget->isSelected = false;
        item_widget->refresh();
        first_colum_ = -1;
        first_row_ = -1;
        second_colum_ = -1;
        second_row_ = -1;
        return;
    }
    item_widget = (ElWidget*)grid_layout_->itemAtPosition(first_row_, first_colum_)->widget();
    int end_colum_1 = item_widget->colum + item_widget->width;
    int end_row_1 = item_widget->row + item_widget->height;

    item_widget = (ElWidget*)grid_layout_->itemAtPosition(second_row_, second_colum_)->widget();
    int end_colum_2 = item_widget->colum + item_widget->width;
    int end_row_2 = item_widget->row + item_widget->height;

    end_colum_ = (end_colum_1 - end_colum_2) > 0 ? end_colum_1 : end_colum_2;
    end_row_ = (end_row_1 - end_row_2) > 0 ? end_row_1 : end_row_2;


    start_colum_ = (first_colum_ - second_colum_) < 0 ? first_colum_ : second_colum_;
    start_row_ = (first_row_ - second_row_) < 0 ? first_row_ : second_row_;

    selected_width_ = end_colum_ - start_colum_;
    selected_height_ = end_row_ - start_row_;


    for (;;)
    {
        int temp_colum = start_colum_;
        int temp_row = start_row_;
        int temp_end_colum = end_colum_;
        int temp_end_row = end_row_;
        int temp_width = selected_width_;
        int temp_height = selected_height_;
        GetRange();
        if (temp_colum == start_colum_ && temp_row == start_row_ && temp_end_colum == end_colum_ && temp_end_row == end_row_ && temp_width == selected_width_ && temp_height == selected_height_)
        {
            break;
        }
    }

    for (int i = start_row_; i < start_row_ + selected_height_; i++)
    {
        for (int j = start_colum_; j < start_colum_ + selected_width_; j++)
        {
            item_widget = (ElWidget*)grid_layout_->itemAtPosition(i, j)->widget();
            if (item_widget == nullptr)continue;
            if (!item_widget->isSelected)
            {
                item_widget->isSelected = true;
            }
            item_widget->refresh();
        }
    }
}



void Manager::GetRange()
{
    if (start_row_ == -1 || start_colum_ == -1 || selected_width_ == -1 || selected_height_ == -1)
    {
        return;
    }

    QLayoutItem* item = nullptr;
    ElWidget* item_widget = nullptr;

    int temp_start_row_ = start_row_;
    int temp_start_colum_ = start_colum_;
    int temp_width = selected_width_;
    int temp_height = selected_height_;
    int item_width = 0;
    int item_height = 0;

    for (int i = temp_start_row_; i < temp_start_row_ + temp_height; i++)
    {
        for (int j = temp_start_colum_; j < temp_start_colum_ + temp_width; j++)
        {
            item = grid_layout_->itemAtPosition(i, j);
            if (item == nullptr)continue;
            item_widget = (ElWidget*)item->widget();
            if (item_widget == nullptr)continue;

            int block_colum;
            int block_row;
            if (item_widget->isCovered)
            {
                block_colum = item_widget->block_colum;
                block_row = item_widget->block_row;
            }
            else
            {
                block_colum = item_widget->colum;
                block_row = item_widget->row;
            }

            item = grid_layout_->itemAtPosition(block_row, block_colum);
            if (item == nullptr)continue;
            item_widget = (ElWidget*)item->widget();
            if (item_widget == nullptr)continue;

            item_width = item_widget->width;
            item_height = item_widget->height;

            if (item_width > 1)
            {
                if (block_colum == temp_start_colum_)
                {
                    if ((block_colum + item_width) >= (temp_start_colum_ + temp_width))
                    {
                        if (end_colum_ < block_colum + item_width)
                        {
                            end_colum_ = block_colum + item_width;
                        }
                    }
                    else if ((block_colum + item_width) < (temp_start_colum_ + temp_width))
                    {

                    }
                }
                else if (block_colum > temp_start_colum_)
                {
                    if ((block_colum + item_width) >= (temp_start_colum_ + temp_width))
                    {
                        if (end_colum_ < block_colum + item_width)
                        {
                            end_colum_ = block_colum + item_width;
                        }
                    }
                    else if ((block_colum + item_width) < (temp_start_colum_ + temp_width))
                    {

                    }
                }
                else if (block_colum < temp_start_colum_)
                {
                    start_colum_ = block_colum;
                    if ((block_colum + item_width) >= (temp_start_colum_ + temp_width))
                    {
                        if (end_colum_ < temp_start_colum_ + item_width)
                        {
                            end_colum_ = temp_start_colum_ + item_width;
                        }
                    }
                    else if ((block_colum + item_width) < (temp_start_colum_ + temp_width))
                    {
                        if (end_colum_ < temp_start_colum_ + temp_width)
                        {
                            end_colum_ = temp_start_colum_ + temp_width;
                        }
                    }

                }

            }

            if (item_height > 1)
            {
                if (block_row == temp_start_row_)
                {
                    if ((block_row + item_height) >= (temp_start_row_ + temp_height))
                    {
                        if (end_row_ < block_row + item_height)
                        {
                            end_row_ = block_row + item_height;
                        }
                    }
                }

                else if (block_row > temp_start_row_)
                {
                    if ((block_row + item_height) >= (temp_start_row_ + temp_height))
                    {
                        if (end_row_ < block_row + item_height)
                        {
                            end_row_ = block_row + item_height;
                        }
                    }
                    else if ((block_row + item_height) < (temp_start_row_ + temp_height))
                    {

                    }
                }

                else if (block_row < temp_start_row_)
                {
                    start_row_ = block_row;
                    if ((block_row + item_height) >= (temp_start_row_ + temp_height))
                    {
                        if (end_row_ < block_row + item_height)
                        {
                            end_row_ = block_row + item_height;
                        }
                    }
                    else if ((block_row + item_height) < (temp_start_row_ + temp_height))
                    {
                        if (end_row_ < temp_start_row_ + temp_height)
                        {
                            end_row_ = temp_start_row_ + temp_height;
                        }
                    }
                }

            }

        }

        selected_width_ = end_colum_ - start_colum_;
        selected_height_ = end_row_ - start_row_;
    }
}

void Manager::SetAddress()
{
    QDialog dialog(this);
    dialog.resize(600, 300);
    QFormLayout* layout = new QFormLayout();
    dialog.setLayout(layout);

    QRegExp exp1("[0-9\.]+$");
    QRegExp exp2("[0-9]+$");

    QLineEdit le_addr;
    le_addr.setText(sock_client_->m_address);
    le_addr.setValidator(new QRegExpValidator(exp1, this));
    layout->addRow("ip_address : ", &le_addr);

    QLineEdit le_port;
    le_port.setText(QString("%1").arg(sock_client_->m_port));
    le_port.setValidator(new QRegExpValidator(exp2, this));
    layout->addRow("port : ", &le_port);

    QPushButton pbSave;
    pbSave.resize(80, 60);
    pbSave.setText("Save");
    QObject::connect(&pbSave, SIGNAL(clicked()), &dialog, SLOT(accept()));
    layout->addRow(&pbSave);

    for (;;)
    {
        if (dialog.exec() == QDialog::Accepted)
        {
            if (le_addr.text().isEmpty())
            {
                QMessageBox::information(nullptr, "error", "please enter ip address");
                continue;
            }

            if (le_port.text().isEmpty())
            {
                QMessageBox::information(nullptr, "error", "please enter port");
                continue;
            }

            //sock_client_->SetAddress(le_port.text().toInt(),le_addr.text());
            emit SetAddr(le_port.text().toInt(), le_addr.text());
            break;
        }
        else if (dialog.close())
        {
            break;
        }
    }
}

void Manager::ResetSvr()
{
    sock_svr_->ResetServer();
}


void Manager::SendLayoutFile()
{
    //QString filename = QFileDialog::getOpenFileName(this);
    //sock_client_->SetMsgFile(QString::fromLocal8Bit("normal"), filename);
    //sock_client_->Send();

    QDialog dia(this);
    QFormLayout* layout = new QFormLayout();
    dia.setLayout(layout);

    QRadioButton rb_refresh;
    rb_refresh.setText(QString::fromLocal8Bit("refresh"));

    QRadioButton rb_store;
    rb_store.setText(QString::fromLocal8Bit("store"));

    QPushButton pb_open;
    pb_open.setText(QString::fromLocal8Bit("open"));
    QObject::connect(&pb_open, SIGNAL(clicked()), &dia, SLOT(accept()));

    layout->addRow(&rb_refresh);
    layout->addRow(&rb_store);
    layout->addRow(&pb_open);

    for (;;)
    {
        if (dia.exec() == QDialog::Accepted)
        {
            QString filename = QFileDialog::getOpenFileName(this);
            if (rb_refresh.isChecked())
            {
                emit OpenFile(QString::fromLocal8Bit("refresh"), filename);
            }
            else
            {
                emit OpenFile(QString::fromLocal8Bit("store"), filename);
            }

            emit StartSend();
            break;
        }
        else if (dia.close())
        {
            return;
        }
    }
}

void Manager::DisconnectToManager()
{
    emit ClientDisconnect();
}

void Manager::StartSend()
{
    emit SendFile();
}

void Manager::OpenFile()
{
    QString filename = QFileDialog::getOpenFileName(this);
    emit OpenFile(QString::fromLocal8Bit("normal"), filename);
}

void Manager::GetClientStatus(bool status)
{
    is_client_connected_ = status;
    if (!is_client_connected_)
    {
        emit ClientConnect();
    }
}


