#include "WatchListTab.hpp"
#include <QInputDialog>


WatchListTab::WatchListTab(QWidget *parent) : MarketTab(parent, [](const Company& c){
    return g::user->watches(c.symbol);
})
{
    auto addButton = new QPushButton("Add Company", this);
    addButton->setGeometry(1500, 200, 150, 70);
    addButton->setStyleSheet(PROMINENT);
    connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
    auto removeButton = new QPushButton("Remove Company", this);
    removeButton->setGeometry(1500, 400, 150, 70);
    removeButton->setStyleSheet(PROMINENT);
    connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
}

void WatchListTab::add()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add To Watchlist"),
                                         tr("Company name:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty())
    {
        TryError(g::user->addWatch(text.toStdString()));
    }
}

void WatchListTab::remove()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add To Watchlist"),
                                         tr("Company name:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty())
    {
        TryError(Expects(g::user->removeWatch(text.toStdString()), "No such company in watchlist."));
    }
}
