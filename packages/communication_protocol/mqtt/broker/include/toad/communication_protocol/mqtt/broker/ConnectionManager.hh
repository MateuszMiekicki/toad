#pragma once
#include "toad/communication_protocol/mqtt/broker/Connection.hh"
#include "toad/communication_protocol/mqtt/client_validator/interface/IncomingClientValidator.hh"

namespace toad::communication_protocol::mqtt
{
struct Client;

class ConnectionManager
{
  private:
    connections_t connections_{};
    std::vector<std::unique_ptr<interface::IncomingClientValidator>> incomingClientValidator_{};

  public:
    ConnectionManager(std::vector<std::unique_ptr<interface::IncomingClientValidator>>);
    void addConnection(std::shared_ptr<Connection>);
    void removeConnection(std::shared_ptr<Connection>);
    void closeConnection(std::shared_ptr<Connection>);
    bool acceptConnection(const Client&) const;
};
} // namespace toad::communication_protocol::mqtt