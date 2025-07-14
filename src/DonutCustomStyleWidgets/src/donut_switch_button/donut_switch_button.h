#ifndef DONUT_SWITCHBUTTON_H
#define DONUT_SWITCHBUTTON_H

#include <QAbstractButton>
#include <QStyleOption>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QFont>

class QStyleOptionButton;

class DonutSwitchButtonPrivate;
class DonutSwitchButton : public QAbstractButton
{
    Q_OBJECT
    
    // Basic properties
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked NOTIFY toggled)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration)
    
    // Color properties
    Q_PROPERTY(QColor onColor READ onColor WRITE setOnColor)
    Q_PROPERTY(QColor offColor READ offColor WRITE setOffColor)
    Q_PROPERTY(QColor knobColor READ knobColor WRITE setKnobColor)
    Q_PROPERTY(QColor disabledColor READ disabledColor WRITE setDisabledColor)
    Q_PROPERTY(QColor onTextColor READ onTextColor WRITE setOnTextColor)
    Q_PROPERTY(QColor offTextColor READ offTextColor WRITE setOffTextColor)
    Q_PROPERTY(QColor knobTextColor READ knobTextColor WRITE setKnobTextColor)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    
    // Shape properties
    Q_PROPERTY(KnobShape knobShape READ knobShape WRITE setKnobShape)
    Q_PROPERTY(TrackShape trackShape READ trackShape WRITE setTrackShape)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth)
    Q_PROPERTY(int trackRadius READ trackRadius WRITE setTrackRadius)
    Q_PROPERTY(int knobRadius READ knobRadius WRITE setKnobRadius)
    
    // Text properties
    Q_PROPERTY(QString onText READ onText WRITE setOnText)
    Q_PROPERTY(QString offText READ offText WRITE setOffText)
    Q_PROPERTY(QString knobText READ knobText WRITE setKnobText)
    Q_PROPERTY(bool showText READ showText WRITE setShowText)
    Q_PROPERTY(bool showKnobText READ showKnobText WRITE setShowKnobText)
    Q_PROPERTY(QFont textFont READ textFont WRITE setTextFont)
    Q_PROPERTY(QFont knobTextFont READ knobTextFont WRITE setKnobTextFont)
    
    // Layout properties
    Q_PROPERTY(int trackMargin READ trackMargin WRITE setTrackMargin)
    Q_PROPERTY(int knobMargin READ knobMargin WRITE setKnobMargin)

public:
    enum KnobShape {
        CircleKnob,
        RoundedRectKnob,
        SquareKnob,
        DiamondKnob,
        CustomKnob
    };
    Q_ENUM(KnobShape)

    enum TrackShape {
        RoundedTrack,
        RectangleTrack,
        EllipseTrack,
        CustomTrack
    };
    Q_ENUM(TrackShape)

    explicit DonutSwitchButton(QWidget* parent = nullptr);
    ~DonutSwitchButton();

    // Basic properties
    bool isChecked() const;
    int animationDuration() const;
    
    // Color properties
    QColor onColor() const;
    QColor offColor() const;
    QColor knobColor() const;
    QColor disabledColor() const;
    QColor onTextColor() const;
    QColor offTextColor() const;
    QColor knobTextColor() const;
    QColor borderColor() const;
    
    // Shape properties
    KnobShape knobShape() const;
    TrackShape trackShape() const;
    int borderWidth() const;
    int trackRadius() const;
    int knobRadius() const;
    
    // Text properties
    QString onText() const;
    QString offText() const;
    QString knobText() const;
    bool showText() const;
    bool showKnobText() const;
    QFont textFont() const;
    QFont knobTextFont() const;
    
    // Layout properties
    int trackMargin() const;
    int knobMargin() const;

public slots:
    void setChecked(bool checked);
    void setAnimationDuration(int duration);
    
    // Color setters
    void setOnColor(const QColor& color);
    void setOffColor(const QColor& color);
    void setKnobColor(const QColor& color);
    void setDisabledColor(const QColor& color);
    void setOnTextColor(const QColor& color);
    void setOffTextColor(const QColor& color);
    void setKnobTextColor(const QColor& color);
    void setBorderColor(const QColor& color);
    
    // Shape setters
    void setKnobShape(KnobShape shape);
    void setTrackShape(TrackShape shape);
    void setBorderWidth(int width);
    void setTrackRadius(int radius);
    void setKnobRadius(int radius);
    
    // Text setters
    void setOnText(const QString& text);
    void setOffText(const QString& text);
    void setKnobText(const QString& text);
    void setShowText(bool show);
    void setShowKnobText(bool show);
    void setTextFont(const QFont& font);
    void setKnobTextFont(const QFont& font);
    
    // Layout setters
    void setTrackMargin(int margin);
    void setKnobMargin(int margin);
    
    void toggle();

signals:
    void toggled(bool checked);
    void clicked(bool checked = false);

public:
    virtual QSize sizeHint() const override;
    virtual QSize minimumSizeHint() const override;

protected:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void resizeEvent(QResizeEvent* event) override;
    virtual void enterEvent(QEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;

private slots:
    void onAnimationValueChanged();
    void onAnimationFinished();

private:
    void initStyleOption(QStyleOptionButton* opt) const;
    void updateKnobPosition();
    void drawTrack(QPainter& painter, const QRectF& rect, const QColor& color);
    void drawKnob(QPainter& painter, const QRectF& rect, const QColor& color);
    void drawText(QPainter& painter);

    DonutSwitchButtonPrivate* d_ptr_;
    friend class DonutSwitchButtonPrivate;
};

#endif