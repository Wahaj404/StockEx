#ifndef __CONDITION_HPP__
#define __CONDITION_HPP__

#include "Util.hpp"
#include <string>
#include <vector>

enum class Comparator
{
    E,
    NE,
    L,
    LE,
    G,
    GE
};

class Condition
{
private:
    static const std::string &getString(Comparator comp);
    std::string column;
    std::string comparatorString;
    std::string value;

public:
    static std::string unpack(const std::vector<Condition> &conditions);
    Condition(const std::string &column, const std::string &value, Comparator comp = Comparator::E);
    Condition(const std::string &column, int value, Comparator comp = Comparator::E);
    std::string str() const;
    static const Condition Impossible;
};

#endif // __CONDITION_HPP__
