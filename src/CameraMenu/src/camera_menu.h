#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "ui_camera_menu.h"
#include "item_listwidget.h"
//#include "config_helper.h"

class ConfigHelper;

class CameraMenu : public QWidget
{
	Q_OBJECT

public:
	CameraMenu(QWidget* parent = Q_NULLPTR);
	~CameraMenu();

	int getCurrentItemIndex();

public:
	enum class ItemListType
	{
		ITEM_LIST_TYPE_NONE = -1,
		ITEM_LIST_TYPE_CAMERA = 0,
		ITEM_LIST_TYPE_LOCAL_FILE = 1,
		ITEM_LIST_TYPE_MEDIA_SRC = 2
	};
signals:
	void sigAddButtonClicked();
	void sigSetButtonClicked();
	void sigDelButtonClicked();
	void sigProcessScreenCapture();
	void sigProcessScreenCaptureFinished();

protected slots:
	void onCmrMenuAddButtonClicked();
	void onCmrMenuSetButtonClicked();
	void onCmrMenuDelButtonClicked();
protected:
	void initUi();
	void initExtendButton();
	void initItemList();
	void addListItem();
	void setListItem();
	void setListItem(ItemListType item_type, int item_index);
	void setMediaSrcItem(int item_index);
	void setLocalListItem(ItemListType item_type, int item_index);

	void deleteItem();
	void deleteItem(ItemListType item_type, int item_index);

private:
	Ui::CameraMenu ui;

	ItemListWidget* lw_camera_ = nullptr;
	ItemListWidget* lw_local_file_ = nullptr;
	ItemListWidget* lw_media_src_ = nullptr;

	QVBoxLayout* vb_camera_ = nullptr;
	QVBoxLayout* vb_local_file_ = nullptr;
	QVBoxLayout* vb_media_src_ = nullptr;
	ConfigHelper* config_tools_ = nullptr;
};

