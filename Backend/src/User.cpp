#include "User.hpp"
#include "RealTime.hpp"
#include "ID.hpp"
#include <numeric>
#include <algorithm>

User::User(const std::string &cnic)
    : account(IRecord::select<Account>({{"CNIC", cnic}}).at(0)),
      watchList(IRecord::select<WatchList>({{"CNIC", cnic}}).at(0)),
      cnic(cnic)
{
}

bool User::sell(const std::string &symbol, int price, int lotCount)
{
    std::vector<std::shared_ptr<Share>> matching;
    RealTime::Get().getCompany(symbol);
    for (auto &share : RealTime::Get().getShares())
    {
        if (symbol == share->symbol && share->getOwner() == cnic)
        {
            matching.push_back(share);
            if (matching.size() == lotCount)
            {
                break;
            }
        }
    }
    Expects(matching.size() >= lotCount, "Not enough matching shares owned.");
    return RealTime::Get().addListing(cnic, symbol, price, lotCount, ListingType::Sell, matching);
}

bool User::buy(const std::string &symbol, int price, int lotCount)
{
    auto total = price * lotCount * 100;
    Expects(account.getBalance() >= total, "Insufficient funds.");
    auto ret = RealTime::Get().addListing(cnic, symbol, price, lotCount, ListingType::Buy);
    account.setBalance(account.getBalance() - total);
    return ret;
}

int User::getBalance() const noexcept
{
    return account.getBalance();
}

void User::transfer(int amount)
{
    account.setBalance(account.getBalance() + amount);
}

bool User::addWatch(const std::string &symbol)
{
    return watchList.addCompany(symbol);
}

bool User::watches(const std::string &symbol) const noexcept
{
    return watchList.contains(symbol);
}

bool User::removeWatch(const std::string &symbol)
{
    return watchList.removeCompany(symbol);
}

void User::buyShares(Share share)
{
    Expects(cnic == share.getOwner(), "Share ownership not transferred from " + cnic + " to " + share.getOwner() + ".");
}

std::list<std::shared_ptr<Share>> User::getShares() const noexcept
{
    std::list<std::shared_ptr<Share>> ret;
    for (const auto &share : RealTime::Get().getShares())
    {
        if (share->getOwner() == cnic)
        {
            ret.push_back(share);
        }
    }
    return ret;
}

void User::sellShares(const ID &id)
{
    for (auto share : RealTime::Get().getShares())
    {
        if (share->lotID == id)
        {
            transfer(share->getPrice() * 100);
            return;
        }
    }
    Expects(false, "This share isn't owned by this user.");
}

User::~User()
{
    watchList.update();
    account.update();
}
