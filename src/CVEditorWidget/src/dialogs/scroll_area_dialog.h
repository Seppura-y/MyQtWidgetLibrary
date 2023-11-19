#ifndef SCROLL_AREA_DIALOG_H
#define SCROLL_AREA_DIALOG_H

#include <QScrollArea>
#include <QListWidget>
#include <QStringList>
#include "dialog_base.h"

class ScrollAreaDialog : public DialogBase
{
	Q_OBJECT

public:
    ScrollAreaDialog(QWidget* parent = nullptr);
    ~ScrollAreaDialog();


    QString getFilePath();
    QString getFileName();
protected:
    virtual void initUI() override;
private:
    QString file_name_;
    QString file_path_;
};


#endif