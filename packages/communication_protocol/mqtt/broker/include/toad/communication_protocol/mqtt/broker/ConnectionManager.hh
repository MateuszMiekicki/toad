#pragma once
#include "toad/communication_protocol/mqtt/broker/Connection.hh"

#include <string_view>

namespace toad::communication_protocol::mqtt
{
using clientId_t = std::string_view;

class ConnectionManager
{
  private:
    connections_t connections_;

  public:
    void addConnection(Connection::con_sp_t);
    void removeConnection(Connection::con_sp_t);
    void closeConnection(Connection::con_sp_t);
    bool acceptConnection(const clientId_t&) const;
};
} // namespace toad::communication_protocol::mqtt