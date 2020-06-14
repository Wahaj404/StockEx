#ifndef __TRANSACTION_HPP__
#define __TRANSACTION_HPP__

#include "IRecord.hpp"
#include "ID.hpp"

class Transaction : public IRecord
{
    IRecord_OVERRIDE;

public:
    const ID id;
    const std::string buyer;
    const std::string seller;
    const std::string symbol;
    const int price;
    const int lotCount;
    const std::string date;
    static const std::string TableName;

    Transaction(const std::string &buyer, const std::string &seller, const std::string &symbol,
                int price, int lotCount);
    Transaction(const std::vector<std::string> &values);
};

#endif // __TRANSACTION_HPP__
