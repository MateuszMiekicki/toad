#include "toad/communication_protocol/mqtt/broker/ClientConnectionHandler.hh"
#include <mqtt/reason_code.hpp>
#include "toad/communication_protocol/mqtt/Logger.hh"
#include "toad/communication_protocol/mqtt/broker/ConnectionManager.hh"

namespace toad::communication_protocol::mqtt
{
void ClientConnectionHandler::onConnect(Connection& connection)
{
    auto wp = connection.getWp();
    connection.get()->set_v5_connect_handler(
        [this, wp](::MQTT_NS::buffer clientId,
                   ::MQTT_NS::optional<::MQTT_NS::buffer> const&,
                   ::MQTT_NS::optional<::MQTT_NS::buffer> const&,
                   ::MQTT_NS::optional<::MQTT_NS::will>,
                   bool,
                   std::uint16_t,
                   ::MQTT_NS::v5::properties /*props*/)
        {
        INFO_LOG("new connection clientId: {}", clientId.data());
        if(not connectionManager_.acceptConnection(clientId.data()))
        {
            wp.lock()->connack(false, ::MQTT_NS::v5::connect_reason_code::client_identifier_not_valid);
            return false;
        }
        wp.lock()->connack(false, ::MQTT_NS::v5::connect_reason_code::success);
        connectionManager_.addConnection(wp.lock());
        return true;
    });
}
    void ClientConnectionHandler::onDisconnect(Connection& connection) 
    {
    auto wp = connection.getWp();
            connection.get()->set_v5_disconnect_handler( // use v5 handler
                [this, wp]
                (::MQTT_NS::v5::disconnect_reason_code reason_code, ::MQTT_NS::v5::properties /*props*/) {
                        INFO_LOG("Client: {} disconnect, with reason code: {}", wp.lock()->get_client_id(), ::MQTT_NS::v5::disconnect_reason_code_to_str(reason_code));
                    // close_proc(connections, subs, sp);
                    connectionManager_.removeConnection(wp.lock());
                });
    }


} // namespace toad::communication_protocol::mqtt