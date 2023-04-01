#include "elwidget.h"
#include "item_listwidget.h"

#include <QPainter>
#include <QStyleOption>
#include <QAction>
#include <QString>
#include <QDebug>
#include <QListWidget>
#include <QTabWidget>
#include <QMimeData>
#include <QJsonObject>
#include <QJsonDocument>
#include <QPixMap>

#define ITEM_LIST_CONFIG "./config/item_list_conf.json"
#define GRID_CONFIG "./config/grid_conf.json"

ElWidget::ElWidget(int row_, int colum_, int w, int h, QWidget* parent) : QWidget(parent)
{
    colum = colum_;
    row = row_;
    width = w;
    height = h;
    isSelected = false;
    isCovered = false;
    isFirstPoint = false;

    block_row = -1;
    block_colum = -1;
    this->setStyleSheet("background-color:rgb(60,60,60)");
    this->setAcceptDrops(true);
}

void ElWidget::paintEvent(QPaintEvent* ev)
{
    QStyleOption opt;
    opt.init(this);

    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void ElWidget::mousePressEvent(QMouseEvent* ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        qDebug() << "left button clicked";
        if (isSelected)
        {
            isSelected = false;
            emit selected(row, colum);
        }
        else
        {
            isSelected = true;
            //this->refresh();
            emit selected(row, colum);
        }
    }
    qDebug() << "row:" << row << " colum:" << colum;
    qDebug() << "width" << width << "height : " << height;
    qDebug() << "block_row : " << block_row << "block_colum : " << block_colum << endl;
    qDebug() << "isCovered : " << isCovered;

}
void ElWidget::dragEnterEvent(QDragEnterEvent* ev)
{
    ev->acceptProposedAction();
}

void ElWidget::dropEvent(QDropEvent* ev)
{
    //int itemIndex = ((ItemListWidget*)ev->source())->currentIndex().row();
    //int itemType = ((ItemListWidget*)ev->source())->itemType;

    //QByteArray arr = ev->mimeData()->data("application/json");
    //qDebug() << arr;
    //QJsonParseError err;
    //QJsonDocument doc(QJsonDocument::fromJson(arr, &err));
    //QJsonObject obj = doc.object();

    //this->name = obj.find("name").value().toString();
    //this->url = obj.find("url").value().toString();
    //this->sub_url = obj.find("sub_url").value().toString();
    //this->item_type = itemType;
    //switch (itemType)
    //{
    //    case 0:
    //    {
    //        //QPixmap pix = QPixmap(":Mng/image/cmr.png");
    //        //pix.scaled(this->size());
    //        //this->image
    //        this->setStyleSheet("	border-image: url(D:/hsy/ffmpeg_code/src/Manager/image/cam.png)");
    //        break;
    //    }
    //    case 1:
    //    {
    //        this->setStyleSheet("	border-image: url(D:/hsy/ffmpeg_code/src/Manager/image/agn.png)");
    //        break;
    //    }
    //    case 2:
    //    {
    //        this->setStyleSheet("	border-image: url(D:/hsy/ffmpeg_code/src/Manager/image/web.png)");
    //        break;
    //    }
    //    case 3:
    //    {
    //        this->setStyleSheet("	border-image: url(D:/hsy/ffmpeg_code/src/Manager/image/pic.png)");
    //        break;
    //    }
    //}


    //ev->setDropAction(Qt::MoveAction);
    //ev->accept();

    QWidget::dropEvent(ev);
}


void ElWidget::refresh()
{
    if (isSelected)
    {
        if (isFirstPoint)
        {
            this->setStyleSheet("background-color:rgb(255,255,127)");
        }
        else
        {
            this->setStyleSheet("background-color:rgb(255,255,255)");
        }

    }
    else
    {
        this->setStyleSheet("background-color:rgb(60,60,60)");
    }
}