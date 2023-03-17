#pragma once

#include <QWidget>

// #include "canvas/canvas_scene.h"
// #include "canvas/canvas_view.h"
// #include "canvas/canvas_widget.h"
#include "ui_display_widget.h"

class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QToolButton;
class QPushButton;
class QButtonGroup;
class QAbstractButton;
class QPropertyAnimation;
class VolumeButton;
class RenderWidget;
class ControlBar;

class DisplayWidget : public QWidget
{
	Q_OBJECT

public:
	DisplayWidget(QWidget *parent = Q_NULLPTR);
	~DisplayWidget();


protected:
	void resizeEvent(QResizeEvent* ev) override;
	void dragEnterEvent(QDragEnterEvent* ev)override;
	void dropEvent(QDropEvent* ev) override;
	bool eventFilter(QObject* watched, QEvent* event) override;
private:
	void initTitle();
	void initContent();
	void initToolBar();
	void initControlBar();

private slots:
	void onPanelChanged(bool is_checked);
	void onTitleButtonToggled(QAbstractButton* bt, bool checked);
	void onToolBarButtonToggled(QAbstractButton* bt, bool checked);
	void onSoundVolumeValueChanged(int value);
private:
	Ui::DisplayWidget ui;

	////////////////////////Title Bar/////////////////////////////
	QPushButton* btn_screen_cap_ = nullptr;
	QPushButton* btn_cam_cap_ = nullptr;
	QPushButton* btn_web_cam_ = nullptr;
	QButtonGroup* btn_group_title_ = nullptr;
	QHBoxLayout* layout_title_ = nullptr;

	////////////////////////Tool Bar/////////////////////////////
	QPushButton* btn_split_1_ = nullptr;
	QPushButton* btn_split_4_ = nullptr;
	QPushButton* btn_split_9_ = nullptr;
	QPushButton* btn_split_16_ = nullptr;
	QPushButton* btn_split_25_ = nullptr;
	QPushButton* btn_split_custom_ = nullptr;
	QButtonGroup* btn_group_toolbar_ = nullptr;

	QPushButton* btn_start_push_ = nullptr;
	QPushButton* btn_push_setting_ = nullptr;
	QPushButton* btn_push_info_ = nullptr;
	QHBoxLayout* layout_toolbar_ = nullptr;

	QPushButton* btn_add_source_ = nullptr;

	VolumeButton* btn_volume_ = nullptr;

	int last_split_id_ = 0;
	//////////////////////Render Widget//////////////////////
	RenderWidget* render_widget_ = nullptr;
	bool is_playing_ = false;


	ControlBar* control_bar_ = nullptr;
	
	////////////////////////canvas/////////////////////////////
	//CanvasWidget* canvas_wid_ = nullptr;
	// CanvasView* canvas_view_ = nullptr;
	// CanvasScene* canvas_scene_ = nullptr;

	///////////////////////audio recorder///////////////////


	///////////get merge picture from canvas////////////


	///////////////////////publisher//////////////////////



};
