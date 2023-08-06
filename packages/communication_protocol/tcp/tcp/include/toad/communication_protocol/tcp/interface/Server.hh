#pragma once

namespace toad::communication_protocol::tcp::interface
{
class Server
{
  public:
    virtual ~Server() = default;
    virtual void start() = 0;
};
} // namespace toad::communication_protocol::tcp::interface