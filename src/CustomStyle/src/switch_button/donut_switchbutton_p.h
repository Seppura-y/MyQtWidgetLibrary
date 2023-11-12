#ifndef DONUT_SWITCHBUTTON_P_H
#define DONUT_SWITCHBUTTON_P_H

#include <QObject>

// class MySwitchButtonPrivate :
// DonutSwitchButton ��������࣬ ����ʵ��Դ��/�����Ƽ���, ͨ���̳��� ���Զ���_Private�� ����
// �����Զ���ؼ�,û�м̳��� QObjectPrivate ֮���, ʹ�� Q_Q Q_D ʱ�򣬻ᱨ����Ҫ�Լ����� q_fun() ����
// 
// Qt �Դ��� QPushButtonPrivate�� QPushButton ʵ��



//#define Q_DECLARE_PUBLIC(Class)                                    \
//    inline Class* q_func() noexcept { return static_cast<Class *>(q_ptr); } \
//    inline const Class* q_func() const noexcept { return static_cast<const Class *>(q_ptr); } \
//    friend class Class;

class DonutSwitchButtonPrivate : public QObjectData
{
public:
    explicit DonutSwitchButtonPrivate();
    ~DonutSwitchButtonPrivate();

    void init();
    bool setSwitchCheck(bool check);
    bool switchCheck();

private:
    bool check;

public:
    //DonutSwitchButton* q_ptr;
    Q_DECLARE_PUBLIC(DonutSwitchButton)

    //inline DonutSwitchButton* q_func() noexcept { return static_cast<DonutSwitchButton*>(q_ptr); } \
    //inline const DonutSwitchButton* q_func() const noexcept { return static_cast<const DonutSwitchButton*>(q_ptr); } \
    //friend class DonutSwitchButton;
};

#endif
