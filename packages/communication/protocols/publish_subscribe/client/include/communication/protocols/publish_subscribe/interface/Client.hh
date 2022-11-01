#pragma once

namespace toad::communication::protocols::publish_subscribe::interface
{
class Client
{
  public:
    ~Client() = default;

    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual bool reestablishConnection() = 0;
};
} // namespace toad::communication::protocols::publish_subscribe::interface