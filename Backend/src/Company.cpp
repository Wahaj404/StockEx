#include "Company.hpp"

const std::string Company::TableName = "Companies";

const std::string &Company::getTable() const noexcept
{
    return TableName;
}

const std::string &Company::insertColumns() const noexcept
{
    static const std::string columns = "Symbol, Current_Price, Low, High, Percent_Change, Volume";
    return columns;
}

std::string Company::insertValues() const noexcept
{
    return build(symbol, currentPrice, low, high, pChange, volume);
}

std::string Company::updateValues() const noexcept
{
    static const std::vector<std::string> values = {"Current_Price", "Low", "High", "Percent_Change", "Volume"};
    return build(values, currentPrice, low, high, pChange, volume);
}

std::vector<Condition> Company::updateConditions() const noexcept
{
    return {{"Symbol", symbol}};
}

std::vector<Condition> Company::removeConditions() const noexcept
{
    return {Condition::Impossible};
}

Company::Company(const std::string &symbol, int currentPrice, int low, int high, double pChange, int volume)
    : symbol(symbol), currentPrice(currentPrice), low(low), high(high), pChange(pChange), volume(volume),
      lowerLock((95 * currentPrice) / 100), upperLock((105 * currentPrice) / 100), close(0)
{
    insert();
}

Company::Company(const std::vector<std::string> &values)
    : symbol(values.at(0)),
      currentPrice(std::stoi(values.at(1))),
      low(std::stoi(values.at(2))),
      high(std::stoi(values.at(3))),
      pChange(std::stod(values.at(4))),
      volume(std::stoi(values.at(5))),
      close(std::stoi(values.at(1))),
      lowerLock((95 * currentPrice) / 100),
      upperLock((105 * currentPrice) / 100)
{
}

void Company::setPrice(int price)
{
    Expects(price >= lowerLock && price <= upperLock,
            "Listed price (" + std::to_string(price) + ") must be between lower lock (" + std::to_string(lowerLock) +
                ") and upper lock (" + std::to_string(upperLock) + ").");
    currentPrice = price;
    if (high < currentPrice)
        high = currentPrice;
    if (low > currentPrice)
        low = currentPrice;
    pChange = static_cast<double>(((currentPrice - close)) / 100 * (close / 10000));
}

int Company::getPrice() const noexcept
{
    return currentPrice;
}

int Company::getLow() const noexcept
{
    return low;
}

int Company::getHigh() const noexcept
{
    return high;
}

double Company::getPChange() const noexcept
{
    return pChange;
}

void Company::increaseVolume(int add)
{
    Expects(add % 100 == 0 && add > 0, "Increase in volume must be a positive multiple of hundred.");
    volume += add;
}

int Company::getVolume() const noexcept
{
    return volume;
}
