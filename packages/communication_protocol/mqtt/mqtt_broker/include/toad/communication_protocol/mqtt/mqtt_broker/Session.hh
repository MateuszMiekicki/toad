#pragma once
#include "toad/communication_protocol/mqtt/mqtt_broker/interface/BrokerEventHandler.hh"

#include <memory>
#include <mqtt/broker/common_type.hpp>
using con_t = MQTT_NS::server<>::endpoint_t;
using con_sp_t = std::shared_ptr<con_t>;

namespace toad::communication_protocol::mqtt::mqtt_broker
{
class Session
{
  private:
  public:
    bool operator<(const Session&) const;
    con_sp_t session_;
    Session() = default;
    Session(con_sp_t);
    // Session(const Session&) = delete;
    // Session& operator=(const Session&) = delete;

    ~Session() = default;
    // Session(Session&&);
    // Session& operator=(Session&&);
};
} // namespace toad::communication_protocol::mqtt::mqtt_broker
