#ifndef __CREDENTIAL_HPP__
#define __CREDENTIAL_HPP__

#include "IRecord.hpp"

class Credential : public IRecord
{
    IRecord_OVERRIDE;

private:
    std::string password;

public:
    std::string cnic;

    static const std::string TableName;

    // TODO: Use hashed password in constructor.
    Credential(const std::string &cnic, const std::string &password);
    Credential(const std::vector<std::string> &values);
    static bool isValid(const std::string &cnic, const std::string &password);
};

#endif // __CREDENTIAL_HPP__
