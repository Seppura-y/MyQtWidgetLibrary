#pragma once
#include <QDialog>
#include <QTabWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QButtonGroup>
#include <QCheckBox>
#include <QLineEdit>

#include "ui_desktop_tab.h"
#include "dialog_title.h"

enum capture_type
{
    CAP_TYPE_VIDEO = 0,
    CAP_TYPE_AUDIO
};

class DialogContentTabBase : public QWidget
{
    Q_OBJECT

public:
    DialogContentTabBase(QWidget* parent = nullptr);
    ~DialogContentTabBase(){}
protected:
    void paintEvent(QPaintEvent* ev) override;
private:

};

class FileTab : public DialogContentTabBase
{
    Q_OBJECT
public:
    explicit FileTab(QWidget* parent = nullptr);

public:
    QLineEdit* edit;
    QPushButton* btnBrowse;
};

class CaptureTab : public DialogContentTabBase
{
    Q_OBJECT
public:
    explicit CaptureTab(int tab_index = 0, QWidget* parent = nullptr, capture_type type = CAP_TYPE_VIDEO);

protected slots:

public:
    QComboBox* cb_dev_name_ = nullptr;
    QComboBox* cb_dev_resolution_ = nullptr;
    capture_type cap_type_;

    int tab_index_ = 0;
};

class DesktopTab : public DialogContentTabBase
{
    Q_OBJECT
public:
    explicit DesktopTab(int tab_index = 0, QWidget* parent = nullptr, capture_type type = CAP_TYPE_VIDEO);
    ~DesktopTab();

signals:
    void sigDeskTopTabProcessingScreenCap();
    void sigDeskTopTabProcessingScreenCapFinshed();
protected slots:
    //void onCaptureAreaChecked();
    void onCaptureAreaChecked(int index);
protected:
    void connectSignals();
public:
    QButtonGroup* group_type_ = nullptr;
    QButtonGroup* group_size_ = nullptr;
    QCheckBox* ck_dxgi_ = nullptr;
    QCheckBox* ck_dshow_ = nullptr;
    QCheckBox* ck_gdi_ = nullptr;
    QCheckBox* ck_full_screen_ = nullptr;
    QCheckBox* ck_capture_area_ = nullptr;

    QLineEdit* le_width_ = nullptr;
    QLineEdit* le_height_ = nullptr;
    QLineEdit* le_x_ = nullptr;
    QLineEdit* le_y_ = nullptr;
    capture_type cap_type_;

    QPushButton* pb_ok_ = nullptr;
    QPushButton* pb_cancel_ = nullptr;

    QRect screen_rect_;

    int tab_index_ = 0;

private:
    Ui::DesktopTab ui;
};
