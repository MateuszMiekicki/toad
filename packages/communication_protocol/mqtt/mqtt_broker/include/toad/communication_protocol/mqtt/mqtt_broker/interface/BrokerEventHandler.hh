#pragma once
#include "toad/network/endpoint/Endpoint.hh"

#include <mqtt_server_cpp.hpp>

using errorCode_t = MQTT_NS::error_code;

using con_t = MQTT_NS::server<>::endpoint_t;
using con_sp_t = std::shared_ptr<con_t>;

namespace toad::communication_protocol::mqtt::mqtt_broker::interface
{
class BrokerEventHandler
{
  public:
    virtual ~BrokerEventHandler() = default;

    // todo: move to other, independent class related with server abstract
    virtual void onAccept(con_sp_t) = 0;
    virtual void onError(errorCode_t) = 0;
};
} // namespace toad::communication_protocol::mqtt::mqtt_broker::interface