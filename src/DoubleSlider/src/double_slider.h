#ifndef DOUBLE_SLIDER_H
#define DOUBLE_SLIDER_H

#include <QWidget>

namespace Ui {
class DoubleSlider;
}

class DoubleSlider : public QWidget
{
    Q_OBJECT

public:
    explicit DoubleSlider(QWidget *parent = nullptr);
    ~DoubleSlider();

    
private slots:
    void onLowerValueChanged(int value);
    void onUpperValueChanged(int value);
private:
    Ui::DoubleSlider *ui;
};

#endif // DOUBLE_SLIDER_H
