#include "toad/communication_protocol/mqtt/client_validator/LengthClientId.hh"

namespace toad::communication_protocol::mqtt
{
bool LengthClientId::check(const clientId_t& clientId) const
{
    return not clientId.empty();
}
} // namespace toad::communication_protocol::mqtt