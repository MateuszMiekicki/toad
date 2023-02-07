#pragma once
#include "toad/broker/mqtt/interface/BrokerEventHandler.hh"
#include "toad/broker/mqtt/Session.hh"
#include "toad/broker/mqtt/Sessions.hh"


namespace toad::broker::mqtt
{
class BrokerEventHandler : public interface::BrokerEventHandler
{
  private:
  Sessions sessions_;
  public:
  BrokerEventHandler() = default;
    // BrokerEventHandler(const BrokerEventHandler&) = delete;
    // BrokerEventHandler& operator=(const BrokerEventHandler&) = delete;
    // ~BrokerEventHandler()=default;
    // BrokerEventHandler()=default;
    // BrokerEventHandler(BrokerEventHandler&&);
    // BrokerEventHandler& operator=(BrokerEventHandler&&);

    // todo: move to other, independent class related with server abstract
     void onAccept(con_sp_t)override;
     void onError(errorCode_t)override;
};
} // namespace toad::server::broker
