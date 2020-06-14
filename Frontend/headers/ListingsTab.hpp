#ifndef LISTINGSTAB_HPP
#define LISTINGSTAB_HPP

#include "RealTime.hpp"
#include "OnStack.hpp"
#include <QWidget>
#include <QTableWidget>

class ListingsTab : public QWidget
{
    Q_OBJECT
    QTableWidget *buy;
    QTableWidget *sell;
public:
    ListingsTab(QWidget *parent = nullptr);
    void update();
};

#endif // LISTINGSTAB_HPP
