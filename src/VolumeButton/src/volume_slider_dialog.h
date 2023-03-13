#ifndef VOLUME_SLIDER_DIALOG_H
#define VOLUME_SLIDER_DIALOG_H

#include <QSlider>
#include <QDialog>

class VolumeSliderDialog : public QDialog
{
	Q_OBJECT

public:
	VolumeSliderDialog(QWidget *parent = nullptr);
	~VolumeSliderDialog();

	void setSliderValue(int value)
	{
		slider_->setValue(value);
	}

protected:
	bool event(QEvent* event) override;

signals:
	void sigSliderValueChanged(int value);

private:
	QSlider* slider_ = nullptr;
};

#endif