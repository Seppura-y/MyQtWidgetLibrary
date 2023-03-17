#include "volume_slider_dialog.h"
#include <QVBoxLayout>
#include <QEvent>
#include <windows.h>

#include "config_helper.h"

//#pragma comment(lib, "user32.lib")

VolumeSliderDialog::VolumeSliderDialog(QWidget* parent)
	: QDialog(parent)
{
	this->setFixedSize(40, 200);
    this->setAttribute(Qt::WA_TranslucentBackground);

	QVBoxLayout* v_layout = new QVBoxLayout(this);
	slider_ = new QSlider(this);
	slider_->setOrientation(Qt::Vertical);
    slider_->setStyleSheet(ConfigHelper::GetInstance()->GetQssString(":resources/res/css/volume_button.css"));
    v_layout->addWidget(slider_);

	setFixedSize(40, 120);
    setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip); // Qt::ToolTip Ðü¸¡ÏÔÊ¾Ð§¹û
    setStyleSheet("QDialog{background-color: rgba(54, 54, 54, 0.5);}");


	connect(slider_, &QSlider::sliderMoved,
        [=](int value)
        {
		    emit sigSliderValueChanged(value);
		}
    );

    connect(slider_, &QSlider::sliderPressed,
        [=]()
        {
            emit sigSliderValueChanged(slider_->value());
        }
    );

}

VolumeSliderDialog::~VolumeSliderDialog()
{
}


bool VolumeSliderDialog::event(QEvent* event)
{
    static bool class_amended = false;

    if (event->type() == QEvent::WinIdChange)
    {
        HWND hwnd = (HWND)winId();

        if (class_amended == false)
        {
            class_amended = true;
            DWORD class_style = ::GetClassLong(hwnd, GCL_STYLE);
            class_style &= ~CS_DROPSHADOW;
            ::SetClassLong(hwnd, GCL_STYLE, class_style);
        }
    }

	return QWidget::event(event);
}
