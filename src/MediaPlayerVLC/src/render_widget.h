#pragma once

#include <QtWidgets/QWidget>

#ifdef _WIN32
#include <basetsd.h>
typedef SSIZE_T ssize_t;
#endif

#include "vlc/vlc.h"

class RenderWidget : public QWidget
{
    Q_OBJECT

public:
    RenderWidget(QWidget *parent = nullptr);
    ~RenderWidget();

    void openMediaFile(QString file_path);
    void setMediaPause(bool status);
signals:
    void sigOpenMediaFileSuccess();
public slots:
    void onOpenMediaFile(QString file_path);
protected:
    void mousePressEvent(QMouseEvent* ev) override;
private:

    libvlc_instance_t* vlc_instance_ = nullptr;
    libvlc_media_player_t* vlc_media_player_ = nullptr;
    libvlc_media_t* vlc_media_ = nullptr;

    bool media_pause_ = false;
};
