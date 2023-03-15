#pragma once
#include <QTabWidget>
#include <QTabBar>

class MyTabBar : public QTabBar
{
public:
    MyTabBar(QWidget* a_parent);
    void setWidth(int a_width);
protected:
    QSize tabSizeHint(int index) const  override;
    void paintEvent(QPaintEvent* ev) override;
private:
    QSize size_;
};


class MyTabWidget : public QTabWidget
{
	Q_OBJECT

public:
    MyTabWidget(QWidget* a_parent = nullptr);

    void resizeEvent(QResizeEvent* e) override;
protected:

private:
    MyTabBar* tabBar_ = nullptr;

};

