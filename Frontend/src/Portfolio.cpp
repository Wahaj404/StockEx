#include "Portfolio.hpp"

Portfolio::Portfolio(QStackedWidget *stack, QWidget *parent) : OnStack(stack, parent)
{
    LOGO
//        logo->setStyleSheet("border: none");
    ABOUT_CONNECT
    auto shares = new QTableWidget(this);
    shares->setColumnCount(3);
    shares->setHorizontalHeaderLabels({"Symbol", "Buying Price", "Quantity"});
    int i = 0;
    for (const auto &share : g::user->getShares())
    {
        shares->insertRow(i);
        shares->setItem(i, 0, new QTableWidgetItem(share->symbol.c_str()));
        shares->setItem(i, 1, new QTableWidgetItem(decString(share->getPrice())));
        shares->setItem(i, 2, new QTableWidgetItem(QString::number(100)));
        ++i;
    }
    shares->setDisabled(true);
    //    shares->setGeometry(0, 45, 960, 1035);
    auto transactions = new QTableWidget(this);
    transactions->setColumnCount(4);
    transactions->setHorizontalHeaderLabels({"Symbol", "Price", "Quantity", "Date"});
    i = 0;
    for (const auto &trans : IRecord::select<Transaction>({{"Buyer_CNIC", g::user->cnic}}))
    {
        transactions->insertRow(i);
        transactions->setItem(i, 0, new QTableWidgetItem(trans.symbol.c_str()));
        transactions->setItem(i, 1, new QTableWidgetItem(decString(trans.price)));
        transactions->setItem(i, 2, new QTableWidgetItem(QString::number(100)));
        transactions->setItem(i, 3, new QTableWidgetItem(trans.date.c_str()));
        ++i;
    }
    transactions->setDisabled(true);
    //    transactions->setGeometry(960, 0, 960, 540);
    auto stransactions = new QTableWidget(this);
    stransactions->setColumnCount(4);
    stransactions->setHorizontalHeaderLabels({"Symbol", "Price", "Quantity", "Date"});
    i = 0;
    for (const auto &trans : IRecord::select<Transaction>({{"Seller_CNIC", g::user->cnic}}))
    {
        stransactions->insertRow(i);
        stransactions->setItem(i, 0, new QTableWidgetItem(trans.symbol.c_str()));
        stransactions->setItem(i, 1, new QTableWidgetItem(decString(trans.price)));
        stransactions->setItem(i, 2, new QTableWidgetItem(QString::number(trans.lotCount * 100)));
        stransactions->setItem(i, 3, new QTableWidgetItem(trans.date.c_str()));
        ++i;
    }
    stransactions->setDisabled(true);
    //    stransactions->setGeometry(960, 540, 960, 540);

    auto central = new QWidget(this);
    auto h0 = new QPushButton("Shares", central);
    h0->setStyleSheet(HEADER);
    auto h1 = new QPushButton("Bought", central);
    h1->setStyleSheet(HEADER);
    auto h2 = new QPushButton("Sold", central);
    h2->setStyleSheet(HEADER);
    auto back = new QPushButton("Market", central);
    back->setGeometry(150, 10, 110, 45);
    back->setStyleSheet(PROMINENT);
    connect(back, SIGNAL(clicked()), this, SLOT(prevSlot()));
    auto grid = new QGridLayout(central);

    auto in = new QPushButton("Transfer from bank account", central);
    auto out = new QPushButton("Transfer to bank account", central);
    connect(in, SIGNAL(clicked()), this, SLOT(TransferIn()));
    connect(out, SIGNAL(clicked()), this, SLOT(TransferOut()));

    auto exportButton = new QPushButton("Export transaction data", central);
    connect(exportButton, SIGNAL(clicked()), this, SLOT(exportTransactions()));

    auto balGrid = new QGridLayout(central);
    currentBalance = new QLabel("Your current balance is: " + decString(g::user->getBalance()) + " Rs.", central);
    currentBalance->setAlignment(Qt::AlignCenter);
    currentBalance->setFont(QFont("Arial", 14));
    balGrid->addWidget(currentBalance, 0, 0, 1, 2);
    balGrid->addWidget(in, 1, 0);
    balGrid->addWidget(out, 1, 1);
    auto topLeft = new QGridLayout(central);
    topLeft->addWidget(logo, 0, 0);
    //    topLeft->setColumnMinimumWidth(0, 110);
    topLeft->setColumnStretch(1, 20);
    topLeft->addWidget(nullptr, 0, 1);
    grid->addLayout(topLeft, 0, 0);
    grid->addLayout(balGrid, 0, 1);
    grid->addWidget(exportButton, 0, 2);
    grid->addWidget(h0, 1, 0);
    grid->addWidget(h1, 1, 1);
    grid->addWidget(h2, 1, 2);
    grid->addWidget(shares, 2, 0);
    grid->addWidget(transactions, 2, 1);
    grid->addWidget(stransactions, 2, 2);
    //    out->setGeometry(in->pos().x() + in->size().width(), in->pos().y(), in->size().width(), in->size().height());
    central->setLayout(grid);
    setCentralWidget(central);
}

void Portfolio::prevSlot()
{
    prev();
}

void Portfolio::TransferIn(int mult)
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Transfer"),
                                         tr("Amount:"), QLineEdit::Normal,
                                         "0", &ok);
    if (ok && !text.isEmpty())
    {
        TryError(Expects(text.toInt() > 0, "Transferred amount must be positive."));
        if (text.toInt() <= 0) {
            return;
        }
        try {
                 g::user->transfer(text.toInt() * 100 * mult);
                 updateBalance();
        }
        catch(std::invalid_argument &ex) {
            QMessageBox::warning(this, "StockEx", "Insufficient funds.");
        }
    }
}
void Portfolio::TransferOut()
{
    TransferIn(-1);
}

void Portfolio::exportTransactions()
{
    std::ofstream file("transactions.txt");
    file << std::setw(20) << "Transactions as buyer\n";
    for (const auto &trans : IRecord::select<Transaction>({{"Buyer_CNIC", g::user->cnic}}))
    {
        file << "Transaction ID " << trans.id << ": " << trans.lotCount * 100 << " shares bought of " << trans.symbol << " at " << trans.price << " Rs. on " << trans.date << "\n";
    }
    file << std::setw(20) << "\nTransactions as seller\n";
    for (const auto &trans : IRecord::select<Transaction>({{"Seller_CNIC", g::user->cnic}}))
    {
        file << "Transaction ID " << trans.id << ": " << trans.lotCount * 100 << " shares sold of " << trans.symbol << " at " << trans.price << " Rs. on " << trans.date << "\n";
    }
}

void Portfolio::updateBalance() {
    currentBalance->setText("Your current balance is: " + decString(g::user->getBalance()) + " Rs.");
}

Portfolio::~Portfolio()
{
}
