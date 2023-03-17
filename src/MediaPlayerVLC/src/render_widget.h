#ifndef RENDER_WIDGET_H
#define RENDER_WIDGET_H

#include <QWidget>
#include <QTime>
#include <memory>

#include "vlc_manager.h"

class RenderWidget : public QWidget
{
    Q_OBJECT

public:
    RenderWidget(QWidget *parent = nullptr);
    ~RenderWidget();

    void openMediaFile(QString file_path);
    void setMediaPause(bool pause);
    void setSeekPos(double value);
    void setSoundVolume(int value);
    void setMediaStop();
signals:
    void sigOpenMediaFileSuccess();
    void sigUpdateTotalDuration(QTime time);
    void sigUpdateCurrentTimePos(QTime time);
    void sigUpdateCurrentSoundVolume(int value);
    void sigRenderMediaEndReached();
public slots:
    //void onOpenMediaFile(QString file_path);
protected:
    void mousePressEvent(QMouseEvent* ev) override;
    void paintEvent(QPaintEvent* ev) override;
private:

    bool media_pause_ = false;

    //std::unique_ptr <VlcManager> render_manager_;
    VlcManager* render_manager_ = nullptr;
};

#endif