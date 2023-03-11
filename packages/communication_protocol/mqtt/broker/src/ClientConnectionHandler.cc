#include "toad/communication_protocol/mqtt/broker/ClientConnectionHandler.hh"

#include "toad/communication_protocol/mqtt/Logger.hh"
#include "toad/communication_protocol/mqtt/broker/Connection.hh"

#include <iostream>

namespace toad::communication_protocol::mqtt
{
void ClientConnectionHandler::onConnect(Connection& connection)
{
    DEBUG_LOG("has value {}", connection.connection != nullptr);
    // auto& ep = connection.connection.get();
    std::weak_ptr<Connection::con_t> wp(connection.connection);

    connection.connection->set_v5_connect_handler(
        [wp](::MQTT_NS::buffer client_id,
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
        wp.lock()->connack(false, ::MQTT_NS::v5::connect_reason_code::success);
        DEBUG_LOG("sended");
        return true;
    });
}
} // namespace toad::communication_protocol::mqtt