#pragma once

namespace toad::storage::database::interface
{
class Transaction
{
  public:
    virtual ~Transaction() = default;
    virtual bool begin() = 0;
    virtual bool commit() = 0;
    virtual bool rollback() = 0;
};
} // namespace toad::storage::database::interface
