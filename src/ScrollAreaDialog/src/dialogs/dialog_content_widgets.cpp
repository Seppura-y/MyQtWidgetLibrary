#include "dialog_content_widgets.h"

//#include "capturer/get_device.h"
#include "screen_capture_dialog.h"
//#include "confile.h"
#include "config_helper.h"
//#include "my_tabwidget.h"

#include "scroll_area_item_base.h"


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

DialogContentBase::DialogContentBase(QWidget* parent) : QWidget(parent)
{
    this->setStyleSheet(ConfigHelper::getInstance()->getQssString(":resources/res/css/dialog_base.css"));
}

void DialogContentBase::paintEvent(QPaintEvent* ev)
{
    QStyleOption option;
    option.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
    QWidget::paintEvent(ev);
}


FileTab::FileTab(QWidget* parent) : DialogContentBase(parent)
{
    QVBoxLayout* vbox = new QVBoxLayout;
    QHBoxLayout* hbox = new QHBoxLayout;

    vbox->addStretch();
    vbox->addWidget(new QLabel("Name:"));
    le_name_ = new QLineEdit;
    le_name_->setFixedHeight(20);
    vbox->addWidget(le_name_);


    vbox->addWidget(new QLabel(tr("Path:")));
    le_path_ = new QLineEdit;
    le_path_->setFixedHeight(20);
    pb_open_ = new QPushButton("Open");
    pb_open_->setFixedSize(50, 20);
    hbox->addWidget(le_path_);
    hbox->addWidget(pb_open_);

    vbox->addLayout(hbox);
    vbox->addStretch();

    setLayout(vbox);

    connect(pb_open_, &QPushButton::clicked, this,
        [=]
        {
            QString file = QFileDialog::getOpenFileName(
                this,
                tr("Open Meida File"),
                "",
                "Video Files(*.3gp *.amv *.asf *.avi *.flv *.m2v *.m4v *.mkv *.mp2 *.mp4 *.mpg *.swf *.ts *.rmvb *.wmv) All Files(*)"
            );

            if (!file.isEmpty())
            {
                le_name_->setText(file);
                le_path_->setText(file);
                emit sigAcceptFilePath(file);
            }
        }
    );

    connect(le_name_, &QLineEdit::textChanged, [=]
        {
            emit sigAcceptFileName(le_name_->text());
        }
    );
}


CaptureTab::CaptureTab(int tab_index, QWidget* parent, capture_type type) : DialogContentBase(parent), cap_type_(type)
{
    tab_index_ = tab_index;
    //QVBoxLayout* vbox = new QVBoxLayout;

    //vbox->addStretch();
    //vbox->addWidget(new QLabel(tr("Device:")));

    //cb_dev_name_ = new QComboBox;
    //cb_dev_resolution_ = new QComboBox;

    //std::vector<CaptureDevice> devs;
    //if (cap_type_ == CAP_TYPE_VIDEO)
    //    //devs = getVideoCaptureDevices();
    //    devs = CaptureDevice::getInstance()->getVideoDevicesList();
    //else{}
    //    //devs = getAudioCaptureDevices();

    ////for (int i = 0; i < devs.size(); ++i) 
    ////{
    ////    cmb->addItem(devs[i].name);
    ////}
    //    for (auto it : devs)
    //    {
    //        cb_dev_name_->addItem(it.name);
    //        for (auto i : it.properties_list)
    //        {
    //            QString str_pix_fmt;
    //            for (auto fmt : ImageFormatTable)
    //            {
    //                if (fmt.directshowFormat == i.pixelFormat)
    //                {
    //                    str_pix_fmt = QString(fmt.name.c_str());
    //                }
    //            }
    //            QString s = QString("%1x%2@%3").arg(i.width).arg(i.height).arg(str_pix_fmt);
    //            cb_dev_resolution_->addItem(s);
    //        }
    //    }

    //vbox->addWidget(cb_dev_name_);
    //vbox->addStretch();
    //vbox->addWidget(cb_dev_resolution_);


    //setLayout(vbox);
}


DesktopTab::DesktopTab(int tab_index, QWidget* parent, capture_type type) : DialogContentBase(parent)
{
    tab_index_ = tab_index;
    ui.setupUi(this);
    this->setStyleSheet(ConfigHelper::getInstance()->getQssString(":/resources/res/css/my_tabwidget.css"));
    auto screen = QGuiApplication::primaryScreen();
    screen_rect_ = screen->geometry();

    group_type_ = new QButtonGroup(this);
    group_type_->setExclusive(true);

    ck_dxgi_ = ui.ck_dxgi;
    ck_dshow_ = ui.ck_dshow;
    ck_gdi_ = ui.ck_gdi;

    group_type_->addButton(ck_dxgi_);
    group_type_->addButton(ck_dshow_);
    group_type_->addButton(ck_gdi_);
    ck_dxgi_->setChecked(true);

    group_size_ = new QButtonGroup(this);
    group_size_->setExclusive(true);

    ck_capture_area_ = ui.ck_capture_area;
    ck_full_screen_ = ui.ck_full_screen;
    group_size_->addButton(ck_capture_area_);
    group_size_->addButton(ck_full_screen_);
    ck_full_screen_->setChecked(true);

    le_width_ = ui.le_width;
    //le_width_->setMaximumSize(100, 50);

    le_height_ = ui.le_height;
    //le_height_->setMaximumSize(100, 50);

    le_x_ = ui.le_x;
    le_y_ = ui.le_y;

    //    cb_dev_name_ = new QComboBox;
    //    cb_dev_resolution_ = new QComboBox;
    //
    //    std::vector<CaptureDevice> devs;
    //    if (cap_type_ == CAP_TYPE_VIDEO)
    //        //devs = getVideoCaptureDevices();
    //        devs = CaptureDevice::getInstance()->getVideoDevicesList();
    //    else {}
    //    //devs = getAudioCaptureDevices();
    //
    ////for (int i = 0; i < devs.size(); ++i) 
    ////{
    ////    cmb->addItem(devs[i].name);
    ////}
    //    for (auto it : devs)
    //    {
    //        cb_dev_name_->addItem(it.name);
    //        for (auto i : it.properties_list)
    //        {
    //            QString str_pix_fmt;
    //            for (auto fmt : ImageFormatTable)
    //            {
    //                if (fmt.directshowFormat == i.pixelFormat)
    //                {
    //                    str_pix_fmt = QString(fmt.name.c_str());
    //                }
    //            }
    //            QString s = QString("%1x%2@%3").arg(i.width).arg(i.height).arg(str_pix_fmt);
    //            cb_dev_resolution_->addItem(s);
    //        }
    //    }
    //
    //    vbox->addWidget(cb_dev_name_);
    //    vbox->addStretch();
    //    vbox->addWidget(cb_dev_resolution_);


        //setLayout(vbox);
    connectSignals();
    this->setStyleSheet(ConfigHelper::getInstance()->getQssString(":resources/res/css/dialog_content.css"));
}

void DesktopTab::connectSignals()
{
    QObject::connect(ck_capture_area_, SIGNAL(stateChanged(int)), this, SLOT(onCaptureAreaChecked(int)));
    QObject::connect(ck_full_screen_, &QCheckBox::stateChanged, this,
        [this]
        {
            std::stringstream stream;
            stream << screen_rect_.x();
            le_x_->setText(stream.str().c_str());
            //stream.clear();
            stream.str("");

            stream << screen_rect_.y();
            le_y_->setText(stream.str().c_str());
            stream.str("");

            stream << screen_rect_.width();
            le_width_->setText(stream.str().c_str());
            stream.str("");

            stream << screen_rect_.height();
            le_height_->setText(stream.str().c_str());
            stream.str("");
            le_x_->setDisabled(true);
            le_y_->setDisabled(true);
            le_width_->setDisabled(true);
            le_height_->setDisabled(true);
        });
    //QObject::connect(group_size_, SIGNAL(idClicked(int)), this, SLOT(onCaptureAreaChecked(int)));
}

void DesktopTab::onCaptureAreaChecked(int index)
//void DesktopTab::onCaptureAreaChecked()
{
    if (!ck_capture_area_->isChecked())
    {
        return;
    }

    le_x_->setDisabled(false);
    le_y_->setDisabled(false);
    le_width_->setDisabled(false);
    le_height_->setDisabled(false);

    ScreenCaptureDialog* dia = new ScreenCaptureDialog();
    Qt::WindowFlags flag = dia->windowFlags();
    dia->setWindowFlags(flag | Qt::MSWindowsFixedSizeDialogHint);
    emit sigDeskTopTabProcessingScreenCap();
    QObject::connect(dia, &ScreenCaptureDialog::accepted, this, [this] {qDebug() << "tab fin"; emit sigDeskTopTabProcessingScreenCapFinshed(); /*this->setVisible(true);*/ });
    QObject::connect(dia, &ScreenCaptureDialog::rejected, this, [this] {qDebug() << "tab fin"; emit sigDeskTopTabProcessingScreenCapFinshed(); /*this->setVisible(true);*/ });
    for (;;)
    {
        if (dia->exec() == QDialog::Accepted)
        {
            auto r = dia->getCaptureArea();
            std::stringstream stream;
            stream << r.x();
            le_x_->setText(stream.str().c_str());
            //stream.clear();
            stream.str("");

            stream << r.y();
            le_y_->setText(stream.str().c_str());
            stream.str("");

            stream << r.width();
            le_width_->setText(stream.str().c_str());
            stream.str("");

            stream << r.height();
            le_height_->setText(stream.str().c_str());
            stream.str("");

            qDebug() << "rect : " << r.x() << " , " << r.y() << " , " << r.width() << " : " << r.height();
            break;
        }
        else if (dia->close())
        {

            return;
        }
    }

}

DesktopTab::~DesktopTab()
{
    if (group_type_)
    {
        delete group_type_;
    }

    if (ck_dshow_)
    {
        delete ck_dshow_;
    }

    if (ck_dxgi_)
    {
        delete ck_dxgi_;
    }

    if (ck_gdi_)
    {
        delete ck_gdi_;
    }

    if (group_size_)
    {
        delete group_size_;
    }

    if (ck_full_screen_)
    {
        delete ck_full_screen_;
    }

    if (ck_capture_area_)
    {
        delete ck_capture_area_;
    }
}

ScrollAreaContent::ScrollAreaContent(QWidget* parent)
    : DialogContentBase(parent)
{
    setFixedSize(150 + 1000 + 30 + 15, 900);
    list_wid_ = new QListWidget(this);
    list_wid_->setFixedWidth(150);
    //list_wid_->setFrameShape(QFrame::NoFrame);
    list_wid_->setFocusPolicy(Qt::NoFocus);

    menu_str_list_ << u8"基本设置" << u8"云盘设置" << u8"下载设置" << u8"接管设置"
        << u8"任务管理" << u8"悬浮窗口" << u8"高级设置" << u8"12" << u8"23" << u8"445" << u8"78" << u8"12.";

    list_wid_->addItems(menu_str_list_);

    scroll_area_ = new QScrollArea(this);
    scroll_area_->setFixedWidth(1000 + 30);
    scroll_area_->setFrameShape(QFrame::NoFrame);
    //scroll_area_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    this->setStyleSheet(ConfigHelper::getInstance()->getQssString(":resources/res/css/scroll_area_widget.css"));

    setting_widget_1_ = new ScrollAreaItemBase();
    setting_widgets_.push_back(setting_widget_1_);

    setting_widget_2_ = new ScrollAreaItemBase();
    setting_widgets_.push_back(setting_widget_2_);

    setting_widget_3_ = new ScrollAreaItemBase();
    setting_widgets_.push_back(setting_widget_3_);

    setting_widget_4_ = new ScrollAreaItemBase();
    setting_widgets_.push_back(setting_widget_4_);

    setting_widget_5_ = new ScrollAreaItemBase();
    setting_widgets_.push_back(setting_widget_5_);

    setting_widget_6_ = new ScrollAreaItemBase();
    setting_widgets_.push_back(setting_widget_6_);


    QWidget* widget = new QWidget();
    QVBoxLayout* v_layout = new QVBoxLayout(widget);
    for (auto wid : setting_widgets_)
    {
        v_layout->addWidget(wid);
        v_layout->addSpacing(10);
    }
    v_layout->setContentsMargins(0, 5, 0, 5);
    scroll_area_->setWidget(widget);

    QHBoxLayout* h_layout = new QHBoxLayout(this);
    h_layout->addWidget(list_wid_);
    h_layout->setSpacing(1);
    h_layout->addWidget(scroll_area_);

    QObject::connect(list_wid_, &QListWidget::itemClicked, this, &ScrollAreaContent::onListItemClicked);
    QObject::connect(scroll_area_->verticalScrollBar(), &QScrollBar::valueChanged, this, &ScrollAreaContent::onScrollValueChanged);

}

void ScrollAreaContent::onListItemClicked(QListWidgetItem* item)
{
    is_item_clicked_ = true;
    QString item_text = item->text();
    QPoint widget_pos;
    int size = menu_str_list_.size();
    for (int i = 0; i < size; i++)
    {
        if (item_text == menu_str_list_[i])
        {
            widget_pos = setting_widgets_[i]->pos();
        }
    }
    scroll_area_->verticalScrollBar()->setValue(widget_pos.y());
}


void ScrollAreaContent::onScrollValueChanged(int value)
{
    if (!is_item_clicked_)
    {
        int size = setting_widgets_.size();
        for (int i = 0; i < size; i++)
        {
            if (!setting_widgets_[i]->visibleRegion().isEmpty())
            {
                list_wid_->item(i)->setSelected(true);
                return;
            }
            else
            {
                list_wid_->item(i)->setSelected(false);
            }
        }
    }

    is_item_clicked_ = false;
}