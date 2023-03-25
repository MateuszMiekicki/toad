#include "toad/communication_protocol/mqtt/broker/ClientConnectionHandler.hh"

#include "toad/communication_protocol/mqtt/Logger.hh"
#include "toad/communication_protocol/mqtt/broker/ConnectionManager.hh"

#include <iostream>
#include <mqtt/reason_code.hpp>

namespace toad::communication_protocol::mqtt
{
void ClientConnectionHandler::onConnect(std::shared_ptr<Connection>& connection)
{
    auto wp = connection->getWp();
    connection->get()->set_v5_connect_handler(
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
        // connectionManager_.addConnection(wp.lock());
        return true;
    });
}

void ClientConnectionHandler::onDisconnect(std::shared_ptr<Connection>& connection)
{
    auto wp = connection->getWp();
    connection->get()->set_v5_disconnect_handler(
        [this, wp](::MQTT_NS::v5::disconnect_reason_code reason_code, ::MQTT_NS::v5::properties /*props*/)
        {
        INFO_LOG("Client: {} disconnect, with reason code: {}",
                 wp.lock()->get_client_id(),
                 ::MQTT_NS::v5::disconnect_reason_code_to_str(reason_code));
        // connectionManager_.removeConnection(wp.lock());
    });
}

void ClientConnectionHandler::onClose(std::shared_ptr<Connection>& connection)
{
    auto wp = connection->getWp();
    connection->get()->set_close_handler(
        [this, wp]()
        {
        INFO_LOG("SERVER CLOSED");
        // connectionManager_.removeConnection(wp.lock());
    });
}

void ClientConnectionHandler::onError(std::shared_ptr<Connection>& connection)
{
    auto wp = connection->getWp();
    connection->get()->set_error_handler(
        [this, wp](::MQTT_NS::error_code ec)
        {
        INFO_LOG("SERVER error_code {}", ec.message());
        // connectionManager_.removeConnection(wp.lock());
    });
}

void ClientConnectionHandler::onPublish(std::shared_ptr<Connection>& connection)
{
    auto wp = connection->getWp();
    using packet_id_t = typename std::remove_reference_t<decltype(*connection->get())>::packet_id_t;
    connection->get()->set_v5_publish_handler(
        [this](::MQTT_NS::optional<packet_id_t>,
               ::MQTT_NS::publish_options,
               ::MQTT_NS::buffer,
               ::MQTT_NS::buffer,
               ::MQTT_NS::v5::properties)
        {
        // TRACE_LOG("publish received:\n"
        // "dup: {}\n"
        // "qos: {}\n"
        // "retain: {}\n"
        // "packed id: {}\n"
        // "topic name: {}\n"
        // "content: {}", publishOptions.get_dup(), publishOptions.get_qos(),
        // publishOptions.get_retain(), packedId?std::to_string(*packedId):"empty", topicName, content);
        return true;
    });
}

void ClientConnectionHandler::onSubscribe(std::shared_ptr<Connection>& connection)
{
    auto wp = connection->getWp();
    using packet_id_t = typename std::remove_reference_t<decltype(*connection->get())>::packet_id_t;
    connection->get()->set_v5_subscribe_handler( // use v5 handler
        [wp](packet_id_t packet_id,
             std::vector<::MQTT_NS::subscribe_entry>
                 entries,
             ::MQTT_NS::v5::properties /*props*/)
        {
        std::cout << "[server] subscribe received. packet_id: " << packet_id << std::endl;
        std::vector<::MQTT_NS::v5::suback_reason_code> res;
        res.reserve(entries.size());
        for(auto const& e: entries)
        {
            std::cout << "[server] topic_filter: " << e.topic_filter << " qos: " << e.subopts.get_qos()
                      << " rap: " << e.subopts.get_rap() << std::endl;
            res.emplace_back(::MQTT_NS::v5::qos_to_suback_reason_code(e.subopts.get_qos()));
        }
        wp.lock()->suback(packet_id, res);
        return true;
    });
}
} // namespace toad::communication_protocol::mqtt