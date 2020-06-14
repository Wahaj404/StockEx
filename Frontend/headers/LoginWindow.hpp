#ifndef __LOGINWINDOW_HPP__
#define __LOGINWINDOW_HPP__

#include "OnStack.hpp"

#include <iostream>
using std::cerr;
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QLabel>
#include <QGridLayout>
#include <QFormLayout>

class LoginWindow : public OnStack
{
    Q_OBJECT

public slots:
    ABOUT_SLOT
    void loginFunction();

public:
    LoginWindow(QStackedWidget* stack, QWidget *parent = nullptr);

    QPushButton *button;
    QLineEdit *cnicBox;
    QLineEdit *passwordBox;

    ~LoginWindow();
};

#endif // __LOGINWINDOW_HPP__
