#include "screen_scroll_area.h"
#include <QAction>
#include <QDebug>
#include <QScrollBar>
ScreenScrollArea::ScreenScrollArea(QWidget* parent) : QScrollArea(parent)
{
    QAction* act = this->menu_.addAction(QString::fromLocal8Bit("merge"));
    QObject::connect(act, SIGNAL(triggered()), this, SLOT(emit_merge()));

    act = this->menu_.addAction(QString::fromLocal8Bit("split"));
    QObject::connect(act, SIGNAL(triggered()), this, SLOT(emit_split()));

    act = this->menu_.addAction(QString::fromLocal8Bit("clear"));
    QObject::connect(act, SIGNAL(triggered()), this, SLOT(emit_clear()));

    act = this->menu_.addAction(QString::fromLocal8Bit("save"));
    QObject::connect(act, SIGNAL(triggered()), this, SLOT(emit_save()));

    act = this->menu_.addAction(QString::fromLocal8Bit("load"));
    QObject::connect(act, SIGNAL(triggered()), this, SLOT(emit_load()));

    act = this->menu_.addAction(QString::fromLocal8Bit("send"));
    QObject::connect(act, SIGNAL(triggered()), this, SLOT(emit_sndfile()));

    act = this->menu_.addAction(QString::fromLocal8Bit("set ip"));
    QObject::connect(act, SIGNAL(triggered()), this, SLOT(emit_setaddr()));

    act = this->menu_.addAction(QString::fromLocal8Bit("reset svr"));
    QObject::connect(act, SIGNAL(triggered()), this, SLOT(emit_rstsvr()));
}

void ScreenScrollArea::contextMenuEvent(QContextMenuEvent* ev)
{
    this->menu_.exec(QCursor::pos());
    ev->accept();
}

void ScreenScrollArea::emit_merge()
{
    emit merge();
}

void ScreenScrollArea::emit_split()
{
    emit split();
}

void ScreenScrollArea::emit_clear()
{
    emit clear();
}

void ScreenScrollArea::emit_save()
{
    emit save();
}
void ScreenScrollArea::emit_load()
{
    emit load();
}
void ScreenScrollArea::emit_rstsvr()
{
    emit rstsvr();
}

void ScreenScrollArea::emit_sndfile()
{
    emit sndfile();
}

void ScreenScrollArea::emit_setaddr()
{
    emit setaddr();
}

void ScreenScrollArea::set_merge_enable(bool en)
{
    menu_.actions().at(0)->setEnabled(en);
}

void ScreenScrollArea::set_split_enable(bool en)
{
    menu_.actions().at(1)->setEnabled(en);
}

int ScreenScrollArea::get_horizontal_scrollbar_height()
{
    return this->horizontalScrollBar()->height();
}
