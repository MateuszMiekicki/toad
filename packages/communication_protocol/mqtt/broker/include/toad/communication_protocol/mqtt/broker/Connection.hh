#pragma once
#include <mqtt_server_cpp.hpp>

namespace toad::communication_protocol::mqtt
{
struct Connection
{
    using con_t = ::MQTT_NS::server<>::endpoint_t;
    using con_sp_t = std::shared_ptr<con_t>;

    Connection(con_sp_t con) : connection(std::move(con))
    {
    }

    con_sp_t connection;
};
} // namespace toad::communication_protocol::mqtt