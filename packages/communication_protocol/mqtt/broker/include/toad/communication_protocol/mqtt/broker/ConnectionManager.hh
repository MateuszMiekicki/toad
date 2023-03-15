#pragma once
#include "toad/communication_protocol/mqtt/broker/Connection.hh"

namespace toad::communication_protocol::mqtt
{
class ConnectionManager
{
  private:
    connections_t connections_;

  public:
    void addConnection(Connection::con_sp_t);
    void removeConnection(Connection::con_sp_t);
    void closeConnection(Connection::con_sp_t);
};
} // namespace toad::communication_protocol::mqtt