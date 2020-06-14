#include "About.hpp"

About::About(QWidget *parent) : QMainWindow(parent)
{
    auto button = new QPushButton(this);
    button->setIcon(QPixmap("Assets\\About.png"));
    button->setIconSize(QSize(1920, 1080));
    button->resize(1920, 1080);
    button->setStyleSheet("background-color: black");
    connect(button, SIGNAL(clicked()), this, SLOT(end()));
    setCentralWidget(button);
}

void About::end() {
    close();
}
