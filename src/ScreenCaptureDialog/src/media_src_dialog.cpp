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

    pb_open->setText("open");
    pb_cancel->setText("cancel");

    QHBoxLayout* pb_layout = new QHBoxLayout();
    pb_layout->setSizeConstraint(QLayout::SetMaximumSize);
    pb_layout->addSpacerItem(new QSpacerItem(150, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    pb_layout->addWidget(pb_open);
    pb_layout->addWidget(pb_cancel);
    QObject::connect(pb_open, &QPushButton::clicked, this, &QDialog::accept);
    QObject::connect(pb_cancel, &QPushButton::clicked, this, &QDialog::reject);

    tab_ = new MyTabWidget();
    desktop_tab_ = new DesktopTab(0);
    capture_tab_ = new CaptureTab(1);

    capture_tab_->setStyleSheet("DialogContentTabBase{border-top-left-radius: #1c1c1c;}");

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


//FileTab::FileTab(QWidget* parent) : QWidget(parent) 
//{
//    QVBoxLayout* vbox = new QVBoxLayout;
//
//    vbox->addStretch();
//    vbox->addWidget(new QLabel(tr("File:")));
//
//    QHBoxLayout* hbox = new QHBoxLayout;
//    edit = new QLineEdit;
//    //std::string str = g_confile->GetValue("last_file_source", "media");
//    //if (!str.empty()) {
//    //    edit->setText(QString::fromUtf8(str.c_str()));
//    //}
//    hbox->addWidget(edit);
//    btnBrowse = new QPushButton("...");
//    connect(btnBrowse, &QPushButton::clicked, this, 
//        [=]() 
//        {
//            QString file = QFileDialog::getOpenFileName(this, tr("Open Meida File"), "",
//                "Video Files(*.3gp *.amv *.asf *.avi *.flv *.m2v *.m4v *.mkv *.mp2 *.mp4 *.mpg *.swf *.ts *.rmvb *.wmv)\n"
//                "All Files(*)");
//            if (!file.isEmpty()) 
//            {
//                edit->setText(file);
//            }
//        }
//    );
//    hbox->addWidget(btnBrowse);
//
//    vbox->addLayout(hbox);
//    vbox->addStretch();
//
//    setLayout(vbox);
//}
//
//
//CaptureTab::CaptureTab(int tab_index, QWidget* parent, capture_type type) : QWidget(parent), cap_type_(type) 
//{
//    tab_index_ = tab_index;
//    //QVBoxLayout* vbox = new QVBoxLayout;
//
//    //vbox->addStretch();
//    //vbox->addWidget(new QLabel(tr("Device:")));
//
//    //cb_dev_name_ = new QComboBox;
//    //cb_dev_resolution_ = new QComboBox;
//
//    //std::vector<CaptureDevice> devs;
//    //if (cap_type_ == CAP_TYPE_VIDEO)
//    //    //devs = getVideoCaptureDevices();
//    //    devs = CaptureDevice::getInstance()->getVideoDevicesList();
//    //else{}
//    //    //devs = getAudioCaptureDevices();
//
//    ////for (int i = 0; i < devs.size(); ++i) 
//    ////{
//    ////    cmb->addItem(devs[i].name);
//    ////}
//    //    for (auto it : devs)
//    //    {
//    //        cb_dev_name_->addItem(it.name);
//    //        for (auto i : it.properties_list)
//    //        {
//    //            QString str_pix_fmt;
//    //            for (auto fmt : ImageFormatTable)
//    //            {
//    //                if (fmt.directshowFormat == i.pixelFormat)
//    //                {
//    //                    str_pix_fmt = QString(fmt.name.c_str());
//    //                }
//    //            }
//    //            QString s = QString("%1x%2@%3").arg(i.width).arg(i.height).arg(str_pix_fmt);
//    //            cb_dev_resolution_->addItem(s);
//    //        }
//    //    }
//
//    //vbox->addWidget(cb_dev_name_);
//    //vbox->addStretch();
//    //vbox->addWidget(cb_dev_resolution_);
//
//
//    //setLayout(vbox);
//}
//
//
//DesktopTab::DesktopTab(int tab_index, QWidget* parent, capture_type type)
//{
//    tab_index_ = tab_index;
//    ui.setupUi(this);
//    this->setStyleSheet(ConfigHelper::GetInstance()->GetQssString(":/screen_capture_dialog/res/css/my_tabwidget.css"));
//
//    auto screen = QGuiApplication::primaryScreen();
//    screen_rect_ = screen->geometry();
//
//    group_type_ = new QButtonGroup(this);
//    group_type_->setExclusive(true);
//    
//    ck_dxgi_ = ui.ck_dxgi;
//    ck_dshow_ = ui.ck_dshow;
//    ck_gdi_ = ui.ck_gdi;
//
//    group_type_->addButton(ck_dxgi_);
//    group_type_->addButton(ck_dshow_);
//    group_type_->addButton(ck_gdi_);
//    ck_dxgi_->setChecked(true);
//
//    group_size_ = new QButtonGroup(this);
//    group_size_->setExclusive(true);
//
//    ck_capture_area_ = ui.ck_capture_area;
//    ck_full_screen_ = ui.ck_full_screen;
//    group_size_->addButton(ck_capture_area_);
//    group_size_->addButton(ck_full_screen_);
//    ck_full_screen_->setChecked(true);
//
//    le_width_ = ui.le_width;
//    //le_width_->setMaximumSize(100, 50);
//
//    le_height_ = ui.le_height;
//    //le_height_->setMaximumSize(100, 50);
//
//    le_x_ = ui.le_x;
//    le_y_ = ui.le_y;
//
////    cb_dev_name_ = new QComboBox;
////    cb_dev_resolution_ = new QComboBox;
////
////    std::vector<CaptureDevice> devs;
////    if (cap_type_ == CAP_TYPE_VIDEO)
////        //devs = getVideoCaptureDevices();
////        devs = CaptureDevice::getInstance()->getVideoDevicesList();
////    else {}
////    //devs = getAudioCaptureDevices();
////
//////for (int i = 0; i < devs.size(); ++i) 
//////{
//////    cmb->addItem(devs[i].name);
//////}
////    for (auto it : devs)
////    {
////        cb_dev_name_->addItem(it.name);
////        for (auto i : it.properties_list)
////        {
////            QString str_pix_fmt;
////            for (auto fmt : ImageFormatTable)
////            {
////                if (fmt.directshowFormat == i.pixelFormat)
////                {
////                    str_pix_fmt = QString(fmt.name.c_str());
////                }
////            }
////            QString s = QString("%1x%2@%3").arg(i.width).arg(i.height).arg(str_pix_fmt);
////            cb_dev_resolution_->addItem(s);
////        }
////    }
////
////    vbox->addWidget(cb_dev_name_);
////    vbox->addStretch();
////    vbox->addWidget(cb_dev_resolution_);
//
//
//    //setLayout(vbox);
//    connectSignals();
//}
//
//void DesktopTab::connectSignals()
//{
//    //QObject::connect(ck_capture_area_, SIGNAL(stateChanged(int)), this, SLOT(onCaptureAreaChecked(int)));
//    QObject::connect(ck_full_screen_, &QCheckBox::stateChanged, this, 
//        [this] 
//        {        
//            std::stringstream stream;
//            stream << screen_rect_.x();
//            le_x_->setText(stream.str().c_str());
//            //stream.clear();
//            stream.str("");
//
//            stream << screen_rect_.y();
//            le_y_->setText(stream.str().c_str());
//            stream.str("");
//
//            stream << screen_rect_.width();
//            le_width_->setText(stream.str().c_str());
//            stream.str("");
//
//            stream << screen_rect_.height();
//            le_height_->setText(stream.str().c_str());
//            stream.str("");
//            le_x_->setDisabled(true);
//            le_y_->setDisabled(true);
//            le_width_->setDisabled(true);
//            le_height_->setDisabled(true); 
//        });
//    //QObject::connect(group_size_, SIGNAL(idClicked(int)), this, SLOT(onCaptureAreaChecked(int)));
//}
//
//void DesktopTab::onCaptureAreaChecked(int index)
////void DesktopTab::onCaptureAreaChecked()
//{
//    if (!ck_capture_area_->isChecked())
//    {
//        return;
//    }
//
//    le_x_->setDisabled(false);
//    le_y_->setDisabled(false);
//    le_width_->setDisabled(false);
//    le_height_->setDisabled(false);
//
//    ScreenCaptureDialog* dia = new ScreenCaptureDialog();
//    Qt::WindowFlags flag = dia->windowFlags();
//    dia->setWindowFlags(flag | Qt::MSWindowsFixedSizeDialogHint);
//    emit sigDeskTopTabProcessingScreenCap();
//    QObject::connect(dia, &ScreenCaptureDialog::accepted, this, [this] {qDebug() << "tab fin"; emit sigDeskTopTabProcessingScreenCapFinshed(); /*this->setVisible(true);*/ });
//    QObject::connect(dia, &ScreenCaptureDialog::rejected, this, [this] {qDebug() << "tab fin"; emit sigDeskTopTabProcessingScreenCapFinshed(); /*this->setVisible(true);*/ });
//    for (;;)
//    {
//        if (dia->exec() == QDialog::Accepted)
//        {
//            auto r = dia->getCaptureArea();
//            std::stringstream stream;
//            stream << r.x();
//            le_x_->setText(stream.str().c_str());
//            //stream.clear();
//            stream.str("");
//
//            stream << r.y();
//            le_y_->setText(stream.str().c_str());
//            stream.str("");
//
//            stream << r.width();
//            le_width_->setText(stream.str().c_str());
//            stream.str("");
//
//            stream << r.height();
//            le_height_->setText(stream.str().c_str());
//            stream.str("");
//
//            qDebug() << "rect : " << r.x() << " , " << r.y() << " , " << r.width() << " : " << r.height();
//            break;
//        }
//        else if (dia->close())
//        {
//
//            return;
//        }
//    }
//
//}
//
//DesktopTab::~DesktopTab()
//{
//    if (group_type_)
//    {
//        delete group_type_;
//    }
//
//    if (ck_dshow_)
//    {
//        delete ck_dshow_;
//    }
//
//    if (ck_dxgi_)
//    {
//        delete ck_dxgi_;
//    }
//
//    if (ck_gdi_)
//    {
//        delete ck_gdi_;
//    }
//
//    if (group_size_)
//    {
//        delete group_size_;
//    }
//
//    if (ck_full_screen_)
//    {
//        delete ck_full_screen_;
//    }
//
//    if (ck_capture_area_)
//    {
//        delete ck_capture_area_;
//    }
//}