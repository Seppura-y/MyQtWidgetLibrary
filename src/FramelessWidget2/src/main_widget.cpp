#include "main_widget.h"
#include <QVBoxLayout>
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent)
    : FramelessWidget(parent)
{
    initUI();
}

void MainWidget::onClose()
{
    this->close();
    return;

    QMessageBox::StandardButton _exit = QMessageBox::warning(this, "提示", "确定要退出吗", 
        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    if (_exit == QMessageBox::Yes)
    {
        this->close();
    }
}

void MainWidget::initUI()
{
    title_bar_ = new TitleBar(this);

    QWidget* w = new QWidget(this);
    w->setMinimumSize(800, 600);

    QVBoxLayout* h_layout = new QVBoxLayout(this);
    h_layout->addWidget(title_bar_);
    h_layout->addWidget(w);

    h_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(h_layout);

    connect(title_bar_, &TitleBar::sigClose, this, &MainWidget::onClose);
}


