#ifndef VOLUME_BUTTON_H
#define VOLUME_BUTTON_H

#include <QPushButton>
#include <QMenu>

#include "volume_slider_dialog.h"

class QGraphicsOpacityEffect;
class QPropertyAnimation;
class QSequentialAnimationGroup;
class QParallelAnimationGroup;

class VolumeButton : public QPushButton
{
    Q_OBJECT

public:
    VolumeButton(QWidget* parent = nullptr);
    ~VolumeButton();

    bool getMute() const
    {
        return is_mute_;
    }

    void setMute(bool mute)
    {
        is_mute_ = mute;
    }

    int getVolume()
    {
        return volume_;
    }

signals:
    void sigVolumeValueChanged(int value);
protected:
    void paintEvent(QPaintEvent* ev) override;
    void enterEvent(QEvent* ev) override;
    void mousePressEvent(QMouseEvent* ev) override;
    void timerEvent(QTimerEvent* ev) override;

private:
    void initUi();
private:
    QMenu* main_menu_ = nullptr;

    int timer_id_ = -1;
    int volume_ = 10;

    bool is_mute_ = false;
    VolumeSliderDialog* volume_slider_dialog_ = nullptr;

    QGraphicsOpacityEffect* graphics_effect_ = nullptr;
    QPropertyAnimation* animation_ = nullptr;
    QSequentialAnimationGroup* sequential_animation_group_ = nullptr;
    QParallelAnimationGroup* parallel_animation_group_ = nullptr;
};

#endif