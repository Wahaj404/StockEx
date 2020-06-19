#include "LoginWindow.hpp"
#include "MainWindow.hpp"
#include "Portfolio.hpp"
#include "Splash.hpp"

#include <QApplication>
#include <QStackedWidget>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(/*"QTableView {"*/
                        "QWidget {background-color: #A0A0A0; border-color: black;} "
                        "QHeaderView::section {background-color: #202020; color: white;} "
                        "QTableView::item {background-color: #E0E0E0; color: black;} "
                        "QLineEdit {background-color: white} "
//                        "QPushButton {background-color: red}"
                    /*"}"*/);
    auto stack = new QStackedWidget;
    auto splash  = new Splash (stack);
    auto w = new LoginWindow(stack);
    stack->addWidget(splash);
    stack->addWidget(w);

    stack->show();
//    stack.setGeometry(0, 30, 1920, 1080);
//    stack.setCurrentIndex(0);
    return a.exec();
}
