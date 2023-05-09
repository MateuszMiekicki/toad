#pragma once

namespace toad::storage::database::interface
{
class Database
{
    virtual ~Database() = default;
    virtual void insert() = 0;
    virtual void commit() = 0;
    virtual void rollback() = 0;
};
} // namespace toad::storage::database::interface