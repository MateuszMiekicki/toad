#include "toad/communication_protocol/mqtt/broker/BrokerEventHandler.hh"

#include "toad/communication_protocol/mqtt/broker/Connection.hh"
#include "toad/communication_protocol/mqtt/broker/ErrorCode.hh"

namespace toad::communication_protocol::mqtt
{
BrokerEventHandler::BrokerEventHandler(
    std::unique_ptr<toad::communication_protocol::mqtt::interface::ClientConnectionHandler>
        clientConnectionHandler) :
    clientConnectionHandler_{std::move(clientConnectionHandler)}
{
}

void BrokerEventHandler::onAccept(Connection connection)
{
    clientConnectionHandler_->onConnect(connection);
}

void BrokerEventHandler::onError(ErrorCode)
{
}
} // namespace toad::communication_protocol::mqtt