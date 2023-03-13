#ifndef VOLUME_BUTTON_H
#define VOLUME_BUTTON_H

#include <QPushButton>
#include <QMenu>

#include "volume_slider_dialog.h"

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

    bool is_mute_ = false;
    VolumeSliderDialog* volume_slider_dialog_ = nullptr;
};

#endif