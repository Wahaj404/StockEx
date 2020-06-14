#include "SQLiteEx.hpp"
#include "C:\MinGW64\opt\include\sqlite3.h"

SQLiteEx::SQLiteEx(char *message, bool freeMemory) : SQLiteEx(std::string(message))
{
    if (freeMemory)
    {
        sqlite3_free(message);
    }
}

SQLiteEx::SQLiteEx(const std::string &message) : message("SQLiteEx: " + message)
{
}

const char *SQLiteEx::what() const noexcept
{
    return message.c_str();
}