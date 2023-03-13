#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <QPushButton>
#include <QMenu>

class MenuButton : public QPushButton
{
    Q_OBJECT

public:
    MenuButton(QWidget* parent = nullptr);
    ~MenuButton();
protected:

private:
    void initUi();
private:
    QMenu* main_menu_ = nullptr;
};

#endif