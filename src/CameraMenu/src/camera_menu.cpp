#include "camera_menu.h"
#include <QVBoxLayout>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QPalette>
#include <QFontDatabase>
#include <QTabBar>

#include "config_helper.h"
#include "item_set_dialog.h"
#include "media_src_dialog.h"

#define ITEM_LIST_CONFIG "./config/configuration.json"
#define ITEM_LIST_COUNT 3

CameraMenu::CameraMenu(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    initUi();

    ui.tw_item->setTabText(0, QString::fromLocal8Bit("相机"));
    ui.tw_item->setTabText(1, QString::fromLocal8Bit("文件"));
    ui.tw_item->setTabText(2, QString::fromLocal8Bit("源"));

    //lw_camera_ = new ItemListWidget(this);
    //lw_camera_ = (ItemListWidget*)ui.tw_item->widget(1);
    //lw_camera_->setDragEnabled(true);

    config_tools_ = ConfigHelper::GetInstance();
    config_tools_->InitJson();
    initItemList();

    QObject::connect(ui.pb_add, &QPushButton::clicked, this, &CameraMenu::onCmrMenuAddButtonClicked);
    QObject::connect(ui.pb_set, &QPushButton::clicked, this, &CameraMenu::onCmrMenuSetButtonClicked);
    QObject::connect(ui.pb_del, &QPushButton::clicked, this, &CameraMenu::onCmrMenuDelButtonClicked);
}

CameraMenu::~CameraMenu()
{
    delete lw_local_file_;
    //delete lw_camera_;
    delete vb_local_file_;
    //delete vb_camera_;
}

void CameraMenu::initUi()
{
    setStyleSheet(ConfigHelper::GetQssString(":/camera_menu/res/css/camera_menu.css"));
    int id = QFontDatabase::addApplicationFont(":/camera_menu/res/fonts/Font Awesome 6 Pro-Light-300.otf");
    if (id < 0)
        qWarning() << "FontAwesome cannot be loaded !";

    QFont font;
    QString family = QFontDatabase::applicationFontFamilies(id).first();
    font.setFamily(family);

    font.setPixelSize(16);
    font.setPointSize(16);
    ui.pb_add->setFont(font);
    ui.pb_set->setFont(font);
    ui.pb_del->setFont(font);

    ui.pb_add->setText(QChar(0xf65e));
    ui.pb_set->setText(QChar(0xf304));
    ui.pb_del->setText(QChar(0xf65f));

    lw_camera_ = new ItemListWidget(0);
    //lw_camera_->setViewMode(QListView::ListMode);
    //lw_camera_->setDragDropMode(QAbstractItemView::InternalMove);
    //lw_camera_->setDragEnabled(true);
    //lw_camera_->setFrameShape(QFrame::NoFrame);
    lw_camera_->setStyleSheet(ConfigHelper::GetQssString(":/camera_menu/res/css/item_list_widget.css"));
    vb_camera_ = new QVBoxLayout();
    vb_camera_->setContentsMargins(0, 0, 0, 0);
    vb_camera_->setMargin(0);
    vb_camera_->setSpacing(0);
    vb_camera_->addWidget(lw_camera_);
    ui.tw_item->widget(0)->setLayout(vb_camera_);

    lw_local_file_ = new ItemListWidget(1);
    //lw_local_file_->setViewMode(QListView::ListMode);
    //lw_local_file_->setDragDropMode(QAbstractItemView::InternalMove);
    //lw_local_file_->setDragEnabled(true);
    //lw_local_file_->setFrameShape(QFrame::NoFrame);
    lw_local_file_->setStyleSheet(ConfigHelper::GetQssString(":/camera_menu/res/css/item_list_widget.css"));
    vb_local_file_ = new QVBoxLayout();
    vb_local_file_->setContentsMargins(0, 0, 0, 0);
    vb_local_file_->setMargin(0);
    vb_local_file_->setSpacing(0);
    vb_local_file_->addWidget(lw_local_file_);
    ui.tw_item->widget(1)->setLayout(vb_local_file_); 
    
    //auto ev_handle = new EventsListener();
    lw_media_src_ = new ItemListWidget(2);
    //lw_media_src_->setViewMode(QListView::ListMode);
    //lw_media_src_->setDragDropMode(QAbstractItemView::InternalMove);
    //lw_media_src_->setDragEnabled(true);
    //lw_local_file_->setFrameShape(QFrame::NoFrame);
    //ev_handle->handleEventsOf(lw_media_src_);
    lw_media_src_->setStyleSheet(ConfigHelper::GetQssString(":/camera_menu/res/css/item_list_widget.css"));
    vb_media_src_ = new QVBoxLayout();
    vb_media_src_->setContentsMargins(0, 0, 0, 0);
    vb_media_src_->setMargin(0);
    vb_media_src_->setSpacing(0);
    vb_media_src_->addWidget(lw_media_src_);
    ui.tw_item->widget(2)->setLayout(vb_media_src_);

}

int CameraMenu::getCurrentItemIndex()
{
    //lw_camera_->currentItem();
    return 0;
}

void CameraMenu::onCmrMenuAddButtonClicked()
{
    addListItem();
}

void CameraMenu::onCmrMenuSetButtonClicked()
{
    setListItem();
}

void CameraMenu::onCmrMenuDelButtonClicked()
{
    deleteItem();
}


void CameraMenu::addListItem()
{
    ItemListType type = (ItemListType)ui.tw_item->currentIndex();
    //switch (type)
    //{
    //	case ItemListType::ITEM_LIST_TYPE_CAMERA:
    //	{
    //		SetListItem(type, -1);
    //		break;
    //	}
    //	case ItemListType::ITEM_LIST_TYPE_LOCAL_FILE:
    //	{
    //		SetLocalListItem(type, -1);
    //		break;
    //	}
    //	default:
    //	{
    //		qDebug() << "AddListItem ITEM_LIST_TYPE_NONE";
    //		break;
    //	}
    //}
    if (type == ItemListType::ITEM_LIST_TYPE_MEDIA_SRC)
    {
        setMediaSrcItem(-1);
    }
    else
    {
        setListItem(type, -1);
    }
}

void CameraMenu::setListItem()
{
    ItemListType type = (ItemListType)ui.tw_item->currentIndex();
    //if (type == ItemListType::ITEM_LIST_TYPE_MEDIA_SRC)
    //{

    //}
    int index = ((ItemListWidget*)(ui.tw_item->widget((int)type)->layout()->itemAt(0)->widget()))->currentIndex().row();
    if (index < 0)
    {
        qDebug() << "SetListItem failed : please select a item";
        return;
    }
    //switch (type)
    //{
    //	case ItemListType::ITEM_LIST_TYPE_CAMERA:
    //	{
    //		SetListItem(type, index);
    //		break;
    //	}
    //	case ItemListType::ITEM_LIST_TYPE_LOCAL_FILE:
    //	{
    //		SetLocalListItem(type, index);
    //		break;
    //	}
    //	default:
    //	{
    //		qDebug() << "SetListItem ITEM_LIST_TYPE_NONE";
    //		return;
    //	}
    //}
    setListItem(type, index);
}
//
//void CameraMenu::SetListItem(ItemListType item_type, int item_index)
//{
//
//    QDialog dia(this);
//    dia.resize(600, 120);
//
//    QFormLayout* formLayout = new QFormLayout();
//    dia.setLayout(formLayout);
//
//    QLineEdit leName;
//    formLayout->addRow(QString::fromLocal8Bit("name : "), &leName);
//
//    QLineEdit leUrl;
//    formLayout->addRow(QString::fromLocal8Bit("url"), &leUrl);
//
//    QLineEdit leSubUrl;
//    if (item_type == ItemListType::ITEM_LIST_TYPE_CAMERA)
//    {
//        formLayout->addRow(QString::fromLocal8Bit("sub_url"), &leSubUrl);
//    }
//
//    QPushButton pbAccept;
//    pbAccept.setText(QString::fromLocal8Bit("accept"));
//    QObject::connect(&pbAccept, SIGNAL(clicked()), &dia, SLOT(accept()));
//    formLayout->addRow(&pbAccept);
//
//    QJsonObject obj;
//    QString key;
//    if (item_index >= 0)
//    {
//        ItemListWidget* lwCur = (ItemListWidget*)ui.tw_item->currentWidget()->layout()->itemAt(0)->widget();
//        lwCur->item_type_ = (int)item_type;
//        key = lwCur->currentItem()->text();
//        obj = *config_tools_->GetObject((ConfigHelper::JsonObjType)item_type);
//
//        if (!obj.contains(key))
//        {
//            qDebug() << "set item : do not have this key";
//            return;
//        }
//        QJsonObject::iterator it = obj.find(key);
//        obj = it.value().toObject();
//        leName.setText(obj.find("name").value().toString());
//        leUrl.setText(obj.find("url").value().toString());
//        if (item_type == ItemListType::ITEM_LIST_TYPE_CAMERA)
//        {
//            leSubUrl.setText(obj.find("SubUrl").value().toString());
//        }
//        DeleteItem(item_type, item_index);
//    }
//
//    QJsonObject info;
//
//    for (;;)
//    {
//        if (dia.exec() == QDialog::Accepted)
//        {
//            if (leName.text().isEmpty())
//            {
//                QMessageBox::information(nullptr, "error", "please set a name");
//                continue;
//            }
//
//            if (leUrl.text().isEmpty())
//            {
//                QMessageBox::information(nullptr, "error", "please set a name");
//                continue;
//            }
//
//            if (item_type == ItemListType::ITEM_LIST_TYPE_CAMERA)
//            {
//                if (leSubUrl.text().isEmpty())
//                {
//                    QMessageBox::information(nullptr, "error", "please set a name");
//                    continue;
//                }
//                info.insert("SubUrl", leSubUrl.text());
//            }
//
//            info.insert("name", leName.text());
//            info.insert("url", leUrl.text());
//            info.insert("item_type", (int)item_type);
//            //info.insert("item_index", index);
//            config_tools_->WriteJson(leName.text(), info, (ConfigHelper::JsonObjType)item_type);
//            config_tools_->SaveJson(ITEM_LIST_CONFIG);
//            InitItemList();
//            break;
//        }
//        else if (dia.close())
//        {
//            //config_tools_->WriteJson(key, obj, (ConfigHelper::JsonObjType)item_type);
//            //QJsonDocument doc;
//            //doc.setObject(obj);
//            //QByteArray arr = doc.toJson();
//            //config_tools_->SaveJson(ITEM_LIST_CONFIG);
//            //InitItemList();
//            return;
//        }
//    }
//
//}

void CameraMenu::setMediaSrcItem(int item_index)
{

}

void CameraMenu::setListItem(ItemListType item_type, int item_index)
{
    ItemSetDialog* dia = new ItemSetDialog((int)item_type);
    Qt::WindowFlags flag = dia->windowFlags();
    dia->setWindowFlags(flag | Qt::MSWindowsFixedSizeDialogHint);

    QJsonObject obj;
    QString key;
    QString name;
    QString url;
    QString sub_url;
    QString server_url;

    if (item_index >= 0)
    {
        ItemListWidget* lwCur = (ItemListWidget*)ui.tw_item->currentWidget()->layout()->itemAt(0)->widget();
        lwCur->setItemType((int)item_type);
        key = lwCur->currentItem()->text();
        obj = *config_tools_->GetObject((ConfigHelper::JsonObjType)item_type);

        if (!obj.contains(key))
        {
            qDebug() << "set item : do not have this key";
            return;
        }
        QJsonObject::iterator it = obj.find(key);
        obj = it.value().toObject();

        name = obj.find("name").value().toString();
        url = obj.find("url").value().toString();
        server_url = obj.find("server_url").value().toString();
        if (item_type == ItemListType::ITEM_LIST_TYPE_CAMERA)
        {
            sub_url = obj.find("SubUrl").value().toString();
        }
        dia->setName(name);
        dia->setUrl(url);
        dia->setSubUrl(sub_url);
        dia->setServerUrl(server_url);
        deleteItem(item_type, item_index);
    }

    QJsonObject info;

    for (;;)
    {
        if (dia->exec() == QDialog::Accepted)
        {
            if (dia->getName().isEmpty())
            {
                QMessageBox::information(nullptr, "error", "please set a name");
                continue;
            }

            if (dia->getUrl().isEmpty())
            {
                QMessageBox::information(nullptr, "error", "url is empty");
                continue;
            }

            if (item_type == ItemListType::ITEM_LIST_TYPE_CAMERA)
            {
                if (dia->getSubUrl().isEmpty())
                {
                    QMessageBox::information(nullptr, "error", "sub url is empty");
                    continue;
                }
                info.insert("SubUrl", dia->getSubUrl());
            }

            info.insert("name", dia->getName());
            info.insert("url", dia->getUrl());
            info.insert("sub_url", dia->getSubUrl());
            info.insert("server_url", dia->getServerUrl());
            info.insert("item_type", (int)item_type);

            config_tools_->WriteJson(dia->getName(), info, (ConfigHelper::JsonObjType)item_type);
            config_tools_->SaveJson(ITEM_LIST_CONFIG);
            initItemList();
            break;
        }
        else if (dia->close())
        {
            if (item_index < 0)
            {
                return;
            }
            config_tools_->WriteJson(key, obj, (ConfigHelper::JsonObjType)item_type);
            ////QJsonDocument doc;
            ////doc.setObject(obj);
            ////QByteArray arr = doc.toJson();
            config_tools_->SaveJson(ITEM_LIST_CONFIG);
            initItemList();
            return;
        }
    }
}

void CameraMenu::setLocalListItem(ItemListType item_type, int item_index)
{
    QString openPicUrl = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择文件"), QString("./"), QString("Files (*.mp4)"));
    QString openPicName = openPicUrl.right(openPicUrl.size() - openPicUrl.lastIndexOf('/') - 1);
    if (openPicName.size())
    {
        if (item_index >= 0)
        {
            ItemListWidget* lwCur = (ItemListWidget*)ui.tw_item->currentWidget()->layout()->itemAt(0)->widget();
            //lwCur->itemType = itemType;
            lwCur->currentItem()->setText(openPicName);
            deleteItem(item_type, item_index);
        }

        QJsonObject obj;
        obj.insert("name", openPicName);
        obj.insert("url", openPicUrl);
        obj.insert("item_type", (int)item_type);
        config_tools_->WriteJson(openPicName, obj, (ConfigHelper::JsonObjType)item_type);
        config_tools_->SaveJson(ITEM_LIST_CONFIG);
        initItemList();
    }

}

void CameraMenu::deleteItem()
{
    int type = ui.tw_item->currentIndex();
    ItemListWidget* curList = (ItemListWidget*)ui.tw_item->currentWidget()->layout()->itemAt(0)->widget();
    if (curList->currentIndex().row() < 0)
    {
        QMessageBox::information(nullptr, "error", QString::fromLocal8Bit("please select a item"));
        return;
    }
    this->deleteItem((ItemListType)type, curList->currentIndex().row());
}

void CameraMenu::deleteItem(ItemListType itemType, int index)
{
    QString key = ((ItemListWidget*)ui.tw_item->currentWidget()->layout()->itemAt(0)->widget())->currentItem()->text();
    QJsonObject* obj = config_tools_->GetObject((ConfigHelper::JsonObjType)itemType);
    if (obj->contains(key))
    {
        //QJsonObject::iterator it = obj.find(key);
        //obj.erase(it);
        obj->take(key);
        config_tools_->SaveJson(ITEM_LIST_CONFIG);
        initItemList();
    }

}

void CameraMenu::initItemList()
{
    if (config_tools_->LoadJson(ITEM_LIST_CONFIG))
    {
        QMessageBox::information(nullptr, "error", QString("load %1 failed").arg(ITEM_LIST_CONFIG));
        return;
    }
    QJsonObject* src;
    QStringList src_key;
    for (int i = 0; i < ITEM_LIST_COUNT; i++)
    {
        ItemListWidget* list = (ItemListWidget*)ui.tw_item->widget(i)->layout()->itemAt(0)->widget();
        list->clear();
        src = config_tools_->GetObject((ConfigHelper::JsonObjType)i);
        if (!src)
        {
            break;
        }
        src_key = src->keys();
        for (auto it = src_key.begin(); it != src_key.end(); it++)
        {
            QString key = *it;
            list->addItem(key);
        }
    }
}

void CameraMenu::initExtendButton()
{

}