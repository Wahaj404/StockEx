#ifndef __SQLITEEX_HPP__
#define __SQLITEEX_HPP__

#include <exception>
#include <string>

class SQLiteEx : public std::exception
{
private:
    std::string message;

public:
    SQLiteEx(char *message, bool freeMemory = true);
    SQLiteEx(const std::string &message);
    const char *what() const noexcept override;
};

#endif // __SQLITEEX_HPP__
