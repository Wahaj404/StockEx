#ifndef MARKETTAB_HPP
#define MARKETTAB_HPP

#include "RealTime.hpp"
#include <QWidget>
#include <QTableWidget>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QScrollBar>
#include "OnStack.hpp"

class updater;

class MarketTab : public QWidget
{
    Q_OBJECT
public slots:
    void buy();
    void sell();
public:
    QTableWidget *table;
    MarketTab(QWidget *parent = nullptr, bool (*valid)(const Company&) = [](const Company&){return true;});
    QLineEdit *sellSymbol;
    QLineEdit *sellPrice;
    QLineEdit *sellQuantity;
    QLineEdit *buySymbol;
    QLineEdit *buyPrice;
    QLineEdit *buyQuantity;    
    void update();
    ~MarketTab();
};
#endif // MARKETTAB_HPP
