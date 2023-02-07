#pragma once
#include <mqtt/broker/common_type.hpp>
#include <memory>
#include "toad/broker/mqtt/interface/BrokerEventHandler.hh"
using con_t = MQTT_NS::server<>::endpoint_t;
using con_sp_t = std::shared_ptr<con_t>;
namespace toad::broker::mqtt
{
class Session
{
  private:
  public:
    bool operator<(const Session&)const;
    con_sp_t session_;
    Session()=default;
    Session(con_sp_t);
    // Session(const Session&) = delete;
    // Session& operator=(const Session&) = delete;

    ~Session() = default;
    // Session(Session&&);
    // Session& operator=(Session&&);
};
} // namespace toad::server::broker
