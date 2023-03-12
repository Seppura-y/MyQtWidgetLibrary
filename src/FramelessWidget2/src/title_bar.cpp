#include "title_bar.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <qt_windows.h>

#include <string>

TitleBar::TitleBar(QWidget* p):
	QWidget(p)
{
	// 窗口关闭同时释放内存，不设置就只是调用hide()，不释放内存
	this->setAttribute(Qt::WA_DeleteOnClose);

	initUI();
}

TitleBar::~TitleBar()
{
}

void TitleBar::initUI()
{
	//禁止父窗口影响子窗口样式
	setAttribute(Qt::WA_StyledBackground);
	this->setFixedHeight(32 + 5 * 2);
	this->setStyleSheet("background-color:rgb(54,54,54)");

	lab_logo_ = new QLabel(this);
	lab_logo_->setFixedSize(32, 32);
	lab_logo_->setStyleSheet(
		std::string(R"(
		background-image:url(:/frameless_widget/res/icons/title_bar/title_icon.png);
		border:none;
		)").c_str()
	);

	lab_title_ = new QLabel(this);
	lab_title_->setText("我是标题");
	lab_title_->setFixedWidth(120);
	lab_title_->setStyleSheet(
		std::string(R"(QLabel
						{
							font-family: Microsoft YaHei;
							font-size:18px;
							color:#BDC8E2;background-color:rgb(54,54,54);
						})").c_str()
	);

	pb_set_ = new QPushButton(this);
	pb_set_->setFixedSize(32, 32);
	pb_set_->setStyleSheet(
		std::string(R"(QPushButton
						{
							background-image:url(:/frameless_widget/res/icons/title_bar/set.svg);
							border:none;
						}
						QPushButton:hover
						{
							background-color:rgb(99, 99, 99);
							background-image:url(:/frameless_widget/res/icons/title_bar/set_hover.svg);
							border:none;
						})").c_str()
	);

	pb_min_ = new QPushButton(this);
	pb_min_->setFixedSize(32, 32);
	pb_min_->setStyleSheet(
		std::string(R"(QPushButton
						{
							background-image:url(:/frameless_widget/res/icons/title_bar/min.svg);
							border:none;
						}
						QPushButton:hover
						{
							background-color:rgb(99, 99, 99);
							background-image:url(:/frameless_widget/res/icons/title_bar/min_hover.svg);
							border:none;
						})").c_str()
	);

	pb_max_ = new QPushButton(this);
	pb_max_->setFixedSize(32, 32);
	pb_max_->setStyleSheet(
		std::string(R"(QPushButton
						{
							background-image:url(:/frameless_widget/res/icons/title_bar/normal.svg);
							border:none;
						}
						QPushButton:hover
						{
							background-color:rgb(99, 99, 99);
							background-image:url(:/frameless_widget/res/icons/title_bar/normal_hover.svg);
							border:none;
						})").c_str()
	);

	pb_close_ = new QPushButton(this);
	pb_close_->setFixedSize(32, 32);
	pb_close_->setStyleSheet(
		std::string(R"(QPushButton
						{
							background-image:url(:/frameless_widget/res/icons/title_bar/close.svg);
							border:none;
						}
						QPushButton:hover
						{
							background-color:rgb(99, 99, 99);
							background-image:url(:/frameless_widget/res/icons/title_bar/close_hover.svg);
							border:none;
						})").c_str()
	);

	QHBoxLayout* h_layout = new QHBoxLayout(this);
	h_layout->addWidget(lab_logo_);
	h_layout->addWidget(lab_title_);
	h_layout->addStretch();
	h_layout->addWidget(pb_set_);
	QSpacerItem* pItem1 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
	h_layout->addSpacerItem(pItem1);

	h_layout->addWidget(pb_min_);
	QSpacerItem* pItem2 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
	h_layout->addSpacerItem(pItem2);
	h_layout->addWidget(pb_max_);
	
	QSpacerItem* pItem3 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
	h_layout->addSpacerItem(pItem3);   // 弹簧每次使用时得new出来，不能重复使用
	h_layout->addWidget(pb_close_);

	h_layout->setContentsMargins(5, 5, 5, 5);

	connect(pb_min_, &QPushButton::clicked, this, &TitleBar::onClicked);
	connect(pb_max_, &QPushButton::clicked, this, &TitleBar::onClicked);
	connect(pb_close_, &QPushButton::clicked, this, &TitleBar::onClicked);
}

void TitleBar::mousePressEvent(QMouseEvent* event)
{
	if (ReleaseCapture())
	{
		QWidget* pWindow = this->window();
		if (pWindow->isTopLevel())
		{
			SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
		}
	}
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
	emit pb_max_->clicked();
}

void TitleBar::onClicked()
{
	 QPushButton* pButton = qobject_cast<QPushButton*>(sender());

	 QWidget* pWindow = this->window();

	 if (pButton == pb_min_)
	 {
		 pWindow->showMinimized();
	 }
	 else if (pButton == pb_max_)
	 {
		 if (pWindow->isMaximized())
		 {
			 pWindow->showNormal();
			 pb_max_->setStyleSheet(
				 std::string(R"(QPushButton
						{
							background-image:url(:/frameless_widget/res/icons/title_bar/normal.svg);
							border:none;
						}
						QPushButton:hover
						{
							background-color:rgb(99, 99, 99);
							background-image:url(:/frameless_widget/res/icons/title_bar/normal_hover.svg);
							border:none;
						})").c_str()
			 );
		 }
		 else
		 {
			 pWindow->showMaximized();
			 pb_max_->setStyleSheet(
				 std::string(R"(QPushButton
						{
							background-image:url(:/frameless_widget/res/icons/title_bar/max.svg);
							border:none;
						}
						QPushButton:hover
						{
							background-color:rgb(99, 99, 99);
							background-image:url(:/frameless_widget/res/icons/title_bar/max_hover.svg);
							border:none;
						})").c_str()
			 );
		 }
	 }
	 else if (pButton == pb_close_)
	 {
		 emit sigClose();
	 }
}

