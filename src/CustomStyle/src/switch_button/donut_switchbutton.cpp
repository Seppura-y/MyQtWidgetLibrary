#include "donut_switchbutton.h"
#include "donut_switchbutton_p.h"
#include "donut_style.h"

#include <QStylePainter>
#include <QStyleOption>
#include <QDebug>


DonutSwitchButton::DonutSwitchButton(QWidget* parent)
    : QAbstractButton(parent)
{
    Q_D(DonutSwitchButton);
    //DonutSwitchButtonPrivate* const d = d_func();
    d->init();
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
    Q_Q(DonutSwitchButton);

    check = false;
    q->setObjectName("DonutSwitchButton");
    q->setChecked(true);
    q->setCheckable(true); //clicked  toggled 都需要开启
    q->connect(q, SIGNAL(clicked(bool)), q, SLOT(setChecked(bool)));
}

bool DonutSwitchButtonPrivate::switchCheck()
{
    return check;
}
