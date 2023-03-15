#include "toad/communication_protocol/mqtt/broker/ConnectionManager.hh"

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
} // namespace toad::communication_protocol::mqtt