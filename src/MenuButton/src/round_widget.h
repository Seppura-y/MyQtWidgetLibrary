#ifndef ROUND_WIDGET_H
#define ROUND_WIDGET_H

#include <QWidget>

#include "menu_button.h"

class RoundWidget : public QWidget
{
    Q_OBJECT

public:
    RoundWidget();
    ~RoundWidget();
protected:
    void paintEvent(QPaintEvent* ev) override;

private:
    void initUI();

private:
    MenuButton* menu_button_ = nullptr;
};

#endif