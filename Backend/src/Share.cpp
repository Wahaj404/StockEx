#include "Share.hpp"

#include "RealTime.hpp"

const std::string Share::TableName = "Shares";

const std::string &Share::getTable() const noexcept
{
    return TableName;
}

const std::string &Share::insertColumns() const noexcept
{
    static const std::string columns = "CNIC, Symbol, Buying_Price";
    return columns;
}

std::string Share::insertValues() const noexcept
{
    return build(cnic, symbol, buyingPrice);
}

std::string Share::updateValues() const noexcept
{
    static const std::vector<std::string> values = {"CNIC", "Buying_Price"};
    return build(values, cnic, buyingPrice);
}

std::vector<Condition> Share::updateConditions() const noexcept
{
    return {{"ID", lotID}};
}

std::vector<Condition> Share::removeConditions() const noexcept
{
    return {Condition::Impossible};
}

Share::Share(const std::string &cnic, const std::string &symbol, int buyingPrice)
    : lotID(TableName), cnic(cnic), symbol(symbol), buyingPrice(buyingPrice)
{
    insert();
}

Share::Share(const std::vector<std::string> &values)
    : lotID(std::stoi(values.at(0))), cnic(values.at(1)), symbol(values.at(2)), buyingPrice(std::stoi(values.at(3)))
{
}

void Share::setPrice(int price)
{
    Expects(price > 0, "BuyingPrice must be positive.");
    buyingPrice = price;
}

int Share::getPrice() const noexcept
{
    return buyingPrice;
}

void Share::setOwner(const std::string &cnic)
{
    Expects(cnic != this->cnic, "Old and new owners are the same.");
    auto &old = RealTime::Get().getUser(this->cnic);
    auto &now = RealTime::Get().getUser(cnic);
    old.sellShares(lotID);
    this->cnic = cnic;
    now.buyShares(*this);
}

const std::string &Share::getOwner() const noexcept
{
    return cnic;
}
