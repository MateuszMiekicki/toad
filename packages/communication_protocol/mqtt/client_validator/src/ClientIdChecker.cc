#include "toad/communication_protocol/mqtt/client_validator/ClientIdChecker.hh"
#include "toad/communication_protocol/mqtt/client_validator/Client.hh"

namespace toad::communication_protocol::mqtt
{
bool ClientIdChecker::accept(const Client& client) const
{
    return not client.clientId.empty();
}
} // namespace toad::communication_protocol::mqtt