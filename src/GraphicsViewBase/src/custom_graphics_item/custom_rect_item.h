#ifndef CUSTOM_RECT_ITEM_H
#define CUSTOM_RECT_ITEM_H

#include <QGraphicsItem>

enum STATE_FLAG {
    DEFAULT_FLAG = 0,
    MOV_LEFT_LINE,    //矩形的左边界区域
    MOV_TOP_LINE,     //矩形的上边界区域
    MOV_RIGHT_LINE,   //矩形的右边界区域
    MOV_BOTTOM_LINE,  //矩形的下边界区域
    MOV_RIGHTBOTTOM_RECT,  //矩形的右下角
    MOV_RECT,  //移动状态
    ROTATE     //旋转状态
};

class CustomRectItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    CustomRectItem(QGraphicsItem* parent = nullptr);
    ~CustomRectItem();

    // 必须重写该函数
    QRectF  boundingRect() const override;

    void setRectSize(QRectF mrect, bool bResetRotateCenter = true);

    void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void SetRotate(qreal RotateAngle, QPointF ptCenter = QPointF(-999, -999));
    QPointF getRotatePoint(QPointF ptCenter, QPointF ptIn, qreal angle);//获取旋转后的点
    QList<QPointF> getRotatePoints(QPointF ptCenter, QList<QPointF> ptIns, qreal angle);//获取多个旋转后的点
    QPolygonF getRotatePolygonFromRect(QPointF ptCenter, QRectF rectIn, qreal angle);//将矩形旋转之后返回多边形
    QRectF getCrtPosRectToSceen();

    QPointF getSmallRotateRectCenter(QPointF ptA, QPointF ptB);//获取旋转时候矩形正上方的旋转标记矩形
    QRectF  getSmallRotateRect(QPointF ptA, QPointF ptB);

private:
    QRectF  m_oldRect;
    QPolygonF m_oldRectPolygon;
    QRectF  m_RotateAreaRect;
    bool    m_bResize;
    QPolygonF m_insicedPolygon;
    QRectF  m_insicedRectf;
    QPolygonF m_leftPolygon;
    QRectF  m_leftRectf;
    QPolygonF m_topPolygon;
    QRectF  m_topRectf;
    QPolygonF m_rightPolygon;
    QRectF  m_rightRectf;
    QPolygonF m_bottomPolygon;
    QRectF  m_bottomRectf;
    QPointF m_startPos;
    STATE_FLAG m_StateFlag;
    QPointF* m_pPointFofSmallRotateRect;
    QRectF m_SmallRotateRect;//矩形顶部用来表示旋转的标记的矩形
    QPolygonF m_SmallRotatePolygon;//矩形顶部用来表示旋转的标记的矩形旋转后形成的多边形
    bool    m_bRotate;
    qreal   m_RotateAngle;
    QPointF m_RotateCenter;
};


#endif