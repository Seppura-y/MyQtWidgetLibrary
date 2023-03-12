#pragma once
#include <QTabWidget>
#include <QTabBar>
#include <QLayout>
#include <QFontDatabase>
#include <QDebug>

class MyTabBar : public QTabBar
{
public:
    MyTabBar(QWidget* a_parent) : QTabBar(a_parent)
    {
        setWidth(size().width());

        int id = QFontDatabase::addApplicationFont(":/MediaManager/res/Font Awesome 6 Pro-Light-300.otf");
        if (id < 0)
            qWarning() << "FontAwesome cannot be loaded !";

        QFont font;
        QString family = QFontDatabase::applicationFontFamilies(id).first();
        font.setFamily(family);

        font.setPixelSize(16);
        font.setPointSize(16);
        this->setFont(font);
        //setTabText(0, QChar(0xf1c8));
        //setTabText(0, QChar(0xf1c8));
    }
    QSize tabSizeHint(int index) const  override
    {
        return QSize(size_.width() / (count() ? count() : 1), size().height());
    }
    void setWidth(int a_width)
    {
        size_ = QSize(a_width, size().height());
        QTabBar::resize(size_);
    }
protected:

private:
    QSize size_;
};


class MyTabWidget : public QTabWidget
{
	Q_OBJECT

public:
    MyTabWidget(QWidget* a_parent) : QTabWidget(a_parent)
    {
        setTabBar(tabBar_);
        this->setDocumentMode(true);
    }

    void resizeEvent(QResizeEvent* e) override
    {
        tabBar_->setWidth(size().width());
        QTabWidget::resizeEvent(e);
    }
protected:

private:
    MyTabBar* tabBar_ = new MyTabBar(this);

};

