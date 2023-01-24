#include "toad/broker/mqtt/Mqtt.hh"
#include "toad/broker/mqtt/EventHandler.hh"
#include "toad/network/endpoint/Endpoint.hh"

int main()
{
    // auto sessions = std::make_shared<toad::broker::mqtt::mqttSessions>(); 
    std::unique_ptr<toad::broker::mqtt::interface::EventHandler> EventHandler = 
        std::make_unique<toad::broker::mqtt::EventHandler>();
    const auto endpoint = toad::network::Endpoint("localhost", 12543);
    std::unique_ptr<toad::broker::mqtt::interface::Mqtt> mqtt = 
    std::make_unique<toad::broker::mqtt::Mqtt>(endpoint, std::make_unique<toad::broker::mqtt::EventHandler>());
    // mqtt->start();
}