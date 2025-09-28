#include "display_widget.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QFontDatabase>
#include <QSpacerItem>
#include <QDebug>
#include <QButtonGroup>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QJsonObject>
#include <QJsonDocument>
#include <QEvent>

#include <QOpenGLWidget>


#include "config_helper.h"
//#include "camera_menu.h"
//#include "item_listwidget.h"

DisplayWidget::DisplayWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//this->setAcceptDrops(true);

	initToolBar();
	initTitle();
	initContent();

	this->setStyleSheet(ConfigHelper::GetQssString(":/resources/res/css/display_widget.css"));
}

DisplayWidget::~DisplayWidget()
{

	// if (canvas_scene_)
	// {
	// 	delete canvas_scene_;
	// 	canvas_scene_ = nullptr;
	// }

	// if (canvas_view_)
	// {
	// 	delete canvas_view_;
	// 	canvas_view_ = nullptr;
	// }
}

void DisplayWidget::resizeEvent(QResizeEvent* ev)
{
	QWidget::resizeEvent(ev);
	//canvas_view_->setGeometry(0, 0, this->width(), this->height());
	//ui.wid_content->setGeometry(0, 0, this->width(), this->height());
}


void DisplayWidget::initTitle()
{
	int id = QFontDatabase::addApplicationFont(":/resources/res/fonts/Font Awesome 6 Pro-Light-300.otf");
	if (id < 0)
		qWarning() << "FontAwesome cannot be loaded !";

	QFont font;
	QString family = QFontDatabase::applicationFontFamilies(id).first();
	font.setFamily(family);

	font.setPixelSize(16);
	font.setPointSize(16);

	layout_title_ = new QHBoxLayout;
	btn_screen_cap_ = new QPushButton;
	btn_cam_cap_ = new QPushButton;
	btn_web_cam_ = new QPushButton;
	btn_group_title_ = new QButtonGroup(this);

	//std::shared_ptr<QSpacerItem> hor_spacer1 = std::make_shared<QSpacerItem>(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);
	QSpacerItem* hor_spacer1 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);
	QSpacerItem* hor_spacer2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

	layout_title_->setMargin(0);
	layout_title_->setSpacing(5);

	btn_screen_cap_->setCheckable(true);
	btn_screen_cap_->setFont(font);
	btn_screen_cap_->setText(QChar(0xe163));
	btn_screen_cap_->setFixedSize(28, 28);
	btn_screen_cap_->setCursor(QCursor(Qt::PointingHandCursor));

	font.setPointSize(16);
	btn_cam_cap_->setCheckable(true);
	btn_cam_cap_->setFont(font);
	btn_cam_cap_->setText(QChar(0xf030));
	btn_cam_cap_->setFixedSize(28, 28);
	btn_cam_cap_->setCursor(QCursor(Qt::PointingHandCursor));

	btn_web_cam_->setCheckable(true);
	btn_web_cam_->setFont(font);
	btn_web_cam_->setText(QChar(0xf03d));
	btn_web_cam_->setFixedSize(28, 28);
	btn_web_cam_->setCursor(QCursor(Qt::PointingHandCursor));

	layout_title_->addSpacerItem(hor_spacer1);
	layout_title_->addWidget(btn_screen_cap_);
	layout_title_->addWidget(btn_cam_cap_);
	layout_title_->addWidget(btn_web_cam_);
	layout_title_->addSpacerItem(hor_spacer2);

	btn_group_title_->addButton(btn_screen_cap_);
	btn_group_title_->addButton(btn_cam_cap_);
	btn_group_title_->addButton(btn_web_cam_);

	ui.wid_title->setLayout(layout_title_);

	connect(btn_group_title_, SIGNAL(buttonToggled(QAbstractButton*, bool)), this, SLOT(onTitleButtonToggled(QAbstractButton*, bool)));

	btn_screen_cap_->setChecked(true);
}

void DisplayWidget::initContent()
{
	QHBoxLayout* layout = new QHBoxLayout;
	//QWidget* widget = new QWidget;
	////widget->setStyleSheet("background-color: green");
	//layout->setContentsMargins(0, 0, 0, 0);
	//layout->addWidget(widget);
	//ui.wid_content->setLayout(layout);

	//canvas_wid_ = new CanvasWidget();
	//layout->setContentsMargins(0, 0, 0, 0);
	//layout->addWidget(canvas_wid_);
	//ui.wid_content->setLayout(layout);

	// canvas_scene_ = new CanvasScene(ui.wid_content, 0);
	// canvas_view_ = new CanvasView(canvas_scene_, ui.wid_content);

	// canvas_view_->viewport()->installEventFilter(this);
	// //canvas_view_->installEventFilter(this);

	// layout->setContentsMargins(0, 0, 0, 0);
	// layout->addWidget(canvas_view_);
	ui.wid_content->setLayout(layout);
}

void DisplayWidget::initToolBar()
{
	int id = QFontDatabase::addApplicationFont(":/resources/res/fonts/Font Awesome 6 Pro-Light-300.otf");
	if (id < 0)
		qWarning() << "FontAwesome cannot be loaded !";

	QFont font;
	QString family = QFontDatabase::applicationFontFamilies(id).first();
	font.setFamily(family);

	font.setPixelSize(16);
	font.setPointSize(16);

	layout_toolbar_ = new QHBoxLayout;
	btn_split_1_ = new QPushButton;
	btn_split_4_ = new QPushButton;
	btn_split_9_ = new QPushButton;
	btn_split_16_ = new QPushButton;
	btn_split_25_ = new QPushButton;
	btn_split_custom_ = new QPushButton;

	btn_start_push_ = new QPushButton;
	btn_push_setting_ = new QPushButton;
	btn_push_info_ = new QPushButton;

	btn_add_source_ = new QPushButton;

	QPushButton* seperator = new QPushButton;
	btn_group_toolbar_ = new QButtonGroup(this);
	QSpacerItem* hor_spacer1 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);
	QSpacerItem* hor_spacer2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

	layout_toolbar_->setContentsMargins(0, 0, 10, 0);
	layout_toolbar_->setMargin(0);
	layout_toolbar_->setSpacing(0);

	btn_split_1_->setCheckable(true);
	btn_split_1_->setFont(font);
	btn_split_1_->setText(QChar(0x23f9));
	btn_split_1_->setFixedSize(28, 28);
	btn_split_1_->setCursor(QCursor(Qt::PointingHandCursor));
	btn_split_1_->setToolTip(QString::fromLocal8Bit("1x1视图"));

	btn_split_4_->setCheckable(true);
	btn_split_4_->setFont(font);
	btn_split_4_->setText(QChar(0xe196));
	btn_split_4_->setFixedSize(28, 28);
	btn_split_4_->setCursor(QCursor(Qt::PointingHandCursor));
	btn_split_4_->setToolTip(QString::fromLocal8Bit("4x4视图"));

	btn_split_9_->setCheckable(true);
	btn_split_9_->setFont(font);
	btn_split_9_->setText(QChar(0xe195));
	btn_split_9_->setFixedSize(28, 28);
	btn_split_9_->setCursor(QCursor(Qt::PointingHandCursor));
	btn_split_9_->setToolTip(QString::fromLocal8Bit("9x9视图"));

	btn_split_16_->setCheckable(true);
	btn_split_16_->setFont(font);
	btn_split_16_->setText(QChar(0xe198));
	btn_split_16_->setFixedSize(28, 28);
	btn_split_16_->setCursor(QCursor(Qt::PointingHandCursor));
	btn_split_16_->setToolTip(QString::fromLocal8Bit("16x16视图"));

	btn_split_25_->setCheckable(true);
	btn_split_25_->setFont(font);
	btn_split_25_->setText(QChar(0xe199));
	btn_split_25_->setFixedSize(28, 28);
	btn_split_25_->setCursor(QCursor(Qt::PointingHandCursor));
	btn_split_25_->setToolTip(QString::fromLocal8Bit("25x25视图"));

	btn_split_custom_->setCheckable(true);
	btn_split_custom_->setFont(font);
	btn_split_custom_->setText(QChar(0xe3c1));
	btn_split_custom_->setFixedSize(28, 28);
	btn_split_custom_->setCursor(QCursor(Qt::PointingHandCursor));
	btn_split_custom_->setToolTip(QString::fromLocal8Bit("自定义视图"));

	seperator->setEnabled(false);
	seperator->setMinimumWidth(20);
	seperator->setMaximumWidth(20);
	seperator->setFont(font);
	seperator ->setText(QChar(0x007c));
	seperator->setStyleSheet("color:dimgray");

	btn_start_push_->setCheckable(true);
	btn_start_push_->setFont(font);
	btn_start_push_->setText(QChar(0x25b6));
	btn_start_push_->setFixedSize(28, 28);
	btn_start_push_->setCursor(QCursor(Qt::PointingHandCursor));
	connect(btn_start_push_, &QPushButton::clicked, this, 
		[&] 
		{
			if (btn_start_push_->isChecked())
			{
				btn_start_push_->setText(QChar(0x23f9));
			}
			else
			{
				btn_start_push_->setText(QChar(0x25b6));
			}
		}
	);
	
	btn_push_setting_->setFont(font);
	btn_push_setting_->setText(QChar(0x2699));
	btn_push_setting_->setFixedSize(28, 28);
	btn_push_setting_->setCursor(QCursor(Qt::PointingHandCursor));

	btn_push_info_->setFont(font);
	btn_push_info_->setText(QChar(0xf05a));
	btn_push_info_->setFixedSize(28, 28);
	btn_push_info_->setCursor(QCursor(Qt::PointingHandCursor));

	//font.setPixelSize(12);
	//font.setPointSize(12);
	btn_add_source_->setFont(font);
	btn_add_source_->setText(QChar(0xe59e));
	btn_add_source_->setFixedSize(28, 28);
	btn_add_source_->setCursor(QCursor(Qt::PointingHandCursor));
	btn_add_source_->setToolTip(QString::fromLocal8Bit("添加捕获源"));

	layout_toolbar_->addSpacerItem(hor_spacer1);
	layout_toolbar_->addWidget(btn_split_1_);
	layout_toolbar_->addWidget(btn_split_4_);
	layout_toolbar_->addWidget(btn_split_9_);
	layout_toolbar_->addWidget(btn_split_16_);
	layout_toolbar_->addWidget(btn_split_25_);
	layout_toolbar_->addWidget(btn_split_custom_);
	layout_toolbar_->addWidget(seperator);

	layout_toolbar_->addWidget(btn_start_push_);
	layout_toolbar_->addWidget(btn_push_setting_);
	layout_toolbar_->addWidget(btn_push_info_);
	layout_toolbar_->addWidget(btn_add_source_);
	layout_toolbar_->addSpacerItem(hor_spacer2);

	btn_group_toolbar_->addButton(btn_split_1_);
	btn_group_toolbar_->addButton(btn_split_4_);
	btn_group_toolbar_->addButton(btn_split_9_);
	btn_group_toolbar_->addButton(btn_split_16_);
	btn_group_toolbar_->addButton(btn_split_25_);
	btn_group_toolbar_->addButton(btn_split_custom_);

	ui.wid_toolbar->setLayout(layout_toolbar_);

	connect(btn_group_toolbar_, SIGNAL(buttonToggled(QAbstractButton*, bool)), this, SLOT(onToolBarButtonToggled(QAbstractButton*, bool)));

	btn_split_1_->setChecked(true);
	//last_split_id_ = btn_group_toolbar_->checkedId();
}

void DisplayWidget::onPanelChanged(bool is_checked)
{

}

void DisplayWidget::onTitleButtonToggled(QAbstractButton* bt, bool checked)
{

	if (dynamic_cast<QPushButton*>(bt) == btn_screen_cap_ || dynamic_cast<QPushButton*>(bt) == btn_cam_cap_)
	{
		if (checked)
		{
			btn_split_1_->setEnabled(false);
			btn_split_4_->setEnabled(false);
			btn_split_9_->setEnabled(false);
			btn_split_16_->setEnabled(false);
			btn_split_25_->setEnabled(false);
			btn_split_custom_->setEnabled(false);

			btn_group_toolbar_->button(last_split_id_)->setChecked(false);
			btn_group_toolbar_->button(last_split_id_)->repaint();

			btn_start_push_->setEnabled(true);
			btn_push_setting_->setEnabled(true);
			btn_push_info_->setEnabled(true);
		}
	}
	else if (dynamic_cast<QPushButton*>(bt) == btn_web_cam_)
	{
		if (checked)
		{
			btn_split_1_->setEnabled(true);
			btn_split_4_->setEnabled(true);
			btn_split_9_->setEnabled(true);
			btn_split_16_->setEnabled(true);
			btn_split_25_->setEnabled(true);
			btn_split_custom_->setEnabled(true);

			btn_group_toolbar_->button(last_split_id_)->setChecked(true);

			btn_start_push_->setEnabled(false);
			btn_push_setting_->setEnabled(false);
			btn_push_info_->setEnabled(false);
		}
	}
	else
	{

	}
}

void DisplayWidget::onToolBarButtonToggled(QAbstractButton* bt, bool checked)
{
	last_split_id_ = btn_group_toolbar_->checkedId();
}

bool DisplayWidget::eventFilter(QObject* watched, QEvent* event)
{
	// CanvasView* window = qobject_cast<CanvasView*>(watched);
	// if (window == nullptr)
	// 	return false;
	//qDebug() << event->type();
	switch (event->type())
	{
		case QEvent::Drop:
		{
			this->dropEvent((QDropEvent*)event);
			return true;
			break;
		}
		case QEvent::DragEnter:
		{
			this->dragEnterEvent((QDragEnterEvent*)event);
			return true;
		}
		case QEvent::MouseButtonPress:
		{
			qDebug() << "mouse button press";
			return true;
		}
		case QEvent::MouseMove:
		{
			qDebug() << "mouse move";
			return true;
		}
		default:
		{
			return false;
		}
	}
}

void DisplayWidget::dragEnterEvent(QDragEnterEvent* ev)
{
	ev->acceptProposedAction();
}

void DisplayWidget::dropEvent(QDropEvent* ev)
{
	//int itemIndex = ((ItemListWidget*)ev->source())->currentIndex().row();
	//CameraMenu::ItemListType itemType = (CameraMenu::ItemListType)((ItemListWidget*)ev->source())->item_type_;

	QByteArray arr = ev->mimeData()->data("application/json");
	qDebug() << arr;
	QJsonParseError err;
	QJsonDocument doc(QJsonDocument::fromJson(arr, &err));
	QJsonObject obj = doc.object();

	QString name = obj.find("name").value().toString();
	qDebug() << "get name : " << name;

	//this->name_ = obj.find("name").value().toString();
	//this->url_ = obj.find("url").value().toString();
	//this->sub_url_ = obj.find("sub_url").value().toString();
	//this->server_url_ = obj.find("server_url").value().toString();
	//this->item_type_ = itemType;

	//emit SigConfigAndStartHandler();


	ev->setDropAction(Qt::MoveAction);
	ev->accept();
}