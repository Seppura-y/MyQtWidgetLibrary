#include "round_widget.h"
#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>

#include "media_src_dialog.h"
#include "config_helper.h"

#include "dialog_base.h"
#include "scroll_area_dialog.h"
#include "triangle_dialog.h"

RoundWidget::RoundWidget(QWidget* parent) : QWidget(parent)
{
    // to make a round widget
    // must set these properties before 
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);

    // method 2
    this->setStyleSheet("QWidget{background-color:gray;border-radius:30px;}");

    QPushButton* pb = new QPushButton(this);
    pb->setFixedSize(32, 32);
    pb->setText("Open");
    pb->move(this->width(), this->height());
    pb->setStyleSheet(ConfigHelper::getInstance()->getQssString(":/resources/res/css/button.css"));

    QObject::connect(pb, &QPushButton::clicked, [=]
        {

            TriangleDialog* dialog = new TriangleDialog(800, 200, this);
            int triangle_start_x = 60;

            dialog->setTrianglePosition(triangle_start_x, 20, 12);

            // 设置三角窗口的弹出位置， 有Qt::Popup属性
            QPoint p1 = pb->mapToGlobal(QPoint(0, 0));  //按钮左上角相对于桌面的绝对位置
            QRect rect1 = pb->rect();

            int x = p1.x() + rect1.width() / 2 - triangle_start_x - 20 / 2;
            int y = p1.y() + rect1.height() + 1 - 15;
            dialog->move(x, y);

            //dialog->show();

            //ScrollAreaDialog* dialog = new ScrollAreaDialog();
            //MediaFileDialog* dialog = new MediaFileDialog();
            for (;;)
            {
                if (dialog->exec() == QDialog::Accepted)
                {
                    qDebug() << "accepted";
                }
                else if (dialog->close())
                {
                    qDebug() << "close";
                }
                delete dialog;
                break;
            }
        }
    );

}

RoundWidget::~RoundWidget()
{
}


// method 1 : 
//void RoundWidget::paintEvent(QPaintEvent *ev)
//{
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setBrush(QBrush(QColor(60, 60, 60)));
//    painter.setPen(Qt::transparent);
//    QRect rect = this->rect();
//    painter.drawRoundedRect(rect, 15, 15);
//}


// method 2 : 
void RoundWidget::paintEvent(QPaintEvent* ev)
{
    QStyleOption option;
    option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
    QWidget::paintEvent(ev);
}

void RoundWidget::initUI()
{
    
}
