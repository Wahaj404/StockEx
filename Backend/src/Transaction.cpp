#include "Transaction.hpp"

const std::string Transaction::TableName = "Transactions";

const std::string &Transaction::getTable() const noexcept
{
    return TableName;
}

const std::string &Transaction::insertColumns() const noexcept
{
    static const std::string columns = "Buyer_CNIC, Seller_CNIC, Symbol, Price, Lot_Count";
    return columns;
}

std::string Transaction::insertValues() const noexcept
{
    return build(buyer, seller, symbol, price, lotCount);
}

std::string Transaction::updateValues() const noexcept
{
    return "";
}

std::vector<Condition> Transaction::updateConditions() const noexcept
{
    return {Condition::Impossible};
}

std::vector<Condition> Transaction::removeConditions() const noexcept
{
    return {Condition::Impossible};
}

Transaction::Transaction(const std::string &buyer, const std::string &seller, const std::string &symbol,
                         int price, int lotCount)
    : id(TableName), buyer(buyer), seller(seller), symbol(symbol), price(price), lotCount(lotCount)
{
    insert();
}

Transaction::Transaction(const std::vector<std::string> &values)
    : id(std::stoi(values.at(0))), buyer(values.at(1)), seller(values.at(2)),
      symbol(values.at(3)), price(std::stoi(values.at(4))), lotCount(std::stoi(values.at(5))),
      date(values.at(6))
{
}
