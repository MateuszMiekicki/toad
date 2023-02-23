#include "toad/communication_protocol/mqtt/mqtt_broker/Session.hh"

namespace toad::communication_protocol::mqtt::mqtt_broker
{
Session::Session(con_sp_t connection) : session_{connection}
{
}

bool Session::operator<(const Session&) const
{
    return true;
}

} // namespace toad::communication_protocol::mqtt::mqtt_broker
