#ifndef DONUT_UNIFIED_SLIDER_P_H
#define DONUT_UNIFIED_SLIDER_P_H

#include <QObject>
#include <QStyleOptionSlider>
#include <QStyleOptionComplex>
#include <QIcon>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRect>
#include <QPoint>
#include <QHash>
#include "donut_unified_slider.h"

// 自定义样式选项
class DonutUnifiedSliderStyleOption : public QStyleOptionComplex
{
public:
    DonutUnifiedSliderStyleOption();
    DonutUnifiedSliderStyleOption(const DonutUnifiedSliderStyleOption& other);
    DonutUnifiedSliderStyleOption& operator=(const DonutUnifiedSliderStyleOption& other);

    // 基本滑块信息
    int minimum = 0;
    int maximum = 100;
    int singleStep = 1;
    int pageStep = 10;
    Qt::Orientation orientation = Qt::Horizontal;
    DonutUnifiedSlider::SliderStyle sliderStyle = DonutUnifiedSlider::HorizontalRangeStyle;

    // Handle信息
    int handleCount = 2;
    QList<int> handleValues;       // 各个handle的值
    QList<int> handlePositions;    // 各个handle的位置
    QList<QRect> handleRects;      // 各个handle的矩形区域
    QList<QIcon> handleIcons;      // 各个handle的图标
    QList<bool> handleHovered;     // 各个handle的悬停状态
    QList<bool> handlePressed;     // 各个handle的按下状态

    // 轨道信息
    QRect grooveRect;              // 轨道矩形
    QRect spanRect;                // 选中区间矩形

    // 外观选项
    bool showRangeLabels = false;
    bool showValueLabels = false;
    bool showTitle = false;
    QString title;
    bool showControlButtons = false;
    bool showConfirmButton = false;
    QString confirmButtonText = "确认";

    // 移动模式
    DonutUnifiedSlider::HandleMovementMode handleMovementMode = DonutUnifiedSlider::FreeMovement;

    // 当前活动的handle
    DonutUnifiedSlider::HandleType activeHandle = DonutUnifiedSlider::NoHandle;
    DonutUnifiedSlider::HandleType hoveredHandle = DonutUnifiedSlider::NoHandle;
};

// 私有实现类
class DonutUnifiedSliderPrivate : public QObject
{
    Q_OBJECT

public:
    explicit DonutUnifiedSliderPrivate(DonutUnifiedSlider* parent);
    ~DonutUnifiedSliderPrivate();

    // 初始化样式选项
    void initStyleOption(DonutUnifiedSliderStyleOption* option) const;
    
    // 坐标转换
    int pixelPosToRangeValue(int pos) const;
    int rangeValueToPixelPos(int value) const;
    
    // Handle操作
    DonutUnifiedSlider::HandleType hitTestHandle(const QPoint& pos) const;
    QRect getHandleRect(DonutUnifiedSlider::HandleType handle) const;
    void updateHandleRects();
    
    // 鼠标事件处理
    void handleMousePress(const QPoint& pos);
    void handleMouseMove(const QPoint& pos);
    void handleMouseRelease(const QPoint& pos);
    
    // 值约束
    int constrainValue(DonutUnifiedSlider::HandleType handle, int value) const;
    void updateHandleValue(DonutUnifiedSlider::HandleType handle, int value);
    
    // 布局相关
    void updateLayout();
    void updateComponentVisibility();
    
    // 工具函数
    int pick(const QPoint& pt) const;
    QRect getGrooveRect() const;
    QRect getSpanRect() const;

public:
    DonutUnifiedSlider* q_ptr;

    // 基本属性
    int minimum_ = 0;
    int maximum_ = 100;
    int singleStep_ = 1;
    int pageStep_ = 10;
    Qt::Orientation orientation_ = Qt::Horizontal;
    DonutUnifiedSlider::SliderStyle sliderStyle_ = DonutUnifiedSlider::HorizontalRangeStyle;

    // Handle相关
    int handleCount_ = 2;
    QList<int> handleValues_;      // 存储各handle的值
    QList<QIcon> handleIcons_;     // 存储各handle的图标
    DonutUnifiedSlider::HandleMovementMode handleMovementMode_ = DonutUnifiedSlider::FreeMovement;
    
    // 当前状态
    DonutUnifiedSlider::HandleType activeHandle_ = DonutUnifiedSlider::NoHandle;
    DonutUnifiedSlider::HandleType hoveredHandle_ = DonutUnifiedSlider::NoHandle;
    bool dragging_ = false;
    QPoint dragStartPos_;
    int dragStartValue_ = 0;

    // 外观设置
    bool showRangeLabels_ = false;
    bool showValueLabels_ = false;
    bool showTitle_ = false;
    QString title_;
    bool showControlButtons_ = false;
    bool showConfirmButton_ = false;
    QString confirmButtonText_ = "确认";

    // UI组件
    QLabel* titleLabel_ = nullptr;
    QPushButton* upButton_ = nullptr;
    QPushButton* downButton_ = nullptr;
    QPushButton* confirmButton_ = nullptr;
    QVBoxLayout* mainLayout_ = nullptr;
    QHBoxLayout* controlLayout_ = nullptr;
    QWidget* sliderWidget_ = nullptr;

    // 缓存的矩形
    QRect grooveRect_;
    QList<QRect> handleRects_;
    QRect spanRect_;

public slots:
    void onUpButtonClicked();
    void onDownButtonClicked();
    void onConfirmButtonClicked();

private:
    Q_DECLARE_PUBLIC(DonutUnifiedSlider)
};

#endif // DONUT_UNIFIED_SLIDER_P_H
