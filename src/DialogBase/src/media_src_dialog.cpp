#include "media_src_dialog.h"

 //#include "capturer/get_device.h"
#include "screen_capture_dialog.h"
//#include "confile.h"
#include "config_helper.h"
#include "my_tabwidget.h"

#include <QLabel>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QCheckBox>
#include <QButtonGroup>
#include <QDebug>
#include <QScreen>
#include <QMouseEvent>
#include <QList>
#include <QStyleOption>
#include <QPainter>

#include <sstream>

struct ImageFormatRow
{
    std::string name;
    //GUID directshowFormat;
};

//static ImageFormatRow ImageFormatTable[] = 
//{ 
//    {"ARGB32", MEDIASUBTYPE_ARGB32},
//    {"RGB32", MEDIASUBTYPE_RGB32},
//    {"RGB24", MEDIASUBTYPE_RGB24},
//    {"RGB555", MEDIASUBTYPE_RGB555},
//    {"RGB565", MEDIASUBTYPE_RGB565},
//    {"MJPG", MEDIASUBTYPE_MJPG},
//    {"JPG", MEDIASUBTYPE_IJPG},
//    {"AYUV", MEDIASUBTYPE_AYUV},
//    {"IYUV", MEDIASUBTYPE_IYUV},
//    {"YV12", MEDIASUBTYPE_YV12},
//    {"UYVY", MEDIASUBTYPE_UYVY},
//    {"YUYV", MEDIASUBTYPE_YUYV},
//    {"YUY2", MEDIASUBTYPE_YUY2},
//    {"NV12", MEDIASUBTYPE_NV12},
//    {"IMC1", MEDIASUBTYPE_IMC1},
//    {"IMC2", MEDIASUBTYPE_IMC2},
//    {"IMC3", MEDIASUBTYPE_IMC3},
//    {"IMC4", MEDIASUBTYPE_IMC4}
//};

MediaSrcDialog::MediaSrcDialog(QWidget* parent) : QDialog(parent)
{
    //ui.setupUi(this);
    initUI();
    initConnect();
}

MediaSrcDialog::~MediaSrcDialog()
{
    if (capture_tab_)
    {
        delete capture_tab_;
    }
    if (desktop_tab_)
    {
        delete desktop_tab_;
    }
    if (title_)
    {
        delete title_;
    }
    if (tab_)
    {
        delete tab_;
    }

}

void MediaSrcDialog::paintEvent(QPaintEvent* ev)
{
    QStyleOption option;
    option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
    QWidget::paintEvent(ev);
}

void MediaSrcDialog::initUI() 
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);

    setFixedSize(600, 380);

    this->setStyleSheet(ConfigHelper::GetInstance()->GetQssString(":/screen_capture_dialog/res/css/media_src_dialog.css"));
    title_ = new DialogTitle(this, "Please select a media source");

    QPushButton* pb_open = new QPushButton();
    QPushButton* pb_cancel = new QPushButton();
    pb_open->setFixedSize(60, 30);
    pb_cancel->setFixedSize(60, 30);

    pb_open->setText("ok");
    pb_cancel->setText("cancel");

    QHBoxLayout* pb_layout = new QHBoxLayout();
    QLabel* lb_empty = new QLabel();
    lb_empty->setStyleSheet("background-color: #1c1c1c;");
    lb_empty->setMinimumWidth(390);
    
    pb_layout->setSizeConstraint(QLayout::SetMaximumSize);
    pb_layout->addSpacerItem(new QSpacerItem(150, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    pb_layout->addWidget(lb_empty, 1);
    pb_layout->addWidget(pb_open);
    pb_layout->addWidget(pb_cancel);
    QObject::connect(pb_open, &QPushButton::clicked, this, &QDialog::accept);
    QObject::connect(pb_cancel, &QPushButton::clicked, this, &QDialog::reject);

    tab_ = new MyTabWidget();
    desktop_tab_ = new DesktopTab(0);
    capture_tab_ = new CaptureTab(1);

    capture_tab_->setStyleSheet("DialogContentTabBase{border-radius: 0px;}");

    //tab->addTab(new FileTab, QIcon(":/image/file.png"), tr("File"));
    tab_->addTab(capture_tab_, tr("Camera"));
    tab_->addTab(desktop_tab_, tr("Desktop"));
    //tab->addTab(new CaptureTab(nullptr, CAP_TYPE_AUDIO), QIcon(":/image/capture.png"), tr("ACapture"));

    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(0);
    vbox->addWidget(title_);
    vbox->addWidget(tab_,1);
    vbox->addLayout(pb_layout,0);
    this->setLayout(vbox);

    QObject::connect(title_, &DialogTitle::sigCloseBtnClicked, this, [this] { this->reject(); });
    QObject::connect(desktop_tab_, &DesktopTab::sigDeskTopTabProcessingScreenCap, this, [this] {emit sigMediaDialogProcessScreenCap(); qDebug() << " "; this->showMinimized(); });
    QObject::connect(desktop_tab_, &DesktopTab::sigDeskTopTabProcessingScreenCapFinshed, this, [this] {qDebug() << "dia fin"; emit sigMediaDialogProcessScreenCapFinished(); this->showNormal(); });
}

void MediaSrcDialog::initConnect() 
{

}

void MediaSrcDialog::mousePressEvent(QMouseEvent* ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        left_bt_pressed_ = true;
        mouse_drag_point_ = ev->pos();
    }
    return QDialog::mousePressEvent(ev);
}

void MediaSrcDialog::mouseMoveEvent(QMouseEvent* ev)
{
    if (title_->geometry().contains(mouse_drag_point_) && left_bt_pressed_)
    {
        this->move(ev->globalPos() - mouse_drag_point_);
    }
    return QDialog::mouseMoveEvent(ev);
}

void MediaSrcDialog::accept() 
{
    switch (tab_->currentIndex())
    {
        //case MEDIA_TYPE_FILE:
        //{
        //    FileTab* filetab = qobject_cast<FileTab*>(tab->currentWidget());
        //    if (filetab) 
        //    {
        //        media_info_.type = MEDIA_TYPE_FILE;
        //        media_info_.src = filetab->edit->text().toUtf8().data();
        //        //g_confile->SetValue("last_file_source", media.src.c_str(), "media");
        //        //g_confile->Save();
        //    }
        //}
        //break;
        //case MEDIA_TYPE_WEBCAM:
        //{
        //    CaptureTab* captab = qobject_cast<CaptureTab*>(tab->currentWidget());
        //    if (captab) 
        //    {
        //        media_info_.type = MEDIA_TYPE_WEBCAM;
        //        media_info_.src = qPrintable(captab->cb_dev_name_->currentText());
        //        media_info_.index = captab->cb_dev_name_->currentIndex();

        //        //std::string res = captab->cb_dev_resolution_->currentData().toString().toStdString();
        //        std::string res = captab->cb_dev_resolution_->currentText().toStdString();
        //        auto pos = res.find("@");
        //        media_info_.resolution = res.substr(0,pos);
        //        //res.substr(pos);
        //        media_info_.pix_format = res.substr(pos+1);

        //        //qDebug() << media_info_.resolution.c_str() << " : " << media_info_.pix_format.c_str();

        //    }
        //}
        //case MEDIA_TYPE_DESKTOP:
        //{
        //    DesktopTab* dsktab = qobject_cast<DesktopTab*>(tab->currentWidget());
        //    if (dsktab)
        //    {
        //        media_info_.type = MEDIA_TYPE_DESKTOP;
        //        
        //        media_info_.src = qPrintable(dsktab->group_type_->checkedButton()->text());
        //        media_info_.index = dsktab->group_type_->checkedId();
        //        media_info_.width = dsktab->le_width_->text().toInt();
        //        media_info_.height = dsktab->le_height_->text().toInt();

        //        std::stringstream stream;
        //        stream << media_info_.width << "x" << media_info_.height;
        //        media_info_.resolution = stream.str();
        //        media_info_.pix_format = "BGRA";

        //        //qDebug() << media_info_.resolution.c_str() << " : " << media_info_.pix_format.c_str();
        //    }
        //}
        //break;
        default:
            break;
    }

    //if (media_info_.type == MEDIA_TYPE_NONE ||
    //    (media_info_.src.empty() && media_info_.index < 0))
    //{
    //    //QMessageBox::information(this, tr("Info"), tr("Invalid media source!"));
    //    return;
    //}

    //g_confile->Set<int>("last_tab", tab->currentIndex(), "media");
    //g_confile->Save();

    QDialog::accept();
}
//
//MediaInfo MediaSrcDialog::getMediaInfo()
//{
//    return media_info_;
//}
