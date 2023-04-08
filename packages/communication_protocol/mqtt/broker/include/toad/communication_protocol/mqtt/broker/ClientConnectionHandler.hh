#pragma once
#include "toad/communication_protocol/mqtt/broker/ConnectionManager.hh"
#include "toad/communication_protocol/mqtt/broker/interface/ClientConnectionHandler.hh"
#include "toad/communication_protocol/mqtt/broker/SubscriptionManager.hh"

namespace toad::communication_protocol::mqtt
{
class ClientConnectionHandler : public interface::ClientConnectionHandler
{
  private:
    std::unique_ptr<ConnectionManager> connectionManager_{nullptr};
    SubscriptionManager subscriptionManager_{};

  public:
    ClientConnectionHandler(std::unique_ptr<ConnectionManager>);
    void onClose(std::shared_ptr<Connection> connection) override;
    void onError(std::shared_ptr<Connection> connection) override;
    void onConnect(std::shared_ptr<Connection>) override;
    void onDisconnect(std::shared_ptr<Connection>) override;
    void onPublish(std::shared_ptr<Connection>) override;
    void onSubscribe(std::shared_ptr<Connection>) override;
    void onUnsubscribe(std::shared_ptr<Connection>) override;
};
} // namespace toad::communication_protocol::mqtt