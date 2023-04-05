#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/mqtt/broker/Broker.hh"
#include "toad/communication_protocol/mqtt/broker/BrokerEventHandler.hh"
#include "toad/communication_protocol/mqtt/broker/ClientConnectionHandler.hh"
#include <memory>
#include <thread>

int main()
{
    using namespace toad::communication_protocol;
    using namespace toad::communication_protocol::mqtt;
    std::vector<std::unique_ptr<interface::IncomingClientValidator>> incomingClientValidator;

    auto connectionManager = std::make_unique<ConnectionManager>(std::move(incomingClientValidator));

    std::unique_ptr<interface::ClientConnectionHandler> clientConnectionHandler =
        std::make_unique<ClientConnectionHandler>(std::move(connectionManager));
    std::unique_ptr<interface::BrokerEventHandler> brokerEventHandler =
        std::make_unique<BrokerEventHandler>(std::move(clientConnectionHandler));
    std::unique_ptr<interface::Broker> broker = std::make_unique<Broker>(Endpoint(), std::move(brokerEventHandler));
    broker->start();
}