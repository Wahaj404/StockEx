#include "SQLite.hpp"
#include "SQLiteEx.hpp"
#include <cassert>

SQLite::SQLite() noexcept
{
    assert(sqlite3_open("StockEx.db", &db) == SQLITE_OK);
    assert(sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr) == SQLITE_OK);
}

void SQLite::run(const std::string &command, int (*callback)(void *, int, char **, char **), void *callbackArg)
{
    static SQLite database;
    char *errorMsg = nullptr;
    if (sqlite3_exec(database.db, command.c_str(), callback, callbackArg, &errorMsg) != SQLITE_OK)
    {
        throw SQLiteEx(errorMsg);
    }
}

SQLite::~SQLite() noexcept
{
    sqlite3_close(db);
}
