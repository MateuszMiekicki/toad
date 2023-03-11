#pragma once
#include "toad/communication_protocol/mqtt/Logger.hh"

#include <mqtt_server_cpp.hpp>

namespace toad::communication_protocol::mqtt
{
// todo(miekicki): refactoring, split into separate files; look at the start and start_session functions
struct Connection
{
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    Connection(Connection&& con) : connection{std::move(con.connection)}
    {
    }

    Connection& operator=(Connection&& con)
    {
        connection = std::move(con.connection);
        return *this;
    }

    using con_t = ::MQTT_NS::server<>::endpoint_t;
    using con_sp_t = std::shared_ptr<con_t>;

    Connection(con_sp_t&& con) : connection(std::move(con))
    {
    }

    con_sp_t connection;

    void start()
    {
        connection->start_session(/*std::move(wp)*/);
    }
};
} // namespace toad::communication_protocol::mqtt