#include "Splash.hpp"

Splash::Splash(QStackedWidget *stack, QWidget *parent)
    :OnStack(stack, parent)
{
    auto logo = new QPushButton(this);
    logo->setIcon(QPixmap("Assets\\Logo.jpg"));
    logo->setIconSize(QSize(640, 640));
    logo->setGeometry(0, 0, 0, 0);
    logo->resize(logo->icon().actualSize(QSize(640, 640)));
    logo->setStyleSheet("background-color: black;");
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Splash::nextSlot);
    timer->start(3000);
    setCentralWidget(logo);
}

void Splash::nextSlot() {
    next();
    timer->stop();
}
