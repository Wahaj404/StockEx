#ifndef __COMPANY_HPP__
#define __COMPANY_HPP__

#include "IRecord.hpp"

class Company : public IRecord
{
    IRecord_OVERRIDE;

private:
    int currentPrice;
    int low;
    int high;
    double pChange;
    int volume;

public:
    const std::string symbol;
    const int close;
    const int lowerLock;
    const int upperLock;

    static const std::string TableName;

    Company(const std::string &symbol, int currentPrice, int low, int high, double pChange, int volume);
    Company(const std::vector<std::string> &values);

    void setPrice(int currentPrice);
    int getPrice() const noexcept;
    int getLow() const noexcept;
    int getHigh() const noexcept;
    double getPChange() const noexcept;
    void increaseVolume(int add);
    int getVolume() const noexcept;
};

#endif // __COMPANY_HPP__
