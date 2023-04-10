#pragma once
#include "toad/communication_protocol/mqtt/broker/PublishOptions.hh"
#include <mqtt_server_cpp.hpp>
#include <vector>

namespace
{
::MQTT_NS::qos convert(toad::communication_protocol::mqtt::QualityOfService qos)
{
    using namespace toad::communication_protocol::mqtt;
    switch(qos)
    {
        case QualityOfService::atMostOnce:
            return ::MQTT_NS::qos::at_most_once;
        case QualityOfService::atLeastOnce:
            return ::MQTT_NS::qos::at_least_once;
        case QualityOfService::exactlyOnce:
            return ::MQTT_NS::qos::exactly_once;
        default:
            throw std::exception();
    }
}
} // namespace

namespace toad::communication_protocol::mqtt
{
using topic_t = std::string_view;
using content_t = std::string_view;

// todo(miekicki): refactoring, split into separate files; look at the start and start_session functions
class Connection
{
  public:
    using con_t = ::MQTT_NS::server<>::endpoint_t;
    using con_sp_t = std::shared_ptr<con_t>;
    using con_wp_t = std::weak_ptr<con_t>;

  private:
    con_sp_t connection_{nullptr};

  public:
    virtual ~Connection() = default;
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    Connection(Connection&& con) : connection_{std::move(con.connection_)}
    {
    }

    Connection& operator=(Connection&& con)
    {
        connection_ = std::move(con.connection_);
        return *this;
    }

    Connection(con_sp_t&& con) : connection_(std::move(con))
    {
    }

    con_sp_t& get()
    {
        return connection_;
    }

    con_wp_t getWp()
    {
        return {connection_};
    }

    void start()
    {
        connection_->start_session(/*std::move(wp)*/);
    }

    virtual void publish(topic_t topic_name, content_t content, const PublishOptions& publishOptions)
    {
        get()->publish(0,
                       std::string(topic_name.data(), topic_name.size()),
                       std::string(content.data(), content.size()),
                       convert(publishOptions.qualityOfService));
    }
};

using connections_t = std::set<std::shared_ptr<Connection>>;
} // namespace toad::communication_protocol::mqtt