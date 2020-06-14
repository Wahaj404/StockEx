#include "Credential.hpp"

const std::string Credential::TableName = "Credentials";

const std::string &Credential::getTable() const noexcept
{
    return TableName;
}

const std::string &Credential::insertColumns() const noexcept
{
    static const std::string columns = "CNIC, Password";
    return columns;
}

std::string Credential::insertValues() const noexcept
{
    return build(cnic, password);
}

std::string Credential::updateValues() const noexcept
{
    static const std::vector<std::string> values = {"Password"};
    return build(values, password);
}

std::vector<Condition> Credential::updateConditions() const noexcept
{
    return {{"CNIC", cnic}};
}

std::vector<Condition> Credential::removeConditions() const noexcept
{
    return {Condition::Impossible};
}

Credential::Credential(const std::string &cnic, const std::string &password) : cnic(cnic), password(password)
{
    insert();
}

Credential::Credential(const std::vector<std::string> &values) : cnic(values.at(0)), password(values.at(1))
{
}

bool Credential::isValid(const std::string &cnic, const std::string &password)
{
    return select<Credential>({{"CNIC", cnic}, {"Password", password}}).size() == 1;
}