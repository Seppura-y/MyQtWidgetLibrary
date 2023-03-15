#include "my_tabwidget.h"
#include <QLayout>
#include <QFontDatabase>
#include <QStylePainter>
#include <QStyleOptionTab>

#include "config_helper.h"


MyTabBar::MyTabBar(QWidget* a_parent) : QTabBar(a_parent)
{
    setWidth(size().width());

    int id = QFontDatabase::addApplicationFont(":/screen_capture_dialog/res/fonts/Font Awesome 6 Pro-Light-300.otf");
    if (id < 0)
    {

    }
    else
    {
        QFont font;
        QString family = QFontDatabase::applicationFontFamilies(id).first();
        font.setFamily(family);

        font.setPixelSize(16);
        font.setPointSize(16);
        this->setFont(font);
        setTabText(0, QChar(0xf1c8));
        setTabText(0, QChar(0xf1c8));
    }
}

QSize MyTabBar::tabSizeHint(int index) const
{
    QSize s = QTabBar::tabSizeHint(index);
    s.transpose();

    s.rwidth() = 90;
    s.rheight() = 50;
    return s;
    return QSize(size_.width() / (count() ? count() : 1), size().height());
}

void MyTabBar::paintEvent(QPaintEvent* ev)
{
    QStylePainter painter(this);
    QStyleOptionTab opt;

    for (int i = 0; i < count(); i++)
    {
        initStyleOption(&opt, i);
        painter.drawControl(QStyle::CE_TabBarTabShape, opt);
        painter.save();

        QSize s = opt.rect.size();
        s.transpose();
        QRect r(QPoint(), s);
        r.moveCenter(opt.rect.center());
        opt.rect = r;

        QPoint c = tabRect(i).center();
        painter.translate(c);
        painter.rotate(90);
        painter.translate(-c);
        painter.drawControl(QStyle::CE_TabBarTabLabel, opt);
        painter.restore();
    }
}

void MyTabBar::setWidth(int a_width)
{
    size_ = QSize(a_width, size().height());
    //QTabBar::resize(size_);
}

MyTabWidget::MyTabWidget(QWidget* a_parent) : QTabWidget(a_parent)
{
    tabBar_ = new MyTabBar(this);
    setTabBar(tabBar_);
    setTabPosition(QTabWidget::West);
    this->setDocumentMode(true);
    this->setStyleSheet(ConfigHelper::GetInstance()->GetQssString(":screen_capture_dialog/res/css/my_tabwidget.css"));
    //this->setLayout(new QGridLayout());
}

void MyTabWidget::resizeEvent(QResizeEvent* e)
{
    tabBar_->setWidth(size().width());
    QTabWidget::resizeEvent(e);
}