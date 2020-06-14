#include "Condition.hpp"
#include <numeric> // For std::accumulate

const Condition Condition::Impossible("0", 1);

const std::string &Condition::getString(Comparator comp)
{
    static const std::vector<std::string> comparatorStrings = {" = ", " != ", " < ", " <= ", " > ", " >= "};
    return comparatorStrings.at(static_cast<int>(comp));
}

Condition::Condition(const std::string &column, const std::string &value, Comparator comp)
    : column(column), value(quote(value)),
      comparatorString(getString(comp)) {}

Condition::Condition(const std::string &column, int value, Comparator comp)
    : column(column), value(std::to_string(value)),
      comparatorString(getString(comp)) {}

std::string Condition::str() const
{
    return column + comparatorString + value;
}

std::string Condition::unpack(const std::vector<Condition> &conditions)
{
    if (conditions.empty())
    {
        return "";
    }
    return "WHERE " +
           std::accumulate(conditions.cbegin(), conditions.cend() - 1, ""s,
                           [](const std::string &accumulator, const Condition &condition) {
                               return accumulator + condition.str() + " AND ";
                           }) +
           conditions.back().str();
}