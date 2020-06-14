#include "Listing.hpp"

#include "Share.hpp"
#include "Transaction.hpp"
#include <numeric>
#include <algorithm>

const std::string Listing::TableName = "Listings";

const std::string &Listing::getTable() const noexcept
{
    return TableName;
}

const std::string &Listing::insertColumns() const noexcept
{
    static const std::string columns = "CNIC, Symbol, Price, Lot_Count, Listing_Type, Share_IDs";
    return columns;
}

std::string Listing::insertValues() const noexcept
{
    auto ids = std::accumulate(shares.cbegin(), shares.cend(), ""s,
                               [](const std::string &accumulator, const std::shared_ptr<Share> &share) {
                                   return accumulator + std::to_string(share->lotID) + ";";
                               });
    return build(cnic, symbol, price, lotCount, static_cast<int>(type), ids);
}

std::string Listing::updateValues() const noexcept
{
    static const std::vector<std::string> values = {"Lot_Count", "Share_IDs"};
    auto ids = std::accumulate(shares.cbegin(), shares.cend(), ""s,
                               [](const std::string &accumulator, const std::shared_ptr<Share> &share) {
                                   return accumulator + std::to_string(share->lotID) + ";";
                               });
    return build(values, lotCount, ids);
}

std::vector<Condition> Listing::updateConditions() const noexcept
{
    return {{"ID", id}};
}

std::vector<Condition> Listing::removeConditions() const noexcept
{
    return {{"ID", id}};
}

Listing::Listing(const std::string cnic, const std::string symbol, int price, int lotCount,
                 ListingType type, const std::vector<std::shared_ptr<Share>> &shares)
    : id(TableName), cnic(cnic), symbol(symbol), price(price), lotCount(lotCount), type(type), shares(shares)
{
    if (type == ListingType::Buy)
    {
        Expects(shares.size() == 0, "A buy listing may not point to any shares.");
    }
    else
    {
        Expects(shares.size() > 0, "A sell listing must point to some shares.");
    }
    insert();
}

Listing::Listing(const std::vector<std::string> &values)
    : id(std::stoi(values.at(0))), cnic(values.at(1)), symbol(values.at(2)), price(std::stoi(values.at(3))),
      lotCount(std::stoi(values.at(4))),
      type(static_cast<ListingType>(std::stoi(values.at(5))))
{
}

void Listing::complete(Listing &other)
{
    Expects(compatible(other), "Attempted completion on incompatible listings.");
    if (type == ListingType::Buy)
    {
        other.complete(*this);
        return;
    }
    int sellCount = std::min(lotCount, other.lotCount);
    for (int i = shares.size() - 1; lotCount >= 0 && other.lotCount >= 0; --i, --lotCount, --other.lotCount)
    {
        shares.at(i)->setPrice(price);
        shares.at(i)->setOwner(other.cnic);
        shares.pop_back();
    }
    if (lotCount == 0)
        remove();
    if (other.lotCount == 0)
        other.remove();
    Transaction(other.cnic, cnic, symbol, price, sellCount);
}

bool Listing::compatible(const Listing &other) const
{
    return type != other.type && cnic != other.cnic && price == other.price;
}
