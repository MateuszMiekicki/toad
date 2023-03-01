#include "toad/communication_protocol/mqtt/broker/ClientConnectionHandler.hh"

#include "toad/communication_protocol/mqtt/Logger.hh"
#include "toad/communication_protocol/mqtt/broker/Connection.hh"

#include <iostream>

namespace toad::communication_protocol::mqtt
{
void ClientConnectionHandler::onConnect(Connection& connection)
{
    std::cout << "[server] accept" << std::endl;
    // Pass spep to keep lifetime.
    // It makes sure wp.lock() never return nullptr in the handlers below
    // including close_handler and error_handler.
    connection.connection->start_session();

    // set connection (lower than MQTT) level handlers
    connection.connection->set_close_handler(
        []()
        {
        std::cout << "[server] closed." << std::endl;
    });
    connection.connection->set_error_handler(
        [](::MQTT_NS::error_code ec)
        {
        std::cout << "[server] error: " << ec.message() << std::endl;
    });

    // set MQTT level handlers
    connection.connection->set_v5_connect_handler( // use v5 handler
        [](::MQTT_NS::buffer client_id,
           ::MQTT_NS::optional<::MQTT_NS::buffer> const& username,
           ::MQTT_NS::optional<::MQTT_NS::buffer> const& password,
           ::MQTT_NS::optional<::MQTT_NS::will>,
           bool clean_start,
           std::uint16_t keep_alive,
           ::MQTT_NS::v5::properties /*props*/)
        {
        using namespace ::MQTT_NS::literals;
        std::cout << "[server] client_id    : " << client_id << std::endl;
        std::cout << "[server] username     : " << (username ? username.value() : "none"_mb) << std::endl;
        std::cout << "[server] password     : " << (password ? password.value() : "none"_mb) << std::endl;
        std::cout << "[server] clean_start  : " << std::boolalpha << clean_start << std::endl;
        std::cout << "[server] keep_alive   : " << keep_alive << std::endl;
        return true;
    });
    connection.connection->set_v5_disconnect_handler( // use v5 handler
        [](::MQTT_NS::v5::disconnect_reason_code reason_code, ::MQTT_NS::v5::properties /*props*/)
        {
        std::cout << "[server] disconnect received."
                  << " reason_code: " << reason_code << std::endl;
    });
}
} // namespace toad::communication_protocol::mqtt