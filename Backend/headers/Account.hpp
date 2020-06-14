#ifndef __ACCOUNT_HPP__
#define __ACCOUNT_HPP__

#include "IRecord.hpp"

class Account : public IRecord
{
    IRecord_OVERRIDE;

private:
    int balance;

public:
    const std::string cnic;

    static const std::string TableName;

    Account(const std::vector<std::string> &values);
    void setBalance(int balance);
    int getBalance() const noexcept;
};

#endif // __ACCOUNT_HPP__
