#include "scroll_area_dialog.h"

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

ScrollAreaDialog::ScrollAreaDialog(QWidget* parent)
	: DialogBase(parent)
{
	initUI();
}

ScrollAreaDialog::~ScrollAreaDialog()
{
}

QString ScrollAreaDialog::getFilePath()
{
	return QString();
}

QString ScrollAreaDialog::getFileName()
{
	return QString();
}

void ScrollAreaDialog::initUI()
{
    setFixedSize(600, 380);

    title_ = new DialogTitle();

    QPushButton* pb_ok = new QPushButton();
    QPushButton* pb_cancel = new QPushButton();
    pb_ok->setFixedSize(60, 30);
    pb_cancel->setFixedSize(60, 30);

    pb_ok->setText("ok");
    pb_cancel->setText("cancel");

    QHBoxLayout* pb_layout = new QHBoxLayout();
    QLabel* lb_empty = new QLabel();
    lb_empty->setStyleSheet("background-color: #1c1c1c;");
    lb_empty->setMinimumWidth(this->width());

    pb_layout->setSizeConstraint(QLayout::SetMaximumSize);
    pb_layout->addSpacerItem(new QSpacerItem(150, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    //pb_layout->addWidget(lb_empty, 1);
    pb_layout->addWidget(pb_ok);
    pb_layout->addWidget(pb_cancel);

    QObject::connect(pb_ok, &QPushButton::clicked, this, &QDialog::accept);
    QObject::connect(pb_cancel, &QPushButton::clicked, this, &QDialog::reject);

    auto tab = new ScrollAreaContent();
    content_widget_ = tab;

    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(0);
    vbox->addWidget(title_);
    vbox->addWidget(content_widget_, 1);
    vbox->addLayout(pb_layout, 0);
    this->setLayout(vbox);

    QObject::connect(title_, &DialogTitle::sigCloseBtnClicked, this, &QDialog::reject);


}
