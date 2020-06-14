#ifndef __REALTIME_HPP__
#define __REALTIME_HPP__

#include "Credential.hpp"
#include "Company.hpp"
#include "User.hpp"
#include "Listing.hpp"
#include "Transaction.hpp"
#include <string>
#include <vector>
#include <map>
#include <list>
#include <memory>

class RealTime
{
private:
    std::list<Listing> listings;
    std::map<std::string, User> users;
    std::vector<std::shared_ptr<Share>> shares;
    RealTime();

    std::map<std::string, Company> companies;
public:
    static RealTime &Get();
    const std::map<std::string, Company> &getCompanies() const;
    const std::list<Listing> &getListings() const;
    std::vector<std::shared_ptr<Share>> getShares();
    const Company &getCompany(const std::string &symbol) const;
    User &getUser(const std::string &cnic);
    bool addListing(const std::string &cnic, const std::string &symbol, int price, int quantity,
                    ListingType type, const std::vector<std::shared_ptr<Share>> &shares = {});
    ~RealTime();
    RealTime(const RealTime &) = delete;
    RealTime operator=(const RealTime &) = delete;
};

#endif // __REALTIME_HPP__
