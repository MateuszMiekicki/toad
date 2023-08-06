#pragma once

namespace toad::communication_protocol::tcp
{
class Message;
} // namespace toad::communication_protocol::tcp

namespace toad::communication_protocol::tcp::interface
{
class Sender
{
  public:
    virtual void send(const Message&) = 0;
    virtual ~Sender() = default;
};
} // namespace toad::communication_protocol::tcp::interface