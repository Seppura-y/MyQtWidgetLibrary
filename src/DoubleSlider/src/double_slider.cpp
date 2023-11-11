#include "double_slider.h"
#include "ui_double_slider.h"
#include "config_helper.h"

DoubleSlider::DoubleSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoubleSlider)
{
    ui->setupUi(this);
    QString s = ConfigHelper::GetQssString(":/resources/res/css/slider.css");
    //ui->db_slider->setStyleSheet(s);
    ui->db_slider->setHandleMovementMode(QxtSpanSlider::NoOverlapping);

    ui->db_slider->setRange(0, 100);
    ui->db_slider->setLowerValue(0);
    ui->db_slider->setUpperValue(100);

    QObject::connect(ui->db_slider, SIGNAL(lowerValueChanged(int)), this, SLOT(onLowerValueChanged(int)));
    QObject::connect(ui->db_slider, SIGNAL(upperValueChanged(int)), this, SLOT(onUpperValueChanged(int)));
}

DoubleSlider::~DoubleSlider()
{
    delete ui;
}

void DoubleSlider::onLowerValueChanged(int value)
{
    ui->le_left->setText(QString::number(value));
}

void DoubleSlider::onUpperValueChanged(int value)
{
    ui->le_left->setText(QString::number(value));
}
