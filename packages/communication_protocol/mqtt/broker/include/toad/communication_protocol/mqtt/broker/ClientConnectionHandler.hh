#pragma once
#include "toad/communication_protocol/mqtt/broker/ConnectionManager.hh"
#include "toad/communication_protocol/mqtt/broker/interface/ClientConnectionHandler.hh"

namespace toad::communication_protocol::mqtt
{
class ClientConnectionHandler : public interface::ClientConnectionHandler
{
  private:
    ConnectionManager connectionManager_;

  public:
    void onConnect(Connection&) override;
    void onDisconnect(Connection&) override;
};
} // namespace toad::communication_protocol::mqtt