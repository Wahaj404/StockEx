#ifndef __ONSTACK_HPP__
#define __ONSTACK_HPP__

#include "RealTime.hpp"
#include "About.hpp"

#include <QMainWindow>
#include <QStackedWidget>
#include <QMessageBox>

QString decString(int num);

#define TryError(func)                                    \
    try                                                   \
    {                                                     \
        func;                                             \
    }                                                     \
    catch (std::exception & ex)                           \
    {                                                     \
        QMessageBox::warning(this, "StockEx", ex.what()); \
    }

#define LOGO                                                              \
    auto logo = new QPushButton(this);                                    \
    logo->setIcon(QPixmap("Assets\\Banner.png")); \
    logo->setIconSize(QSize(110, 45));                                    \
    logo->setGeometry(0, 0, 0, 0);                                        \
    logo->resize(logo->icon().actualSize(QSize(110, 45)));                \
    logo->setStyleSheet("background-color: black; border: none");

#define HEADER "background-color: black; color: white; border-style: outset; "     \
               "border-top-left-radius: 4px; border-top-right-radius: 4px; "       \
               "border-bottom-left-radius: 4px; border-bottom-right-radius: 4px; " \
               "font: bold 14px"

#define PROMINENT "background-color: red; color: white; "                             \
                  "border-top-left-radius: 4px; border-top-right-radius: 4px; "       \
                  "border-bottom-left-radius: 4px; border-bottom-right-radius: 4px; " \
                  "width: 40px; height: 40px;"                                        \
                  "font: bold 14px"

class OnStack : public QMainWindow
{
    Q_OBJECT
protected:
    QStackedWidget *stack;
public slots:
    void pageUpdater();
public:
    OnStack(QStackedWidget *stack, QWidget *parent = nullptr);
    void prev(int offset = 1);
    void next(int offset = 1);
    ~OnStack();

    static User *user;
};

//User* user = nullptr;

using g = OnStack;

#endif // __ONSTACK_HPP__
