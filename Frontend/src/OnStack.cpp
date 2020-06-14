#include "OnStack.hpp"

#include "Portfolio.hpp"

User* OnStack::user = nullptr;

QString decString(int num) {
    auto first = QString::number(num / 100), second = QString::number(num % 100);
    if (first.length() == 0) {
        first = "0";
    }
    if (second.length() == 0) {
        second = "00";
    }
    else if (second.length() == 1) {
        second = "0" + second;
    }
    return first + "." + second;
}

OnStack::OnStack(QStackedWidget *stack, QWidget *parent) :  QMainWindow(parent), stack(stack)
{
    connect(stack, SIGNAL(currentChanged(int)), this, SLOT(pageUpdater()));
}

//void OnStack:nextSlot(int offset) {
//    next(offset);
//}

void OnStack::prev(int offset){
    next(-offset);
}

void OnStack::next(int offset){
    stack->setCurrentIndex(stack->currentIndex() + offset);
}

void OnStack::pageUpdater() {
    if (stack->currentIndex() == 3) {
        ((Portfolio *) stack->currentWidget())->updateBalance();
    }
}

OnStack::~OnStack()
{
}
