#include "main_wid.h"

#include <QGraphicsRectItem>

#include <QDebug>

MainWid::MainWid(QWidget* parent)
	: QWidget(parent)
{
    lab_scene_pos_ = new QLabel(this);
    lab_scene_pos_->setGeometry(10, 5, 160, 30);
    lab_scene_pos_->show();

    lab_view_pos_ = new QLabel(this);
    lab_view_pos_->setGeometry(300, 5, 160, 30);
    lab_view_pos_->show();

    lab_item_pos_ = new QLabel(this);
    lab_item_pos_->setGeometry(10, 80, 160, 30);
    lab_item_pos_->show();

    view_ = new GraphicsViewBasic(this);
    view_->setGeometry(10, 120, this->width() - 10, this->height() - 80);
    view_->show();

    QObject::connect(view_, &GraphicsViewBasic::sigMouseMovePoint, this, &MainWid::onMouseMovePoint);
    QObject::connect(view_, &GraphicsViewBasic::sigMouseClickedPoint, this, &MainWid::onMouseClickedPoint);

    initGraphicsView();
}

MainWid::~MainWid()
{
    delete lab_scene_pos_;
    delete lab_view_pos_;
    delete lab_item_pos_;
    delete view_;
}

void MainWid::initGraphicsView()
{
    QRectF rect(-300, -100, 400, 200);
    scene_ = new QGraphicsScene(rect);

    //����ͼ���ó���
    view_->setScene(scene_);

    //��һ�����ο򣬴�С����scene
    QGraphicsRectItem* item = new QGraphicsRectItem(rect);

    //��ѡ�������н��㣬���ǲ����ƶ�
    item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    QPen    pen;
    pen.setWidth(20);
    item->setPen(pen);
    scene_->addItem(item);

    //һ��λ��scene���ĵ���Բ
    QGraphicsEllipseItem* item2 = new QGraphicsEllipseItem(-100, -50, 200, 100);
    item2->setPos(-200, 0);
    item2->setBrush(QBrush(Qt::blue));
    item2->setFlags(QGraphicsItem::ItemIsMovable
        | QGraphicsItem::ItemIsSelectable
        | QGraphicsItem::ItemIsFocusable);
    scene_->addItem(item2);

    //һ��Բ������λ��scene�ı�Ե
    QGraphicsEllipseItem* item3 = new QGraphicsEllipseItem(-50, -50, 100, 100);
    item3->setPos(rect.right(), rect.bottom());
    item3->setBrush(QBrush(Qt::red));
    item3->setFlags(QGraphicsItem::ItemIsMovable
        | QGraphicsItem::ItemIsSelectable
        | QGraphicsItem::ItemIsFocusable);
    scene_->addItem(item3);

    scene_->clearSelection();

}

void MainWid::onMouseMovePoint(QPoint point)
{
    QPointF p(point);
    QString str = QString::asprintf("mov view pos : %.0f, %.0f", p.x(), p.y());
    lab_view_pos_->setText(str);
    QPointF point_of_scene = view_->mapToScene(point);
    lab_scene_pos_->setText(QString::asprintf("mov scene pos : %.0f, %.0f", point_of_scene.x(), point_of_scene.y()));
}

void MainWid::onMouseClickedPoint(QPoint point)
{
    QPointF point_of_scene = view_->mapToScene(point);
    lab_scene_pos_->setText(QString::asprintf("clk scene pos : %.0f, %.0f", point_of_scene.x(), point_of_scene.y()));

    QGraphicsItem* item = nullptr;
    item = scene_->itemAt(point_of_scene, view_->transform());
    if (item != nullptr)
    {
        QPointF point_of_item = item->mapFromScene(point_of_scene);
        lab_item_pos_->setText(QString::asprintf("clk itme pos : %.0f, %.0f", point_of_item.x(), point_of_item.y()));
    }
}