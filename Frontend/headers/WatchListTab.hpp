#ifndef WATCHLISTTAB_HPP
#define WATCHLISTTAB_HPP

#include "MarketTab.hpp"

class WatchListTab : public MarketTab
{
    Q_OBJECT
public slots:
    void add();
    void remove();
public:
    WatchListTab(QWidget *parent = nullptr);
};

#endif // WATCHLISTTAB_HPP
