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
    void addConnection(std::shared_ptr<Connection>);
    void removeConnection(std::shared_ptr<Connection>);
    void closeConnection(std::shared_ptr<Connection>);
    bool acceptConnection(
        const clientId_t&) const; // todo(miekicki): remove from it and make better solution with more dynamic rules
};
} // namespace toad::communication_protocol::mqtt