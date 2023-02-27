#pragma once
#include "toad/communication_protocol/mqtt/broker/interface/ClientConnectionHandler.hh"

namespace toad::communication_protocol::mqtt
{
class ClientConnectionHandler : public interface::ClientConnectionHandler
{
  public:
    void onConnect(Connection&) override;
};
} // namespace toad::communication_protocol::mqtt