#include "WatchList.hpp"
#include "RealTime.hpp"
#include <sstream>
#include <numeric>

using namespace std::string_literals;

const std::string WatchList::TableName = "WatchLists";

const std::string &WatchList::getTable() const noexcept
{
    return TableName;
}

const std::string &WatchList::insertColumns() const noexcept
{
    static const std::string columns = "CNIC, Companies";
    return columns;
}

std::string WatchList::insertValues() const noexcept
{
    return build(cnic, std::accumulate(companies.cbegin(), companies.cend(), ""s,
                                       [](const std::string &accumulator, const std::string &symbol) {
                                           return accumulator + symbol + ";";
                                       }));
}

std::string WatchList::updateValues() const noexcept
{
    static const std::vector<std::string> values = {"Companies"};
    return build(values, std::accumulate(companies.cbegin(), companies.cend(), ""s,
                                         [](const std::string &accumulator, const std::string &symbol) {
                                             return accumulator + symbol + ";";
                                         }));
}

std::vector<Condition> WatchList::updateConditions() const noexcept
{
    return {{"CNIC", cnic}};
}

std::vector<Condition> WatchList::removeConditions() const noexcept
{
    return {Condition::Impossible};
}

WatchList::WatchList(const std::string &cnic) : cnic(cnic)
{
    IRecord::insert();
}

WatchList::WatchList(const std::vector<std::string> &values) : cnic(values.at(0))
{
    std::stringstream ss(values.at(1));
    std::string str;
    while (std::getline(ss, str, ';'))
    {
        companies.insert(str);
    }
}

bool WatchList::addCompany(const std::string &symbol)
{
    RealTime::Get().getCompany(symbol);
    return companies.insert(symbol).second;
}

bool WatchList::contains(const std::string &symbol) const
{
    return companies.find(symbol) != companies.cend();
}

bool WatchList::removeCompany(const std::string &symbol)
{
    return companies.erase(symbol) == 1;
}