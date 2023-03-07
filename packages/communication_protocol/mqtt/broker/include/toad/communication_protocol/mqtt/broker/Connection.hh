#pragma once
#include <mqtt_server_cpp.hpp>

namespace toad::communication_protocol::mqtt
{
// todo(miekicki): refactoring, split into separate files; look at the start and start_session functions
struct Connection
{
    using con_sp_t = std::shared_ptr<::MQTT_NS::server<>::endpoint_t>;

    Connection(con_sp_t con) : connection(std::move(con))
    {
    }

    con_sp_t connection;
    void start()
    {
        connection->start_session();
    }
};
} // namespace toad::communication_protocol::mqtt