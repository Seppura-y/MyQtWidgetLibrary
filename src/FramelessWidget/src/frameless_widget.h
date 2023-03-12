#ifndef FRAMELESS_WIDGET_H
#define FRAMELESS_WIDGET_H

#include <QWidget>

namespace Ui {
class FramelessWidget;
}

class Title;

class FramelessWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FramelessWidget(QWidget *parent = nullptr);
    ~FramelessWidget();

signals:
    void sigWindowMaximized();
    void sigWindowNormal();

private:
    void initUi();
    void initTitle();
private:
    Ui::FramelessWidget *ui;
    Title* title_;

    bool maximized_flag_ = false;
    bool is_maximized_init_ = false;
    QRect maximized_rect_;
    QRect normal_rect_;
};

#endif // FRAMELESS_WIDGET_H
