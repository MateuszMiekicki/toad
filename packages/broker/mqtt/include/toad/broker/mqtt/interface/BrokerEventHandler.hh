#pragma once
#include <mqtt_server_cpp.hpp>
#include "toad/network/endpoint/Endpoint.hh"

using errorCode_t = MQTT_NS::error_code;

using con_t = MQTT_NS::server<>::endpoint_t;
using con_sp_t = std::shared_ptr<con_t>;

namespace toad::broker::mqtt::interface
{
class BrokerEventHandler
{
  public:
    virtual ~BrokerEventHandler() = default;

    // todo: move to other, independent class related with server abstract
    virtual void onAccept(con_sp_t) = 0;
    virtual void onError(errorCode_t) = 0;
};
} // namespace toad::broker::mqtt::interface