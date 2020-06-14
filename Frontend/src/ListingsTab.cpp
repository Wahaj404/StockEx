#include "ListingsTab.hpp"

ListingsTab::ListingsTab(QWidget *parent) : QWidget(parent)
{
    sell = new QTableWidget(this);
    buy = new QTableWidget(this);
//    buy->setStyleSheet("QHeaderView::section {background-color: black; color: red;} "
//                       "QTableView::item {background-color: blue; color: red;}");
    sell->setColumnCount(4);
    buy->setColumnCount(4);
    sell->setHorizontalHeaderLabels({"Symbol", "Price", "Lot Count", "Total Value"});
    buy->setHorizontalHeaderLabels({"Symbol", "Price", "Lot Count", "Total Value"});
    int i = 0, j = 0;
    for (const auto &listing : RealTime::Get().getListings())
    {
        if (listing.type == ListingType::Buy)
        {
            buy->insertRow(i);
            buy->setItem(i, 0, new QTableWidgetItem(listing.symbol.c_str()));
            buy->setItem(i, 1, new QTableWidgetItem(decString(listing.price)));
            buy->setItem(i, 2, new QTableWidgetItem(QString::number(listing.lotCount * 100)));
            buy->setItem(i, 3, new QTableWidgetItem(decString(listing.price * listing.lotCount * 100)));
            ++i;
        }
        else
        {
            sell->insertRow(j);
            sell->setItem(j, 0, new QTableWidgetItem(listing.symbol.c_str()));
            sell->setItem(j, 1, new QTableWidgetItem(decString(listing.price)));
            sell->setItem(j, 2, new QTableWidgetItem(QString::number(listing.lotCount * 100)));
            sell->setItem(i, 3, new QTableWidgetItem(decString(listing.price * listing.lotCount * 100)));
            ++j;
        }
    }
    buy->setDisabled(true);
    sell->setDisabled(true);
    buy->setGeometry(0, 0, 960, 1080);
    sell->setGeometry(960, 0, 960, 1080);
}

void ListingsTab::update() {
    buy->clearContents();
    buy->setRowCount(0);
    sell->clearContents();
    sell->setRowCount(0);
    int i = 0, j = 0;
    for (const auto &listing : RealTime::Get().getListings())
    {
        if (listing.type == ListingType::Buy)
        {
            buy->insertRow(i);
            buy->setItem(i, 0, new QTableWidgetItem(listing.symbol.c_str()));
            buy->setItem(i, 1, new QTableWidgetItem(QString::number(listing.price)));
            buy->setItem(i, 2, new QTableWidgetItem(QString::number(listing.lotCount)));
            ++i;
        }
        else
        {
            sell->insertRow(j);
            sell->setItem(j, 0, new QTableWidgetItem(listing.symbol.c_str()));
            sell->setItem(j, 1, new QTableWidgetItem(QString::number(listing.price)));
            sell->setItem(j, 2, new QTableWidgetItem(QString::number(listing.lotCount)));
            ++j;
        }
    }
}
