#include "toad/communication_protocol/mqtt/broker/ConnectionManager.hh"

#include "toad/communication_protocol/mqtt/Logger.hh"

namespace toad::communication_protocol::mqtt
{
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

bool ConnectionManager::acceptConnection(const clientId_t& clientId) const
{
    return not clientId.empty();
}
} // namespace toad::communication_protocol::mqtt