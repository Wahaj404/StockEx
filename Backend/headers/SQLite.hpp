#ifndef __SQLITE_HPP__
#define __SQLITE_HPP__

#include "C:\MinGW64\opt\include\sqlite3.h"
#include <string>

class SQLite
{
private:
    sqlite3 *db;
    SQLite() noexcept;

public:
    static void run(const std::string &command, int (*callback)(void *, int, char **, char **) = nullptr, void *callbackArg = nullptr);
    ~SQLite() noexcept;
    SQLite(const SQLite &) = delete;
    SQLite operator=(const SQLite &) = delete;
};

#endif // __SQLITE_HPP__
