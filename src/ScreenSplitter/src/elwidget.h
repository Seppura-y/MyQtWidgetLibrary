#ifndef ELWIDGET_H
#define ELWIDGET_H

#include <QObject>
#include <QWidget>
#include <QMenu>
#include <QContextMenuEvent>
#include <QPaintEvent>

#include "screen_configuration.h"
class ElWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ElWidget(int row, int colum, int w = 1, int h = 1, QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* ev) override;
    void mousePressEvent(QMouseEvent* ev) override;
    void dragEnterEvent(QDragEnterEvent* ev) override;
    void dropEvent(QDropEvent* ev) override;

signals:
    void selected(int x, int y);
public slots:
    void refresh();

public:
    bool isCovered = false;
    bool isSelected = false;
    bool isFirstPoint = false;

    int width = -1;
    int height = -1;
    int colum = -1;
    int row = -1;

    int block_row = -1;
    int block_colum = -1;

    int item_type = -1;
    int item_index = -1;
    QString name;
    QString url;
    QString sub_url;

private:
    QMenu menu_;

};

#endif // ELWIDGET_H
