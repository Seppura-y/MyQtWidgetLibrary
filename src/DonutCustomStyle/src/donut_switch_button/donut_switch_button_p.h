#ifndef DONUT_SWITCH_BUTTON_P_H
#define DONUT_SWITCH_BUTTON_P_H

#include <QObject>
#include <QStyle>


QT_FORWARD_DECLARE_CLASS(QStylePainter)
QT_FORWARD_DECLARE_CLASS(QStyleOptionSlider)
QT_FORWARD_DECLARE_CLASS(DonutSwitchButton)

class DonutSwitchButtonPrivate : public QObject
{
    Q_OBJECT

public:
    explicit DonutSwitchButtonPrivate();
    ~DonutSwitchButtonPrivate();

    void init();
    bool setSwitchCheck(bool check);
    bool switchCheck();

private:
    bool is_checked_;

public:
    DonutSwitchButton* q_ptr_;
    friend class DonutSwitchButton;

};

#endif
