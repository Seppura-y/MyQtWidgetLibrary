#include "media_player_gui_class.h"
#include "main_widget.h"
#include "control_bar.h"

MediaPlayerGuiClass& MediaPlayerGuiClass::getInstance()
{
    static MediaPlayerGuiClass media_player_gui_class;
    return media_player_gui_class;
}

void MediaPlayerGuiClass::connectSignalsAndSlots()
{
    if (main_widget_ && control_bar_)
    {
        QObject::connect(main_widget_, &MainWidget::sigUpArrowKeyPressed,   control_bar_, &ControlBar::onVolumeAddByKeyboard);
        QObject::connect(main_widget_, &MainWidget::sigDownArrowKeyPressed, control_bar_, &ControlBar::onVolumeSubByKeyboard);
        QObject::connect(main_widget_, &MainWidget::sigLeftArrowKeyPressed, control_bar_, &ControlBar::onSeekBackwardByKeyboard);
        QObject::connect(main_widget_, &MainWidget::sigRightArrowKeyPressed, control_bar_, &ControlBar::onSeekForwardByKeyboard);
        QObject::connect(main_widget_, &MainWidget::sigSpaceKeyPressed, control_bar_, &ControlBar::onPauseByKeyboard);
        QObject::connect(main_widget_, &MainWidget::sigMKeyPressed,   control_bar_, &ControlBar::onMuteByKeyboard);
    }
}

MediaPlayerGuiClass::MediaPlayerGuiClass(QObject* parent) : QObject(parent)
{

}
