#include "ID.hpp"
#include "Util.hpp"
#include "SQLite.hpp"

ID::ID(int id) : id(id)
{
    Expects(id >= 0, "ID objects may not be initialized with negative values.");
}

ID::ID(const std::string &tableName)
{
    SQLite::run(
        "SELECT seq FROM sqlite_sequence WHERE name = " + quote(tableName) + ";",
        [](void *id, int, char **val, char **) {
            *((int *)id) = atoi(*val) + 1;
            return 0;
        },
        &id);
}

ID::operator int() const
{
    return id;
}

bool ID::operator==(const ID &other) const noexcept
{
    return id == other.id;
}