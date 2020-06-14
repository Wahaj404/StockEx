#include "RealTime.hpp"
#include "Util.hpp"

RealTime::RealTime()
{
    for (const auto &company : IRecord::select<Company>())
    {
        companies.emplace(company.symbol, company);
    }
    for (const auto &cred : IRecord::select<Credential>())
    {
        users.emplace(cred.cnic, cred.cnic);
    }
    for (const auto &listing : IRecord::select<Listing>())
    {
        listings.push_back(listing);
    }
    for (const auto &share : IRecord::select<Share>())
    {
        shares.push_back(std::make_shared<Share>(share));
    }
}

RealTime &RealTime::Get()
{
    static RealTime realTime;
    return realTime;
}

const std::map<std::string, Company> &RealTime::getCompanies() const
{
    return companies;
}

const std::list<Listing> &RealTime::getListings() const
{
    return listings;
}

std::vector<std::shared_ptr<Share>> RealTime::getShares()
{
    return shares;
}

const Company &RealTime::getCompany(const std::string &symbol) const
{
    auto it = companies.find(symbol);
    Expects(it != companies.cend(), "Invalid company symbol.");
    return it->second;
}

User &RealTime::getUser(const std::string &cnic)
{
    auto it = users.find(cnic);
    Expects(it != users.cend(), "Invalid CNIC.");
    return it->second;
}

bool RealTime::addListing(const std::string &cnic, const std::string &symbol, int price, int lotCount,
                          ListingType type, const std::vector<std::shared_ptr<Share>> &shares)
{
    auto &company = const_cast<Company &>(getCompany(symbol));
    Expects(price >= company.lowerLock && price <= company.upperLock,
            "Listed price (" + std::to_string(price) + ") must be between lower lock (" +
                std::to_string(company.lowerLock) + ") and upper lock (" + std::to_string(company.upperLock) + ").");
    company.increaseVolume(lotCount * 100);

    auto diff = price - company.getPrice();
    company.setPrice(company.getPrice() + diff / 10);

    Listing cur(cnic, symbol, price, lotCount, type, shares);
    for (auto it = listings.begin(); it != listings.end(); ++it)
    {
        if (cur.compatible(*it))
        {
            cur.complete(*it);
            if (it->lotCount == 0)
            {
                auto old = it--;
                listings.erase(old);
            }
            if (cur.lotCount == 0)
            {
                return true;
            }
        }
    }
    listings.push_back(cur);
    return false;
}

RealTime::~RealTime()
{
    for (const auto &company : companies)
    {
        company.second.update();
    }
    for (const auto &listing : listings)
    {
        listing.update();
    }
    for (const auto &share : shares)
    {
        share->update();
    }
}
