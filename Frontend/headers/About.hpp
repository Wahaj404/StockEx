#ifndef ABOUT_HPP
#define ABOUT_HPP

#include <QMainWindow>
#include <QPushButton>

#define ABOUT_SLOT void aboutSlot() {auto about = new About(this); about->showFullScreen();}
#define ABOUT_CONNECT connect(logo, SIGNAL(clicked()), this, SLOT(aboutSlot()));

class About : public QMainWindow
{
    Q_OBJECT

public slots:
    void end();
public:
    explicit About(QWidget *parent = nullptr);
};

#endif // ABOUT_HPP
