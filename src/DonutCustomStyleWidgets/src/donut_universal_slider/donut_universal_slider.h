#ifndef DONUT_UNIVERSAL_SLIDER_H
#define DONUT_UNIVERSAL_SLIDER_H

#include <QSlider>
#include <QIcon>
#include <QString>
#include "donut_universal_slider_option.h"

class DonutUniversalSliderPrivate;

class DonutUniversalSlider : public QSlider
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DonutUniversalSlider)

    Q_PROPERTY(SliderType sliderType READ sliderType WRITE setSliderType)
    Q_PROPERTY(HandleCount handleCount READ handleCount WRITE setHandleCount)
    Q_PROPERTY(int lowerValue READ lowerValue WRITE setLowerValue)
    Q_PROPERTY(int upperValue READ upperValue WRITE setUpperValue)
    Q_PROPERTY(int middleValue READ middleValue WRITE setMiddleValue)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(bool showConfirmButton READ showConfirmButton WRITE setShowConfirmButton)
    Q_PROPERTY(bool showTriangleButtons READ showTriangleButtons WRITE setShowTriangleButtons)
    Q_PROPERTY(bool showValueLabels READ showValueLabels WRITE setShowValueLabels)

public:
    using SliderType = DonutUniversalSliderOption::SliderType;
    using HandleCount = DonutUniversalSliderOption::HandleCount;

    enum Handle {
        NoHandle,
        LowerHandle,
        UpperHandle,
        MiddleHandle,
        ConfirmButton,
        UpTriangle,
        DownTriangle
    };
    Q_ENUM(Handle)

    enum HandleMovementMode {
        FreeMovement,
        NoCrossing,
        NoOverlapping
    };
    Q_ENUM(HandleMovementMode)

    // 构造函数
    explicit DonutUniversalSlider(QWidget* parent = nullptr);
    explicit DonutUniversalSlider(SliderType type, QWidget* parent = nullptr);
    explicit DonutUniversalSlider(SliderType type, Qt::Orientation orientation, QWidget* parent = nullptr);
    ~DonutUniversalSlider();

    // 滑块类型配置
    SliderType sliderType() const;
    void setSliderType(SliderType type);

    HandleCount handleCount() const;
    void setHandleCount(HandleCount count);

    // 值访问器
    int lowerValue() const;
    int upperValue() const;
    int middleValue() const;

    // Handle图标设置
    QIcon lowerHandleIcon() const;
    void setLowerHandleIcon(const QIcon& icon);

    QIcon upperHandleIcon() const;
    void setUpperHandleIcon(const QIcon& icon);

    QIcon middleHandleIcon() const;
    void setMiddleHandleIcon(const QIcon& icon);

    // 垂直滑块专用功能
    QString title() const;
    void setTitle(const QString& title);

    bool showConfirmButton() const;
    void setShowConfirmButton(bool show);

    bool showTriangleButtons() const;
    void setShowTriangleButtons(bool show);

    QIcon upTriangleIcon() const;
    void setUpTriangleIcon(const QIcon& icon);

    QIcon downTriangleIcon() const;
    void setDownTriangleIcon(const QIcon& icon);

    QIcon confirmIcon() const;
    void setConfirmIcon(const QIcon& icon);

    // 数值标签
    bool showValueLabels() const;
    void setShowValueLabels(bool show);

    // Movement mode
    HandleMovementMode handleMovementMode() const;
    void setHandleMovementMode(HandleMovementMode mode);

public Q_SLOTS:
    void setLowerValue(int value);
    void setUpperValue(int value);
    void setMiddleValue(int value);
    void setSpan(int lower, int upper);
    void setSpan(int lower, int middle, int upper);

Q_SIGNALS:
    void lowerValueChanged(int value);
    void upperValueChanged(int value);
    void middleValueChanged(int value);
    void spanChanged(int lower, int upper);
    void spanChanged(int lower, int middle, int upper);
    void handlePressed(Handle handle);
    void handleReleased(Handle handle);
    void confirmClicked();

protected:
    // 事件处理
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void leaveEvent(QEvent* event) override;

    // Style option初始化
    virtual void initStyleOption(DonutUniversalSliderOption* option) const;

private:
    Q_DISABLE_COPY(DonutUniversalSlider)
    DonutUniversalSliderPrivate* const d_ptr;
};

Q_DECLARE_METATYPE(DonutUniversalSlider::SliderType)
Q_DECLARE_METATYPE(DonutUniversalSlider::HandleCount)
Q_DECLARE_METATYPE(DonutUniversalSlider::Handle)
Q_DECLARE_METATYPE(DonutUniversalSlider::HandleMovementMode)

#endif // DONUT_UNIVERSAL_SLIDER_H
