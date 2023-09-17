#ifndef ROUND_WIDGET_H
#define ROUND_WIDGET_H

#include <QWidget>

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

};

#endif