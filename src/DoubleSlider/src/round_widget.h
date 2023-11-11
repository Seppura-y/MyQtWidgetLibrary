#ifndef ROUND_WIDGET_H
#define ROUND_WIDGET_H

#include <QWidget>

#include <QProxyStyle>
#include <QSlider>
#include <QStyleOptionSlider>
#include <QStyle>

#include <QRect>

class DonutSliderStyle : public QProxyStyle
{
public:
    DonutSliderStyle(QStyle* style = nullptr);
    DonutSliderStyle& operator=(const DonutSliderStyle& other)
    {
        if (this != &other)
        {
            rect_ = other.rect_;
        }
        return *this;
    }
protected:

    bool DonutSliderStyle::eventFilter(QObject* watched, QEvent* event) override;
    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex* opt, SubControl sc, const QWidget* widget) const override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget = nullptr) const override;
public:
    mutable QRect rect_;
    QSize handle_size_;
};

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