#include "Account.hpp"

const std::string Account::TableName = "Accounts";

const std::string &Account::getTable() const noexcept 
{
    return TableName;
}

const std::string &Account::insertColumns() const noexcept 
{
    static const std::string columns = "CNIC, Balance";
    return columns;
}

std::string Account::insertValues() const noexcept 
{
    return build(cnic, balance);
}

std::string Account::updateValues() const noexcept 
{
    static const std::vector<std::string> values = {"Balance"};
    return build(values, balance);
}

std::vector<Condition> Account::updateConditions() const noexcept 
{
    return {{"CNIC", cnic}};
}

std::vector<Condition> Account::removeConditions() const noexcept 
{
    return {Condition::Impossible};
}

Account::Account(const std::vector<std::string> &values) : cnic(values.at(0)), balance(std::stoi(values.at(1)))
{
}

void Account::setBalance(int balance)
{
    Expects(balance >= 0, "Balance may not be negative.");
    this->balance = balance;
}

int Account::getBalance() const noexcept
{
    return balance;
}