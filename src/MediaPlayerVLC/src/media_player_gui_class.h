#ifndef MEDIA_PLAYER_GUI_CLASS_H
#define MEDIA_PLAYER_GUI_CLASS_H

#include <QObject>

class ControlBar;
class MainWidget;

class MediaPlayerGuiClass : public QObject
{
	Q_OBJECT

public:
	static MediaPlayerGuiClass& getInstance();

	MediaPlayerGuiClass(const MediaPlayerGuiClass& other) = delete;
	MediaPlayerGuiClass operator=(const MediaPlayerGuiClass& other) = delete;
	MediaPlayerGuiClass(QObject* parent = nullptr);
private:
public:
	void setMainWidget(MainWidget* wid) { this->main_widget_ = wid; }
	void setControlBar(ControlBar* ctrl_bar) { this->control_bar_ = ctrl_bar; }

	void connectSignalsAndSlots();

private:
	MainWidget* main_widget_ = nullptr;
	ControlBar* control_bar_ = nullptr;
};

#endif