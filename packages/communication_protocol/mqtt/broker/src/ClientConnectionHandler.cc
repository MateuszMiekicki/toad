#include "toad/communication_protocol/mqtt/broker/ClientConnectionHandler.hh"

#include "toad/communication_protocol/mqtt/Logger.hh"
#include "toad/communication_protocol/mqtt/broker/ConnectionManager.hh"

#include <iostream>

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
        if(clientId.empty())
        {
            wp.lock()->connack(false, ::MQTT_NS::v5::connect_reason_code::client_identifier_not_valid);
            return false;
        }
        // using namespace ::MQTT_NS::literals;
        // ::MQTT_NS::v5::properties connack_ps {
        //     ::MQTT_NS::v5::property::session_expiry_interval(10),
        //     ::MQTT_NS::v5::property::receive_maximum(10),
        //     ::MQTT_NS::v5::property::maximum_qos(::MQTT_NS::qos::exactly_once),
        //     ::MQTT_NS::v5::property::retain_available(true),
        //     ::MQTT_NS::v5::property::maximum_packet_size(100),
        //     ::MQTT_NS::v5::property::assigned_client_identifier("test cid"_mb),
        //     ::MQTT_NS::v5::property::topic_alias_maximum(0),
        //     ::MQTT_NS::v5::property::reason_string("test connect success"_mb),
        //     ::MQTT_NS::v5::property::user_property("key1"_mb, "val1"_mb),
        //     ::MQTT_NS::v5::property::user_property("key2"_mb, "val2"_mb),
        //     ::MQTT_NS::v5::property::wildcard_subscription_available(false),
        //     ::MQTT_NS::v5::property::subscription_identifier_available(false),
        //     ::MQTT_NS::v5::property::shared_subscription_available(false),
        //     ::MQTT_NS::v5::property::server_keep_alive(5),
        //     ::MQTT_NS::v5::property::response_information("test response information"_mb),
        //     ::MQTT_NS::v5::property::server_reference("test server reference"_mb),
        //     ::MQTT_NS::v5::property::authentication_method("test authentication method"_mb),
        //     ::MQTT_NS::v5::property::authentication_data("test authentication data"_mb)
        // };
        wp.lock()->connack(false, ::MQTT_NS::v5::connect_reason_code::success /*,std::move(connack_ps)*/);
        connectionManager_.addConnection(wp.lock());
        return true;
    });
}
} // namespace toad::communication_protocol::mqtt