#ifndef __LISTING_HPP__
#define __LISTING_HPP__

#include "IRecord.hpp"
#include "ID.hpp"
#include <memory>

class Share;

enum class ListingType
{
    Buy,
    Sell
};

class Listing : public IRecord
{
    IRecord_OVERRIDE;

private:
public:
    const ID id;
    const std::string cnic;
    const std::string symbol;
    const int price;
    int lotCount;
    ListingType type;
    std::vector<std::shared_ptr<Share>> shares;

    static const std::string TableName;

    Listing(const std::string cnic, const std::string symbol, int price, int lotCount,
            ListingType type, const std::vector<std::shared_ptr<Share>> &shares = {});
    Listing(const std::vector<std::string> &values);
    void complete(Listing &other);
    bool compatible(const Listing &other) const;
};

#endif // __LISTING_HPP__
