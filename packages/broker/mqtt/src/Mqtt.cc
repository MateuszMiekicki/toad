#include <mqtt_server_cpp.hpp>

#include "toad/broker/mqtt/Mqtt.hh"
#include "toad/network/endpoint/Endpoint.hh"
#include "toad/broker/mqtt/BrokerEventHandler.hh"

namespace toad::broker::mqtt
{
Mqtt::~Mqtt()
{
}

Mqtt::Mqtt(const toad::network::Endpoint& endpoint, std::unique_ptr<interface::BrokerEventHandler> eventHandler) :
    brokerContext_{}, broker_(endpoint.endpoint(), brokerContext_), eventHandler_(std::move(eventHandler))
{
    broker_.set_error_handler(std::bind(&interface::BrokerEventHandler::onError, eventHandler_.get(), std::placeholders::_1));
    broker_.set_accept_handler(std::bind(&interface::BrokerEventHandler::onAccept, eventHandler_.get(), std::placeholders::_1));
    // MQTT_NS::setup_log();
    
}

bool Mqtt::start()
{
    std::cout<<"start\n";
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
} // namespace toad::broker::mqtt
