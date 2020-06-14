#include "IRecord.hpp"

void IRecord::insert() const
{
    SQLite::run("INSERT INTO " + getTable() + " (" + insertColumns() + ") VALUES (" + insertValues() + ");");
}

void IRecord::update() const
{
    SQLite::run("UPDATE " + getTable() + " SET " + updateValues() + " " + Condition::unpack(updateConditions()) + ";");
}

void IRecord::remove() const
{
    SQLite::run("DELETE FROM " + getTable() + " " + Condition::unpack(removeConditions()) + ";");
}