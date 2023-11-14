#ifndef DONUT_SWITCHBUTTON_H
#define DONUT_SWITCHBUTTON_H

#include <QAbstractButton>
#include <QStyleOption>

class QStyleOptionButton;

class DonutSwitchButtonPrivate;
class DonutSwitchButton : public QAbstractButton
{
    Q_OBJECT

public:
    explicit DonutSwitchButton(QWidget* parent = nullptr);
    ~DonutSwitchButton();

public:
    virtual QSize sizeHint() const override;

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    void initStyleOption(QStyleOptionButton* opt) const;

    DonutSwitchButtonPrivate* d_ptr_;
    friend class DonutSwitchButtonPrivate;
};

#endif