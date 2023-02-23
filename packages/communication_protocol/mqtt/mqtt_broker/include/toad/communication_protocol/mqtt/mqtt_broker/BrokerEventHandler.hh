#pragma once
#include "toad/communication_protocol/mqtt/mqtt_broker/Session.hh"
#include "toad/communication_protocol/mqtt/mqtt_broker/Sessions.hh"
#include "toad/communication_protocol/mqtt/mqtt_broker/interface/BrokerEventHandler.hh"
#include "toad/communication_protocol/mqtt/mqtt_broker/interface/ClientEventHandler.hh"

namespace toad::communication_protocol::mqtt::mqtt_broker
{
class BrokerEventHandler : public interface::BrokerEventHandler
{
  private:
    Sessions sessions_;
    std::unique_ptr<interface::ClientEventHandler> clientEventHandler_{nullptr};

  public:
    BrokerEventHandler(std::unique_ptr<interface::ClientEventHandler>);
    // BrokerEventHandler(const BrokerEventHandler&) = delete;
    // BrokerEventHandler& operator=(const BrokerEventHandler&) = delete;
    // ~BrokerEventHandler()=default;
    // BrokerEventHandler()=default;
    // BrokerEventHandler(BrokerEventHandler&&);
    // BrokerEventHandler& operator=(BrokerEventHandler&&);

    // todo: move to other, independent class related with server abstract
    void onAccept(con_sp_t) override;
    void onError(errorCode_t) override;
};
} // namespace toad::communication_protocol::mqtt::mqtt_broker
