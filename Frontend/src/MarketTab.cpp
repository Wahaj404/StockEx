#include "MarketTab.hpp"

//std::vector<std::string> csv(const std::string&coms) {
//    std::stringstream ss(coms);
//    std::string str;
//    std::vector<std::string> ret;
//    while(std::getline(ss, str, ',')) {
//        ret.push_back(str);
//    }
//    return ret;
//}

MarketTab::MarketTab(QWidget *parent, bool (*valid)(const Company &)) : QWidget(parent)
{
    table = new QTableWidget(this);
    table->setColumnCount(9);
    table->setHorizontalHeaderLabels({"Symbol", "Current Price", "Low", "High", "Percent Change", "Volume", "Lower Lock", "Upper Lock", "Last Day Close"});
    int i = 0;
    for (const auto &companyP : RealTime::Get().getCompanies())
    {
        auto company = companyP.second;
        if (valid(company))
        {
            table->insertRow(i);
            table->setItem(i, 0, new QTableWidgetItem(company.symbol.c_str()));
            table->setItem(i, 1, new QTableWidgetItem(decString(company.getPrice())));
            table->setItem(i, 2, new QTableWidgetItem(decString(company.getLow())));
            table->setItem(i, 3, new QTableWidgetItem(decString(company.getHigh())));
            table->setItem(i, 4, new QTableWidgetItem(QString::number(company.getPChange(), 'f', 2)));
            table->setItem(i, 5, new QTableWidgetItem(QString::number(company.getVolume())));
            table->setItem(i, 6, new QTableWidgetItem(decString(company.lowerLock)));
            table->setItem(i, 7, new QTableWidgetItem(decString(company.upperLock)));
            table->setItem(i, 8, new QTableWidgetItem(decString(company.close)));
            ++i;
        }
    }
//    table->setDisabled(true);
    for (int i = 0; i < table->rowCount(); ++i) {
        for (int j = 0; j < 8; ++j) {
            auto item = table->item(i, j);
            item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
        }
    }
    table->setVerticalScrollBar(new QScrollBar(Qt::Orientation::Vertical, table));
    table->verticalScrollBar()->setMinimum(0);
    table->verticalScrollBar()->setMaximum(100);



    auto sellForm = new QFormLayout;
    auto sellHeader = new QPushButton("Sell");
    sellHeader->setStyleSheet(HEADER);
    sellForm->addWidget(sellHeader);
    sellSymbol = new QLineEdit(this);
    sellSymbol->setStyleSheet("background-color: white");
    sellForm->addRow(new QLabel("Symbol:"), sellSymbol);
    sellPrice = new QLineEdit(this);
    sellPrice->setStyleSheet("background-color: white");
    sellForm->addRow(new QLabel("Price:"), sellPrice);
    sellQuantity = new QLineEdit(this);
    sellQuantity->setStyleSheet("background-color: white");
    sellForm->addRow(new QLabel("Quantity:"), sellQuantity);
    auto sellButton = new QPushButton("Sell");
    connect(sellButton, SIGNAL(clicked()), this, SLOT(sell()));
    sellForm->addWidget(sellButton);

    auto buyForm = new QFormLayout;
    auto buyHeader = new QPushButton("Buy");
    buyHeader->setStyleSheet(HEADER);
    buyForm->addWidget(buyHeader);
    buySymbol = new QLineEdit(this);
    buySymbol->setStyleSheet("background-color: white");
    buyForm->addRow(new QLabel("Symbol:"), buySymbol);
    buyPrice = new QLineEdit(this);
    buyPrice->setStyleSheet("background-color: white");
    buyForm->addRow(new QLabel("Price:"), buyPrice);
    buyQuantity = new QLineEdit(this);
    buyQuantity->setStyleSheet("background-color: white");
    buyForm->addRow(new QLabel("Quantity:"), buyQuantity);
    auto buyButton = new QPushButton("Buy");
    connect(buyButton, SIGNAL(clicked()), this, SLOT(buy()));
    buyForm->addWidget(buyButton);

    auto grid = new QGridLayout(this);
    grid->addWidget(table, 0, 0, 2, 2);
    grid->addLayout(buyForm, 0, 2);
    grid->addLayout(sellForm, 1, 2);
    grid->setColumnStretch(0, 10);
    setLayout(grid);
}

void MarketTab::buy()
{
    try {
        g::user->buy(buySymbol->text().toStdString(), buyPrice->text().toDouble() * 100, buyQuantity->text().toInt() / 100);
    }
    catch(std::exception &ex) {
        QMessageBox::warning(this, "StockEx", ex.what());
    }
}

void MarketTab::sell()
{
    TryError(g::user->sell(sellSymbol->text().toStdString(), sellPrice->text().toDouble() * 100, sellQuantity->text().toInt() / 100));
}

MarketTab::~MarketTab()
{
}

void MarketTab::update()
{
    for (int i = 0; i < table->rowCount(); ++i)
    {
        auto &company = const_cast<Company &>(RealTime::Get().getCompany(table->item(i, 0)->text().toStdString()));
        //        if (rand() % 2 == 0) {
        //            company.setPrice(company.getPrice() + rand() % 10);
        //        }
        if (company.getPrice() != table->item(i, 1)->text().toInt())
        {
            for (int j = 1; j < 5; ++j) {
                auto item = table->item(i, j);
                item->setFlags(item->flags() &  Qt::ItemIsEditable);
            }
            table->setItem(i, 1, new QTableWidgetItem(decString(company.getPrice())));
            table->setItem(i, 2, new QTableWidgetItem(decString(company.getLow())));
            table->setItem(i, 3, new QTableWidgetItem(decString(company.getHigh())));
            table->setItem(i, 4, new QTableWidgetItem(QString::number(company.getPChange())));
            table->setItem(i, 5, new QTableWidgetItem(QString::number(company.getVolume())));
            for (int j = 1; j < 5; ++j) {
                auto item = table->item(i, j);
                item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
            }
//            table->setDisabled(true);
        }
    }
}
