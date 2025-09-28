#include "donut_universal_slider_option.h"

DonutUniversalSliderOption::DonutUniversalSliderOption()
    : QStyleOptionSlider()
    , sliderType(RangeSlider)
    , handleCount(TwoHandles)
    , showConfirmButton(false)
    , showTriangleButtons(false)
    , showValueLabels(true)
    , lowerValue(0)
    , upperValue(100)
    , middleValue(50)
    , lowerHovered(false)
    , upperHovered(false)
    , middleHovered(false)
    , confirmHovered(false)
    , upTriangleHovered(false)
    , downTriangleHovered(false)
    , lowerPressed(false)
    , upperPressed(false)
    , middlePressed(false)
    , confirmPressed(false)
    , upTrianglePressed(false)
    , downTrianglePressed(false)
{
}

DonutUniversalSliderOption::DonutUniversalSliderOption(const DonutUniversalSliderOption& other)
    : QStyleOptionSlider(other)
    , sliderType(other.sliderType)
    , handleCount(other.handleCount)
    , lowerHandleIcon(other.lowerHandleIcon)
    , upperHandleIcon(other.upperHandleIcon)
    , middleHandleIcon(other.middleHandleIcon)
    , title(other.title)
    , showConfirmButton(other.showConfirmButton)
    , showTriangleButtons(other.showTriangleButtons)
    , upTriangleIcon(other.upTriangleIcon)
    , downTriangleIcon(other.downTriangleIcon)
    , confirmIcon(other.confirmIcon)
    , showValueLabels(other.showValueLabels)
    , lowerValueText(other.lowerValueText)
    , upperValueText(other.upperValueText)
    , middleValueText(other.middleValueText)
    , lowerHandleRect(other.lowerHandleRect)
    , upperHandleRect(other.upperHandleRect)
    , middleHandleRect(other.middleHandleRect)
    , spanRect(other.spanRect)
    , titleRect(other.titleRect)
    , confirmButtonRect(other.confirmButtonRect)
    , upTriangleRect(other.upTriangleRect)
    , downTriangleRect(other.downTriangleRect)
    , lowerValueRect(other.lowerValueRect)
    , upperValueRect(other.upperValueRect)
    , middleValueRect(other.middleValueRect)
    , lowerValue(other.lowerValue)
    , upperValue(other.upperValue)
    , middleValue(other.middleValue)
    , lowerHovered(other.lowerHovered)
    , upperHovered(other.upperHovered)
    , middleHovered(other.middleHovered)
    , confirmHovered(other.confirmHovered)
    , upTriangleHovered(other.upTriangleHovered)
    , downTriangleHovered(other.downTriangleHovered)
    , lowerPressed(other.lowerPressed)
    , upperPressed(other.upperPressed)
    , middlePressed(other.middlePressed)
    , confirmPressed(other.confirmPressed)
    , upTrianglePressed(other.upTrianglePressed)
    , downTrianglePressed(other.downTrianglePressed)
{
}

DonutUniversalSliderOption& DonutUniversalSliderOption::operator=(const DonutUniversalSliderOption& other)
{
    if (this != &other) {
        QStyleOptionSlider::operator=(other);
        sliderType = other.sliderType;
        handleCount = other.handleCount;
        lowerHandleIcon = other.lowerHandleIcon;
        upperHandleIcon = other.upperHandleIcon;
        middleHandleIcon = other.middleHandleIcon;
        title = other.title;
        showConfirmButton = other.showConfirmButton;
        showTriangleButtons = other.showTriangleButtons;
        upTriangleIcon = other.upTriangleIcon;
        downTriangleIcon = other.downTriangleIcon;
        confirmIcon = other.confirmIcon;
        showValueLabels = other.showValueLabels;
        lowerValueText = other.lowerValueText;
        upperValueText = other.upperValueText;
        middleValueText = other.middleValueText;
        lowerHandleRect = other.lowerHandleRect;
        upperHandleRect = other.upperHandleRect;
        middleHandleRect = other.middleHandleRect;
        spanRect = other.spanRect;
        titleRect = other.titleRect;
        confirmButtonRect = other.confirmButtonRect;
        upTriangleRect = other.upTriangleRect;
        downTriangleRect = other.downTriangleRect;
        lowerValueRect = other.lowerValueRect;
        upperValueRect = other.upperValueRect;
        middleValueRect = other.middleValueRect;
        lowerValue = other.lowerValue;
        upperValue = other.upperValue;
        middleValue = other.middleValue;
        lowerHovered = other.lowerHovered;
        upperHovered = other.upperHovered;
        middleHovered = other.middleHovered;
        confirmHovered = other.confirmHovered;
        upTriangleHovered = other.upTriangleHovered;
        downTriangleHovered = other.downTriangleHovered;
        lowerPressed = other.lowerPressed;
        upperPressed = other.upperPressed;
        middlePressed = other.middlePressed;
        confirmPressed = other.confirmPressed;
        upTrianglePressed = other.upTrianglePressed;
        downTrianglePressed = other.downTrianglePressed;
    }
    return *this;
}
