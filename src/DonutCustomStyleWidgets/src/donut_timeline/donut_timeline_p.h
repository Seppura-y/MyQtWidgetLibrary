#ifndef DONUT_TIMELINE_P_H
#define DONUT_TIMELINE_P_H

#include <QStyle>
#include <QObject>
#include <QStyleOptionSlider>
#include <QStyleOptionComplex>
#include "donut_timeline.h"

QT_FORWARD_DECLARE_CLASS(QStylePainter)
QT_FORWARD_DECLARE_CLASS(QStyleOptionSlider)

// DonutTimeline的数据类
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
    int pixelPosToRangeValue(int pos) const;

    // mousePressedEvent中，分别传入 lower_pressed_ 和 upper_pressed_的引用， 以查看此次鼠标点中的是哪个SubControl
    // SC_SliderGroove 或 SC_SliderHandle 或 SC_SliderTickmarks
    void handleMousePress(const QPoint& pos, QStyle::SubControl& control, int value, DonutTimeline::SpanHandle handle);

    // 未用
    QRect getSpan(QPainter* painter, const QRect& rect) const;

    void triggerAction(QAbstractSlider::SliderAction action, bool main);
    void swapControls();

    int lower_;
    int upper_;
    int current_;

    int lower_pos_;
    int upper_pos_;
    int current_pos_;

    // 实测不设置offset也没看出什么影响
    int offset_;
    int position_;

    // 记录最后点击的是哪个handle
    DonutTimeline::SpanHandle last_pressed_;

    DonutTimeline::SpanHandle main_control_;

    // 记录鼠标点中的是哪个SubControl
    QStyle::SubControl lower_pressed_;
    // 记录鼠标点中的是哪个SubControl
    QStyle::SubControl upper_pressed_;

    DonutTimeline::HandleMovementMode movement_;
    bool first_movement_;

    // 停止追踪slider位置的标志位，防止setUpperPosition 和 setLowerPosition中循环调用triggerAction
    bool block_tracking_;

    QRect lower_rect_;
    QRect upper_rect_;

    bool lower_hovered_;
    bool upper_hovered_;

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
	QRect span_rect_;

	QPoint span_start_;
	QPoint span_end_;

	int upper_position_;
	int lower_position_;

	QStyle::SubControls lower_handle_;
	QStyle::SubControls upper_handle_;

	bool lower_hovered_ = false;
	bool upper_hovered_ = false;
};
#endif