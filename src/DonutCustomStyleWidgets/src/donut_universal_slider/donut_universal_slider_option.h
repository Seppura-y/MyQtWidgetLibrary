#ifndef DONUT_UNIVERSAL_SLIDER_OPTION_H
#define DONUT_UNIVERSAL_SLIDER_OPTION_H

#include <QStyleOptionSlider>
#include <QIcon>
#include <QString>
#include <QRect>

class DonutUniversalSliderOption : public QStyleOptionSlider
{
public:
    enum SliderType {
        RangeSlider,        // 双端滑块显示范围
        SingleSlider,       // 单端滑块显示值  
        VerticalSlider      // 垂直滑块带标题和确认按钮
    };

    enum HandleCount {
        TwoHandles,
        ThreeHandles
    };

    DonutUniversalSliderOption();
    DonutUniversalSliderOption(const DonutUniversalSliderOption& other);
    DonutUniversalSliderOption& operator=(const DonutUniversalSliderOption& other);

    // 滑块类型配置
    SliderType sliderType;
    HandleCount handleCount;
    
    // Handle图标
    QIcon lowerHandleIcon;
    QIcon upperHandleIcon;
    QIcon middleHandleIcon;
    
    // 垂直滑块专用
    QString title;
    bool showConfirmButton;
    bool showTriangleButtons;
    QIcon upTriangleIcon;
    QIcon downTriangleIcon;
    QIcon confirmIcon;
    
    // 是否显示数值标签
    bool showValueLabels;
    QString lowerValueText;
    QString upperValueText;
    QString middleValueText;
    
    // Handle位置和矩形
    QRect lowerHandleRect;
    QRect upperHandleRect;
    QRect middleHandleRect;
    QRect spanRect;
    QRect titleRect;
    QRect confirmButtonRect;
    QRect upTriangleRect;
    QRect downTriangleRect;
    QRect lowerValueRect;
    QRect upperValueRect;
    QRect middleValueRect;
    
    // 值信息
    int lowerValue;
    int upperValue;
    int middleValue;
    
    // 鼠标悬停状态
    bool lowerHovered;
    bool upperHovered;
    bool middleHovered;
    bool confirmHovered;
    bool upTriangleHovered;
    bool downTriangleHovered;
    
    // 按压状态
    bool lowerPressed;
    bool upperPressed;
    bool middlePressed;
    bool confirmPressed;
    bool upTrianglePressed;
    bool downTrianglePressed;
};

#endif // DONUT_UNIVERSAL_SLIDER_OPTION_H
