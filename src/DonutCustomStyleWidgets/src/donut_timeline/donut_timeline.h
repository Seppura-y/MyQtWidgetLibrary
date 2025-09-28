#ifndef DONUT_TIMELINE_H
#define DONUT_TIMELINE_H

#include <QSlider>

class DonutTimelinePrivate;
class DonutTimeline : public QSlider
{
	Q_OBJECT

    Q_PROPERTY(int lowerValue READ lowerValue WRITE setLowerValue)
    Q_PROPERTY(int upperValue READ upperValue WRITE setUpperValue)
    Q_PROPERTY(int lowerPosition READ lowerPosition WRITE setLowerPosition)
    Q_PROPERTY(int upperPosition READ upperPosition WRITE setUpperPosition)
    Q_PROPERTY(HandleMovementMode handleMovementMode READ handleMovementMode WRITE setHandleMovementMode)
    Q_ENUMS(HandleMovementMode)
public:
    explicit DonutTimeline(QWidget* parent = nullptr);
    explicit DonutTimeline(Qt::Orientation orientation, QWidget* parent = nullptr);
    ~DonutTimeline();

    enum HandleMovementMode
    {
        FreeMovement,
        NoCrossing,
        NoOverlapping
    };

    enum SpanHandle
    {
        NoHandle,
        LowerHandle,
        UpperHandle,
        MiddleHandle
    };

    HandleMovementMode handleMovementMode() const;
    void setHandleMovementMode(HandleMovementMode mode);

    int lowerValue() const;
    int upperValue() const;
    int middleValue() const;

    int lowerPosition() const;
    int upperPosition() const;
    int middlePosition() const;

public Q_SLOTS:
    // 内部调用setSpan, 传入d_ptr_->upper_作为上限值
    void setLowerValue(int lower);
    // 内部调用setSpan, 传入d_ptr_->lower_作为下限值
    void setUpperValue(int upper);

    void setMiddleValue(int middle);

    void setSpan(int lower, int upper);

    // 更新d_ptr_->lower_pos_
    void setLowerPosition(int lower);
    // 更新d_ptr_->upper_pos_
    void setUpperPosition(int upper);

    void setMiddlePosition(int middle);
Q_SIGNALS:
    void spanChanged(int lower, int upper);

    void lowerValueChanged(int lower);
    void upperValueChanged(int upper);
    void middleValueChanged(int middle);

    void lowerPositionChanged(int lower);
    void upperPositionChanged(int upper);
    void middlePositionChanged(int middle);

    void sliderPressed(SpanHandle handle);

protected:
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void paintEvent(QPaintEvent* event);

private:
    DonutTimelinePrivate* d_ptr_;
    friend class DonutTimelinePrivate;
};

#endif