#include "toad/communication_protocol/mqtt/mqtt_broker/Session.hh"

#include "toad/communication_protocol/mqtt/mqtt_broker/Mqtt.hh"
#include "toad/communication_protocol/mqtt/mqtt_broker/BrokerEventHandler.hh"
#include "toad/communication_protocol/mqtt/mqtt_broker/ClientEventHandler.hh"

#include "toad/network/endpoint/Endpoint.hh"

int main()
{
    // auto sessions = std::make_shared<toad::communication_protocol::mqtt::mqtt_broker::mqttSessions>(); 
    std::unique_ptr<toad::communication_protocol::mqtt::mqtt_broker::interface::ClientEventHandler> clientEventHandler = 
        std::make_unique<toad::communication_protocol::mqtt::mqtt_broker::ClientEventHandler>();
    std::unique_ptr<toad::communication_protocol::mqtt::mqtt_broker::interface::BrokerEventHandler> brokerEventHandler = 
        std::make_unique<toad::communication_protocol::mqtt::mqtt_broker::BrokerEventHandler>(std::move(clientEventHandler));
    const auto endpoint = toad::network::Endpoint();
    std::unique_ptr<toad::communication_protocol::mqtt::mqtt_broker::interface::Mqtt> mqtt = 
    std::make_unique<toad::communication_protocol::mqtt::mqtt_broker::Mqtt>(endpoint, std::move(brokerEventHandler));
    mqtt->start();
}