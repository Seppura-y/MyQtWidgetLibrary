#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
#include "title_bar.h"
#include "frameless_widget.h"

class MainWidget : public FramelessWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = Q_NULLPTR);

private slots:
    void onClose();

private:
    void initUI();

private:
    TitleBar* title_bar_ = nullptr;
};


#endif