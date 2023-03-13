#include "menu_button.h"

#include "config_helper.h"

#include <QAction>
#include <QFileDialog>

MenuButton::MenuButton(QWidget *parent) : QPushButton(parent)
{
    //this->setAttribute(Qt::WA_StyledBackground);

    main_menu_ = new QMenu;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // File Menu
    QMenu* file_menu = new QMenu;
    file_menu->setIcon(QIcon(":/menu_button/res/icons/file.png"));
    file_menu->setTitle("file");

    QList<QAction*> file_menu_actions;

    QAction* act_open_file = new QAction(QIcon(":/menu_button/res/icons/file.png"), "open files", this);
    act_open_file->setShortcut(QKeySequence("Ctrl+O"));

    QAction* act_open_folder = new QAction("open folder", this);
    QAction* act_open_url = new QAction("open url", this);

    file_menu_actions << act_open_file << act_open_folder << act_open_url;
    file_menu->addActions(file_menu_actions);
    file_menu->setStyleSheet(ConfigHelper::GetInstance()->GetQssString(":/menu_button/res/css/menu_button.css"));

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    QAction* act_play = new QAction(QIcon(":/menu_button/res/icons/play.png"), "play", this);
    QAction* act_tools = new QAction(QIcon(":/menu_button/res/icons/tools.png"), "tools", this);


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Options Menu
    QMenu* options_menu = new QMenu;
    options_menu->setTitle("options");
    options_menu->setIcon(QIcon(":/menu_button/res/icons/set.png"));
    QList<QAction*> options_menu_actions;

    QAction* act_sys_option = new QAction("system options", this);
    QAction* act_play_option = new QAction("play options", this);
    QAction* act_subtitle_option = new QAction("subtitle options", this);
    options_menu_actions << act_sys_option << act_play_option << act_subtitle_option;
    options_menu->addActions(options_menu_actions);
    options_menu->setStyleSheet(ConfigHelper::GetInstance()->GetQssString(":/menu_button/res/css/menu_button.css"));


    QAction* act_exit = new QAction(QIcon(":/menu_button/res/icons/exit.png"), "exit", this);


    connect(act_open_file, &QAction::triggered, [=] {
        QString file_name = QFileDialog::getOpenFileName(this,
        "please select media files",
        "D:/",
        "files(*.mp4 *.flv)");

        if (file_name.isEmpty())
        {
            return;
        }
    });

    main_menu_->addMenu(file_menu);
    main_menu_->addAction(act_play);
    main_menu_->addAction(act_tools);
    main_menu_->addSeparator();
    main_menu_->addMenu(options_menu);
    main_menu_->addSeparator();
    main_menu_->addAction(act_exit);

    main_menu_->setStyleSheet(ConfigHelper::GetInstance()->GetQssString(":/menu_button/res/css/menu_button.css"));

    this->setMenu(main_menu_);
    this->setStyleSheet(ConfigHelper::GetInstance()->GetQssString(":/menu_button/res/css/menu_button.css"));
}

MenuButton::~MenuButton()
{
    if (main_menu_)
    {
        delete main_menu_;
    }
}

void MenuButton::initUi()
{

}
