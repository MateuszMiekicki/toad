#include "toad/communication_protocol/mqtt/broker/ClientConnectionHandler.hh"
#include <memory>
int main()
{
    using namespace toad::communication_protocol::mqtt;
    std::unique_ptr<interface::ClientConnectionHandler> clientConnectionHandler = 
    std::make_unique<ClientConnectionHandler>();
}