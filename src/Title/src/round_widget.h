#ifndef ROUND_WIDGET_H
#define ROUND_WIDGET_H

#include <QWidget>
#include "title.h"

class RoundWidget : public QWidget
{
    Q_OBJECT

public:
    RoundWidget(QWidget* parent = nullptr);
    ~RoundWidget();
protected:
    void paintEvent(QPaintEvent* ev) override;

private:
    void initUI();

private:
    Title* title_ = nullptr;
};

#endif