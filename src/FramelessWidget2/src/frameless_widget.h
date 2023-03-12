#ifndef FRAMELESS_WIDGET_H
#define FRAMELESS_WIDGET_H

#include <QWidget>

class FramelessWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FramelessWidget(QWidget *parent = nullptr);
    ~FramelessWidget();

protected:
    bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
private:

private:
    int border_width_ = 5;
};

#endif // FRAMELESS_WIDGET_H
