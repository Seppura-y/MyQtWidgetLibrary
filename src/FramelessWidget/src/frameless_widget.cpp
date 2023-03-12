#include "frameless_widget.h"
#include "ui_frameless_widget.h"

#include "title.h"

FramelessWidget::FramelessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FramelessWidget)
{
    ui->setupUi(this);

    initUi();
}

FramelessWidget::~FramelessWidget()
{
    delete ui;
}

void FramelessWidget::initUi()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    this->layout()->setContentsMargins(0, 0, 0, 0);
    initTitle();
}

void FramelessWidget::initTitle()
{
    title_ = new Title();
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(title_);
    ui->title_wid->setLayout(layout);
    //title_->setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    title_->setGeometry(0, 0, this->width(), title_->height());

    connect(title_, &Title::sigCloseBtnClicked, this, [this] {
        this->close();
        });

    connect(title_, &Title::sigMaxBtnClicked, this, [this] {
        if (this->isMaximized())
        {
            this->showNormal();
            emit sigWindowNormal();
        }
        else
        {
            if (maximized_flag_ && is_maximized_init_)
            {
                this->setGeometry(maximized_rect_);
                this->setWindowState(Qt::WindowMaximized);
                maximized_flag_ = false;
            }
            else
            {
                this->showMaximized();
            }

            emit sigWindowMaximized();

            if (!is_maximized_init_)
            {
                is_maximized_init_ = true;
                maximized_rect_ = this->geometry();
            }
        }
        });

    connect(title_, &Title::sigMiniBtnClicked, this, [this] {
        this->showMinimized();
        });

    connect(title_, &Title::sigTitleDoubleClicked, this, [this] {
        if (this->isMaximized())
        {
            this->showNormal();
            emit sigWindowNormal();
        }
        else
        {
            if (maximized_flag_ && is_maximized_init_)
            {
                this->setGeometry(maximized_rect_);
                this->setWindowState(Qt::WindowMaximized);
                maximized_flag_ = false;
            }
            else
            {
                this->showMaximized();
            }

            emit sigWindowMaximized();

            if (!is_maximized_init_)
            {
                is_maximized_init_ = true;
                maximized_rect_ = this->geometry();
            }
        }
        });

    //ui->title_wid = title_;
    //ui->title_wid->show();
    this->installEventFilter(title_);
}
