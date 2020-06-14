#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "OnStack.hpp"
#include "MarketTab.hpp"
#include "ListingsTab.hpp"
#include "WatchListTab.hpp"
#include <QPushButton>

class MainWindow : public OnStack
{
    Q_OBJECT
public slots:
    void tabUpdater();
    void nextSlot();
    void logOut();
    ABOUT_SLOT
public:
    MainWindow(QStackedWidget *stack, QWidget *parent = nullptr);
    QTabWidget *tabs;
    ~MainWindow();
};

#endif // MAINWINDOW_HPP
