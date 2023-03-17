#include <QSlider>

class CustomSlider : public QSlider
{
    Q_OBJECT

public:
    CustomSlider(QWidget* parent = nullptr);
    ~CustomSlider();
protected:
    void mousePressEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);
signals:
    void sigCustomSliderValueChanged(int value);

private:
    bool is_pressed_ = false;
};