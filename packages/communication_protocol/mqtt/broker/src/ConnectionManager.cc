#include "toad/communication_protocol/mqtt/broker/ConnectionManager.hh"

#include "toad/communication_protocol/mqtt/Logger.hh"

namespace toad::communication_protocol::mqtt
{
void ConnectionManager::addConnection(Connection::con_sp_t connection)
{
    connections_.insert(connection);
}

void ConnectionManager::removeConnection(Connection::con_sp_t connection)
{
    connections_.erase(connection);
}

void ConnectionManager::closeConnection(Connection::con_sp_t)
{
}

bool ConnectionManager::acceptConnection(const clientId_t& clientId) const
{
    return not clientId.empty();
}
} // namespace toad::communication_protocol::mqtt