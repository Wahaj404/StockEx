#ifndef __USER_HPP__
#define __USER_HPP__

#include "Account.hpp"
#include "Share.hpp"
#include "WatchList.hpp"
#include "Listing.hpp"
#include <string>
#include <list>

class User
{
private:
    Account account;
    WatchList watchList;

public:
    const std::string cnic;
    User(const std::string &cnic);
    bool sell(const std::string &symbol, int price, int lotCount);
    bool buy(const std::string &symbol, int price, int lotCount);
    int getBalance() const noexcept;
    void transfer(int amount);
    bool addWatch(const std::string &symbol);
    bool watches(const std::string &symbol) const noexcept;
    bool removeWatch(const std::string &symbol);
    std::list<std::shared_ptr<Share>> getShares() const noexcept;
    void buyShares(Share share);
    void sellShares(const ID &id);
    ~User();
    User(const User &) = delete;
    const User &operator=(const User &) = delete;
};

#endif // __USER_HPP__
