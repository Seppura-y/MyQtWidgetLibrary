#ifndef CONTROL_BAR_H
#define CONTROL_BAR_H

#include <QWidget>
class CustomSlider;
class VolumeButton;
class QPushButton;
class QTimeEdit;

class ControlBar : public QWidget
{
    Q_OBJECT

public:
    explicit ControlBar(QWidget* parent = nullptr);
    ~ControlBar();

    void initUI();

public:
    void setTotalDuration(QTime second);
    void setCurrentDuration(QTime second);
    void setPlaying(bool status);
    void setFullscreen(bool status);
    void setStop();
    void setSoundSliderValue(int value);

protected:
    void paintEvent(QPaintEvent* ev) override;

private:
    //void onPlaySliderValueChanged();
    //void onVolumeSliderValueChanged();
private slots:

signals:
    void sigPreviousClip();
    void sigPlaying(bool);
    void sigNextClip();
    void sigStopPlaying();
    void sigFullscreen(bool);
    void sigSoundVolumeChanged(int);
    void sigControlSliderChanged(double);
    void sigOpenMediaFile(QString);
    //void sigShowOrHidePlaylist();
    //void sigPlaySeek(double dPercent);
    //void sigPlayVolume(double dPercent);
    //void sigPlayOrPause();
    //void sigStop();
    //void sigForwardPlay();
    //void sigBackwardPlay();
    //void sigShowMenu();
    //void sigShowSetting();
private:
    int total_duration_;
    double m_dLastVolumePercent;
    bool is_playing_ = false;
    bool is_fullscreen_ = false;
    bool is_stoped_ = true;

    CustomSlider*   play_slider_ = nullptr;
    VolumeButton*   volume_button_ = nullptr;
    QPushButton*    btn_play_or_pause_ = nullptr;
    QPushButton*    btn_stop_ = nullptr;
    QPushButton*    btn_next_clip_ = nullptr;
    QPushButton*    btn_previous_clip_ = nullptr;
    QPushButton*    btn_fullscreen_ = nullptr;
    QPushButton*    btn_open_file_ = nullptr;
    QTimeEdit*      t_edit_total_ = nullptr;
    QTimeEdit*      t_edit_current_ = nullptr;
};


#endif