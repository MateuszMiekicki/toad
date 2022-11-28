#pragma once

namespace toad::storage::database::interface
{
class Database
{
  public:
    virtual ~Database() = default;
    virtual auto connect() -> bool = 0;
    virtual auto isConnected() -> bool = 0;
    virtual auto reconnect() -> bool = 0;
    virtual auto disconnect() -> bool = 0;
};
} // namespace toad::storage::database::interface
