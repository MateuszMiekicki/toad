#pragma once

namespace toad::communication_protocol::mqtt
{
class Client;
} // namespace toad::communication_protocol::mqtt

namespace toad::communication_protocol::mqtt::interface
{
// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class IncomingClientValidator
{
  public:
    virtual ~IncomingClientValidator() = default;
    virtual bool accept(const Client&) const = 0;
};
} // namespace toad::communication_protocol::mqtt::interface