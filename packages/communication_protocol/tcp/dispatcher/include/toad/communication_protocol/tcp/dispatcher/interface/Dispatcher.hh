#pragma once

namespace toad::communication_protocol::tcp::interface
{
class Dispatcher
{
  public:
    virtual ~Dispatcher() = default;
    virtual void dispatch() = 0;
};
} // namespace toad::communication_protocol::tcp::interface