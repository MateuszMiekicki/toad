#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/mqtt/broker/Broker.hh"
#include "toad/communication_protocol/mqtt/broker/BrokerEventHandler.hh"
#include "toad/communication_protocol/mqtt/broker/ClientConnectionHandler.hh"
#include <memory>
#include <spdlog/spdlog.h>
#include <thread>

int main(int argc, char* argv[])
{
    spdlog::set_level(spdlog::level::info);
    using namespace toad::communication_protocol;
    using namespace toad::communication_protocol::mqtt;
    auto endpoint = Endpoint();
    if(argc == 3)
    {
        auto address = argv[1];
        auto port = static_cast<unsigned short>(std::stoi(argv[2]));
        endpoint = Endpoint(address, port);
    }

    std::vector<std::unique_ptr<interface::IncomingClientValidator>> incomingClientValidator;

    auto connectionManager = std::make_unique<ConnectionManager>(std::move(incomingClientValidator));

    std::unique_ptr<interface::ClientConnectionHandler> clientConnectionHandler =
        std::make_unique<ClientConnectionHandler>(std::move(connectionManager));
    std::unique_ptr<interface::BrokerEventHandler> brokerEventHandler =
        std::make_unique<BrokerEventHandler>(std::move(clientConnectionHandler));
    std::unique_ptr<interface::Broker> broker = std::make_unique<Broker>(endpoint, std::move(brokerEventHandler));
    broker->start();
}