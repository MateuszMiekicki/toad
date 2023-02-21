#include "toad/broker/mqtt/Session.hh"

#include "toad/broker/mqtt/Mqtt.hh"
#include "toad/broker/mqtt/BrokerEventHandler.hh"
#include "toad/broker/mqtt/ClientEventHandler.hh"

#include "toad/network/endpoint/Endpoint.hh"

int main()
{
    // auto sessions = std::make_shared<toad::broker::mqtt::mqttSessions>(); 
    std::unique_ptr<toad::broker::mqtt::interface::ClientEventHandler> clientEventHandler = 
        std::make_unique<toad::broker::mqtt::ClientEventHandler>();
    std::unique_ptr<toad::broker::mqtt::interface::BrokerEventHandler> brokerEventHandler = 
        std::make_unique<toad::broker::mqtt::BrokerEventHandler>(std::move(clientEventHandler));
    const auto endpoint = toad::network::Endpoint();
    std::unique_ptr<toad::broker::mqtt::interface::Mqtt> mqtt = 
    std::make_unique<toad::broker::mqtt::Mqtt>(endpoint, std::move(brokerEventHandler));
    mqtt->start();
}