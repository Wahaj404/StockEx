#ifndef __WATCHLIST_HPP__
#define __WATCHLIST_HPP__

#include "IRecord.hpp"
#include <string>
#include <set>

class WatchList : public IRecord
{
    IRecord_OVERRIDE;

private:
    std::set<std::string> companies;

public:
    const std::string cnic;
    static const std::string TableName;

    WatchList(const std::string &cnic);
    WatchList(const std::vector<std::string> &values);
    bool addCompany(const std::string &symbol);
    bool contains(const std::string &symbol) const;
    bool removeCompany(const std::string &symbol);
};

#endif // __WATCHLIST_HPP__
