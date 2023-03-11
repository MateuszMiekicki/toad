#pragma once

namespace toad::communication_protocol
{
class ErrorCode;
} // namespace toad::communication_protocol

namespace toad::communication_protocol::mqtt
{
class Connection;
} // namespace toad::communication_protocol::mqtt

namespace toad::communication_protocol::mqtt::interface
{
class BrokerEventHandler
{
  public:
    virtual ~BrokerEventHandler() = default;
    virtual void onAccept(Connection&) = 0;
    virtual void onError(ErrorCode) = 0;
};
} // namespace toad::communication_protocol::mqtt::interface