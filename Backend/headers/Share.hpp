#ifndef __SHARE_HPP__
#define __SHARE_HPP__

#include "IRecord.hpp"
#include "ID.hpp"

class Share : public IRecord
{
    IRecord_OVERRIDE;

private:
    int buyingPrice;
    std::string cnic;

public:
    const ID lotID;
    const std::string symbol;

    static const std::string TableName;

    Share(const std::string &cnic, const std::string &symbol, int buyingPrice);
    Share(const std::vector<std::string> &values);
    void setPrice(int price);
    int getPrice() const noexcept;
    void setOwner(const std::string &cnic);
    const std::string &getOwner() const noexcept;
};

#endif // __SHARE_HPP__
