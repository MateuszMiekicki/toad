#include "toad/communication_protocol/mqtt/broker/ClientConnectionHandler.hh"

#include "toad/communication_protocol/mqtt/Logger.hh"
#include "toad/communication_protocol/mqtt/broker/ConnectionManager.hh"
#include "toad/communication_protocol/mqtt/broker/PublishOptions.hh"
#include "toad/communication_protocol/mqtt/broker/Subscription.hh"
#include "toad/communication_protocol/mqtt/broker/SubscriptionOptions.hh"

#include <exception>
#include <mqtt/reason_code.hpp>

namespace
{
toad::communication_protocol::mqtt::QualityOfService convert(const ::MQTT_NS::qos& qos)
{
    using namespace toad::communication_protocol::mqtt;
    switch(qos)
    {
        case ::MQTT_NS::qos::at_most_once:
            return QualityOfService::atMostOnce;
        case ::MQTT_NS::qos::at_least_once:
            return QualityOfService::atLeastOnce;
        case ::MQTT_NS::qos::exactly_once:
            return QualityOfService::exactlyOnce;
        default:
            throw std::exception();
    }
}

toad::communication_protocol::mqtt::RetainAsPublished convert(const ::MQTT_NS::rap& rap)
{
    using namespace toad::communication_protocol::mqtt;
    switch(rap)
    {
        case ::MQTT_NS::rap::dont:
            return RetainAsPublished::discard;
        case ::MQTT_NS::rap::retain:
            return RetainAsPublished::retain;
        default:
            throw std::exception();
    }
}

toad::communication_protocol::mqtt::SubscriptionOptions convertToSubscriptionOptions(const ::MQTT_NS::qos& qos,
                                                                                     const ::MQTT_NS::rap& rap)
{
    return {convert(qos), convert(rap)};
}

toad::communication_protocol::mqtt::Duplicate convert(const ::MQTT_NS::dup& dup)
{
    using namespace toad::communication_protocol::mqtt;
    switch(dup)
    {
        case ::MQTT_NS::dup::no:
            return Duplicate::no;
        case ::MQTT_NS::dup::yes:
            return Duplicate::yes;
        default:
            throw std::exception();
    }
}

toad::communication_protocol::mqtt::RetainAsPublished convert(const ::MQTT_NS::retain& retain)
{
    using namespace toad::communication_protocol::mqtt;
    switch(retain)
    {
        case ::MQTT_NS::retain::no:
            return RetainAsPublished::discard;
        case ::MQTT_NS::retain::yes:
            return RetainAsPublished::retain;
        default:
            throw std::exception();
    }
}

toad::communication_protocol::mqtt::PublishOptions
convertToPublishOptions(const ::MQTT_NS::publish_options& publishOptions)
{
    return {convert(publishOptions.get_qos()), convert(publishOptions.get_retain()), convert(publishOptions.get_dup())};
}

toad::communication_protocol::mqtt::Subscription
convertToSubscription(std::shared_ptr<toad::communication_protocol::mqtt::Connection> connection,
                      const ::MQTT_NS::buffer& topic, const ::MQTT_NS::qos& qos, const ::MQTT_NS::rap& rap)
{
    return {connection, topic.data(), convertToSubscriptionOptions(qos, rap)};
}

std::string_view toStringView(const ::MQTT_NS::buffer& buffer)
{
    return {buffer.data(), buffer.size()};
}
} // namespace

namespace toad::communication_protocol::mqtt
{
void ClientConnectionHandler::onConnect(std::shared_ptr<Connection> connection)
{
    connection->get()->set_connect_handler(
        [this, connection](::MQTT_NS::buffer clientId,
                           ::MQTT_NS::optional<::MQTT_NS::buffer> const&,
                           ::MQTT_NS::optional<::MQTT_NS::buffer> const&,
                           ::MQTT_NS::optional<::MQTT_NS::will>,
                           bool,
                           std::uint16_t)
        {
        INFO_LOG("new connection clientId: {}", clientId.data());
        if(not connectionManager_.acceptConnection(clientId.data()))
        {
            connection->get()->connack(false, ::MQTT_NS::connect_return_code::identifier_rejected);
            return false;
        }
        connection->get()->connack(false, ::MQTT_NS::connect_return_code::accepted);

        connectionManager_.addConnection(connection);
        return true;
    });
}

void ClientConnectionHandler::onDisconnect(std::shared_ptr<Connection> connection)
{
    connection->get()->set_disconnect_handler(
        [this, connection]()
        {
        INFO_LOG("Client: {} disconnect", connection->get()->get_client_id());
        connectionManager_.removeConnection(connection);
    });
}

void ClientConnectionHandler::onClose(std::shared_ptr<Connection> connection)
{
    connection->get()->set_close_handler(
        [this, connection]()
        {
        INFO_LOG("SERVER CLOSED");
        connectionManager_.removeConnection(connection);
    });
}

void ClientConnectionHandler::onError(std::shared_ptr<Connection> connection)
{
    connection->get()->set_error_handler(
        [this, connection](::MQTT_NS::error_code ec)
        {
        INFO_LOG("SERVER error_code {}", ec.message());
        connectionManager_.removeConnection(connection);
    });
}

void ClientConnectionHandler::onPublish(std::shared_ptr<Connection> connection)
{
    using packet_id_t = typename std::remove_reference_t<decltype(*connection->get())>::packet_id_t;
    connection->get()->set_publish_handler(
        [this](::MQTT_NS::optional<packet_id_t>,
               ::MQTT_NS::publish_options publishOptions,
               ::MQTT_NS::buffer topic,
               ::MQTT_NS::buffer content)
        {
        subscriptionManager_.publish(toStringView(topic),
                                     toStringView(content),
                                     convertToPublishOptions(publishOptions));
        // TRACE_LOG("publish received:\n"
        // "dup: {}\n"
        // "qos: {}\n"
        // "retain: {}\n"
        // "packed id: {}\n"
        // "topic name: {}\n"
        // "content: {}", publishOptions.get_dup(), publishOptions.get_qos(),
        // publishOptions.get_retain(), packedId?std::to_string(*packedId):"empty", topicName, content);
        TRACE_LOG("{}", convertToPublishOptions(publishOptions).qualityOfService);
        return true;
    });
}

void ClientConnectionHandler::onSubscribe(std::shared_ptr<Connection> connection)
{
    using packet_id_t = typename std::remove_reference_t<decltype(*connection->get())>::packet_id_t;
    connection->get()->set_subscribe_handler(
        [this, connection](packet_id_t packet_id, std::vector<::MQTT_NS::subscribe_entry> entries)
        {
        std::vector<::MQTT_NS::suback_return_code> res;
        res.reserve(entries.size());

        for(auto const& entry: entries)
        {
            res.emplace_back(::MQTT_NS::qos_to_suback_return_code(entry.subopts.get_qos()));
            auto sub =
                convertToSubscription(connection, entry.topic_filter, entry.subopts.get_qos(), entry.subopts.get_rap());
            subscriptionManager_.subscribe(sub);
        }
        connection->get()->suback(packet_id, res);
        return true;
    });
}
} // namespace toad::communication_protocol::mqtt