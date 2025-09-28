#ifndef DONUT_UNIVERSAL_SLIDER_P_H
#define DONUT_UNIVERSAL_SLIDER_P_H

#include "donut_universal_slider.h"
#include "donut_universal_slider_option.h"
#include <QObject>
#include <QIcon>
#include <QString>

class DonutUniversalSliderPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(DonutUniversalSlider)

public:
    explicit DonutUniversalSliderPrivate(DonutUniversalSlider* q);
    virtual ~DonutUniversalSliderPrivate();

    void initStyleOption(DonutUniversalSliderOption* option) const;

    // 坐标转换函数
    int pick(const QPoint& pt) const;
    int pixelPosToRangeValue(int pos) const;
    int rangeValueToPixelPos(int value) const;

    // 碰撞检测
    DonutUniversalSlider::Handle hitTest(const QPoint& pos) const;
    QRect getHandleRect(DonutUniversalSlider::Handle handle) const;

    // 值约束
    void constrainValues();
    void updatePositions();

public:
    DonutUniversalSlider* q_ptr;

    // 滑块配置
    DonutUniversalSliderOption::SliderType sliderType_;
    DonutUniversalSliderOption::HandleCount handleCount_;
    
    // 图标
    QIcon lowerHandleIcon_;
    QIcon upperHandleIcon_;
    QIcon middleHandleIcon_;
    QIcon upTriangleIcon_;
    QIcon downTriangleIcon_;
    QIcon confirmIcon_;
    
    // 垂直滑块专用
    QString title_;
    bool showConfirmButton_;
    bool showTriangleButtons_;
    bool showValueLabels_;
    
    // 值
    int lowerValue_;
    int upperValue_;
    int middleValue_;
    
    // 鼠标状态
    DonutUniversalSlider::Handle pressedHandle_;
    DonutUniversalSlider::Handle hoveredHandle_;
    QPoint lastMousePos_;
    
    // 移动模式
    DonutUniversalSlider::HandleMovementMode movementMode_;
    
    // 悬停状态
    bool lowerHovered_;
    bool upperHovered_;
    bool middleHovered_;
    bool confirmHovered_;
    bool upTriangleHovered_;
    bool downTriangleHovered_;
    
    // 按压状态
    bool lowerPressed_;
    bool upperPressed_;
    bool middlePressed_;
    bool confirmPressed_;
    bool upTrianglePressed_;
    bool downTrianglePressed_;

private Q_SLOTS:
    void updateRange(int min, int max);

private:
    void handleMousePress(const QPoint& pos);
    void handleMouseMove(const QPoint& pos);
    void handleMouseRelease(const QPoint& pos);
    void updateHoverState(const QPoint& pos);
    void resetPressedStates();
};

#endif // DONUT_UNIVERSAL_SLIDER_P_H
