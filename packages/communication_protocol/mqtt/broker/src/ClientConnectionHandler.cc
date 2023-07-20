#include "toad/communication_protocol/mqtt/broker/ClientConnectionHandler.hh"
#include "rapidjson/error/error.h" // rapidjson::ParseResult
#include "toad/communication_protocol/mqtt/broker/ConnectionManager.hh"
#include "toad/communication_protocol/mqtt/broker/PublishOptions.hh"
#include "toad/communication_protocol/mqtt/broker/Subscription.hh"
#include "toad/communication_protocol/mqtt/broker/SubscriptionOptions.hh"
#include "toad/communication_protocol/mqtt/client_validator/Client.hh"
#include "toad/communication_protocol/mqtt/Logger.hh"
#include "toad/storage/database/questdb/QuestDB.hh"
#include <exception>
#include <mqtt/reason_code.hpp>
#include <rapidjson/document.h>

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

toad::communication_protocol::mqtt::Subscription
convertToSubscription(std::shared_ptr<toad::communication_protocol::mqtt::Connection> connection,
                      const ::MQTT_NS::buffer& topic)
{
    return {connection, topic.data(), {}};
}

std::string_view toStringView(const ::MQTT_NS::buffer& buffer)
{
    return {buffer.data(), buffer.size()};
}

toad::communication_protocol::mqtt::optionalAuthn
convertToAuthenticationData(const ::MQTT_NS::optional<::MQTT_NS::buffer>& username,
                            const ::MQTT_NS::optional<::MQTT_NS::buffer>& password)
{
    if(username)
    {
        return toad::communication_protocol::mqtt::AuthenticationData{
            username.value().data(),
            password.get_value_or(::MQTT_NS::buffer()).data()};
    }
    return std::nullopt;
}

toad::communication_protocol::mqtt::Client buildClient(const ::MQTT_NS::buffer& clientId,
                                                       const ::MQTT_NS::optional<::MQTT_NS::buffer>& username,
                                                       const ::MQTT_NS::optional<::MQTT_NS::buffer>& password)
{
    return {clientId.data(), convertToAuthenticationData(username, password)};
}

auto isValidJson(const std::string& json_str)
{
    auto out = std::optional<rapidjson::Document>();

    rapidjson::Document document;
    /*rapidjson::ParseResult ok =*/document.Parse(json_str.c_str());
    if(!document.HasParseError())
    {
        out = std::make_optional<rapidjson::Document>(std::move(document));
    }
    else
    {
        WARN_LOG("Error during parsing JSON: {}", "ok.Code()");
    }
    return out;
}

auto buildSensorDataEntity(const std::string& json)
{
    auto out = std::optional<toad::storage::database::entities::sensorDatalist_t>();
    if(const auto parsedJson = isValidJson(json); parsedJson.has_value())
    {
        if(parsedJson.value().IsArray())
        {
            toad::storage::database::entities::sensorDatalist_t sensorDatalist;
            sensorDatalist.reserve(parsedJson.value().Size());
            for(rapidjson::SizeType i = 0; i < parsedJson.value().Size(); i++)
            {
                if(parsedJson.value()[i].IsObject())
                {
                    toad::storage::database::entities::SensorData data;
                    if(parsedJson.value()[i].HasMember("mac_address") &&
                       parsedJson.value()[i]["mac_address"].IsString())
                    {
                        data.mac_address = parsedJson.value()[i]["mac_address"].GetString();
                    }
                    if(parsedJson.value()[i].HasMember("pin_number") && parsedJson.value()[i]["pin_number"].IsInt64())
                    {
                        data.pin_number = parsedJson.value()[i]["pin_number"].GetInt64();
                    }
                    if(parsedJson.value()[i].HasMember("value") && parsedJson.value()[i]["value"].IsNumber())
                    {
                        data.value = parsedJson.value()[i]["value"].GetDouble();
                    }
                    sensorDatalist.emplace_back(std::move(data));
                }
            }
            out = std::make_optional(sensorDatalist);
        }
    }
    return out;
}
} // namespace

namespace toad::communication_protocol::mqtt
{
ClientConnectionHandler::ClientConnectionHandler(std::unique_ptr<ConnectionManager> connectionManager) :
    storage_(std::make_unique<storage::database::QuestDB>("questdb", "9009")),
    connectionManager_{std::move(connectionManager)}, subscriptionManager_{}
{
}

void ClientConnectionHandler::onConnect(std::shared_ptr<Connection> connection)
{
    connection->get()->set_connect_handler(
        [this, connection](::MQTT_NS::buffer clientId,
                           const ::MQTT_NS::optional<::MQTT_NS::buffer>& username,
                           const ::MQTT_NS::optional<::MQTT_NS::buffer>& password,
                           ::MQTT_NS::optional<::MQTT_NS::will>,
                           bool,
                           std::uint16_t)
        {
        INFO_LOG("new connection clientId: {}", clientId.data());
        if(not connectionManager_->acceptConnection(buildClient(clientId, username, password)))
        {
            connection->get()->connack(false, ::MQTT_NS::connect_return_code::identifier_rejected);
            return false;
        }
        connection->get()->connack(false, ::MQTT_NS::connect_return_code::accepted);
        connectionManager_->addConnection(connection);
        return true;
    });
}

void ClientConnectionHandler::onDisconnect(std::shared_ptr<Connection> connection)
{
    connection->get()->set_disconnect_handler(
        [this, connection]()
        {
        INFO_LOG("Client: {} disconnect", connection->get()->get_client_id());
        connectionManager_->removeConnection(connection);
    });
}

void ClientConnectionHandler::onClose(std::shared_ptr<Connection> connection)
{
    connection->get()->set_close_handler(
        [this, connection]()
        {
        INFO_LOG("SERVER CLOSED");
        connectionManager_->removeConnection(connection);
    });
}

void ClientConnectionHandler::onError(std::shared_ptr<Connection> connection)
{
    connection->get()->set_error_handler(
        [this, connection](::MQTT_NS::error_code ec)
        {
        INFO_LOG("SERVER error_code {}", ec.message());
        connectionManager_->removeConnection(connection);
    });
}

void ClientConnectionHandler::onPublish(std::shared_ptr<Connection> connection)
{
    using packet_id_t = typename std::remove_reference_t<decltype(*connection->get())>::packet_id_t;
    connection->get()->set_publish_handler(
        [this, connection](::MQTT_NS::optional<packet_id_t>,
                           ::MQTT_NS::publish_options publishOptions,
                           ::MQTT_NS::buffer topic,
                           ::MQTT_NS::buffer content)
        {
        INFO_LOG("clientId: {} publishes in {}", connection->get()->get_client_id(), toStringView(topic));
        TRACE_LOG(R"({{"{}": {{"topic": "{}", "content": {}, {}}}}})",
                  connection->get()->get_client_id(),
                  toStringView(topic),
                  toStringView(content),
                  convertToPublishOptions(publishOptions));
        subscriptionManager_.publish(toStringView(topic),
                                     toStringView(content),
                                     convertToPublishOptions(publishOptions));
        if(const auto output = buildSensorDataEntity({content.data(), content.size()}); output.has_value())
        {
            for(const auto& data: *output)
            {
                storage_->insert(data);
            }
            storage_->commit();
        }
        return true;
    });
}

void ClientConnectionHandler::onSubscribe(std::shared_ptr<Connection> connection)
{
    using packet_id_t = typename std::remove_reference_t<decltype(*connection->get())>::packet_id_t;
    connection->get()->set_subscribe_handler(
        [this, connection](packet_id_t packet_id, std::vector<::MQTT_NS::subscribe_entry> entries)
        {
        INFO_LOG("clientId: {} subscribe {}",
                 connection->get()->get_client_id(),
                 toStringView(entries.back().topic_filter));

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

void ClientConnectionHandler::onUnsubscribe(std::shared_ptr<Connection> connection)
{
    connection->get()->set_unsubscribe_handler(
        [this, connection](short unsigned int packet_id, std::vector<::MQTT_NS::unsubscribe_entry> entries)
        {
        for(auto const& entry: entries)
        {
            auto sub = convertToSubscription(connection, entry.topic_filter);
            subscriptionManager_.unsubscribe(sub);
        }
        connection->get()->unsuback(packet_id);
        return true;
    });
}
} // namespace toad::communication_protocol::mqtt