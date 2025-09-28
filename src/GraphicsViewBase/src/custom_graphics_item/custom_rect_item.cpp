#include "custom_rect_item.h"

#include <QtMath>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

CustomRectItem::CustomRectItem(QGraphicsItem* parent) :
    m_bResize(false),
    m_oldRect(200, 200, 200, 200),
    m_bRotate(false),
    m_RotateAngle(0),
    m_StateFlag(DEFAULT_FLAG)
{
    setRectSize(m_oldRect);

    //设置光标形状,手的形状
    setCursor(Qt::ArrowCursor);

    //设置图元是可移动的
    setFlags(QGraphicsItem::ItemIsMovable
        | QGraphicsItem::ItemIsSelectable
        | QGraphicsItem::ItemIsFocusable);

    m_pPointFofSmallRotateRect = new QPointF[4];
    SetRotate(0);
}

CustomRectItem::~CustomRectItem()
{
    delete[] m_pPointFofSmallRotateRect;
    m_pPointFofSmallRotateRect = nullptr;
}

QRectF CustomRectItem::boundingRect() const
{
    QRectF boundingRectF = m_oldRectPolygon.boundingRect();
    return QRectF(boundingRectF.x() - 40, boundingRectF.y() - 40,
        boundingRectF.width() + 80, boundingRectF.height() + 80);
}

void CustomRectItem::setRectSize(QRectF mrect, bool bResetRotateCenter)
{
    m_oldRect = mrect;

    if (bResetRotateCenter)
    {
        m_RotateCenter.setX(m_oldRect.x() + m_oldRect.width() / 2);
        m_RotateCenter.setY(m_oldRect.y() + m_oldRect.height() / 2);
    }

    m_oldRectPolygon = getRotatePolygonFromRect(m_RotateCenter, m_oldRect, m_RotateAngle);

    m_insicedRectf = QRectF(m_oldRect.x() + 8, m_oldRect.y() + 8, m_oldRect.width() - 16, m_oldRect.height() - 16);
    m_insicedPolygon = getRotatePolygonFromRect(m_RotateCenter, m_insicedRectf, m_RotateAngle);

    m_leftRectf = QRectF(m_oldRect.x(), m_oldRect.y(), 8, m_oldRect.height() - 8);
    m_leftPolygon = getRotatePolygonFromRect(m_RotateCenter, m_leftRectf, m_RotateAngle);

    m_topRectf = QRectF(m_oldRect.x() + 8, m_oldRect.y(), m_oldRect.width() - 8, 8);
    m_topPolygon = getRotatePolygonFromRect(m_RotateCenter, m_topRectf, m_RotateAngle);

    m_rightRectf = QRectF(m_oldRect.right() - 8, m_oldRect.y() + 8, 8, m_oldRect.height() - 16);
    m_rightPolygon = getRotatePolygonFromRect(m_RotateCenter, m_rightRectf, m_RotateAngle);

    m_bottomRectf = QRectF(m_oldRect.x(), m_oldRect.bottom() - 8, m_oldRect.width() - 8, 8);
    m_bottomPolygon = getRotatePolygonFromRect(m_RotateCenter, m_bottomRectf, m_RotateAngle);

    m_SmallRotateRect = getSmallRotateRect(mrect.topLeft(), mrect.topRight());//矩形正上方的旋转标记矩形
    m_SmallRotatePolygon = getRotatePolygonFromRect(m_RotateCenter, m_SmallRotateRect, m_RotateAngle);
}

void CustomRectItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    //反锯齿
    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen mPen = QPen(Qt::black);
    mPen.setWidth(5);
    painter->setPen(mPen);

    //绘制旋转后的矩形
    painter->drawPolygon(m_oldRectPolygon);

    //绘制旋转圆形
    mPen.setWidth(2);
    mPen.setColor(Qt::green);
    painter->setPen(mPen);
    QPointF pf = getSmallRotateRectCenter(m_oldRectPolygon[0], m_oldRectPolygon[1]);
    QRectF rect = QRectF(pf.x() - 10, pf.y() - 10, 20, 20);

    //绘制圆形
    painter->drawEllipse(rect);

    //绘制点
    painter->drawPoint(pf);

    if (option->state & QStyle::State_Selected)
    {
        // 绘制选择后的虚线框
        const qreal penWidth = 1;

        // 边框区域颜色
        QColor color = QColor(Qt::white);

        painter->setPen(QPen(color, penWidth, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawPolygon(m_oldRectPolygon);
    }
}

void CustomRectItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_startPos = event->pos();
        if (m_SmallRotatePolygon.containsPoint(m_startPos, Qt::WindingFill))
        {
            //鼠标在旋转圆形内内
            setCursor(Qt::PointingHandCursor);
            m_StateFlag = ROTATE;
        }
        else if (m_insicedPolygon.containsPoint(m_startPos, Qt::WindingFill))
        {
            //在矩形内框区域时
            setCursor(Qt::ClosedHandCursor);   //改变光标形状,手的形状
            m_StateFlag = MOV_RECT;
        }
        else if (m_leftPolygon.containsPoint(m_startPos, Qt::WindingFill))
        {
            //矩形的左边界区域
            setCursor(Qt::SizeHorCursor);
            m_StateFlag = MOV_LEFT_LINE;
        }
        else if (m_rightPolygon.containsPoint(m_startPos, Qt::WindingFill))
        {
            //矩形的右边界区域
            setCursor(Qt::SizeHorCursor);
            m_StateFlag = MOV_RIGHT_LINE;
        }
        else if (m_topPolygon.containsPoint(m_startPos, Qt::WindingFill))
        {
            //矩形的上边界区域
            setCursor(Qt::SizeVerCursor);
            m_StateFlag = MOV_TOP_LINE;
        }
        else if (m_bottomPolygon.containsPoint(m_startPos, Qt::WindingFill))
        {
            //矩形的下边界区域
            setCursor(Qt::SizeVerCursor);
            m_StateFlag = MOV_BOTTOM_LINE;
        }
        else
        {
            m_StateFlag = DEFAULT_FLAG;
        }
    }
    else
    {
        QGraphicsItem::mousePressEvent(event);
    }
}

void CustomRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_StateFlag == ROTATE)
    {
        // 注意atan2计算出来的是弧度值，需要转化为角度值
        int nRotateAngle = atan2((event->pos().x() - m_RotateCenter.x()),
            (event->pos().y() - m_RotateCenter.y())) * 180 / M_PI;

        SetRotate(180 - nRotateAngle);
        setRectSize(m_oldRect);
    }
    else if (m_StateFlag == MOV_RECT)
    {
        QPointF point = (event->pos() - m_startPos);
        moveBy(point.x(), point.y());
        setRectSize(m_oldRect);
        scene()->update();
    }
    else if (m_StateFlag == MOV_LEFT_LINE)
    {
        QPointF pf = QPointF((m_oldRectPolygon.at(1).x() + m_oldRectPolygon.at(2).x()) / 2, ((m_oldRectPolygon.at(1).y() + m_oldRectPolygon.at(2).y()) / 2));

        //计算到右侧边中点的距离
        qreal dis = sqrt((event->pos().x() - pf.x()) * (event->pos().x() - pf.x()) + (event->pos().y() - pf.y()) * (event->pos().y() - pf.y()));
        qreal dis2LT = sqrt((event->pos().x() - m_oldRectPolygon.at(0).x()) * (event->pos().x() - m_oldRectPolygon.at(0).x()) + (event->pos().y() - m_oldRectPolygon.at(0).y()) * (event->pos().y() - m_oldRectPolygon.at(0).y()));
        qreal dis2RT = sqrt((event->pos().x() - m_oldRectPolygon.at(1).x()) * (event->pos().x() - m_oldRectPolygon.at(1).x()) + (event->pos().y() - m_oldRectPolygon.at(1).y()) * (event->pos().y() - m_oldRectPolygon.at(1).y()));
        if (dis<16 || dis2LT>dis2RT)
        {
            return;
        }
        else
        {
            QRectF newRect(m_oldRect);
            newRect.setLeft(m_oldRect.right() - dis);
            newRect.setRight(m_oldRect.right());
            setRectSize(newRect, false);
            m_RotateCenter = QPointF((m_oldRectPolygon.at(0).x() + m_oldRectPolygon.at(2).x()) / 2, (m_oldRectPolygon.at(0).y() + m_oldRectPolygon.at(2).y()) / 2);
            m_oldRect.moveCenter(m_RotateCenter);
            setRectSize(m_oldRect);

            //必须要用scene()->update()，不能用update();否则会出现重影
            scene()->update();
        }
    }
    else if (m_StateFlag == MOV_TOP_LINE)
    {
        //底边中点
        QPointF pf = QPointF((m_oldRectPolygon.at(2).x() + m_oldRectPolygon.at(3).x()) / 2, ((m_oldRectPolygon.at(2).y() + m_oldRectPolygon.at(3).y()) / 2));

        //计算到底边中点的距离
        qreal dis = sqrt((event->pos().x() - pf.x()) * (event->pos().x() - pf.x()) + (event->pos().y() - pf.y()) * (event->pos().y() - pf.y()));
        qreal dis2LT = sqrt((event->pos().x() - m_oldRectPolygon.at(0).x()) * (event->pos().x() - m_oldRectPolygon.at(0).x()) + (event->pos().y() - m_oldRectPolygon.at(0).y()) * (event->pos().y() - m_oldRectPolygon.at(0).y()));
        qreal dis2LB = sqrt((event->pos().x() - m_oldRectPolygon.at(3).x()) * (event->pos().x() - m_oldRectPolygon.at(3).x()) + (event->pos().y() - m_oldRectPolygon.at(3).y()) * (event->pos().y() - m_oldRectPolygon.at(3).y()));

        if (dis<16 || dis2LT>dis2LB)
        {
            return;
        }
        else
        {
            QRectF newRect(m_oldRect);
            newRect.setTop(m_oldRect.bottom() - dis);
            newRect.setBottom(m_oldRect.bottom());
            setRectSize(newRect, false);
            m_RotateCenter = QPointF((m_oldRectPolygon.at(0).x() + m_oldRectPolygon.at(2).x()) / 2, (m_oldRectPolygon.at(0).y() + m_oldRectPolygon.at(2).y()) / 2);
            m_oldRect.moveCenter(m_RotateCenter);
            setRectSize(m_oldRect);
            scene()->update();//必须要用scene()->update()，不能用update();否则会出现重影
        }
    }
    else if (m_StateFlag == MOV_RIGHT_LINE)
    {
        QPointF pf = QPointF((m_oldRectPolygon.at(0).x() + m_oldRectPolygon.at(3).x()) / 2, ((m_oldRectPolygon.at(0).y() + m_oldRectPolygon.at(3).y()) / 2));

        //计算到左侧边中点的距离
        qreal dis = sqrt((event->pos().x() - pf.x()) * (event->pos().x() - pf.x()) + (event->pos().y() - pf.y()) * (event->pos().y() - pf.y()));
        qreal dis2LT = sqrt((event->pos().x() - m_oldRectPolygon.at(0).x()) * (event->pos().x() - m_oldRectPolygon.at(0).x()) + (event->pos().y() - m_oldRectPolygon.at(0).y()) * (event->pos().y() - m_oldRectPolygon.at(0).y()));
        qreal dis2RT = sqrt((event->pos().x() - m_oldRectPolygon.at(1).x()) * (event->pos().x() - m_oldRectPolygon.at(1).x()) + (event->pos().y() - m_oldRectPolygon.at(1).y()) * (event->pos().y() - m_oldRectPolygon.at(1).y()));
        if (dis < 16 || dis2LT < dis2RT)
        {
            return;
        }
        else
        {
            QRectF newRect(m_oldRect);
            newRect.setLeft(m_oldRect.left());
            newRect.setRight(m_oldRect.left() + dis);
            setRectSize(newRect, false);
            m_RotateCenter = QPointF((m_oldRectPolygon.at(0).x() + m_oldRectPolygon.at(2).x()) / 2, (m_oldRectPolygon.at(0).y() + m_oldRectPolygon.at(2).y()) / 2);
            m_oldRect.moveCenter(m_RotateCenter);
            setRectSize(m_oldRect);

            //必须要用scene()->update()，不能用update();否则会出现重影
            scene()->update();
        }
    }
    else if (m_StateFlag == MOV_BOTTOM_LINE)
    {
        //顶边中点
        QPointF pf = QPointF((m_oldRectPolygon.at(0).x() + m_oldRectPolygon.at(1).x()) / 2, ((m_oldRectPolygon.at(0).y() + m_oldRectPolygon.at(1).y()) / 2));

        //计算到底边中点的距离
        qreal dis = sqrt((event->pos().x() - pf.x()) * (event->pos().x() - pf.x()) + (event->pos().y() - pf.y()) * (event->pos().y() - pf.y()));
        qreal dis2LT = sqrt((event->pos().x() - m_oldRectPolygon.at(0).x()) * (event->pos().x() - m_oldRectPolygon.at(0).x()) + (event->pos().y() - m_oldRectPolygon.at(0).y()) * (event->pos().y() - m_oldRectPolygon.at(0).y()));
        qreal dis2LB = sqrt((event->pos().x() - m_oldRectPolygon.at(3).x()) * (event->pos().x() - m_oldRectPolygon.at(3).x()) + (event->pos().y() - m_oldRectPolygon.at(3).y()) * (event->pos().y() - m_oldRectPolygon.at(3).y()));
        if (dis < 16 || dis2LT < dis2LB)
        {
            return;
        }
        else
        {
            QRectF newRect(m_oldRect);
            newRect.setTop(m_oldRect.top());
            newRect.setBottom(m_oldRect.top() + dis);
            setRectSize(newRect, false);
            m_RotateCenter = QPointF((m_oldRectPolygon.at(0).x() + m_oldRectPolygon.at(2).x()) / 2, (m_oldRectPolygon.at(0).y() + m_oldRectPolygon.at(2).y()) / 2);
            m_oldRect.moveCenter(m_RotateCenter);
            setRectSize(m_oldRect);

            //必须要用scene()->update()，不能用update();否则会出现重影
            scene()->update();
        }
    }
}

void CustomRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    setCursor(Qt::ArrowCursor);
    if (m_StateFlag == MOV_RECT)
    {
        m_StateFlag = DEFAULT_FLAG;
    }
    else
    {
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

void CustomRectItem::SetRotate(qreal RotateAngle, QPointF ptCenter)
{
    m_bRotate = true;
    if (ptCenter.x() == -999 && ptCenter.y() == -999)
    {
        m_RotateCenter = QPointF(m_oldRect.x() + m_oldRect.width() / 2, m_oldRect.y() + m_oldRect.height() / 2);
    }
    else
    {
        m_RotateCenter = ptCenter;
    }

    m_RotateAngle = RotateAngle;
    this->update();
}

QPointF CustomRectItem::getRotatePoint(QPointF ptCenter, QPointF ptIn, qreal angle)
{
    double dx = ptCenter.x();
    double dy = ptCenter.y();
    double x = ptIn.x();
    double y = ptIn.y();
    double xx, yy;
    xx = (x - dx) * cos(angle * M_PI / 180) - (y - dy) * sin(angle * M_PI / 180) + dx;
    yy = (x - dx) * sin(angle * M_PI / 180) + (y - dy) * cos(angle * M_PI / 180) + dy;

    return QPointF(xx, yy);
}

QList<QPointF> CustomRectItem::getRotatePoints(QPointF ptCenter, QList<QPointF> ptIns, qreal angle)
{
    QList<QPointF> lstPt;
    for (int i = 0; i < ptIns.count(); i++)
    {
        lstPt.append(getRotatePoint(ptCenter, ptIns.at(i), angle));
    }
    return lstPt;
}

QPolygonF CustomRectItem::getRotatePolygonFromRect(QPointF ptCenter, QRectF rectIn, qreal angle)
{
    QVector<QPointF> vpt;
    QPointF pf = getRotatePoint(ptCenter, rectIn.topLeft(), angle);
    vpt.append(pf);
    pf = getRotatePoint(ptCenter, rectIn.topRight(), angle);
    vpt.append(pf);
    pf = getRotatePoint(ptCenter, rectIn.bottomRight(), angle);
    vpt.append(pf);
    pf = getRotatePoint(ptCenter, rectIn.bottomLeft(), angle);
    vpt.append(pf);
    pf = getRotatePoint(ptCenter, rectIn.topLeft(), angle);
    vpt.append(pf);
    return QPolygonF(vpt);
}

QRectF CustomRectItem::getCrtPosRectToSceen()
{
    QRectF retRect = QRectF(m_oldRect.x() + pos().x(), m_oldRect.y() + pos().y(), m_oldRect.width(), m_oldRect.height());
    return retRect;
}

QRectF CustomRectItem::getSmallRotateRect(QPointF ptA, QPointF ptB)
{
    QPointF pt = getSmallRotateRectCenter(ptA, ptB);
    return QRectF(pt.x() - 10, pt.y() - 10, 20, 20);
}

QPointF CustomRectItem::getSmallRotateRectCenter(QPointF ptA, QPointF ptB)
{
    //A,B点的中点C
    QPointF ptCenter = QPointF((ptA.x() + ptB.x()) / 2, (ptA.y() + ptB.y()) / 2);

    //中垂线方程式为 y=x*k + b
    qreal x, y;//旋转图标矩形的中心
    if (abs(ptB.y() - ptA.y()) < 0.1)
    {
        if (ptA.x() < ptB.x())//矩形左上角在上方
        {
            x = ptCenter.x();
            y = ptCenter.y() - 20;
        }
        else
        {
            //矩形左上角在下方
            x = ptCenter.x();
            y = ptCenter.y() + 20;
        }
    }
    else if (ptB.y() > ptA.y()) //顺时针旋转0-180
    {
        qreal k = (ptA.x() - ptB.x()) / (ptB.y() - ptA.y());//中垂线斜率
        qreal b = (ptA.y() + ptB.y()) / 2 - k * (ptA.x() + ptB.x()) / 2;
        //求AB线中垂线上离AB中点20个像素的点C的坐标
        x = 20 * cos(atan(k)) + ptCenter.x();
        y = k * x + b;
    }
    else if (ptB.y() < ptA.y()) //顺时针旋转180-360
    {
        qreal k = (ptA.x() - ptB.x()) / (ptB.y() - ptA.y());//中垂线斜率
        qreal b = (ptA.y() + ptB.y()) / 2 - k * (ptA.x() + ptB.x()) / 2;

        //求AB线中垂线上离AB中点20个像素的点C的坐标
        x = -20 * cos(atan(k)) + ptCenter.x();
        y = k * x + b;
    }

    return QPointF(x, y);
}

