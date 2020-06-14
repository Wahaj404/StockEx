#ifndef __IRECORD_HPP__
#define __IRECORD_HPP__

#include "Util.hpp"
#include "SQLite.hpp"
#include "Condition.hpp"
#include <type_traits>

#define IRecord_OVERRIDE                                               \
    const std::string &getTable() const noexcept override;             \
    const std::string &insertColumns() const noexcept override;        \
    std::string insertValues() const noexcept override;                \
    std::string updateValues() const noexcept override;                \
    std::vector<Condition> updateConditions() const noexcept override; \
    std::vector<Condition> removeConditions() const noexcept override;

class IRecord
{
private:
    virtual const std::string &getTable() const noexcept = 0;
    virtual const std::string &insertColumns() const noexcept = 0;
    virtual std::string insertValues() const noexcept = 0;
    virtual std::string updateValues() const noexcept = 0;
    virtual std::vector<Condition> updateConditions() const noexcept = 0;
    virtual std::vector<Condition> removeConditions() const noexcept = 0;

protected:
    void insert() const;
    void remove() const;

public:
    void update() const;

    template <class RecordType>
    static std::vector<RecordType> select(const std::vector<Condition> &conditions = {});
};

template <class RecordType>
std::vector<RecordType> IRecord::select(const std::vector<Condition> &conditions)
{
    static_assert(std::is_base_of<IRecord, RecordType>::value,
                  "Only classes inherited from IRecord may use  IRecord::select().");
    std::vector<RecordType> ret;
    SQLite::run(
        "SELECT * FROM " + RecordType::TableName + " " + Condition::unpack(conditions) + ";",
        [](void *retPtr, int columnCount, char **columnValues, char **) {
            ((std::vector<RecordType> *)retPtr)->emplace_back(std::vector<std::string>(columnValues, columnValues + columnCount));
            return 0;
        },
        &ret);
    return ret;
}

#endif // __IRECORD_H__
