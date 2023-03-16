#pragma once

namespace toad::communication_protocol::mqtt
{
class Connection;
} // namespace toad::communication_protocol::mqtt

namespace toad::communication_protocol::mqtt::interface
{
// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class ClientConnectionHandler
{
  public:
    virtual ~ClientConnectionHandler() = default;
    virtual void onConnect(Connection&) = 0;
};
} // namespace toad::communication_protocol::mqtt::interface