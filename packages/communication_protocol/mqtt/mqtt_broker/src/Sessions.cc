#include "toad/communication_protocol/mqtt/mqtt_broker/Sessions.hh"

#include "toad/communication_protocol/mqtt/mqtt_broker/Session.hh"

namespace toad::communication_protocol::mqtt::mqtt_broker
{
bool Sessions::addSession(Session session)
{
    sessions_.insert(session);
}

bool Sessions::closeSession(Session)
{
}
} // namespace toad::communication_protocol::mqtt::mqtt_broker
