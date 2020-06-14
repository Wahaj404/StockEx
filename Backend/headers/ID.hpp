#ifndef __ID_HPP__
#define __ID_HPP__

#include <string>

class ID
{
private:
    int id;

public:
    ID(int id);
    ID(const std::string &tableName);
    operator int() const;
    bool operator==(const ID &other) const noexcept;
};

#endif // __ID_HPP__
