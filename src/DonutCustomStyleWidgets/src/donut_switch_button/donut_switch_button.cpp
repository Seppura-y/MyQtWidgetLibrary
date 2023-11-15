#include "donut_switch_button.h"
#include "donut_switch_button_p.h"

#include "donut_style.h"
#include "donut_style_painter.h"

#include <QStylePainter>
#include <QStyleOption>
#include <QDebug>


DonutSwitchButton::DonutSwitchButton(QWidget* parent)
    : QAbstractButton(parent), d_ptr_(new DonutSwitchButtonPrivate)
{
    d_ptr_->q_ptr_ = this;
    d_ptr_->init();
    setStyle(new DonutStyle);
}

DonutSwitchButton::~DonutSwitchButton()
{

}

QSize DonutSwitchButton::sizeHint() const
{
    return QSize(60, 40);
}

void DonutSwitchButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QStyleOptionButton opt;
    initStyleOption(&opt);

    DonutStylePainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawControl(DonutStyle::CE_SwitchButton, &opt);
}

void DonutSwitchButton::initStyleOption(QStyleOptionButton* opt) const
{
    if (!opt)
        return;

    opt->init(this);
    opt->initFrom(this);

    if (isChecked())
        opt->state |= QStyle::State_On;
    else
        opt->state |= QStyle::State_Off;
}

DonutSwitchButtonPrivate::DonutSwitchButtonPrivate()
{
}

DonutSwitchButtonPrivate::~DonutSwitchButtonPrivate()
{
}

void DonutSwitchButtonPrivate::init()
{
    is_checked_ = false;
    q_ptr_->setObjectName("DonutSwitchButton");
    q_ptr_->setChecked(true);
    q_ptr_->setCheckable(true); //clicked  toggled 都需要开启
    q_ptr_->connect(q_ptr_, SIGNAL(clicked(bool)), q_ptr_, SLOT(setChecked(bool)));
}

bool DonutSwitchButtonPrivate::switchCheck()
{
    return is_checked_;
}
