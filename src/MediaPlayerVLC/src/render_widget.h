#ifndef RENDER_WIDGET_H
#define RENDER_WIDGET_H

#include <QWidget>
#include <QTime>
#include <memory>
#include <QTimer>
#include <QAbstractNativeEventFilter>


#include "vlc_manager.h"

class RenderWidget : public QWidget/*, public QAbstractNativeEventFilter*/
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

    bool getFullscreen();
signals:
    void sigOpenMediaFileSuccess();
    void sigUpdateTotalDuration(QTime time);
    void sigUpdateCurrentTimePos(QTime time);
    void sigUpdateCurrentSoundVolume(int value);
    void sigRenderMediaEndReached();

    void sigShowFullscreen(bool);
public slots:
    //void onOpenMediaFile(QString file_path);
    
private slots:
    void onMouseHideTimeout();

protected:
    void paintEvent(QPaintEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;
    //void mouseDoubleClickEvent(QMouseEvent* ev) override;
    //bool nativeEventFilter(const QByteArray& eventType, void* message, long* result) override;

private:
    void initVlcManager();
private:

    bool media_pause_ = false;

    //std::unique_ptr <VlcManager> render_manager_;
    VlcManager* render_manager_ = nullptr;

    QTimer timer_mouse_hide_;
    QTimer timer_fullscreen_;
    bool is_mouse_hide_ = false;
    bool is_fullscreen_ = false;
};

#endif