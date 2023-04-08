#include "toad/communication_protocol/mqtt/broker/ConnectionManager.hh"
#include "toad/communication_protocol/mqtt/client_validator/Client.hh"
#include "toad/communication_protocol/mqtt/Logger.hh"

namespace
{
bool runChecks(
    const std::vector<std::unique_ptr<toad::communication_protocol::mqtt::interface::IncomingClientValidator>>&
        incomingClientValidators,
    const toad::communication_protocol::mqtt::Client& client)
{
    for(const auto& validator: incomingClientValidators)
    {
        if(not validator->accept(client))
        {
            return false;
        }
    }
    return true;
}

} // namespace

namespace toad::communication_protocol::mqtt
{
ConnectionManager::ConnectionManager(std::vector<std::unique_ptr<interface::IncomingClientValidator>>
                                         incomingClientValidator) :
    incomingClientValidator_{std::move(incomingClientValidator)}
{
}

void ConnectionManager::addConnection(std::shared_ptr<Connection> connection)
{
    connections_.insert(connection);
}

void ConnectionManager::removeConnection(std::shared_ptr<Connection> connection)
{
    connections_.erase(connection);
}

void ConnectionManager::closeConnection(std::shared_ptr<Connection>)
{
}

bool ConnectionManager::acceptConnection(const Client& client) const
{
    return runChecks(incomingClientValidator_, client);
}
} // namespace toad::communication_protocol::mqtt