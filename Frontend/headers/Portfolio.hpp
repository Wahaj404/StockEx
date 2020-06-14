#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include "OnStack.hpp"
#include <QTableWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QInputDialog>
#include <fstream>
#include <iomanip>

class Portfolio : public OnStack
{
    Q_OBJECT

public slots:
    void prevSlot();
    void TransferIn(int mult = 1);
    void TransferOut();
    void exportTransactions();
    ABOUT_SLOT

public:
    Portfolio(QStackedWidget *stack, QWidget *parent = nullptr);
    QLabel *currentBalance;
    void updateBalance();
    ~Portfolio();
};

#endif // PORTFOLIO_HPP
