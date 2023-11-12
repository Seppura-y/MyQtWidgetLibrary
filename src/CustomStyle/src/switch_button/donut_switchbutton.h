#ifndef DONUT_SWITCHBUTTON_H
#define DONUT_SWITCHBUTTON_H

#include <QAbstractButton>
#include <QStyleOption>

// qglobal.h
// 
//#define Q_CAST_IGNORE_ALIGN(body) QT_WARNING_PUSH QT_WARNING_DISABLE_GCC("-Wcast-align") body QT_WARNING_POP
//#define Q_DECLARE_PRIVATE(Class) \
//    inline Class##Private* d_func() noexcept \
//    { Q_CAST_IGNORE_ALIGN(return reinterpret_cast<Class##Private *>(qGetPtrHelper(d_ptr));) } \
//    inline const Class##Private* d_func() const noexcept \
//    { Q_CAST_IGNORE_ALIGN(return reinterpret_cast<const Class##Private *>(qGetPtrHelper(d_ptr));) } \
//    friend class Class##Private;

class QStyleOptionButton;

class DonutSwitchButtonPrivate;
class DonutSwitchButton : public QAbstractButton
{
    Q_OBJECT
public:
    explicit DonutSwitchButton(QWidget* parent = nullptr);
    ~DonutSwitchButton();

    // QWidget interface
public:
    virtual QSize sizeHint() const override;

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    void initStyleOption(QStyleOptionButton* opt) const;
    Q_DECLARE_PRIVATE(DonutSwitchButton)
    //inline DonutSwitchButtonPrivate* d_func() noexcept
    //{
    //    Q_CAST_IGNORE_ALIGN(return reinterpret_cast<DonutSwitchButtonPrivate*>(qGetPtrHelper(d_ptr));)
    //}

    //inline const DonutSwitchButtonPrivate* d_func() const noexcept
    //{
    //    Q_CAST_IGNORE_ALIGN(return reinterpret_cast<const DonutSwitchButtonPrivate*>(qGetPtrHelper(d_ptr));)
    //}
    //friend class DonutSwitchButtonPrivate;
};

#endif