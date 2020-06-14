#ifndef SPLASH_HPP
#define SPLASH_HPP

#include "OnStack.hpp"
#include <QPushButton>
#include <QTimer>

class Splash : public OnStack
{
    Q_OBJECT
public slots:
    void nextSlot();
public:
    Splash(QStackedWidget *stack, QWidget *parent = nullptr);
    QTimer *timer;
};

#endif // SPLASH_HPP
