#ifndef DONUT_UNIFIED_SLIDER_H
#define DONUT_UNIFIED_SLIDER_H

#include <QSlider>
#include <QPixmap>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class DonutUnifiedSliderPrivate;

class DonutUnifiedSlider : public QWidget
{
    Q_OBJECT

    // 基本属性
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int value READ value WRITE setValue)
    Q_PROPERTY(int lowerValue READ lowerValue WRITE setLowerValue)
    Q_PROPERTY(int upperValue READ upperValue WRITE setUpperValue)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(SliderStyle sliderStyle READ sliderStyle WRITE setSliderStyle)
    Q_PROPERTY(int handleCount READ handleCount WRITE setHandleCount)
    
    // 外观属性
    Q_PROPERTY(bool showRangeLabels READ showRangeLabels WRITE setShowRangeLabels)
    Q_PROPERTY(bool showValueLabels READ showValueLabels WRITE setShowValueLabels)
    Q_PROPERTY(bool showTitle READ showTitle WRITE setShowTitle)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(bool showControlButtons READ showControlButtons WRITE setShowControlButtons)
    Q_PROPERTY(bool showConfirmButton READ showConfirmButton WRITE setShowConfirmButton)
    Q_PROPERTY(QString confirmButtonText READ confirmButtonText WRITE setConfirmButtonText)

public:
    explicit DonutUnifiedSlider(QWidget* parent = nullptr);
    explicit DonutUnifiedSlider(Qt::Orientation orientation, QWidget* parent = nullptr);
    ~DonutUnifiedSlider();

    // 滑块样式枚举
    enum SliderStyle
    {
        HorizontalRangeStyle,    // 水平双handle带量程显示
        HorizontalMultiStyle,    // 水平多handle带量程显示  
        VerticalControlStyle     // 垂直单handle带控制按钮和确认键
    };
    Q_ENUM(SliderStyle)

    // Handle移动模式
    enum HandleMovementMode
    {
        FreeMovement,
        NoCrossing,
        NoOverlapping
    };
    Q_ENUM(HandleMovementMode)

    // Handle标识
    enum HandleType
    {
        NoHandle = -1,
        LowerHandle = 0,
        MiddleHandle = 1,
        UpperHandle = 2
    };
    Q_ENUM(HandleType)

    // 基本属性访问器
    int minimum() const;
    int maximum() const;
    int value() const;
    int lowerValue() const;
    int upperValue() const;
    Qt::Orientation orientation() const;
    SliderStyle sliderStyle() const;
    int handleCount() const;

    // 外观属性访问器
    bool showRangeLabels() const;
    bool showValueLabels() const;
    bool showTitle() const;
    QString title() const;
    bool showControlButtons() const;
    bool showConfirmButton() const;
    QString confirmButtonText() const;

    // Handle相关
    HandleMovementMode handleMovementMode() const;
    void setHandleMovementMode(HandleMovementMode mode);

    // Handle图标设置
    void setHandleIcon(HandleType handle, const QIcon& icon);
    void setHandleIcon(HandleType handle, const QPixmap& pixmap);
    QIcon getHandleIcon(HandleType handle) const;

    // 获取特定handle的值
    int getHandleValue(HandleType handle) const;

public slots:
    void setMinimum(int min);
    void setMaximum(int max);
    void setRange(int min, int max);
    void setValue(int value);
    void setLowerValue(int lower);
    void setUpperValue(int upper);
    void setOrientation(Qt::Orientation orientation);
    void setSliderStyle(SliderStyle style);
    void setHandleCount(int count); // 2 或 3

    // 外观设置
    void setShowRangeLabels(bool show);
    void setShowValueLabels(bool show);
    void setShowTitle(bool show);
    void setTitle(const QString& title);
    void setShowControlButtons(bool show);
    void setShowConfirmButton(bool show);
    void setConfirmButtonText(const QString& text);

    // Handle值设置
    void setHandleValue(HandleType handle, int value);
    void setSpan(int lower, int upper);
    void setTripleSpan(int lower, int middle, int upper);

    // 控制按钮操作
    void stepUp();
    void stepDown();

signals:
    void valueChanged(int value);
    void lowerValueChanged(int lower);
    void upperValueChanged(int upper);
    void handleValueChanged(HandleType handle, int value);
    void spanChanged(int lower, int upper);
    void tripleSpanChanged(int lower, int middle, int upper);
    void sliderPressed(HandleType handle);
    void sliderReleased(HandleType handle);
    void confirmClicked(int currentValue);         // 单handle确认
    void confirmClicked(int lower, int upper);     // 双handle确认
    void confirmClicked(int lower, int middle, int upper); // 三handle确认

protected:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void resizeEvent(QResizeEvent* event) override;

private slots:
    void onControlButtonClicked();
    void onConfirmButtonClicked();
    void updateLayout();

private:
    DonutUnifiedSliderPrivate* d_ptr_;
    void initializeComponents();
    void setupLayout();
    Q_DECLARE_PRIVATE(DonutUnifiedSlider)
};

#endif // DONUT_UNIFIED_SLIDER_H
