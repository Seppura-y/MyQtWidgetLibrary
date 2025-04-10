#ifndef VOLUME_SLIDER_DIALOG_H
#define VOLUME_SLIDER_DIALOG_H

#include <QDialog>

class CustomSlider;

class VolumeSliderDialog : public QDialog
{
	Q_OBJECT

public:
	VolumeSliderDialog(QWidget *parent = nullptr);
	~VolumeSliderDialog();

	void setSliderValue(int value);

protected:
	bool event(QEvent* event) override;

signals:
	void sigSliderValueChanged(int value);

private:
	CustomSlider* slider_ = nullptr;
};

#endif