#include "scroll_area_item_base.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>

ScrollAreaItemBase::ScrollAreaItemBase(QWidget* parent)
	: QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_StyledBackground);
	this->setStyleSheet("background-color:rgb(51, 51, 51);color:rgb(200,200,200);");

	QLabel* lab_base_set = new QLabel(this);
	lab_base_set->setText(u8"基本设置");

	QCheckBox* ckb_start_with_win = new QCheckBox(this);
	ckb_start_with_win->setText(u8"开机启动");
	std::string s = R"(
		QCheckBox::indicator:checked { color: red; }
		QCheckBox::indicator:checked:hover { color: darkred; }
		QCheckBox::indicator:unchecked { background-color: lightgray; }
		QCheckBox::indicator:unchecked:hover { background-color: gray; }
	)";

	//std::string s = R"(
	//QCheckBox::indicator:checked {
	//	color: orange;
	//})";
	ckb_start_with_win->setStyleSheet(QString(s.c_str()));

	QCheckBox* ckb_no_disturb = new QCheckBox(this);
	ckb_no_disturb->setFixedWidth(140);
	ckb_no_disturb->setText(u8"开启免打扰模式");

	QLabel* lb_1 = new QLabel(this);
	lb_1->setText("?");

	QCheckBox* ckb_boss_key = new QCheckBox(this);
	ckb_boss_key->setFixedWidth(105);
	ckb_boss_key->setText(u8"开启老板键");

	QLineEdit* le_1 = new QLineEdit(this);
	le_1->setFixedWidth(100);
	le_1->setStyleSheet("border-style:solid;border-width:1px;border-color:rgb(79,79,79);");
	QLabel* lb_2 = new QLabel(this);
	lb_2->setText("?");

	QCheckBox* ckb_show_main = new QCheckBox(this);
	ckb_show_main->setText(u8"新建时显示主界面");

	QLabel* lb_download_mode = new QLabel(this);
	lb_download_mode->setText(u8"下载模式");

	QRadioButton* rb_max_speed = new QRadioButton(this);
	rb_max_speed->setText(u8"全速下载");

	QRadioButton* rb_limmit_speed = new QRadioButton(this);
	rb_limmit_speed->setText(u8"限速下载");
	rb_limmit_speed->setFixedWidth(90);

	QPushButton* pb_setting = new QPushButton(this);
	pb_setting->setText(u8"修改设置");
	pb_setting->setStyleSheet("background-color:#1A1A1A;color:#5F5F5F");

	QLabel* lb_cfginfo = new QLabel(this);
	lb_cfginfo->setText(u8"限制时间段: 00:00-23:59 最大下载速度:不限速");

	QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addWidget(lab_base_set);
	main_layout->addSpacing(20);

	QHBoxLayout* h_layout_1 = new QHBoxLayout();
	h_layout_1->addSpacing(35);

	QVBoxLayout* v_layout_1 = new QVBoxLayout();
	v_layout_1->addWidget(ckb_start_with_win);
	v_layout_1->addSpacing(20);

	QHBoxLayout* h_layout_2 = new QHBoxLayout;
	h_layout_2->addWidget(ckb_no_disturb);
	h_layout_2->addWidget(lb_1);

	v_layout_1->addLayout(h_layout_2);  // 添加免打扰的水平布局
	v_layout_1->addSpacing(20);

	QHBoxLayout* h_layout_3 = new QHBoxLayout;
	h_layout_3->addWidget(ckb_boss_key);
	h_layout_3->addWidget(le_1);
	h_layout_3->addWidget(lb_2);

	v_layout_1->addLayout(h_layout_3);
	v_layout_1->addSpacing(20);

	v_layout_1->addWidget(ckb_show_main);
	v_layout_1->addSpacing(20);

	v_layout_1->addWidget(lb_download_mode);  // 下载模式
	v_layout_1->addSpacing(20);

	QHBoxLayout* h_layout_4 = new QHBoxLayout;  //  下载模式下面的水平布局
	h_layout_4->addSpacing(30);

	QVBoxLayout* v_layout_2 = new QVBoxLayout();

	QHBoxLayout* h_layout_5 = new QHBoxLayout;
	h_layout_5->addWidget(rb_max_speed);
	h_layout_5->addWidget(lb_2);
	v_layout_2->addLayout(h_layout_5);
	v_layout_2->addSpacing(20);

	// 限速下载
	QHBoxLayout* h_layout_6 = new QHBoxLayout;
	h_layout_6->addWidget(rb_limmit_speed);
	h_layout_6->addWidget(pb_setting);
	h_layout_6->addWidget(lb_cfginfo);
	h_layout_6->addStretch();

	v_layout_2->addLayout(h_layout_6);

	h_layout_4->addLayout(v_layout_2);

	v_layout_1->addLayout(h_layout_4);
	h_layout_1->addLayout(v_layout_1);

	main_layout->addLayout(h_layout_1);
	main_layout->setContentsMargins(20, 20, 20, 20);
}

ScrollAreaItemBase::~ScrollAreaItemBase()
{
}
