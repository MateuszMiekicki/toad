#include "toad/broker/mqtt/Mqtt.hh"
#include "toad/network/endpoint/Endpoint.hh"

namespace toad::broker::mqtt
{
Mqtt::~Mqtt()
{
}

Mqtt::Mqtt(const toad::network::Endpoint& endpoint, std::unique_ptr<interface::EventHandler> eventHandler) :
    brokerContext_{}, broker_(endpoint.endpoint(), brokerContext_), eventHandler_(std::move(eventHandler))
{
}

bool Mqtt::start()
{
    // broker_.listen();
    // brokerContext_.run();
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
