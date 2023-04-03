#pragma once
#include "toad/communication_protocol/mqtt/broker/ConnectionManager.hh"
#include "toad/communication_protocol/mqtt/broker/interface/ClientConnectionHandler.hh"
#include "toad/communication_protocol/mqtt/broker/SubscriptionManager.hh"

namespace toad::communication_protocol::mqtt
{
class ClientConnectionHandler : public interface::ClientConnectionHandler
{
  private:
    ConnectionManager connectionManager_;
    SubscriptionManager subscriptionManager_;

  public:
    void onClose(std::shared_ptr<Connection> connection) override;
    void onError(std::shared_ptr<Connection> connection) override;
    void onConnect(std::shared_ptr<Connection>) override;
    void onDisconnect(std::shared_ptr<Connection>) override;
    void onPublish(std::shared_ptr<Connection>) override;
    void onSubscribe(std::shared_ptr<Connection>) override;
};
} // namespace toad::communication_protocol::mqtt