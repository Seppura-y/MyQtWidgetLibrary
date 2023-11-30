#include <QWidget>

#include <QPropertyAnimation>
#include <QPainter>
#include <QMouseEvent>

// ������Ч����SwicthButton , ��paintEvent��ʵ����۶������Զ���style
class SwitchButton : public QWidget
{
    Q_OBJECT
        // ����һ�����ԣ����ڿ��ƻ����λ��
        Q_PROPERTY(int pos READ pos WRITE setPos)
public:
    SwitchButton(QWidget* parent = nullptr) : QWidget(parent)
    {
        setFixedSize(50, 25);
        setFocusPolicy(Qt::NoFocus);
        setAcceptDrops(false);
        m_checked = false;
        m_pos = 0;
        m_animation = new QPropertyAnimation(this, "pos");
        m_animation->setDuration(300);
        // ���ö����Ļ�������ΪInOutQuad
        m_animation->setEasingCurve(QEasingCurve::InOutQuad);
        connect(this, &SwitchButton::clicked, this, &SwitchButton::toggle);
    }

    bool isChecked() const
    {
        return m_checked;
    }

    int pos() const
    {
        return m_pos;
    }

    void setPos(int pos)
    {
        if (m_pos != pos)
        {
            m_pos = pos;
            update();
        }
    }

signals:
    void stateChanged(bool checked);
    void clicked();

public slots:
    void toggle()
    {
        if (!m_checked)
        {
            m_checked = true;
            m_animation->setStartValue(0);
            m_animation->setEndValue(25);
            m_animation->start();
        }
        else
        {
            m_checked = false;
            m_animation->setStartValue(25);
            m_animation->setEndValue(0);
            m_animation->start();
        }
        emit stateChanged(m_checked);
    }

protected:
    void paintEvent(QPaintEvent* event) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        // ����Ϊƽ��ģʽ
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        // ����Ϊ���ģʽ
        painter.setBrush(Qt::SolidPattern);
        painter.setPen(Qt::NoPen);
        if (!m_checked)
        {
            painter.setBrush(QColor(200, 200, 200));
            painter.drawRoundedRect(rect(), 12.5, 12.5);
            painter.setBrush(Qt::white);
            painter.drawEllipse(m_pos, 0, 25, 25);
        }
        else
        {
            painter.setBrush(QColor(0, 200, 0));
            painter.drawRoundedRect(rect(), 12.5, 12.5);
            painter.setBrush(Qt::white);
            painter.drawEllipse(m_pos, 0, 25, 25);
        }
    }

    void mouseReleaseEvent(QMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            emit clicked();
        }
    }

private:
    bool m_checked;
    int m_pos;
    QPropertyAnimation* m_animation;
};
