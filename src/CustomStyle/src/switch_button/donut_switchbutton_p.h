#ifndef DONUT_SWITCHBUTTON_P_H
#define DONUT_SWITCHBUTTON_P_H

#include <QObject>

// class MySwitchButtonPrivate :
// DonutSwitchButton 类的数据类， 便于实现源码/二进制兼容, 通常继承于 “自定义_Private” 的类
// 若是自定义控件,没有继承于 QObjectPrivate 之类的, 使用 Q_Q Q_D 时候，会报错，需要自己定义 q_fun() 函数
// 
// Qt 自带的 QPushButtonPrivate， QPushButton 实现



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
