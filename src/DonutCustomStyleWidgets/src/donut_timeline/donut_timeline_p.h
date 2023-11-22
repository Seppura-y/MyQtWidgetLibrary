#ifndef DONUT_TIMELINE_P_H
#define DONUT_TIMELINE_P_H

#include <QStyle>
#include <QObject>
#include <QStyleOptionSlider>
#include <QStyleOptionComplex>
#include "donut_timeline.h"

QT_FORWARD_DECLARE_CLASS(QStylePainter)
QT_FORWARD_DECLARE_CLASS(QStyleOptionSlider)
QT_FORWARD_DECLARE_CLASS(QWidget)

// DonutTimeline��������
class DonutTimelinePrivate : public QObject
{
	Q_OBJECT

public:
    DonutTimelinePrivate();

	void initStyleOption(QStyleOptionSlider* option, DonutTimeline::SpanHandle handle = DonutTimeline::UpperHandle) const;

    int pick(const QPoint& pt) const
    {
        return q_ptr_->orientation() == Qt::Horizontal ? pt.x() : pt.y();
    }

    // ������λ��ת��Ϊ��ֵ
    int pixelPosToRangeValue(int pos) const;

    // mousePressedEvent�У��ֱ��� lower_pressed_ �� upper_pressed_�����ã� �Բ鿴�˴������е����ĸ�SubControl
    // SC_SliderGroove �� SC_SliderHandle �� SC_SliderTickmarks
    void handleMousePress(const QPoint& pos, QStyle::SubControl& control, int value, DonutTimeline::SpanHandle handle);

    // δ��
    QRect getSpan(QPainter* painter, const QRect& rect) const;

    void triggerAction(QAbstractSlider::SliderAction action, bool main);

    // FreeMovement���õ�
    void swapControls();

    int lower_;
    int upper_;
    int middle_;

    int lower_pos_;
    int upper_pos_;
    int middle_pos_;
    int mouse_hover_pos_;

    // ʵ�ⲻ����offsetҲû����ʲôӰ��
    int offset_;

    // ÿ�ε��handleʱ��¼��ʼλ�ã�����ʵ�ֵ�����϶��뿪PM_MaximumDragDistance��Χʱ�����û���������λ��
    int position_;

    // ��¼����������ĸ�handle
    DonutTimeline::SpanHandle last_pressed_;

    DonutTimeline::SpanHandle main_control_;

    // ��¼�����е����ĸ�SubControl
    QStyle::SubControl lower_pressed_;
    // ��¼�����е����ĸ�SubControl
    QStyle::SubControl upper_pressed_;
    QStyle::SubControl middle_pressed_;

    DonutTimeline::HandleMovementMode movement_;
    bool first_movement_;

    // ֹͣ׷��sliderλ�õı�־λ����ֹsetUpperPosition �� setLowerPosition��ѭ������triggerAction
    bool block_tracking_;

    QRect lower_rect_;
    QRect upper_rect_;
    QRect middle_rect_;

    // �����⼸��ֵ���������ͣ���
    bool lower_hovered_;
    bool upper_hovered_;
    bool middle_hovered_;

    DonutTimeline::SpanHandle hovered_handle_;

public Q_SLOTS:
    void updateRange(int min, int max);
    void movePressedHandle();

private:

    DonutTimeline* q_ptr_;
	friend class DonutTimeline;
};

class DonutTimelineStyleOption : public QStyleOptionSlider
{
public:
    DonutTimelineStyleOption();
    DonutTimelineStyleOption(const DonutTimelineStyleOption& other) : QStyleOptionSlider() { *this = other; }
    DonutTimelineStyleOption& operator=(const DonutTimelineStyleOption&) = default;
public:
	QRect upper_rect_;
    QRect lower_rect_;
    QRect middle_rect_;
	QRect span_rect_;

	QPoint span_start_;
	QPoint span_end_;

	//int upper_position_;
	//int lower_position_;
    int cur_position_;

	QStyle::SubControls lower_handle_;
    QStyle::SubControls upper_handle_;
    QStyle::SubControls middle_handle_;

	bool lower_hovered_ = false;
    bool upper_hovered_ = false;
    bool middle_hovered_ = false;

    QWidget* wid_ = nullptr;
};
#endif