#include "toad/communication_protocol/mqtt/mqtt_broker/Mqtt.hh"

#include "toad/communication_protocol/mqtt/Logger.hh"
#include "toad/communication_protocol/mqtt/mqtt_broker/BrokerEventHandler.hh"
#include "toad/network/endpoint/Endpoint.hh"

#include <mqtt_server_cpp.hpp>

namespace toad::communication_protocol::mqtt::mqtt_broker
{
Mqtt::~Mqtt()
{
}

Mqtt::Mqtt(const toad::network::Endpoint& endpoint, std::unique_ptr<interface::BrokerEventHandler> eventHandler) :
    brokerContext_{}, broker_(endpoint.endpoint(), brokerContext_), eventHandler_(std::move(eventHandler))
{
    broker_.set_error_handler(
        std::bind(&interface::BrokerEventHandler::onError, eventHandler_.get(), std::placeholders::_1));
    broker_.set_accept_handler(
        std::bind(&interface::BrokerEventHandler::onAccept, eventHandler_.get(), std::placeholders::_1));
}

bool Mqtt::start()
{
    INFO_LOG("mqtt broker start {}", 12);
    DEBUG_LOG("DEBUG_LOGmqtt broker start {}", 12);
    WARN_LOG("WARN_LOGmqtt broker start {}", 12);
    ERROR_LOG("ERROR_LOGmqtt broker start {}", 12);

    broker_.listen();
    brokerContext_.run();
    return true;
}

bool Mqtt::stop()
{
    return true;
}

bool Mqtt::restart()
{
    return true;
}
} // namespace toad::communication_protocol::mqtt::mqtt_broker
