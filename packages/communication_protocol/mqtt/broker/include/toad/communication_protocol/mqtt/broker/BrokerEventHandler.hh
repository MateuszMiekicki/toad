#pragma once
#include "toad/communication_protocol/mqtt/broker/interface/BrokerEventHandler.hh"
#include "toad/communication_protocol/mqtt/broker/interface/ClientConnectionHandler.hh"

#include <memory>

namespace toad::communication_protocol
{
class ErrorCode;
} // namespace toad::communication_protocol

namespace toad::communication_protocol::mqtt
{
class Connection;
} // namespace toad::communication_protocol::mqtt

namespace toad::communication_protocol::mqtt
{
class BrokerEventHandler : public interface::BrokerEventHandler
{
  private:
    std::unique_ptr<interface::ClientConnectionHandler> clientConnectionHandler_;

  public:
    BrokerEventHandler(std::unique_ptr<interface::ClientConnectionHandler>);
    void onAccept(Connection) override;
    void onError(ErrorCode) override;
};
} // namespace toad::communication_protocol::mqtt
