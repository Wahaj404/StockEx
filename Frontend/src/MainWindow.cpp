#include "MainWindow.hpp"

MainWindow::MainWindow(QStackedWidget *stack, QWidget *parent)
    : OnStack(stack, parent)
{
    LOGO
//            ABOUT_CONNECT
//            connect(logo, SIGNAL(clicked()), this, SLOT(aboutSlot()));
    tabs = new QTabWidget(this);
    tabs->addTab(new MarketTab(tabs), "Market");
    tabs->addTab(new ListingsTab(tabs), "Listings");
    tabs->addTab(new WatchListTab(tabs), "WatchList");
    auto button = new QPushButton("Portfolio", tabs);
    button->setGeometry(745, 6, 110, 21);
    button->setStyleSheet("background-color: red; color: white; border-style: outset; "
                          "border-top-left-radius: 4px; border-top-right-radius: 4px; "
                          "border-bottom-left-radius: 4px; border-bottom-right-radius: 4px; "
                          "font: bold 14px"
                          /*":pressed{ border-style: inset; background-color: orange;}"*/);
    connect(button, SIGNAL(clicked()), this, SLOT(nextSlot()));
    connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(tabUpdater()));
    tabs->setStyleSheet("QTabWidget::tab-bar {color: black; left: 110px}"
                        "QTabBar::tab {border-top-left-radius: 4px; border-top-right-radius: 4px; padding: 5px; height: 21 px; width: 200px;"
                        "border-color: black; color: black;}"
                        "QTabBar::tab:selected {font: bold; border-style: outset; background-color: gray}"
                        "QTabBar::tab:!selected {font: italic; border-style: inset; margin-top: 3px; background-color: white;}");
    auto logout = new QPushButton("Log Out", tabs);
    logout->setGeometry(1810, 6, 110, 21);
    logout->setStyleSheet("background-color: #1D2994; color: white");
    connect(logout, SIGNAL(clicked()), this, SLOT(logOut()));

    tabs->resize(1920, 1080);
    tabs->update();
    showFullScreen();
}

void MainWindow::tabUpdater() {
    if (tabs->currentIndex() == 0 || tabs->currentIndex() == 2) {
        ((MarketTab *) tabs->currentWidget())->update();
    }
    else if (tabs->currentIndex() == 1) {
        ((ListingsTab *) tabs->currentWidget())->update();
    }
}

void MainWindow::logOut() {
    g::user = nullptr;
    stack->removeWidget(stack->widget(3));
    stack->removeWidget(this);
}


void MainWindow::nextSlot() {
    next();
}

MainWindow::~MainWindow()
{
}
