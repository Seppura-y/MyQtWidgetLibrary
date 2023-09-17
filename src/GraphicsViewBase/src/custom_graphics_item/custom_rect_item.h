#ifndef CUSTOM_RECT_ITEM_H
#define CUSTOM_RECT_ITEM_H

#include <QGraphicsItem>

enum STATE_FLAG {
    DEFAULT_FLAG = 0,
    MOV_LEFT_LINE,    //���ε���߽�����
    MOV_TOP_LINE,     //���ε��ϱ߽�����
    MOV_RIGHT_LINE,   //���ε��ұ߽�����
    MOV_BOTTOM_LINE,  //���ε��±߽�����
    MOV_RIGHTBOTTOM_RECT,  //���ε����½�
    MOV_RECT,  //�ƶ�״̬
    ROTATE     //��ת״̬
};

class CustomRectItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    CustomRectItem(QGraphicsItem* parent = nullptr);
    ~CustomRectItem();

    // ������д�ú���
    QRectF  boundingRect() const override;

    void setRectSize(QRectF mrect, bool bResetRotateCenter = true);

    void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void SetRotate(qreal RotateAngle, QPointF ptCenter = QPointF(-999, -999));
    QPointF getRotatePoint(QPointF ptCenter, QPointF ptIn, qreal angle);//��ȡ��ת��ĵ�
    QList<QPointF> getRotatePoints(QPointF ptCenter, QList<QPointF> ptIns, qreal angle);//��ȡ�����ת��ĵ�
    QPolygonF getRotatePolygonFromRect(QPointF ptCenter, QRectF rectIn, qreal angle);//��������ת֮�󷵻ض����
    QRectF getCrtPosRectToSceen();

    QPointF getSmallRotateRectCenter(QPointF ptA, QPointF ptB);//��ȡ��תʱ��������Ϸ�����ת��Ǿ���
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
    QRectF m_SmallRotateRect;//���ζ���������ʾ��ת�ı�ǵľ���
    QPolygonF m_SmallRotatePolygon;//���ζ���������ʾ��ת�ı�ǵľ�����ת���γɵĶ����
    bool    m_bRotate;
    qreal   m_RotateAngle;
    QPointF m_RotateCenter;
};


#endif